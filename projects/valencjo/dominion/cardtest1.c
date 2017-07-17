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

int testSmithy(int player, int handPos, struct gameState *gState)
{
  int worked = 1;
  int lessThan = 0;
	int numHandCards = gState->handCount[player];
  int numDeckCards = gState->deckCount[player];
  int numDiscards = gState->discardCount[player];
	if (numDeckCards < 3)
    lessThan = 1;
  if(smith(player, handPos, gState) != 0)
  {
    printf("Smithy didn't work\n");
    worked = 0;
  }
  if(gState->handCount[player] != (numHandCards+2) && (numDiscards + numDeckCards) >2)
  {
    printf("wrong number of cards in hand previous:%d now: %d\n",numHandCards,gState->handCount[player]);
    worked = 0;
  }
  if(lessThan && (numDeckCards + numDiscards)>2)
  {
    if(gState->deckCount[player] != (numDiscards + numDeckCards - 3))
    {
      worked = 0;
    
    printf("Wrong deck smaller than 2 previous:%d %d now:%d\n",numDeckCards,numDiscards,gState->deckCount[player]);
  }
  }
  else if(lessThan && !((numDiscards + numDeckCards)>2))
  {
    if(gState->deckCount[player] != 0)
    {
      worked = 0;
    
    printf("Wrong deck and discard smaller than 3");
   }
  }
  else
  {
    if(gState->deckCount[player] != (numDeckCards - 3))
    {
      worked = 0;
    
    printf("Wrong deck count greater than 2 previous:%d now%d\n",numDeckCards, gState->deckCount[player]);
     }
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

  printf ("Testing Smithy.\n");
  SelectStream(2);
  PutSeed(3);
  memset(&G, 23, sizeof(struct gameState)); 
  r = initializeGame(2, k, 1, &G);
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
  for (handCount = 0; handCount < 5; handCount++) {
    memset(&G, 23, sizeof(struct gameState)); 
    r = initializeGame(2, k, 1, &G);
    G.deckCount[p] = deckCount;
    memset(G.deck[p], 0, sizeof(int) * deckCount);
    G.discardCount[p] = discardCount;
    memset(G.discard[p], 0, sizeof(int) * discardCount);
    G.handCount[p] = handCount;
    memset(G.hand[p], 0, sizeof(int) * handCount);
    int handPos = 0;
    G.hand[p][0] = smithy;
    testSmithy(p,handPos, &G);
  }
      }
    }
  }

  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}