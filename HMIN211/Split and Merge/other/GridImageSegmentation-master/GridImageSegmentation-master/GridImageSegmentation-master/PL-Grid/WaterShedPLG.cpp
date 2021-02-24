#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include "TxtImage.cpp"
#include <cmath>
#include <sys/stat.h>
#include <algorithm>

using namespace std;


int main(int argc, char **argv)
{
	//inicjacja stałych 
	const int INQUEUE = -3;
	const int MASK = -2;
	const int INIT = -1;
	const int WSHEED = 0;

	string imagePath = "test.bmp"; //Obraz domyślny, wykorzystywany gdy nie zostanie podany obraz jako argument
	int i = 2;
	double temp;
	FILE *file;

	//Inicjacja pliku statystycznego
	ofstream endfile;
	endfile.open("data.txt");

	//sprawdzenie argumentów wejściowych
	if (argc != 2)
	{
		std::cout << "Zla liczba argumentow\n";
		return(0);
	}

	struct stat buffer;
	if (!stat(argv[1], &buffer))
	{
		std::cout << "Obraz istnieje!!!\n";
		imagePath = argv[1];
	}
	else
	{
		std::cout << "Obraz nie istnieje!!! Blad - " << stat(argv[1], &buffer) << "\n";
		return(0);
	}

	//Załadowanie obrazu wejściowego
	std::cout << "Podane argumenty: Obraz- " << imagePath << "\n";
	endfile << "Podane argumenty: Obraz- " << imagePath << "\n\n";
	TxtImage image(imagePath.c_str());

	//Odczytanie proporcji obrazu
	int imgWidth = image.width();
	int imgHeight = image.height();

	std::cout << "Liczba kolorów: " << image.spectrum() << "\n\n";

	vector< vector<int> > img_raw(imgWidth, vector<int>(imgHeight));

	queue< int > fifo;
	vector < pair <int, int> > brightness(imgHeight*imgWidth);
	map<int, pair<int, int> > coordinates;
	map<int, bool> flag;

	int upperlimit = imgWidth * imgHeight;

	for (int n = 0; n < upperlimit; ++n)
	{
		int i = n / imgHeight;
		int j = n - i * imgHeight;

		img_raw[i][j] = image(i, j, 0, 0);
	}


	 
	/////Algorytm obliczający gradient Sobela autorstwa Jamala Ahmeda Rahima//////
	vector< vector<int> > img2dhororg(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img2dverorg(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img2dmag(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_tamy(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_out(imgWidth, vector<int>(imgHeight));

	///horizontal
	int max = -200, min = 2000; 

	for (int i = 1; i < imgHeight - 1; i++) {
		for (int j = 1; j < imgWidth - 1; j++) {
			int curr = img_raw[i - 1][j - 1] + 2 * img_raw[i - 1][j] + img_raw[i - 1][j + 1] - img_raw[i + 1][j - 1] - 2 * img_raw[i + 1][j] - img_raw[i + 1][j + 1];
			img2dhororg[i][j] = curr;
			if (curr > max) max = curr;
			if (curr < min) min = curr;
		}
	}


	///vertical:
	max = -200; min = 2000;

	for (int i = 1; i < imgHeight - 1; i++) {
		for (int j = 1; j < imgWidth - 1; j++) {
			int curr = img_raw[i - 1][j - 1] + 2 * img_raw[i][j - 1] + img_raw[i + 1][j - 1] - img_raw[i - 1][j + 1] - 2 * img_raw[i][j + 1] - img_raw[i + 1][j + 1];
			img2dverorg[i][j] = curr;
			if (curr > max) max = curr;
			if (curr < min) min = curr;
		}
	}

	///magnitude
	max = -200; min = 2000;

	for (int i = 0; i < imgHeight; i++) {
		for (int j = 0; j < imgWidth; j++) {
			img2dmag[i][j] = sqrt(pow(img2dhororg[i][j], 2) + pow(img2dverorg[i][j], 2));
			if (img2dmag[i][j] > max) max = img2dmag[i][j];
			if (img2dmag[i][j] < min) min = img2dmag[i][j];
		}
	}

	int diff = max - min;

	for (int i = 0; i < imgHeight; i++) {
		for (int j = 0; j < imgWidth; j++) {
			float abc = (img2dmag[i][j] - min) / (diff*1.0);
			img2dmag[i][j] = abc * 255;
		}
	}

	////Koniec algorytmu//////

	/////Zapis gradientu do pliku i umieszczenie jego pikseli w tablicy
	image.fill(0);
	for (int i = 0; i < imgHeight; i++) {
		for (int j = 0; j < imgWidth; j++) {
			image(i, j, 0, 0) = img2dmag[i][j];
			image(i, j, 0, 1) = img2dmag[i][j];
			image(i, j, 0, 2) = img2dmag[i][j];

			brightness[i*imgHeight + j].first = img2dmag[i][j];
			brightness[i*imgHeight + j].second = i * imgHeight + j;

			flag[i*imgHeight + j] = false;
			img_out[i][j] = INIT;
		}
	}

	string name = "sobel.bmp";
	string dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	image.save(dir.c_str());

	int curLabel = 0;
	std::sort(brightness.begin(),brightness.end());
	int curPx = 0;
	int lastPx = 0;

	//////Pętla realizująca działanie algorytmu segmentacji - wersja zrównoleglona (dokładne wytłumaczenie działania fragmentu znajduje się w pracy na str. 53) /////
	for (int h = 0; h < 256; ++h)
	{
		curPx = lastPx;
		while (curPx < brightness.size() && brightness[curPx].first == h)
		{
			int x = brightness[curPx].second / imgHeight;
			int y = brightness[curPx].second - (x * imgHeight);
			img_out[x][y] = MASK;

			vector< vector<int> > neighs(4, vector<int>(2));
			neighs[0][0] = x - 1; neighs[0][1] = y; neighs[1][0] = x + 1; neighs[1][1] = y;
			neighs[2][0] = x; neighs[2][1] = y - 1; neighs[3][0] = x; neighs[3][1] = y + 1;

			for (int i = 0; i < 4; ++i)
			{
				int nx = neighs[i][0];
				int ny = neighs[i][1];
				if (!(nx < 0 || nx > imgHeight - 1 || ny < 0 || ny > imgWidth - 1))
				{
					if (img_out[nx][ny] == WSHEED || img_out[nx][ny] > 0)
					{
						img_out[x][y] = INQUEUE;
						fifo.push(brightness[curPx].second);

						break;
					}
				}
			}

			++curPx;
		}

		while(!fifo.empty())
		{ 

			int x = fifo.front() / imgHeight;
			int y = fifo.front() - (x * imgHeight);
			vector< vector<int> > neighs(4, vector<int>(2));
			neighs[0][0] = x - 1; neighs[0][1] = y; neighs[1][0] = x + 1; neighs[1][1] = y;
			neighs[2][0] = x; neighs[2][1] = y - 1; neighs[3][0] = x; neighs[3][1] = y + 1;

#pragma omp parallel for 
			for (int i = 0; i < 4; ++i)
			{
				int nx = neighs[i][0];
				int ny = neighs[i][1];

				if (!(nx < 0 || nx > imgHeight - 1 || ny < 0 || ny > imgWidth - 1))
				{
					if (img_out[nx][ny] > 0)
					{
						if (img_out[x][y] == INQUEUE || (img_out[x][y] == WSHEED && flag[x*imgHeight + y] == true))
						{
							img_out[x][y] = img_out[nx][ny];
						}
						else if (img_out[x][y] > 0 && img_out[x][y] != img_out[nx][ny])
						{
							img_out[x][y] = WSHEED;
							flag[x*imgHeight + y] = false;
						}
					}
					else if (img_out[nx][y - 1] == WSHEED)
					{
						if (img_out[x][y] == INQUEUE)
						{
							img_out[x][y] = WSHEED;
							flag[x*imgHeight + y] = true;
						}
					}
					else if (img_out[nx][ny] == MASK)
					{
						img_out[nx][ny] = INQUEUE;
						fifo.push((nx * imgHeight) + ny);

					}

				}
			}

			fifo.pop();
		}

		curPx = lastPx;
		while (curPx < brightness.size() && brightness[curPx].first == h)
		{
			int x = brightness[curPx].second / imgHeight;
			int y = brightness[curPx].second - (x * imgHeight);

			if (img_out[x][y] == MASK)
			{
				fifo.push(brightness[curPx].second);
				img_out[x][y] = ++curLabel;

				while (!fifo.empty())
				{

					int nx = fifo.front() / imgHeight;
					int ny = fifo.front() - (nx * imgHeight);
					vector< vector<int> > neighs(4, vector<int>(2));
					neighs[0][0] = nx - 1; neighs[0][1] = ny; neighs[1][0] = nx + 1; neighs[1][1] = ny;
					neighs[2][0] = nx; neighs[2][1] = ny - 1; neighs[3][0] = nx; neighs[3][1] = ny + 1;

#pragma omp parallel for 
					for (int i = 0; i < 4; ++i)
					{
						int n2x = neighs[i][0];
						int n2y = neighs[i][1];

						if (!(n2x < 0 || n2x > imgHeight - 1 || n2y < 0 || n2y > imgWidth - 1))
						{
							if (img_out[n2x][n2y] == MASK)
							{
								fifo.push((n2x * imgHeight) + n2y);
								img_out[n2x][n2y] = curLabel;
							}
						}
					}
					fifo.pop();

				}
			}
			++curPx;
		}
		lastPx = curPx;
	}

	std::cout << "Koniec";

	endfile << "Liczba wyznczonych basenów: " << curLabel << "\n\n";

	vector<int> cuntLabel(curLabel);
	int cuntSheeds = 0;

	/////Koniec działania pętli/////

	////Zapis wyznaczonych tam do pliku
	image.fill(0);
	for (int i = 0; i < imgHeight; i++) 
	{
		for (int j = 0; j < imgWidth; j++) 
		{
			int tymval = 0;

			if (img_out[i][j] == 0)
			{
				tymval = 255;
				++cuntSheeds;
			}
			else
			{
				tymval = 0;
				if (img_out[i][j] > 0) ++cuntLabel[img_out[i][j] - 1];
			}

			image(i, j, 0, 0) = tymval;
			image(i, j, 0, 1) = tymval;
			image(i, j, 0, 2) = tymval;
		}
	}


	//Zapis danych do pliku statystycznego
	endfile << "Liczba pikseli jako tamy: " << cuntSheeds << "\n\n";

	for (int i = 0; i < curLabel; i++)
	{
		endfile << "Liczba pikseli w basenie " << i + 1 << ": " << cuntLabel[i] << "\n";
	}

	endfile.close();

	name = "tamy.bmp";
	dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	image.save(dir.c_str());

	////Zapis wyznaczonych stref i tam do pliku
	for (int i = 0; i < imgHeight; i++)
	{
		for (int j = 0; j < imgWidth; j++)
		{
			int tymval = 0;

			if (img_out[i][j] > 0)
			{
				tymval = img_out[i][j] * 40;
			}
			else
			{
				tymval = 0;
			}

			image(i, j, 0, 0) = tymval;
			image(i, j, 0, 1) = tymval;
			image(i, j, 0, 2) = tymval;
		}
	}

	name = "wynik.bmp";
	dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	image.save(dir.c_str());

	std::cout << "Zapisano";
}

