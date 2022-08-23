#include"route_optimizer.h"
#include"letter_manager.h"
#include"graph_impl.h"

int  value[200];
int  route[200];
bool must_pass[200];
int  value_mrk = 0;
int  route_ptr = 0;
int  MP_V      = 0;
int  begin     = 0;
long long min_cost = __INT64_MAX__;
long long cur_cost = 0;
long long travelled = 0;
long long comb = 0;


void initialize(int Route[]) {
    min_cost  = __INT64_MAX__;
    cur_cost  = 0;
    value_mrk = 0;
    route_ptr = 0;
    MP_V      = 0;
    begin = 0;
    travelled = 0;

    for (int i = 0; i < 200; ++i) {
        Route[i] = route[i] = value[i] = -1;
        must_pass[i] = false;
    }
}


void label_letters(letter_collection LC, graph G) {
    for (int i = 0; i < LC.size; ++i) {
        for (int j = 0; j < G.V; ++j) {
            if (not(strcmp(LC.letters[i].address, G.label_map[j]))) {
                if (must_pass[j]) {
                    printf("\n" CYN "input might contain duplic letter %s %s %d" reset "\n", LC.letters[i].address, LC.letters[i].name, LC.letters[i].stamp);
                } else {
                    must_pass[j] = true;
                    MP_V++;
                }
                break;
            }
        }
    }
}

int label_start(char S[], graph G) {
    for (int i = 0; i < G.V; ++i) {
        if (not(strcmp(S, G.label_map[i]))) {
            return i;
        }
    }
}

void PDO(int S, graph G, int Route[], int pre_node) {
    travelled++;
    if (min_cost > cur_cost) {
        bool flag = false;
        if (value[S] == -1) {
            value[S] = value_mrk++;                 //* assigning value to node
            flag = true;
            if (must_pass[S])   MP_V--;
        }
        route[route_ptr++] = S;
        if (MP_V != 0 or S != begin) {
            location_ptr it = G.adj_list[S];
            while (it != NULL) {
                if (value[S] > value[it->label] and (it->label != pre_node or must_pass[S])) { //* one more improvement
                    cur_cost += it->cost;
                    PDO(it->label, G, Route, S);
                    cur_cost -= it->cost;
                }
                it = it->next;
            }
        } else {
            printf("\ntravelled : %lld\n", travelled);
            for (int i = 0; i < 200; ++i) Route[i] = -1;
            for (int i = 0; i != route_ptr; ++i) {
                Route[i] = route[i];
                printf(WHT"%s"CYN" -> " reset, G.label_map[Route[i]]);
            }
            puts("");
            min_cost = cur_cost;
        }
        if (flag) {
            value[S] = -1;
            value_mrk--;
        }
        if (must_pass[S] and flag) MP_V++;
        route_ptr += -1;
        route[route_ptr] = -1;
    }
}


void Find_Route(char S[], graph G, PostMan* PM) {
    PM->Route = (int*)calloc(200, sizeof(int));
    initialize(PM->Route);
    begin = label_start(S, G);
    // MP_V = PM->LC.size;
    label_letters(PM->LC, G);
    PDO(begin, G, PM->Route, begin);
    PM->dist_travel = min_cost;
    printf("\ntravelled : %lld\n", travelled);
}

