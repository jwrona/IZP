/*
 * Soubor:  proj2.c
 * Datum:   2011/11/14
 * Autor:   Jan Wrona, xwrona00@stud.fit.vutbr.cz
 * Projekt: Iteracni vypocty, projekt c. 2 pro predmet IZP
 * Popis: Program aproximuje funce arkus sinus a logaritmus, dale pocita
 * prubeznou delku lomene cary a prubeznou minimalni a maximalni moznou delku
 * lomene cary s chybou.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>

#define LN10 2.3025850929940456840179914546843642076011014886287729760333
#define PI 3.1415926535897932384626433832795028841971693993751058209749
#define PI_PUL 1.5707963267948966192313216916397514420985846996875529104874

/*
 * Vyctovy typ ecodes pro chybove kody.
 */
enum ecodes
{
  NEG_SIGDIG = 0, //zaporna presnost SIGDIG
  NEG_ERR,        //zaporna chyba lomene cary
  WRONG_PARAM,    //spatne zadane parametry
  WRONG_ERR,      //spatne zadana chyba u lomene cary
  WRONG_SIGDIG,   //spatne zadany presnost SIGDIG
  WRONG_BASE,     //spatne zadany zaklad logaritmu
  LOT_PARAM,      //prilis mnoho parametru prikaz. radky
};

/*
 * Konstantni pole retezcu obsahujici chybove hlaseni.
 */
const char *ECODEMSG[] =
{
  "Chybne zadana presnost SIGDIG (nemuze byt zaporna)!",
  "Chybne zadana chyba (nemuze byt zaporna)!",
  "Chybne zadane paramatry prikazove radky!",
  "Chybne zadana chyba (nepovolene znaky)!",
  "Chybne zadana presnost SIGDIG (nepovolene znaky)!",
  "Chybne zadany zaklad logaritmu!",
  "Prilis mnoho parametru prikazove radky!",
};

const char ERANGEMSG[] = 
{ // textovy retezec pro chybu ERANGE z errno
  "Nastalo preteceni nebo podteceni (prilis velke nebo male vstupni cislo)!"
};

/*
 * Konstatni pole charu obsahujici napovedu.
 */
const char HELP[] =
{
  "Program Iteracni vypocty.\n"
  "Autor: Jan Wrona.\n"
  "Program provadi aproximaci matematickych funkci arkus sinus a logaritmus,\n"
  "dale pocita delku lomene cary a delku lomene cary s chybou.\n\n"
  "Pouziti:\n"
  "\tproj2 -h\t\t-> vypise tuto napovedu\n"
  "\tproj2 --arcsin sigdig\t-> vypocet funce arcusi sinus se zadanou\n"
  "                                   presnosti digdig\n"
  "\tproj2 --logax sigdig a\t-> vypocet logaritmu o zakladu a se\n"
  "                                   zadanou presnosti sigdig\n"
  "\tproj2 --lbl\t\t-> vypocet prubezne delky lomene cary\n"
  "\tproj2 --lble ERR\t-> vypocet prubezne minimalni a maximalni delky\n"
  "                                   lomene cary se zadanou chybou ERR\n"
  "\tproj2\t\t\t-> spusteni bez parametru, vypise tuto napovedu"
};

/**
 * Funkce vypisujici chybovou hlasku odpovidajici 
 * chybovemu kodu z vyctovehu typu ecodes nebo hodnote errno.
 * Parametrem code se predava funkci chybovy kod.
 */
void error (int code)
{
  if (code >= NEG_SIGDIG && code <= LOT_PARAM)
  { // kontrola zda je chybovy kod spravny
    fprintf(stderr, "%s\n", ECODEMSG[code]);
  }

  else if (errno == ERANGE)
  { // pouze pri chybe ERANGE
    fprintf(stderr, "%s\n", ERANGEMSG);
  }
}

typedef struct tcoordinates
{ // datova struktura obsahujici souradnice pro pouziti u lomene cary
  double x1, x2;
  double y1, y2;
} Tcoordinates;

/**
 * Funcke lble pro vypocet delky lomene cary s chybou.
 * Souradnice se ji predavaji hodnotou, tak jako chyba err, vysledne hodnoty
 * funce uklada do promennych ktere ji jsou predany odkazem.
 */
void lble(Tcoordinates coordin, double err, double *result_min, 
          double *result_max)
{
  double xa, xb, xc, xd; //pomocne promenne pro intervalovou aritmetiku pro
                         //souradnici x
  double ya, yb, yc, yd; //pomocne promenne pro intervalovou aritmetiku pro
                         //souradnici y
  double xmax, xmin, ymax, ymin; //promenne pro ulozeni vysledku intervalove
                                 //aritmetiky

  //prevedeni souradnic tak, aby prvni bod vzdy lezel v nule, souradnice
  //druheho bodu jsou prepocitany tak, aby vzdalenost mezi nimi byla stejna
  coordin.x2 = fabs(coordin.x1 - coordin.x2);
  coordin.y2 = fabs(coordin.y1 - coordin.y2);
  coordin.x1 = 0;
  coordin.y1 = 0;

  //aplikace chyby na souradnice x
  xa = coordin.x1 - err;
  xb = coordin.x1 + err;
  xc = coordin.x2 - err;
  xd = coordin.x2 + err;

  //aplikace chyby na souradnice y
  ya = coordin.y1 - err;
  yb = coordin.y1 + err;
  yc = coordin.y2 - err;
  yd = coordin.y2 + err;

  //vypocet nejmensich a nejvetsich rozdilu mezi intervaly pomoci intervalove
  //aritmetiky
  xmax = (xd - xa);
  xmin = (xc - xb);  
  ymax = (yd - ya);
  ymin = (yc - yb);

  //osetreni stavu, kdy se intervaly prekryvaji podle obou os
  if (xmin <= 0 && ymin <= 0)
    *result_min += 0;
  
  //osetreni stavu, kdy se intervaly prekryvaji podle osy y
  if (xmin <= 0 && ymin >= 0)
    *result_min += ymin;

  //osetreni stavu, kdy se intervaly prekryvaji podle osy x
  if (ymin <= 0 && xmin >= 0)
    *result_min += xmin;

  //vypocet nejmensi mozne delky
  if (xmin > 0 && ymin > 0)
    *result_min += sqrt(xmin * xmin + ymin * ymin);

  *result_max += sqrt(xmax * xmax + ymax * ymax);//vypocet nejvetsi mozne delky
}

/**
 * Funkce lbl pro vypocet delky lomene cary.
 * Souradnice jsou ji predavany odkazem na strukturu a funkce vraci vysledek.
 */
double lbl(Tcoordinates *p_coordin)
{
  //vypocet delky lomene cary pomoci Pythagorovy vety
  return sqrt((p_coordin->x1 - p_coordin->x2) * (p_coordin->x1 - p_coordin->x2)
           +(p_coordin->y1 - p_coordin->y2) * (p_coordin->y1 - p_coordin->y2));
}

/**
 * Funkce myArctan pro vypocet arcus tangens.
 * Parametr je ji predavan hodnotou, stejne jako pozadovana presnost sigdig.
 * Vysledek funkce vraci.
 */
double myArctan(double z, double sigdig)
{
  int priznak = 0; //promenna pro signalizaci, ze je parametr vetsi nez 1
  int neg = 1; //promenna pro signalizaci, ze je parametr zaporny
  int n = 0, n2 = 0; //pomocna pormenna v iteracnich cyklech a n2 je pozita pro
                     //urychleni vypoctu
  if (z < 0)
  { //test na znamenko parametru a jeho uprava
    z = fabs(z);
    neg = -1;
  }

  if (z > 1)
  { //test na velikost parametru a jeho uprava
    z = 1 / z;
    priznak = 1;
  }

  double t = z; //promenna pro ulozeni hodnory aktualniho kroku
  double result = z; //promenna pro celkovy vysledek
  double z2 = z * z; //promenna pro urychleni vypoctu

  /*
   * Hlavni iteracni cyklus pocitajici rekurentne podle taylorovy rady.
   */
  for (n = 1; (fabs(t) > fabs(result) * sigdig); n++)
  {
    n2 = 2 * n;
    t *= (-((z2 * (n2 - 1)) / (n2 + 1)));
    result += t;
  }

  //pokud byl parametr vetsi nez 1, je potreba vysledek upravit
  if (priznak == 1)
    return neg * (PI_PUL - result);

  //pokud byl parametr zaporny, je potreba vysledek negovat
  return (neg * result);
}

/**
 * Funkce myArcsin pro vypocet arkus sinus.
 * Parametr z predavan hodnotou, stejne jako pozadovana presnost sigdig.
 * Vysledek funkce vraci. 
 */
double myArcsin(double z, double sigdig)
{
  //kontrola zda argument lezi v definicnim oboru
  if ((z > 1) || (z < -1))
    return NAN;

  //osetreni hranicnich stavu, pro ktere algoritmus nefunguje
  if (z == 1 && z == -1)
    return PI_PUL;

  //volani myArctan s upravenym parametrem a presnosti
  return myArctan((z / (sqrt(1 - z * z))), sigdig);
}

/**
 * Funkce prepocet_sigdig pro prepocet parametru zadaneho
 * jako presnost na pocet desetinnych mist.
 * Sigdig je predavano hodnotou a funkce vraci vyslednou prepocitanou presnost.
 */
double prepocet_sigdig(double sigdig)
{
  double precision = 0.01;

  if (sigdig < 0)
  { //kontrola znamenka presnosti
    error(NEG_SIGDIG);
    exit(1);
  }

  while (sigdig > 0)
  { //samotny prepocet
    precision /= 10;
    sigdig--;
  }
  return precision;
}

/**
 * Funkce myLn pro vypocet prirozeneho logaritmu
 * Parametr x i presnost sigdig jsou predavany hodnotou, vysledek funkce vraci.
 */
double myLn(double x, double sigdig)
{
  double t = 0; //promenna pro ulozeni jednotlivych kroku
  double result = 0; //promenna pro ulozeni vysledku
  int n = 0; //pomocna promenna v iteracnich cyklech
  int exponent = 0; //promenna kvuli rozdeleni parametru na mantisu a exponent

  if (x < 0.0) //kontrola znamenka parametru x
    return NAN;

  if (x >= 0.0 && x <= 0.0) //test na nulovy parametr x
    return -INFINITY;

  for (; x > 10; exponent++) //prepocet na mantisu a exponent
    x /= 10;
  for (; x < 1; exponent--)
    x *= 10;

  /*
   * Hlavni iteracni cyklus pro vypocet prirozeneho logaritmu pro parametry
   * v intervalu 0 az 2, vypocet funguje na zaklade rekurentniho vztahu
   * vychazejici z Taylorovy rady pro prirozeny logaritmus.
   */
  if (x < 2)
  {
    t = (x - 1);
    result = (x - 1);
    for (n = 2; fabs(t) > (fabs(result) * sigdig); n++)
    {
      t *= (((1 - n) * (x - 1)) / n);
      result += t;
    }
    return (result + exponent * LN10);
  }

  /*
   * Hlavni iteracni cyklus pro vypocet prirozeneho logaritmu pro parametry
   * vetsi nez 2, vypocet funguje na zaklade rekurentniho vztahu vychazejici
   * z upravene taylorovy rady pro prirozeny logaritmus.
   */
  x = (x / (x-1)); //pokud je parametr vetsi nez 2, je ho potreba upravit
  t = (1 / x);
  result = (1 / x);
  for (n = 2; fabs(t) > (fabs(result) * sigdig); n++)
  {
    t *= ((n - 1) / (n * x));
    result += t;
  }
  return (result + exponent * LN10);
}

/**
 * Funkce myLog pro vypocet logaritmu s presnosti zadanou jako sigdig.
 * Numerus, zaklad i presnost jsou predavany hodnotou a vysledek logaritmu
 * funkce vraci.
 */
double myLog(double numerus, double base, double sigdig)
{
  if(isinf(numerus))
    return INFINITY;
  //vycisleni libovolneho logaritmu podilem dvou prirozenych logaritmu, 
  //jeden pocitajici s parametrem numerus a druhy s parametrem zaklad
  return (myLn(numerus, sigdig) / myLn(base, sigdig));
}

/**
 * Hlavni funkce main,
 * zajistuje nacitani parametru z prikazove radky, nacitani
 * hodnot ze standardniho vstupu a nasledne volani odpovidajicich
 * funcki. Parametr argc je pocet argumentu prikaz.radky a *argv[] je pole
 * retezcu tyto argumenty obsahujici.
 */
int main(int argc, char *argv[])
{
  Tcoordinates coordin = {0, 0, 0, 0}; //definice struktury pro souradnice
  double numerus = 0, base = 0; //promenne pro numerus a zaklad logaritmu
  double sigdig = 0, lbl_err = 0; // promenne pro presnost a chybu
  double res_lbl = 0, res_lbl_max = 0, res_lbl_min = 0; //presna, maximalni a
  //minimalni prubezna delka lomene cary
  int znak = 0, count = 0; //pomocne promenne
  char *strtod_err = NULL; //ukazatel na char, vyznam ma pri pouziti fce strtod

  if (argc == 1)
  { // pokud pocet parametru = 1 (spusteni bez parametru)
    puts(HELP); //vypis napovedy
    return 0;
  }

  /*
   * Blok spusteny pri dvou parametrech na prikazove radce, obstarava tedy
   * lomenou caru a vypis napovedy pri argumentu -h
   */
  if (argc == 2)
  { // pokud pocet parametru = 2
    if (strcmp("--lbl", argv[1]) == 0) 
    { // spusteni pri parametru --lbl
      scanf(" "); //vynechani bilych znaku
      while (1)
      {//nekonecny cyklus pro nacitani vstupni posloupnosti a volani funkce lbl
        if ((znak = getchar()) == EOF ) //test na konec souboru
          return 0;
        ungetc(znak, stdin); // pokud nenarazi na EOF, vrati znak do stdin

        if (scanf("%lf %lf ", &coordin.x2, &coordin.y2) == 2)
        { //cteni vstupu s kontrolou poctu prectenych hodnot
          if (errno > 0)
          { //kontrola chyb
            error(errno);
            return 1;
          }
          if (count == 0)
          { //pri nacteni prnich souradnic musi program vypsat nulu
            printf("%.10e\n", 0.0);
            count = 1; //aby uz podminka priste neplatila
          }
          else
          { // pri nacteni jinych nez prvnich souradnic
            res_lbl += lbl(&coordin); //volani funkce pro vypocet delky a jeji
            //pricteni k prubeznemu vysledku
            printf("%.10e\n", res_lbl); //tisk prubezneho vysledku
          }
          // vymena souradnic
          coordin.x1 = coordin.x2;
          coordin.y1 = coordin.y2;
        }
        else
        { // osetreni spatne zadanych souradnic
          printf("%.10e\n", NAN);
          scanf("%*s ");
        }
      }
    }
    else if (strcmp("-h", argv[1]) == 0)
    { // spusteni pri parametru -h
      puts(HELP); //vypis napovedy
      return 0;
    }
    else
    {
      error(WRONG_PARAM);
      return 1;
    }
  }

  /*
   * Blok spusteny pri trech parametrech na prikazove radce, obstarava tedy
   * funkce pro vypocet lomene cary s chybou a arkus sinus.
   */
  if (argc == 3)
  { // pokud pocet parametru = 3
    if (strcmp("--lble", argv[1]) == 0)
    { // spusteni pri parametru --lble
      if ((lbl_err = strtod(argv[2], &strtod_err)) < 0)
      { //prevod retezce z argumentu na double, a test na znamenko
        error(NEG_ERR); //vypis chyby pri zaporne chybe
        return 1;
      }
      if ((strtod_err == argv[2]) || (*strtod_err != 0))
      { //test spatne zadane chyby
        error(WRONG_ERR);
        return 1;
      }
      if (errno > 0)
      { //test chybove promenne errno z duvodu mozneho preteceni
        error(errno);
        return 1;
      }

      scanf(" "); //vymazani bilych znaku
      while (1)
      { //nekonecny cyklus pro nacitani vstupnich hodnot a volani funkce lble
        if ((znak = getchar()) == EOF ) //test na konec souboru
          return 0;
        ungetc(znak, stdin); // pokud nenarazi na EOF, vrati znak do stdin

        if (scanf("%lf %lf ", &coordin.x2, &coordin.y2) == 2)
        { //nacteni hodnot ze vstupu a test na pocet uspesne nactenych hodnot
          if (errno > 0)
          { //test promenne errno z duvodu mozneho preteceni
            error(errno);
            return 1;
          }
          if (count == 0)
          { //pri nacteni prvnich souradnic program musi vypsat nuly
            printf("%.10e\n%.10e\n", 0.0, 0.0);
            count = 1; //aby se priste podminka neplatila
          }
          else
          { //pri nacteni jinych nez prvnich souradnic
            lble(coordin, lbl_err, &res_lbl_min, &res_lbl_max); //volani funkce
            //ktera vypocita maximalni a minimalni lomenou caru
            printf("%.10e\n%.10e\n", res_lbl_min, res_lbl_max);//vypis vysledku
          }
          // zamena souradnic
          coordin.x1 = coordin.x2;
          coordin.y1 = coordin.y2;
        }
        else
        { //osetreni chybneho vstupu
          printf("%.10e\n", NAN);
          scanf("%*s ");
        }
      }
    }

    else if (strcmp("--arcsin", argv[1]) == 0 )
    { // spusteni pri parametru --arcsin
      sigdig = strtod(argv[2], &strtod_err); //prevedeni retezce na double
      if ((strtod_err == argv[2]) || (*strtod_err != 0))
      { //test na spravne zadanou presnost
        error(WRONG_SIGDIG);
        return 1;
      }
      if (errno > 0)
      { //test promenne errno z duvodu mozneho preteceni
        error(errno);
        return 1;
      }

      sigdig = prepocet_sigdig(sigdig);//prepocet presnosti do pozadovane formy
      scanf(" "); //odstraneni bilych znaku ze vstupu

      while (1)
      { //nekonecny cyklus zajistujici nacitani hodnot a volani funkce myArcsin
        if ((znak = getchar()) == EOF ) //test na konec souboru
          return 0;
        ungetc(znak, stdin); // pokud nenarazi na EOF, vrati znak do stdin

        if (scanf("%lf ", &numerus) == 1)
        { //nacteni hodnoty a kontrola zda se v poradku nacetla
          if (errno > 0)
          { //test promenne errno z duvodu mozneho preteceni
          error(errno);
          return 1;
          }
          printf("%.10e\n", myArcsin(numerus, sigdig)); //volani funkce pro
          //vypocet arkus sinus a vypis vysledku
        }
        else
        { //spusti se pri nespravnem znaku na vstupu
          printf("%.10e\n", NAN);
          scanf("%*s "); //odstraneni spatnych znaku ze vstupniho bufferu
        }
      }
    }

    else
    { //kontrola spravne zadanych parametru prikazove radky
      error(WRONG_PARAM);
      return 1;
    }
  }

  /*
   * Blok spusteny pri ctyrech parametrech na prikazove radce, obstarava tedy
   * logaritmus.
   */
  if (argc == 4)
  { // pokud pocet parametru = 4
    if (strcmp("--logax", argv[1]) == 0 )
    { // spusteni pri parametru --logax
      sigdig = strtod(argv[2], &strtod_err); //prevod retezce na double
      if (errno > 0)
      { //test promenne errno z duvodu mozneho preteceni
        error(errno);
        return 1;
      }
      if ((strtod_err == argv[2]) || (*strtod_err != 0))
      { //kontrola spravne zadaneho vstupu
        error(WRONG_SIGDIG);
        return 1;
      }

      base = strtod(argv[3], &strtod_err); //prevod retezce na double
      if (errno > 0)
      { //test promenne errno z duvodu mozneho preteceni
        error(errno);
        return 1;
      }
      if ((strtod_err == argv[3]) || (*strtod_err != 0))
      { //kontrola spravne zadaneho vstupu
        error(WRONG_BASE);
        return 1;
      }

      sigdig =prepocet_sigdig(sigdig);//prepocet presnosti na pozadovany format
      scanf(" "); //odstraneni bilych znaku ze vstupu

      while (1)
      { //nekonecny cyklus ktery nacita hodnoty ze vstupu a vola funkci myLog
        if ((znak = getchar()) == EOF ) //kontrola dosazeni konce souboru
          return 0;
        ungetc(znak, stdin); // pokud nenarazi na EOF, vrati znak do stdin

        if (scanf("%lf ", &numerus) == 1)
        { //nacteni hodnoty ze vstupu a kontrola spravneho nacteni
          if (errno > 0)
          { //test promenne errno z duvodu mozneho preteceni
            error(errno);
            return 1;
          }
          printf("%.10e\n", myLog(numerus, base, sigdig)); //volani funkce
          //myLog pro vypocet logaritmu a vypis vysledku
        }
        else
        { //spusteni pri nepovolenem znaku na vstupu
          printf("%.10e\n", NAN);
          scanf("%*s "); //odstraneni nepovolenych znaku ze vstupniho bufferu
        }
      }
    }
    else
    { //spusteni pri spatne zadanych parametrech prikazove radky
      error(WRONG_PARAM);
      return 1;
    }
  }

  if (argc > 4) //pokud je prilis velky pocet parametru
  { //test na prilis velky pocet parametru prikazove radky
    error(LOT_PARAM);
    return 1;
  }

  return 0;
}
