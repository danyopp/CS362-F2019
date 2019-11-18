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
printf("Current Cards in hand: \n");
int a = 0, b = 0 ;

for(b=0; b < G.numPlayers; b++)
{
	printf("Player %d Cards: \n", b+1);
	printf("Current Cards in hand: ");
	for(a=0; a < G.handCount[b]; a++)
		{
		printf("%d ", G.hand[b][a]);
		}
	printf("\n");
	printf("Current Cards in deck: ");
	for(a=0; a < G.deckCount[b]; a++)
		{
		printf("%d ", G.deck[b][a]);
		}
	printf("\n");
	printf("Current Cards in discard ");
	for(a=0; a < G.discardCount[b]; a++)
		{
		printf("%d ", G.discard[b][a]);
		}
	printf("\n");
}
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

	//make sure minion is in hand of current player
	int foundMinion = 0;
	for(a=0 ; a < postG->handCount[postG->whoseTurn] ; a++)
	  {
		if( postG->hand[postG->whoseTurn][a] == tribute)
		{	foundMinion = 1;} 
	  }
	if (foundMinion == 0)
  	  {
		//add baron to a random card in players hand
		postG->hand[postG->whoseTurn][rand() % postG->handCount[postG->whoseTurn]] = tribute; 
	  }		

}



// "" struct struct trialnum
void testResults(struct gameState preG, struct gameState G, int nextplayer, int trialNum)
{
	//Test results for expected outcome
	
	//nextplayers deckcount > 1
	//discard 2 cards , else discard one
	//No cards avalibl from next player
	if(preG.deckCount[nextplayer] + preG.discardCount[nextplayer] == 0)
	{
		assert(preG.numActions, G.numActions, "Result0: No cards to draw; Actions not the same", preG, G, trialNum);
		assert(preG.coins, G.coins, "Result0: No cards to draw; Coins not the same", preG, G, trialNum);
		assert(preG.handCount[preG.whoseTurn], G.handCount[G.whoseTurn], "Result0: No cards to draw; Hand count not the same", preG, G, trialNum);

	}

	//One card only avalible from nextplayer
	else if(preG.deckCount[nextplayer] + preG.discardCount[nextplayer] == 1)
	{
		//check deckcount = 0; discard = 1
		int cardFound;
		if(preG.deckCount[nextplayer]!= 0)
		{	cardFound = preG.deck[nextplayer][0];		}
		else
		{	cardFound = preG.discard[nextplayer][0];	}		

		if(cardFound >= 0 && cardFound <= 3)
		{
		   //victory cards
		   assert(preG.handCount[preG.whoseTurn]+2, G.handCount[G.whoseTurn], "Result1: only one card avalible from next player; Handcount should increase by 2", preG, G, trialNum);     	
		   assert(preG.coins, G.coins, "Result1: only one card avalible from next player; treasures not increase", preG, G, trialNum);     	
		   assert(preG.numActions , G.numActions, "Result1: only one card avalible from next player; actions should not increase", preG, G, trialNum);     	
		}
		if(cardFound >= 4 && cardFound <= 6)
		{
		   //treasure cards
		   assert(preG.handCount[preG.whoseTurn], G.handCount[G.whoseTurn], "Result1: only one card avalible from next player; Handcount should not increase", preG, G, trialNum);     	
		   assert(preG.coins + 2, G.coins, "Result1: only one card avalible from next player; treasures should increase by 2", preG, G, trialNum);     	
		   assert(preG.numActions, G.numActions, "Result1: only one card avalible from next player; actions should not increase", preG, G, trialNum);     	

		}
		if(cardFound >= 7 && cardFound <= 26)
		{
		   //actions card2
		   assert(preG.handCount[preG.whoseTurn], G.handCount[G.whoseTurn], "Result1: only one card avalible from next player; Handcount should not increase", preG, G, trialNum);     	
		   assert(preG.coins , G.coins, "Result1: only one card avalible from next player; treasures should not increase", preG, G, trialNum);     	
		   assert(preG.numActions + 2, G.numActions, "Result1: only one card avalible from next player; actions should increase by 2", preG, G, trialNum);     	
		}
	}

	//two or more cards avalible
	else if(G.deckCount[nextplayer] + G.discardCount[nextplayer] >= 2) 
	{
		int cardFound, cardFound2;
		int addHandCount = 0, addtreasure = 0, addActions = 0;
		if(preG.deckCount[nextplayer]>= 2)
		{	cardFound = preG.deck[nextplayer][0];
			cardFound2 = preG.deck[nextplayer][1];	
		}
		if(cardFound == cardFound2)
		{
			cardFound2 = -1;
		}
 
		if(cardFound >= 0 && cardFound <= 3)
		{
		   //victory card
		   addHandCount += 2;
		}
		if(cardFound >= 4 && cardFound <= 6)
		{
		   //treasure cards
		   addtreasure += 2;
		}
		if(cardFound >= 7 && cardFound <= 26)
		{
		   //actions card2
		   addActions += 2;
	 	}
	
		if(cardFound2 >= 0 && cardFound2 <= 3)
		{
		   //victory cards
		   addHandCount += 2;   
		}
		if(cardFound2 >= 4 && cardFound2 <= 6)
		{
		   //treasure cards
		   addtreasure += 2;
		}
		if(cardFound2 >= 7 && cardFound2 <= 26)
		{
		   //actions card2
		   addActions += 2;  
		}   
		   
		   assert(preG.handCount[preG.whoseTurn] + addHandCount, G.handCount[G.whoseTurn], "Result2:  Handcount incorrect", preG, G, trialNum);     	
		   assert(preG.coins + addtreasure , G.coins, "Result2: treasures incorrect", preG, G, trialNum);     	
		   assert(preG.numActions + addActions, G.numActions, "Result2: actions incorrect", preG, G, trialNum);     	
		
	
	
	}
return;
}




int main()
{
   int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

   struct gameState postG;
   struct gameState preG;

   unsigned seed;
   seed = time(0);
   srand(seed);

   int c, numOfTrials = 3000;
   for(c = 0;c< numOfTrials;c++)
   {
	memset(&preG, 23, sizeof(struct gameState)); 
	memset(&postG, 23, sizeof(struct gameState)); 
	int r = initializeGame(2, k, seed, &postG);
	assert(0,r,"initialize Game", preG, postG, c);


	//randomize hands and decks
	randomizer(&preG, &postG);
	//Copy to pre gamestate
	memcpy(&preG, &postG, sizeof(postG));

//get current player and nextplayer
	int curplayr = postG.whoseTurn;
	int nextplayr;
	if(curplayr == postG.numPlayers-1)
	{  nextplayr = 0; }
 	else
	{ nextplayr = postG.whoseTurn+1; }
//	printf("totalplayers: %d currentplayer: %d nextplayer: %d\n", postG.numPlayers, curplayr, nextplayr);


//	printGameState(preG);
//	printGameState(postG);
	r = tributeEffect( &postG, nextplayr, curplayr);

//	printGameState(preG);
//	printGameState(postG);
	

	assert(0,r,"tributeEffect Return Value", preG, postG, c);
	testResults(preG, postG, nextplayr , c);

   }
return 0;
}


