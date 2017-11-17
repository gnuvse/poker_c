// to-do
// добавить проверку на последовательность от 10 до короля!

// Перетасовка
void shuffle(int deck[][13]);
// Сдача игрокам
void deal(int deck[][13], int p1[][13], int p2[][13]);
void deal_after_cards_change(int deck[][13], int p2[][13]);
// Печать сдачи
void print_deal(const char *face[], const char *suit[], int p[][13]);
void print_deal_after_resubmission(int p[][13], const char *face[], const char *suit[], int assess);
// Количество повтряющихся карт у игроа
void repeat_card(int p[][13], int repeat_face[], int repeat_suit[]);
void repeat_card_after_resubmission(int p[][13], int repeat_face[], int repeat_suit[], int assess);

// Комбинации на номиналах карты
int combination_on_face(int repeat_face[], const char *face[]);
int combination_on_suit(int repeat_suit[]);
int combination_on_sequence(int repeat_face[]);
int max_on_3(int a, int b, int c);
int identify_power_hand(int a, int b);

// --
int assess_power_hand(int power_hand);
void get_new_card(int repeat_face[], const int count);
void marking_array(int repeat_face[], int count_mark, int size);
//--

void zeroing_a(int a[], int size);
void print_a(int a[], int size);
