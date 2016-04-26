#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct card_struct{
    int suit;
    int value;
};
typedef struct card_struct Card_struct;

void new_deck(Card_struct deck[]);
void shuffle_deck(Card_struct shuffle_deck[],Card_struct shuffDeck[]);
void print_deck(Card_struct deck[]);

int main()
{
    Card_struct deck[52];
    Card_struct shuffled[52];

    new_deck(deck);
    shuffle_deck(deck, shuffled);
    print_deck(shuffled);

    return 0;
}

void new_deck(Card_struct deck[])
{
    int i=0;
    int j=0;
    int k=0;

    for(i=0;i<4;i++)
    {
        for(j=0;j<13;j++)
        {
            deck[k].suit=i;     //0 Klöver 1 Ruter 2 Hjärter 3 Spader
            deck[k].value=j;
            k++;
        }
    }
}

void shuffle_deck(Card_struct deck[], Card_struct shuffled[])
{
    int i=0;
    int r;

    srand(time(NULL));

    //Fisher-Yates shuffle
    for(i=0;i<51;i++)   //bara 51 ggr, 52'a kortet tilldelas sist.
    {
        r=rand();
        r=r%(51-i);

        shuffled[i].suit=deck[r].suit;
        shuffled[i].value=deck[r].value;

        deck[r].suit=deck[51-i].suit;
        deck[r].value=deck[51-i].value;
    }
    shuffled[51].suit=deck[0].suit;
    shuffled[51].value=deck[0].value;
    //shuffle klar
}

void print_deck(Card_struct deck[])
{
    for(int i=0;i<52;i++)
    {
        if(deck[i].suit == 0)
            printf("clubs %d\n",deck[i].value+2);
        else if(deck[i].suit == 1)
            printf("diamonds %d\n",deck[i].value+2);
        else if(deck[i].suit == 2)
            printf("hearts %d\n",deck[i].value+2);
        else
            printf("spades %d\n",deck[i].value+2);
    }
    printf("\n\n");
}
