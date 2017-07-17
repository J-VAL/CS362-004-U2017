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
		exit(1);
}

int testGameOver(struct gameState *gState)
{
	int fail = 0;
	gState->supplyCount[province] = 0;
	if(isGameOver(&gState) == 0)
		assertTrue(0);
	gState->supplyCount[province] = 6;
	if(isGameOver(&gState) == 1)
		assertTrue(0);
 	gState->supplyCount[curse]=0;
	if(isGameOver(&gState) == 1)
		assertTrue(0);
	gState->supplyCount[copper]=0;
	if(isGameOver(&gState) == 1)
		assertTrue(0);
	int i = 0;
		for(i;i<25;i++)
	{
		printf("%d\n",gState->supplyCount[i]);
	}
	gState->supplyCount[estate]=0;
	if(isGameOver(&gState) == 0)
		assertTrue(0);
	int i=0;
	for(i;i<25;i++)
	{
		gState->supplyCount[i] = 0;
	}
	if(isGameOver(&gState) == 0)
		assertTrue(0);
	if(FAILEDTEST == 0)
		printf("TEST SUCCESSFULLY COMPLETED!\n");
		
}


int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing isGameOver.\n");
  SelectStream(2);
  PutSeed(3);
  for(i=0;i<100;i++)
  {
  	memset(&G, 23, sizeof(struct gameState)); 
	r = initializeGame(2, k, 1, &G);
	testGameOver(&G);
	}

return 0;
}