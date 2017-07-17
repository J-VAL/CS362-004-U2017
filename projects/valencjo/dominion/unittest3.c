#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int FAILEDTEST = 0;

void assertTrue(int i)
{
	printf("TEST FAILED!\n");
	FAILEDTEST = 1;
	if (i==1)
	{
		printf("UPDATECOINS FAILED.  EXITING PROGRAM!");
		exit(1);
	}
}

int testUpdateCoins(int player, struct gameState *gState, int bonus)
{
	int worked;
	worked = updateCoins(player,gState,bonus);
	if(worked != 0)
		assertTrue(1);
	return gState->coins;
	
}


int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing isGameOver.\n");
  SelectStream(2);
  PutSeed(3);
    memset(&G, 23, sizeof(struct gameState)); 
	r = initializeGame(2, k, 1, &G);

  	G.handCount[0]=6;
  	int j = 0;
  	for(j;j<3;j++)
  	{
  		G.hand[0][j] = copper;
  	}
  	for(j;j<6;j++)
  	{
  		G.hand[0][j] = curse;
  	}
  	if(testUpdateCoins(0,&G,0) != 3)
  		assertTrue(0);
  	j=0;
  	for(j;j<3;j++)
  	{
  		G.hand[0][j] = silver;
  	}
  	for(j;j<6;j++)
  	{
  		G.hand[0][j] = curse;
  	}
  	if(testUpdateCoins(0,&G,0) != 6)
  		assertTrue(0);
  	j=0;
  	for(j;j<3;j++)
  	{
  		G.hand[0][j] = gold;
  	}
  	for(j;j<6;j++)
  	{
  		G.hand[0][j] = curse;
  	}
  	if(testUpdateCoins(0,&G,0) != 9)
  		assertTrue(0);
  	G.hand[0][0] = copper;
  	G.hand[0][1] = copper;
  	G.hand[0][2] = silver;
  	G.hand[0][3] = silver;
  	G.hand[0][4] = gold;
  	G.hand[0][5] = gold;
  	if(testUpdateCoins(0,&G,0) != 12)
  		assertTrue(0);
  	if(testUpdateCoins(0,&G,4) != 16)
  		assertTrue(0);
  	j=0;
  	for(j;j<6;j++)
  	{
  		G.hand[0][j] = curse;
  	}
  	if(testUpdateCoins(0,&G,0) != 0)
  		assertTrue(0);
  	if(testUpdateCoins(0,&G,5) != 5)
  		assertTrue(0);
  	G.hand[0][0] = copper;
  	if(testUpdateCoins(0,&G,0) != 1)
  		assertTrue(0);
  	G.handCount[0] = 500;
  	j = 0;
  	for(j;j<500;j++)
  	{
  		G.hand[0][j] = copper;
  	}
  	if(testUpdateCoins(0,&G,0) != 500)
  		assertTrue(0);
  	G.handCount[1] = 6;
  	G.hand[1][0] = copper;
  	G.hand[1][1] = copper;
  	G.hand[1][2] = silver;
  	G.hand[1][3] = silver;
  	G.hand[1][4] = gold;
  	G.hand[1][5] = gold;
  	if(testUpdateCoins(1,&G,0) != 12)
  		assertTrue(0);
  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}