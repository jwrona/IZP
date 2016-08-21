/*
 * Soubor:  proj3.c
 * Datum:   2011/12/4
 * Autor:   Jan Wrona, xwrona00@stud.fit.vutbr.cz
 * Projekt: Maticove operace, projekt c. 3 pro predmet IZP
 * Popis:   Program nacita ze vstupniho souboru matice libovlneho rozmeru
 * a provadi s nimi operace scitani, nasobeni, transpozice nebo maticovy
 * vyraz. Dale provadi prostorove operace a to konkretne oznaceni
 * vodniho toku a cestu koule po kulecniku.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_NAME_LEN 100
#define MY_ERRNO 1000

//datovy typ pro ulozeni matice a poctu jejich radku a sloupcu
typedef struct TMatrix {
  int rc;
  int cc;
  int **matrix;
} tmatrix;

//datovy typ pro ulozeni parametru prikazove radky
typedef struct Tparams {
  char file1[MAX_NAME_LEN];
  char file2[MAX_NAME_LEN];
  int row;
  int column;
  int dir;
  int pow;
} tparams;

//vyctovy typ pro smery kulecniku
typedef enum {
  VY = 0,
  ZA,
  SV,
  SZ,
  JV,
  JZ,
} DIRECTIONS;

//vyctovy typ pro urceni jednotlivych funkci programu
typedef enum {
  NOPARAMS = 0,
  HELP,
  TEST,
  ADD,
  MULT,
  TRANS,
  EXPR,
  WATER,
  CAROM
} ARGCODES;

//vyctovy typ pro chybove kody
typedef enum {
  UNK_PARAM = MY_ERRNO,
  LONG_NAME,
  BAD_CLOSE,
  BAD_COORDINATES,
  WRONG_MATRIX,
  WRONG_MATRIX2,
  ERR_ADD,
  ERR_MULT,
  ERR_CAR,
} ECODES;

//zneni chybovych hlaseni
const char *ECODEMSG[] = {
  "Spatne zadane parametry!",
  "Prilis dlouhy nazev souboru!",
  "Soubor se neporadilo uzavrit!",
  "Souradnice lezi mimo matici!",
  "Spatny format vstupni matice!",
  "Vstupni matice obsahuje nepovolene znaky!",
};

//text napovedy
const char HELPMSG[] = {
  "Program Maticove operace.\n"
    "Autor: Jan Wrona.\n"
    "Popis: Program nacita ze vstupniho souboru matice libovolneho rozmeru\n"
    "a provadi s nimi operace scitani, nasobeni, transpozice nebo maticovy\n"
    "vyraz. Dale provadi prostorove operace a to konkretne oznaceni\n"
    "vodniho toku a cestu koule po kulecniku.\n"
    "Pouziti:\n"
    "\tproj3 -h -> vypise tuto napovedu\n"
    "\tproj3 --test -> kontrola vstupni matice\n"
    "\tproj3 --add A.txt B.txt -> vypocet souctu dvou matic\n"
    "\tproj3 --mult A.txt B.txt -> vypocet soucinu dvou matic\n"
    "\tproj3 --trans A.txt -> provede transpozici vstupni matice\n"
    "\tproj3 --expr A.txt B.txt -> vypocte maticovy vyraz (A*B^T+A)\n"
    "\tproj3 --water r s M.txt -> oznaci hladinu vodniho toku v matici\n"
    "\tM pramenici na souradnici [r, s]\n"
    "\tproj3 --carom r s dir power M.txt -> sleduje cestu kulecnikove koule\n"
    "\tpo stole M s pocatecnimi souradnicemi koule [r, s]. Dir znaci pocatecni\n"
    "\tsmer odpalu (V, Z, SV, SZ, JV, JZ) a power je celociselne zadana sila odpalu."
};

//deklarace funkci
int checkErrno(void);
int doParams(int argc, char **argv, tparams * p_params);

FILE *openFile(char *name);
void closeFile(FILE * fr);

tmatrix *loadMatrix(char *filename);
tmatrix *allocStruct(int rc, int cc);
void freeStruct(tmatrix * p_free);
void writeMatrix(tmatrix * p_matrix);

tmatrix *addMatrix(tmatrix * p_matrix1, tmatrix * p_matrix2);
void serviceAddMatrix(tparams * p_params);
tmatrix *multMatrix(tmatrix * p_matrix1, tmatrix * p_matrix2);
void serviceMultMatrix(tparams * p_params);
tmatrix *transMatrix(tmatrix * p_matrix1);
void serviceTransMatrix(tparams * p_params);
void testMatrix(tparams * p_params);
void serviceExprMatrix(tparams * p_params);

void water(tmatrix * p_matrix, tmatrix * p_matrix2, int row, int col);
void coordinates(int row, int col, int *nrow, int *ncol, int dir);
void serviceWater(tparams * p_params);
void carom(int row, int col, int dir, int pow, tmatrix * p_matrix);
void serviceCarom(tparams * p_params);

/*
 * Hlavni funkce main s parametry argc urcujici pocet parametru prikazove radky
 * a **argv coz jsou textove retezce se znenim techto parametru.
 */
int main(int argc, char **argv)
{
  tparams params;               //pro ulozeni parametru prikazove radky

  switch (doParams(argc, argv, &params))
  {                             //switch zpracovavajici navratovou hodnotu funkce doParams
  case NOPARAMS:
    printf("Pro napovedu spustte s parametrem -h.\n");
    break;
  case HELP:
    puts(HELPMSG);
    break;
  case TEST:
    testMatrix(&params);
    break;
  case TRANS:
    serviceTransMatrix(&params);
    break;
  case MULT:
    serviceMultMatrix(&params);
    break;
  case ADD:
    serviceAddMatrix(&params);
    break;
  case EXPR:
    serviceExprMatrix(&params);
    break;
  case WATER:
    serviceWater(&params);
    break;
  case CAROM:
    serviceCarom(&params);
    break;
  default:
    break;
  }

  if (checkErrno() != 0)        //kontrola chybove promenne errno
    return EXIT_FAILURE;

  return EXIT_SUCCESS;
}

/*
 * Funkce pro volajici potrebne funkce pro spravny prubeh funkce kulecniku
 */
void serviceCarom(tparams * p_params)
{
  tmatrix *matice1 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni matice ze vstupu
    return;

  if (p_params->row >= matice1->rc || p_params->row < 0 ||
      p_params->column >= matice1->cc || p_params->column < 0)
  {                             //kontrola zda pocatecni souradnice koule lezi v matici
    freeStruct(matice1);
    errno = BAD_COORDINATES;
    return;
  }

  if (matice1->rc == 1 && (p_params->dir > ZA))
  {                             //osetreni pripadu kdy matice je pouze 1 radek vysoka
    freeStruct(matice1);
    errno = ERR_CAR;
    return;
  }
  if (matice1->cc == 1 && (p_params->dir <= ZA))
  {                             //osetreni pripadu kdy matice je pouze 1 sloupec siroka
    freeStruct(matice1);
    errno = ERR_CAR;
    return;
  }

  //samotna funkce kulecniku
  carom(p_params->row, p_params->column, p_params->dir, p_params->pow, matice1);

  freeStruct(matice1);          //uvolneni pameti
  return;
}

/*
 * Funkce pro vypis drahy kulecnikove koule, predava se ji pocatecni souradnice
 * koule, smer odpalu, sila odpalu a take samotna matice.
 */
void carom(int row, int col, int dir, int pow, tmatrix * p_matrix)
{
  int nrow = 0, ncol = 0;

  while (pow > 0)
  {                             //hlavni cyklus
    coordinates(row, col, &nrow, &ncol, dir);   //zjisteni novych souradnic koule
    if ((nrow < p_matrix->rc && nrow >= 0) &&
        (ncol < p_matrix->cc && ncol >= 0))
    {                           //kontrola zda nove souradnice lezi v mezich matice
      printf("%d ", p_matrix->matrix[row][col]);
      pow--;
      row = nrow;
      col = ncol;
    }
    else
      switch (dir)
      {                         //switch zajistujici zmenu smeru pri "narazu do steny"
      case VY:
        dir = ZA;
        break;
      case ZA:
        dir = VY;
        break;
      case SV:
        if (nrow < 0 && ncol == p_matrix->cc)
          dir = JZ;
        else if (nrow < 0)
          dir = JV;
        else if (ncol == p_matrix->cc)
          dir = SZ;
        break;
      case SZ:
        if (nrow < 0 && ncol < 0)
          dir = JV;
        else if (nrow < 0)
          dir = JZ;
        else if (ncol < 0)
          dir = SV;
        break;
      case JV:
        if (nrow == p_matrix->rc && ncol == p_matrix->cc)
          dir = SZ;
        else if (nrow == p_matrix->rc)
          dir = SV;
        else if (ncol == p_matrix->cc)
          dir = JZ;
        break;
      case JZ:
        if (nrow == p_matrix->rc && ncol < 0)
          dir = SV;
        else if (nrow == p_matrix->rc)
          dir = SZ;
        else if (ncol < 0)
          dir = JV;
        break;
      }
  }
  putchar('\n');
}

/*
 * Funkce volajici potrebne funkce pro vodni tok
 */
void serviceWater(tparams * p_params)
{
  tmatrix *matice1 = NULL;
  tmatrix *matice2 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni matice ze vstupu
    return;

  if (p_params->row >= matice1->rc || p_params->row < 0 ||
      p_params->column >= matice1->cc || p_params->column < 0)
  {                             //kontrola zda pocatecni souradnice lezi v mezich matice
    freeStruct(matice1);
    errno = BAD_COORDINATES;
    return;
  }

  if ((matice2 = allocStruct(matice1->rc, matice1->cc)) == NULL)
  {                             //alokace pameti pro vystupni matici
    freeStruct(matice1);
    return;
  }

  for (int row = 0; row < matice2->rc; row++)
  {                             //naplneni vystupni matice jednickami
    for (int column = 0; column < matice2->cc; column++)
      matice2->matrix[row][column] = 1;
  }
  //samotna funkce vodniho toku
  water(matice1, matice2, p_params->row, p_params->column);
  writeMatrix(matice2);         //vypis matice
  freeStruct(matice2);          //uvolneni pameti
  freeStruct(matice1);

  return;
}

/*
 * Funkce vodniho toku v matici, predava se ji pointery na vstupni i vystupni
 * datove typy obsahujici matici a pocateni souradnice vody.
 */
void water(tmatrix * p_matrix, tmatrix * p_matrix2, int row, int col)
{
  int nrow = 0, ncol = 0;
  int lower = p_matrix->matrix[row][col];

  p_matrix2->matrix[row][col] = 0;      //"rozliti vody" do aktualniho prvku

  for (int dir = VY; dir <= JZ; dir++)
  {                             //hlavni cyklus vodniho toku
    for (int dir2 = VY; dir2 <= JZ; dir2++)
    {      //zjisteni nejmensiho prvku v okoli a jeho ulozeni do promenne lower
      coordinates(row, col, &nrow, &ncol, dir2);    //zjisteni novych souradnic
      if ((nrow < p_matrix->rc && nrow >= 0) &&
          (ncol < p_matrix->cc && ncol >= 0))
      {                         //kontrola zda souradnice lezi v matici
        if (lower > p_matrix->matrix[nrow][ncol])
          lower = p_matrix->matrix[nrow][ncol]; //ulozeni nizsiho prvku
      }
    }

    coordinates(row, col, &nrow, &ncol, dir);   //zjisteni novych souradnic
    if ((nrow < p_matrix->rc && nrow >= 0) &&
        (ncol < p_matrix->cc && ncol >= 0) &&
        (p_matrix2->matrix[nrow][ncol] != 0))
    {        //kontrola zda souradnice lezi v matici a zda uz v prvku neni voda
      if (lower == p_matrix->matrix[nrow][ncol])//pri shode s nalezenym minimem
        water(p_matrix, p_matrix2, nrow, ncol); //volej rekurentne funcki water
    }
  }
}

/*
 * Funkce, ktera podle zadanych souradnic a smeru urci nove souradnice
 */
void coordinates(int row, int col, int *nrow, int *ncol, int dir)
{
  switch (dir)
  {
  case VY:                     //vychod
    *nrow = row;
    *ncol = col + 1;
    break;
  case ZA:                     //zapad
    *nrow = row;
    *ncol = col - 1;
    break;
  case SV:                     //severovychod
    *nrow = row - 1;
    if ((row & 1) == 1)
      *ncol = col + 1;
    else
      *ncol = col;
    break;
  case SZ:                     //severozapad
    *nrow = row - 1;
    if ((row & 1) == 0)
      *ncol = col - 1;
    else
      *ncol = col;
    break;
  case JV:                     //jihovychod
    *nrow = row + 1;
    if ((row & 1) == 1)
      *ncol = col + 1;
    else
      *ncol = col;
    break;
  case JZ:                     //jihozapad
    *nrow = row + 1;
    if ((row & 1) == 0)
      *ncol = col - 1;
    else
      *ncol = col;
    break;
  default:
    break;
  }
}

/*
 * Funkce volajici potrebne funkce pro maticovy vyraz
 */
void serviceExprMatrix(tparams * p_params)
{
  tmatrix *matice1 = NULL;
  tmatrix *matice2 = NULL;
  tmatrix *matice3 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni matice 1
    return;

  if ((matice2 = loadMatrix(p_params->file2)) == NULL)  //nacteni matice 2
  {
    freeStruct(matice1);
    return;
  }

  if ((matice3 = transMatrix(matice2)) == NULL) //transpozice matice 2
  {
    freeStruct(matice2);
    freeStruct(matice1);
    return;
  }
  freeStruct(matice2);

  if ((matice2 = multMatrix(matice1, matice3)) == NULL) //soucin matic
  {
    freeStruct(matice1);
    freeStruct(matice3);
    return;
  }
  freeStruct(matice3);

  if ((matice3 = addMatrix(matice1, matice2)) != NULL)  //soucet matic
    writeMatrix(matice3);

  freeStruct(matice2);          //uvolneni pameti
  freeStruct(matice1);
}

/*
 * Funkce volajici potrebne funce pro soucin dvou matic
 */
void serviceMultMatrix(tparams * p_params)
{
  tmatrix *matice1 = NULL;
  tmatrix *matice2 = NULL;
  tmatrix *matice3 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni matice 1
    return;

  if ((matice2 = loadMatrix(p_params->file2)) == NULL)  //nacteni matice 2
  {
    freeStruct(matice1);
    return;
  }

  if ((matice3 = multMatrix(matice1, matice2)) != NULL) //soucin matic
  {
    writeMatrix(matice3);
    freeStruct(matice3);
  }
  freeStruct(matice2);          //uvolneni pameti
  freeStruct(matice1);
}

/*
 * Funkce provadejici soucin dvou matic, ty se ji predavaji odkazem a funkce
 * vraci pointer na nove alokovanou vyslednou matici.
 */
tmatrix *multMatrix(tmatrix * p_matrix1, tmatrix * p_matrix2)
{
  tmatrix *p_matrix3 = NULL;

  if (p_matrix1->cc != p_matrix2->rc)
  {                             //kontrola zda je matice mozne nasobit
    errno = ERR_MULT;
    return NULL;
  }

  if ((p_matrix3 = allocStruct(p_matrix1->rc, p_matrix2->cc)) == NULL)  //alokace
    return NULL;

  p_matrix3->rc = p_matrix1->rc;
  p_matrix3->cc = p_matrix2->cc;

  for (int row = 0; row < p_matrix3->rc; row++)
  {                             //hlavni cyklus pro nasobeni
    for (int column = 0; column < p_matrix3->cc; column++)
    {
      p_matrix3->matrix[row][column] = 0;       //vynulovani vysledne matice

      for (int n = 0; n < p_matrix1->cc; n++)   //samotne nasobeni
        p_matrix3->matrix[row][column] +=
          (p_matrix1->matrix[row][n] * p_matrix2->matrix[n][column]);
    }
  }
  return p_matrix3;
}

/*
 * Funkce volajici potrebne funkce pro transpozici matice
 */
void serviceTransMatrix(tparams * p_params)
{
  tmatrix *matice1 = NULL;
  tmatrix *matice2 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni vstupni matice
    return;

  if ((matice2 = transMatrix(matice1)) != NULL)
  {                             //transpozice
    writeMatrix(matice2);
    freeStruct(matice2);
  }
  freeStruct(matice1);          //uvolneni pameti
}

/*
 * Funkce pro transpozici matice. Vstupni matice je predavana odkazem a funkce
 * vraci pointer na nove alokovanou transponovanou matici.
 */
tmatrix *transMatrix(tmatrix * p_matrix1)
{
  tmatrix *p_matrix2 = NULL;

  if ((p_matrix2 = allocStruct(p_matrix1->cc, p_matrix1->rc)) == NULL)  //alokace
    return NULL;

  for (int row = 0; row < p_matrix2->rc; row++)
  {                             //hlavni cyklus pro transponovani
    for (int column = 0; column < p_matrix2->cc; column++)
      //"prohozeni" radku se sloupcem
      p_matrix2->matrix[row][column] = p_matrix1->matrix[column][row];
  }

  return p_matrix2;
}

/*
 * Funkce volajici potrebne funkce pro soucet dvou matic.
 */
void serviceAddMatrix(tparams * p_params)
{
  tmatrix *matice1 = NULL;
  tmatrix *matice2 = NULL;
  tmatrix *matice3 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni matice 1
    return;

  if ((matice2 = loadMatrix(p_params->file2)) == NULL)  //nacteni matice 2
  {
    freeStruct(matice1);
    return;
  }

  if ((matice3 = addMatrix(matice1, matice2)) != NULL)  //soucet dvou matic
    writeMatrix(matice3);       //vypis vystupni matice

  freeStruct(matice2);          //uvolneni pameti
  freeStruct(matice1);
}

/*
 * Funkce provadejici soucet dvou matic, ty se ji predavaji odkazem. Funkce
 * vraci pointer na vystupni matici, coz je zaroven prvni vstupni matice, 
 * takze funkce funguje destruktivne vuci prvni vstupni matici.
 */
tmatrix *addMatrix(tmatrix * p_matrix1, tmatrix * p_matrix2)
{
  if ((p_matrix1->rc != p_matrix2->rc) || (p_matrix1->cc != p_matrix2->cc))
  {                             //kontrola zda je mozne provadet soucet
    errno = ERR_ADD;
    return NULL;
  }

  for (int row = 0; row < p_matrix1->rc; row++)
  {                             //hlavni cyklus pro scitani
    for (int column = 0; column < p_matrix1->cc; column++)
      (p_matrix1->matrix[row][column] += p_matrix2->matrix[row][column]);
  }
  return p_matrix1;
}

/*
 * Funkce volajici potrebne funce pro test matice.
 */
void testMatrix(tparams * p_params)
{
  tmatrix *matice1 = NULL;

  if ((matice1 = loadMatrix(p_params->file1)) == NULL)  //nacteni vstupni matice
    return;                     //coz je zaroven i jeji kontrola

  writeMatrix(matice1);         //vypis matice
  freeStruct(matice1);          //uvolneni pameti
}

/*
 * Funkce pro otevreni souboru s parametrem jmeno souboru ve stringu a vraci
 * pointer na otevreny soubor.
 * Fopen nastavuje errno na ENOENT kdyz se mu nepovede otevrit soubor.
 */
FILE *openFile(char *name)
{
  FILE *fr = NULL;

  if ((fr = fopen(name, "r")) == NULL)
    return NULL;

  return fr;
}

/*
 * CloseFile je funkce s parametrem pointeru na soubor ktery ma zavrit,
 * pri neuspechu nastavuje errno na BAD_CLOSE.
 */
void closeFile(FILE * fr)
{
  if ((fclose(fr)) == EOF)
    errno = BAD_CLOSE;
  return;
}

/*
 * Funkce pro nacitani a kontrolu spravnosti matice s parametrem nazev souboru.
 * Detekce chyb pomoci errno -> ERANGE, WRONG_MATRIX pri spatnem formatu matice,
 * WRONG_MATRIX2 pri nepovolenem znaku v matici.
 */
tmatrix *loadMatrix(char *filename)
{
  int number_counter = 0, row_counter = 0;
  int rc = 0, cc = 0;
  int znak = 0, ret = 0;
  tmatrix *p_matrix = NULL;
  FILE *file = NULL;

  if ((file = openFile(filename)) == NULL)      //otevreni souboru
    return NULL;

  if ((fscanf(file, "%d", &rc)) != 1)
  {                             //nacteni prvni hodnoty (ocekava se pocet radku)
    closeFile(file);
    errno = WRONG_MATRIX;
    return NULL;
  }
  if (rc <= 0)
  {                             //pocet radku nemuze byt zaporny ani nulovy
    closeFile(file);
    errno = WRONG_MATRIX;
    return NULL;
  }

  if (fscanf(file, "%d", &cc) != 1)
  {                             //nacteni druhe hodnoty (ocekava se pocet sloupcu)
    closeFile(file);
    errno = WRONG_MATRIX;
    return NULL;
  }
  if (cc <= 0)
  {                             //pocet sloupcu nemuze byt zaporny ani nulovy
    closeFile(file);
    errno = WRONG_MATRIX;
    return NULL;
  }

  if (errno == ERANGE)
  {                             //kontrola preceteni
    closeFile(file);
    return NULL;
  }

  while ((znak = (fgetc(file))) == ' ')
    ;                           //odstrani mezer

  if (znak != '\n')
  {                             //kdyz nenarazi na konec radku
    closeFile(file);
    errno = WRONG_MATRIX;
    return NULL;
  }

  if ((p_matrix = allocStruct(rc, cc)) == NULL)
  {                             //alokace pameti pro matici
    closeFile(file);
    return NULL;
  }

  p_matrix->rc = rc;            //naplneni struktury poctem radku
  p_matrix->cc = cc;            //a sloupcu

  for (int row = 0; row < p_matrix->rc; row++, row_counter++)
  {                             //hlavni nacitaci cyklus
    for (int column = 0; column < p_matrix->cc; column++)
    {
      if ((ret = fscanf(file, "%d", &p_matrix->matrix[row][column])) == EOF)
      {                         //cteni hodnoty ze souboru, kontrola na konec souboru EOF
        freeStruct(p_matrix);
        errno = WRONG_MATRIX;
        closeFile(file);
        return NULL;
      }
      if (ret != 1)
      {                         //kontrola navratove hodnoty funkce fscanf
        closeFile(file);
        freeStruct(p_matrix);
        errno = WRONG_MATRIX2;
        return NULL;
      }
      number_counter++;         //inkrementace citace hodnot
      while ((znak = (fgetc(file))) == ' ')
        ;                       //odstraneni mezer

      if (znak == '\n' && (column + 1) != p_matrix->cc)
      {                         //pokud narazi na konec radku kdy jeste nemel byt
        closeFile(file);
        freeStruct(p_matrix);
        errno = WRONG_MATRIX;
        return NULL;
      }
      else
        ungetc(znak, file);     //navraceni nactene hodnoty do bufferu
    }
  }

  if ((rc * cc) != (number_counter) || rc != row_counter ||
      (fscanf(file, "%*d") != EOF))
  {                             //kontrola spravnosti nactene matice
    closeFile(file);
    freeStruct(p_matrix);
    errno = WRONG_MATRIX;
    return NULL;
  }

  closeFile(file);              //uzavreni souboru
  if (errno != 0)               //kontrola errno
    return NULL;

  return p_matrix;
}

/*
 * Funkce pro alokaci pameti pro celou struktutu, predava se ji pocet radku
 * a sloupcu jako velikost pole. Pokud alokace selze, misto adresy alokovane
 * pameti vraci NULL a nastavuje errno na ENOMEM.
 */
tmatrix *allocStruct(int rc, int cc)
{
  tmatrix *p_allocm;

  if ((p_allocm = malloc(sizeof(tmatrix))) == NULL)     //alokace strukury
    return NULL;

  p_allocm->rc = rc;            //ulozeni poctu radku
  p_allocm->cc = cc;            //a sloupcu do struktury

  if ((p_allocm->matrix = malloc(p_allocm->rc * (sizeof(int *)))) == NULL)
    return NULL;                //alokace jednorozmerenho pole pointeru na integer

  for (int n = 0; n < p_allocm->rc; n++)
  {
    if ((p_allocm->matrix[n] = malloc(p_allocm->cc * (sizeof(int)))) == NULL)
      return NULL;              //alokace dvourozmerneho pole integeru
  }

  return p_allocm;
}

/*
 * Funkce pro uvolneni pameti cele sktruktury tmatrix.
 */
void freeStruct(tmatrix * p_free)
{
  for (int n = 0; n < p_free->rc; n++)
    free(p_free->matrix[n]);
  free(p_free->matrix);
  free(p_free);
}

/*
 * Funkce pro vypis matice.
 */
void writeMatrix(tmatrix * p_matrix)
{
  printf("%d %d\n", p_matrix->rc, p_matrix->cc);        //pocet radku a sloupcu
  for (int row = 0; row < p_matrix->rc; row++)
  {                             //hlavni vypisovaci cyklus
    for (int column = 0; column < p_matrix->cc; column++)
      printf("%d ", p_matrix->matrix[row][column]);
    putchar('\n');
  }
}

/*
 * Funkce pro kontrolu chybove promenne errno a pripadny vypis chybovych hlaseni.
 */
int checkErrno(void)
{
  if (errno > 0)
  {
    if (errno < UNK_PARAM)
      perror("Chyba");

    if (errno >= UNK_PARAM && errno < ERR_ADD)
    {
      errno -= MY_ERRNO;
      fprintf(stderr, "%s\n", ECODEMSG[errno]);
    }
    if (errno >= ERR_ADD)
      puts("false");

    return 1;
  }
  return 0;
}

/*
 * Funkce zpracovavajici parametry prikazove radky s navratovou hodnotou
 * urcenou podle zvolene funkce programu.
 */
int doParams(int argc, char **argv, tparams * p_params)
{
  char *strtol_err = NULL;

  switch (argc)
  {                             //switch podle poctu parametru
  case 1:
    return NOPARAMS;
    break;
  case 2:
    if (strcmp(argv[1], "-h") == 0)
      return HELP;
    break;
  case 3:
    if (strcmp(argv[1], "--test") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[2]);
      return TEST;
    }

    if (strcmp(argv[1], "--trans") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[2]);
      return TRANS;
    }
    break;
  case 4:
    if (strcmp(argv[1], "--add") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[2]);

      if (strlen(argv[3]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file2, argv[3]);

      return ADD;
    }

    if (strcmp(argv[1], "--mult") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[2]);

      if (strlen(argv[3]) >= MAX_NAME_LEN)
      {                         //kontrola zadane delky souboru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file2, argv[3]);

      return MULT;
    }

    if (strcmp(argv[1], "--expr") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
      {
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[2]);

      if (strlen(argv[3]) >= MAX_NAME_LEN)
      {
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file2, argv[3]);

      return EXPR;
    }
    break;
  case 5:
    if (strcmp(argv[1], "--water") == 0)
    {
      p_params->row = (int) strtol(argv[2], &strtol_err, 10);
      if (strtol_err == argv[2] || *strtol_err != 0)
      {                         //kontrola chybne zadaneho parametru
        errno = UNK_PARAM;
        return -1;
      }
      p_params->column = (int) strtol(argv[3], &strtol_err, 10);
      if (strtol_err == argv[3] || *strtol_err != 0)
      {                         //kontrola chybne zadaneho parametru
        errno = UNK_PARAM;
        return -1;
      }
      if (strlen(argv[4]) >= MAX_NAME_LEN)
      {
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[4]);

      return WATER;
    }
    break;
  case 7:
    if (strcmp(argv[1], "--carom") == 0)
    {
      p_params->row = (int) strtol(argv[2], &strtol_err, 10);
      if (strtol_err == argv[2] || *strtol_err != 0)
      {                         //kontrola chybne zadaneho parametru
        errno = UNK_PARAM;
        return -1;
      }
      p_params->column = (int) strtol(argv[3], &strtol_err, 10);
      if (strtol_err == argv[3] || *strtol_err != 0)
      {                         //kontrola chybne zadaneho parametru
        errno = UNK_PARAM;
        return -1;
      }
      p_params->dir = -1;       //pro kontrolu spatne zadaneho smeru
      if (strcmp(argv[4], "V") == 0)
        p_params->dir = VY;
      if (strcmp(argv[4], "Z") == 0)
        p_params->dir = ZA;
      if (strcmp(argv[4], "SV") == 0)
        p_params->dir = SV;
      if (strcmp(argv[4], "SZ") == 0)
        p_params->dir = SZ;
      if (strcmp(argv[4], "JV") == 0)
        p_params->dir = JV;
      if (strcmp(argv[4], "JZ") == 0)
        p_params->dir = JZ;
      if (p_params->dir == -1)
      {                         //pri spatne zadanem smeru
        errno = UNK_PARAM;
        return -1;
      }
      p_params->pow = (int) strtol(argv[5], &strtol_err, 10);
      if (strtol_err == argv[5] || *strtol_err != 0)
      {                         //kontrola chybne zadaneho parametru
        errno = UNK_PARAM;
        return -1;
      }
      if (strlen(argv[6]) >= MAX_NAME_LEN)
      {                         //kontrola chybne zadaneho parametru
        errno = LONG_NAME;
        return -1;
      }
      strcpy(p_params->file1, argv[6]);
      return CAROM;
    }
    break;
  default:
    break;
  }

  errno = UNK_PARAM;
  return -1;
}
