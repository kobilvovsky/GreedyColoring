//
//  main.c
//  GreedyColoring
//
//  Created by Kobi Lvovsky on 12/12/2019.
//  Copyright © 2019 Computer Science. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

enum Colors {NOCOLOR = 0, Black = 1, White = 2, Grey = 3, Red = 4, Green = 5, Blue = 6, Yellow = 7, Orange = 8, Purple = 9, Pink = 10, Brown = 11, Violet = 12};

typedef struct Interval {
    int begin;
    int end;
    int degree;
    enum Colors color;
    struct Interval **next;
} Interval;

typedef struct Graph {
    Interval *array;
    int vertices;
    int edges;
    int max_deg;
    int min_deg;
    int chrom_num;
} Graph;

void GreedyColoring(void);
void print_intervals(Graph *G, int size);
int partition (Interval *arr, int low, int high);
void quick_sort(Interval *arr, int low, int high);
void swap(Interval *a, Interval *b);
void print_graph_data(Graph *G);

int main() {
    GreedyColoring();
}

void GreedyColoring() {
    Graph G;
    int k;
    int i;
    int j;
    int q;
    
    printf("Please input k:\n");
    scanf("%d", &k);
    
    G.min_deg = 0;
    G.max_deg = 0;
    G.vertices = k;
    G.chrom_num = 0;
    G.array = (Interval*) malloc (G.vertices * sizeof(Interval));// allocation of k intervals
    for (i = 0; i < k; i++) {
        G.array[i].next = (Interval**) malloc ((G.vertices-1) * sizeof(Interval*));
        G.array[i].color = 0;
        for (j = 0; j < k-1; j++) {
            G.array[i].next[j] = NULL;
        }
        G.array[i].degree = 0;
    }
    
    printf("You will now be asked to to insert a family of %d intervals:\n", k);
    
    i = 0;
    printf("Interval Number %d: ", i+1);
    scanf("%d %d", &G.array[i].begin, &G.array[i].end);
    i++;
    while (i < k) {
        printf("Interval Number %d: ", i+1);
        scanf("%d %d", &G.array[i].begin, &G.array[i].end);
        i++;
    }
    print_intervals(&G, k);
    quick_sort(G.array, 0, k-1);
    printf("The intervals in sorted order:\n");
    print_intervals(&G, k);
    i = 0;
    while (i < k) {
        if (i == 0) {
            G.array[i].color = 1;
        }
        for (q = i+1; q < k; q++) {
            if(G.array[i].end >= G.array[q].begin) {
                G.array[i].next[G.array[i].degree++] = &G.array[q];
                G.array[q].degree++;
                G.edges++;
                if (G.array[i].color == 0 && G.array[q].color == 0) {
                    G.array[i].color = 1;
                    G.array[q].color = 2;
                }
                else if (G.array[i].color != 0 && G.array[q].color == 0) {
                    G.array[q].color = 1;
                }
                else
                    if (G.array[i].color != 0 && G.array[q].color == G.array[i].color) {
                        G.array[q].color = G.array[q].degree+1;
                    }
            }
            
        }
        if (G.chrom_num <= G.array[i].color) {
            G.chrom_num = G.array[i].color;
        }
        if (G.max_deg <= G.array[i].degree) {
            G.max_deg = G.array[i].degree;
        }
        else {
            if (i == 0) {
                G.min_deg = G.array[i].degree;
            }
            else if (G.min_deg >= G.array[i].degree) {
                G.min_deg = G.array[i].degree;
            }
        }
        i++;
    }
    j=1;
    while (j <= G.chrom_num) {
        printf("{");
        for (i=0; i<k; i++) {
            if(G.array[i].color == j) {
                printf("[%d,%d], ", G.array[i].begin,G.array[i].end);
            }
        }
        printf("} = %d, ", j);
        j++;
    }
    printf("\n");
    print_graph_data(&G);
}


void print_graph_data(Graph *G) {
    printf("Max Degree of the Graph: %d\n", G->max_deg);
    printf("Min Degree of the Graph: %d\n", G->min_deg);
    printf("Number of Edges in the Graph: %d\n", G->edges);
    printf("Number of Vertices in the Graph: %d\n", G->vertices);
    printf("The Graph Chromatic Number is: %d\n", G->chrom_num);
}

void print_intervals(Graph *G, int size) {
    int i;
    printf("The interval family is:\n");
    for (i = 0; i < size-1; i++) {
        printf("[%d, %d], ", G->array[i].begin, G->array[i].end);
    }
    printf("[%d, %d]\n", G->array[i].begin, G->array[i].end);
}



int partition (Interval *arr, int low, int high)
{
    int pivot = arr[high].begin;    // pivot
    int i = (low - 1);  // Index of smaller element
  
    for (int j = low; j <= high-1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j].begin < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i + 1);
}
  

void quick_sort(Interval *arr, int low, int high)
{
    if (low < high)
    {
        int part_index = partition(arr, low, high);
        quick_sort(arr, low, part_index - 1);
        quick_sort(arr, part_index + 1, high);
    }
}


void swap(Interval *a, Interval *b)
{
    Interval temp = *a;
    *a = *b;
    *b = temp;
}
