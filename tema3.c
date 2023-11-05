/* IMBREA GIULIA-STEFANIA 311 CB */ 
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "dir_file_arb.h"

/*insereaza lexicografic un director/fisier in arborele specificat*/
int insert(TArb * a, void * x, int fcmp(TArb, void * )) {
  if ( * a == NULL) { //arborele este vid
    * a = ConstrFr(x);
    return 0;
  }
  if (fcmp( * a, x) == 0) { //exista deja un director/fisier cu acelasi nume
    return -1;
  }
  if (fcmp( * a, x) > 0) {
    if (( * a) -> st == NULL) { //verific iarasi daca se potriveste numele
      ( * a) -> st = ConstrFr(x);
      return 1;
    }
    return insert( & ( * a) -> st, x, fcmp); //nu am gasit nimic, reapelez
  }
  if (fcmp( * a, x) < 0) {
    if (( * a) -> dr == NULL) {
      ( * a) -> dr = ConstrFr(x);
      return 1;
    }
    return insert( & ( * a) -> dr, x, fcmp);
  }
  return 0;
}

TArb search(TArb r, void * x, int fcmp(TArb, void * )) {
  if (r == NULL)
    return NULL; //NULL daca nu a gasit un folder/file cu acelasi nume
  if (fcmp(r, x) == 0) {
    return r;
  }
  if (fcmp(r, x) < 0)
    return search(r -> dr, x, fcmp);
  return search(r -> st, x, fcmp);
}

void ls(TArb a, void f(TArb)) { //listeaza continutul unui director
  if (a == NULL) //director gol
    return;
  ls(a -> st, f);
  f(a); //functie de print
  ls(a -> dr, f);
}

TArb min(TArb a) { //returneaza adresa celui mai "mic" cuvant dpdv lexicografic
  if (a -> dr == NULL && a -> st == NULL)
    return a;
  if (a -> st != NULL)
    return min(a -> st);
  else
    return a;
}

/* sterge un director/ fisier din arbore*/
TArb delete(TArb a, void * x, int fcmp(TArb, void * ), void elib(void * )) {
  static int ok = 0;
  if (a == NULL) //nu am ce sterge
    return NULL;
  else if (fcmp(a, x) > 0)
    a -> st = delete(a -> st, x, fcmp, elib);
  else if (fcmp(a, x) < 0)
    a -> dr = delete(a -> dr, x, fcmp, elib);
  else { //am gasit elementul de sters
    if (a -> st == NULL && a -> dr == NULL) { //caz1: elementul este o frunza
      if (ok == 0)
        elib(a -> info);
      free(a);
      a = NULL;
    } else if (a -> st == NULL) { //caz2: are un copil
      TArb aux = a;
      a = a -> dr;
      elib(aux -> info);
      free(aux);

    } else if (a -> dr == NULL) {
      TArb aux = a;
      a = a -> st;
      elib(aux -> info);
      free(aux);
    } else { //caz3: 2 copii
      ok = 1;
      TArb aux = min(a -> dr);
      elib(a -> info);
      a -> info = aux -> info;
      a -> dr = delete(a -> dr, aux -> info, fcmp, elib);
    }
  }
  return a;
}

void pwd(Director * curr) {
  if (strcmp(curr -> nume, "root") == 0) {
    printf("/root");
    return;
  } else {
    pwd(curr -> parent);
    printf("/%s", curr -> nume);
  }
}

//find_d(root->directories, dir)
void find_d(TArb a, Director * dir, TArb * found) {
  if (a == NULL)
    return;
  TArb p = search(a, dir, fcmp_dir_dir);
  if (p != NULL) {
    * found = p;
  } else { //nu am gasit
    find_d(DIR(a) -> directories, dir, found); //caut in subdirectoare
    if (a -> st != NULL)
      find_d(a -> st, dir, found);
    if (a -> dr != NULL)
      find_d(a -> dr, dir, found);
  }
}

//root->directories
void find_f(TArb a, Fisier * fis, TArb * found) {
  if (a == NULL)
    return;
  TArb p = search(DIR(a) -> files, fis, fcmp_fis_fis);
  if (p != NULL) {
    * found = p;
    return; //adresa unde am gasit elem
  } else { //in toate cazurile trb sa caut in subdir din radacina arborelui
    find_f(DIR(a) -> directories, fis, found);
    if (a -> st != NULL)
      find_f(a -> st, fis, found);
    if (a -> dr != NULL)
      find_f(a -> dr, fis, found);
  }
  return;
}

int main() {
  char line[200];
  char * cuv;
  Director * root = InitDirector("root");
  Director * curr = root;
  //TArb root = ConstrFr(curent);
  while (fgets(line, 200, stdin)) {
    cuv = strtok(line, " \n");
    if (strcmp(cuv, "touch") == 0) {
      cuv = strtok(NULL, " \n");
      Fisier * f = InitFisier(cuv); //initializez structura fisier
      //mai intai verific daca exista un director cu acelasi nume
      f -> parent = curr;
      if (search(curr -> directories, f, fcmp_dir_fis) != NULL) {
        printf("Directory %s already exists!\n", cuv);
        free_fis(f);
      } else if (insert( & curr -> files, f, fcmp_fis_fis) == -1) {
        printf("File %s already exists!\n", cuv);
        free_fis(f);
      }
    }
    if (strcmp(cuv, "mkdir") == 0) {
      cuv = strtok(NULL, " \n");
      Director * dir = InitDirector(cuv); //initializez structura fisier
      dir -> parent = curr;
      if (search(curr -> files, dir, fcmp_fis_dir) != NULL) {
        printf("File %s already exists!\n", cuv);
        free_dir(dir);
      } else if (insert( & curr -> directories, dir, fcmp_dir_dir) == -1) {
        printf("Directory %s already exists!\n", cuv);
        free_dir(dir);
      }
    }
    if (strcmp(cuv, "ls") == 0) {
      ls(curr -> directories, print_dir);
      ls(curr -> files, print_fis);
      printf("\n");
    }
    if (strcmp(cuv, "rm") == 0) {
      cuv = strtok(NULL, " \n");
      Fisier * f = InitFisier(cuv);
      if (search(curr -> files, f, fcmp_fis_fis) == NULL)
        printf("File %s doesn't exist!\n", cuv);
      else
        curr -> files = delete(curr -> files, f, fcmp_fis_fis, free_fis);
      free_fis(f);
    }
    if (strcmp(cuv, "rmdir") == 0) {
      cuv = strtok(NULL, " \n");
      Director * dir = InitDirector(cuv);
      if (search(curr -> directories, dir, fcmp_dir_dir) == NULL)
        printf("Directory %s doesn't exist!\n", cuv);
      else {
        curr -> directories = delete(curr -> directories, dir, fcmp_dir_dir, free_dir2);
      }
      free_dir(dir);
    }
    if (strcmp(cuv, "cd") == 0) {
      cuv = strtok(NULL, " \n");
      if (strcmp(cuv, "..") == 0) {
        curr = curr -> parent;
      } else {
        Director * dir = InitDirector(cuv);
        if (search(curr -> directories, dir, fcmp_dir_dir) == NULL) {
          printf("Directory not found!\n");
        } else {
          curr = ((TArb)(search(curr -> directories, dir, fcmp_dir_dir))) -> info;
        }
        free_dir(dir);
      }
    }
    if (strcmp(cuv, "pwd") == 0) {
      pwd(curr);
      printf("\n");
    }
    if (strcmp(cuv, "find") == 0) {
      cuv = strtok(NULL, " \n");
      if (strcmp(cuv, "-d") == 0) {
        cuv = strtok(NULL, " \n");
        Director * dir = InitDirector(cuv);
        TArb found = NULL;
        find_d(root -> directories, dir, & found);
        if (found == NULL)
          printf("Directory %s not found!\n", cuv);
        else {
          printf("Directory %s found!\n", cuv);
          pwd(DIR(found));
          printf("\n");
        }
        free_dir(dir);
      }
      if (strcmp(cuv, "-f") == 0) {
        cuv = strtok(NULL, " \n");
        Fisier * fis = InitFisier(cuv);
        TArb found = NULL;
        found = search(root -> files, fis, fcmp_fis_fis);
        if (found != NULL) {
          printf("File %s found!\n", cuv);
          pwd(FIS(found) -> parent);
          printf("\n");
        } else {
          found = NULL;
          find_f(root -> directories, fis, & found);
          if (found == NULL)
            printf("File %s not found!\n", cuv);
          else {
            printf("File %s found!\n", cuv);
            pwd(FIS(found) -> parent);
            printf("\n");
          }
        }
        free_fis(fis);
      }
    }
    if (strcmp(cuv, "quit") == 0) {
      DistrArb(root -> files, free_fis);
      distrugeF(root -> directories);
      distrugeD(root -> directories);
      free_dir(root);
      break;
    }
  }
  return 0;
}