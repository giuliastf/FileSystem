/* IMBREA GIULIA-STEFANIA 311 CB */
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "dir_file_arb.h"

void free_fis(void * fis) {
  if (!fis) return;
  free(((Fisier * )(fis)) -> nume);
  free(fis);
}

void distrugeF(TArb a) { // distruge toate fisierele din sistem
  if (a == NULL) // n am ce elimina
    return;
  distrugeF(DIR(a) -> directories);
  if (a -> st != NULL)
    distrugeF(a -> st);
  if (a -> dr != NULL)
    distrugeF(a -> dr); //a este frunza, director cu arbore de fisiere
  DistrArb(DIR(a) -> files, free_fis);
}

void distrugeD(TArb a) {
  if (a == NULL) // n am ce elimina
    return;
  distrugeD(DIR(a) -> directories);
  if (a -> st != NULL)
    distrugeD(a -> st);
  if (a -> dr != NULL)
    distrugeD(a -> dr);
  free_dir(DIR(a)); // a este frunza, director
  free(a);
}

void free_dir(void * dir) {
  if (!dir) return;
  free(((Director * )(dir)) -> nume);
  free(dir);
}

void free_dir2(void * dir) { //distruge un director + tot ceea ce contine
  DistrArb(((Director * )(dir)) -> files, free_fis);
  distrugeF(((Director * )(dir)) -> directories);
  distrugeD(((Director * )(dir)) -> directories);
  free_dir(dir);
}

Director * InitDirector(char * nume) {
  Director * dir = (Director * ) malloc(sizeof(Director));
  if (!dir)
    return NULL;
  dir -> nume = calloc(51, 1);
  strncpy(dir -> nume, nume, strlen(nume));
  dir -> directories = NULL;
  dir -> files = NULL;
  dir -> parent = NULL;
  return dir;
}

Fisier * InitFisier(char * nume) {
  Fisier * f = (Fisier * ) malloc(sizeof(Fisier));
  if (!f)
    return NULL;
  f -> nume = calloc(51, 1);
  strncpy(f -> nume, nume, strlen(nume));
  f -> parent = NULL;
  return f;
}

int fcmp_dir_dir(TArb a, void * d) {
  return strcmp(DIR(a) -> nume, ((Director * )(d)) -> nume);
}
int fcmp_fis_fis(TArb a, void * f) {
  return strcmp(FIS(a) -> nume, ((Fisier * )(f)) -> nume);
}
int fcmp_dir_fis(TArb a, void * f) {
  return strcmp(DIR(a) -> nume, ((Fisier * )(f)) -> nume);
}
int fcmp_fis_dir(TArb a, void * d) {
  return strcmp(FIS(a) -> nume, ((Director * )(d)) -> nume);
}
void print_dir(TArb a) {
  printf("%s ", DIR(a) -> nume);
}
void print_fis(TArb a) {
  printf("%s ", FIS(a) -> nume);
}