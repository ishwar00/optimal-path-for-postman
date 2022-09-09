#include "graph_impl.h"
#include"route_optimizer.h"
#include"letter_manager.h"

void free_memory(graph G, letter_collection LC, PostManList PML) {
    for (int i = 0; i < G.V; ++i) {
        free(G.label_map[i]);
        location_ptr at = G.adj_list[i];
        while (at != NULL) {
            location_ptr store = at;
            at = at->next;
            free(store);
        }
    }

    for (PostMan* i = PML.list; i != NULL;) {
        PostMan* store = i->next;
        free(i->Route);
        free(i->LC.letters);
        free(i);
        i = store;
    }
    free(LC.letters);
    free(G.label_map);
    free(G.adj_list);
    return;
}


int main() {
    FILE* input = fopen("input.txt", "r");
    FILE* output = fopen("ouput.txt", "w");
    
    graph G = construct_empty_graph(input);
    construct_graph(&G, input);
    
    char post_office[30] = { 0 };
    if (fscanf(input, "%s", post_office) != 1) terminate("while reading post office");
    letter_collection LC = collect_letters(input);
    sort_letters(LC);

    PostManList PML = get_postmans(input);
    distribute_letters(LC, &PML);
    for (PostMan* i = PML.list; i != NULL; i = i->next) {
        printf("\n" GRN "searching optimal path for %s..." reset "\n", i->name);
        Find_Route(post_office, G, i);
        print_route(G, i, output);
        sort_letters_based_on_route(i, G);
        print_letters(i->LC, output);
    }
    free_memory(G, LC, PML);
    return 0;
}
