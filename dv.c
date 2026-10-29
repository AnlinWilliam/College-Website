#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 10              
#define INFINITY INT_MAX      

struct Node {
    int distance[MAX_NODES];    
    int next_hop[MAX_NODES];     
};

void initialize(struct Node nodes[], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (i == j) {
                
                nodes[i].distance[j] = 0;
             
                nodes[i].next_hop[j] = j;
            } else {
                
                nodes[i].distance[j] = INFINITY;
                
                nodes[i].next_hop[j] = -1;
            }
        }
    }
}

void print_routing_tables(struct Node nodes[], int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        printf("\nRouting table for node %d:\n", i);
        printf("Destination\tDistance\tNext Hop\n");

        for (int j = 0; j < num_nodes; j++) {
            printf("%d\t\t", j);

            if (nodes[i].distance[j] == INFINITY) {
                printf("INF\t\t");
            } else {
                printf("%d\t\t", nodes[i].distance[j]);
            }

            printf("%d\n", nodes[i].next_hop[j]);
        }
    }
}

void update_routing_table(struct Node nodes[], int num_nodes,
                          int adjacency_matrix[][MAX_NODES]) {

    int updated;
    int iteration = 0;

    do {
        updated = 0;
        iteration++;

        for (int i = 0; i < num_nodes; i++) {

            for (int j = 0; j < num_nodes; j++) {

                if (i != j && adjacency_matrix[i][j] != INFINITY) {

                    for (int k = 0; k < num_nodes; k++) {

                        if (nodes[j].distance[k] == INFINITY)
                            continue;

                        if (nodes[i].distance[k] >
                            nodes[j].distance[k] + adjacency_matrix[i][j]) {

                            nodes[i].distance[k] =
                                nodes[j].distance[k] + adjacency_matrix[i][j];

                            nodes[i].next_hop[k] = j;

                            updated = 1;
                        }
                    }
                }
            }
        }

        printf("\nAfter iteration %d:\n", iteration);
        print_routing_tables(nodes, num_nodes);

    } while (updated);  
}

int main() {
    struct Node nodes[MAX_NODES];
    int num_nodes;
    int adjacency_matrix[MAX_NODES][MAX_NODES];

    printf("Enter number of nodes (max %d): ", MAX_NODES);
    scanf("%d", &num_nodes);

    if (num_nodes <= 0 || num_nodes > MAX_NODES) {
        printf("Invalid number of nodes.\n");
        return 1;
    }

    printf("Enter the adjacency matrix (use %d for infinity):\n", INFINITY);

    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            scanf("%d", &adjacency_matrix[i][j]);

            if (i == j) {
                adjacency_matrix[i][j] = 0;
            }
        }
    }

    initialize(nodes, num_nodes);

    // Set initial direct links
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            if (adjacency_matrix[i][j] != INFINITY && i != j) {
                nodes[i].distance[j] = adjacency_matrix[i][j];
                nodes[i].next_hop[j] = j;
            }
        }
    }

    printf("\nInitial routing tables:\n");
    print_routing_tables(nodes, num_nodes);

    // Run Distance Vector algorithm
    update_routing_table(nodes, num_nodes, adjacency_matrix);

    printf("\nFinal routing tables:\n");
    print_routing_tables(nodes, num_nodes);

    return 0;
}
