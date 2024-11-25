#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>
#include "functions.h"

#define ROTATION_FLOW (2.25 / 1000) // CHANGE ME TO CORRECT RORATION_FLOW IN LITER

#define ROTATION_FLOW (2.25 / 1000) //CHANGE ME TO CORRECT ROTATION_FLOW in LITER

/*int main(void) {
    // Declare a two dimensional array, without a set length.
    data *array;
    flow *flowArray;
    height *heightArray;
    sensor *stringParths;
    int size;

    array = array_from_file("./data/sensor0.txt", &size);

    flowArray = flow_array(array, size);

    heightArray = height_array(flowArray, size);

    // Prints time and rotations.
    for (int i = 0; i < size; i++) {
        printf("%d %d\n", array[i].time, array[i].rotations);
    }

    for (int i = 0; i < size; i++) {
        printf("%d %f\n", flowArray[i].time, flowArray[i].flow);
    }
    
    for (int i = 0; i < size; i++) {
        printf("%d %f\n", heightArray[i].time, heightArray[i].height);
    }

    stringParths = path_of_sensors("./data/");

    size = number_of_sensors("./data/");

    for (int i = 0; i < size; i++)
    {
        printf("%d %s\n",stringParths[i].id,stringParths[i].name);
    }
    

    free(array);

    return 0;
}*/

flow *flow_array(data *dataArray, int size) {
    // We have to double the size of the malloc because we will have two doubles in each index.
    flow *flowArray = malloc(sizeof(flow) * size);
    double V = 0.1; // TODO: CHANGE ME 
    double deltaTime;

    // Validate the initialization of the array.
    if (flowArray == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }

    // Calculates the flow using Q=dv/dt for each time
    for (int i = 0; i < size; i++) {
        flowArray[i].time = (double)dataArray[i].time;

        // Calculate the time difference between the current and previous time.
        if (i > 0) {
            deltaTime = (double)(dataArray[i].time - dataArray[i - 1].time);
        } else {
            deltaTime = 1.0;
        }

        // Calculate the flow rate.  
        flowArray[i].flow = (double)dataArray[i].rotations*V/deltaTime;
    }

    return flowArray;
}
    
height *height_array(flow *flowArray, int size) {
    height *heightArray = malloc(sizeof(height) * size);
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
        heightArray[i].time = flowArray[i].time;

        // Calculating the height of the water
        Q=flowArray[i].flow;
        heightArray[i].height = (Q*Q)/(2*g*A*A);
    }
    
    return heightArray;
}

// This function reads the data from a file and stores it in a two dimensional array.
data *array_from_file(char *filePath, int *size) {
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
    data *array = malloc(sizeof(data) * lines);

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
        array[i].time = time;
        array[i].rotations = rotations;
    }

    fclose(file);

    return array;
}

int number_of_sensors(char folderPath[1024]) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(folderPath);

    if (d) {
        // Loops over all the files in the folder
        while ((dir = readdir(d)) != NULL) {
            // Checks if the dirnames are not . or ..
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                count++;
            } 
        }
        closedir(d);
    }

    return count;
}

sensor *path_of_sensors(char folderPath[1024]) {
    DIR *d;
    struct dirent *dir;
    int size = number_of_sensors(folderPath);
    sensor *parth = malloc(sizeof(sensor) * size);
    int i = 0;

    d = opendir(folderPath);

    if (d) {
        // Loops over all the files in the folder
        while ((dir = readdir(d)) != NULL) {
            // Checks if the dirnames are not . or ..
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                // Copy the name of the file into parth array.
                strcpy(parth[i].parth, dir->d_name);
                strcpy(parth[i].name, dir->d_name);
                parth[i].id = i;
                i++;
            } 
        }
        closedir(d);
    }

    return parth;
}

double avage_flow(int timePeriod, flow flowArray[]){
    //timePeriod in hours 
    int timeBetweenMeasurements = flowArray[1].time - flowArray[0].time; //In miliseconds
    double measurementsPerHour = 60 / (timeBetweenMeasurements / 1000 / 60);
    double measurementsForPeriod = measurementsPerHour * timePeriod;
    int arrayLength = sizeof(flowArray)-1; // NOGET VIRKER IKKE - HVORFOR ER MIT ARRAY KUN 8? (CHANGE ME)
    double totalFlow = 0; 
    double averageFlow = 0;

    for (int i = measurementsForPeriod; i >= 0; i--){
        totalFlow += flowArray[arrayLength-i].flow;
    }

    averageFlow = totalFlow / timePeriod;

    return averageFlow;
}