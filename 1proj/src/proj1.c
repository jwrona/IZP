/*
 * Soubor:  proj1.c
 * Datum:   2011/10/30
 * Autor:   Jan Wrona, xwrona00@stud.fit.vutbr.cz
 * Projekt: Prevod casovych udaju, projekt c. 1 pro predmet IZP
 * Popis:   Program provádí prevod casovych udaju, konkretne sekund na casove
 * udaje jine, konkretne minuty, hodiny, dny a tydny. Prevod je mozne ovlivnit 
 * pomoci prepinacu zadanych na prikazove radce. Defaultni prevod je na tydny, 
 * informace o prepinacich je mozne se dozvedet z napovedy, ktera se spousti 
 * pomoci parametru --help.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define SEK_MIN 60  // pocet sekud v minute
#define MIN_HOD 60  // pocet minut v hodine
#define HOD_DEN 24  // pocet hodin ve dni
#define DEN_TYD 7   // pocet dni v tydnu

/*
 * Vyctovy typ ecodes pro chybove kody.
 */
enum ecodes
{
  LOT_PARAM = 0, //prilis mnoho parametru prikazove radky
  UNK_PARAM,     //neznamy parametr na prikazove radce
  TOO_LARGE,     //prilis velke cislo na vstupu
  WRONG_INPUT,   //nepovoleny znak na vstupu

};

/*
 * Konstantni pole retezcu obsahujici chybove hlaseni.
 */
const char *ECODEMSG[] =
{
  "Prilis mnoho parametru!\n",
  "Neznamy parametr!\n",
  "Prilis velke cislo na vstupu!\n",
  "Nepovoleny znak na vstupu!\n",
};

/*
 * Konstatni pole charu obsahujici napovedu.
 */
const char HELP[] =
{
  "Program Prevod casovych udaju.\n"
  "Autor: Jan Wrona.\n"
  "Program provadi prevod sekund na ostatni casove udaje (minuty, hodiny,\n"
  "dny a tydny).\n\n"
  "Pouziti: proj1 --help -> vypise tuto napovedu\n"
  "         proj1 -t     -> prevod na sekundy, minuty, hodiny, dny a tydny\n"
  "         proj1 -d     -> prevod na sekundy, minuty, hodiny a dny\n"
  "         proj1 -h     -> prevod na sekundy, minuty a hodiny\n"
  "         proj1 -m     -> prevod na sekundy a minuty\n"
  "         proj1 -s     -> bez prevodu\n"
  "         proj1        -> stejne jako proj1 -t"
};

/**
 * Funkce vypisujici chybovou hlasku odpovidajici 
 * chybovemu kodu z vyctovehu typu ecodes. Parametrem code se predava funkci
 * chybovy kod.
 */
void error (int code)
{
  if (code >= LOT_PARAM && code <= WRONG_INPUT) {
    fprintf(stderr, "%s\n", ECODEMSG[code]);
    puts(HELP);
  }
}

/**
 * Funkce zajistujici cteni ze standardniho vstupu a zaroven
 * prevod na unsigned long. Vysledek je predavany odkazem pomoci 
 * parametru *p_s. Navratovy typ je int z duvodu moznosti vzniku chyb pri
 * cteni ze vstupu. Pokud se pri cteni objevi nejaka chyba, funkce zavola
 * podprogram pro vypis chyby a vrati hodnotu 1. Pri bezchybnem behu funkce
 * vrati hodnotu 0.
 */
int cteni(unsigned long *p_s)
{
  int i; /* pomocna promenna v cyklech */
  int test = 0; /* promenna pro testovani nuly na vstupu */


/*
 * Hlavni cyklus - nacte znak z bufferu, prevede jej na
 * dekadickou cislici.
 */
  while ((i = getchar()) != EOF && i != '\n') {

    /*
     * Test zda je znak cislice a prevedeni na dekadickou
     * hodnotu. Ulozeni do unsigned long.
     */
    if (i >= '0' && i <= '9') {
      i -= '0';
      test = 1;

      /*
       * Test na preteceni pomoci konstanty ULONG_MAX.
       */
      if (*p_s > ((ULONG_MAX - i) / 10)) {
	error(TOO_LARGE);
	return 1;
      }

      /*
       * Posun dosavadni hodnoty do vyssiho radu a pricteni
       * nove nactene cislice.
       */
      *p_s = ((*p_s) * 10) + i;
    }
    else {
      error(WRONG_INPUT);
      return 1;
    }
  }

  /*
   * Test na nulu na vstupu.
   */
  if (test == 1 && *p_s == 0)
    return 0;

  /*
   * Test na prazdny vstup (EOF nebo \n).
   */
  if ((i == EOF || i == '\n') && (*p_s == 0 && test == 0)) {
   return 1;
  }
  
  return 0;
}

/**
 * Funkce pro prevod sekund na minuty a sekundy. Pocet minut se ziska 
 * celociselnym delenim sekund a konstantou SEK_MIN, zbytek po tomto deleni
 * urcuje pocet sekund a je ziskan operaci modulo.
 * Parametry jsou predavany odkazem. Parametr *p_s znaci sekundy, parametr *p_m
 * znaci minuty.
 */
void prevod_m(unsigned long *p_s, unsigned long *p_m)
{
  *p_m = *p_s / SEK_MIN;
  *p_s %= SEK_MIN;
}

/**
 * Funkce pro prevod minut na hodiny a minuty. Je zavolana funkce pro prevod
 * sekund na minuty. Pocet hodin se ziska celociselnym delenim minut a 
 * konstantou MIN_HOD, zbytek po tomto deleni urcuje pocet minut a je ziskan
 * operaci modulo.
 * Parametry jsou predavany odkazem. Parametr *p_s znaci sekundy, parametr *p_m
 * znaci minuty, parametr *p_h znaci hodiny.
 */
void prevod_h(unsigned long *p_s, unsigned long *p_m, unsigned long *p_h)
{
  prevod_m(p_s, p_m);
  *p_h = *p_m / MIN_HOD;
  *p_m %= MIN_HOD;
}

/**
 * Funkce pro prevod hodin na dny a hodiny. Je zavolana funkce pro prevod
 * minut na hodiny. Pocet dnu se ziska celociselnym delenim hodin a 
 * konstantou HOD_DEN, zbytek po tomto deleni urcuje pocet hodin a je ziskan
 * operaci modulo.
 * Parametry jsou predavany odkazem. Parametr *p_s znaci sekundy, parametr *p_m
 * znaci minuty, parametr *p_h znaci hodiny, parametr *p_d znaci dny.
 */
void prevod_d(unsigned long *p_s, unsigned long *p_m, unsigned long *p_h, 
              unsigned long *p_d)
{
  prevod_h(p_s, p_m, p_h);
  *p_d = *p_h / HOD_DEN;
  *p_h %= HOD_DEN;
}

/**
 * Funkce pro prevod dnu na tydny a dny. Je zavolana funkce pro prevod
 * hodin na dny. Pocet tydnu se ziska celociselnym delenim dnu a 
 * konstantou DEN_TYD, zbytek po tomto deleni urcuje pocet dnu a je ziskan
 * operaci modulo.
 * Parametry jsou predavany odkazem. Parametr *p_s znaci sekundy, parametr *p_m
 * znaci minuty, parametr *p_h znaci hodiny, parametr *p_d znaci dny, 
 * parametr *p_t znaci tydny.
 */
void prevod_t(unsigned long *p_s, unsigned long *p_m, unsigned long *p_h, 
              unsigned long *p_d, unsigned long *p_t)
{
  prevod_d(p_s, p_m, p_h, p_d);
  *p_t = *p_d / DEN_TYD;
  *p_d %= DEN_TYD;
}

/**
 * Funkce zajistujici vypis hodnodnot na standardni vystup stdout. 
 * Zajistuje taktez sklonovani a osetruje vypisovani
 * nulovych hodnot.
 * Jednotlive hodnoty casovych udaju jsou predavany parametry, s znaci sekundy, 
 * m znaci minuty, h znaci hodiny, d znaci dny a t znaci tydny.
 */
void vypis(unsigned long s, unsigned long m, unsigned long h, 
           unsigned long d, unsigned long t)
{

/*
 * Celek zajistujici sklonovani a vypis hodnot pro tydny
 */
  if (t == 1)
    printf("%lu tyden", t);
  if (t == 2 || t == 3 || t == 4)
    printf("%lu tydny", t);
  if (t > 4)
    printf("%lu tydnu", t);

  if (t !=0 && (s != 0 || m != 0 || h != 0 || d != 0))
    putchar(32);

/*
 * Celek zajistujici sklonovani a vypis hodnot pro dny
 */
  if (d == 1)
    printf("%lu den", d);
  if (d == 2 || d == 3 || d == 4)
    printf("%lu dny", d);
  if (d > 4)
    printf("%lu dnu", d);

  if (d != 0 && (s != 0 || m != 0 || h != 0))
    putchar(32);

/*
 * Celek zajistujici sklonovani a vypis hodnot pro hodiny
 */
  if (h == 1)
    printf("%lu hodina", h);
  if (h == 2 || h == 3 || h == 4)
    printf("%lu hodiny", h);
  if (h > 4)
    printf("%lu hodin", h);

  if (h != 0 && (s != 0 || m != 0))
    putchar(32);

/*
 * Celek zajistujici sklonovani a vypis hodnot pro minuty
 */  
  if (m == 1)
    printf("%lu minuta", m);
  if (m == 2 || m == 3 || m == 4)
    printf("%lu minuty", m);
  if (m > 4)
    printf("%lu minut", m);

  if (m != 0 && s != 0)
    putchar(32);

/*
 * Celek zajistujici sklonovani a vypis hodnot pro sekundy
 */
  if (s == 1)
    printf("%lu sekunda", s);
  if (s == 2 || s == 3 || s == 4)
    printf("%lu sekundy", s);
  if (s > 4)
    printf("%lu sekund", s);
}

/**
 * Zacatek
 * hlavni
 * funkce.
 * Zajistuje urceni prepinace na prikazove radce, osetruje pripadne chyby
 * v zadani prepinace. Dale vola funci pro cteni ze standardniho vstupu, 
 * podle zadaneho prepinace zavola pozadovanou funkci pro prevod a nasledne
 * zavola funkci pro vypis hodnot na standardni vystup.
 * Parametr argc urcuje pocet argumentu na prikazove radce a pole
 * retezcu argv obsahuje tyto jednotlive argumenty.
 */
int main(int argc, char *argv[])
{
  unsigned long s = 0, m = 0, h = 0, d = 0, t = 0;
  // promenne pro ulozeni hodnot jednotlivych casovych udaju
  // vim, ze pouzivani jednoznakovych promennych je brano jako chyba, ale 
  // v tomto programu mi pouziti identifikatoru s pro sekundy atd. prijde jako
  // dostatecne vystizne

  int para = 0; // nastavi se podle zjisteneho parametru

/*
 * Podminka pro kontrolu vice nez dvou parametru.
 */
  if (argc > 2) {
    error(LOT_PARAM);
    return EXIT_FAILURE;
  }

/*
 * Podminka pro zjisteni parametru
 * pomoci porovnani dvou retezcu.
 * Pri shode nastavi priznak para.
 */
  if (argc == 2) {
    if (strcmp("-s", argv[1]) == 0 ) {
      para = 's';
    }

    if (strcmp("-m", argv[1]) == 0) {
      para = 'm';
    }

    if (strcmp("-h", argv[1]) == 0) {
      para = 'h';
    }

    if (strcmp("-d", argv[1]) == 0) {
      para = 'd';
    }

    if (strcmp("-t", argv[1]) == 0) {
      para = 't';
    }

    if (strcmp("--help", argv[1]) == 0) {
      puts(HELP);
      return EXIT_SUCCESS;
    }
  }

/*
 * Podminka pro kontrolu zadani neznameho parametru.
 */
  if (argc == 2 && para == 0) {
    error(UNK_PARAM);
    return EXIT_FAILURE;
  }
  
/*
 * Podminka pro kontrolu nezadani zadneho parametru.
 */
  if (argc == 1) {
    para = 't';
  }

/*
 * Volani funkce pro cteni znaku a zaroven testovani jeji navratove hodnoty.
 */
  if (cteni(&s) == 1)  //pri jednicce je chyba cteni
    return EXIT_FAILURE;

/*
 * Podminka zajistujici vypis "0 sekund" pri zadani nuly na vstupu.
 */
  if (s == 0) {
    printf("0 sekund\n");
    return EXIT_SUCCESS;
  }

/*
 * Switch zajistujici volani jednotlivych funkci pro prevod, 
 * rozhoduje se podle priznaku para.
 */
  switch (para) {
    case 's' : break; //bez prevodu
    case 'm' : prevod_m(&s, &m); break; //prevod na minuty
    case 'h' : prevod_h(&s, &m, &h); break; //prevod na hodiny
    case 'd' : prevod_d(&s, &m, &h, &d); break; // prevod na dny
    case 't' : prevod_t(&s, &m, &h, &d, &t); break; //prevod na tydny
  }

  vypis(s, m, h, d, t); // volani funkce vypis pro vypis hodnot
  putchar('\n'); // vlozeni znaku zakonceni radku

  return EXIT_SUCCESS;
}
