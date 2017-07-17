CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testShuffle: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

testIsGameOver: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

testGetCost: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

testSmith: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

testAdventure: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

testCouncil: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

testGarden: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

runAllTests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

rununittest1: unittest1
	./unittest1 &> unittest1result.out
	gcov dominion.c >> unittest1result.out
	cat dominion.c.gcov >> unittest1result.out

rununittest2: unittest2
	./unittest2 &> unittest2result.out
	gcov dominion.c >> unittest2result.out
	cat dominion.c.gcov >> unittest2result.out

rununittest3: unittest3
	./unittest3 &> unittest3result.out
	gcov dominion.c >> unittest3result.out
	cat dominion.c.gcov >> unittest3result.out

rununittest4: unittest4
	./unittest4 &> unittest4result.out
	gcov dominion.c >> unittest4result.out
	cat dominion.c.gcov >> unittest4result.out

runcardtest1: cardtest1
	./cardtest1 &> cardtest1result.out
	gcov dominion.c >> cardtest1result.out
	cat dominion.c.gcov >> cardtest1result.out

runcardtest2: cardtest2
	./cardtest2 &> cardtest2result.out
	gcov dominion.c >> cardtest2result.out
	cat dominion.c.gcov >> cardtest2result.out

runcardtest3: cardtest3
	./cardtest3 &> cardtest3result.out
	gcov dominion.c >> cardtest3result.out
	cat dominion.c.gcov >> cardtest3result.out

runcardtest4: cardtest4
	./cardtest4 &> cardtest4result.out
	gcov dominion.c >> cardtest4result.out
	cat dominion.c.gcov >> cardtest4result.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
