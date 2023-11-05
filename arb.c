/* IMBREA GIULIA-STEFANIA 311 CB */ 
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "dir_file_arb.h"

TArb ConstrNod(void * x, TArb s, TArb d, TArb parinte) // ret. adresa nodului
{
  TArb aux = (TArb) malloc(sizeof(TNod)); // incearca alocare spatiu 
  if (!aux) return NULL; // spatiu insuficient
  aux -> info = x;
  aux -> st = s;
  aux -> dr = d; // actualizeaza campurile nodului 
  return aux; // intoarce adresa nodului sau NULL
}

TArb ConstrFr(void * x) // intoarce adresa frunzei sau NULL
{
  TArb aux = (TArb) malloc(sizeof(TNod));
  if (!aux) return NULL;
  aux -> info = x;
  aux -> st = aux -> dr = NULL;

  return aux;
}

void distruge(TArb r, void fct(void * )) // distruge toate nodurile 
{
  if (!r) return;
  distruge(r -> st, fct); // distruge subarborele stang 
  distruge(r -> dr, fct); // distruge subarborele drept
  fct(r -> info);
  free(r);
}

void DistrArb(TArb n, void fct(void * )) {
  if (!(n)) return;
  distruge(n, fct); // distruge toate nodurile
  n = NULL; //arborele este vid
}