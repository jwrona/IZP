/*
  Projekt: Jak na projekty v jazyce C

  Základní konstrukce jazyka C
  Lekce 3 - ukazatele

  Autor: David Martinek, martinek (zavináè) fit.vutbr.cz
  Datum: 12.03.2009
  Kódování dokumentu: ISO8859-2
  Popis: Tento program slou¾í pro demonstraci základních stavebních prvkù
         jazyka C.
  Webová adresa: http://www.fit.vutbr.cz/~martinek/clang/
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
#include <stdio.h>
#include <stdlib.h>

///////// Definice konstant ///////////////////////////////////////////////////
// symbolická konstanta
#define DELKA 10

///////// Definice podprogramù ////////////////////////////////////////////////

//== zaèátek = ukazatele na lokální promìnné ==
/**
 * Funkce pro demonstraci práce s ukazateli na jednoduché datové typy.
 *
 * Ukazatel je speciální èíselný datový typ. Promìnné typu ukazatel obsahují
 * celé èíslo, které je interpretováno jako adresa urèité pamì»ové buòky.
 * Obvykle pracujeme s tzv. typovými ukazateli, tedy ukazateli na int, double,
 * char, atd. Takovému cílovému typu se øíká bázový typ ukazatele a slou¾í
 * k tomu, abychom vìdìli, na jak velkou èást pamìti od dané adresy se máme
 * podívat. Napø. typ int * je ukazatel na ètyøbajtový int, tedy adresa ukazuje
 * na konkrétní místo v pamìti (buòku o velikosti 1 bajt) a pøekladaè ví, ¾e
 * mù¾e pracovat s následujícími ètyømi bajty.
 */
void simplePointers(void)
{
  int promenna = 1234; // promìnná typu int obsahující hodnotu 1234
  // definice lokální promìnné typu ukazatel na int
  // nyní obsahuje náhodnou adresu, nelze ji tedy rozumnì pou¾ít
  int *ukazatel;

  // nyní zkopírujeme do promìnné ukazatel adresu promìnné promenna
  // & je tzv. referenèní operátor - vrací adresu svého argumentu
  ukazatel = &promenna;

  // nyní vytvoøíme druhou promìnnou typu ukazatel na int
  // a zkopírujeme do ní obsah promìnné ukazatel
  // druhyUk nyní obsahuje rovnì¾ adresu promìnné promenna
  // øíkáme, ¾e ukazuje na promìnnou promenna
  int *druhyUk = ukazatel;

  // ukazatele, tedy adresy lze porovnávat
  if (ukazatel == druhyUk)
  {
    printf("Oba ukazatele ukazují na stejné místo v pamìti.\n");
  }

  // Pomocí operátoru * se umíme podívat na místo, na které ukazatel ukazuje.
  // * je tzv. dereferenèní operátor - vrací hodnotu, na kterou ukazatel ukazuje
  // Datový typ výsledku je urèen bázovým typem ukazatele, tak¾e pokud ukazatel
  // ukazuje na int, je výsledek operátoru * také typu int.
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // Obsah promìnné promenna lze nyní modifikovat tøemi zpùsoby.
  // 1. pøímou zmìnou  promìnné promenna
  promenna = 987;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // 2. pøes promìnnou ukazatel pomocí dereferenèního operátoru
  *ukazatel = 654;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // 3. pøes promìnnou druhyUk opìt pomocí dereferenèního operátoru
  *druhyUk = 357;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);


  // Ukazatele na rùzné bázové typy jsou vzájemnì kompatibilní jenom tak, jak
  // jsou vzájemnì kompatibilní tyto bázové typy.
  // V tomto pøípadì by pøekladaè vypsal varování:
  // warning: initialization from incompatible pointer type
//  double *ukDouble = ukazatel;
  // Program by se sice nakonec pøelo¾il, ale dále v programu by toto mohlo
  // vést k záva¾ným chybám.

  // Ukazatele + return
  // POZOR! Funkce mohou vracet ukazatel, ale nikdy se nepokou¹ejte vracet
  // ukazatel ukazující na lokální promìnnou! Lokální promìnné po ukonèení
  // funkce zanikají, proto by výsledek takovéto funkce nebyl pou¾itelný,
  // resp. jeho pou¾itím bychom zpùsobili chybu bìhu programu.

  // TIP: Pokud nìèemu nerozumíte, zeptejte se nebo zkuste najít odpovìï ve
  // vhodné uèebnici jazyka C.
}

//== konec = ukazatele na lokální promìnné ==

//== zaèátek = ukazatele a lokální pole ==

/**
 * Pomocná funkce pro tisk obsahu pole na standardní výstup.
 *
 * V¹imnìte si, ¾e parametr pole se pøedává jako ukazatel na bázový typ int
 * a dále se s ním pracuje jako s polem.
 *
 * Dále si v¹imnìte, ¾e je nutné pøedat jako dal¹í parametr poèet prvkù pole,
 * proto¾e datový typ pole si poèet svých prvkù nepamatuje.
 *
 * TIP: Datový typ pole v jazyce C si nepamatuje, ani nemù¾e pamatovat svou
 *      délku. Zamyslete se nad tím, proè tomu tak je.
 */
void tiskPole(char * text, int *pole, int delka)
{
  printf("%s { ", text);
  for (int i = 0; i < delka; ++i)
  {
    printf("%d, ", pole[i]);
  }
  printf("}\n");
}

/**
 * Funkce pro demonstraci vztahu mezi ukazateli a lokálními poli.
 *
 */
void lokalniPole(void)
{

  // neinicializovaný ukazatel
  int *uk;

  // neinicializované jednorozmìrné pole
  int mocniny[DELKA];

  // podíváme se, co pole skuteènì obsahuje
  // v¹imnìte si, jak se pole pøedává funkci tiskPole
  tiskPole("mocniny = ", mocniny, DELKA);

  // inicializace pole
  for (int i = 0; i < DELKA; ++i)
  {
    mocniny[i] = i*i;
  }
  // podíváme se, co pole skuteènì obsahuje po inicializaci
  tiskPole("mocniny = ", mocniny, DELKA);

  // kopie ukazatele - samotný identifikátor pole má význam ukazatele na
  // zaèátek pole
  // od této chvíle lze s ukazatelem uk pracovat stejnì jako s polem
  // POZOR! Zde se nevytváøí kopie pole! Pole zùstává v pamìti jen jednou.
  //        Zde se kopíruje ukazatel, tak¾e k jednomu poli pak jde pøistupovat
  //        ze dvou míst - pøes identifikátory uk a mocniny.
  uk = mocniny;
  tiskPole("uk = ", uk, 10);

  // pøes ukazatel mù¾eme pole modifikovat
  // nyní vyrobíme posloupnost tøetích mocnin celých èísel
  for (int i = 0; i < DELKA; ++i)
  {
    uk[i] = uk[i] * i; // nebo takto: uk[i] *= i;
  }

  tiskPole("uk = ", uk, 10);

  // POZOR! Opaènì to nejde! Do promìnné typu pole NELZE nic pøiøadit
  // pole = uk; // toto pøekladaè odhalí jako syntaktickou chybu
}

/**
 * Funkce pro demonstraci toho, jak se dají kopírovat lokální, jednorozmìrná
 * pole.
 */
void kopieLokalnichPoli(void)
{
  // dvì lokální, neinicializovaná pole
  int pole1[DELKA], pole2[DELKA];

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    pole1[i] = i + 1;
  }

  tiskPole("pole1 = ", pole1, DELKA);

  // pole nelze kopírovat pouhým pøiøazením!
  // datový typ pole nezná svou délku, tak¾e by pøekladaè nevìdìl, kolik jak
  // velký úsek pamìti má kopírovat
//  pole2 = pole1; // syntaktická chyba

  // musíme postupovat prvek po prvku (nebo pou¾ít odpovídající knihovní funkci)
  for (int i = 0; i < DELKA; ++i)
  {
    pole2[i] = pole1[i];
  }

  tiskPole("pole2 = ", pole2, DELKA);
}

//== konec = ukazatele a lokální pole ==


//== zaèátek = dynamická alokace ==

/**
 * Demonstrace dynamicky alokovaných promìnných.
 *
 * Lokální promìnné jsou umístìny v oblasti pamìti zvané zásobník. Pøi definici
 * promìnné se automaticky na zásobníku vyhradí potøebný kus pamìti a pøi
 * ukonèení bloku nebo funkce se tato pamì» zase automaticky uvolní - není
 * potøeba se o to starat. Nevýhodou je, ¾e lokální promìnné nelze vynést
 * z funkce ven, proto¾e po jejím ukonèení automaticky zanikají. Velikost
 * zásobníku také bývá z bezpeènostních dùvodù omezena, tak¾e nelze vyu¾ít
 * ve¹kerou dostupnou pamì» poèítaèe.
 *
 * Dynamicky alokované promìnné jsou umístìny v oblasti pamìti zvané hromada.
 * Tuto pamì» lze spravovat pouze ruènì, pomocí volání knihovních funkcí
 * malloc a free. Tímto zpùsobem lze vyu¾ít témìø ve¹kerou dostupnou pamì»
 * poèítaèe, ale programátor je sám zodpovìdný za správnou alokaci pamìti
 * i její uvolnìní, pokud u¾ ji nepotøebuje.
 */
void dynamickaAlokace(void)
{
  // neinicializovaný ukazatel na int
  int *uCislo;

  // alokace pamìti na hromadì o velikosti jednoho intu
  // operátor sizeof vrací poèet bajtù, které daný typ zabírá
  // funkci malloc pou¾ívejte V®DY v kombinaci se sizeof
  // tímto pøíkazem alokujeme na hromadì prostor pro jednu promìnnou typu int
  uCislo = malloc(1*sizeof(int));

  // k novì alokované promìnné lze pøistupovat pouze pomocí ukazatele, v na¹em
  // pøípadì uCislo
  // prozatím je hodnota alokované pamì»ové buòky neinicializovaná
  // k hodnotì pamì»ové buòky na adrese uCislo se nyní dostaneme pomocí
  // dereferenèního operátoru *
  printf("*uCislo = %d\n", *uCislo);
  *uCislo = 10;
  printf("*uCislo = %d\n", *uCislo);

  // dále tuto buòku nebudeme potøebovat, proto ji musíme uvolnit pomocí
  // funkce free - v¹imnìte si, ¾e funkci free se pøedává ukazatel
  free(uCislo);

  // Nyní je uCislo de facto neinicializovaný ukazatel, resp. ukazuje do
  // nealokované pamìti. Odkaz pøes takový ukazatel by zpùsobil havárii.
  // Èásteèným zmírnìním tohoto rizika je nastavení na hodnotu NULL, co¾ je
  // prázdný ukazatel. Odkaz pøes nìj vede také k havárii, ale alespoò takový
  // ukazatel mù¾eme otestovat, ne¾ s ním nìco provedeme (èasto se takto
  // testují parametry funkcí).
  uCislo = NULL;


  // stejným zpùsobem mù¾eme na hromadì alokovat pole
  // k pøístupu k takto alokovanému poli vyu¾ijeme ukazatel
  // funkci malloc øekneme, aby alokovala pamì» o velikosti DELKA*sizeof(int)
  // bajtù
  int *dynPole = malloc(DELKA*sizeof(int));

  // nyní je pole neinicializované (nenechte se zmást, pokud v nìm budou nuly,
  // je to jen náhoda)
  // v¹imnìte si, ¾e od této chvíle se s dynamicky alokovaným polem pracuje
  // stejnì jako s lokálním
  tiskPole("dynPole = ", dynPole, DELKA);

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    dynPole[i] = i*i;
  }
  tiskPole("dynPole = ", dynPole, DELKA);

  // po skonèení práce musíme pole zase uvolnit
  free(dynPole);
}

/**
 * Demonstrace kopírování dynamických polí.
 */
void kopieDynamickychPoli(void)
{
  // dvì lokální promìnné typu ukazatel na int
  int *pole1, *pole2;

  // alokujeme pole s délkou delka
  pole1 = malloc(DELKA*sizeof(int));

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    pole1[i] = i + 1;
  }
  tiskPole("pole1 = ", pole1, DELKA);

  // toto je pouhá kopie ukazatelù, nikoli polí!
  // nyní budou na stejné pole ukazovat dva ukazatele
  pole2 = pole1;

  // udìláme v poli zmìnu pøes ukazatel pole2, abychom vidìli, ¾e tato zmìna
  // bude viditelná i pøes ukazatel pole1
  pole2[5] = 9999;
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // skuteènou kopii lze udìlat pouze tak, ¾e alokujeme prostor pro druhé,
  // stejnì dlouhé pole a pak jej prvek po prvku zkopírujeme
  pole2 = malloc(DELKA*sizeof(int));
  for (int i = 0; i < DELKA; ++i)
  {
    pole2[i] = pole1[i];
  }
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // nyní máme skuteènou kopii pole
  // aby bylo vidìt, ¾e oba ukazatele ukazují na jiná pole, provedeme v jednom
  // z nich zmìnu
  pole2[2] = 888;
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // nakonec musíme alokovanou pamì» uvolnit
  free(pole1);
  free(pole2);
}

//== konec = dynamická alokace ==

//== zacatek = operace s typem ukazatel ==
/**
 * Ukázka dal¹ích operací nad datovým typem ukazatel. Bì¾nì pou¾ívané jsou
 * pøiøazení, indexování, reference a dereference. Ostatní (porovnávání,
 * sèítání s celými èísly) NEPOU®ÍVEJTE dokud to nebude absolutnì nezbytné,
 * proto¾e to obvykle vede k tì¾ko èitelným programùm.
 */
void operaceNadUkazateli(void)
{
  // ukazatele lze kopírovat pøiøazovacím operátorem - kopíruje se adresa!
  int *pole = malloc(DELKA*sizeof(int));

  // ukazatele lze indexovat
  for (int i = 0; i < DELKA; ++i)
  {
    if (i <= 1)
    { pole[i] = i; }
    else
    { pole[i] = pole[i-1] + pole[i-2]; }
  }
  tiskPole("pole = ", pole, DELKA);

  // ukazatele lze i porovnávat a pøièítat/odeèítat k nim celé èíslo
  // tomuto se øíká adresová aritmetika
  // POZOR! Tohle nepou¾ívejte. Adresová aritmetika vede k obtí¾nì èitelnému
  // kódu, proto je takový program více náchylný k chybám.
  // POZOR! Nepou¾ívejte to jen proto, abyste udìlali dojem. Pøi obhajobì
  // projektu tím spí¹e vyprovokujete otázky, které velmi dùkladnì provìøí
  // va¹e skuteèné znalosti!

  int *pozice = pole; // kopie ukazatelù
  printf("Fibonacciho posloupnost: ");
  // pøiètení èísla k adrese znamená toté¾, co indexování
  while (pozice < pole+DELKA) // porovnání ukazatelù
  {
    printf(" %d ", *pozice); // dereference - získání odkazované hodnoty
    ++pozice; // posun na adresu dal¹ího prvku v poli -- adresa = adresa + sizeof(int)
  }
  printf("\n");


  // Adresové aritmetiky se dá také pou¾ít pro pøedání pouze èásti pole do
  // podprogramu. Zde pøedáváme ukazatel na pole posunutý o 3 prvky (tedy od
  // indexu 3) øíkáme funkci, ¾e má zpracovat následující 4 prvky.
  // TIP: U¾ jste si uvìdomili, proè si pole nemù¾e pamatovat svou délku?
  tiskPole("pole[3-6] = ", pole+3, 4);

  // Stejnì mù¾eme zpracovávat textové øetìzce
  char * zprava = "Uvedomte si, ze jazyk C je fajn";
  printf("%s\n", zprava+16);

  // nyní uvolníme nepou¾ívanou pamì»
  free(pole);
//  free(pozice); // Tohle by vedlo k havárii. Proè?

}
//== konec = operace s typem ukazatel ==

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
  printf("=== funkce simplePointers ===\n");
  simplePointers();

  printf("=== funkce lokalniPole ===\n");
  lokalniPole();

  printf("=== funkce kopieLokalnichPoli ===\n");
  kopieLokalnichPoli();

  printf("=== funkce dynamickaAlokace ===\n");
  dynamickaAlokace();

  printf("=== funkce kopieDynamickychPoli ===\n");
  kopieDynamickychPoli();

  printf("=== funkce operaceNadUkazateli ===\n");
  operaceNadUkazateli();


  return EXIT_SUCCESS;  // program konèí bez chyby
}
