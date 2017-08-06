#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertTrue(int i)
{
	printf("TEST FAILED!\n");
	if (i==1)
		exit(1);
}

int checkShuffle(int p, struct gameState *gState)
{
	int fail = 0;
	int i = 0;
	int count = 0;
	struct gameState last;
	memset(&last, 23, sizeof(struct gameState)); 
	while(i<100){
		int j = 0;
		for(j;j<gState->deckCount[p];j++)
		{
		last.deck[p][j] = gState->deck[p][j];
		}
		j=0;
		shuffle(p,gState);
		int same = 1;
		for(j;j<gState->deckCount[p];j++)
		{
			if(gState->deck[p][j] != last.deck[p][j])
				same = 0;
		}
		if(same == 1)
			count++;
		if(count == 100)
			fail = 1;
		i++;
		if (i == 100)
			count = 0;
	}
	if(fail == 1)
		assertTrue(0);
	else
		printf("TEST SUCCESSFULLY COMPLETED!\n");
	return 0;
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing Shuffle.\n");
   SelectStream(2);
  PutSeed(3);
  	  memset(&G, 23, sizeof(struct gameState)); 
	r = initializeGame(2, k, 1, &G);
    for (p = 0; p < 2; p++) {
    handCount = 0;
   for (deckCount = 6; deckCount < 500; deckCount++) {
	  
	  G.deckCount[p] = deckCount;
	  if(deckCount%2 == 0)
	  	G.deck[p][deckCount-1] = council_room;
	  else
	  	G.deck[p][deckCount-1] = adventurer;

	  checkShuffle(p, &G);
	}
	}
return 0;
}