/*
  Projekt: Jak na projekty v jazyce C

  Základní konstrukce jazyka C
  Lekce 2 - pole, textové øetìzce, cykly

  Autor: David Martinek, martinek (zavináè) fit.vutbr.cz
  Datum: 06.03.2009
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
#include <string.h>


///////// Definice konstant ///////////////////////////////////////////////////
// symbolická konstanta N obsahující hodnotu 5, budeme ji pou¾ívat pro
// specifikaci rozmìrù polí
// TIP: v¹imnìte si, ¾e zde není nikde støedník ani rovnítko
// TIP: podívejte se na tuto konstrukci do nìjaké uèebnice jazyka C
#define N 5

// symbolická konstanta obsahující hodnotu 7
#define M 7

///////// Definice podprogramù ////////////////////////////////////////////////

//== zaèátek == pole - inicializace a tisk na obrazovku ==
/**
 * Funkce, která vyrobí jednorozmìrné pole, naplní jej hodnotami a vytiskne
 * jeho obsah na obrazovku.
 */
void tiskPoleMocnin(void)
{
  int pole[N]; // deklarace + definice lokální promìnné - pole o pìti prvcích
               // ka¾dý prvek tohoto pole je promìnná typu int

  // cyklus pro naplnìní pole hodnotami
  // i - index pole, v tomto pøípadì bude postupnì nabývat hodnot 0, 1, 2, 3 a 4
  // POZOR: v jazyce C se pole indexují od nuly a NIKDY jinak
  for (int i = 0; i < N; ++i)
  {
    pole[i] = i*i; // do ka¾dého prvku vlo¾íme druhou mocninu indexu
  }

  // tisk pole na standardní výstup
  // nelze tisknout celé pole najdenou, musíme tisknout po jednotlivých prvcích
  for (int i = 0; i < N; ++i)
  {
    printf("pole[%d] = %d\n", i, pole[i]);
  }
}

/**
 * Abychom nemuseli ka¾dé pole tisknout ruènì, vyrobíme si funkci, která umí
 * vytisknout pole zadané jako parametr. Proto¾e si datový typ pole neumí
 * zapamatovat svou délku, musíme délku pole dodat jako druhý parametr.
 *
 * pole - jednorozmìrné pole s prvky typu int, v¹imnìte si, ¾e hranaté
 *        závorky jsou prázdné, rozmìr dodáme dal¹ím parametrem
 * delka - délka pole, tedy poèet jeho prvkù
 *
 * TIP: V¹imnìte si, v jakém formátu funce vytiskne pole na výstup. Stejnou
 * formu zápisu lze pou¾ít i v jazyce C pro inicializaci pole pøi definici
 * promìnné.
 */
void tiskPole(int pole[], int delka)
{
  printf("{ ");
  for (int i = 0; i < delka; ++i)
  {
    printf("[%d]=%d, ", i, pole[i]);
  }
  printf("}\n");
}
// Poznámka: pole se v jazyce C pøedává v¾dy jako ukazatel na jeho zaèátek.
// V jazyce C nelze pøedat pole hodnotou. To znamená, ¾e v¾dy kdy¾ modifikujeme
// nìjaký prvek pole pøedaného jako parametr, zùstane tato zmìna v poli
// zachována i po skonèení této funkce.

// Poznámka: Proto¾e pracujeme s jednorozmìrným polem a pro jazyk C jsou pole
// a ukazatele velmi pøíbuzné datové typy (viz uèebnice jazyka C), mohla by
// hlavièka pøedchozí funkce vypadat i takto, ani¾ by se jakkoli zmìnil její
// význam:
// void tiskPole(int *pole, int delka)

/**
 * Demonstrace rùzných zpùsobù vytváøení a inicializací jednorozmìrných polí.
 * Nyní pro tisk pou¾ijeme funkci tiskPole.
 *
 * V¹imnìte si, ¾e se pole pøedává zdánlivì hodnotou, aèkoliv pøedchozí poznámky
 * øíkají, ¾e se pole pøedává jako ukazatel. Je to tak proto, ¾e vlastnì
 * pøedáváme hodnotou ukazatel na zaèátek pole - tento ukazatel nechceme mìnit,
 * pøípadné zmìny by se týkaly prvkù pole, nikoli ukazatele na jeho zaèátek.
 * Blí¾e viz uèebnice jazyka C.
 */
void tiskniLany(void)
{
  // neinicializované pole délky N
  // prvky nyní mohou mít libovolnou hodnotu
  // i kdy¾ èasto bude jejich hodnota nula, nelze se na to spoléhat!
  int pole1[N];
  printf("Neinicializované pole: ");
  tiskPole(pole1, N);

  // inicializace pomocí inicializátoru pole
  // Poèet prvkù nyní není potøeba zadávat, proto¾e se dopoèítá
  // z inicializátoru.
  int pole2[] = {2, 4, 6, 8};
  printf("Inicializátor 1: ");
  tiskPole(pole2, 4);

  // pokud zadáme rozmìr a inicializujeme jenom nìkteré prvky, ostatní prvky
  // budou mít automaticky hodnotu nula
  // POZOR! Tohle platí jen pøi pou¾ití inicializátoru, bez nìj jsou v¹echny
  // prvky neinicializované a mají tudí¾ nezaruèitelnou hodnotu!
  int pole3[7] = {1, 4, 9};
  printf("Inicializátor 2: ");
  tiskPole(pole3, 7);

  // v inicializátoru lze pou¾ít i index, hodí se to zejména u dlouhých
  // polí, v nich¾ chceme inicializovat jen vybrané hodnoty
  // v¹imnìte si, na jakých pozicích jsou prvky bez uvedeného indexu
  // nevyjmenované prvky jsou zde inicializovány na nulu
  // Poznámka: tohle ve star¹ích verzích jazyka C dìlat nejde
  int pole4[7] = {1, 4, [3]=16, 25};
  printf("Inicializátor 2: ");
  tiskPole(pole4, 7);

  // dal¹í mo¾ností je inicializovat pole pomocí cyklu, jak bylo demonstrováno
  // ve funkci tiskPoleMocnin
}

/**
 * Funkce pro tisk dvojrozmìrných polí.
 *
 * Matice nebo 2D pole je vlastnì polem jednorozmìrných polí. Ze stejného
 * dùvodu, jako u jednorozmìrných polí lze zde nechat první hranaté závorky,
 * tedy poèet øádkù pole, prázdné. Poèet øádkù je nutné pøedat jako dal¹í
 * parametr. Dal¹í dimenzi je ov¹em naopak NUTNÉ uvést, aby pøekladaè vìdìl,
 * jak dlouhé jsou øádky, z jeho pohledu tedy prvky jednoprvkového pole.
 *
 * TIP: V¹imnìte si, v jakém formátu funkce tiskne matici na výstup.
 * Stejnou formu zápisu lze pou¾ít i v jazyce C pro inicializace vícerozmìrných
 * polí pøi definicích promìnných. V podstatì jde o slo¾ený inicializátor
 * jednorozmìrného pole.
 *
 * POZOR! Tato funkce je pouze ukázková. V praxi je tento zpùsob práce s maticí
 * z nìkolika dùvodù krajnì NEVHODNÝ a tì¾kopádný. Mnohem vhodnìj¹í je pou¾ívat
 * dynamicky alokovaná pole zabalená spolu s rozmìry ve struktuøe. Blí¾e viz
 * uèebnice jazyka C.
 */
void tiskMatice(int matice[][N], int radku)
{
  printf("{\n");
  for (int r = 0; r < radku; ++r)
  {
    printf("  { ");
    for (int s = 0; s < N; ++s)
    {
      printf("%d, ", matice[r][s]);
    }
    printf("},\n");
  }
  printf("}\n");
}

/**
 * Demonstrace vytváøení a inicializací dvojrozmìrných polí, tedy matic.
 * Matice je v jazyce C chápána jako pole jednorozmìrných polí, neboli pole
 * øádkù. První rozmìr obvykle udává poèet øádkù, druhý rozmìr poèet sloupcù
 * (tedy délku øádkù).
 */
void dvojrozmernaPole(void)
{
  // neinicializované dvojrozmìrné pole o M øádcích a N sloupcích
  int matice1[M][N];
  tiskMatice(matice1, M);

  // pou¾ití iniciálizátorù pro dvojrozmìrné pole MxN (tedy 7x5)
  // v¹imnìte si rùzných zpùsobù inicializace v jednotlivých øádcích
  int matice2[M][N] = {
    { 0, 1, 2, 3, 4 },
    { 0 },
    { [3]=1 },
    { 1, [3]=1, 7 },
    { 5 },
    // poslední dva vynechám úplnì, proto¾e je to uvnitø inicializátoru
    // budou naplnìny nulami
  };
  tiskMatice(matice2, M);
}

/////////////////////////////////////////////////////////////////////////////
// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //
/////////////////////////////////////////////////////////////////////////////
// Pole vytváøená v pøedchozích ukázkách NELZE pou¾ívat jako návratové hodnoty
// funkcí. Nelze ani vytvoøit funkci, která by mìla jako návratový typ tento
// druh polí. Pro tyto úèely se v jazyce C pou¾ívají dynamicky alokovaná pole
// a ukazatele.
/////////////////////////////////////////////////////////////////////////////
// Tato pole rovnì¾ NELZE kopírovat pomocí pøiøazovacího operátoru. Nelze
// udìlat toto: pole1 = pole2. Tuto konstrukci pøekladaè odmítne. Kopírování
// polí je nutné dìlat po prvcích pomocí pøíkazù pro cykly. Dùvodem pro toto
// omezení je to, ¾e si jazyk C nepamatuje délku polí (zejména u vícerozmìrných
// polí by to bylo implementaènì problematické). Je bezpeènìj¹í nechat tuto
// èinnost na programátorovi, který ví, kam a¾ v poli mù¾e jít a zároveò ho to
// nutí si uvìdomit, ¾e operace kopírování polí není zadarmo.
/////////////////////////////////////////////////////////////////////////////

//== konec == lokální pole - inicializace a tisk na obrazovku ==

//== zaèátek == textové øetìzce ==
/**
 * Funkce vytiskne textový øetìzec na výstup po jednotlivých znacích, které
 * budou pro názornost prolo¾eny pomlèkami.
 *
 * Funkce pøedpokládá, ¾e textový øetìzec je ukonèen znakem s kódem nula.
 * V¹imnìte si, ¾e se øetìzec pøedává jako ukazatel a uvnitø se s ním pracuje
 * jako s polem.
 */
void tiskPoZnacich(char *text)
{
  int i = 0;
  while (text[i] != '\0')
  {
    printf("%c-", text[i]);
    ++i;
  }
  // opravdu je na konci nula? jesli¾e ano, tak ji vytiskneme
  if (text[i] == 0) printf("\\0");
  // Poznámka: Znak s kódem nula zapí¹eme v jazyce C pomocí znakové
  // konstanty '\0', ale po tisku na obrazovku bychom nic nevidìli, proto¾e
  // tento znak není tisknutelný. Textový øetìzec obsahující opaèné lomítko
  // a znak '0' zde tiskneme jen pro názornost. Funkce ze systémové knihovny
  // ukonèovací znak s kódem nula nikdy netisknou. Tento speciální znak slou¾í
  // pouze jako zará¾ka, aby nebylo potøeba nikam ukládat délku øetìzcù.
}

/**
 * Typ char lze vnímat i jako celoèíselný typ. Ka¾dému znaku odpovídá èíslo,
 * neboli kód v ASCII tabulce. V jazyce C není potøeba pracnì pøevádìt znaky
 * na kódy a opaènì, proto¾e jde o tuté¾ hodnotu.
 *
 * Tato funkce vytiskne textový øetìzec jako pole èíselných kódù, ukonèené
 * prvkem s kódem nula.
 */
void tiskKodu(char *text)
{
  int i = 0;
  while (text[i] != 0)
  {
    printf("%d-", text[i]); // nyní tiskneme dekadické èíslo
    ++i;
  }
  // opravdu je na konci nula? jesli¾e ano, tak ji vytiskneme
  if (text[i] == 0) printf("%d", text[i]);
}

/**
 * Funkce pro demonstraci rùzných zpùsobù práce s textovými øetìzci.
 *
 * V jazyce C je textový øetìzec pole znakù libovolné délky, který je v¾dy
 * ukonèen znakem s kódem nula, který slou¾í jako zará¾ka. Podle tohoto znaku
 * se pozná, jak je øetìzec dlouhý, resp. kde konèí. To umo¾òuje pracovat
 * s øetìzci libovolné délky (napø. v Pascal si øetìzec svou délku pamatuje,
 * ale mù¾e pak být dlouhý pouze 255 znakù).
 */
void textoveRetezce(void)
{
  // neinicializovaný ukazatel na char
  // je¹tì to není pou¾itelné jako textový øetìzec
  // obsahuje nespecifikovanou náhodnou adresu!
  char *text1;

  // pøiøazení textové konstanty
  text1 = "Jedna, dve";
  printf("text1 = %s\n", text1);

  // inicializace textovou konstantou
  char *text2 = "Surio Mario Martinez Juarez jde";
  printf("text2 = %s\n", text2);

  // podívejme se na obsah øetìzce blí¾e
  printf("text2 po znacich: ");
  tiskPoZnacich(text2);
  printf("\ntext2 jako pole kodu:");
  tiskKodu(text2);
  printf("\n");

  // textový øetìzec není nic jiného, ne¾ pole znakù, které má jako poslední
  // prvek znak s kódem nula
  // díky pøíbuznosti polí a ukazatelù budou funkce, které oèekávají jako
  // parametr textový øetìzec (ukazatel na char) fungovat i s polem charù
  char text3[] = { 'n', 'e', 's', 'e', ' ', 'p', 'y', 't', 'e', 'l', ' ',
                   's', ' ', 'B', 'r', 'o', 'u', 'k', 'y', '\0', };
  printf("text3 = %s\n", text3);
  printf("text3 po znacich: ");
  tiskPoZnacich(text3);
  printf("\ntext3 jako pole kodu:");
  tiskKodu(text3);
  printf("\n");

  // Místo nepohodlného inicializátoru pole lze v tomto pøípadì pou¾ít
  // inicializaci textovým øetìzcem.
  // Dojde k vytvoøení nového pole a zkopírování znakù na svá místa.
  // V¹imnìte si, ¾e není potøeba vyplòovat dimenzi pole, ani koncovou nulu.
  // Pokud bychom ji vyplnili, musí být konstantní øetìzec men¹í, ne¾ tento
  // rozmìr, aby se do pole ve¹el. Pokud je krat¹í, doplní se zbytek pole
  // nulami.
  char text4[] = "nese pytel s Brouky";
  printf("text4 = %s\n", text4);
  printf("text4 po znacich: ");
  tiskPoZnacich(text4);
  printf("\ntext4 jako pole kodu:");
  tiskKodu(text4);
  printf("\n");

  // mezi ukazatelem na char a polem jsou ov¹em rozdíly
  // 1. ukazatel lze kopírovat, ale nekopíruje se øetìzec, pouze ukazatel na nìj
  //    pùvodní øetìzec zùstává na svém místì
  char text5[] = "IIIIIII";
  char *text6 = text5;
  printf("\nkopie ukazatele\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  // 2. pole nelze kopírovat
  // zkuste to odkomentovat, ulo¾it a pøelo¾it
  // text5 = text6;    // tohle nejde, pøekladaè ohlásí chybu pøi pøekladu

  // 3. v poli lze mìnit prvky podle libosti
  text5[3] = 'X'; // zmìna se projeví i v text6, proto¾e ukazuje na text5
  printf("zmena prvku pole\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  // 4. pokud ukazatel ukazuje na pole, lze pøes nìj mìnit prvky
  text6[2] = 'x'; text6[4] = 'x';
  printf("zmena prvku pole pres ukazatel\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  //5. pokud ukazatel ukazuje na konstantní textový øetìzec, prvky mìnit NEJDOU
  text6 = "OOOOOOO";
  // zkuste to odkomentovat, ulo¾it, pøelo¾it a spustit
  //text6[3] = 'I'; // tohle jde pøelo¾it, ale program by tady HAVAROVAL
  printf("ukazatel na konstantni retezec\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

}

//== konec == textové øetìzce ==

//== zaèátek == cykly ==

/**
 * Funkce pro výpoèet délky textového øetìzce.
 *
 * Demonstrace cyklu while. Pokud vyhodnotí podmínku jako pravdivou, vykoná
 * dal¹í iteraci cyklu. Bìhem výpoètu se mohou promìnné testované v podmínce
 * libovolnì modifikovat. Proto¾e vyhodnocuje podmínku pøed vlastní iterací,
 * nemusí tìlo cyklu probìhnout ani jednou.
 *
 * TIP V¹imnìte si, ¾e tato funkce se bez zvlá¹tního o¹etøování správnì vyrovná
 * i s prázdným øetìzcem (tedy takovým, který obsahuje pouze ukonèovací nulu).
 */
int stringLength(char *text)
{
  int length = 0;
  while (text[length] != '\0')  // dokud nejsme na konci øetìzce, ...
  {
    ++length;    // ... pøièítej jednièku
  }
  return length;
}

/**
 * Vytiskne zadaný textový øetìzec po znacích na standardní výstup a odøádkuje.
 *
 * Dal¹í demonstrace pou¾ití cyklu while pro prùchod textovým øetìzcem.
 */
void printStringWhile1(char *text)
{
  int index = 0;  // definice a inicializace indexu pro pohyb poli
  while (text[index] != '\0') // ukonèovací podmínka vyu¾ívá toho, ¾e
  {                           // øetìzec je ukonèen znakem s kódem 0
    putchar(text[index]);  // funkce putchar vytiskne právì jeden znak
    ++index;               // zvý¹í index
  }
  putchar('\n'); // odøádkování
}

/**
 * Funguje stejnì jako printStringWhile1.
 *
 * Demonstrace jiného zpùsobu procházení textovým øetìzcem.
 * TIP: Tento algoritmus mù¾ete brát jako vzor.
 * TIP: Pokud tomuto algoritmu zatím nejste schopni porozumìt, nevadí.
 *      Pøeskoète jej a vra»te se k nìmu pozdìji.
 */
void printStringWhile2(char *text)
{
  int index = 0;
  int znak = 0;  // pozor! opravdu je zde int, nikoli char
  // (znak = text[index++])
  // - pøiøadí promìnné znak z pole text na indexu index a poté zvý¹í hodnotu
  //   promìnné index o jednièku -- podívejte se do uèebnice jazyka C na
  //   vysvìtlení operátoru ++
  // - celý pøiøazovací výraz musí být v závorce, proto¾e jeho výsledek
  //   následnì porovnáváme se znakem '\0'
  while ((znak = text[index++]) != '\0')
  {
    putchar(znak); // vytiskne jeden znak na standardní výstup
  }
  putchar('\n'); // odøádkování
}

/**
 * Funguje stejnì jako printStringWhile1.
 *
 * Pro pochopení tohoto kódu je nutná znalost práce s ukazateli a znalost
 * vztahu mezi ukazatelem, polem a operátorem ++.
 * POZOR! Nepou¾ívejte kód, o kterém si nejste jisti, jak funguje. Pøedchozí
 *        ukázky jsou dùkazem, ¾e stejnou vìc lze naprogramovat více zpùsoby.
 *        Tento zpùsob je sice o trochu efektivnìj¹í, ne¾ ty pøedchozí, ale
 *        zase je mnohem hùøe pochopitelný. Pokud nìco takového pou¾ijete
 *        v projektu do nìjakého kurzu programování, je témìø jisté, ¾e
 *        cvièící bude pøi obhajobì chtít, a» podrobnì vysvìtlíte, jak to
 *        funguje.
 */
void printStringWhile3(char *text)
{
  while(*text != 0)
  {
    putchar(*text++);
  }
  putchar('\n'); // odøádkování
}

/**
 * Funguje stejnì jako printStringWhile1.
 *
 * Tato funkce pouze demonstruje, ¾e v jazyce C jsou v¹echny tyty cyklù
 * vzájemnì pøevoditelné. Cyklus typu do-while se pøíli¹ nehodí pro práci
 * s poli a textovými øetìzci, proto¾e jeho tìlo v¾dy probìhne alespoò
 * jednou. Abychom o¹etøili situaci, kdy je potøeba zpracovat prázdný øetìzec,
 * musíme si pomoci dodateènou podmínkou if.
 * Podmínka cyklu se vyhodnotí po provedení jedné iterace. Cyklus provede dal¹í
 * iteraci, pokud je podmínka pravdivá.
 *
 * TIP: V¹imnìte si formátování pøíkazu do-while v této ukázce. Toto formátování
 *      minimalizuje mo¾nost zámìny s cyklem while s prázdným tìlem.
 */
void printStringDoWhile(char *text)
{
  int index = 0;
  int znak = text[index];
  if (znak != '\0')
  {
    do { // Pozor na poøadí jednotlivých pøíkazù. Prohodíme-li následující tøi
         // øádky, bude to fungovat chybnì.
      putchar(znak);
      ++index;
      znak = text[index];
    } while (znak != '\0'); // POZOR! Zde musí být støedník
  }
  putchar('\n'); // odøádkování
}

/**
 * Funguje stejnì jako printStringWhile1.
 *
 * Demonstrace pou¾ití cyklu for. Cyklus for je v jazyce C velmi univerzální
 * (v jazyce C lze v¹echny typy cyklù vzájemnì pøevést). Cyklus má v kulatých
 * závorkách tøi výrazy oddìlené pomocí støedníkù. Pro správnou èinnost je
 * nutné pochopit, v jakém poøadí se tyto výrazy vyhodnocují. Pro pochopení
 * pomù¾e toto schéma: for (inicializace; podmínka; modifikace) { tìlo }
 * Postup výpoètu je nyní takový:
 * 1. inicializace provede se PRÁVÌ JEDNOU
 * 2. vyhodnocení podmínky, pokud je pravdivá, provede tìlo, jinak cyklus konèí
 * 3. provede se tìlo
 * 4. vykoná se èást modifikace, kde se obvykle modifikuje øídící promìnná
 *    cyklu, poté se pøejde opìt na vyhodnocení podmínky
 * Kterákoli z tìchto ètyø èástí mù¾e zùstat prázdná
 */
void printStringFor(char *text)
{
  for (int index; text[index] != '\0'; ++index)
  {
    putchar(text[index]);
  }
  putchar('\n'); // odøádkování
}

/**
 * Funguje stejnì jako printStringFor.
 *
 * Naivní a nevhodná implementace vyu¾ívající funkci strlen pro zji¹tìní
 * délky øetìzce. Nevhodná je proto, ¾e výpoèet délky øetìzce vy¾aduje
 * prùchod celým øetìzcem, a kdy¾ se toto dìje v cyklu, místo N iterací
 * se provede NxN iterací (kde N je délka øetìzce). V tomto pøípadì by bylo
 * lep¹í ulo¾it výsledek funkce strlen do pomocné promìnné a tu pak pou¾ívat.
 * Je¹tì lep¹í øe¹ení je demonstrováno ve funkci printStringFor - pro prùchod
 * øetìzcem vùbec nepotøebujeme znát jeho délku.
 *
 * TIP: Pøi pou¾ití funkcí uvnitø cyklu se v¾dy zamyslete nad tím, jak tyto
 *      funkce fungují a jestli tu akci nestaèí udìlat pouze jednou.
 */
void printStringForNaive(char *text)
{
  for (unsigned int index = 0; index < strlen(text); ++index)
  {
    putchar(text[index]);
  }
  putchar('\n'); // odøádkování
}

/**
 * Otoèí poøadí znakù v textovém øetìzci. Postupnì prohazuje první znak
 * s posledním, druhý s pøedposledním, atd.
 *
 * V cyklu for (ostatnì jako i v ostatních cyklech) se mù¾e vyskytovat více
 * øídících promìnných.
 */
void otocRetezec(char *text)
{
  // v inicializaèní èásti lze definovat a inicializovat i nìkolik lokálních
  // promìnných, zde left a right jsou indexy do textového øetìzce
  // v èásti modifikace lze modifikovat i více promìnných, jednotlivé
  // výrazy v této èásti jsou oddìleny èárkou (operátor èárka, viz uèebnice)
  for (int left = 0, right = strlen(text) - 1; left < right ; ++left, --right)
  { // v tìle provede zámìnu dvou znakù v øetìzci
    char tmp = text[left];
    text[left] = text[right];
    text[right] = tmp;
  }
}

/**
 * Funkce pro demonstraci rùzných typù cyklù v jazyce C.
 */
void cykly(void)
{
  printf("*** cyklus while ***\n");
  char *veta = "Ententyky, dve hmozdinky, mlady muz sel z metra.";
  printf("veta = %s\n", veta);
  printf("printStringWhile1: ");
  printStringWhile1(veta);
  printf("printStringWhile2: ");
  printStringWhile2(veta);
  printf("printStringWhile3: ");
  printStringWhile3(veta);

  printf("*** cyklus do-while ***\n");
  printf("printStringDoWhile: ");
  printStringDoWhile(veta);

  printf("*** cyklus for ***\n");
  printf("printStringFor: ");
  printStringFor(veta);
  printf("printStringForNaive: ");
  printStringForNaive(veta);

  char palindrom[] = "kobyla ma maly bok";
  printf("palindrom = %s\n", palindrom);
  otocRetezec(palindrom);
  printf("otocRetezec(palindrom): %s\n", palindrom);
}

//== konec == cykly ==


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
  printf("=== funkce tiskPoleMocnin ===\n");
  tiskPoleMocnin();

  printf("=== funkce tiskniLany ===\n");
  tiskniLany();

  printf("=== funkce dvojrozmernaPole ===\n");
  dvojrozmernaPole();

  printf("=== funkce textoveRetezce ===\n");
  textoveRetezce();

  printf("=== funkce cykly ===\n");
  cykly();

  return EXIT_SUCCESS;  // program konèí bez chyby
}
