#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define DIR(a)((Director * )(a -> info))
#define FIS(a)((Fisier * )(a -> info))
typedef struct nod {
  void * info;
  struct nod * st, * dr;
}
TNod, * TArb, * nArb;

typedef struct Director {
  char * nume;
  TArb files;
  TArb directories;
  struct Director * parent; //pointer la directorul parinte
}
Director;

typedef struct {
  char * nume;
  Director * parent; //pointer la directorul parinte
}
Fisier;

void distruge(TArb r, void fct(void * )); //distruge toate nodurile
void DistrArb(TArb n, void fct(void * )); //distruge arborele
TArb ConstrNod(void * x, TArb s, TArb d, TArb parinte);
TArb ConstrFr(void * x);

void distrugeF(TArb a); //distruge arborele de fisiere 
void free_fis(void * fis); //elibereaza numele fisierului + fisier
Fisier * InitFisier(char * nume); //initielizeaza un fisier
void print_fis(TArb a); //acceseaza numele fisierului si il afiseaza

void distrugeD(TArb a); //distruge arborele de directoare
void free_dir(void * dir); //elibereaza numele directorului + director
void free_dir2(void * dir); //distruge tot directorul(subdirectoare+fisiere)
Director * InitDirector(char * nume); //initializeaza un director
void print_dir(TArb a); //acceseaza numele directorului si il afiseaza

/*functii de comparare nume fisiere/directoare in functie de tipul arborelui*/
int fcmp_dir_dir(TArb a, void * d);
int fcmp_fis_fis(TArb a, void * f);
int fcmp_dir_fis(TArb a, void * f);
int fcmp_fis_dir(TArb a, void * d);