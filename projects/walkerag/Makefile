CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o interface.o 
	gcc -o unitTest1Baron unittest1.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unitTest2Minion unittest2.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unitTest3Ambassador unittest3.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o unitTest4Tribute unittest4.c dominion.o rngs.o interface.o $(CFLAGS) 
	gcc -o unitTest5Mine unittest5.c dominion.o rngs.o interface.o $(CFLAGS)
	./unitTest1Baron
	./unitTest2Minion
	./unitTest3Ambassador
	./unitTest4Tribute
	./unitTest5Mine
	gcov dominion.c -b -f >> unittestresults.out

randomtestresults: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o interface.o rngs.o
	gcc -o randomtest1Baron randomtestcard1.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o randomtest2Minion randomtestcard2.c dominion.o rngs.o interface.o $(CFLAGS)
	gcc -o randomtest3Tribute randomtestcard3.c dominion.o rngs.o interface.o $(CFLAGS)
	./randomtest1Baron
	./randomtest2Minion
	./randomtest3Tribute
	gcov dominion.c -b -f >> randomtestresults.out	

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
