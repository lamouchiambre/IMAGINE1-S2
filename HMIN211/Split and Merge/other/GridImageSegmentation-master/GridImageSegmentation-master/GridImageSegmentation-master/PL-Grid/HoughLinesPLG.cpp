#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <algorithm>
#include <sys/stat.h>
#include "TxtImage.cpp"

using namespace std;

//Funkcja sumująca wszystkie elementy w wektorze
int sumVec(vector < int > &vec, int size , int mode)
{

	int sum = 0;
	int iul = vec.size();

	for (int i = 0; i < iul; ++i)
	{
		int a = vec[i] / size;
		int p = vec[i] - a * size;

		if (mode == 0)
		{
			sum += a;
		}
		else
		{
			sum += p;
		}
	}

	return sum;
}

//Funkcja wyznczająca skupienie elementów w wektorze "vec" względem punktu o współżędnych "a" i "p"
double focus(vector < int > &vec, int size, int a, int p)
{
	double foc = 0;

	int iul = vec.size();
	for (int i = 0; i < iul; ++i)
	{
		int ai = vec[i] / size;
		int pi = vec[i] - ai * size;

		foc += sqrt(pow(ai - a, 2) + pow(pi - p,2));
	}

	foc = foc / (vec.size());

	return foc;
}

//Funkcja rekurencyjna realizująca algorytm grupowania
vector < int > group(vector < int > &vec, int size, double focLimit)
{

	bool end = false;
	vector < int > gr1;
	vector < int > gr2;

	int a1 = vec[0] / size;
	int p1 = vec[0] - a1 * size;

	int a2 = vec[1] / size;
	int p2 = vec[1] - a2 * size;
	
	while(end == false)
	{
		gr1.clear();
		gr2.clear();

		int iul = vec.size();
		for (int i = 0; i < iul; ++i)
		{
			int ai = vec[i] / size;
			int pi = vec[i] - ai * size;

			if (sqrt(pow(ai - a1, 2) + pow(ai - a1, 2)) < sqrt(pow(pi - p2, 2) + pow(pi - p2, 2)))
			{
				gr1.insert(gr1.begin(), (ai*size) + pi);
			}
			else
			{
				gr2.insert(gr2.begin(), (ai*size) + pi);
			}
		}

		int a1j = a1;
		int p1j = p1;

		int a2j = a2;
		int p2j = p2;

		if (gr1.size() > 0)
		{
			a1j = sumVec(gr1, size, 0) / gr1.size();
			p1j = sumVec(gr1, size, 1) / gr1.size();
		}
		else
		{
			a2j = sumVec(gr2, size, 0) / gr2.size();
			p2j = sumVec(gr2, size, 1) / gr2.size();
			return vector<int> {a2j, p2j};
		}

		if (gr2.size() > 0)
		{
			a2j = sumVec(gr2, size, 0) / gr2.size();
			p2j = sumVec(gr2, size, 1) / gr2.size();
		}
		else
		{
			return vector<int> {a1j, p1j};
		}

		if (a1j == a1 && p1j == p1 && a2j == a2 && p2j == p2)
		{
			end = true;
		}
		else
		{
			a1 = a1j;
			p1 = p1j;

			a2 = a2j;
		    p2 = p2j;
		}
	}

	vector < int > tempvec;
	vector < int > resvec;
	double f = focus(gr1, size, a1, p1);

	if (f > focLimit)
	{
		tempvec = group(gr1, size, focLimit);

		for (int i = 0; i < tempvec.size(); ++i)
		{
			resvec.insert(resvec.begin() + resvec.size(), tempvec[i]);
		}
	}
	else
	{
		resvec.insert(resvec.begin() + resvec.size(), a1);
		resvec.insert(resvec.begin() + resvec.size(), p1);
	}

	f = focus(gr2, size, a2, p2);
	if (f > focLimit)
	{
		tempvec = group(gr2, size, focLimit);

		for (int i = 0; i < tempvec.size(); ++i)
		{
			resvec.insert(resvec.begin() + resvec.size(), tempvec[i]);
		}

	}
	else
	{
		resvec.insert(resvec.begin() + resvec.size(), a2);
		resvec.insert(resvec.begin() + resvec.size(), p2);
	}

	return resvec;
}

int main(int argc, char **argv)
{
	double PI = 3.14159265;
	int splitW = 3;
	int splitH = 3;
	string imagePath = "test.bmp";  //Obraz domyślny, wykorzystywany gdy nie zostanie podany obraz jako argument
	int c = 2;
	double temp;
	FILE *file;

	//Inicjacja piku statystycznego
	ofstream endfile;
	endfile.open("data.txt");



	//Sprawdzenie podanych argumentów
	switch (argc)
	{
	case 0:

		std::cout << "Nie podano obrazu, użyto obrazu testowego!\n";
		break;
	case 1:

		std::cout << "Nie podano obrazu, użyto obrazu testowego!\n";
		break;

	case 2:
		try
		{
			temp = std::stoi(argv[1]);
			std::cout << "Nie podano obrazu, użyto obrazu testowego!\n";
			splitW = temp;
			splitH = temp;

		}
		catch (const std::exception&)
		{
			struct stat buffer;
			if (!stat(argv[1], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[1];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
			}
		}
		break;

	case 3:
		try
		{
			c = 1;
			temp = std::stoi(argv[c++]);
			splitW = temp;
			splitH = temp;

			temp = std::stoi(argv[c++]);
			std::cout << "Nie podano obrazu, użyto obrazu testowego!\n";
			splitH = temp;

		}
		catch (const std::exception&)
		{
			struct stat buffer;
			if (!stat(argv[--c], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[c];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
				return(0);
			}
		}
		break;

	default:
		try
		{
			c = 1;
			temp = std::stoi(argv[c++]);
			splitW = temp;

			temp = std::stoi(argv[c++]);
			splitH = temp;

			struct stat buffer;
			if (!stat(argv[c], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[c];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
				return(0);
			}

		}
		catch (const std::exception&)
		{
			struct stat buffer;
			if (!stat(argv[--c], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[c];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
				return(0);
			}
		}
		break;
	}

	std::cout << "Podane argumenty: Podzial poziomo - " << splitW << ", podzial pionowo - " << splitH << ", obraz- " << imagePath << "\n";
	endfile << "Podane argumenty: Podzial poziomo - " << splitW << ", podzial pionowo - " << splitH << ", obraz- " << imagePath << "\n";

	TxtImage image(imagePath.c_str());

	//Pozyskanie proporcji obrazu
	int imgWidth = image.width();
	int imgHeight = image.height();

	//Próg skupienia
	double focLimit = 10;

	std::cout << "Liczba kolorów: " << image.spectrum() << "\n\n";

	vector< vector<int> > img_raw(imgWidth, vector<int>(imgHeight));

	int l = 180;

	std::cout << "Sinus: "<< sin(l* PI/180) << "  Cosinus: " << cos(l* PI / 180) <<"\n";

	int v = imgWidth * sin(0 / 180) + imgHeight * cos(0 / 180);

	vector< vector<int> > A(l, vector<int>(2*v));

	int upperlimit = imgWidth * imgHeight;


	for (int n = 0; n < upperlimit; ++n)
	{
		int i = n / imgHeight;
		int j = n - (i * imgHeight);

		img_raw[i][j] = image(i, j, 0, 0);
	}

	//Incjacja zbioru akumulatorów lokalnych (jeden akumulator na jeden analizowany fragment)
	vector< vector <vector<int>> > Apart(splitW*splitH, vector< vector<int> >(l, vector<int>(2*v)));

	upperlimit = splitW * splitH;

	//////Pętla realizująca działanie algorytmu segmentacji - wersja zrównoleglona (dokładne wytłumaczenie działania fragmentu znajduje się w pracy na str. 57) /////
#pragma omp parallel for 
	for (int itr = 0; itr < upperlimit; ++itr)
	{
		int i = itr / splitH;
		int j = itr - (i * splitH);

			std::cout << "Podzial zakonczony\n";

			int xul = round(imgWidth / splitH);
			int yul = round(imgHeight / splitH);
			int upperLimit = xul * yul;

			for (int n = 0; n < upperLimit; ++n)
			{
				int x = n / yul;
				int y = n - (x * yul);
				
				x = x + i * xul;
				y = y + j * yul;

				if (img_raw[x][y] > 200)
				{
					for (int a = 0; a < l; ++a)
					{
						double p = (x) * cos(a * PI / 180) + (y) * sin(a * PI / 180);
						//if (p > v) p = v - 1;

						if (p <= v) ++Apart[itr][a][v + (int)p];
					}
				}
			}

			cout << "Fragment przeanalizowany\n";
			int max = 0;
			 
			int upperlimit = l * 2 * v;

			for (int n = 0; n < upperlimit; ++n)
			{
				int a = n / (2 * v);
				int p = n - (a * 2 * v);

				if (max < Apart[itr][a][p]) max = Apart[itr][a][p];
			}

			for (int n = 0; n < upperlimit; ++n)
			{
				int a = n / (2 * v);
				int p = n - (a * 2 * v);

				if (Apart[itr][a][p] > 0)
				{
					int temp = Apart[itr][a][p];
					bool passed = true;

					if (p > 0 && Apart[itr][a][p - 1] > temp)
						passed = false;
					if (p < (2 * v) - 1 && Apart[itr][a][p + 1] > temp)
						passed = false;
					if (a > 0 && Apart[itr][a - 1][p] > temp)
						passed = false;
					if (a < l - 1 && Apart[itr][a + 1][p] > temp)
						passed = false;

					if (passed && Apart[itr][a][p] > max*0.9)
						++A[a][p];
				}
			}
	}
	
	TxtImage img(l, 2 * v, 1, 3);
	img.fill(0);
	int max = 0;

	upperlimit = l * 2 * v;

	//Znalezienie maksimum o najwyższej wartości
	for (int n = 0; n < upperlimit; ++n)
	{
		int a = n / (2 * v);
		int p = n - (a * 2 * v);

		if (max < A[a][p]) max = A[a][p];
	}

	vector < int > svec;
	//Umieszczenie wszystkich maksimów na obrazie i w wektorze
	for (int n = 0; n < upperlimit; ++n)
	{
		int a = n / (2 * v);
		int p = n - (a * 2 * v);

		if ((A[a][p]) > 0)
		{

			img(a, p, 0, 0) = 255;
			img(a, p, 0, 1) = 255;
			img(a, p, 0, 2) = 255;

			svec.insert(svec.begin() + svec.size(), a * A[a].size() + p);
		}
	}

	//Zapisanie obrazu przedstawiającego zawartość akumulatora globalnego
	string name = "Aku.bmp";
	string dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	img.save(dir.c_str());
	cout << "Obraz zapisany\n";

	endfile << "Liczba maksimów po segmentacji: " << svec.size() << "\n\n";

	//Faza grupowania

	int sa = sumVec(svec, A[0].size(), 0) / svec.size();
	int sp = sumVec(svec, A[0].size(), 1) / svec.size();

	//Wyznaczenie skupienia dla wszystkich maksimów
	int sfoc = focus(svec, A[0].size(), sa, sp);
	
	//Jeżeli skupienie jest więsze, niż próg, to uruchamiana jest funkcja grupująca, gdzie następnie 
	if (sfoc > focLimit)
	{
		vector < int > res2 = group(svec, A[0].size(), focLimit);

		TxtImage img(l, 2 * v, 1, 3);
		img.fill(0);

		TxtImage img2(imgWidth, imgHeight, 1, 3);
		img2.fill(0);

		for (int i = 0; i < res2.size()/2; ++i)
		{
			img(res2[i*2], res2[i*2 + 1], 0, 0) = 255;
			img(res2[i*2], res2[i * 2 + 1], 0, 1) = 255;
			img(res2[i*2], res2[i * 2 + 1], 0, 2) = 255;

			for (int x = 0; x < imgWidth; ++x)
			{
				int y = ((res2[i * 2 + 1] - v) - (x * cos(res2[i * 2] * (PI / 180)))) / sin(res2[i * 2] * (PI / 180));

				if (y > 0 && y < v)
				{
					img2(x, y, 0, 0) = 255;
					img2(x, y, 0, 1) = 255;
					img2(x, y, 0, 2) = 255;
				}
			}
		}

		endfile << "Liczba maksimów po grupowaniu: " << svec.size();

		name = "Group.bmp";
		dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
		img.save(dir.c_str());
		cout << "Obraz zapisany\n";

		name = "Segm.bmp";
		dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
		img2.save(dir.c_str());
		cout << "Obraz zapisany\n";

	}
	else
	{
		TxtImage img(l, 2 * v, 1, 3);
		img.fill(0);

		img(sa, sp, 0, 0) = 255;
		img(sa, sp, 0, 1) = 255;
		img(sa, sp, 0, 2) = 255;
		
		name = "Group.bmp";
		dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
		img.save(dir.c_str());
		cout << "Obraz zapisany\n";

		TxtImage img2(imgWidth, imgHeight, 1, 3);
		img2.fill(0);

		for (int x = 0; x < imgWidth; ++x)
		{
			int y = ((sp-v) - (x * cos(sa * (PI / 180)))) / sin(sa*(PI / 180));

			if (y > 0 && y < v)
			{
				img2(x, y, 0, 0) = 255;
				img2(x, y, 0, 1) = 255;
				img2(x, y, 0, 2) = 255;
			}
		}

		endfile << "Liczba maksimów po grupowaniu: 1";

		name = "Segm.bmp";
		img2.save(name.c_str());
		//dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
		//img2.save(dir.c_str());
		cout << "Obraz zapisany\n";
	}

	endfile.close();
}
 