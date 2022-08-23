#ifndef letter_manager 
#define letter_manager
#include"graph_impl.h"

extern bool must_pass[200];


typedef struct {
    char address[30];
    char name[30];
    int stamp;
} letter;

typedef struct {
    letter* letters;
    int size;
} letter_collection;

typedef struct PostMan {
    int* Route;
    char name[30];
    int dist_travel;
    letter_collection LC;
    struct PostMan* next;
} PostMan;

typedef struct {
    int No_PostMans;
    PostMan* list;
} PostManList;

PostManList get_postmans(FILE*);

bool read_letter(letter*, FILE*);

void distribute_letters(letter_collection , PostManList*);

letter_collection collect_letters(FILE* input);

void sort_letters(letter_collection LC);

void put_into(letter*, letter*);

void print_route(graph, PostMan*, FILE*);

void print_letters(letter_collection, FILE*);

void sort_letters_based_on_route(PostMan*, graph);




#endif // !letter   