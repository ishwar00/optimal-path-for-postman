#ifndef graph_impl 
#define graph_impl

#include<stdio.h>
#include<stdbool.h>
#include<iso646.h>
#include<stdlib.h>
#include<string.h>
#include"ANSI_Color.h"

struct location {
    int  label;
    int cost;
    char address[30];
    struct location* next;
};

typedef struct location location; 
typedef location*       location_ptr;

typedef struct {
    int V;
    int E;
    char** label_map;
    location_ptr* adj_list;
} graph;

typedef graph* graph_ptr;

void terminate(char str[]);

graph construct_empty_graph(FILE* );  //* constructs empty adjacent list for each node

void construct_graph(graph_ptr , FILE* );  //* Fills adjacent lists

location_ptr new_node(location );       //* creats node of 'location' type returns pointer to it

void label_location(location_ptr, graph_ptr);

void add_edge(location , location , graph_ptr ); //* creats undirected edge between u and v node

void print(graph, FILE*);

#endif // !graph  
