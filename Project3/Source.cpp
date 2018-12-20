#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
	anuala,bianuala,perena
}Tip_planta;

typedef enum
{
	primavara,vara,toamna
}Perioada_inflor;

typedef struct nod
{
	char nume[30];
	float pret;
	Tip_planta tip;
	Perioada_inflor per;
	struct nod *st, *dr;
}nod;

nod *rad = NULL;
float suma;
nod *introducere(nod *t, char *nume, float pret, Tip_planta tip, Perioada_inflor per)
{
	if (t == NULL)
	{
		t = (nod*)malloc(sizeof(nod));
		strcpy(t->nume, nume);
		t->pret = pret;
		t->per = per;
		t->tip = tip;
		t->dr = NULL;
		t->st = NULL;
	}
	else
	{
		if (strcmp(t->nume, nume) < 0)
			t->dr = introducere(t->dr, nume, pret, tip, per);
		if (strcmp(t->nume, nume) > 0)
			t->st = introducere(t->st, nume, pret, tip, per);
	}
	return t;
}
void citire()
{
	FILE *f;
	f = fopen("plante.txt", "r");
	char nume[30];
	float pret;
	Tip_planta tip;
	Perioada_inflor per;
	while (!feof(f))
	{
		fscanf(f, "%s %d %f %d", nume, &tip, &pret, &per);
		rad = introducere(rad, nume, pret, tip, per);
	}
}
void afisare(nod *t)
{
	if (t != NULL)
	{
		afisare(t->dr);
		printf("Nume:%s\nTip:%d\nPret:%f\nPer:%d\n------------\n",t->nume,t->tip,t->pret,t->per);
		afisare(t->st);
	}
}
nod *twoson(nod *p, nod *t)
{
	nod *q,*aux;
	q = p;
	if (q->dr != NULL)
		q->dr = twoson(q->dr, t);
	else
	{
		strcpy(t->nume, q->nume);
		t->per = q->per;
		t->pret = q->pret;
		t->tip = q->tip;
		aux = q;
		q = q->st;
		free(aux);
		
	}
	return q;
}
nod *stergere(nod *t, char *nume)
{
	nod *aux;
	if (t == NULL)
		printf("nu exista nod");
	else
		if (strcmp(t->nume, nume) < 0)
			t->dr = stergere(t->dr, nume);
		else
			if (strcmp(t->nume, nume) > 0)
				t->st = stergere(t->st, nume);
			else
				if (t->st == NULL)
				{
					aux = t;
					t = t->dr;
					free(aux);
					return t;
				}
				else
					if (t->dr == NULL)
					{
						aux = t;
						t = t->st;
						free(aux);
						return t;
					}
					else

						t->st = twoson(t->st, t);
	return t;
}
void transv(nod *t,char *nume)
{
	FILE *f;
	f = fopen("fact.txt", "a");
	if (t != NULL) {
		transv(t->dr, nume);
		if (strcmp(t->nume, nume) == 0)
		{
			fprintf(f, "%s %d %f %d\n", t->nume, t->tip, t->pret, t->per);
			suma = suma + t->pret;
		}
		transv(t->st, nume);
	}
	fclose(f);
}
void cauta()
{
	FILE *f;
	f = fopen("fact.txt", "a");
	char nume[30];
	while (scanf("%s", nume) && strcmp(nume, "gata") != 0)
	{
		transv(rad, nume);
	}
	fprintf(f, "\n%f", suma);
	fclose(f);
}
int main()
{
	int opt;
	do
	{
		printf("opt=");
		scanf("%d", &opt);
		switch (opt)
		{
		case 1: 
		{
			citire();
			printf("\n\n%s",rad->nume);
			break;
		}
		case 2: 
		{
				 afisare(rad);
				 break;
		}
		 case 3 : 
		 {
						 char nume[30];
						 scanf("%s",nume);
						 stergere(rad,nume);
						 break;
		 }
		 case 4: {
			 cauta();
			 break;
		 }
		case 5: {
			exit(0);
			break;
		}
		default: {
			break;
				}
		}
	} while (opt != 5);
	return 0;
}