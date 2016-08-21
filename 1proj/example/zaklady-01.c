/*
  Projekt: Jak na projekty v jazyce C
  Autor: David Martinek, martinek (zaviná¿) fit.vutbr.cz
  Datum: 11.02.2009
  Kódování dokumentu: ISO8859-2
  Popis: Tento program slou¾í pro demonstraci základních stavebních prvkù
         jazyka C.
*/

// Jak èíst tento zdrojový soubor
// 1. Zaènìte sekcí pro vkládání rozhraní knihoven.
// 2. Podívejte se na funkci main, která se nachází na konci souboru.
// 3. Ve funkci main se v urèitém poøadí volají jednotlivé podprogramy.
//    V tom poøadí, v jakém se volají ve funkci main, si prohlédnìte jejich
//    definice v prostøední èásti zdrojového souboru. Pøed ka¾dou funkcí se
//    nachází komentáø, který vysvìtluje, co se v této funkci dìje.
// 4. Pøelo¾te tento zdrojový soubor pomocí pøekladaèe jazyka C. Na webových
//    stránkách Jak na projekty v jazyce C najdete postup, jak pøekladaè
//    zavolat.
//    Také mù¾ete pou¾ít pøíkaz make. Makefile je pøibalen. Pokud nerozumíte,
//    co to znamená, pøeètìte si o programu make na webových stránkách.


////////// Sekce pro vkládání rozhraní knihoven ///////////////////////////////

// Zde se vkládá rozhraní knihoven, které bude program pou¾ívat. V tomto
// programu se budou pou¾ívat podprogramy z nìkolika èástí systémové knihovny.
// V tomto konkrétním pøípadì bude potøeba rozhraní stdio.h, stdlib.h, math.h,
// limits.h a float.h.
// Informaci o tom, jaké rozhraní je potøeba pou¾ít, se dozvíte v nápovìdì
// k systémovým funkcím (napøíklad v manuálových stránkách).
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

///////// Definice podprogramù ////////////////////////////////////////////////

//== zaèátek == jednoduchý tisk na obrazovku ==
/**
 * Funkce bez parametrù a bez návratové hodnoty (klíèové slovo void).
 * Pomocí systémové funkce printf vytiskne nápis na standardní výstup programu.
 * V¹imnìte si, ¾e odøádkování se provádí vlo¾ením \n do textu.
 * V¹imnìte si, ¾e více textových øetìzcù za sebou, které jsou oddìleny jenom
 * mezerami, tvoøí jeden textový øetìzec.
 */
void hello(void)
{
  printf("Ahoj.\n"
         "Já jsem program pro demonstraci základních konstrukcí jazyka C.\n");
}

/**
 * Funkce bez návratové hodnoty, ale s jedním parametrem. Parametr signature
 * je textový øetìzec (typ char*). Pomocí tohoto parametru mù¾eme mìnit
 * èást textu, který se bude tisknout.
 *
 * V¹imnìte si znaèky %s v ti¹tìném øetìzci. Na místì této znaèky se vytiskne
 * obsah promìnné, která se nachází za øetìzcem. V tomto pøípadì jde
 * o promìnnou signature.
 */
void signedHello(char *signature)
{
  printf("Ahoj.\nJá jsem program pro demonstraci konstrukcí jazyka C.\n"
         "Mým autorem je %s.\n", signature);
}
//== konec == jednoduchý tisk na obrazovku ==





//== zaèátek == lokální promìnné
/**
 * Funkce bez parametrù a bez návratové hodnoty. Demonstruje vytváøení
 * celoèíselných promìnných.
 *
 * V¹imnìte si, ¾e deklarace promìnných se mù¾e vyskytovat i uprostøed programu
 */
void variables(void)
{
  int a;     // deklarace (a zároveò definicie) promìnné bez inicializace,
             // promìnná a má teï neznámou hodnotu
  int b = 7; // definice promìnné b s inicializaci, b má hodnotu 7

  a = 11;         // nastavení hodnoty promìnné a na hodnotu 11
  int c = a + b;  // definice a inicializace promìnné c, c má teï hodnotu 18

  // tisk èíselných hodnot promìnných a, b, c
  printf("sou¿et %d a %d je %d\n", a, b, c);

  // v¹imnìte si, ¾e místo promìnné, se zde mù¾e vyskytovat i výraz, pokud je
  // výsledkem správný datový typ
  printf("sou¿in %d a %d je %d\n", a, b, a * b);
}

/**
 * Funkce pro demonstraci, jak tisknout hodnoty jednoduchých typù na
 * standardní výstup.
 *
 * V¹imnìte si maximálních hodnot jednotlivých èíselných typù.
 * V¹imnìte si, jaké formátovací znaèky pou¾ívá funkce printf pro tisk
 * hodnot jednotlivých datových typù.
 * Deklarace konstant obsahujících maximální hodnoty jednotlivých typù se
 * se nachází v hlavièkových souborech limits.h (CHAR_MAX a¾ ULLONG_MAX)
 * a float.h (FLT_MAX, DBL_MAX).
 */
void printTypes(void)
{
  char znak = 'A';               // char se dá pou¾ít jako znak...
  char malecislo = CHAR_MAX;     // ... ale také jako malé celé èíslo
  char * text = "Toto je textový øetìzec.";

  short strednicislo = SHRT_MAX; // short -- støednì velká celá èísla
  int cislo = INT_MAX;           // int -- bì¾nì pou¾ívaná celá èísla
  long vetsicislo = LONG_MAX;    // long -- del¹í celá èísla
  long long obrovskecislo = LLONG_MAX; // long long velmi velká celá èísla

  // Pou¾itím pøedpony unsigned vyrobíme bezznaménkový typ -- pouze kladná
  // celá èísla. Typ unsigned nelze pou¾ít s jinými ne¾ celoèíselnými typy.
  unsigned char kladnemale = UCHAR_MAX;
  unsigned short kladnestredni = USHRT_MAX;
  unsigned int kladnecislo = UINT_MAX;
  unsigned long kladnevetsi = ULONG_MAX;
  unsigned long long kladneobrovske = ULLONG_MAX;

  float descislo = FLT_MAX;    // desetinná èísla s jednoduchou pøesností
  double presnejsi = DBL_MAX;  // desetinná èísla s dvojitou pøesností

  printf("Pøehled jednoduchých datových typù.\n");
  printf("char jako èíslo -- maximum:    %hhd\n", malecislo);
  printf("unsigned char -- maximum:      %hhu\n", kladnemale);
  printf("short -- maximum:              %hd\n", strednicislo);
  printf("unsigned short -- maximum:     %hu\n", kladnestredni);
  printf("int -- maximum:                %d\n", cislo);
  printf("unsigned int -- maximum:       %u\n", kladnecislo);
  printf("long -- maximum:               %ld\n", vetsicislo);
  printf("unsigned long -- maximum:      %lu\n", kladnevetsi);
  printf("long long -- maximum:          %lld\n", obrovskecislo);
  printf("unsigned long long -- maximum: %llu\n", kladneobrovske);
  printf("float -- maximum:              %g\n", descislo);
  printf("double -- maximum:             %g\n", presnejsi);
  printf("char jako znak: %c\n", znak);
  printf("textový øetìzec: %s\n", text);
}

//== konec == lokální promìnné





//== zaèátek == funkce bez návratové hodnoty s parametry pøedávanými hodnotou
/**
 * Funkce bez návratové hodnoty, ale s parametry pøedávanými hodnotou.
 * Hodnota parametrù a a b se nyní specifikuje a¾ pøi zavolání funkce, tak¾e
 * výsledek závisí na tom, jak programátor tuto funkci pou¾ije.
 */
void parameters1(int a, int b)
{
  int c = a + b; // hodnota lokální promìnné c je rovna souètu hodnot a a b

  // tisk èíselných hodnot promìnných a, b, c
  printf("souèet %d a %d je %d\n", a, b, c);

  // tisk souèinu hodnot a a b
  printf("souèin %d a %d je %d\n", a, b, a * b);
}
//== konec == funkce bez návratové hodnoty s parametry pøedávanými hodnotou





//== zaèátek == funkce s návratovou hodnotou
/**
 * Vypoète obsah trojúhelníka pomocí Heronova vzorce.
 * Parametry a, b, c udávají délky jednotlivých stran.
 * Funkce vrací obsah trojúhelníka jako svoji návratovou hodnotu.
 * Funkce pou¾ívá funkci sqrt pro výpoèet odmocniny. Tato funkce se nachází
 * v matematické knihovnì, proto bylo potøeba pou¾ít rozhraní math.h.
 *
 * Pozor! Funkce v této podobì funguje chybnì pro taková zadání, ze kterých
 * nelze sestrojit trojúhelník. Zkuste se zamyslet, jaké pøípady to jsou.
 */
double getArea(double a, double b, double c)
{
  double s = (a + b + c)/2.0;       // pomocná lokální promìnná
  return sqrt(s*(s-a)*(s-b)*(s-c)); // pøíkaz return vrací výslednou hodnotu
                                    // pro volající funkci
}

/**
 * Funkce se tøemi parametry bez návratové hodnoty. Volá funkci getArea.
 * Demonstruje volání funkce s parametry a získávání její návratové hodnoty.
 */
void triangle(double a, double b, double c)
{
  // pomocná lokální promìnná
  double obvod = a + b + c;

  // Zavolá funkci getArea definovanou vý¹e, která z parametrù a, b, c
  // vypoète obsah trojúhelníka a vrátí jej jako svou návratovou hodnotu.
  // Tato hodnota se zde následnì ulo¾í do promìnné obsah.
  double obsah = getArea(a, b, c);

  printf("Máme dán trojúhelník o stranách a=%f, b=%f, c=%f.\n"
         "Obvod trojúhelníka je %f.\n"
         "Obsah trojúhelníka je %f.\n",
         a, b, c, obvod, obsah);
}
//== konec == funkce s návratovou hodnotou




//== zaèátek == funkce s parametry pøedávanými odkazem
/**
 * Funkce bez návratové hodnoty, ale se dvìma parametry pøedávanými odkazem.
 * Funkce swap vymìní obsahy zadaných promìnných.
 * Parametry a a b se zde pøedávají odkazem, tedy pomocí ukazatele. Typ int *
 * znamená "ukazatel na int". Uvnitø funkce musíme s hodnotami pracovat pomocí
 * dereferenèního operátoru *.
 */
void swap(int *a, int *b)
{
  int tmp = *a;  // uchování hodnoty promìnné *a
  *a = *b;       // do *a ulo¾í hodnotu *b
  *b = tmp;      // do *b ulo¾ hodnotu promìnné tmp

  // Pozor!
  // a -- promìnná typu ukazatel na int
  // *a -- pohled na místo v pamìti, kam ukazatel a odkazuje, tedy promìnná
  //       typu int
}

/**
 * Demonstrace volání funkcí s parametry pøedávanými odkazem.
 * Volá funkci swap, která má dva parametry pøedávané odkazem.
 */
void parameters2(void)
{
  int x = -115;
  int y = 687;

  printf("Inicializace: x = %d, y = %d\n", x, y);

  // Funkce swap oèekává, ¾e za parametry dosadíme ukazatele na int.
  // Potøebujeme tedy zjistit, na jakých adresách pamìti le¾í promìnné x a y.
  // Vyu¾ijeme k tomu referenèní operátor &. Výraz &x vrací adresu promìnné x,
  // èili ukazatel na promìnnou x.
  swap(&x, &y);

  printf("Po zavolání swap(&x, &y): x = %d, y = %d\n", x, y);

  // V¹imnìte si, ¾e do parametrù pøedávaných odkazem nelze dosadit konstantní
  // výraz, proto¾e takový výraz 1) nelze modifikovat 2) nejsme schopni urèit
  // jeho adresu v pamìti.
  // Následující pøíklady jsou nesmyslné.
  // swap(12, 3+x);      -- tohle nejde
  // swap(&12, &(3+x));  -- ani tohle nejde
}
//== konec == funkce s parametry pøedávanými odkazem




//== zaèátek == kombinace v¹ech tøí zpùsobù komunikace funkce s okolím
/**
 * Bezpeèné dìlení. Funkce vypoète podíl a zbytek po dìlení dvou èísel.
 * Pokud je v¹e v poøádku, je její návratovou hodnotou logická hodnota true
 * (jednièka) a parametr divident bude obsahovat celoèíselný podíl a parametr
 * remainder bude obsahovat zbytek po dìlení. Pokud by mìlo dojít k dìlení
 * nulou, které pro celá èísla není definováno, funkce vrátí false (nula).
 * V tomto pøípadì zùstanou hodnoty parametrù divident a remainder nedotèeny.
 */
int safeDivision(int *divident, int divisor, int *remainder)
{
  if (divisor == 0)
    return 0; // false

  *remainder = *divident % divisor;  // zbytek po celoèíselném dìlení
  *divident = *divident / divisor;   // celoèíselné dìlení
  return 1;  // true
}

/**
 * Demonstrace volání funkce safeDivision, kde se kombinuje návratová hodnota,
 * parametry pøedávané hodnotou i odkazem.
 */
void parameters3(int x, int y)
{
  int rest;   // Pozor! Neinicializovaná hodnota je ¹patný zvyk!
              // Vìt¹inou zde asi bude hodnota 0, ale nedá se na to spoléhat!

  printf("Pøed výpoètem: x = %d, y = %d, rest = %d\n", x, y, rest);

  // Volání funkce safeDivision a okam¾ité pou¾ití její návratové hodnoty
  // v podmínce pøíkazu if. Promìnné x a rest se pøedávají odkazem, proto¾e
  // budou ve funkci modifikovány. Promìnná y se pøedává hodnotou a její
  // hodnota se nemù¾e zmìnit.
  if (safeDivision(&x, y, &rest))
  {
    printf("Po dìlení: x = %d, y = %d, rest = %d\n", x, y, rest);
  }
  else
  {
    printf("Dìlení nulou! Nic se nespoèítalo: x = %d, y = %d, rest = %d\n", x, y, rest);
  }
}
//== konec == kombinace v¹ech tøí zpùsobù komunikace funkce s okolím



///////// Funkce main /////////////////////////////////////////////////////////

/**
 * Hlavní funkce programu. Zde se nachází startovací bod programu. Funkce
 * main se spustí jako první pøi spu¹tìní pøelo¾eného programu. Z této funkce
 * se volají v¹echny ostatní podprogramy.
 *
 * V tomto pøípadì jde o funkci bez parametrù (to øíká klíèové slovo void),
 * která vrací hodnotu typu int. Podle této hodnoty operaèní systém, který
 * tuto funkci zavolal, pozná, zda program skonèil bez problémù nebo jestli
 * nedo¹lo k nìjaké chybì.
 */
int main(void)
{
  printf("=== funkce hello ===\n");
  hello();  // závorky zde nesmìjí chybìt!

  printf("\n=== funkce signedHello ===\n");
  signedHello("David Martinek"); //za parametr dosazen øetìzec "David Martinek"


  printf("\n=== funkce variables ===\n");
  variables(); // závorky zde nesmìjí chybìt!

  printf("\n=== funkce printTypes ===\n");
  printTypes();// závorky zde nesmìjí chybìt!


  printf("\n=== funkce parameters ===\n");
  // parametr a obdr¾í kopii hodnoty 17
  // parametr b obdr¾í kopii hodnoty 24
  parameters1(17, 24);


  printf("\n=== funkce triangle - obsah trojúhelníka ===\n");
  // strany trojúhelníka mají délku 43.2, 92.4 a 62.3
  triangle(43.2, 92.4, 62.3);

  printf("\n=== funkce triangle - co kdy¿ ze zadaných hodnot nelze vytvo¿it trojúhelník? ===\n");
  // strany trojúhelníka mají délku 2.5, 3.1 a 12.0 -- takový trojúhelník
  // nelze zkonstruovat
  triangle(2.5, 3.1, 12.0);
  // Poznámka: NaN znamená Not a Number - speciální hodnota typu double,
  //           která se pou¾ívá pro situace, kdy výsledek operace není
  //           definován.


  printf("\n=== funkce parameters2 - p¿edávání parametrú odkazem ===\n");
  parameters2();


  printf("\n=== funkce parameters3 - parametry odkazem i hodnotou ===\n");
  parameters3(46, 21);

  printf("\n=== funkce parameters3 - d¿lení nulou ===\n");
  parameters3(46, 0);

  return EXIT_SUCCESS;  // program konèí bez chyby
}
