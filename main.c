#include <stdio.h>
#include <stdlib.h>

// The output array shoud be dataArray[dateTime][frequency]
int (*array_from_file(char *filePath))[2];

// The flow can be calculated using calculus Q=dV/dt out array shoud be flowArray[dateTime][flow]
double *flow_array(int *dataArray);

// This function takes the avage flow in a given time
double avage_flow(int startDateTime, int endDateTime, double *flowArray);

// This function gives the max flow in a given time
double max_flow(int startDateTime, int endDateTime, double *flowArray);

// This function gives the min flow in a given time
double min_flow(int startDateTime, int endDateTime, double *flowArray);

// This function outputs an array with the start and end dateTime of flow beieng above threshold overflowArray[overflowStartDateTime,overflowEndDateTime]
double *overflow_accurencens(int startDateTime, int endDateTime, double threshold, double *flowArray);

// Coud use https://gr-framework.org/c.html for drawing graphs or 
void draw_graph(double *array);

int main(void) {
    int (*array)[2];


    array = array_from_file("data.txt");

    for (int i = 0; i < 5; i++) {
        printf("%d %d\n", array[i][0], array[i][1]);
    }

    return 0;
}

int (*array_from_file(char *filePath))[2] {
    int time, frequency;
    int lines = 0;
    char ch;

    // Open the data file in read mode
    FILE *file = fopen(filePath, "r");

    // Buffer to store the lines
    char line[25];

    // Error handling
    if (file == NULL) {
        printf("Error reading file\n");
        exit(EXIT_FAILURE);
    }

    // Calculates the number of lines
    // Check if end of file
    while (!feof(file)) 
    {
        // Get next char in file
        ch = fgetc(file);

        // Checks if the char is a newline
        if (ch == '\n') {
            lines++;
        }
    }

    int (*array)[2] = malloc(sizeof(int) * lines * 2);

    if (array == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }

    // Reset the file pointer
    rewind(file);
    
    for (int i = 0; i < lines; i++){
        fgets(line, sizeof(line), file);
        sscanf(line, "%d %d", &time, &frequency);
        array[i][0] = time;
        array[i][1] = frequency;
    }

    fclose(file);

    return array;
}