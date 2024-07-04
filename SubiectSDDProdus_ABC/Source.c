#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Produs
{
	unsigned short int id;
	char* denumire;
	unsigned short int stoc;
	unsigned char nrClienti;
	unsigned short int* stocuriLaClienti;
}Produs;
typedef struct Nod
{
	Produs* info;
	struct Nod* left;
	struct Nod* right;
}Nod;
Produs* initializareProdus(unsigned short int id, char* denumire, unsigned short int stoc,
	unsigned char nrClienti, unsigned short int* storuiLaClienti)
{
	Produs* produs = (Produs*)malloc(sizeof(Produs));
	produs->id = id;
	produs->denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(produs->denumire, denumire);
	produs->stoc = stoc;
	produs->nrClienti = nrClienti;
	produs->stocuriLaClienti = (unsigned short int*)malloc(sizeof(unsigned short int) * (nrClienti));
	for (int i = 0; i < nrClienti; i++)
	{
		produs->stocuriLaClienti[i] = storuiLaClienti[i];
	}
	return produs;
}
Nod* initializareNod(Produs* produs)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->left = NULL;
	nodNou->right = NULL;
	return nodNou;
}
Nod* inserareProdus(Nod* radacina, Produs* produs)
{
	if (radacina == NULL)
	{
		return initializareNod(produs);
	}
	else if (produs->id < radacina->info->id)
	{
		radacina->left = inserareProdus(radacina->left, produs);
	}
	else if (produs->id > radacina->info->id)
	{
		radacina->right = inserareProdus(radacina->right, produs);
	}
	return radacina;
}
void afisareInOrdine(Nod* radacina)
{
	if (radacina != NULL)
	{
		afisareInOrdine(radacina->left);
		printf("%hu %s %hu %hhu\n", radacina->info->id, radacina->info->denumire,
			radacina->info->stoc, radacina->info->nrClienti);
		for (int i = 0; i < radacina->info->nrClienti; i++) {
			printf(" %hu", radacina->info->stocuriLaClienti[i]);
		}
		printf("\n");

		afisareInOrdine(radacina->right);
	}
}
void dezalocare(Nod* radacina)
{
	if (radacina != NULL)
	{
		dezalocare(radacina->left);
		dezalocare(radacina->right);
		free(radacina->info->denumire);
		free(radacina->info->stocuriLaClienti);
		free(radacina->info);
		free(radacina);

	}
}
//nr de prod cu stoc mai mare decat un prag dat ca param
int nrProd(Nod* radacina, int prag)
{
	int contor = 0;
	if (radacina != NULL)
	{
		if (radacina->info->stoc > prag)
		{
			contor++;
		}
		contor += nrProd(radacina->left, prag);
		contor += nrProd(radacina->right, prag);
	}
	return contor;
}
//determinati valoarea stocului mediu la clienti pt un produs dat ca id in paramametru
float valStocMediu(Nod* radacina, unsigned short int id)
{
	float valoare = 0;
	if (radacina != NULL)
	{
		if (radacina->info->id == id)
		{
			for (int i = 0; i < radacina->info->nrClienti; i++)
			{
				valoare = valoare + radacina->info->stocuriLaClienti[i];
			}
			return valoare / radacina->info->nrClienti;

		}
		else if(radacina->info->id > id)
		{
			return valStocMediu(radacina->left, id);
		}
		else if (radacina->info->id < id)
		{
			return valStocMediu(radacina->right, id);
		}
	}
}
//stergeti nodul radacina->afisare inordine 
Nod* stergereRadacine(Nod* radacina)
{
	if (radacina == NULL)
	{
		return NULL;
	}
	if (radacina != NULL)
	{

	}
}


void main() 
{
	FILE* f = fopen("Produs.txt", "r");
	if (f != NULL)
	{
		char bufferline[300], split_line[] = ",\n";
		Nod* radacina = NULL;
		while (fgets(bufferline, sizeof(bufferline), f))
		{
			char* token = strtok(bufferline, split_line);
			unsigned short int id = (unsigned short int)atoi(token);

			token = strtok(NULL, split_line);
			char* denumire = (char*)malloc(sizeof(char)*( strlen(token) + 1));
			strcpy(denumire, token);

			token = strtok(NULL, split_line);
			unsigned short int stoc = (unsigned short int)atoi(token);

			token = strtok(NULL, split_line);
			unsigned char nrClienti = (unsigned char)atoi(token);

			token = strtok(NULL, split_line);
			
			unsigned short int* stocuriLaClienti = (unsigned short int*)malloc(sizeof(unsigned short int) * nrClienti);
			for (int i = 0; i < nrClienti; i++) {
				
				stocuriLaClienti[i] = (unsigned short int)atoi(token);
				token = strtok(NULL, split_line);
			}

			Produs* produs = initializareProdus(id, denumire, stoc, nrClienti, stocuriLaClienti);
			radacina = inserareProdus(radacina,produs);

	

		}
		fclose(f);
		afisareInOrdine(radacina);

		printf("Cerinta2: \n");
		int nr = 0;
		nr = nrProd(radacina, 600);
		printf("%d", nr);

		printf("Cerinta3: \n");
		float val = 0;
		val = valStocMediu(radacina, 1);
		printf("%5.2f", val);












		dezalocare(radacina);
	}
}