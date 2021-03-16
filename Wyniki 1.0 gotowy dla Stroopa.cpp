#include <stdio.h>
#include <stdlib.h>
#include<string.h>

	struct  wyniki_Stroop{ // Poszczególne kolumny to: liczba porzadkowa, l1, l2, l3, l4, czas
		int liczba_porzadkowa;
		char id[256];
		int wyniki[4][40];
		
		
	};
	
int main()
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
// printf("%i\t\t\t%s\n", i, adres[i]);
i++;
}
fclose(fptr);

// Koniec części pierwszej: upload listy adresów.

struct wyniki_Stroop wynik[i]; //Zadeklarowana tablica struktur z wynikami
int n;

for(n=0; n<i; n++)
{

	strcpy(wynik[n].id, adres[n]);

}


/* for(n=0; n<i; n++)
{
	printf("%s", wynik[n].id);
} */ //Test 


	printf("\n ===Lista Wynikow zaladowana. Import wynikow...===\n\n");	

printf("Wykryto %i zbiorow wynikow\n\n", i);

int lzadan = 40, licznik2 = 0;
int suma[i-1], srednia[i-1];
FILE *dane[i-1]; 
FILE *output;

for (int lzbioru = 0, lp = 1; lzbioru < i-1; lzbioru++) 
{
	dane[lzbioru] = fopen(("%s", adres[lzbioru]), "r");
	wynik[lzbioru].liczba_porzadkowa = lzbioru+1;
	
	srednia[lzbioru] = 0;
	suma[lzbioru] = 0;

//	printf("lzbioru =%i\n", lzbioru); //test

printf("Zbior nr %i \nNazwa: [%s]\nLp.\tl1\tl2\tl3\tl4\tczas:\n", wynik[lzbioru].liczba_porzadkowa, wynik[lzbioru].id);	//napisz adres
	
	for(int x = 0; x <= lzadan; x++) // stala liczba przykladow dla danej gry; nie wiem czemu to działa xD
	{
		while ( fscanf(dane[lzbioru ], "%*s %*s %*s %i %i %i %i %i", &wynik[lzbioru].wyniki[0][x], 
															&wynik[lzbioru].wyniki[1][x],
															&wynik[lzbioru].wyniki[2][x],
															&wynik[lzbioru].wyniki[3][x],
															&wynik[lzbioru].wyniki[4][x]) != EOF)
			{
		/*	printf("%i.\t%i\t%i\t%i\t%i\t%i\n", lp, 
											wynik[lzbioru].wyniki[0][x], 
											wynik[lzbioru].wyniki[1][x],
											wynik[lzbioru].wyniki[2][x],
											wynik[lzbioru].wyniki[3][x],
											wynik[lzbioru].wyniki[4][x]); */
			srednia[lzbioru] += wynik[lzbioru].wyniki[4][x];
			suma[lzbioru] += wynik[lzbioru].wyniki[0][x];
			lp++;
			};
		
	};
		fclose(dane[lzbioru]);
		lp=1;
		srednia[lzbioru] /= lzadan;
		printf("Wyniki:\nSredni czas = %i\nSuma dobrych odpowiedzi = %i /%i\n\n", srednia[lzbioru], suma[lzbioru], lzadan);
	
		
}
	printf("\n ===Wyniki przetworzone. Eksportowanie wynikow...===\n\n");
	
	FILE *results;
	results = fopen("results.csv", "w");
	fprintf(results, "Liczba_porzadkowa;Nazwa_pliku;Suma_poprawnych;Sredni_czas\n");
	for (n = 0; n <= i; n++)
	{
		fprintf(results, "%i;%s;%d;%d\n", wynik[n].liczba_porzadkowa, wynik[n].id, suma[n], srednia[n]);
	} 
	fclose(results);
	
	
	results = fopen("Opis_wynikow.txt", "w");

	fprintf(results, "Kolumna 1: Liczba porzadkowa,\nKolumna 2: Nazwa pliku zrodlowego\nKolumna 3: Suma poprawnych odpowiedzi\nKolumna 4: Sredni czas odpowiedzi w ms.");
 
	fclose(results);
	
	printf("\n ===Utworzono pliki wynikow.===\n\n");
	

	   return 0;
}

