#include"graph_impl.h"
#include"letter_manager.h"
#include"route_optimizer.h"

void terminate(char str[]) {
    printf("Oops! unexpected data in input stream > ....." CYN "%s" reset ".... <\n", str);
    puts(CYN "Aborting..." reset);
    exit(1);
}

graph construct_empty_graph(FILE* input) {
    graph G = { 0, 0, NULL, NULL };
    if (fscanf(input, "%d", &G.V) != 1) terminate("while reading V");
    G.adj_list  = (location_ptr*)calloc(G.V, sizeof(location_ptr));
    G.label_map = (char**)       calloc(G.V, sizeof(char*));
    printf(GRN "Done constructing empty graph with " YEL "%d vertices\n" reset, G.V);
    return G;
}

location_ptr new_node(location v) {
    location_ptr store = (location_ptr)calloc(1, sizeof(location));
    strcpy(store->address, v.address);
    store->label = v.label;
    store->cost = v.cost;
    return store;
}

void add_edge(location u, location v, graph* G) {
    location_ptr store = new_node(v);
    store->next = G->adj_list[u.label];
    G->adj_list[u.label] = store;

    store = new_node(u);
    store->next = G->adj_list[v.label];
    G->adj_list[v.label] = store;
}

void label_location(location* u, graph* G) {     
    int i = 0;
    for (; i < G->V and G->label_map[i] != NULL; ++i) {
        if (not(strcmp(G->label_map[i], u->address))) {
            u->label = i;
            return;
        }
    }
    if (i < G->V ) {
        G->label_map[i] = strdup(u->address);
        u->label = i;
    }
}

void construct_graph(graph* G, FILE* input) {
    int cost = 0;
    while (true) {
        location u = { 0, 0, { 0 }, NULL };
        location v = { 0, 0, { 0 }, NULL };
        if (fscanf(input, "%d", &cost) != 1) {
            char buffer[100];
            fscanf(input, "%s", buffer);
            break;
        }
        if (fscanf(input, "%s", v.address) != 1) terminate("while reading edge");
        if (fscanf(input, "%s", u.address) != 1) terminate("while reading edge");
        u.cost = v.cost = cost;
        label_location(&u, G);
        label_location(&v, G);
        add_edge(u, v, G);
        G->E++;
    }
    printf("\n"GRN "Done! reading locations with " YEL "%d edges\n" reset, G->E) ;
}

void print(graph Graph, FILE* output) {
    fprintf(output, "adjacent lists of locations \n");
    for (int i = 0; i < Graph.V; ++i) {
        fprintf(output, " %-19s ->  ", Graph.label_map[i]);
        location_ptr at = Graph.adj_list[i];
        while (at != NULL) {
            fprintf(output, "( %-16s, %-3d )  ", at->address, at->cost);
            at = at->next;
        }
        fputs("\n", output);
    }
    printf("\n"GRN "Done printing graph!\n" reset);
}
