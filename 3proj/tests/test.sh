#!/bin/sh

#pro velke blazny staci misto BIN="./proj3" napsat BIN="valgrind --leak-check=full .proj3"

BIN="./proj3"

make clean
######################################################
echo -n "TEST00 Prekladu ->>>>>>>>>> "
make 2>preklad
if [ -s "preklad" ]; then
echo "Pri prekladu nastaly chyby! vice v souboru preklad\n"
else echo "OK\n"
fi
######################################################
echo "TEST01 ./proj3 --h"
$BIN --h 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST02 ./proj3 -help"
$BIN -help 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST03 ./proj3 -h"
$BIN -h >out
if [ -s "out" ]; then
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST04 ./proj3 --test"
$BIN --test 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST05 ./proj3 -test"
$BIN -test 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST06 ./proj3 -test fileta"
$BIN -test fileta 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST07 ./proj3 --test fileta <-soubor neexistuje"
$BIN --test fileta 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST08 ./proj3 --test tests/mat0x0 obsahuje 0"
$BIN --test tests/mat0x0 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST09 ./proj3 --test tests/mat1x0 neobsahuje prvek"
$BIN --test tests/mat1x0 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST10 ./proj3 --test tests/mat0x1"
$BIN --test tests/mat0x1 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST11 ./proj3 --test tests/mat1x1"
$BIN --test tests/mat1x1 >out
if [ -s "out" ]; then
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST12 ./proj3 --test tests/mat1x1x"
$BIN --test tests/mat1x1x 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST13 ./proj3 --test tests/mat1x1float"
$BIN --test tests/mat1x1float 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST14 ./proj3 --test tests/mat1xx"
$BIN --test tests/mat1xx 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST15 ./proj3 --test tests/mat5x5over"
$BIN --test tests/mat5x5over 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST16 ./proj3 --test tests/mat5x5"
$BIN --test tests/mat5x5 >out
if [ -s "out" ]; then
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST17 ./proj3 --test tests/mat5x5less"
$BIN --test tests/mat5x5less 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST18 ./proj3 --add tests/mat5x5 tests/mat1x1 ->false"
$BIN --add tests/mat5x5 tests/mat1x1 >out
if [ -s "out" ]; then
cat out
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST19 ./proj3 --add tests/mat5x5 tests/mat5x5"
$BIN --add tests/mat5x5 tests/mat5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/addmat5x5mat5x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST20 ./proj3 --add tests/mat4x5 tests/mat5x4 ->false"
$BIN --add tests/mat4x5 tests/mat5x4 >out
if [ -s "out" ]; then
cat out
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST21 ./proj3 --add tests/mat1x5 tests/mat1x5over ->error"
$BIN --add tests/mat1x5 tests/mat1x5over 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST22 ./proj3 --add tests/mat5x5 tests/mat5x5less ->error"
$BIN --add tests/mat5x5 tests/mat5x5less 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST23 ./proj3 --mult tests/mat5x5 tests/mat5x5less ->error"
$BIN --mult tests/mat5x5 tests/mat5x5less 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST24 ./proj3 --mult tests/mat5x5 tests/mat5x5"
$BIN --mult tests/mat5x5 tests/mat5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/multmat5x5mat5x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST25 ./proj3 --mult tests/mat4x5 tests/mat5x4"
$BIN --mult tests/mat4x5 tests/mat5x4 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/multmat4x5mat5x4 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST26 ./proj3 --mult tests/mat5x4 tests/mat4x5"
$BIN --mult tests/mat5x4 tests/mat4x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/multmat5x4mat4x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST27 ./proj3 --trans tests/mat5x5"
$BIN --trans tests/mat5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/transmat5x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST28 ./proj3 --trans tests/mat5x4"
$BIN --trans tests/mat5x4 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/transmat5x4 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST29 ./proj3 --expr tests/mat5x5 tests/mat5x5"
$BIN --expr tests/mat5x5 tests/mat5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/exprmat5x5mat5x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST30 ./proj3 --expr tests/mat5x5 tests/transmat5x5"
$BIN --expr tests/mat5x5 tests/transmat5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/exprmat5x5transmat5x5 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST31 ./proj3 --expr tests/mat4x5 tests/transmat5x4 ->false"
$BIN --expr tests/mat4x5 tests/mat5x4 >out
if [ -s "out" ]; then
cat out
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST32 ./proj3 --expr tests/mat5x4 tests/transmat4x5 ->false"
$BIN --expr tests/mat5x4 tests/mat4x5 >out
if [ -s "out" ]; then
cat out
echo "OK\n"
else echo "Nevypsal na stdout < mozna chyba!\n"
fi
######################################################
echo "TEST33 ./proj3 --expr tests/mat1x1 tests/mat1x1"
$BIN --expr tests/mat1x1 tests/mat1x1 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/exprmat1x1mat1x1 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST34 ./proj3 --test tests/mat1x-1 ->error"
$BIN --expr tests/mat1x-1 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST35 ./proj3  --water r s tests/mat1x1 ->error"
$BIN --water r s tests/mat1x1 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST36 ./proj3  --water 1 1 tests/mat1x1 ->error za hranici pole"
$BIN --water 1 1 tests/mat1x1 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST37 ./proj3  --water 0 0 tests/mat1x1"
$BIN --water 0 0 tests/mat1x1  >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/watermat1x1 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST38 ./proj3  --water 2 2 tests/watermat5x5"
$BIN --water 2 2 tests/watermat5x5  >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/watermat5x5res >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST39 ./proj3  --water 2 2 tests/izpmat5x4"
$BIN --water 2 2 tests/izpmat5x4  >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/izpmat5x4res >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST40 ./proj3  --water 2 2 tests/mat0x0 ->error"
$BIN --water 2 2 tests/mat0x0 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST41 ./proj3  --water 8 25 tests/water15x55 <V tomto testu muze byt malicka chybicka, nejsem si jistej>"
$BIN --water 8 25 tests/water15x55 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/water15x55res >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST42 ./proj3  --water 0 0 tests/water5x5"
$BIN --water 0 0 tests/water5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/water5x5res >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST43 ./proj3  --water 2 2 tests/water5x5"
$BIN --water 2 2 tests/water5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/water5x5oneres >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST44 ./proj3  --carom 0 0 S 10 tests/carom2x2 ->error"
$BIN --carom 0 0 S 10 tests/carom2x2 2>err
if [ -s "err" ]; then
echo "OK\n"
else echo "Nevypsal na stderr < chyba!\n"
fi
######################################################
echo "TEST45 ./proj3  --carom 0 0 V 10 tests/carom2x2"
$BIN --carom 0 0 V 10 tests/carom2x2 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom2x2V10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST46 ./proj3  --carom 0 0 JV 10 tests/carom2x2"
$BIN --carom 0 0 JV 10 tests/carom2x2 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom2x2JV10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST47 ./proj3  --carom 0 0 JZ 10 tests/carom2x2"
$BIN --carom 0 0 JZ 10 tests/carom2x2 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom2x2JZ10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST48 ./proj3  --carom 2 2 JZ 10 tests/carom5x5"
$BIN --carom 2 2 JZ 10 tests/carom5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom5x5JZ10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST49 ./proj3  --carom 2 1 JZ 10 tests/carom5x5"
$BIN --carom 2 1 JZ 10 tests/carom5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom5x5JZ102 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST50 ./proj3  --carom 2 2 SZ 10 tests/carom5x5"
$BIN --carom 2 2 SZ 10 tests/carom5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom5x5SZ10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST51 ./proj3  --carom 2 1 SZ 10 tests/carom5x5"
$BIN --carom 2 1 SZ 10 tests/carom5x5 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom5x5SZ102 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST52 ./proj3  --carom 0 1 JZ 10 tests/carom4x4"
$BIN --carom 0 1 JZ 10 tests/carom4x4 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom4x4JZ10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST53 ./proj3  --carom 1 2 JV 10 tests/carom4x4"
$BIN --carom 1 2 JV 10 tests/carom4x4 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom4x4JV10 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST54 ./proj3  --carom 2 2 JV 10 tests/carom4x4"
$BIN --carom 2 2 JV 10 tests/carom4x4 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom4x4JV102 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi
######################################################
echo "TEST55 ./proj3  --carom 0 0 SV 1000000 tests/carom1x1"
$BIN --carom 0 0 SV 1000000 tests/carom1x1 >out
if [ -s "out" ]; then
echo "OK"
else echo "Nevypsal na stdout < mozna chyba!"
fi
diff -wB out tests/carom1x1SV1000000 >diff_out
if [ -s "diff_out" ]; then
echo "Vysledek neodpovida\n"
else echo "Vysledek OK\n"
fi

echo "mate radi velikonoce?"
echo "KONEC"


rm -rf diff_out err out












