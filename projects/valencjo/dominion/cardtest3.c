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

int testCouncil(int player, int handPos, struct gameState *gState)
{
  int worked = 1;

  int numHandCards = gState->handCount[player];
  int numDeckCards = gState->deckCount[player];
  int numDiscards = gState->discardCount[player];
  int numCardsOther;
  int newNumCardsOther;
  int i;
  for (i = 0; i < gState->numPlayers; i++)
  {
    if ( i != player )
      {
        numCardsOther = gState->handCount[i];
      }
  }
  if(council(player,handPos,gState) != 0)
  {
    worked = 0;
    printf("council_room failed!");
    assertTrue(1);
  }
if(gState->handCount[player] != (numHandCards+3))
{
  worked = 0;
  printf("Didn't get 4 more cards old:%d new%d\n",numHandCards,gState->handCount[player]);
}
if(gState->discardCount[player] != (numDiscards+1))
{
  worked = 0;
  printf("Didn't discard council_room\n");
}
  for (i = 0; i < gState->numPlayers; i++)
  {
    if ( i != player )
      {
        newNumCardsOther = gState->handCount[i];
      }
  }
if(newNumCardsOther != (numCardsOther+1))
{
  worked = 0;
  printf("Other player didn't gain card!\n");
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

  printf ("Testing council_room.\n");
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
    testCouncil(p,handPos, &G);
  }
      }
    }
  }

  if(FAILEDTEST == 0)
    printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}