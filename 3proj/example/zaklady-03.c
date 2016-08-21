/*
  Projekt: Jak na projekty v jazyce C

  Z�kladn� konstrukce jazyka C
  Lekce 3 - ukazatele

  Autor: David Martinek, martinek (zavin��) fit.vutbr.cz
  Datum: 12.03.2009
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

///////// Definice konstant ///////////////////////////////////////////////////
// symbolick� konstanta
#define DELKA 10

///////// Definice podprogram� ////////////////////////////////////////////////

//== za��tek = ukazatele na lok�ln� prom�nn� ==
/**
 * Funkce pro demonstraci pr�ce s ukazateli na jednoduch� datov� typy.
 *
 * Ukazatel je speci�ln� ��seln� datov� typ. Prom�nn� typu ukazatel obsahuj�
 * cel� ��slo, kter� je interpretov�no jako adresa ur�it� pam�ov� bu�ky.
 * Obvykle pracujeme s tzv. typov�mi ukazateli, tedy ukazateli na int, double,
 * char, atd. Takov�mu c�lov�mu typu se ��k� b�zov� typ ukazatele a slou��
 * k tomu, abychom v�d�li, na jak velkou ��st pam�ti od dan� adresy se m�me
 * pod�vat. Nap�. typ int * je ukazatel na �ty�bajtov� int, tedy adresa ukazuje
 * na konkr�tn� m�sto v pam�ti (bu�ku o velikosti 1 bajt) a p�eklada� v�, �e
 * m��e pracovat s n�sleduj�c�mi �ty�mi bajty.
 */
void simplePointers(void)
{
  int promenna = 1234; // prom�nn� typu int obsahuj�c� hodnotu 1234
  // definice lok�ln� prom�nn� typu ukazatel na int
  // nyn� obsahuje n�hodnou adresu, nelze ji tedy rozumn� pou��t
  int *ukazatel;

  // nyn� zkop�rujeme do prom�nn� ukazatel adresu prom�nn� promenna
  // & je tzv. referen�n� oper�tor - vrac� adresu sv�ho argumentu
  ukazatel = &promenna;

  // nyn� vytvo��me druhou prom�nnou typu ukazatel na int
  // a zkop�rujeme do n� obsah prom�nn� ukazatel
  // druhyUk nyn� obsahuje rovn� adresu prom�nn� promenna
  // ��k�me, �e ukazuje na prom�nnou promenna
  int *druhyUk = ukazatel;

  // ukazatele, tedy adresy lze porovn�vat
  if (ukazatel == druhyUk)
  {
    printf("Oba ukazatele ukazuj� na stejn� m�sto v pam�ti.\n");
  }

  // Pomoc� oper�toru * se um�me pod�vat na m�sto, na kter� ukazatel ukazuje.
  // * je tzv. dereferen�n� oper�tor - vrac� hodnotu, na kterou ukazatel ukazuje
  // Datov� typ v�sledku je ur�en b�zov�m typem ukazatele, tak�e pokud ukazatel
  // ukazuje na int, je v�sledek oper�toru * tak� typu int.
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // Obsah prom�nn� promenna lze nyn� modifikovat t�emi zp�soby.
  // 1. p��mou zm�nou  prom�nn� promenna
  promenna = 987;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // 2. p�es prom�nnou ukazatel pomoc� dereferen�n�ho oper�toru
  *ukazatel = 654;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);

  // 3. p�es prom�nnou druhyUk op�t pomoc� dereferen�n�ho oper�toru
  *druhyUk = 357;
  printf("promenna = %d, *ukazatel = %d, *druhyUk = %d\n",
    promenna, *ukazatel, *druhyUk);


  // Ukazatele na r�zn� b�zov� typy jsou vz�jemn� kompatibiln� jenom tak, jak
  // jsou vz�jemn� kompatibiln� tyto b�zov� typy.
  // V tomto p��pad� by p�eklada� vypsal varov�n�:
  // warning: initialization from incompatible pointer type
//  double *ukDouble = ukazatel;
  // Program by se sice nakonec p�elo�il, ale d�le v programu by toto mohlo
  // v�st k z�va�n�m chyb�m.

  // Ukazatele + return
  // POZOR! Funkce mohou vracet ukazatel, ale nikdy se nepokou�ejte vracet
  // ukazatel ukazuj�c� na lok�ln� prom�nnou! Lok�ln� prom�nn� po ukon�en�
  // funkce zanikaj�, proto by v�sledek takov�to funkce nebyl pou�iteln�,
  // resp. jeho pou�it�m bychom zp�sobili chybu b�hu programu.

  // TIP: Pokud n��emu nerozum�te, zeptejte se nebo zkuste naj�t odpov�� ve
  // vhodn� u�ebnici jazyka C.
}

//== konec = ukazatele na lok�ln� prom�nn� ==

//== za��tek = ukazatele a lok�ln� pole ==

/**
 * Pomocn� funkce pro tisk obsahu pole na standardn� v�stup.
 *
 * V�imn�te si, �e parametr pole se p�ed�v� jako ukazatel na b�zov� typ int
 * a d�le se s n�m pracuje jako s polem.
 *
 * D�le si v�imn�te, �e je nutn� p�edat jako dal�� parametr po�et prvk� pole,
 * proto�e datov� typ pole si po�et sv�ch prvk� nepamatuje.
 *
 * TIP: Datov� typ pole v jazyce C si nepamatuje, ani nem��e pamatovat svou
 *      d�lku. Zamyslete se nad t�m, pro� tomu tak je.
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
 * Funkce pro demonstraci vztahu mezi ukazateli a lok�ln�mi poli.
 *
 */
void lokalniPole(void)
{

  // neinicializovan� ukazatel
  int *uk;

  // neinicializovan� jednorozm�rn� pole
  int mocniny[DELKA];

  // pod�v�me se, co pole skute�n� obsahuje
  // v�imn�te si, jak se pole p�ed�v� funkci tiskPole
  tiskPole("mocniny = ", mocniny, DELKA);

  // inicializace pole
  for (int i = 0; i < DELKA; ++i)
  {
    mocniny[i] = i*i;
  }
  // pod�v�me se, co pole skute�n� obsahuje po inicializaci
  tiskPole("mocniny = ", mocniny, DELKA);

  // kopie ukazatele - samotn� identifik�tor pole m� v�znam ukazatele na
  // za��tek pole
  // od t�to chv�le lze s ukazatelem uk pracovat stejn� jako s polem
  // POZOR! Zde se nevytv��� kopie pole! Pole z�st�v� v pam�ti jen jednou.
  //        Zde se kop�ruje ukazatel, tak�e k jednomu poli pak jde p�istupovat
  //        ze dvou m�st - p�es identifik�tory uk a mocniny.
  uk = mocniny;
  tiskPole("uk = ", uk, 10);

  // p�es ukazatel m��eme pole modifikovat
  // nyn� vyrob�me posloupnost t�et�ch mocnin cel�ch ��sel
  for (int i = 0; i < DELKA; ++i)
  {
    uk[i] = uk[i] * i; // nebo takto: uk[i] *= i;
  }

  tiskPole("uk = ", uk, 10);

  // POZOR! Opa�n� to nejde! Do prom�nn� typu pole NELZE nic p�i�adit
  // pole = uk; // toto p�eklada� odhal� jako syntaktickou chybu
}

/**
 * Funkce pro demonstraci toho, jak se daj� kop�rovat lok�ln�, jednorozm�rn�
 * pole.
 */
void kopieLokalnichPoli(void)
{
  // dv� lok�ln�, neinicializovan� pole
  int pole1[DELKA], pole2[DELKA];

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    pole1[i] = i + 1;
  }

  tiskPole("pole1 = ", pole1, DELKA);

  // pole nelze kop�rovat pouh�m p�i�azen�m!
  // datov� typ pole nezn� svou d�lku, tak�e by p�eklada� nev�d�l, kolik jak
  // velk� �sek pam�ti m� kop�rovat
//  pole2 = pole1; // syntaktick� chyba

  // mus�me postupovat prvek po prvku (nebo pou��t odpov�daj�c� knihovn� funkci)
  for (int i = 0; i < DELKA; ++i)
  {
    pole2[i] = pole1[i];
  }

  tiskPole("pole2 = ", pole2, DELKA);
}

//== konec = ukazatele a lok�ln� pole ==


//== za��tek = dynamick� alokace ==

/**
 * Demonstrace dynamicky alokovan�ch prom�nn�ch.
 *
 * Lok�ln� prom�nn� jsou um�st�ny v oblasti pam�ti zvan� z�sobn�k. P�i definici
 * prom�nn� se automaticky na z�sobn�ku vyhrad� pot�ebn� kus pam�ti a p�i
 * ukon�en� bloku nebo funkce se tato pam� zase automaticky uvoln� - nen�
 * pot�eba se o to starat. Nev�hodou je, �e lok�ln� prom�nn� nelze vyn�st
 * z funkce ven, proto�e po jej�m ukon�en� automaticky zanikaj�. Velikost
 * z�sobn�ku tak� b�v� z bezpe�nostn�ch d�vod� omezena, tak�e nelze vyu��t
 * ve�kerou dostupnou pam� po��ta�e.
 *
 * Dynamicky alokovan� prom�nn� jsou um�st�ny v oblasti pam�ti zvan� hromada.
 * Tuto pam� lze spravovat pouze ru�n�, pomoc� vol�n� knihovn�ch funkc�
 * malloc a free. T�mto zp�sobem lze vyu��t t�m�� ve�kerou dostupnou pam�
 * po��ta�e, ale program�tor je s�m zodpov�dn� za spr�vnou alokaci pam�ti
 * i jej� uvoln�n�, pokud u� ji nepot�ebuje.
 */
void dynamickaAlokace(void)
{
  // neinicializovan� ukazatel na int
  int *uCislo;

  // alokace pam�ti na hromad� o velikosti jednoho intu
  // oper�tor sizeof vrac� po�et bajt�, kter� dan� typ zab�r�
  // funkci malloc pou��vejte V�DY v kombinaci se sizeof
  // t�mto p��kazem alokujeme na hromad� prostor pro jednu prom�nnou typu int
  uCislo = malloc(1*sizeof(int));

  // k nov� alokovan� prom�nn� lze p�istupovat pouze pomoc� ukazatele, v na�em
  // p��pad� uCislo
  // prozat�m je hodnota alokovan� pam�ov� bu�ky neinicializovan�
  // k hodnot� pam�ov� bu�ky na adrese uCislo se nyn� dostaneme pomoc�
  // dereferen�n�ho oper�toru *
  printf("*uCislo = %d\n", *uCislo);
  *uCislo = 10;
  printf("*uCislo = %d\n", *uCislo);

  // d�le tuto bu�ku nebudeme pot�ebovat, proto ji mus�me uvolnit pomoc�
  // funkce free - v�imn�te si, �e funkci free se p�ed�v� ukazatel
  free(uCislo);

  // Nyn� je uCislo de facto neinicializovan� ukazatel, resp. ukazuje do
  // nealokovan� pam�ti. Odkaz p�es takov� ukazatel by zp�sobil hav�rii.
  // ��ste�n�m zm�rn�n�m tohoto rizika je nastaven� na hodnotu NULL, co� je
  // pr�zdn� ukazatel. Odkaz p�es n�j vede tak� k hav�rii, ale alespo� takov�
  // ukazatel m��eme otestovat, ne� s n�m n�co provedeme (�asto se takto
  // testuj� parametry funkc�).
  uCislo = NULL;


  // stejn�m zp�sobem m��eme na hromad� alokovat pole
  // k p��stupu k takto alokovan�mu poli vyu�ijeme ukazatel
  // funkci malloc �ekneme, aby alokovala pam� o velikosti DELKA*sizeof(int)
  // bajt�
  int *dynPole = malloc(DELKA*sizeof(int));

  // nyn� je pole neinicializovan� (nenechte se zm�st, pokud v n�m budou nuly,
  // je to jen n�hoda)
  // v�imn�te si, �e od t�to chv�le se s dynamicky alokovan�m polem pracuje
  // stejn� jako s lok�ln�m
  tiskPole("dynPole = ", dynPole, DELKA);

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    dynPole[i] = i*i;
  }
  tiskPole("dynPole = ", dynPole, DELKA);

  // po skon�en� pr�ce mus�me pole zase uvolnit
  free(dynPole);
}

/**
 * Demonstrace kop�rov�n� dynamick�ch pol�.
 */
void kopieDynamickychPoli(void)
{
  // dv� lok�ln� prom�nn� typu ukazatel na int
  int *pole1, *pole2;

  // alokujeme pole s d�lkou delka
  pole1 = malloc(DELKA*sizeof(int));

  // inicializace
  for (int i = 0; i < DELKA; ++i)
  {
    pole1[i] = i + 1;
  }
  tiskPole("pole1 = ", pole1, DELKA);

  // toto je pouh� kopie ukazatel�, nikoli pol�!
  // nyn� budou na stejn� pole ukazovat dva ukazatele
  pole2 = pole1;

  // ud�l�me v poli zm�nu p�es ukazatel pole2, abychom vid�li, �e tato zm�na
  // bude viditeln� i p�es ukazatel pole1
  pole2[5] = 9999;
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // skute�nou kopii lze ud�lat pouze tak, �e alokujeme prostor pro druh�,
  // stejn� dlouh� pole a pak jej prvek po prvku zkop�rujeme
  pole2 = malloc(DELKA*sizeof(int));
  for (int i = 0; i < DELKA; ++i)
  {
    pole2[i] = pole1[i];
  }
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // nyn� m�me skute�nou kopii pole
  // aby bylo vid�t, �e oba ukazatele ukazuj� na jin� pole, provedeme v jednom
  // z nich zm�nu
  pole2[2] = 888;
  tiskPole("pole1 = ", pole1, DELKA);
  tiskPole("pole2 = ", pole2, DELKA);

  // nakonec mus�me alokovanou pam� uvolnit
  free(pole1);
  free(pole2);
}

//== konec = dynamick� alokace ==

//== zacatek = operace s typem ukazatel ==
/**
 * Uk�zka dal��ch operac� nad datov�m typem ukazatel. B�n� pou��van� jsou
 * p�i�azen�, indexov�n�, reference a dereference. Ostatn� (porovn�v�n�,
 * s��t�n� s cel�mi ��sly) NEPOU��VEJTE dokud to nebude absolutn� nezbytn�,
 * proto�e to obvykle vede k t�ko �iteln�m program�m.
 */
void operaceNadUkazateli(void)
{
  // ukazatele lze kop�rovat p�i�azovac�m oper�torem - kop�ruje se adresa!
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

  // ukazatele lze i porovn�vat a p�i��tat/ode��tat k nim cel� ��slo
  // tomuto se ��k� adresov� aritmetika
  // POZOR! Tohle nepou��vejte. Adresov� aritmetika vede k obt�n� �iteln�mu
  // k�du, proto je takov� program v�ce n�chyln� k chyb�m.
  // POZOR! Nepou��vejte to jen proto, abyste ud�lali dojem. P�i obhajob�
  // projektu t�m sp�e vyprovokujete ot�zky, kter� velmi d�kladn� prov���
  // va�e skute�n� znalosti!

  int *pozice = pole; // kopie ukazatel�
  printf("Fibonacciho posloupnost: ");
  // p�i�ten� ��sla k adrese znamen� tot�, co indexov�n�
  while (pozice < pole+DELKA) // porovn�n� ukazatel�
  {
    printf(" %d ", *pozice); // dereference - z�sk�n� odkazovan� hodnoty
    ++pozice; // posun na adresu dal��ho prvku v poli -- adresa = adresa + sizeof(int)
  }
  printf("\n");


  // Adresov� aritmetiky se d� tak� pou��t pro p�ed�n� pouze ��sti pole do
  // podprogramu. Zde p�ed�v�me ukazatel na pole posunut� o 3 prvky (tedy od
  // indexu 3) ��k�me funkci, �e m� zpracovat n�sleduj�c� 4 prvky.
  // TIP: U� jste si uv�domili, pro� si pole nem��e pamatovat svou d�lku?
  tiskPole("pole[3-6] = ", pole+3, 4);

  // Stejn� m��eme zpracov�vat textov� �et�zce
  char * zprava = "Uvedomte si, ze jazyk C je fajn";
  printf("%s\n", zprava+16);

  // nyn� uvoln�me nepou��vanou pam�
  free(pole);
//  free(pozice); // Tohle by vedlo k hav�rii. Pro�?

}
//== konec = operace s typem ukazatel ==

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


  return EXIT_SUCCESS;  // program kon�� bez chyby
}
