#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include "functions.h"

// Constant for converting mL to m^3
#define ML_TO_M3 1000000

#define SEC_TO_HOUR (60 * 60)

#define PI 3.14

flow *flow_from_id(int id, int *size, time_t referenceStartTime) {
    char filePath[MAX_SIZE + 32]; // 32 is to make space for "./data/" or any other path
    sensor *sensors = path_of_sensors("./data/");
    sprintf(filePath, "./data/%s", sensors[id].path);
    free(sensors);
    flow *flowArray = flow_array_from_file(filePath, size, referenceStartTime);
    return flowArray;
}

height *height_from_id(int id, int *size, time_t referenceStartTime) {
    flow *flowArray = flow_from_id(id, size, referenceStartTime);
    height *heightArray = height_array(flowArray, *size);
    free(flowArray);
    return heightArray;
}

overflow_period *overflow_occurrences_id(int id, float threshold, int *overflowCount, time_t referenceStartTime) {
    int size;
    height *heightArray = height_from_id(id, &size, referenceStartTime);
    overflow_period *overflowArray = overflow_occurrences(heightArray, size, threshold, overflowCount);
    free(heightArray);
    return overflowArray;
}
    
height *height_array(flow *flowArray, int size) {
    height *heightArray = malloc(sizeof(height) * size);
    const double g = 9.81; // Gravitational acceleration constant
    const double A = 0.20*0.20*PI; // Area of pipe hole
    double Q; // Volumetric flow rate

    
    
    // Validate the initialization of the array.
    if (heightArray == NULL) {
        printf("Error in array\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < size; i++) {
        // Copying the time from the flowArray to the heightArray
        heightArray[i].timestamp = flowArray[i].timestamp;

        // Calculating the height of the water
        Q=flowArray[i].flow*ML_TO_M3;
        heightArray[i].height = (Q*Q)/(2*g*A*A);
    }
    
    return heightArray;
}

// This function reads the data from a file and stores it in a two dimensional array.
flow *flow_array_from_file(char *filePath, int *size, time_t referenceStartTime) {
    int time, flowData;
    int lines = 0;
    char ch;

    // Open the data file in read mode.
    FILE *file = fopen(filePath, "r");

    // Buffer to store the lines.
    char line[MAX_BUFFER];

    // Validate the opening of the file.
    if (file == NULL) {
        printf("Error reading file\n");
        exit(EXIT_FAILURE);
    }

    // Calculate the number of lines assuming there is a newline at the end.
    // Check if end of file.
    while (!feof(file)) {
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
    flow *array = malloc(sizeof(flow) * lines);

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
        sscanf(line, "%d %d", &time, &flowData);
        
        array[i].timestamp = referenceStartTime + (time / 1000); // Convert milliseconds to seconds and add to reference start time;
        array[i].flow = flowData;
    }

    fclose(file);

    return array;
}

int number_of_sensors(char folderPath[MAX_SIZE]) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(folderPath);

    if (d) {
        // Loops over all the files in the folder
        while ((dir = readdir(d)) != NULL) {
            // Checks if the dir names are not . or ..
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                count++;
            } 
        }
        closedir(d);
    }

    return count;
}

sensor *path_of_sensors(char folderPath[]) {
    DIR *d;
    struct dirent *dir;
    int size = number_of_sensors(folderPath);
    sensor *path = malloc(sizeof(sensor) * size);
    int i = 0;

    d = opendir(folderPath);

    if (d) {
        // Loops over all the files in the folder
        while ((dir = readdir(d)) != NULL) {
            // Checks if the dir names are not . or ..
            if (strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")) {
                // Copy the name of the file into path array.
                strcpy(path[i].path, dir->d_name);
                strcpy(path[i].name, dir->d_name);
                path[i].id = i;
                i++;
            } 
        }
        closedir(d);
    }

    return path;
}

double average_flow(int measurementsForPeriod, flow flowArray[], int arrayLength) {
    double totalFlow = 0;
    double averageFlow = 0;

    // Check from the latest measurement and back
    for (int i = measurementsForPeriod; i > 0; i--) {
        totalFlow += flowArray[arrayLength-i].flow;
    }

    averageFlow = totalFlow / measurementsForPeriod;
    return averageFlow;
}

int calculate_measurements_for_period(double timePeriod, flow flowArray[]) {
    // timePeriod in hours
    int deltaTime = flowArray[1].timestamp - flowArray[0].timestamp; // In milliseconds

    int measurementsPerHour = SEC_TO_HOUR / deltaTime;
    int measurementsForPeriod = (int)((double)measurementsPerHour * timePeriod);

    return measurementsForPeriod;
}

double min_max_flow(int measurementsForPeriod, int min_max_bit, flow flowArray[], int size) {
    //Function assumes sorted flow array with the lowest flow value at index 0.
    flow flowForTimePeriod[measurementsForPeriod];

    // Copy the array to get only the end
    for (int i = 0; i < measurementsForPeriod; i++) {
        flowForTimePeriod[i] = flowArray[(size - 1) - i];
    }

    qsort(flowForTimePeriod, measurementsForPeriod, sizeof(flow), comp_asc);

    switch (min_max_bit) {
        case 0:
            return flowForTimePeriod[0].flow;
        case 1:
            return flowForTimePeriod[measurementsForPeriod-1].flow;
        default:
            return -1;
    }
}

int comp_asc(const void *a, const void *b) {
    return ((struct flow*)a) -> flow - ((struct flow*)b) -> flow;
}

overflow_period *overflow_occurrences(height *heightArray, int size, float threshold, int *overflowCount) {
    overflow_period *overflowArray = malloc(sizeof(overflow_period) * size);
    int count = 0;
    int inOverflow = 0;
    time_t start = 0;

    for (int i = 0; i < size; i++) {
        if (heightArray[i].height > threshold) {
            if (!inOverflow) {
                start = heightArray[i].timestamp;
                inOverflow = 1;
            }
        } else {
            if (inOverflow) {
                overflowArray[count].start = start;
                overflowArray[count].end = heightArray[i].timestamp;
                count++;
                inOverflow = 0;
            }
        }
    }

    // If the last period is still in overflow
    if (inOverflow) {
        overflowArray[count].start = start;
        overflowArray[count].end = heightArray[size - 1].timestamp;
        count++;
    }

    *overflowCount = count;
    return overflowArray;
}
