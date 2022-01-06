#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Reading_Input(char file_name[], int cost_matrix[][10], int number_of_routers) ///This function is for reading in cost matric from file and store that matrix in cost matrix array
{
    int i, j;
    FILE *file_read; ///Declaring file pointer
    file_read = fopen(file_name, "r"); ///Opening file using file pointer
    if(file_read == NULL) ///Checking if the file is opened or not
    {
        printf("error: unable to open file: %s\n", file_name); ///Printing out error message if the file is not opened properly
		exit(EXIT_FAILURE); ///Stopping the program if the file is n ot opened.
    }

    printf("\nReading in cost matrix from the file...\n");
    for(i = 1; i <= number_of_routers; i++) ///Reading in values from file and storing in cost matrix
    {
        for(j = 1; j <= number_of_routers; j++)
            fscanf(file_read, "%d", &cost_matrix[i][j]);
    }
    printf("File read is done.\n\n");

    return 0;
}

int Display_Cost_Matrix(int cost_matrix[][10], int number_of_routers, char first_node_character) ///This function is to display cost matrix
{
    int i, j;
    printf("\nThe cost matrix representation is displayed below.\n");
    for(i = 1; i <= number_of_routers; i++) ///Displaying the node characters in one row based on first node character inputted by user
        printf("     %c", first_node_character + (i - 1));
    printf("\n");
    for(i = 1; i <= number_of_routers; i++) ///Printing out cost matrix for each node in each iteration
    {
        printf("%c", first_node_character + (i - 1)); ///Displaying the node characters in each column based on first node character inputted by user
        for(j = 1; j <= number_of_routers; j++)
        {
            if(j == 1)
                printf("%5d", cost_matrix[i][j]);
            else
                printf("%6d", cost_matrix[i][j]);
        }
        printf("\n\n");
    }

    return 0;
}

int main()
{
    printf("+----------------------------------------------+\n");
	printf("|             Name: Utpal Kumar Dey            |\n");
	printf("|             Dijkstra Algorithm               |\n");
	printf("+----------------------------------------------+\n\n\n\n");

///Necessary variable declaration

    int number_of_routers, cost_matrix[10][10], i, j, k, link_state_table[10][10], node_flag[10], flag_count, previous_cost, previous_node;
    int starting_node, step_number, path_cost[10], current_i, current_j, temp_i, temp_j;
    char first_node_character, source_node, file_name[15], path_taken[10][10];
    struct node_track
    {
        char node_from;
        int i_from, j_from;
    };
     struct node_track tracker[10][10];

///Necessary variable declaration

///Reading in inputs

    printf("OSPF Link-State (LS) Routing:\n");
    printf("-----------------------------\n");

    printf("Enter the number of routers: "); ///Prompting for number of routers
    scanf("%d", &number_of_routers); ///Reading in number of routers
    printf("Enter filename with cost matrix values: "); ///Prompting for file name
    scanf("%s", file_name); ///Reading in file name

    Reading_Input(file_name, cost_matrix, number_of_routers); ///Calling Reading_Input() function for reading in cost matrix from file

    printf("Enter character representation of first node: "); ///Prompting for character representation of first node
    getchar(); ///Discarding extra character from terminal
    scanf("%c", &first_node_character); ///Reading in character representation of first node
    printf("Enter the source router: "); ///Prompting for source node
    getchar(); ///Discarding extra character from terminal
    scanf("%c", &source_node); ///Reading in first node

///Reading in inputs

///Displaying cost matrix

    Display_Cost_Matrix(cost_matrix, number_of_routers, first_node_character); ///Calling Display_Cost_Matrix() function to display the cost matrix

///Displaying cost matrix

///Initializing for Dijkstra algorithm

    starting_node = source_node - first_node_character + 1; ///Determining the starting node for the algorithm

    for(i = 1; i <= number_of_routers; i++) ///Initializig flags for all nodes
        if(i == starting_node)
            node_flag[i] = 1;
        else
            node_flag[i] = 0;

    for(i = 0; i <= number_of_routers; i++) ///Initializing link state table
    {
        for(j = 1; j <= number_of_routers; j++)
            link_state_table[i][j] = -1;
    }

///Initializing for Dijkstra algorithm


///Dijkstra algorithm starting...

    i = 1; ///Starting from step number 1
    previous_cost = 0; ///Initializing starting cost to 0
    previous_node = starting_node; ///Initializing starting node for the algorithm

    while(1)
    {
        for(j = 1; j <= number_of_routers; j++) ///Iterating through each node
        {
            if(!node_flag[j]) ///Checking if the current node is calculated or not
            {
                if(cost_matrix[previous_node][j] != -1) ///Checking if previous step is empty
                {
                    if(link_state_table[i-1][j] > 0 && link_state_table[i-1][j] < cost_matrix[previous_node][j] + previous_cost) ///Checking if previous step has lesser value than current calculated value for this position
                    {
                        link_state_table[i][j] = link_state_table[i-1][j]; ///Assigning previous step value to current step
                        tracker[i][j].node_from = tracker[i-1][j].node_from; ///Keeping track of the node from where this step is calculated
                        tracker[i][j].i_from = i - 1; ///Keeping track of the position of the node from where this step is calculated
                        tracker[i][j].j_from = j; ///Keeping track of the position of the node from where this step is calculated
                    }
                    else
                    {
                        link_state_table[i][j] = cost_matrix[previous_node][j] + previous_cost; ///Assigning newly calculated cost
                        tracker[i][j].node_from = first_node_character + previous_node - 1; ///Keeping track of the node from where this step is calculated
                        tracker[i][j].i_from = i - 1; ///Keeping track of the position of the node from where this step is calculated
                        tracker[i][j].j_from = previous_node; ///Keeping track of the position of the node from where this step is calculated
                    }
                }
                else if(link_state_table[i-1][j] > 0) ///If previous step has value
                {
                    link_state_table[i][j] = link_state_table[i-1][j]; ///Assigning previous step value to current step
                    tracker[i][j].node_from = tracker[i-1][j].node_from; ///Keeping track of the node from where this step is calculated
                    tracker[i][j].i_from = i - 1; ///Keeping track of the position of the node from where this step is calculated
                    tracker[i][j].j_from = j; ///Keeping track of the position of the node from where this step is calculated
                }
            }
        }
        flag_count = 0; ///Initializinf flag count to 0
        for(j = 1; j <= number_of_routers; j++) ///Couting how many nodes have been processed
        {
            if(node_flag[j])
                flag_count++;
        }
        if(flag_count == number_of_routers) ///If all the nodes have been processed then stop
            break;
        for(j = 1; j <= number_of_routers; j++) ///Assigning initial cost and node number for current node
        {
            if(link_state_table[i][j] != -1)
            {
                previous_cost = link_state_table[i][j];
                previous_node = j;
                break;
            }
        }
        for(j = 1; j <= number_of_routers; j++) ///Finding out minimum cost and node number for current node
        {
            if(link_state_table[i][j] != -1)
            {
                if(link_state_table[i][j] <= previous_cost)
                {
                    previous_cost = link_state_table[i][j];
                    previous_node = j;
                }
            }
        }
        node_flag[previous_node] = 1; ///Current node is being flagged for not to use in later calculation
        i++;
    }

    step_number = i; ///Getting step number from algorithm

    for(i = 1; i <= number_of_routers; i++) ///Each node is being processed through each iteration
    {
        path_cost[i] = 0; ///Initializing path cost for current node to 0
        k = 0;
        if(i != starting_node) ///Checking if the current node is not source node
        {
            path_taken[i][k] = first_node_character + i - 1; ///Assigning current node to shortest path string
            k++;
            for(j = 1; j <= step_number; j++) ///Processing each step in each iteration
            {
                if(!path_cost[i] && link_state_table[j][i] != -1) ///Finding out least cost for current node across that particular column in link state table
                {
                    path_cost[i] = link_state_table[j][i]; ///Assigning current least cost
                    current_i = j; ///Holding current position for later use
                    current_j = i; ///Holding current position for later use
                    path_taken[i][k] = tracker[current_i][current_j].node_from; ///Keeping track of the node from where this step has come
                }
                else if(path_cost[i] && link_state_table[j][i] != -1 && link_state_table[j][i] < path_cost[i]) ///Finding out least cost for current node across that particular column in link state table
                {
                    path_cost[i] = link_state_table[j][i]; ///Assigning current least cost
                    current_i = j; ///Holding current position for later use
                    current_j = i; ///Holding current position for later use
                    path_taken[i][k] = tracker[current_i][current_j].node_from; ///Keeping track of the node from where this step has come
                }
            }
            k++;
            while(current_i && current_j) ///Going back to previous node in each iteration
            {
                if(path_taken[i][k-1] != tracker[current_i][current_j].node_from) ///Checking if different node is found on the way to source
                {
                    path_taken[i][k] = tracker[current_i][current_j].node_from; ///Assigning different node on the way to shortest path string
                    k++;
                }
                temp_i = current_i;
                temp_j = current_j;
                current_i = tracker[temp_i][temp_j].i_from; ///Holding position for previous node to go backward
                current_j = tracker[temp_i][temp_j].j_from;///Holding position for previous node to go backward
            }
        }
        else ///If the current node is source node
        {
            path_taken[i][k] = source_node; ///Assigning source node to shortest path string
            k++;
        }
        path_taken[i][k] = '\0';
    }

///Dijkstra algorithm ending...


///Diplaying least cost and least cost path taken.

    for(i = 1; i <= number_of_routers; i++) ///Displaying least cost and least cost path taken for each node in each iteration
    {
        printf("%c ==> %c:\n", source_node, (first_node_character + i - 1)); ///Printing out source and destination node
        printf("path cost: %d\n", path_cost[i]); ///Priting out least cost between source and destination node
        printf("path taken: ");
        k = strlen(path_taken[i]);
        printf("%c", path_taken[i][k-1]); ///Printing out shortest path for current node
        for(j = k - 2; j >= 0; j--) ///Printing out shortest path for current node
        {
            printf(" --> %c", path_taken[i][j]); ///Printing out shortest path for current node
        }
        printf("\n\n");
    }

///Diplaying least cost and least cost path taken.

    return 0;
}
