/*
  Projekt: Jak na projekty v jazyce C
  Autor: David Martinek, martinek (zavin�) fit.vutbr.cz
  Datum: 11.02.2009
  K�dov�n� dokumentu: ISO8859-2
  Popis: Tento program slou�� pro demonstraci z�kladn�ch stavebn�ch prvk�
         jazyka C.
*/

// Jak ��st tento zdrojov� soubor
// 1. Za�n�te sekc� pro vkl�d�n� rozhran� knihoven.
// 2. Pod�vejte se na funkci main, kter� se nach�z� na konci souboru.
// 3. Ve funkci main se v ur�it�m po�ad� volaj� jednotliv� podprogramy.
//    V tom po�ad�, v jak�m se volaj� ve funkci main, si prohl�dn�te jejich
//    definice v prost�edn� ��sti zdrojov�ho souboru. P�ed ka�dou funkc� se
//    nach�z� koment��, kter� vysv�tluje, co se v t�to funkci d�je.
// 4. P�elo�te tento zdrojov� soubor pomoc� p�eklada�e jazyka C. Na webov�ch
//    str�nk�ch Jak na projekty v jazyce C najdete postup, jak p�eklada�
//    zavolat.
//    Tak� m��ete pou��t p��kaz make. Makefile je p�ibalen. Pokud nerozum�te,
//    co to znamen�, p�e�t�te si o programu make na webov�ch str�nk�ch.


////////// Sekce pro vkl�d�n� rozhran� knihoven ///////////////////////////////

// Zde se vkl�d� rozhran� knihoven, kter� bude program pou��vat. V tomto
// programu se budou pou��vat podprogramy z n�kolika ��st� syst�mov� knihovny.
// V tomto konkr�tn�m p��pad� bude pot�eba rozhran� stdio.h, stdlib.h, math.h,
// limits.h a float.h.
// Informaci o tom, jak� rozhran� je pot�eba pou��t, se dozv�te v n�pov�d�
// k syst�mov�m funkc�m (nap��klad v manu�lov�ch str�nk�ch).
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>

///////// Definice podprogram� ////////////////////////////////////////////////

//== za��tek == jednoduch� tisk na obrazovku ==
/**
 * Funkce bez parametr� a bez n�vratov� hodnoty (kl��ov� slovo void).
 * Pomoc� syst�mov� funkce printf vytiskne n�pis na standardn� v�stup programu.
 * V�imn�te si, �e od��dkov�n� se prov�d� vlo�en�m \n do textu.
 * V�imn�te si, �e v�ce textov�ch �et�zc� za sebou, kter� jsou odd�leny jenom
 * mezerami, tvo�� jeden textov� �et�zec.
 */
void hello(void)
{
  printf("Ahoj.\n"
         "J� jsem program pro demonstraci z�kladn�ch konstrukc� jazyka C.\n");
}

/**
 * Funkce bez n�vratov� hodnoty, ale s jedn�m parametrem. Parametr signature
 * je textov� �et�zec (typ char*). Pomoc� tohoto parametru m��eme m�nit
 * ��st textu, kter� se bude tisknout.
 *
 * V�imn�te si zna�ky %s v ti�t�n�m �et�zci. Na m�st� t�to zna�ky se vytiskne
 * obsah prom�nn�, kter� se nach�z� za �et�zcem. V tomto p��pad� jde
 * o prom�nnou signature.
 */
void signedHello(char *signature)
{
  printf("Ahoj.\nJ� jsem program pro demonstraci konstrukc� jazyka C.\n"
         "M�m autorem je %s.\n", signature);
}
//== konec == jednoduch� tisk na obrazovku ==





//== za��tek == lok�ln� prom�nn�
/**
 * Funkce bez parametr� a bez n�vratov� hodnoty. Demonstruje vytv��en�
 * celo��seln�ch prom�nn�ch.
 *
 * V�imn�te si, �e deklarace prom�nn�ch se m��e vyskytovat i uprost�ed programu
 */
void variables(void)
{
  int a;     // deklarace (a z�rove� definicie) prom�nn� bez inicializace,
             // prom�nn� a m� te� nezn�mou hodnotu
  int b = 7; // definice prom�nn� b s inicializaci, b m� hodnotu 7

  a = 11;         // nastaven� hodnoty prom�nn� a na hodnotu 11
  int c = a + b;  // definice a inicializace prom�nn� c, c m� te� hodnotu 18

  // tisk ��seln�ch hodnot prom�nn�ch a, b, c
  printf("sou�et %d a %d je %d\n", a, b, c);

  // v�imn�te si, �e m�sto prom�nn�, se zde m��e vyskytovat i v�raz, pokud je
  // v�sledkem spr�vn� datov� typ
  printf("sou�in %d a %d je %d\n", a, b, a * b);
}

/**
 * Funkce pro demonstraci, jak tisknout hodnoty jednoduch�ch typ� na
 * standardn� v�stup.
 *
 * V�imn�te si maxim�ln�ch hodnot jednotliv�ch ��seln�ch typ�.
 * V�imn�te si, jak� form�tovac� zna�ky pou��v� funkce printf pro tisk
 * hodnot jednotliv�ch datov�ch typ�.
 * Deklarace konstant obsahuj�c�ch maxim�ln� hodnoty jednotliv�ch typ� se
 * se nach�z� v hlavi�kov�ch souborech limits.h (CHAR_MAX a� ULLONG_MAX)
 * a float.h (FLT_MAX, DBL_MAX).
 */
void printTypes(void)
{
  char znak = 'A';               // char se d� pou��t jako znak...
  char malecislo = CHAR_MAX;     // ... ale tak� jako mal� cel� ��slo
  char * text = "Toto je textov� �et�zec.";

  short strednicislo = SHRT_MAX; // short -- st�edn� velk� cel� ��sla
  int cislo = INT_MAX;           // int -- b�n� pou��van� cel� ��sla
  long vetsicislo = LONG_MAX;    // long -- del�� cel� ��sla
  long long obrovskecislo = LLONG_MAX; // long long velmi velk� cel� ��sla

  // Pou�it�m p�edpony unsigned vyrob�me bezznam�nkov� typ -- pouze kladn�
  // cel� ��sla. Typ unsigned nelze pou��t s jin�mi ne� celo��seln�mi typy.
  unsigned char kladnemale = UCHAR_MAX;
  unsigned short kladnestredni = USHRT_MAX;
  unsigned int kladnecislo = UINT_MAX;
  unsigned long kladnevetsi = ULONG_MAX;
  unsigned long long kladneobrovske = ULLONG_MAX;

  float descislo = FLT_MAX;    // desetinn� ��sla s jednoduchou p�esnost�
  double presnejsi = DBL_MAX;  // desetinn� ��sla s dvojitou p�esnost�

  printf("P�ehled jednoduch�ch datov�ch typ�.\n");
  printf("char jako ��slo -- maximum:    %hhd\n", malecislo);
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
  printf("textov� �et�zec: %s\n", text);
}

//== konec == lok�ln� prom�nn�





//== za��tek == funkce bez n�vratov� hodnoty s parametry p�ed�van�mi hodnotou
/**
 * Funkce bez n�vratov� hodnoty, ale s parametry p�ed�van�mi hodnotou.
 * Hodnota parametr� a a b se nyn� specifikuje a� p�i zavol�n� funkce, tak�e
 * v�sledek z�vis� na tom, jak program�tor tuto funkci pou�ije.
 */
void parameters1(int a, int b)
{
  int c = a + b; // hodnota lok�ln� prom�nn� c je rovna sou�tu hodnot a a b

  // tisk ��seln�ch hodnot prom�nn�ch a, b, c
  printf("sou�et %d a %d je %d\n", a, b, c);

  // tisk sou�inu hodnot a a b
  printf("sou�in %d a %d je %d\n", a, b, a * b);
}
//== konec == funkce bez n�vratov� hodnoty s parametry p�ed�van�mi hodnotou





//== za��tek == funkce s n�vratovou hodnotou
/**
 * Vypo�te obsah troj�heln�ka pomoc� Heronova vzorce.
 * Parametry a, b, c ud�vaj� d�lky jednotliv�ch stran.
 * Funkce vrac� obsah troj�heln�ka jako svoji n�vratovou hodnotu.
 * Funkce pou��v� funkci sqrt pro v�po�et odmocniny. Tato funkce se nach�z�
 * v matematick� knihovn�, proto bylo pot�eba pou��t rozhran� math.h.
 *
 * Pozor! Funkce v t�to podob� funguje chybn� pro takov� zad�n�, ze kter�ch
 * nelze sestrojit troj�heln�k. Zkuste se zamyslet, jak� p��pady to jsou.
 */
double getArea(double a, double b, double c)
{
  double s = (a + b + c)/2.0;       // pomocn� lok�ln� prom�nn�
  return sqrt(s*(s-a)*(s-b)*(s-c)); // p��kaz return vrac� v�slednou hodnotu
                                    // pro volaj�c� funkci
}

/**
 * Funkce se t�emi parametry bez n�vratov� hodnoty. Vol� funkci getArea.
 * Demonstruje vol�n� funkce s parametry a z�sk�v�n� jej� n�vratov� hodnoty.
 */
void triangle(double a, double b, double c)
{
  // pomocn� lok�ln� prom�nn�
  double obvod = a + b + c;

  // Zavol� funkci getArea definovanou v��e, kter� z parametr� a, b, c
  // vypo�te obsah troj�heln�ka a vr�t� jej jako svou n�vratovou hodnotu.
  // Tato hodnota se zde n�sledn� ulo�� do prom�nn� obsah.
  double obsah = getArea(a, b, c);

  printf("M�me d�n troj�heln�k o stran�ch a=%f, b=%f, c=%f.\n"
         "Obvod troj�heln�ka je %f.\n"
         "Obsah troj�heln�ka je %f.\n",
         a, b, c, obvod, obsah);
}
//== konec == funkce s n�vratovou hodnotou




//== za��tek == funkce s parametry p�ed�van�mi odkazem
/**
 * Funkce bez n�vratov� hodnoty, ale se dv�ma parametry p�ed�van�mi odkazem.
 * Funkce swap vym�n� obsahy zadan�ch prom�nn�ch.
 * Parametry a a b se zde p�ed�vaj� odkazem, tedy pomoc� ukazatele. Typ int *
 * znamen� "ukazatel na int". Uvnit� funkce mus�me s hodnotami pracovat pomoc�
 * dereferen�n�ho oper�toru *.
 */
void swap(int *a, int *b)
{
  int tmp = *a;  // uchov�n� hodnoty prom�nn� *a
  *a = *b;       // do *a ulo�� hodnotu *b
  *b = tmp;      // do *b ulo� hodnotu prom�nn� tmp

  // Pozor!
  // a -- prom�nn� typu ukazatel na int
  // *a -- pohled na m�sto v pam�ti, kam ukazatel a odkazuje, tedy prom�nn�
  //       typu int
}

/**
 * Demonstrace vol�n� funkc� s parametry p�ed�van�mi odkazem.
 * Vol� funkci swap, kter� m� dva parametry p�ed�van� odkazem.
 */
void parameters2(void)
{
  int x = -115;
  int y = 687;

  printf("Inicializace: x = %d, y = %d\n", x, y);

  // Funkce swap o�ek�v�, �e za parametry dosad�me ukazatele na int.
  // Pot�ebujeme tedy zjistit, na jak�ch adres�ch pam�ti le�� prom�nn� x a y.
  // Vyu�ijeme k tomu referen�n� oper�tor &. V�raz &x vrac� adresu prom�nn� x,
  // �ili ukazatel na prom�nnou x.
  swap(&x, &y);

  printf("Po zavol�n� swap(&x, &y): x = %d, y = %d\n", x, y);

  // V�imn�te si, �e do parametr� p�ed�van�ch odkazem nelze dosadit konstantn�
  // v�raz, proto�e takov� v�raz 1) nelze modifikovat 2) nejsme schopni ur�it
  // jeho adresu v pam�ti.
  // N�sleduj�c� p��klady jsou nesmysln�.
  // swap(12, 3+x);      -- tohle nejde
  // swap(&12, &(3+x));  -- ani tohle nejde
}
//== konec == funkce s parametry p�ed�van�mi odkazem




//== za��tek == kombinace v�ech t�� zp�sob� komunikace funkce s okol�m
/**
 * Bezpe�n� d�len�. Funkce vypo�te pod�l a zbytek po d�len� dvou ��sel.
 * Pokud je v�e v po��dku, je jej� n�vratovou hodnotou logick� hodnota true
 * (jedni�ka) a parametr divident bude obsahovat celo��seln� pod�l a parametr
 * remainder bude obsahovat zbytek po d�len�. Pokud by m�lo doj�t k d�len�
 * nulou, kter� pro cel� ��sla nen� definov�no, funkce vr�t� false (nula).
 * V tomto p��pad� z�stanou hodnoty parametr� divident a remainder nedot�eny.
 */
int safeDivision(int *divident, int divisor, int *remainder)
{
  if (divisor == 0)
    return 0; // false

  *remainder = *divident % divisor;  // zbytek po celo��seln�m d�len�
  *divident = *divident / divisor;   // celo��seln� d�len�
  return 1;  // true
}

/**
 * Demonstrace vol�n� funkce safeDivision, kde se kombinuje n�vratov� hodnota,
 * parametry p�ed�van� hodnotou i odkazem.
 */
void parameters3(int x, int y)
{
  int rest;   // Pozor! Neinicializovan� hodnota je �patn� zvyk!
              // V�t�inou zde asi bude hodnota 0, ale ned� se na to spol�hat!

  printf("P�ed v�po�tem: x = %d, y = %d, rest = %d\n", x, y, rest);

  // Vol�n� funkce safeDivision a okam�it� pou�it� jej� n�vratov� hodnoty
  // v podm�nce p��kazu if. Prom�nn� x a rest se p�ed�vaj� odkazem, proto�e
  // budou ve funkci modifikov�ny. Prom�nn� y se p�ed�v� hodnotou a jej�
  // hodnota se nem��e zm�nit.
  if (safeDivision(&x, y, &rest))
  {
    printf("Po d�len�: x = %d, y = %d, rest = %d\n", x, y, rest);
  }
  else
  {
    printf("D�len� nulou! Nic se nespo��talo: x = %d, y = %d, rest = %d\n", x, y, rest);
  }
}
//== konec == kombinace v�ech t�� zp�sob� komunikace funkce s okol�m



///////// Funkce main /////////////////////////////////////////////////////////

/**
 * Hlavn� funkce programu. Zde se nach�z� startovac� bod programu. Funkce
 * main se spust� jako prvn� p�i spu�t�n� p�elo�en�ho programu. Z t�to funkce
 * se volaj� v�echny ostatn� podprogramy.
 *
 * V tomto p��pad� jde o funkci bez parametr� (to ��k� kl��ov� slovo void),
 * kter� vrac� hodnotu typu int. Podle t�to hodnoty opera�n� syst�m, kter�
 * tuto funkci zavolal, pozn�, zda program skon�il bez probl�m� nebo jestli
 * nedo�lo k n�jak� chyb�.
 */
int main(void)
{
  printf("=== funkce hello ===\n");
  hello();  // z�vorky zde nesm�j� chyb�t!

  printf("\n=== funkce signedHello ===\n");
  signedHello("David Martinek"); //za parametr dosazen �et�zec "David Martinek"


  printf("\n=== funkce variables ===\n");
  variables(); // z�vorky zde nesm�j� chyb�t!

  printf("\n=== funkce printTypes ===\n");
  printTypes();// z�vorky zde nesm�j� chyb�t!


  printf("\n=== funkce parameters ===\n");
  // parametr a obdr�� kopii hodnoty 17
  // parametr b obdr�� kopii hodnoty 24
  parameters1(17, 24);


  printf("\n=== funkce triangle - obsah troj�heln�ka ===\n");
  // strany troj�heln�ka maj� d�lku 43.2, 92.4 a 62.3
  triangle(43.2, 92.4, 62.3);

  printf("\n=== funkce triangle - co kdy� ze zadan�ch hodnot nelze vytvo�it troj�heln�k? ===\n");
  // strany troj�heln�ka maj� d�lku 2.5, 3.1 a 12.0 -- takov� troj�heln�k
  // nelze zkonstruovat
  triangle(2.5, 3.1, 12.0);
  // Pozn�mka: NaN znamen� Not a Number - speci�ln� hodnota typu double,
  //           kter� se pou��v� pro situace, kdy v�sledek operace nen�
  //           definov�n.


  printf("\n=== funkce parameters2 - p�ed�v�n� parametr� odkazem ===\n");
  parameters2();


  printf("\n=== funkce parameters3 - parametry odkazem i hodnotou ===\n");
  parameters3(46, 21);

  printf("\n=== funkce parameters3 - d�len� nulou ===\n");
  parameters3(46, 0);

  return EXIT_SUCCESS;  // program kon�� bez chyby
}
