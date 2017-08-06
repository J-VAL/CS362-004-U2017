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
//  printf("Hand: %d\n",numHandCards);
 // printf("Deck: %d\n",numDeckCards);
 // printf("Discards: %d\n",numDiscards);
  int numCardsOther;
  int newNumCardsOther;
  int lessThan = 0;
  int i;
  int buys = gState->numBuys;
  if (numDeckCards < 4)
    lessThan = 1;
  for (i = 0; i < gState->numPlayers; i++)
  {
    if ( i != player )
      {
        numCardsOther = gState->handCount[i];
      }
  }
  if(council_room_func(handPos,gState) != 0)
  {
    worked = 0;
    printf("council_room failed!");
    assertTrue(1);
  }
//  printf("Ran through once.\n");
  if(gState->handCount[player] != (numHandCards+3) && (numDiscards + numDeckCards) >3 )
  {
    printf("wrong number of cards in hand previous:%d now: %d\n",numHandCards,gState->handCount[player]);
    worked = 0;
  }
  if(lessThan && (numDeckCards + numDiscards)>3)
  {
    if(gState->deckCount[player] != (numDiscards + numDeckCards - 4))
    {
      worked = 0;
    
    printf("Wrong deck smaller than 3 previous:%d %d now:%d\n",numDeckCards,numDiscards,gState->deckCount[player]);
  }
  }
  else if(lessThan && !((numDiscards + numDeckCards)>3))
  {
    if(gState->deckCount[player] != 0)
    {
      worked = 0;
    
    printf("Wrong deck and discard smaller than 4\n");
   }
   if(gState->handCount[player] != (numHandCards + numDeckCards + numDiscards -1))
   {
    worked = 0;
    printf("Wrong hand count with deck and discard smaller than 4.\nHand:%d\nDeck:%d\nDiscard:%d\nNew Hand:%d\n",numHandCards,numDeckCards,numDiscards,gState->handCount[player]);
   }
  }
  else
  {
    if(gState->deckCount[player] != (numDeckCards - 4) )
    {
      worked = 0;
    
    printf("Wrong deck count greater than 3 previous:%d now%d\n",numDeckCards, gState->deckCount[player]);
     }
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
if(gState->numBuys != (buys+1))
{
  worked = 0;
  printf("Didn't increase buys!\n");
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
  for (n = 0; n < 10000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    G.numPlayers = 2;
    for(p = 0; p<2;p++)
    {
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
    
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
  }
  G.playedCardCount = floor(Random() * MAX_DECK);
    for(r = 0;r<G.playedCardCount;r++)
    {
      
        G.playedCards[r] = floor(Random() * 22) + 4;
      
    }
    p = floor(Random() * 2);
    int handPos = floor(Random() * G.handCount[p]);
    G.hand[p][handPos] = council_room;
   // printf("Got here.\n");
    G.whoseTurn = p;
    testCouncil(p,handPos, &G);
    
  }

  if(FAILEDTEST == 0)
    printf("TEST SUCCESSFULLY COMPLETED!\n");

return 0;
}