/*
 * Soubor:  proj4.c
 * Datum:   2011/12/18
 * Autor:   Jan Wrona, xwrona00@stud.fit.vutbr.cz
 * Projekt: Ceske razeni, projekt c. 4 pro predmet IZP
 * Popis:   Program nacita radky textu ze vstupniho souboru a serazene je
 *          zapisuje do vystupniho souboru. Razeni probiha podle abecedniho
 *          porovnani retezcu podle normy CSN 97 6030, tedy ceskeho razeni.
 *          Program take podporuje ruzne kodovani vstupnich znaku, ve stejnem
 *          kodovani jako je vstupni soubor je take soubor vystupni.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include <errno.h>

#define MAX_NAME_LEN 100 //makro pro max. jmena vst. souboru
#define MY_ERRNO 1000 //makro pro hodnotu mych chybovych kodu

//struktura pro ulozeni parametru
typedef struct Tparams {
  char encoding[MAX_NAME_LEN];
  char file1[MAX_NAME_LEN];
  char file2[MAX_NAME_LEN];
} tparams;

//struktura prvku seznamu
typedef struct Trow {
  wchar_t *text; //radek textu
  struct Trow *next; //ukazatel na dalsi polozku
} trow;

//zahlavi seznamu
typedef struct Tlist {
  trow *head;
} tlist;

//vyctovy typ pro chybove kody
typedef enum {
  UNK_PARAM = MY_ERRNO,
  LONG_NAME,
  ELOC,
  EOPEN,
  ECLOSE,
} ECODES;

//texty chybovych hlaseni
const char *ECODEMSG[] = {
  "Spatne zadane parametry!",
  "Prilis dlouhy nazev souboru!",
  "Spatne zadana lokalizace!",
  "Soubor se neporadilo otevrit!",
  "Soubor se neporadilo uzavrit!",
};

//text napovedy
const char HELPMSG[] = {
    "Program Ceske razeni.\n"
    "Autor: Jan Wrona.\n"
    "Popis:   Program nacita radky textu ze vstupniho souboru a serazene je\n"
    "zapisuje do vystupniho souboru. Razeni probiha podle abecedniho\n"
    "porovnani retezcu podle normy CSN 97 6030, tedy ceskeho razeni. Program\n"
    "take podporuje ruzne kodovani vstupnich znaku, ve stejnem kodovani jako\n"
    "je vstupni soubor je take soubor vystupni.\n"
    "Pouziti:\n"
    "\tproj4 [--loc LOCALE] soubor1.txt soubor2.txt\n"
    "\tsoubor1.txt -> jméno vstupniho souboru\n"
    "\tsoubor2.txt -> jméno vystupniho souboru\n"
    "\t--loc LOCALE -> nepovinný parametr, který reprezentuje znakovou sadu\n"
    "\tvstupniho souboru\n"
};

//kodovaci tabulka pro prvni pruchod
const int CODETABLE1[] = {
  [L' '] = 1,
  [L'A'] = 2,[L'a'] = 2,[L'\u00c1'] = 2,[L'\u00e1'] = 2,
  [L'B'] = 3,[L'b'] = 3,
  [L'C'] = 4,[L'c'] = 4,
  [L'\u010c'] = 5,[L'\u010d'] = 5,
  [L'D'] = 6,[L'd'] = 6,[L'\u010e'] = 6,[L'\u010f'] = 6,
  [L'E'] = 7,[L'e'] = 7,[L'\u00e9'] = 7,[L'\u00c9'] = 7,[L'\u011a'] =
    7,[L'\u011b'] = 7,
  [L'F'] = 8,[L'f'] = 8,
  [L'G'] = 9,[L'g'] = 9,
  [L'H'] = 10,[L'h'] = 10,
  [L'@'] = 11,[L'#'] = 11,      //Ch a ch
  [L'I'] = 12,[L'i'] = 12,[L'\u00cd'] = 12,[L'\u00ed'] = 12,
  [L'J'] = 13,[L'j'] = 13,
  [L'K'] = 14,[L'k'] = 14,
  [L'L'] = 15,[L'l'] = 15,
  [L'M'] = 16,[L'm'] = 16,
  [L'N'] = 17,[L'n'] = 17,[L'\u0147'] = 17,[L'\u0148'] = 17,
  [L'O'] = 18,[L'o'] = 18,[L'\u00d3'] = 18,[L'\u00f3'] = 18,
  [L'P'] = 19,[L'p'] = 19,
  [L'Q'] = 20,[L'q'] = 20,
  [L'R'] = 21,[L'r'] = 21,
  [L'\u0158'] = 22,[L'\u0159'] = 22,
  [L'S'] = 23,[L's'] = 23,
  [L'\u0160'] = 24,[L'\u0161'] = 24,
  [L'T'] = 25,[L't'] = 25,[L'\u0164'] = 25,[L'\u0165'] = 25,
  [L'U'] = 26,[L'u'] = 26,[L'\u00da'] = 26,[L'\u00fa'] = 26,[L'\u016e'] =
    26,[L'\u016f'] = 26,
  [L'V'] = 27,[L'v'] = 27,
  [L'W'] = 28,[L'w'] = 28,
  [L'X'] = 29,[L'x'] = 29,
  [L'Y'] = 30,[L'y'] = 30,[L'\u00dd'] = 30,[L'\u00fd'] = 30,
  [L'Z'] = 31,[L'z'] = 31,
  [L'\u017d'] = 32,[L'\u017e'] = 32,
};

//kodovaci tabulka pro druhy pruchod
const int CODETABLE2[] = {
  [L' '] = 1,
  [L'A'] = 2,[L'a'] = 2,
  [L'\u00c1'] = 3,[L'\u00e1'] = 3,
  [L'B'] = 4,[L'b'] = 4,
  [L'C'] = 5,[L'c'] = 5,
  [L'\u010c'] = 6,[L'\u010d'] = 6,
  [L'D'] = 7,[L'd'] = 7,
  [L'\u010e'] = 8,[L'\u010f'] = 8,
  [L'E'] = 9,[L'e'] = 9,
  [L'\u00e9'] = 10,[L'\u00c9'] = 10,
  [L'\u011a'] = 11,[L'\u011b'] = 11,
  [L'F'] = 12,[L'f'] = 12,
  [L'G'] = 13,[L'g'] = 13,
  [L'H'] = 14,[L'h'] = 14,
  [L'@'] = 15,[L'#'] = 15,      //Ch a ch
  [L'I'] = 16,[L'i'] = 16,
  [L'\u00cd'] = 17,[L'\u00ed'] = 17,
  [L'J'] = 18,[L'j'] = 18,
  [L'K'] = 19,[L'k'] = 19,
  [L'L'] = 20,[L'l'] = 20,
  [L'M'] = 21,[L'm'] = 21,
  [L'N'] = 22,[L'n'] = 22,
  [L'\u0147'] = 23,[L'\u0148'] = 23,
  [L'O'] = 24,[L'o'] = 24,
  [L'\u00d3'] = 25,[L'\u00f3'] = 25,
  [L'P'] = 26,[L'p'] = 26,
  [L'Q'] = 27,[L'q'] = 27,
  [L'R'] = 28,[L'r'] = 28,
  [L'\u0158'] = 29,[L'\u0159'] = 29,
  [L'S'] = 30,[L's'] = 30,
  [L'\u0160'] = 31,[L'\u0161'] = 31,
  [L'T'] = 32,[L't'] = 32,
  [L'\u0164'] = 33,[L'\u0165'] = 33,
  [L'U'] = 34,[L'u'] = 34,
  [L'\u00da'] = 35,[L'\u00fa'] = 35,
  [L'\u016e'] = 36,[L'\u016f'] = 36,
  [L'V'] = 37,[L'v'] = 37,
  [L'W'] = 38,[L'w'] = 38,
  [L'X'] = 39,[L'x'] = 39,
  [L'Y'] = 40,[L'y'] = 40,
  [L'\u00dd'] = 41,[L'\u00fd'] = 41,
  [L'Z'] = 42,[L'z'] = 42,
  [L'\u017d'] = 43,[L'\u017e'] = 43,
};

//deklarace funkci
int doParams(tparams * p_params, int argc, char **argv);
void myPerror(int ecode);
int readLine(tlist * list, FILE * fr);
int readFile(tlist * list, tparams * p_params);
void freeList(tlist * list);
int writeList(tlist * list, tparams * p_params);
int compareRow(trow * row1, trow * row2, const int *CODETABLE);
void switchRow(tlist * list, trow * row1, trow * row2);
void sortList(tlist * list);
trow *insertFirst(tlist * list, wchar_t * row);

int main(int argc, char **argv)
{
  tparams params;               //pro ulozeni parametru prikazove radky
  tlist list = { NULL };        //zahlavi linearniho seznamu

  switch (doParams(&params, argc, argv))
  { //switch predevsim pro nastaveni lokalicaze podle vstupnich parametru
  case -1:
    return puts(HELPMSG), EXIT_FAILURE;
  case 0:
    puts(HELPMSG);
    return 0;
  case 1: //nebyla zadana lokalizace
    if ((setlocale(LC_ALL, "")) == NULL)
      return myPerror(ELOC), EXIT_FAILURE;
    break;
  case 2: //byla zadana lokalizace
    if ((setlocale(LC_ALL, params.encoding)) == NULL)
      return myPerror(ELOC), EXIT_FAILURE;
    break;
  default:
    break;
  }

  if ((readFile(&list, &params)) != 0)
  { //cteni vstupniho souboru
    freeList(&list);
    return myPerror(errno), EXIT_FAILURE;
  }

  sortList(&list); //samotne razeni

  if ((writeList(&list, &params)) != 0)
  { //vypis serazeneho seznamu do souboru
    freeList(&list);
    return myPerror(errno), EXIT_FAILURE;
  }

  freeList(&list); //uvolneni pameti
  return EXIT_SUCCESS;
}

void sortList(tlist * list)
{ //funkce pro serazeni seznamu
  trow *tmp = list->head;
  int i = 1;

  while (i != 0)
  { //hlavni cyklus
    i = 0;
    while (tmp->next != NULL)
    {                           //dokud nenarazi na konec seznamu
      if (compareRow(tmp, tmp->next, CODETABLE1))
      {                         //porovnej dva retezce
        switchRow(list, tmp, tmp->next);        //pokud nesedi poradi tak je zameni
        i++;                    //inkrementace poctu prehozeni
      }
      else
        tmp = tmp->next;        //pokud poradi retezcu sedi, posun na dalsi polozku seznamu
    }
    tmp = list->head;           //presun na zacatek seznamu
  }
}

int compareRow(trow * row1, trow * row2, const int *CODETABLE)
{                               //funkce pro porovnani dvou retezcu
  //pri shodnosti vraci 0, kdyz je row1 mensi (prijde nahoru) vraci 0, kdyz row2 prijde nahoru vraci 1
  for (int i = 0;; i++)
  {
    int first = CODETABLE[row1->text[i]];
    int second = CODETABLE[row2->text[i]];

    if (row1->text[i] == L'\0' && row2->text[i] == L'\0')
    { //pokud jsou retezce stejne
      if (CODETABLE == CODETABLE1)
        return compareRow(row1, row2, CODETABLE2);
        //rekurentni volani funkce pro porovnani, pouze s jinou kodovaci tabukĺkou
      else
        return 0; //retezce jsou naproste shodne
    }
    if (row1->text[i] == L'\0')
      return 0; //pokud je prvni retezec kratsi
    if (row2->text[i] == L'\0')
      return 1; //pokud je druhy retezec kratsi
    if ((first == 0) && (second == 0)) //testy na nezname znaky
      return 0;
    if (first == 0)
      return 1;
    if (second == 0)
      return 0;
    if (first < second)
      return 0; //prvni retezec ma mensi hodnotu
    if (first > second)
      return 1; //druhy retezec ma mensi hodnotu
  }
}

void switchRow(tlist * list, trow * row1, trow * row2)
{ //funkce pro zamenu dvou za soub lezicich polozek seznamu
  trow *tmp = list->head;

  if (tmp == row1)
  { //pripad ze se jedna o prvni polozku seznamu
    tmp = row2->next;
    row2->next = list->head;
    list->head = row2;
    row1->next = tmp;
  }
  else
  {
    while (tmp->next != row1)
      tmp = tmp->next; //nalezeni predchozi polozky
    tmp->next = row2;
    row1->next = row2->next;
    row2->next = row1;
  }
}

trow *insertFirst(tlist * list, wchar_t * row)
{                               //funkce pro vklad polozky seznamu na jeho pocatek
  trow *tmp = NULL;

  if ((tmp = malloc(sizeof(trow))) == NULL) //alokace
    return NULL;                //detekce chyby

  tmp->next = list->head;
  tmp->text = row;
  list->head = tmp;
  return tmp;
}

int writeList(tlist * list, tparams * p_params)
{                               //vypise text vsech polozek seznamu do souboru
  trow *tmp = list->head;
  FILE *fw = NULL;

  if ((fw = fopen(p_params->file2, "w")) == NULL)
    return 1;                   //detekce chyby otevreni souboru

  while (tmp != NULL)
  { //dokud nenarazi na konec seznamu
    int i = 0;

    while (tmp->text[i] != L'\0')
    { //dokud nenarazi na ukoncovaci nulu
      if (tmp->text[i] == L'@')
      { //dekodovani Ch
        fputwc(L'C', fw);
        fputwc(L'h', fw);
        i++;
        continue;
      }

      if (tmp->text[i] == L'#')
      { //dekodovani ch
        fputwc(L'c', fw);
        fputwc(L'h', fw);
        i++;
        continue;
      }
      fputwc(tmp->text[i++], fw);
    }

    fputwc(L'\n', fw);
    tmp = tmp->next;
  }
  if ((fclose(fw)) == EOF)
    return 1;                   //detekce chyby uzavreni
  return 0;
}

void freeList(tlist * list)
{                               //uvolni vsechnu pamet vsech polozek seznamu
  trow *tmp = NULL;

  while ((tmp = list->head) != NULL)
  {
    if (tmp->text != NULL)
      free(tmp->text);
    list->head = tmp->next;
    free(tmp);
  }
}

int readFile(tlist * list, tparams * p_params)
{                               //otevre soubor a preda jej funcki pro zpracovani radku, kontroluje konec souboru
  wint_t znak = 0;
  FILE *fr = NULL;

  if ((fr = fopen(p_params->file1, "r")) == NULL)
    return 1;                   //detekce chyby a nastaveni errno

  while ((znak = fgetwc(fr)) != WEOF)
  { //dokud nenarazis na konec souboru
    if (errno == EILSEQ)
    { //test na nepovoleny znak
      fclose(fr);
      return 1;
    }

    ungetwc(znak, fr); //navrat znaku do bufferu

    if (readLine(list, fr))
    { //cteni radky
      fclose(fr);
      return 1;
    }
  }

  if (errno == EILSEQ)
  { //test na nepovoleny znak
    fclose(fr);
    return 1;
  }

  if ((fclose(fr)) == EOF)
    return 1;                   //detekce chyby zavreni souboru

  return 0;
}

int readLine(tlist * list, FILE * fr)
{                               //vytvori polozku seznamu, naplni ji textem a zaradi ji do seznamu na prvni misto
  int buffsize = 0, count = 0;
  int chSign = 0, ChSign = 0;
  wint_t znak = 0;
  wchar_t *tmp_text = NULL;
  const int BLOCKSIZE = 16;

  while ((znak = fgetwc(fr)) != L'\n')
  { //dokud nenarazi na konec radku
    if (errno == EILSEQ)
    { 
      if (tmp_text != NULL)
        free(tmp_text);
      return 1;
    }

    if (count == buffsize)
    { //zvetseni velikosti bufferu podle poctu nactenych znaku
      buffsize += BLOCKSIZE;
      wchar_t *tmp = realloc(tmp_text, buffsize * sizeof(wchar_t));

      if (tmp == NULL)
      {
        if (tmp_text != NULL)
          free(tmp_text);
        return 1;               //detekce chyby reallocu a nastaveni errno
      }
      tmp_text = tmp;
    }

    //detekce ch
    if (znak == L'C')
      ChSign = 1; //nastaveni priznaku pro ch
    if (znak == L'c')
      chSign = 1;

    if ((ChSign || chSign) && (znak == L'H' || znak == L'h'))
    {
      if (ChSign)
      {
        tmp_text[--count] = L'@';
        ChSign = 0;
      }
      if (chSign)
      {
        tmp_text[--count] = L'#';
        chSign = 0;
      }
    }
    else
      tmp_text[count] = znak;

    if ((ChSign || chSign) && (znak != L'C' && znak != L'c'))
    { //vynulovani priznaku pro ch
      ChSign = 0;
      chSign = 0;
    }
    count++;
  }

  if (count == buffsize)
  { //pridani pameti pro zakoncovaci nulu
    wchar_t *tmp = realloc(tmp_text, (buffsize + 1) * sizeof(wchar_t));

    if (tmp == NULL)
    {
      if (tmp_text != NULL)
        free(tmp_text);
      return 1;                 //detekce chyby reallocu a nastaveni errno
    }
    tmp_text = tmp;
  }
  tmp_text[count] = L'\0'; //vlozeni zakoncovani nuly

  if ((insertFirst(list, tmp_text)) == NULL)
  { //vlozeni nacteneho radku do polozky seznamu
    if (tmp_text != NULL)
      free(tmp_text);
    return 1;
  }
  return 0;
}

void myPerror(int ecode)
{ //funkce pro vypis chybovych hlaseni
  if (ecode >= UNK_PARAM && ecode <= ECLOSE)
    fprintf(stderr, "%s\n", ECODEMSG[(ecode - MY_ERRNO)]);
  else if (errno != 0)
    perror("Chyba");
}

int doParams(tparams * p_params, int argc, char **argv)
{                               //funkce zpracovavajici parametry
  //pri chybe vraci -1, pri vypisu napovedy vraci 0
  //pri nezadane lokalicazi vraci 1 a pri zadane lokalizaci vraci 2
  switch (argc)
  {
  case 1:
  case 2:
    return 0; //bez parametru nebo s jednim parametrem
  case 3: //bez zadane lokalizace
    if (strlen(argv[1]) >= MAX_NAME_LEN)
      return myPerror(LONG_NAME), -1;
    strcpy(p_params->file1, argv[1]);

    if (strlen(argv[2]) >= MAX_NAME_LEN)
      return myPerror(LONG_NAME), -1;
    strcpy(p_params->file2, argv[2]);
    return 1;

  case 5: //se zadanou lokalizaci
    if (strcmp(argv[1], "--loc") == 0)
    {
      if (strlen(argv[2]) >= MAX_NAME_LEN)
        return myPerror(LONG_NAME), -1;
      strcpy(p_params->encoding, argv[2]);

      if (strlen(argv[3]) >= MAX_NAME_LEN)
        return myPerror(LONG_NAME), -1;
      strcpy(p_params->file1, argv[3]);

      if (strlen(argv[4]) >= MAX_NAME_LEN)
        return myPerror(LONG_NAME), -1;
      strcpy(p_params->file2, argv[4]);
      return 2;
    }
  }
  return myPerror(UNK_PARAM), -1;
}
