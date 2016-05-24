#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct card_struct{
    int suit;
    int value;
    char char_suit;
    char char_value;
};
typedef struct card_struct Card_struct;

void new_deck(Card_struct deck[]);
void shuffle_deck(Card_struct shuffle_deck[],Card_struct shuffDeck[]);
void print_deck(Card_struct deck[]);
void convert_int_to_char(Card_struct deck[]);
void deal_deck(Card_struct shuffled[],char p1[],char p2[],char p3[],char p4[]);

int main()
{
    Card_struct deck[52];
    Card_struct shuffled[52];
    char p1[26];
    char p2[26];
    char p3[26];
    char p4[26];

    new_deck(deck);
    shuffle_deck(deck, shuffled);
    convert_int_to_char(shuffled);
    print_deck(shuffled);
    deal_deck(shuffled, p1, p2, p3, p4);

    return 0;
}

void deal_deck(Card_struct shuffled[],char p1[],char p2[],char p3[],char p4[])
{
    for(int i=0; i<13; i++)
    {
        p1[i*2] = shuffled[i*4].char_suit;
        p1[i*2+1] = shuffled[i*4].char_value;

        p2[i*2] = shuffled[i*4+1].char_suit;
        p2[i*2+1] = shuffled[i*4+1].char_value;

        p3[i*2] = shuffled[i*4+2].char_suit;
        p3[i*2+1] = shuffled[i*4+2].char_value;

        p4[i*2] = shuffled[i*4+3].char_suit;
        p4[i*2+1] = shuffled[i*4+3].char_value;

    }
    printf("p1:");
    for(int i=0; i<13; i++)
    {
        printf("%c%c",p1[i*2],p1[i*2+1]);
    }
    printf("\np2:");
    for(int i=0; i<13; i++)
    {
        printf("%c%c",p2[i*2],p2[i*2+1]);
    }
    printf("\np3:");
    for(int i=0; i<13; i++)
    {
        printf("%c%c",p3[i*2],p3[i*2+1]);
    }
    printf("\np4:");
    for(int i=0; i<13; i++)
    {
        printf("%c%c",p4[i*2],p4[i*2+1]);
    }
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
        r = rand();
        r = r%(51-i);

        shuffled[i].suit = deck[r].suit;
        shuffled[i].value = deck[r].value;

        deck[r].suit = deck[51-i].suit;
        deck[r].value = deck[51-i].value;
    }
    shuffled[51].suit=deck[0].suit;
    shuffled[51].value=deck[0].value;
    //shuffle klar
}

void convert_int_to_char(Card_struct deck[])
{
    for(int i=0;i<52;i++)
    {
        if(deck[i].value == 10)
            deck[i].char_value = 'A';
        else if(deck[i].value == 11)
            deck[i].char_value = 'B';
        else if(deck[i].value == 12)
            deck[i].char_value = 'C';
        else
            deck[i].char_value = deck[i].value + '0';

        deck[i].char_suit = deck[i].suit + '0';
    }
}

void print_deck(Card_struct deck[])
{
    for(int i=0;i<52;i++)
    {
        if(deck[i].char_suit == '0')
            printf("clubs %c%c\n",deck[i].char_suit,deck[i].char_value);
        else if(deck[i].char_suit == '1')
            printf("diamonds %c%c\n",deck[i].char_suit,deck[i].char_value);
        else if(deck[i].char_suit == '2')
            printf("hearts %c%c\n",deck[i].char_suit,deck[i].char_value);
        else if(deck[i].char_suit == '3')
            printf("spades %c%c\n",deck[i].char_suit,deck[i].char_value);
        else
            printf("bad shuffle");
    }
    printf("\n\n");
}
