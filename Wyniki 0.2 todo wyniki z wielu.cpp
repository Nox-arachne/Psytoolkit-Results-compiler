#include <stdio.h>
#include <stdlib.h>
#include<string.h>

	struct  wyniki_Stroop{ // Poszczególne kolumny to: liczba porzadkowa, l1, l2, l3, l4, czas
		int liczba_porzadkowa;
		char id[256];
		int wyniki[4][40];
		
	};
	
int main(int argc, const char *argv[])
{
char adres [150][256];
	
int i = 0;
FILE *fptr;
fptr = fopen("list.txt","r");
	
if (fptr == NULL)
	{
	printf("Error w trakcie otwierania pliku");
    exit(1);
	}

printf("Test funkcji fscanf(): \n\n");
printf("Liczba porzadkowa:\tAdres:\n");


while ( fscanf(fptr, " %*s %*s %*s %s", &adres[i]) != EOF )
{
printf("%i\t\t\t%s\n", i, adres[i]);
i++;
}
fclose(fptr);
// Koniec czêœci pierwszej: upload listy adresów.

struct wyniki_Stroop wynik[i]; //Zadeklarowana tablica struktur z wynikami
int n;

for(n=0; n<i; n++)
{

	strcpy(wynik[n].id, adres[n]);
//	wynik[n].id[sizeof(wynik[n].id-2)] = '\0';
} //Kopiowanie adresów do ID w poszczególnych instancjach struktury


/* for(n=0; n<i; n++)
{
	printf("%s", wynik[n].id);
} */ //Test 


	printf("\n ===Lista Wynikow zaladowana. Test importu wynikow===\n\n");	

printf("Wykryto %i zbiorow wynikow\n\n", i);

int lp=1, lzbioru = 0, lzadan = 0, licznik2 = 0;
FILE *dane[i-1]; 

while (lzbioru < i-1) 
{
printf("Zbior nr %i \nNazwa: [%s]\nLp.\tl1\tl2\tl3\tl4\tczas:\n", lzbioru+1, wynik[lzbioru].id);	
	dane[lzbioru] = fopen(("%s", adres[lzbioru]), "r");
	printf("lzbioru =%i\n", lzbioru);
	wynik[lzbioru].liczba_porzadkowa = lzbioru+1;
	while(lzadan < 41) // stala liczba przykladow dla danej gry; nie wiem czemu to dzia³a xD
	{
	while ( fscanf(dane[lzbioru ], "%*s %*s %*s %i %i %i %i %i", &wynik[lzbioru].wyniki[0][licznik2], 
															&wynik[lzbioru].wyniki[1][licznik2],
															&wynik[lzbioru].wyniki[2][licznik2],
															&wynik[lzbioru].wyniki[3][licznik2],
															&wynik[lzbioru].wyniki[4][licznik2]) != EOF)
		{
		printf("%i.\t%i\t%i\t%i\t%i\t%i\n", lp, 
											wynik[lzbioru].wyniki[0][licznik2], 
											wynik[lzbioru].wyniki[1][licznik2],
											wynik[lzbioru].wyniki[2][licznik2],
											wynik[lzbioru].wyniki[3][licznik2],
											wynik[lzbioru].wyniki[4][licznik2]);
			
		lp++;
		};
		lp = 1;
		lzadan++;
		
	};
fclose(dane[lzbioru]);
lzbioru++;	
licznik2 = 0;
}
	/*

int licznik = 0;
while (adres[licznik] != NULL)
{
	FILE *dane;
	dane = fopen(("%s", adres[licznik]), "r");
	wynik[licznik].liczba_porzadkowa = licznik+1;
	
	
	while ( fscanf(dane, " %*s %*s %*s %i %i %i %i %i", &wynik[licznik].wyniki[0], 
														&wynik[licznik].wyniki[1],
														&wynik[licznik].wyniki[2],
														&wynik[licznik].wyniki[3],
														&wynik[licznik].wyniki[4]) != EOF );
	{
	
	printf("%i.\t%i\t%i\t%i\t%i\t%i\n", wynik[i].liczba_porzadkowa, 
										wynik[licznik].wyniki[0], 
										wynik[licznik].wyniki[1],
										wynik[licznik].wyniki[2],
										wynik[licznik].wyniki[3],
										wynik[licznik].wyniki[4]);
	}
	licznik++;
	fclose(dane);
} */
	   return 0;
}
// printf("Zestaw %s\n***\n", adres[j]);
