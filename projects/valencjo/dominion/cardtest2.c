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

int testAdventure(int treasure, int player,int* thand, struct gameState *gState)
{
  int worked = 1;
  int coinCount = 0;
  int newCoinCount = 0;
  int i = 0;
  for(i;i<gState->handCount[player];i++)
  {
    if(gState->hand[player][i] == copper || gState->hand[player][i] == silver ||gState->hand[player][i] == gold )
      coinCount++;
  }
  if(adventure(treasure,player,thand,gState) != 0)
  {
    printf("adventurer didn't work!\n");
    assertTrue(1);
    FAILEDTEST = 1;
  }
  for(i;i<gState->handCount[player];i++)
  {
    if(gState->hand[player][i] == copper || gState->hand[player][i] == silver ||gState->hand[player][i] == gold )
      newCoinCount++;
  }
  if(newCoinCount != (coinCount+2))
  {
    worked = 0;
    printf("Didn't gain two more treasure cards to hand! new:%d old%d",newCoinCount,coinCount);
  }

	if(worked == 0)
  {
		assertTrue(0);
    FAILEDTEST = 1;
  }
	return worked;
	
}


int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;
  int temphand[MAX_HAND];
  printf ("Testing adventurer.\n");
  SelectStream(2);
  PutSeed(3);
  i = 0;
  while(i<1000)
  {
  memset(&G, 23, sizeof(struct gameState)); 
  r = initializeGame(2, k, 1, &G);
  int treasure=0;
  testAdventure(treasure,0,&temphand,&G);
  i++;
}

  
      

  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}