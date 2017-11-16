#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// to-do
// добавить проверку на последовательность от 10 до короля!

// Перетасовка
void shuffle(int deck[][13]);
// Сдача игрокам
void deal(int deck[][13], int p1[][13], int p2[][13]);
// Печать сдачи
void print_deal(const char *face[], const char *suit[], int p[][13]);
// Количество повтряющихся карт у игроа
void repeat_card(int p[][13], int repeat_face[], int repeat_suit[]);

// Комбинации на номиналах карты
int combination_on_face(int repeat_face[], const char *face[]);
int combination_on_suit(int repeat_suit[]);
int combination_on_sequence(int repeat_face[]);
int max_on_3(int a, int b, int c);
int identify_power_hand(int a, int b);

// --
int assess_power_hand(int power_hand);
void get_new_card(int repeat_face[], const int count);
//--

void zeroing_a(int a[], int size);
void print_a(int a[], int size);


int main()
{
    // Card deck
    const char *suit[ 4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    const char *face[13] = {"Ace", "Two", "Three", "Four",
                      "Five", "Six", "Seven", "Eight",
                      "Nine", "Ten", "Jack", "Queen", "King"};

    // Data deck and players
    int deck[4][13] = {{0}};
    int p1[4][13] = {{0}};
    int p2[4][13] = {{0}};

    // Data for combination determination
    int repeat_face[13] = {0};
    int repeat_suit[4] = {0};


    // Arrays for testing
    //int test_face1[13] = {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
    //int test_face2[13] = {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
    //int test_face1[13] = {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2};
    //int test_face2[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 0, 0};
    //int test_face[13] = {0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //int test_suit[4] = {0, 0, 5, 0};

    srand(time(NULL));

    // Сдача карт
    shuffle(deck);
    deal(deck, p1, p2);


    //print_deal(face, suit, p1);
    printf("\n");

    //print_deal(face, suit, p2);
    int p_hand1;
    int p_hand2;

    printf("Player1:\n");
    print_deal(face, suit, p1);
    printf("\n");
    repeat_card(p1, repeat_face, repeat_suit);
    p_hand1 = max_on_3(combination_on_face(repeat_face, face),
                       combination_on_suit(repeat_suit),
                       combination_on_sequence(repeat_face));


    zeroing_a(repeat_face, 13);
    zeroing_a(repeat_suit, 4);
    printf("\n");
    printf("\n");


    printf("Player2:\n");
    print_deal(face, suit, p2);
    printf("\n");
    repeat_card(p2, repeat_face, repeat_suit);
    p_hand2 = max_on_3(combination_on_face(repeat_face, face),
                       combination_on_suit(repeat_suit),
                       combination_on_sequence(repeat_face));
    printf("\n");
    //print_a(repeat_face, 13);
    printf("\n");

    printf("\n");
    //print_a(repeat_suit, 4);
    printf("\n");

    /*printf("combin? %d\n", combination_on_face(repeat_face, face));


    printf("Flash? %d\n", combination_on_suit(repeat_suit));
    printf("Straight? %d\n", combination_on_sequence(repeat_face));*/
    printf("p1 = %d; p2 = %d\n", p_hand1, p_hand2);
    printf("Player%d win!!\n", identify_power_hand(p_hand1, p_hand2));

    printf("\n");
    printf("\n");
    printf("\n");

    printf("Asses power hand: p2 %d!!\n", assess_power_hand(p_hand2));



    return 0;
}

void shuffle(int deck[][13])
{
    int card, row, column;

    for (card = 1; card < 53; card++) {
        row = rand() % 4;
        column = rand() % 13;

        while (deck[row][column] != 0) {
            row = rand() % 4;
            column = rand() % 13;
        }
        deck[row][column] = card;
    }

    deck[row][column] = card;
}

void deal(int deck[][13], int p1[][13], int p2[][13])
{
    int card, row, column;

    for (card = 1; card < 53; card++)
        for (row = 0; row < 4; row++)
            for (column = 0; column < 13; column++)
                if (deck[row][column] == card) {
                    card % 2 == 0 ? (p1[row][column] =
                                     deck[row][column]) :
                                    (p2[row][column] =
                                     deck[row][column]);
                    /*printf("%5s of %-8s%c", face[column],
                           suit[row],card % 2 == 0 ? '\n' : '\t');*/
                }
}

int assess_power_hand(int power_hand)
{
    if (power_hand >= 2 && power_hand <= 14)
        return 3;
    else if (power_hand >= 15 && power_hand <= 46)
        return 1;
    else if (power_hand >= 82 && power_hand <= 94)
        return 2;
    else if (power_hand == 0)
        return 3;
    else
        return -1;

}

int identify_power_hand(int a, int b)
{
    if (a > b)
        return 1;
    if (a == b)
        return 0;
    else
        return 2;
}

int combination_on_sequence(int repeat_face[])
{
    int count = 0;
    int tmp;
    for (int i = 0; i < 13; i++)
        if (repeat_face[i] == 1) {
            for (int j = i; j < i + 5; j++)
                if (repeat_face[j] == 1) {
                    count++;
                    tmp = i;
                }
            break;
        }

    if (count == 5)
        return 100 + tmp;
    else
        return -1;
}

int combination_on_face(int repeat_face[], const char *face[])
{
    int power_hand = 0;
    int pair = 0;
    int triple = 0;
    for (int i = 0; i < 13; i++)
        if (repeat_face[i] >= 2) {
            switch(repeat_face[i]) {
                case 2:
                    printf("Player have pair: %s!\n", face[i]);
                    if (triple == 1)
                        return 200;

                    if (pair == 1)
                        power_hand += 20 + i;
                    else {
                        power_hand = 1 + i;
                        pair = 1;
                    }

                    if (i == 0)
                        power_hand += 13;

                    break;
                case 3:
                    if (pair == 1)
                        power_hand = 200;
                    else {
                        triple = 1;
                        power_hand = 1 + i + 80;
                    }
                    if (i == 0)
                        power_hand += 13;
                    printf("Player have triple: %s!\n", face[i]);
                    break;


                case 4:
                    printf("Player have cair: %s!\n", face[i]);
                    return 4 + i + 90;
                default:
                    printf("Erro!\n");
                    break;
            }
        }
    return power_hand;
}

int combination_on_suit(int repeat_suit[])
{
    for (int i = 0; i < 4; i++)
        if (repeat_suit[i] == 5)
            return 150;
    return -1;
}

void print_a(int a[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);
}

void print_deal(const char *face[], const char *suit[], int p[][13])
{
    for (int card = 1; card < 11; card++)
        for (int row = 0; row < 4; row++)
            for (int column = 0; column < 13; column++)
                if (p[row][column] == card)
                    printf("%5s of %-8s\n", face[column],
                            suit[row]);

}

void repeat_card(int p[][13], int repeat_face[], int repeat_suit[])
{
    for (int card = 1; card < 11; card++)
        for (int row = 0; row < 4; row++)
            for (int column = 0; column < 13; column++)
                if (p[row][column] == card) {
                    ++repeat_face[column];
                    ++repeat_suit[row];
                }
}

int max_on_3(int a, int b, int c)
{
    if (a > b && a > c)
        return a;
    else if (b > a && b > c)
        return b;
    else
        return c;
}

void zeroing_a(int a[], int size)
{
    for (int i = 0; i < size; i++)
        a[i] = 0;
}
