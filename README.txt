/* IMBREA GIULIA-STEFANIA 311 CB */
[arb.c]
ConstrNod = returneaza adresa nodului creat
ConstrFr = returneaza adresa fruncei create
distruge = distruge toate nodurile
DistrArb = distruge arborele

[dir_file]
distrugeF = distruge toate fisierele din sistem
    -verific daca am ce elimina
    -merg in stanga sau in dreapta, repet procesul prin recursivitate
distrugeD = distruge arborele de directoare
free_dir = elibereaza numele si dir
free_dir2 = distruge un director total(subdrectoare, fisiere, fisierele subdirectoarelor)
InitDirector = initializeaza un director cu numele primit(restul campurilor cu NULL)
InitFisier = initializeaza un fisier cu numele primit
functii-le de timp fcmp_dir_fis sunt folosite pt a folosi strcmp, cu castul potrivit

[tema3.c]
insert = insereaza un director/fisier intr-un arbore de directoare/fisiere
         - se face in ordine lexicografica
         - verific mai intai daca arborele este vid(inserez direct)
         - verific daca elementul curent are acelasi nume
         - daca nu merg fie in dreapta fie in stanga si repet procesul
search = cauta intr-un arbore daca exista un element cu acelasi nume ca cel al elementului *x
         - seamana cu insert doar ca returneaza adresa elementului cu acelasi nume
ls = listeaza continutul unui director
    - apelez recursiv functia pt partea stanga, dreapta, iar functia folosita este cea de print, avand cast-urile necesare
    - min 
min = /returneaza adresa celui mai "mic" nume dpdv lexicografic
    - daca elementul este o frunza, se returneaza adresa lui
    - daca copilul din stanga exista, se reapeleaza functia
    - altfel inseamna ca elementul de la adresa curenta este cel mai "mic"
delete = sterge un director/fiser din arborele dat 
    - verific mai intai daca arborele este vid
    - exista 4 cazuri odata ce am gasit elementul cu acelasi nume precum cel al lui x:
        1. ( 0 copii) el este o frunza, il elimin
        2. daca exista un copil fie in stanga, fie in dreapta, mut acel copil in locul elementului curent
        3. daca are ambii copii, caut cel mai mic copil din dreapta dpdv lexicografic, il inlocuiesc cu elem curent si apelez
        in mod recursiv functia de eliminare pentru ramura din dreapta

pwd = printeaza calea absoluta pt directorul dat, se reapeleaza recursiv pana cand numele elementului curent este root 
find_d = cauta un director in arborele de directoare, adresa este salvata in found prin efect lateral
    - apelez mai intai fct search 
    -daca aceasta a dat NULL, reapelez functia find_d pentru arborele de directoare din director si eventual pentru copilul din stanga si din dreata
find_f = cauta un fisier in arborele de directoare
    - verific mai intai daca exista fisierul in arborele files
    - asemanator cu find_d, daca nu s-a gasit un element, caut in subdirectoare si la ambii copii

main

-initializez directorul curent cu root
touch:
-initializez un fisier, avand ca parinte directorul curent 
-verific daca acesta exista cu search
-daca nu, il inserez 
mkdir
-ca la touch, doar ca initializez un director 
ls
-apelez functia ls pentru arborele de directoare si de fisiere din directorul curent 
rm 
-initializez fisier
-caut cu search fisierul de sters, daca l-am gasit, apelez functia deletw
rmdir
-ca la rm, dar este pentru directoare
cd 
-caut directorul cu search, daca l am gasit, directorul curent(curr) devine directorul mentionat dupa cd 
pwd = apelez functia pwd
find-d / find -f
-apelez functia find_d/find_f, in functie de ce returneaza, apelez functia pwd

