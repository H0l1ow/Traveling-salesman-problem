#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits.h>

using namespace std;


const int n = 16;
int droga = 0;
int D[n][n];
int odwiedzone[n] = {0};
string nazwy_miast[16] = { "Bialystok", "Bydgoszcz", "Gdansk", "Gorzow Wielkopolski", "Katowice","Kielce", "Krakow", "Lublin", "Lodz", "Olsztyn", "Opole", "Poznan", "Rzeszow", "Szczecin", "Warszawa", "Wroclaw" };

void wczytywanie_danych()
{

	fstream fileOpen;
	fileOpen.open("przyklad.txt");

	if (!fileOpen.is_open())
	{
		cout << "Blad! Brak pliku badz problem z uprawnieniami :(" << endl;
	}
	else
	{

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				fileOpen >> D[i][j];
			}
			//odwiedzone[i] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(4);
			cout << D[i][j];
		}
		cout << endl;
	}


	fileOpen.close();

}

int ostatnia_droga(int c)
{
	int i, nc = INT_MAX;
	int min = INT_MAX, kmin;

	for (i = 0; i < n; i++)
	{
		if ((D[c][i] != 0) && (odwiedzone[i] == 0))
			if (D[c][i] + D[i][c] < min)
			{
				min = D[i][c] + D[c][i];
				kmin = D[c][i];
				nc = i;
			}
	}

	if (min != INT_MAX)
		droga += kmin;

	return nc;
}

void minimalny_koszt(int miasto)
{
	int nmiasto = 0;

	odwiedzone[miasto] = 1;

	cout << " " << miasto + 1 << ": " << nazwy_miast[miasto] << "--->";

	nmiasto = ostatnia_droga(miasto);

	if (nmiasto == INT_MAX)
	{
		nmiasto = 0;
		cout << nmiasto + 1;
		droga += D[miasto][nmiasto];

		return;
	}

	minimalny_koszt(nmiasto);
}

int main()
{	

		int x = 0;

		wczytywanie_danych();

		cout << endl;

		for (int i = 0; i < n; i++) {
			cout << i + 1 << ": " << nazwy_miast[i] << " ";
			if ((i + 1) % 6 == 0)
			{
				cout << endl;
			}

		}
		do {
			cout << "\n\nWprowadz miasto poczatkowe (1-16): "; cin >> x;
		} while (x > 16 || x < 1);
		cout << "Czyli: " << nazwy_miast[x - 1];

		cout << "\n\nDroga komiwojazera:\n";
		cout << "========================\n\n";
		minimalny_koszt(x - 1);

		cout << "\n\nIlosc kilometrow: " << droga << endl;

}
