# Násobička matic
Tento program přijímá dvě matice na standratním vstupu a vrací jejich součin na standartní výstup. 

## V Čem je řešení zajímávé?
Data jsou v paměti ukládána výhodně. Matice se ukládájí transponovaně tak, aby byl maximální cache hit v paměti při práci s jednolivými řádky matice. Program byl napsán efektivně za použití C++ vychytávek a pomocných funkcí tak, aby se autor neupsal k smrti a nedošlo ke snížení kvality celého řešení. Při načítání velkého množství čísel jsou standartní funkce velmi pomalé, a proto byla napsána vlastní funkce `getNum()`. Ve výchozí podobě se při výpočtu řešení používají vlákna. To lze vypnout za pomocí přepínače. Celý program se překvapivě rychlostí vyrovná implementaci v Numpy, což je poměrně překvapivé k "jednoduchosti" řešení.

## Kompilace
Jedná se o jednosouborový program. Stačí použít `g++ -Wall -Wextra -g -pthread -std=c++11 -Ofast matrix.cpp -o ./main` anebo `cmake CMakeLists.txt` k vygenerování Makefile. 

## Formát vstupu
Vstup je formátován takto:
```
vyska sirka
data
vyska sirka
data
```
Výstup je formátován takto:
```
vyska sirka
data
```
Níže jsou uvedeny ukázky vstupu a výstupu.
```
3 3
1 2 3
4 5 6
7 8 9
3 3
9 8 7
6 5 4
3 2 1
```
```
3 3
30 24 18
84 69 54
138 114 90
```

## Návratové hodnoty
`0` - vše proběhlo ok
`1` - neznámé argumenty
`2` - špatné dimenze matice A
`3` - špatné dimenze matice B
`4` - špatné dimenze pro násobení matic

## Jak použít?
Pro výpočet se defaultně používají vlákna (tedy pokud je matice velká). Pro jednovláknový běh stačí použít přepínač `-singleThread`. Pro velké matice je vhodné použít soubory na vstup a výstup.
`./main -singleThread < ./tests/input/test01.txt > ./output01.txt`
`./main -singleThread < ./tests/input/test02.txt > ./output02.txt`
`./main < ./tests/input/test03.txt > ./output03.txt`
`./main < ./tests/input/test04.txt > ./output04.txt`

## Testování
Pro testování byly vytvořeny Python skripty. `test.py` umožňuje porovnat 2 soubory, zda jsou stejné.
`matrix.py` čte matice ze souboru a vypočítá jejich součin. Lze použít pro generování správných výsledků.
V obou skriptech je nutné měnit názvy souborů dle potřeby.

## Statistika
Měření proběhlo na MacBook Pro 2017 (dvoujádro) a nejnovější verzi numpy. Časy jsou uvedeny ve vteřinách. Měřen byl čistý výpočet, nikoli načítání dat. Pokud vezmeme v úvahu i načítání dat, tak to Python převálcuje nadobro.

| Data   | čas numpy | čas programu | čas programu (-singleThread) |
|--------|-----------|--------------|------------------------------|
| test01 | 0.000022  | 0.0000005    | 0.000000461                  | 
| test02 | 0.000020  | 0.000000544  | 0.000000535                  | 
| test03 | 1.649378  | 0.0973859    | 0.186383                     | 
| test04 | 32.928086 | 0.866959     | 1.85268                      | 

Při obrovských maticích `numpy.matmul()` překvapivě pokulhává.

