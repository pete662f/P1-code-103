#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 2

// The output array shoud be dataArray[dateTime][rotations]
int (*array_from_file(char *filePath, int *size))[ARRAY_SIZE];

// The flow can be calculated using calculus Q=dV/dt out array shoud be flowArray[dateTime][flow]
double (*flow_array(int (*dataArray)[ARRAY_SIZE], int size))[ARRAY_SIZE];

// The height of the water can be calculated using the formula h=(Q^2)/(2*g*A^2) out array shoud be heightArray[dateTime][height]
double (*height_array(double (*flowArray)[ARRAY_SIZE], int size))[ARRAY_SIZE];

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
    // Declare a two dimensional array, without a set length.
    int (*array)[ARRAY_SIZE];
    double (*flowArray)[ARRAY_SIZE];
    double (*heightArray)[ARRAY_SIZE];
    int size;

    array = array_from_file("data.txt", &size);

    flowArray = flow_array(array, size);

    heightArray = height_array(flowArray, size);

    // Prints time and rotations.
    for (int i = 0; i < size; i++) {
        printf("%d %d\n", array[i][0], array[i][1]);
    }

    for (int i = 0; i < size; i++) {
        printf("%f %f\n", flowArray[i][0], flowArray[i][1]);
    }
    
    for (int i = 0; i < size; i++) {
        printf("%f %f\n", heightArray[i][0], heightArray[i][1]);
    }

    free(array);

    return 0;
}

double (*flow_array(int (*dataArray)[ARRAY_SIZE], int size))[ARRAY_SIZE] {
    // We have to double the size of the malloc because we will have two doubles in each index.
    double (*flowArray)[ARRAY_SIZE] = malloc(sizeof(double) * size * ARRAY_SIZE);
    double V = 0.1; // TODO: CHANGE ME 
    double deltaTime;

    // Validate the initialization of the array.
    if (flowArray == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }

    // Calculates the flow using Q=dv/dt for each time
    for (int i = 0; i < size; i++) {
        flowArray[i][0] = (double)dataArray[i][0];

        // Calculate the time difference between the current and previous time.
        if (i > 0) {
            deltaTime = (double)(dataArray[i][0] - dataArray[i - 1][0]);
        } else {
            deltaTime = 1.0;
        }

        // Calculate the flow rate.  
        flowArray[i][1] = (double)dataArray[i][1]*V/deltaTime;
    }

    return flowArray;
}
    
double (*height_array(double (*flowArray)[ARRAY_SIZE], int size))[ARRAY_SIZE] {
    double (*heightArray)[ARRAY_SIZE] = malloc(sizeof(double) * size * ARRAY_SIZE);
    double g = 9.81; // Gravitational acceleration constant
    double A = 0.1; // TODO: CHANGE ME
    double Q; // Volematric flow rate

    // Validate the initialization of the array.
    if (heightArray == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++)
    {
        // Copying the time from the flowArray to the heightArray
        heightArray[i][0] = flowArray[i][0];

        // Calculating the height of the water
        Q=flowArray[i][1];
        heightArray[i][1] = (Q*Q)/(2*g*A*A);
    }
    
    return heightArray;
}

// This function reads the data from a file and stores it in a two dimensional array.
int (*array_from_file(char *filePath, int *size))[ARRAY_SIZE] {
    int time, rotations;
    int lines = 0;
    char ch;

    // Open the data file in read mode.
    FILE *file = fopen(filePath, "r");

    // Buffer to store the lines.
    char line[25];

    // Validate the opening of the file.
    if (file == NULL) {
        printf("Error reading file\n");
        exit(EXIT_FAILURE);
    }

    // Calculates the number of lines.
    // Check if end of file.
    while (!feof(file)) 
    {
        // Get next char in file.
        ch = fgetc(file);

        // Checks if the char is a newline.
        if (ch == '\n') {
            lines++;
        }
    }

    // Returns the size of the array as pointer.
    *size = lines;

    // We have to double the size of the malloc because we will have two integers in each index.
    int (*array)[ARRAY_SIZE] = malloc(sizeof(int) * lines * ARRAY_SIZE);

    // Validate the initialization of the array.
    if (array == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }

    // Resets the current position of the pointer to the start of the file.
    rewind(file);
    
    // Read the file and store the values in the array.
    for (int i = 0; i < lines; i++){
        // Read the line from the file and sizeof(line) is the size of the buffer.
        fgets(line, sizeof(line), file);
        // sscanf is used to read formatted input from a string.
        sscanf(line, "%d %d", &time, &rotations);
        array[i][0] = time;
        array[i][1] = rotations;
    }

    fclose(file);

    return array;
}