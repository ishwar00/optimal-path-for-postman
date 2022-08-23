
#ifndef route_optimizer
#define route_optimizer
#include"graph_impl.h"
#include"letter_manager.h"


void initialize(int A[]);
void label_letters(letter_collection LC, graph G);
int label_start(char S[], graph G);
void Find_Route(char S[], graph G, PostMan*);
void PDO(int S, graph G, int Route[], int pre_node);
// void PDO(int S, graph G, int Route[]);

#endif //!   route optimizer  