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

int testGetCost(int cardNumber)
{
	int worked;
	worked = getCost(cardNumber);
	if(worked == -1)
		assertTrue(1);
	return worked;
	
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

    if(testGetCost(curse) != 0)
      assertTrue(0);
    if(testGetCost(estate) != 2)
      assertTrue(0);
    if(testGetCost(duchy) != 5)
      assertTrue(0);
    if(testGetCost(province) != 8)
      assertTrue(0);
    if(testGetCost(copper) != 0)
      assertTrue(0);
    if(testGetCost(silver) != 3)
      assertTrue(0);
    if(testGetCost(gold) != 6)
      assertTrue(0);
    if(testGetCost(adventurer) != 6)
      assertTrue(0);
    if(testGetCost(council_room) != 5)
      assertTrue(0);
    if(testGetCost(feast) != 4)
      assertTrue(0);
    if(testGetCost(gardens) != 4)
      assertTrue(0);
    if(testGetCost(mine) != 5)
      assertTrue(0);
    if(testGetCost(remodel) != 4)
      assertTrue(0);
    if(testGetCost(smithy) != 4)
      assertTrue(0);
    if(testGetCost(village) != 3)
      assertTrue(0);
    if(testGetCost(baron) != 4)
      assertTrue(0);
    if(testGetCost(great_hall) != 3)
      assertTrue(0);
    if(testGetCost(minion) != 5)
      assertTrue(0);
    if(testGetCost(steward) != 3)
      assertTrue(0);
    if(testGetCost(tribute) != 5)
      assertTrue(0);
    if(testGetCost(ambassador) != 3)
      assertTrue(0);
    if(testGetCost(cutpurse) != 4)
      assertTrue(0);
    if(testGetCost(embargo) != 2)
      assertTrue(0);
    if(testGetCost(outpost) != 5)
      assertTrue(0);
    if(testGetCost(salvager) != 4)
      assertTrue(0);
    if(testGetCost(sea_hag) != 4)
      assertTrue(0);
    if(testGetCost(treasure_map) != 4)
      assertTrue(0);
  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}