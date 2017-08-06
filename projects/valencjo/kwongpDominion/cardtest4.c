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
    printf("EXITING PROGRAM!");
    exit(1);
  }
}

int testGarden(struct gameState* gState)
{
  int worked = 0;
  worked = cardEffect(gardens, 0, 0, 0, &gState, 0, 0);
  if(worked != -1)
  {
    printf("Garden failed!\n");
    assertTrue(1);
  }
}


int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
         remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing garden.\n");
  SelectStream(2);
  PutSeed(3);
  memset(&G, 23, sizeof(struct gameState)); 
  r = initializeGame(2, k, 1, &G);
  i=0;
  while(i<1000)
  {
    testGarden(&G);
    i++;
  }


  if(FAILEDTEST == 0)
    printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}