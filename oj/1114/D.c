#include <stdio.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

typedef struct {
    int type;
    int rank;
} TR, *pTR;

int read_hand(int num_in_rank[], int num_in_suit[]);
void judge_hand(pTR result, const int num_in_rank[], const int num_in_suit[]);

int main(void)
{
    int num_in_rank[NUM_RANKS];
    int num_in_suit[NUM_SUITS];

    TR result;

    if (!read_hand(num_in_rank, num_in_suit)) {
        puts("Failed to read one hand");
        return 0;
    } 

    judge_hand(&result, num_in_rank, num_in_suit);

    switch (result.type) {
    case 0:
        printf("Flush %d\n", result.rank);  break;
    case 1:
        printf("Straight %d\n", result.rank);   break;
    case 2:
        printf("Flush-Straight %d\n", result.rank);   break;
    default:
        printf("Others %d\n", result.rank);
    }

    return 0;
}

int read_hand(int num_in_rank[], int num_in_suit[])
{
    char rank_ch, suit_ch;

    int cards_read = 0;
    int rank, suit;

    int readed[NUM_SUITS][NUM_RANKS] = { 0 };

    for (rank = 0; rank < NUM_RANKS; rank++)
        num_in_rank[rank] = 0;

    for (suit = 0; suit < NUM_SUITS; suit++)
        num_in_suit[suit] = 0;

    while (cards_read < NUM_CARDS) {
        suit_ch = getchar();
        switch (suit_ch) {
        case 's':  case 'S':  suit = 0;  break;
        case 'h':  case 'H':  suit = 1;  break;
        case 'c':  case 'C':  suit = 2;  break;
        case 'd':  case 'D':  suit = 3;  break;
        default:   suit = -1;
        }
        rank_ch = getchar();
        switch (rank_ch) {
        case '2':    rank = 0;       break;
        case '3':    rank = 1;       break;
        case '4':    rank = 2;       break;
        case '5':    rank = 3;       break;
        case '6':    rank = 4;       break;
        case '7':    rank = 5;       break;
        case '8':    rank = 6;       break;
        case '9':    rank = 7;       break;
        case 't':  case 'T':  rank = 8;  break;
        case 'j':  case 'J':  rank = 9;  break;
        case 'q':  case 'Q':  rank = 10; break;
        case 'k':  case 'K':  rank = 11; break;
        case 'a':  case 'A':  rank = 12; break;
        default:      rank = -1;
        }

        getchar();

        if (suit == -1 || rank == -1) {
            printf("%c%c is invalid\n", suit_ch, rank_ch);
            break;
        }

        if (readed[suit][rank]) {
            printf("%c%c is already existed\n", suit_ch, rank_ch);
            break;
        }

        num_in_suit[suit]++;
        num_in_rank[rank]++;
        readed[suit][rank] = 1;
        cards_read++;
    }

    if (cards_read == NUM_CARDS)
        return 1;   // succeeded
    else
        return 0;   // failed
}


void judge_hand(pTR result, const int num_in_rank[], const int num_in_suit[])
{
    int rank = 0;
    int Flush = 0, Straight = 0;
    for(int i = 0; i < NUM_RANKS; i++)
    {
        rank += num_in_rank[i] * (i + 2);
    }
    result->rank = rank;

    for(int i = 0; i < NUM_SUITS; i++)
    {
        if(num_in_suit[i] == NUM_CARDS)
        {
            Flush = 1;
            break;
        }
    }
    int status = 0, count = 0;
    for(int i = 0; i < NUM_RANKS; i++)
    {
        if(num_in_rank[i] != 0 && status == 0)
        {
            status = 1;
            count++;
            continue;
        }

        if(num_in_rank[i] != 0 && status == 1)
        {
            count++;
            continue;
        }

        if(num_in_rank[i] == 0 && status == 1)
        {
            break;
        }
    }
    
    if(count == 5) Straight = 1;

    if(Flush==0 && Straight==0) result->type = 3;
    if(Flush==1 && Straight==0) result->type = 0;
    if(Flush==0 && Straight==1) result->type = 1;
    if(Flush==1 && Straight==1) result->type = 2;

    return;
}

