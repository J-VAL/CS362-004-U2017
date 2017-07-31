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
  //printf("got to beginning\n");
  int worked = 1;
  int coinCount = 0;
  int newCoinCount = 0;
  int i = 0;
  for(i;i<gState->handCount[player];i++)
  {
    if(gState->hand[player][i] == copper || gState->hand[player][i] == silver ||gState->hand[player][i] == gold )
      coinCount++;
    //printf("old card: %d\n",(int)gState->hand[player][i]);
  }
  if(adventure(treasure,player,thand,gState) != 0)
  {
   // printf("adventurer didn't work!\n");
    assertTrue(1);
    FAILEDTEST = 1;
  }
  //printf("got through a run\n");
  for(i=0;i<gState->handCount[player];i++)
  {
    if(gState->hand[player][i] == copper || gState->hand[player][i] == silver ||gState->hand[player][i] == gold )
      newCoinCount++;
   // printf("new card: %d\n",(int)gState->hand[player][i]);
  }
  if(newCoinCount != (coinCount+2) && gState->deckCount[player] != 0)
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

  int n,p,i,r,treasure,deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;
  int temphand[MAX_HAND];
  printf ("Testing adventurer.\n");
  SelectStream(2);
  PutSeed(3);
  for (n = 0; n < 10000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    treasure = 0;
    for(r = 0;r<G.deckCount[p];r++)
    {
      
        G.deck[p][r] = floor(Random() * 26);
      
    }
    for(r = 0;r<G.handCount[p];r++)
    {
      
        G.hand[p][r] = floor(Random() * 26);
      
    }
    for(r = 0;r<G.discardCount[p];r++)
    {
      
        G.discard[p][r] = floor(Random() * 26);
      
    }
    testAdventure(treasure,p,temphand,&G);
  }

  
      

  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}