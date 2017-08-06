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
//  printf("Hand: %d\n",numHandCards);
 // printf("Deck: %d\n",numDeckCards);
//  printf("Discards: %d\n",numDiscards);
	if (numDeckCards < 3)
    lessThan = 1;
  if(smithy_func(handPos, gState) != 0)
  {
    printf("Smithy didn't work\n");
    worked = 0;
  }
  //printf("Ran through once.\n");
  if(gState->handCount[player] != (numHandCards+2) && (numDiscards + numDeckCards) >2 && !lessThan)
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
    
    printf("Wrong deck and discard smaller than 3\n");
   }
   if(gState->handCount[player] != (numHandCards + numDeckCards + numDiscards - 1))
   {
    worked = 0;
    printf("Wrong hand count with deck and discard smaller than 3\n");
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
    G.playedCardCount = floor(Random() * MAX_DECK);
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
    for(r = 0;r<G.playedCardCount;r++)
    {
      
        G.playedCards[r] = floor(Random() * 22) + 4;
      
    }
    int handPos = floor(Random() * G.handCount[p]);
    G.hand[p][handPos] = smithy;
   // printf("Got here.\n");
    G.whoseTurn = p;
    testSmithy(p,handPos, &G);
    
  }

  if(FAILEDTEST == 0)
  	printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}