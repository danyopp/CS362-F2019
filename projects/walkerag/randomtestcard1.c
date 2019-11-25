#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int printGameState(struct gameState G);
void randomizer(struct gameState *preG, struct gameState *postG);
void testResults(struct gameState preG, struct gameState G, int choice1, int trialNum);
int assert(int expected, int testval , char* string, struct gameState preG, struct gameState postG, int TrialNum );
 



int assert(int expected, int testval , char* string, struct gameState preG, struct gameState postG, int trialNum )
{ 
	if(expected==testval)
	{	return 0;}
	else if(expected > testval)
	{
		printf("\n\nERROR: Trial Number: %d\n", trialNum);
		printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);
//		printf("------Preconditions:------\n");
//		printGameState(preG);
//		printf("------Postconditions:------\n");
//		printGameState(postG);
	} 
	else if(expected < testval)
	{
		printf("\n\nERROR: Trial Number: %d\n", trialNum);
		printf("ASSERT FAILED: (%d-expected)(%d-value present) for %s\n", expected, testval, string);
//		printf("------Preconditions:------\n");
//		printGameState(preG);
//		printf("------Postconditions:------\n");
//		printGameState(postG);
	

	} 

	return 1;
}




int printGameState(struct gameState G)
{
printf("numPlayers: %d\n", G.numPlayers);
printf("Whose turn: %d\n", G.whoseTurn);
printf("Number of buys: %d\n", G.numBuys);
printf("Number of coins: %d\n", G.coins);
printf("Current player Handcount: %d\n", G.handCount[G.whoseTurn]);
printf("Current player DeckCount: %d\n", G.deckCount[G.whoseTurn]);
printf("Current player Discard Count: %d\n", G.discardCount[G.whoseTurn]);
printf("Current Cards in hand: ");
int a = 0;
for(a=0; a < G.handCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.hand[G.whoseTurn][a]);
	}
printf("\n");
printf("Current Cards in deck: ");
for(a=0; a < G.deckCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.deck[G.whoseTurn][a]);
	}
printf("\n");
printf("Current Cards in discard ");
for(a=0; a < G.discardCount[G.whoseTurn]; a++)
	{
	printf("%d ", G.discard[G.whoseTurn][a]);
	}
printf("\n");

printf("Cards numbers in supply ");

for(a=0; a < 26; a++)
	{
	printf("%d ", G.supplyCount[a]);
	}
printf("\n");

return 0;
}


void randomizer(struct gameState *preG, struct gameState *postG)
{
	int cardsIn = 20; 
	int a, playr, randCard;
	postG->numPlayers = (rand() % 3)+2; 		//number of players
	postG->whoseTurn = rand() % postG->numPlayers; // whose turn it is
	postG->coins = rand() % 72 ; //Max treasure in game
	postG->numBuys = rand() % 20; //Number of Buys
	postG->supplyCount[estate] = rand() % 13; //Number of supplys

	for (playr = 0;playr< postG->numPlayers; playr++)	
	   {
		//Set up player hands discard and decks
		postG->handCount[playr] = (rand() % cardsIn)+1; //Number of cards in player's hand
		postG->deckCount[playr] = (rand() % cardsIn); //Number of cards in player's deck
		postG->discardCount[playr] = (rand() % cardsIn); //Number of cards in player's discard count
	
		for(a=0;a<postG->handCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->hand[playr][a] = randCard;
		}
		for(a=0;a<postG->deckCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->deck[playr][a] = randCard;
		}
		for(a=0;a<postG->discardCount[playr];a++) //randomize cards in hand
		{
			randCard = rand() % (treasure_map+1); 
			postG->discard[playr][a] = randCard;
		}
	
	    }

	//make sure baron is in hand of current player
	int foundBaron = 0;
	for(a=0;a<postG->handCount[postG->whoseTurn];a++)
	  {
		if(postG->hand[postG->whoseTurn][a] == baron)
		{	foundBaron = 1;} 
	  }
	if (foundBaron == 0)
  	  {
		//add baron to a random card in players hand
		postG->hand[postG->whoseTurn][rand() % postG->handCount[postG->whoseTurn]] = baron; 
	  }		

}




void testResults(struct gameState preG, struct gameState G, int choice1, int trialNum)
{
	//Test results for expected outcome

	assert( preG.numBuys + 1, G.numBuys , "Number of Buys should have increased by 1", preG, G, trialNum); 
	int preEstateCountHand = 0, postEstateCountHand = 0;
	int preEstateCountDiscard = 0, postEstateCountDiscard = 0;
	int d;

	//count estates in hand and discard
	for(d=0; d< G.handCount[G.whoseTurn];d++)
	{
		if (G.hand[G.whoseTurn][d] == estate)
		{postEstateCountHand++;}
	}
	for(d=0; d< preG.handCount[preG.whoseTurn];d++)
	{
		if (G.hand[G.whoseTurn][d] == estate)
		{preEstateCountHand++;}
	}
	for(d=0; d< G.discardCount[G.whoseTurn];d++)
	{
		if (G.discard[G.whoseTurn][d] == estate)
		{postEstateCountDiscard++;}
	}
	for(d=0; d< preG.discardCount[preG.whoseTurn];d++)
	{
		if (G.discard[G.whoseTurn][d] == estate)
		{preEstateCountDiscard++;}
	}
	
	//assert(expectedval, testVal...
	//choice == 0: No estate discarded from hand, gained estate in discard
	if(choice1==0)
	{
	   assert(preG.numBuys + 1, G.numBuys, "Choice0: Number of buys should have been increased by 1\n", preG, G, trialNum);	
	   assert(preG.coins, G.coins, "Choice0: Number of coins should not have changed\n", preG, G, trialNum);
	   assert(preEstateCountHand, postEstateCountHand, "Choice0: Number of estates in hand should not change\n", preG, G, trialNum);
	   assert(preEstateCountDiscard+1, postEstateCountDiscard, "Choice0: An additional estate should have been added to discard\n", preG, G, trialNum);
	   assert(preG.supplyCount[estate]-1, G.supplyCount[estate], "Choice0: supply of estates should decrease by one\n", preG, G, trialNum);
	}
	//choice == 1: Estate discarded from hand to discard, + 4 treasure 
	if(choice1==1)
	{
	   if (preEstateCountHand == 0 )
		{//assert(1, preEstateCountHand, " Choice1: Need at least one estate in hand to gain +4 treasure", preG, G, trialNum);
		 assert(preG.coins, G.coins, " Choice1:No estates in hand/ Number of coins should not have changed\n", preG, G, trialNum);
		 assert(preG.supplyCount[estate]-1, G.supplyCount[estate], "Choice1: No estates in hand/ supply of estates should decrease by one\n", preG, G, trialNum);
		}	
	   assert(preG.numBuys+1, G.numBuys , "Choice1: Number of buys should have been increased by 1\n", preG, G, trialNum);	
	   if (preEstateCountHand >=1)
	  	{assert(preG.coins+4, G.coins, "Choice1: Number of coins should increase by 4\n", preG, G, trialNum);
		 assert(preEstateCountHand - 1, postEstateCountHand, "Choice1: Number of estates in hand should decreae by 1\n", preG, G, trialNum);
		 assert(preG.supplyCount[estate], G.supplyCount[estate], "Choice1: supply of estates should not have changed\n",preG,G,trialNum);
		}
	   assert(preEstateCountDiscard+1, postEstateCountDiscard, "Choice1: An additional estate should have been added to discard\n", preG, G, trialNum);
	}

return;
}








//Declare Gamestate
int main()
{
   int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

   struct gameState postG;
   struct gameState preG;

   unsigned seed;
   seed = time(0);
   srand(seed);

//int coppers[MAX_HAND];
//int silvers[MAX_HAND];
//int golds[MAX_HAND];

   int c, numOfTrials = 3000;
   for(c = 0;c< numOfTrials;c++)
   {
	memset(&preG, 23, sizeof(struct gameState)); 
	memset(&postG, 23, sizeof(struct gameState)); 
	int r = initializeGame(2, k, seed, &postG);
	assert(0,r,"initialize Game", preG, postG, c);
	int choice = rand() % 2;
	randomizer(&preG, &postG);
	memcpy(&preG, &postG, sizeof(postG));
//	printGameState(preG);
//	printGameState(postG);
//	r = baronEffect(choice, &postG, postG.whoseTurn);
	r = cardBaron(postG.whoseTurn, &postG, 0, choice);
	assert(0,r,"baronEffect Return Value", preG, postG, c);
	testResults(preG, postG, choice, c);

   }
return 0;
}


