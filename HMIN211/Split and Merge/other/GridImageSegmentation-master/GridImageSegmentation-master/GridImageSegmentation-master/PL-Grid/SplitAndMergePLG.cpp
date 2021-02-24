#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <fstream>
#include <sys/stat.h>
#include "TxtImage.cpp"

using namespace std;

//Funkcja wyszukująca minimalmną lub maksymalną intensywność piksela wśród danych stref 
int getMinMax(set<int> classes, vector<vector <int>> &img, map <int, vector<int> > &coordinates, bool isMax)
{
	set < int > ::iterator itr;
	int min = 255;
	int max = 0;
	double wyn = 0;

	for (itr = classes.begin(); itr != classes.end(); ++itr)
	{
		for (int i = coordinates[*itr][0]; i < coordinates[*itr][1]; i++)
		{
			for (int j = coordinates[*itr][2]; j < coordinates[*itr][3]; j++)
			{
				if (img[i][j] < min) min = img[i][j];
				if (img[i][j] > max) max = img[i][j];
			}
		}
	}

	if (isMax) { wyn = max; }
	else { wyn = min; }

	return wyn;
}

//Funkcja sumująca wszystkie elementy wektora vector
int Sum(vector< vector<int> > &vector, int xStart, int xEnd, int yStart, int yEnd)
{
	int sum = 0;
	for (int i = xStart; i < xEnd; i++)
	{
		for (int j = yStart; j < yEnd; j++)
		{
			sum += vector[i][j];
		}
	}

	int wyn = sum;

	return wyn;
}

//Funkcja wyznaczająca wariancję ze wszystkich pikseli wśród danych stref 
double Varian(set<int> classes, vector<vector <int>> &img, map <int, vector<int> > &coordinates)
{
	set < int > ::iterator itr;
	int sum = 0;
	int sumSq = 0;
	int counter = 0;
	double wyn1 = 0;
	double wyn2 = 0;

	int clsS = classes.size();

	for (itr = classes.begin(); itr != classes.end(); ++itr)
	{
		for (int i = coordinates[*itr][0]; i < coordinates[*itr][1]; i++)
		{
			for (int j = coordinates[*itr][2]; j < coordinates[*itr][3]; j++)
			{
				sum += img[i][j];
				sumSq += img[i][j] * img[i][j];
				++counter;
			}
		}
	}

	wyn1 = sumSq / counter  - ((sum / counter) * (sum / counter));

	double avg = sum / counter;
	sum = 0;
	counter = 0;

	for (itr = classes.begin(); itr != classes.end(); ++itr)
	{
		for (int i = coordinates[*itr][0]; i < coordinates[*itr][1]; i++)
		{
			for (int j = coordinates[*itr][2]; j < coordinates[*itr][3]; j++)
			{
				sum += (img[i][j] - avg) * (img[i][j] - avg);
				++counter;
			}
		}
	}

	wyn2 = sum / counter;

	return wyn2;
}


//Funkcja rekurencyjna realizująca etap podziału (dokładne wytłumaczenie działania fragmentu znajduje się w pracy na str. 50) /////
int Split(vector< vector<int> > &img, vector< vector<int> > &result, map <int, vector<int> > &class_list, double varMax, int splitMin, int rank, int xStart, int xEnd, int yStart, int yEnd)
{
	double var = 0;
	int xSize = xEnd - xStart;
	int ySize = yEnd - yStart;
	int avg = Sum(img, xStart, xEnd, yStart, yEnd) / ((xSize)*(ySize));

	for (int i = xStart; i < xEnd; i++)
	{
		for (int j = yStart; j < yEnd; j++)
		{
			var += (img[i][j] - avg) * (img[i][j] - avg);
			result[i][j] = result[i][j] * 10 + rank;
		}
	}

	var = var / ((xSize)*(ySize));

	if (var > varMax && (xSize > splitMin || ySize > splitMin))
	{
		Split(img, result, class_list, varMax, splitMin, 1, xStart, xStart + (xEnd - xStart) / 2, yStart, yStart + (yEnd - yStart) / 2);
		Split(img, result, class_list, varMax, splitMin, 2, xStart, xStart + (xEnd - xStart) / 2, yStart + (yEnd - yStart) / 2, yEnd);
		Split(img, result, class_list, varMax, splitMin, 3, xStart + (xEnd - xStart) / 2, xEnd, yStart, yStart + (yEnd - yStart) / 2);
		Split(img, result, class_list, varMax, splitMin, 4, xStart + (xEnd - xStart) / 2, xEnd, yStart + (yEnd - yStart) / 2, yEnd);
	}
	else
	{
		class_list[result[xStart][yStart]] = vector< int >{ xStart , xEnd , yStart , yEnd , avg };
	}

	return 0;
}

//Funkca zwracająca listę (kolekcję) sąsiadów danej strefy
set<int> getNeighbors(vector< vector<int> > &pool, int xStart, int xEnd, int yStart, int yEnd)
{
	set<int> result;

	for (int i = xStart; i < xEnd; ++i)
	{
		if (yStart - 1 > 0)
			result.insert(pool[i][yStart - 1]);

		if (yEnd + 1 < pool.size())
			result.insert(pool[i][yEnd + 1]);
	}

	for (int i = yStart; i < yEnd; ++i)
	{
		if (xStart - 1 > 0)
			result.insert(pool[xStart - 1][i]);
		if (xEnd + 1 < pool[0].size())
			result.insert(pool[xEnd + 1][i]);
	}

	return result;
}


//Funkcja przypisująca pikselowi ostateczną strefę, do której należy
int setOwners( map < int, int > &clOwn, map < int, set<int> > &clMer)
{ 

	for (auto const &itr : clMer)
	{
		for (auto const &itr2 : itr.second)
		{
			clOwn[itr2] = itr.first;
		}

	}

	return 0;
}

int main(int argc, char **argv)
{
	//Wartości domyślne parametrów minimpalnego rozmiary strefy i wariancji
	double variance = 0.005;
	double minSplit = 3;
	string imagePath = "test.bmp"; //Obraz domyślny, wykorzystywany gdy nie zostanie podany obraz jako argument
	int i = 2;
	double temp;
	FILE *file;

	ofstream endfile;
	endfile.open("data.txt");

	bool isVar = false;
	int avgPr = 15;

	//Sprawdzenie argumentów wejściowych
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
			variance = temp;

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
			i = 1;
			temp = std::stoi(argv[i++]);
			variance = temp;

			temp = std::stoi(argv[i++]);
			std::cout << "Nie podano obrazu, użyto obrazu testowego!\n";
			minSplit = temp;

		}
		catch (const std::exception&)
		{
			struct stat buffer;
			if (!stat(argv[--i], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[i];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
				return(0);
			}
		}
		break;
	case 4:
		try
		{
			i = 1;
			temp = std::stoi(argv[i++]);
			variance = temp;

			temp = std::stoi(argv[i++]);;
			minSplit = temp;

			struct stat buffer;
			if (!stat(argv[i], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[i];
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
			if (!stat(argv[--i], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[i];
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
			i = 1;
			temp = std::stoi(argv[i++]);
			variance = temp;

			temp = std::stoi(argv[i++]);;
			minSplit = temp;

			temp = std::stoi(argv[i++]);;
			if (temp) isVar = true;
			else isVar = false;

			struct stat buffer;
			if (!stat(argv[i], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[i];
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
			if (!stat(argv[--i], &buffer))
			{
				std::cout << "Obraz istnieje!!!\n";
				imagePath = argv[i];
			}
			else
			{
				std::cout << "Obraz nie istnieje!!!\n";
				return(0);
			}
		}
		break;
	}

	std::cout << "Podane argumenty: Wariancja- " << variance << ", prog- " << minSplit << ", obraz- " << imagePath << "\n";
	endfile << "Podane argumenty: Wariancja- " << variance << ", prog- " << minSplit << ", obraz- " << imagePath << "\n\n";

	//Załadowanie obrazu wejsciowego
	TxtImage image(imagePath.c_str());

	//Wyznaczenie proporcji obrazu
	int imgWidth = image.width();
	int imgHeight = image.height();

	std::cout << "Liczba kolorów: " << image.spectrum() << "\n\n";

	vector< vector<int> > img_raw(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_split(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_merge(imgWidth, vector<int>(imgHeight));

	map < int, vector<int> > img_class_list;

	map < int, int > classIntensity;
	map < int, int > classMin;
	map < int, int > classMax;

	int upperlimit = imgHeight * imgWidth;

	for (int n = 0; n < upperlimit; ++n)
	{
		int i = n / imgHeight;
		int j = n - (i * imgHeight);

		img_raw[i][j] = image(i, j, 0, 0);
		img_split[i][j] = 0;
	}


	//Uruchomienie funkcji rekurencyjnej realizującej fazę podziału
	Split(img_raw, img_split, img_class_list, variance, minSplit, 0, 0, imgWidth, 0, imgHeight);

	set < int > test;
	set < int > ::iterator itr;

	set < int > classList;

	map < int, set< int > > classNeighbors;

	//Umieszczenie każdej strefy w kolekcji i wyznaczenie ich wartości średniej minimalnej i maksymalnej (trzy różne kryteria homogeniczności)
	for (std::map< int, vector< int > >::iterator itr2 = img_class_list.begin(); itr2 != img_class_list.end(); ++itr2)
	{
		test = getNeighbors(img_split, itr2->second[0], itr2->second[1], itr2->second[2], itr2->second[3]);

		classNeighbors[itr2->first] = test;
		classIntensity[itr2->first] = itr2->second[4];
		classMin[itr2->first] = getMinMax({ itr2->first }, img_raw, img_class_list, false);
		classMax[itr2->first] = getMinMax({ itr2->first }, img_raw, img_class_list, true);

		classList.insert(itr2->first);
	}


	map < int, set< int > > classMerge;
	map < int, int > classOwner;

	bool working = true;
	set < int > ::iterator tempClass = classList.begin(); //Pierwsza strefa z listy, która będzie analizowana w fazie łączenia
	set < int > ::iterator tempNeigh;
	int mergeClass = 5 * pow(10, (int)log10(*(--classList.end()))); //Etykieta, którą bedą przyjmować strefy połączone

	int mergeNum = 0;
	bool next = true;

	//Zapisanie wyników fazy podziału do pliku

	TxtImage imgSplit(imgWidth, imgHeight, 1, 3);
	imgSplit.fill(0);

	for (i = 1; i < imgWidth - 1; ++i)
	{
		for (int j = 1; j < imgHeight - 1; ++j)
		{
			int currPxCls = img_split[i][j];
			if (currPxCls != img_split[i - 1][j])
			{
				imgSplit(i, j, 0, 0) = 255;
				imgSplit(i, j, 0, 1) = 0;
				imgSplit(i, j, 0, 2) = 0;
			}
			else if (currPxCls != img_split[i + 1][j])
			{
				imgSplit(i, j, 0, 0) = 255;
				imgSplit(i, j, 0, 1) = 0;
				imgSplit(i, j, 0, 2) = 0;
			}
			else if (currPxCls != img_split[i][j - 1])
			{
				imgSplit(i, j, 0, 0) = 255;
				imgSplit(i, j, 0, 1) = 0;
				imgSplit(i, j, 0, 2) = 0;
			}
			else if (currPxCls != img_split[i][j + 1])
			{
				imgSplit(i, j, 0, 0) = 255;
				imgSplit(i, j, 0, 1) = 0;
				imgSplit(i, j, 0, 2) = 0;
			}
			else
			{
				imgSplit(i, j, 0, 0) = img_raw[i][j];
				imgSplit(i, j, 0, 1) = img_raw[i][j];
				imgSplit(i, j, 0, 2) = img_raw[i][j];
			}
		}
	}

	string name = "Split.bmp";
	string dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	imgSplit.save(dir.c_str());

	endfile << "Liczba wyznaczonych stref po fazie podziału: " << img_class_list.size() <<"\n\n";

	set < int > tempNeighs;
	set < int > tempMerged;
	set < int > ::iterator itr2;

	//Pętla realizujaca fazę łączenia
	while (working) //Pętla realizowana do momentu aż nie będzie już stref, które są homogeniczne
	{
		next = true;
		for (itr = classNeighbors[*tempClass].begin(); itr != classNeighbors[*tempClass].end(); ++itr) //Dla każdej strefy sąsiadującą z tą analizowaną
		{
			tempNeigh = itr;
			
			//Jeżeli zostało wybrane kryterium średniej, to jest ono sprawdzane między dwoma strefami
			if ((isVar == false && (abs(classMin[*tempClass] - classMin[*tempNeigh]) < avgPr)) || isVar)
			{
				tempNeighs.clear();
				tempMerged.clear();

				if (*tempClass < mergeClass && *tempNeigh < mergeClass) //Sprawdzenie, czy obie strefy nie były wcześniej łączone
				{
					tempMerged = { *tempClass, *tempNeigh };

					if ((isVar && (Varian(tempMerged, img_raw, img_class_list) < variance)) || isVar == false) //Jeżeli zostało wybrane kryterium wariancji, to jest sprawdzane między dwoma strefami
					{
						/////Operacja łączenia dwóch stref w jedną nową/////

						for (itr2 = classNeighbors[*tempClass].begin(); itr2 != classNeighbors[*tempClass].end(); ++itr2)
						{
							if (*itr2 != *tempNeigh)
							{
								tempNeighs.insert(*itr2);
							}
						}

						for (itr2 = classNeighbors[*tempNeigh].begin(); itr2 != classNeighbors[*tempNeigh].end(); ++itr2)
						{
							if (*itr2 != *tempClass)
							{
								tempNeighs.insert(*itr2);
							}
						}

						next = false;
						int newMerge = ++mergeNum + mergeClass;

						//Aktualizacja odpowiednich tablic
						classOwner[*tempClass] = newMerge;
						classOwner[*tempNeigh] = newMerge;
						classNeighbors[newMerge] = tempNeighs;
						classList.insert(newMerge); //Umieszczenie w tablicy analizowanych stref nową strefę  
						classIntensity[newMerge] = (classIntensity[*tempClass] + classIntensity[*tempNeigh]) / 2;
						if (classMin[*tempClass] < classMin[*tempNeigh]) classMin[newMerge] = classMin[*tempClass];
						else classMin[newMerge] = classMin[*tempNeigh];
						if (classMax[*tempClass] > classMax[*tempNeigh]) classMax[newMerge] = classMax[*tempClass];
						else classMax[newMerge] = classMax[*tempNeigh];

						classMerge[newMerge] = { *tempClass,*tempNeigh };

						for (itr2 = tempNeighs.begin(); itr2 != tempNeighs.end(); ++itr2)
						{
							auto pos = classNeighbors[*itr2].find(*tempClass);
							if (pos != classNeighbors[*itr2].end())
							{
								classNeighbors[*itr2].erase(pos);
							}

							pos = classNeighbors[*itr2].find(*tempNeigh);
							if (pos != classNeighbors[*itr2].end())
							{
								classNeighbors[*itr2].erase(pos);
							}

							classNeighbors[*itr2].insert(newMerge);
						}

						//Usunięcie dwóch poprzednich stref z listy analizowanych
						classList.erase(*tempClass);
						classList.erase(*tempNeigh);
						break;
					}
				}
				else if (*tempClass > mergeClass) //Jeżeli aktualna strefa stanowi już polączenie kilku stref
				{

					if (*tempNeigh > mergeClass)  //Jeżeli również sąsiad stanowi już polączenie kilku stref
					{
						tempMerged.insert(classMerge[*tempClass].begin(), classMerge[*tempClass].end());
						tempMerged.insert(classMerge[*tempNeigh].begin(), classMerge[*tempNeigh].end());

						if ((isVar && (Varian(tempMerged, img_raw, img_class_list) < variance)) || isVar == false)  //Jeżeli zostało wybrane kryterium wariancji, to jest sprawdzane między dwoma strefami
						{
							/////Operacja przeniesienia wszystkich stref sąsiada do aktualnie analizowanej strefy łączonej/////

							for (itr2 = classNeighbors[*tempClass].begin(); itr2 != classNeighbors[*tempClass].end(); ++itr2)
							{
								if (*itr2 != *tempNeigh)
								{
									tempNeighs.insert(*itr2);
								}
							}

							for (itr2 = classNeighbors[*tempNeigh].begin(); itr2 != classNeighbors[*tempNeigh].end(); ++itr2)
							{
								if (*itr2 != *tempClass)
								{
									tempNeighs.insert(*itr2);
								}
							}

							next = false;
							//Aktualizacja odpowiednich tablic
							classOwner[*tempNeigh] = *tempClass;
							classIntensity[*tempClass] = (classIntensity[*tempClass] + classIntensity[*tempNeigh]) / 2;
							if (classMin[*tempClass] < classMin[*tempNeigh]) classMin[*tempClass] = classMin[*tempClass];
							else classMin[*tempClass] = classMin[*tempNeigh];
							if (classMax[*tempClass] > classMax[*tempNeigh]) classMax[*tempClass] = classMax[*tempClass];
							else classMax[*tempClass] = classMax[*tempNeigh];

							classMerge[*tempClass].insert(classMerge[*tempNeigh].begin(), classMerge[*tempNeigh].end());
							classMerge.erase(*tempNeigh); //Usunięcie sąsiada z listy stref połączonych

							for (itr2 = tempNeighs.begin(); itr2 != tempNeighs.end(); ++itr2)
							{
								auto pos = classNeighbors[*itr2].find(*tempNeigh);
								if (pos != classNeighbors[*itr2].end())
								{
									classNeighbors[*itr2].erase(pos);
								}

								classNeighbors[*itr2].insert(*tempClass);

							}
							classList.erase(*tempNeigh); //Usunięcie sąsiada z listy stref analizowanych
							classNeighbors[*tempClass] = tempNeighs;
							break;
						}
					}
					else //Jeżeli sąsiad jest niezłączoną strefą
					{
						tempMerged.insert(classMerge[*tempClass].begin(), classMerge[*tempClass].end());
						tempMerged.insert(*tempNeigh);

						if ((isVar && (Varian(tempMerged, img_raw, img_class_list) < variance)) || isVar == false) //Jeżeli zostało wybrane kryterium wariancji, to jest sprawdzane między dwoma strefami
						{
							/////Operacja połączenia sąsiada z aktualnie analizowaną strefą/////

							for (itr2 = classNeighbors[*tempClass].begin(); itr2 != classNeighbors[*tempClass].end(); ++itr2)
							{
								if (*itr2 != *tempNeigh)
								{
									tempNeighs.insert(*itr2);
								}
							}

							for (itr2 = classNeighbors[*tempNeigh].begin(); itr2 != classNeighbors[*tempNeigh].end(); ++itr2)
							{
								if (*itr2 != *tempClass)
								{
									tempNeighs.insert(*itr2);
								}
							}

							next = false;
							//Aktualizacja odpowiednich tablic
							classOwner[*tempNeigh] = *tempClass;
							classIntensity[*tempClass] = (classIntensity[*tempClass] + classIntensity[*tempNeigh]) / 2;
							if (classMin[*tempClass] < classMin[*tempNeigh]) classMin[*tempClass] = classMin[*tempClass];
							else classMin[*tempClass] = classMin[*tempNeigh];
							if (classMax[*tempClass] > classMax[*tempNeigh]) classMax[*tempClass] = classMax[*tempClass];
							else classMax[*tempClass] = classMax[*tempNeigh];

							classMerge[*tempClass].insert(*tempNeigh); //Umiesczenie sąsiada na liście pochłoniętych stref aktualnej strefy 

							for (itr2 = tempNeighs.begin(); itr2 != tempNeighs.end(); ++itr2)
							{
								auto pos = classNeighbors[*itr2].find(*tempNeigh);
								if (pos != classNeighbors[*itr2].end())
								{
									classNeighbors[*itr2].erase(pos);
								}

								classNeighbors[*itr2].insert(*tempClass);

							}
							classList.erase(*tempNeigh); //Usunięcie sąsiada z listy analizowanych stref
							classNeighbors[*tempClass] = tempNeighs;
							break;
						}
					}
				}
				else //Jeżeli sąsiad jest strefą zlączoną, a analizowana strefa nie
				{
					tempMerged.insert(classMerge[*tempNeigh].begin(), classMerge[*tempNeigh].end());
					tempMerged.insert(*tempClass);

					if ((isVar && (Varian(tempMerged, img_raw, img_class_list)) < variance)) //Jeżeli zostało wybrane kryterium wariancji, to jest sprawdzane między dwoma strefami
					{
						/////Operacja połączenia aktualnie analizowanej strefy z sąsiadem/////

						for (itr2 = classNeighbors[*tempClass].begin(); itr2 != classNeighbors[*tempClass].end(); ++itr2)
						{
							if (*itr2 != *tempNeigh)
							{
								tempNeighs.insert(*itr2);
							}
						}

						for (itr2 = classNeighbors[*tempNeigh].begin(); itr2 != classNeighbors[*tempNeigh].end(); ++itr2)
						{
							if (*itr2 != *tempClass)
							{
								tempNeighs.insert(*itr2);
							}
						}

						next = false;
						//Aktualizacja odpowiednich tablic
						classOwner[*tempClass] = *tempNeigh;
						classNeighbors[*tempNeigh] = tempNeighs;
						classIntensity[*tempNeigh] = (classIntensity[*tempClass] + classIntensity[*tempNeigh]) / 2;
						if (classMin[*tempClass] < classMin[*tempNeigh]) classMin[*tempNeigh] = classMin[*tempClass];
						else classMin[*tempNeigh] = classMin[*tempNeigh];
						if (classMax[*tempClass] > classMax[*tempNeigh]) classMax[*tempNeigh] = classMax[*tempClass];
						else classMax[*tempNeigh] = classMax[*tempNeigh];

						classMerge[*tempNeigh].insert(*tempClass); //Umieszczenie aktualnej tablicy w kolekcji sąsiada

						for (itr2 = tempNeighs.begin(); itr2 != tempNeighs.end(); ++itr2)
						{
							auto pos = classNeighbors[*itr2].find(*tempClass);
							if (pos != classNeighbors[*itr2].end())
							{
								classNeighbors[*itr2].erase(pos);
							}

							classNeighbors[*itr2].insert(*tempNeigh);

						}

						classList.erase(*tempClass); //Usunięcie aktualnej strefy z listy analizowanych stref
						break;
					}
				}
			}

		}
		if (next) //Jeżeli żaden z sąsiadów nie jest homogeniczny z aktualną strefą
		{
			//Analiza jest przełączana na kolejną strefę na liście
			tempNeigh = tempClass;
			++tempClass;
			//Jeżeli osiągnieto koniec listy analizowanych stref, to faza łączenia jest kończona
			if (tempClass == classList.end())
			{
				working = false;
			}
			classList.erase(*tempNeigh); //Usunięcie wcześniej analizowanej strefy z listy analizowanych stref
		}
		else //Jeżeli nie to analizuje się strefę będącą na szczycie listy analizowanych stref
		{
			tempClass = classList.begin();
		}
	}

	setOwners(classOwner, classMerge); //Przypisanie aktualnych właścicieli do wszystkich pierwotnych stref (będącymi wynikiem fazy podziału)

	img_merge = img_split;
	vector< vector<int> > img_bound(imgWidth, vector<int>(imgHeight));
	vector< vector<int> > img_result(imgWidth, vector<int>(imgHeight));

	for (int i = 0; i < imgWidth; ++i)
	{
#pragma omp parallel for 
		for (int j = 0; j < imgHeight; ++j)
		{
			img_merge[i][j] = classOwner[img_merge[i][j]];
			img_bound[i][j] = 0;
		}
	}

	//Zapisanie wyniku fazy łączenia do plików
	TxtImage img(imgWidth, imgHeight, 1, 3);
	TxtImage img2(imgWidth, imgHeight, 1, 3);

	img.fill(0);
	img2.fill(0);

	for (i = 1; i < imgWidth - 1; ++i)
	{
#pragma omp parallel for 
		for (int j = 1; j < imgHeight - 1; ++j)
		{
			int currPxCls = img_merge[i][j];
			if (currPxCls != img_merge[i - 1][j] || img_merge[i - 1][j] == 0)
			{
				img_bound[i][j] = 255;
				img(i, j, 0, 0) = 255;
				img(i, j, 0, 1) = 0;
				img(i, j, 0, 2) = 0;

				img2(i, j, 0, 0) = img(i, j, 0, 0);
			}
			else if (currPxCls != img_merge[i + 1][j] || img_merge[i - 1][j] == 0)
			{
				img_bound[i][j] = 255;
				img(i, j, 0, 0) = 255;
				img(i, j, 0, 1) = 0;
				img(i, j, 0, 2) = 0;

				img2(i, j, 0, 0) = img(i, j, 0, 0);
			}
			else if (currPxCls != img_merge[i][j - 1] || img_merge[i - 1][j] == 0)
			{
				img_bound[i][j] = 255;
				img(i, j, 0, 0) = 255;
				img(i, j, 0, 1) = 0;
				img(i, j, 0, 2) = 0;

				img2(i, j, 0, 0) = img(i, j, 0, 0);
			}
			else if (currPxCls != img_merge[i][j + 1] || img_merge[i - 1][j] == 0)
			{
				img_bound[i][j] = 255;
				img(i, j, 0, 0) = 255;
				img(i, j, 0, 1) = 0;
				img(i, j, 0, 2) = 0;

				img2(i, j, 0, 0) = img(i, j, 0, 0);
			}
			else
			{
				img(i, j, 0, 0) = 0;
				img(i, j, 0, 1) = 0;
				img(i, j, 0, 2) = 0;

				img2(i, j, 0, 0) = img_raw[i][j];
				img2(i, j, 0, 1) = img_raw[i][j];
				img2(i, j, 0, 2) = img_raw[i][j];
			}
		}
	}

	name = "Bounds.bmp";
	dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	img.save(dir.c_str());

	name = "All.bmp";
	dir = imagePath.substr(0, imagePath.find(".")) + "/" + name;
	img2.save(dir.c_str());

	endfile << "Liczba wyznaczonych stref po fazie podziału: " << classMerge.size() << "\n\n";

	endfile.close();

	std::cout << "Koniec" << "\n";
}
