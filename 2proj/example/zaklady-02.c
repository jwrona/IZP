/*
  Projekt: Jak na projekty v jazyce C

  Z�kladn� konstrukce jazyka C
  Lekce 2 - pole, textov� �et�zce, cykly

  Autor: David Martinek, martinek (zavin��) fit.vutbr.cz
  Datum: 06.03.2009
  K�dov�n� dokumentu: ISO8859-2
  Popis: Tento program slou�� pro demonstraci z�kladn�ch stavebn�ch prvk�
         jazyka C.
  Webov� adresa: http://www.fit.vutbr.cz/~martinek/clang/
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///////// Definice konstant ///////////////////////////////////////////////////
// symbolick� konstanta N obsahuj�c� hodnotu 5, budeme ji pou��vat pro
// specifikaci rozm�r� pol�
// TIP: v�imn�te si, �e zde nen� nikde st�edn�k ani rovn�tko
// TIP: pod�vejte se na tuto konstrukci do n�jak� u�ebnice jazyka C
#define N 5

// symbolick� konstanta obsahuj�c� hodnotu 7
#define M 7

///////// Definice podprogram� ////////////////////////////////////////////////

//== za��tek == pole - inicializace a tisk na obrazovku ==
/**
 * Funkce, kter� vyrob� jednorozm�rn� pole, napln� jej hodnotami a vytiskne
 * jeho obsah na obrazovku.
 */
void tiskPoleMocnin(void)
{
  int pole[N]; // deklarace + definice lok�ln� prom�nn� - pole o p�ti prvc�ch
               // ka�d� prvek tohoto pole je prom�nn� typu int

  // cyklus pro napln�n� pole hodnotami
  // i - index pole, v tomto p��pad� bude postupn� nab�vat hodnot 0, 1, 2, 3 a 4
  // POZOR: v jazyce C se pole indexuj� od nuly a NIKDY jinak
  for (int i = 0; i < N; ++i)
  {
    pole[i] = i*i; // do ka�d�ho prvku vlo��me druhou mocninu indexu
  }

  // tisk pole na standardn� v�stup
  // nelze tisknout cel� pole najdenou, mus�me tisknout po jednotliv�ch prvc�ch
  for (int i = 0; i < N; ++i)
  {
    printf("pole[%d] = %d\n", i, pole[i]);
  }
}

/**
 * Abychom nemuseli ka�d� pole tisknout ru�n�, vyrob�me si funkci, kter� um�
 * vytisknout pole zadan� jako parametr. Proto�e si datov� typ pole neum�
 * zapamatovat svou d�lku, mus�me d�lku pole dodat jako druh� parametr.
 *
 * pole - jednorozm�rn� pole s prvky typu int, v�imn�te si, �e hranat�
 *        z�vorky jsou pr�zdn�, rozm�r dod�me dal��m parametrem
 * delka - d�lka pole, tedy po�et jeho prvk�
 *
 * TIP: V�imn�te si, v jak�m form�tu funce vytiskne pole na v�stup. Stejnou
 * formu z�pisu lze pou��t i v jazyce C pro inicializaci pole p�i definici
 * prom�nn�.
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
// Pozn�mka: pole se v jazyce C p�ed�v� v�dy jako ukazatel na jeho za��tek.
// V jazyce C nelze p�edat pole hodnotou. To znamen�, �e v�dy kdy� modifikujeme
// n�jak� prvek pole p�edan�ho jako parametr, z�stane tato zm�na v poli
// zachov�na i po skon�en� t�to funkce.

// Pozn�mka: Proto�e pracujeme s jednorozm�rn�m polem a pro jazyk C jsou pole
// a ukazatele velmi p��buzn� datov� typy (viz u�ebnice jazyka C), mohla by
// hlavi�ka p�edchoz� funkce vypadat i takto, ani� by se jakkoli zm�nil jej�
// v�znam:
// void tiskPole(int *pole, int delka)

/**
 * Demonstrace r�zn�ch zp�sob� vytv��en� a inicializac� jednorozm�rn�ch pol�.
 * Nyn� pro tisk pou�ijeme funkci tiskPole.
 *
 * V�imn�te si, �e se pole p�ed�v� zd�nliv� hodnotou, a�koliv p�edchoz� pozn�mky
 * ��kaj�, �e se pole p�ed�v� jako ukazatel. Je to tak proto, �e vlastn�
 * p�ed�v�me hodnotou ukazatel na za��tek pole - tento ukazatel nechceme m�nit,
 * p��padn� zm�ny by se t�kaly prvk� pole, nikoli ukazatele na jeho za��tek.
 * Bl�e viz u�ebnice jazyka C.
 */
void tiskniLany(void)
{
  // neinicializovan� pole d�lky N
  // prvky nyn� mohou m�t libovolnou hodnotu
  // i kdy� �asto bude jejich hodnota nula, nelze se na to spol�hat!
  int pole1[N];
  printf("Neinicializovan� pole: ");
  tiskPole(pole1, N);

  // inicializace pomoc� inicializ�toru pole
  // Po�et prvk� nyn� nen� pot�eba zad�vat, proto�e se dopo��t�
  // z inicializ�toru.
  int pole2[] = {2, 4, 6, 8};
  printf("Inicializ�tor 1: ");
  tiskPole(pole2, 4);

  // pokud zad�me rozm�r a inicializujeme jenom n�kter� prvky, ostatn� prvky
  // budou m�t automaticky hodnotu nula
  // POZOR! Tohle plat� jen p�i pou�it� inicializ�toru, bez n�j jsou v�echny
  // prvky neinicializovan� a maj� tud� nezaru�itelnou hodnotu!
  int pole3[7] = {1, 4, 9};
  printf("Inicializ�tor 2: ");
  tiskPole(pole3, 7);

  // v inicializ�toru lze pou��t i index, hod� se to zejm�na u dlouh�ch
  // pol�, v nich� chceme inicializovat jen vybran� hodnoty
  // v�imn�te si, na jak�ch pozic�ch jsou prvky bez uveden�ho indexu
  // nevyjmenovan� prvky jsou zde inicializov�ny na nulu
  // Pozn�mka: tohle ve star��ch verz�ch jazyka C d�lat nejde
  int pole4[7] = {1, 4, [3]=16, 25};
  printf("Inicializ�tor 2: ");
  tiskPole(pole4, 7);

  // dal�� mo�nost� je inicializovat pole pomoc� cyklu, jak bylo demonstrov�no
  // ve funkci tiskPoleMocnin
}

/**
 * Funkce pro tisk dvojrozm�rn�ch pol�.
 *
 * Matice nebo 2D pole je vlastn� polem jednorozm�rn�ch pol�. Ze stejn�ho
 * d�vodu, jako u jednorozm�rn�ch pol� lze zde nechat prvn� hranat� z�vorky,
 * tedy po�et ��dk� pole, pr�zdn�. Po�et ��dk� je nutn� p�edat jako dal��
 * parametr. Dal�� dimenzi je ov�em naopak NUTN� uv�st, aby p�eklada� v�d�l,
 * jak dlouh� jsou ��dky, z jeho pohledu tedy prvky jednoprvkov�ho pole.
 *
 * TIP: V�imn�te si, v jak�m form�tu funkce tiskne matici na v�stup.
 * Stejnou formu z�pisu lze pou��t i v jazyce C pro inicializace v�cerozm�rn�ch
 * pol� p�i definic�ch prom�nn�ch. V podstat� jde o slo�en� inicializ�tor
 * jednorozm�rn�ho pole.
 *
 * POZOR! Tato funkce je pouze uk�zkov�. V praxi je tento zp�sob pr�ce s matic�
 * z n�kolika d�vod� krajn� NEVHODN� a t�kop�dn�. Mnohem vhodn�j�� je pou��vat
 * dynamicky alokovan� pole zabalen� spolu s rozm�ry ve struktu�e. Bl�e viz
 * u�ebnice jazyka C.
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
 * Demonstrace vytv��en� a inicializac� dvojrozm�rn�ch pol�, tedy matic.
 * Matice je v jazyce C ch�p�na jako pole jednorozm�rn�ch pol�, neboli pole
 * ��dk�. Prvn� rozm�r obvykle ud�v� po�et ��dk�, druh� rozm�r po�et sloupc�
 * (tedy d�lku ��dk�).
 */
void dvojrozmernaPole(void)
{
  // neinicializovan� dvojrozm�rn� pole o M ��dc�ch a N sloupc�ch
  int matice1[M][N];
  tiskMatice(matice1, M);

  // pou�it� inici�liz�tor� pro dvojrozm�rn� pole MxN (tedy 7x5)
  // v�imn�te si r�zn�ch zp�sob� inicializace v jednotliv�ch ��dc�ch
  int matice2[M][N] = {
    { 0, 1, 2, 3, 4 },
    { 0 },
    { [3]=1 },
    { 1, [3]=1, 7 },
    { 5 },
    // posledn� dva vynech�m �pln�, proto�e je to uvnit� inicializ�toru
    // budou napln�ny nulami
  };
  tiskMatice(matice2, M);
}

/////////////////////////////////////////////////////////////////////////////
// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //// POZOR //
/////////////////////////////////////////////////////////////////////////////
// Pole vytv��en� v p�edchoz�ch uk�zk�ch NELZE pou��vat jako n�vratov� hodnoty
// funkc�. Nelze ani vytvo�it funkci, kter� by m�la jako n�vratov� typ tento
// druh pol�. Pro tyto ��ely se v jazyce C pou��vaj� dynamicky alokovan� pole
// a ukazatele.
/////////////////////////////////////////////////////////////////////////////
// Tato pole rovn� NELZE kop�rovat pomoc� p�i�azovac�ho oper�toru. Nelze
// ud�lat toto: pole1 = pole2. Tuto konstrukci p�eklada� odm�tne. Kop�rov�n�
// pol� je nutn� d�lat po prvc�ch pomoc� p��kaz� pro cykly. D�vodem pro toto
// omezen� je to, �e si jazyk C nepamatuje d�lku pol� (zejm�na u v�cerozm�rn�ch
// pol� by to bylo implementa�n� problematick�). Je bezpe�n�j�� nechat tuto
// �innost na program�torovi, kter� v�, kam a� v poli m��e j�t a z�rove� ho to
// nut� si uv�domit, �e operace kop�rov�n� pol� nen� zadarmo.
/////////////////////////////////////////////////////////////////////////////

//== konec == lok�ln� pole - inicializace a tisk na obrazovku ==

//== za��tek == textov� �et�zce ==
/**
 * Funkce vytiskne textov� �et�zec na v�stup po jednotliv�ch znac�ch, kter�
 * budou pro n�zornost prolo�eny poml�kami.
 *
 * Funkce p�edpokl�d�, �e textov� �et�zec je ukon�en znakem s k�dem nula.
 * V�imn�te si, �e se �et�zec p�ed�v� jako ukazatel a uvnit� se s n�m pracuje
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
  // opravdu je na konci nula? jesli�e ano, tak ji vytiskneme
  if (text[i] == 0) printf("\\0");
  // Pozn�mka: Znak s k�dem nula zap�eme v jazyce C pomoc� znakov�
  // konstanty '\0', ale po tisku na obrazovku bychom nic nevid�li, proto�e
  // tento znak nen� tisknuteln�. Textov� �et�zec obsahuj�c� opa�n� lom�tko
  // a znak '0' zde tiskneme jen pro n�zornost. Funkce ze syst�mov� knihovny
  // ukon�ovac� znak s k�dem nula nikdy netisknou. Tento speci�ln� znak slou��
  // pouze jako zar�ka, aby nebylo pot�eba nikam ukl�dat d�lku �et�zc�.
}

/**
 * Typ char lze vn�mat i jako celo��seln� typ. Ka�d�mu znaku odpov�d� ��slo,
 * neboli k�d v ASCII tabulce. V jazyce C nen� pot�eba pracn� p�ev�d�t znaky
 * na k�dy a opa�n�, proto�e jde o tut� hodnotu.
 *
 * Tato funkce vytiskne textov� �et�zec jako pole ��seln�ch k�d�, ukon�en�
 * prvkem s k�dem nula.
 */
void tiskKodu(char *text)
{
  int i = 0;
  while (text[i] != 0)
  {
    printf("%d-", text[i]); // nyn� tiskneme dekadick� ��slo
    ++i;
  }
  // opravdu je na konci nula? jesli�e ano, tak ji vytiskneme
  if (text[i] == 0) printf("%d", text[i]);
}

/**
 * Funkce pro demonstraci r�zn�ch zp�sob� pr�ce s textov�mi �et�zci.
 *
 * V jazyce C je textov� �et�zec pole znak� libovoln� d�lky, kter� je v�dy
 * ukon�en znakem s k�dem nula, kter� slou�� jako zar�ka. Podle tohoto znaku
 * se pozn�, jak je �et�zec dlouh�, resp. kde kon��. To umo��uje pracovat
 * s �et�zci libovoln� d�lky (nap�. v Pascal si �et�zec svou d�lku pamatuje,
 * ale m��e pak b�t dlouh� pouze 255 znak�).
 */
void textoveRetezce(void)
{
  // neinicializovan� ukazatel na char
  // je�t� to nen� pou�iteln� jako textov� �et�zec
  // obsahuje nespecifikovanou n�hodnou adresu!
  char *text1;

  // p�i�azen� textov� konstanty
  text1 = "Jedna, dve";
  printf("text1 = %s\n", text1);

  // inicializace textovou konstantou
  char *text2 = "Surio Mario Martinez Juarez jde";
  printf("text2 = %s\n", text2);

  // pod�vejme se na obsah �et�zce bl�e
  printf("text2 po znacich: ");
  tiskPoZnacich(text2);
  printf("\ntext2 jako pole kodu:");
  tiskKodu(text2);
  printf("\n");

  // textov� �et�zec nen� nic jin�ho, ne� pole znak�, kter� m� jako posledn�
  // prvek znak s k�dem nula
  // d�ky p��buznosti pol� a ukazatel� budou funkce, kter� o�ek�vaj� jako
  // parametr textov� �et�zec (ukazatel na char) fungovat i s polem char�
  char text3[] = { 'n', 'e', 's', 'e', ' ', 'p', 'y', 't', 'e', 'l', ' ',
                   's', ' ', 'B', 'r', 'o', 'u', 'k', 'y', '\0', };
  printf("text3 = %s\n", text3);
  printf("text3 po znacich: ");
  tiskPoZnacich(text3);
  printf("\ntext3 jako pole kodu:");
  tiskKodu(text3);
  printf("\n");

  // M�sto nepohodln�ho inicializ�toru pole lze v tomto p��pad� pou��t
  // inicializaci textov�m �et�zcem.
  // Dojde k vytvo�en� nov�ho pole a zkop�rov�n� znak� na sv� m�sta.
  // V�imn�te si, �e nen� pot�eba vypl�ovat dimenzi pole, ani koncovou nulu.
  // Pokud bychom ji vyplnili, mus� b�t konstantn� �et�zec men��, ne� tento
  // rozm�r, aby se do pole ve�el. Pokud je krat��, dopln� se zbytek pole
  // nulami.
  char text4[] = "nese pytel s Brouky";
  printf("text4 = %s\n", text4);
  printf("text4 po znacich: ");
  tiskPoZnacich(text4);
  printf("\ntext4 jako pole kodu:");
  tiskKodu(text4);
  printf("\n");

  // mezi ukazatelem na char a polem jsou ov�em rozd�ly
  // 1. ukazatel lze kop�rovat, ale nekop�ruje se �et�zec, pouze ukazatel na n�j
  //    p�vodn� �et�zec z�st�v� na sv�m m�st�
  char text5[] = "IIIIIII";
  char *text6 = text5;
  printf("\nkopie ukazatele\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  // 2. pole nelze kop�rovat
  // zkuste to odkomentovat, ulo�it a p�elo�it
  // text5 = text6;    // tohle nejde, p�eklada� ohl�s� chybu p�i p�ekladu

  // 3. v poli lze m�nit prvky podle libosti
  text5[3] = 'X'; // zm�na se projev� i v text6, proto�e ukazuje na text5
  printf("zmena prvku pole\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  // 4. pokud ukazatel ukazuje na pole, lze p�es n�j m�nit prvky
  text6[2] = 'x'; text6[4] = 'x';
  printf("zmena prvku pole pres ukazatel\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

  //5. pokud ukazatel ukazuje na konstantn� textov� �et�zec, prvky m�nit NEJDOU
  text6 = "OOOOOOO";
  // zkuste to odkomentovat, ulo�it, p�elo�it a spustit
  //text6[3] = 'I'; // tohle jde p�elo�it, ale program by tady HAVAROVAL
  printf("ukazatel na konstantni retezec\n");
  printf("text5 = %s\n", text5);
  printf("text6 = %s\n", text6);

}

//== konec == textov� �et�zce ==

//== za��tek == cykly ==

/**
 * Funkce pro v�po�et d�lky textov�ho �et�zce.
 *
 * Demonstrace cyklu while. Pokud vyhodnot� podm�nku jako pravdivou, vykon�
 * dal�� iteraci cyklu. B�hem v�po�tu se mohou prom�nn� testovan� v podm�nce
 * libovoln� modifikovat. Proto�e vyhodnocuje podm�nku p�ed vlastn� iterac�,
 * nemus� t�lo cyklu prob�hnout ani jednou.
 *
 * TIP V�imn�te si, �e tato funkce se bez zvl�tn�ho o�et�ov�n� spr�vn� vyrovn�
 * i s pr�zdn�m �et�zcem (tedy takov�m, kter� obsahuje pouze ukon�ovac� nulu).
 */
int stringLength(char *text)
{
  int length = 0;
  while (text[length] != '\0')  // dokud nejsme na konci �et�zce, ...
  {
    ++length;    // ... p�i��tej jedni�ku
  }
  return length;
}

/**
 * Vytiskne zadan� textov� �et�zec po znac�ch na standardn� v�stup a od��dkuje.
 *
 * Dal�� demonstrace pou�it� cyklu while pro pr�chod textov�m �et�zcem.
 */
void printStringWhile1(char *text)
{
  int index = 0;  // definice a inicializace indexu pro pohyb poli
  while (text[index] != '\0') // ukon�ovac� podm�nka vyu��v� toho, �e
  {                           // �et�zec je ukon�en znakem s k�dem 0
    putchar(text[index]);  // funkce putchar vytiskne pr�v� jeden znak
    ++index;               // zv��� index
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Funguje stejn� jako printStringWhile1.
 *
 * Demonstrace jin�ho zp�sobu proch�zen� textov�m �et�zcem.
 * TIP: Tento algoritmus m��ete br�t jako vzor.
 * TIP: Pokud tomuto algoritmu zat�m nejste schopni porozum�t, nevad�.
 *      P�esko�te jej a vra�te se k n�mu pozd�ji.
 */
void printStringWhile2(char *text)
{
  int index = 0;
  int znak = 0;  // pozor! opravdu je zde int, nikoli char
  // (znak = text[index++])
  // - p�i�ad� prom�nn� znak z pole text na indexu index a pot� zv��� hodnotu
  //   prom�nn� index o jedni�ku -- pod�vejte se do u�ebnice jazyka C na
  //   vysv�tlen� oper�toru ++
  // - cel� p�i�azovac� v�raz mus� b�t v z�vorce, proto�e jeho v�sledek
  //   n�sledn� porovn�v�me se znakem '\0'
  while ((znak = text[index++]) != '\0')
  {
    putchar(znak); // vytiskne jeden znak na standardn� v�stup
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Funguje stejn� jako printStringWhile1.
 *
 * Pro pochopen� tohoto k�du je nutn� znalost pr�ce s ukazateli a znalost
 * vztahu mezi ukazatelem, polem a oper�torem ++.
 * POZOR! Nepou��vejte k�d, o kter�m si nejste jisti, jak funguje. P�edchoz�
 *        uk�zky jsou d�kazem, �e stejnou v�c lze naprogramovat v�ce zp�soby.
 *        Tento zp�sob je sice o trochu efektivn�j��, ne� ty p�edchoz�, ale
 *        zase je mnohem h��e pochopiteln�. Pokud n�co takov�ho pou�ijete
 *        v projektu do n�jak�ho kurzu programov�n�, je t�m�� jist�, �e
 *        cvi��c� bude p�i obhajob� cht�t, a� podrobn� vysv�tl�te, jak to
 *        funguje.
 */
void printStringWhile3(char *text)
{
  while(*text != 0)
  {
    putchar(*text++);
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Funguje stejn� jako printStringWhile1.
 *
 * Tato funkce pouze demonstruje, �e v jazyce C jsou v�echny tyty cykl�
 * vz�jemn� p�evoditeln�. Cyklus typu do-while se p��li� nehod� pro pr�ci
 * s poli a textov�mi �et�zci, proto�e jeho t�lo v�dy prob�hne alespo�
 * jednou. Abychom o�et�ili situaci, kdy je pot�eba zpracovat pr�zdn� �et�zec,
 * mus�me si pomoci dodate�nou podm�nkou if.
 * Podm�nka cyklu se vyhodnot� po proveden� jedn� iterace. Cyklus provede dal��
 * iteraci, pokud je podm�nka pravdiv�.
 *
 * TIP: V�imn�te si form�tov�n� p��kazu do-while v t�to uk�zce. Toto form�tov�n�
 *      minimalizuje mo�nost z�m�ny s cyklem while s pr�zdn�m t�lem.
 */
void printStringDoWhile(char *text)
{
  int index = 0;
  int znak = text[index];
  if (znak != '\0')
  {
    do { // Pozor na po�ad� jednotliv�ch p��kaz�. Prohod�me-li n�sleduj�c� t�i
         // ��dky, bude to fungovat chybn�.
      putchar(znak);
      ++index;
      znak = text[index];
    } while (znak != '\0'); // POZOR! Zde mus� b�t st�edn�k
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Funguje stejn� jako printStringWhile1.
 *
 * Demonstrace pou�it� cyklu for. Cyklus for je v jazyce C velmi univerz�ln�
 * (v jazyce C lze v�echny typy cykl� vz�jemn� p�ev�st). Cyklus m� v kulat�ch
 * z�vork�ch t�i v�razy odd�len� pomoc� st�edn�k�. Pro spr�vnou �innost je
 * nutn� pochopit, v jak�m po�ad� se tyto v�razy vyhodnocuj�. Pro pochopen�
 * pom��e toto sch�ma: for (inicializace; podm�nka; modifikace) { t�lo }
 * Postup v�po�tu je nyn� takov�:
 * 1. inicializace provede se PR�V� JEDNOU
 * 2. vyhodnocen� podm�nky, pokud je pravdiv�, provede t�lo, jinak cyklus kon��
 * 3. provede se t�lo
 * 4. vykon� se ��st modifikace, kde se obvykle modifikuje ��d�c� prom�nn�
 *    cyklu, pot� se p�ejde op�t na vyhodnocen� podm�nky
 * Kter�koli z t�chto �ty� ��st� m��e z�stat pr�zdn�
 */
void printStringFor(char *text)
{
  for (int index; text[index] != '\0'; ++index)
  {
    putchar(text[index]);
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Funguje stejn� jako printStringFor.
 *
 * Naivn� a nevhodn� implementace vyu��vaj�c� funkci strlen pro zji�t�n�
 * d�lky �et�zce. Nevhodn� je proto, �e v�po�et d�lky �et�zce vy�aduje
 * pr�chod cel�m �et�zcem, a kdy� se toto d�je v cyklu, m�sto N iterac�
 * se provede NxN iterac� (kde N je d�lka �et�zce). V tomto p��pad� by bylo
 * lep�� ulo�it v�sledek funkce strlen do pomocn� prom�nn� a tu pak pou��vat.
 * Je�t� lep�� �e�en� je demonstrov�no ve funkci printStringFor - pro pr�chod
 * �et�zcem v�bec nepot�ebujeme zn�t jeho d�lku.
 *
 * TIP: P�i pou�it� funkc� uvnit� cyklu se v�dy zamyslete nad t�m, jak tyto
 *      funkce funguj� a jestli tu akci nesta�� ud�lat pouze jednou.
 */
void printStringForNaive(char *text)
{
  for (unsigned int index = 0; index < strlen(text); ++index)
  {
    putchar(text[index]);
  }
  putchar('\n'); // od��dkov�n�
}

/**
 * Oto�� po�ad� znak� v textov�m �et�zci. Postupn� prohazuje prvn� znak
 * s posledn�m, druh� s p�edposledn�m, atd.
 *
 * V cyklu for (ostatn� jako i v ostatn�ch cyklech) se m��e vyskytovat v�ce
 * ��d�c�ch prom�nn�ch.
 */
void otocRetezec(char *text)
{
  // v inicializa�n� ��sti lze definovat a inicializovat i n�kolik lok�ln�ch
  // prom�nn�ch, zde left a right jsou indexy do textov�ho �et�zce
  // v ��sti modifikace lze modifikovat i v�ce prom�nn�ch, jednotliv�
  // v�razy v t�to ��sti jsou odd�leny ��rkou (oper�tor ��rka, viz u�ebnice)
  for (int left = 0, right = strlen(text) - 1; left < right ; ++left, --right)
  { // v t�le provede z�m�nu dvou znak� v �et�zci
    char tmp = text[left];
    text[left] = text[right];
    text[right] = tmp;
  }
}

/**
 * Funkce pro demonstraci r�zn�ch typ� cykl� v jazyce C.
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

  return EXIT_SUCCESS;  // program kon�� bez chyby
}
