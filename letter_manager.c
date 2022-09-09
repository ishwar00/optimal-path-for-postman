#include"graph_impl.h"
#include"letter_manager.h"
#include"route_optimizer.h"


bool read_letter(letter* L, FILE* input) {
    if (fscanf(input, "%s %s %d",
        L->address,
        L->name,
        &L->stamp) != 3) terminate("while reading letters");
    if (L->stamp == -1)  return false;
    return true;
}

letter_collection collect_letters(FILE* input) {
    letter_collection LC = { NULL, 0 };
    LC.letters = (letter*)calloc(150, sizeof(letter));
    
    for (int i = 0; i < 150 and read_letter(&LC.letters[i], input); ++i) {
        LC.size++;
    }
    printf("\n" BLU "%d letters have been collected\n" reset, LC.size);
    if (LC.size == 75) {
        puts("\n" CYN "Only 150 letters are allowed rest will be discarded" reset);
        letter buffer;
        while (read_letter(&buffer, input));
    }
    return LC;
}

void put_into(letter* a, letter* b) {
    if (a != b) {
        a->stamp = b->stamp;
        strcpy(a->address, b->address);
        strcpy(a->name, b->name);
    }
}

void print_route(graph G, PostMan* PM, FILE* output) {
    fprintf(output, "\n%s will deliver through : ", PM->name);
    for (int i = 0; PM->Route[i] != -1; ++i) {
        fprintf(output, "%s %s", G.label_map[PM->Route[i]], (PM->Route[i + 1] != -1) ? "-> " : "\n");
    }
    fprintf(output,"distance needs to be travelled is %d Units\n", PM->dist_travel);
}

void print_letters(letter_collection LC, FILE* output) {
    fprintf(output, "letters to be delivered are : \n");
    for (int i = 0; i < LC.size; ++i) {
        fprintf(output, "%35s %s %d \n", LC.letters[i].address, LC.letters[i].name, LC.letters[i].stamp);
    }
}

void distribute_letters(letter_collection LC, PostManList* PML) {
    PostMan* store = PML->list;
    for (int i = 0; i < LC.size; ++i) {
        put_into(&store->LC.letters[store->LC.size++], &LC.letters[i]);
        store = store->next;
        if (store == NULL) store = PML->list;
    }
}
    
PostManList get_postmans(FILE* input) {
    PostManList PML = { 0, NULL };
    while (true) {
        PostMan* store = (PostMan*)calloc(1, sizeof(PostMan));
        fscanf(input, "%s", store->name);
        if (atoi(store->name)) {
            free(store);
            break;
        }
        store->LC.letters = (letter*)calloc(30, sizeof(letter));
        PML.No_PostMans++;
        store->next = PML.list;
        PML.list = store;
    }
    return PML;
}

void sort_letters(letter_collection LC) {
    for (int i = 0; i < LC.size; ++i) {
        for (int j = 0; j < LC.size - (1 + i); ++j) {
            if (LC.letters[j].stamp > LC.letters[j + 1].stamp) {
                letter store;
                put_into(&store, &LC.letters[j]);
                put_into(&LC.letters[j], &LC.letters[j + 1]);
                put_into(&LC.letters[j + 1], &store);
            }
        }
    }
}

void sort_letters_based_on_route(PostMan* PM, graph G) {
    for (int i = 0, counter = 0; PM->Route[i] != -1; ++i) {
        if (must_pass[i]) {
            for (int j = counter; j < PM->LC.size; ++j) {
                if (strcmp(G.label_map[i], PM->LC.letters[j].address)) {
                    letter buffer;
                    put_into(&buffer, &PM->LC.letters[counter]);
                    put_into(&PM->LC.letters[counter], &PM->LC.letters[j]);
                    put_into(&PM->LC.letters[j], &buffer);
                    counter++;
                }
            }
        }
    }
}
