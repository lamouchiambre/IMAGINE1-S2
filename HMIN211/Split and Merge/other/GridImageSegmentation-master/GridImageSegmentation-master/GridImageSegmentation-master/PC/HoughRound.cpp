#include "pch.h"
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
#include "CImg\CImg.h"
//#include "../TxtImage/TxtImage.cpp"

using namespace std;
using namespace cimg_library;

////Funkcja wyznaczająca okrąg na podstawie średnich wartości parametrów grupy okręgów
vector<int> getAvgRound(map < int, vector<int> > &middles)
{
	int nx = 0;
	int ny = 0;
	int nr = 0;
	int n = 0;

	for (auto itr = middles.begin(); itr != middles.end(); ++itr)
	{
		nx += itr->second[0];
		ny += itr->second[1];
		nr += itr->second[2];
		++n;
	}

	if (n)
	{
		return { nx / n, ny / n, nr / n };
	}
	else
	{
		return { 0, 0, 0 };
	}
	
}

////Funkcja wyznaczająca skupienie okręgów w grupie
int getFocus(map < int, vector<int> > &middles)
{
	int foc = 0;
	vector<int> fcsRnd = getAvgRound(middles);
	int n = 0;

	for (auto itr = middles.begin(); itr != middles.end(); ++itr)
	{
		foc += abs(fcsRnd[0] - itr->second[0]) + abs(fcsRnd[1] - itr->second[1]) + abs(fcsRnd[2] - itr->second[2]);
		++n;
	}
	
	if (foc)
	{
		return foc / n;
	}
	else
	{
		return 0;
	}
}

//Funkcja rekurencyjna realizująca fazę grupowania 
map < int, vector<int> > getGroup(map < int, vector<int> > &middles, int focLimit)
{
	bool work = true;

	map < int, vector<int> > firstGroup;
	map < int, vector<int> > secondGroup;

	vector<int> firstMiddle(3);
	vector<int> secondMiddle(3);

	vector<int> newFirstMiddle(3);
	vector<int> newSecondMiddle(3);

	firstMiddle = middles[0];

	for (int i = 1; i < middles.size(); ++i)
	{
		if (firstMiddle[0] != middles[i][0] || firstMiddle[1] != middles[i][1] || firstMiddle[2] != middles[i][2])
		{
			secondMiddle = middles[i];
			break;
		}
	}
	
	while (work)
	{
		firstGroup.clear();
		secondGroup.clear();

		for (auto itr = middles.begin(); itr != middles.end(); ++itr)
		{
			if ((abs(firstMiddle[0] - itr->second[0]) + abs(firstMiddle[1] - itr->second[1]) + abs(firstMiddle[2] - itr->second[2])) < (abs(secondMiddle[0] - itr->second[0]) + abs(secondMiddle[1] - itr->second[1]) + abs(secondMiddle[2] - itr->second[2])))
			{
				firstGroup[firstGroup.size()] = itr->second;
			}
			else
			{
				secondGroup[secondGroup.size()] = itr->second;
			}
		}

		newFirstMiddle = getAvgRound(firstGroup);
		newSecondMiddle = getAvgRound(secondGroup);

		if (firstMiddle == newFirstMiddle && secondMiddle == newSecondMiddle)
		{
			work = false;
		}

		firstMiddle = newFirstMiddle;
		secondMiddle = newSecondMiddle;
	}
	
	map < int, vector<int> > finalGroup;

	if (getFocus(firstGroup) > focLimit)
	{
		map < int, vector<int> > tempGroup;
		tempGroup = getGroup(firstGroup, focLimit);

		for (int itr = 0; itr < tempGroup.size(); ++itr)
		{
			finalGroup[finalGroup.size()] = tempGroup[itr];
		}
	}
	else
	{
		finalGroup[finalGroup.size()] = firstMiddle;
	}

	if (getFocus(secondGroup) > focLimit)
	{
		map < int, vector<int> > tempGroup;
		tempGroup = getGroup(secondGroup, focLimit);

		for (int itr = 0; itr < tempGroup.size(); ++itr)
		{
			finalGroup[finalGroup.size()] = tempGroup[itr];
		}
	}
	else
	{
		finalGroup[finalGroup.size()] = secondMiddle;
	}

	return finalGroup;

}

/////Dwie funkcje od rysowania okręgów na podstawie algorytmu Brensenham’a autorstwa Drashan’a Grjara/////

void addCircle(CImg<unsigned char> &img, int x, int y, int xt, int yt)
//void addCircle(TxtImage &img, int x, int y, int xt, int yt) //Funkcja rysująca piksele
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

void drawCircle(CImg<unsigned char> &img, int x, int y, int r)
//void drawCircle(TxtImage &img, int x, int y, int r) //Funkcja wyznaczająca piksele okręgów o zadanych parametrach x, y, r
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

////Dwie zmodyfikowane funkcje od rysowania okręgów zajmujace się wyliczniem aktywnych pikseli na obrazie na zadanym okręgu
int pxCircle(vector< vector<int> > &img, int x, int y, int xt, int yt)
{
	int counter = 0;

	if (img[x + xt][y + yt] > 200) ++counter;
	if (img[x - xt][y + yt] > 200) ++counter;
	if (img[x + xt][y - yt] > 200) ++counter;
	if (img[x - xt][y - yt] > 200) ++counter;
	if (img[x + yt][y + xt] > 200) ++counter;
	if (img[x - yt][y + xt] > 200) ++counter;
	if (img[x + yt][y - xt] > 200) ++counter;
	if (img[x - yt][y - xt] > 200) ++counter;

	return counter;
}

int getPxAmnt(vector< vector<int> > &img, int x, int y, int r)
{
	int xt = 0;
	int yt = r;
	int d = 3 - 2 * r;

	int counter = 0;

	counter += pxCircle(img, x, y, xt, yt);

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

		counter += pxCircle(img, x, y, xt, yt);
	}

	return counter;
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

	int deltaX = 10;
	int deltaY = 10;
	int deltaR = 2;

	int trshVal = 20;

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
			if (argc != 8)
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

				deltaX = std::stoi(argv[c++]);
				deltaY = std::stoi(argv[c++]);
				deltaR = std::stoi(argv[c++]);
				trshVal = std::stoi(argv[c++]);
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

	std::cout << "Podane argumenty: Podzial poziomo - " << splitW << ", podzial pionowo - " << splitH << ", obraz- " << imagePath << ", parametry redukcji (x,y,r,próg): " << deltaX << "," << deltaY << "," << deltaR << "," << trshVal << "\n";
	endfile << "Podane argumenty: Podzial poziomo - " << splitW << ", podzial pionowo - " << splitH << ", obraz- " << imagePath << ", parametry redukcji (x,y,r,próg): " << deltaX << "," << deltaY << "," << deltaR << "," << trshVal << "\n\n";

	CImg<unsigned char> image(imagePath.c_str());
	//TxtImage image(imagePath.c_str());

	//Pozyskanie proporcji obrazu
	int imgWidth = image.width();
	int imgHeight = image.height();

	//Próg skupienia
	double focLimit = 20;

	std::cout << "Liczba kolorów: " << image.spectrum() << "\n\n";

	vector< vector<int> > img_raw(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_part(imgWidth / splitW, vector<int>(imgHeight / splitH));

	//Zmienne wyznaczające przedział możliwych promieni wyznaczanych okręgów
	int rMin = 2;
	int rMax = imgWidth > imgHeight ? imgHeight / 2 : imgWidth / 2;

	//Inicjacja głównego akumulatora
	vector<int> A(rMax);

	int upperlimit = imgWidth * imgHeight;

	for (int n = 0; n < upperlimit; ++n)
	{
		int i = n / imgHeight;
		int j = n - (i * imgHeight);

		img_raw[i][j] = image(i, j, 0, 0);
	}


	map < int, vector<int> > middles;
	CImg<unsigned char> img(imgWidth, imgHeight, 1, 3);
	//TxtImage img(imgWidth, imgHeight, 1, 3);
	img.fill(0);

	upperlimit = splitW * splitH;

	//Incjacja zbioru akumulatorów lokalnych (jeden akumulator na jeden analizowany fragment)
	vector< vector<int> > Apart(upperlimit, vector<int>(rMax));

	vector< vector<int> > bestMid(upperlimit, vector<int>(4));
	int upperlimit2 = imgWidth * imgHeight;
	int upperlimit3 = floor(imgWidth / splitW) * floor(imgHeight / splitH);
	int fragWidth = floor(imgWidth / splitW);
	int fragHeight = floor(imgHeight / splitH);


	//////Pętla realizująca działanie algorytmu segmentacji - wersja zrównoleglona (dokładne wytłumaczenie działania fragmentu znajduje się w pracy na str. 62) /////
	#pragma loop( hint_parallel(0) )
	#pragma loop( ivdep )
	for (int n = 0; n < upperlimit; ++n)
	{
		int i = n / splitH;
		int j = n - (i * splitH);

		std::cout << "Podzial zakonczony\n";

		bestMid[n] = { 0, 0, 0, 0 };
		for (int m = 0; m < upperlimit2; ++m)
		{
						
			int x = m / imgHeight;
			int y = m - (x * imgHeight);


			for (int o = 0; o < upperlimit3; ++o)
			{
				int xq = o / fragHeight;
				int yq = o - (xq * fragHeight);

				xq = xq + (i * fragWidth);
				yq = yq + (j * fragHeight);

				if (img_raw[xq][yq] > 200)
				{
					int r = sqrt(((x - xq)*(x - xq)) + ((y - yq)*(y - yq)));
					if (r > rMin && r < rMax && r + x < imgWidth && x - r > 0 && y + r < imgHeight && y - r > 0)
					{
						Apart[n][r] = Apart[n][r] + 1;
					}
				}

			}

			int maxK = 0;
			int maxV = 0;

			for (int ri = 0; ri < rMax; ++ri)
			{
				if (Apart[n][ri] > maxV)
				{
					maxK = ri;
					maxV = Apart[n][ri];
				}
				Apart[n][ri] = 0;
			}

			if (bestMid[n][3] < maxV)
			{
				bestMid[n] = { x, y, maxK, maxV };
			}
		}

		std::cout << "Fragment przeanalizowany\n";
			
		if (bestMid[n][2] != 0)
		{
			middles[middles.size()] = bestMid[n];
			drawCircle(img, bestMid[n][0], bestMid[n][1], bestMid[n][2]);
		}

	}
	/////Koniec zrównoleglonej pętli/////

	endfile << "Liczba okręgów po segmentacji: " << middles.size() << "\n\n";

	string name = "Aku.bmp";
	img.save(name.c_str());

	std::cout << "Obraz zapisany\n";
	
	//////Faza redukcji

	//Wstawianie parametrów redukcji
	int wyn = 0;

	bool end = false;

	temp = 0;

	map < int, vector<int> > rdcdMiddles;

	//Pętla realizująca algorytm redukcji
	for (int itr = 0; itr < middles.size(); ++itr)
	{
		trshVal = 2 * PI * middles[itr][2] * 0.4;

		for (int x = middles[itr][0] - deltaX; x < middles[itr][0] + deltaX; ++x)
		{
			for (int y = middles[itr][1] - deltaY; y < middles[itr][1] + deltaY; ++y)
			{
				for (int r = middles[itr][2] - deltaR; r < middles[itr][2] + deltaR; ++r)
				{
					if (x - r >= 0 && x + r < imgWidth && y - r >= 0 && y + r < imgHeight)
					{
						wyn = getPxAmnt(img_raw, x, y, r);
						if (wyn > trshVal)
						{
							rdcdMiddles[rdcdMiddles.size()] = middles[itr];
							end = true;

							break;
						}
					}
				}

				if (end) break;
			}

			if (end) break;
		}

		end = false;
	}

	endfile << "Liczba okręgów po segmentacji: " << rdcdMiddles.size() << "\n\n";
	
	img.fill(0);

	//Rysowanie okręgów na obrazie 
	for (int itr = 0; itr < rdcdMiddles.size(); ++itr)
	{
		drawCircle(img, rdcdMiddles[itr][0], rdcdMiddles[itr][1], rdcdMiddles[itr][2]);
	}

	//Zapisanie obrazu z wyżnaczonymi okręgami po redukcji
	name = "Reduced.bmp";
	img.save(name.c_str());
	cout << "Obraz zapisany\n";

	//Faza grupowania
	
	int testFocus = getFocus(rdcdMiddles);
	map < int, vector<int> > grpdMiddles;

	//Jeżeli skupienie wyznaczonych okręgów jest większe, niż zadany limit, to uruchamiana jest funkcja grupowania
	if (getFocus(rdcdMiddles) > focLimit)
	{
		grpdMiddles = getGroup(rdcdMiddles, focLimit);
	}
	else //Jeżeli nie, to wyznaczany jest jeden okrąg
	{
		grpdMiddles[0] = getAvgRound(rdcdMiddles);
	}

	img.fill(0);
	
	//Rysowanie okręgów na obrazie 
	for (int itr = 0; itr < grpdMiddles.size(); ++itr)
	{
		drawCircle(img, grpdMiddles[itr][0], grpdMiddles[itr][1], grpdMiddles[itr][2]);
	}

	endfile << "Liczba okręgów po segmentacji: " << grpdMiddles.size() << "\n\n";
	endfile.close();

	//Zapisanie obrazu z wyżnaczonymi okręgami po grupowaniu
	name = "Grouped.bmp";
	img.save(name.c_str());
	cout << "Obraz zapisany\n";

}
