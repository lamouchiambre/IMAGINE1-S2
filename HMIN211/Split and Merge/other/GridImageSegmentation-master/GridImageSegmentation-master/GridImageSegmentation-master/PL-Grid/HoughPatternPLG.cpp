#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <queue>
#include <cmath>
#include <algorithm>
#include <sys/stat.h>
#include "TxtImage.cpp"

using namespace std;

/////Dwie funkcje od rysowania okręgów na podstawie algorytmu Brensenham’a autorstwa Drashan’a Grjara/////

void addCircle(TxtImage &img, int x, int y, int xt, int yt) //Funkcja rysująca piksele
{
	img(x + xt, y + yt, 0, 0) = 255;
	img(x - xt, y + yt, 0, 0) = 255;
	img(x + xt, y - yt, 0, 0) = 255;
	img(x - xt, y - yt, 0, 0) = 255;
	img(x + yt, y + xt, 0, 0) = 255;
	img(x - yt, y + xt, 0, 0) = 255;
	img(x + yt, y - xt, 0, 0) = 255;
	img(x - yt, y - xt, 0, 0) = 255;
}

void drawCircle(TxtImage &img, int x, int y, int r) //Funkcja wyznaczająca piksele okręgów o zadanych parametrach x, y, r 
{
	int xt = 0;
	int yt = r;
	int d = 3 - 2 * r;

	addCircle(img, x, y, xt, yt);

	while (yt >= xt)
	{
		xt++;

		if (d > 0)
		{
			yt--;
			d = d + 4 * (xt - yt) + 10;
		}
		else
		{
			d = d + 4 * xt + 6;
		}

		addCircle(img, x, y, xt, yt);
	}
}

int main(int argc, char **argv)
{
	double PI = 3.14159265; //Stała pikseli
	string imagePath = "test.bmp"; //Obraz domyślny, wykorzystywany gdy nie zostanie podany obraz jako argument
	string patternPath = "patterntest.bmp"; //Wzór domyślny, wykorzystywany gdy nie zostanie podany wzór jako argument
	int c = 2;
	double temp;
	FILE *file;

	ofstream endfile;
	endfile.open("data.txt");
	
	//Sprawdzenie podanych argumentów
	if(argc != 3)
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

	if (!stat(argv[2], &buffer))
	{
		std::cout << "Wzorzec istnieje!!!\n";
		patternPath = argv[2];
	}
	else
	{
		std::cout << "Wzorzec nie istnieje!!!\n";
		return(0);
	}

	std::cout << "Podane argumenty: Obraz - " << imagePath << ", wzorzec - " << patternPath << "\n";
	endfile << "Podane argumenty: Obraz - " << imagePath << ", wzorzec - " << patternPath << "\n\n";

	//Pobranie obrazu
	TxtImage image(imagePath.c_str());

	//Wyznaczenie proporcji obrazu
	int imgWidth = image.width();
	int imgHeight = image.height();

	//Pobranie wzorca
	TxtImage pattern(patternPath.c_str());

	//Wyznaczenie proporcji wzorca
	int pttrnWidth = pattern.width();
	int pttrnHeight = pattern.height();

	map < int, vector<int> > imgPxs;
	map < int, vector<int> > pttrnPxs;

	int upperLim = imgWidth * imgHeight;

	//Umieszczenie współżędnych aktywnych pikseli obrazu do mapy
	for (int n = 0; n < upperLim; ++n)
	{
		int i = n / imgHeight;
		int j = n - (i * imgHeight);

		int temp = image(i, j, 0, 0);
		if (temp > 200)
		{
			imgPxs[imgPxs.size()] = { i, j };
		}
	}

	upperLim = pttrnWidth * pttrnHeight;

	//Umieszczenie współżędnych aktywnych pikseli wzorca do mapy
	for (int n = 0; n < upperLim; ++n)
	{
		int nl = n;

		int x = nl / pttrnWidth;
		int y = nl - (x * pttrnWidth);


		int temp = pattern(x, y, 0, 0);
		if (temp > 200)
			pttrnPxs[pttrnPxs.size()] = {x, y};
		
	}

	//Zapis danych do pliku statystycznego
	endfile << "Liczba aktywnych pikseli w obrazie wejściowym: " << imgPxs.size() << "\n";
	endfile << "Liczba aktywnych pikseli we wzorcu: " << pttrnPxs.size() << "\n\n";

	vector< vector <vector<int>> > A3d(imgWidth, vector< vector<int> >(imgHeight, vector<int>(360)));
	int xr = 0;
	int yr = 0;
	
	int imgPxsS = imgPxs.size();

	upperLim = pttrnPxs.size() * 360 * imgPxs.size();

	//////Fragment kodu realizujący działanie algorytmu segmentacji - wersja zrównoleglona (dokładne wytłumaczenie działania fragmentu znajduje się w pracy na str. 64) /////
	//Pętla wykonująca operację generowania akumulatora
#pragma omp parallel for 
	for (int n = 0; n < upperLim; ++n)
	{
		int pttrItr = n / (360 * imgPxsS);
		int st2n = n - (pttrItr * (360 * imgPxsS));
		int imgItr = st2n / 360;
		int a = st2n - (imgItr * 360);

		int x = pttrnPxs[pttrItr][0];
		int y = pttrnPxs[pttrItr][1];

		int xpart = xr + (x - xr) * cos(a * PI / 180) - (y - yr) * sin(a * PI / 180);
		int ypart = yr + (x - xr) * sin(a * PI / 180) + (y - yr) * cos(a * PI / 180);

		int xn = imgPxs[imgItr][0];
		int yn = imgPxs[imgItr][1];

		int xt = xn - xpart;
		int yt = yn - ypart;

		if (xt >= 0 && xt < imgWidth && yt >= 0 && yt < imgHeight)
		{
			++A3d[xt][yt][a];
		}

	}

	std::cout << "Koniec algorytmu\n";
	
	int valMax = 0;
	vector< vector<int> > A2d(imgWidth, vector<int>(imgHeight));

	vector<int> best(3);

	upperLim = imgWidth * imgHeight;

	//Pętla wykonująca konwersję akumulatora na postać dwuwymiarową
#pragma omp parallel for 
	for (int n = 0; n < upperLim; ++n)
	{

		int x = n / (imgHeight);
		int y = n - (x * imgHeight);

		int aMax = 0;
		for (int a = 0; a < 360; ++a)
		{
			if (A3d[x][y][a] > aMax)
			{
				aMax = A3d[x][y][a];
				if (aMax > valMax)
				{
					valMax = aMax;
					best = { x,y,a };
				}
			}
		}

		A2d[x][y] = aMax;
	}

	TxtImage img(imgWidth, imgHeight, 1, 3);
	img.fill(0);

	//Zapisanie dwuwymiarowego akumulatora do pliku
#pragma omp parallel for 
	for (int n = 0; n < upperLim; ++n)
	{
		int valMaxL = valMax;

		int x = n / (imgHeight);
		int y = n - (x * imgHeight);

		img(x, y, 0, 0) = 255 - ((A2d[x][y] / valMaxL) * 255);
		img(x, y, 0, 1) = 255 - ((A2d[x][y] / valMaxL) * 255);
		img(x, y, 0, 2) = 255 - ((A2d[x][y] / valMaxL) * 255);
	}

	string name = "Aku2d.bmp";
	string dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	img.save(dir.c_str());
	cout << "Akumulator zapisany\n";

	//Dorysowanie okręgu do obrazu wejściowego w miejsce znalezionego kształtu
	drawCircle(image, best[0] + (pttrnWidth / 2), best[1] + (pttrnHeight / 2), (pttrnWidth / 2));

	//Zapisanie obrazu wyjściowego
	name = "Found.bmp";
	dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	image.save(dir.c_str());
	cout << "Obraz zapisany\n";
}
