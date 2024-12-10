#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

time_t reference_start_time;

void water_level_graph(int sensorChoice);
void water_level_statistics(int sensorChoice);
void flow_graph(int sensorChoice);
void set_water_level_alarm(int sensorChoice);
void data_menu(int sensorChoice);
void sensor_menu();

int main(void) {
    reference_start_time = time(NULL); // Set the reference start time
    while (1) {
        sensor_menu(); 
    } 
    
    return 0;
}

void sensor_menu() {
    int choice;
    int numberOfSensors;
    int isValid;

    // Uses functions from functions.h (number_of_sensors, and parth_of_sensors) 
    numberOfSensors = number_of_sensors("./data/");
    sensor *sensor = path_of_sensors("./data/");

        
    if (numberOfSensors < 0 || sensor == NULL) {
        printf("Failed to load sensors.\n");
        return;
    }


// The code in the do-while loop runs until the conditions in the while-loop are fullfilled
    do {
        printf("\n--- Sensor Menu ---\n");
        printf("0. Exit the program\n");

        for (int i = 0; i < numberOfSensors; i++) {
            char *pch;
            // Pch removes file exstention (.txt) on sensor menu
            pch = strtok(sensor[i].name,".");
            printf("%d. %s\n", i + 1, pch);
        }

        

        printf("Choose sensor: ");
        isValid = scanf(" %d", &choice);

        // Removes the input buffer
        while (getchar() != '\n');    

        if (choice > numberOfSensors || choice < 0 || !isValid) {
            printf("\n\x1B[31mInvalid sensor choice!\x1B[0m\n");    // colors the printf statement in the terminal
        }
    } while (choice > numberOfSensors || choice < 0 || !isValid);
    
    free(sensor);

    data_menu(choice);
}

void data_menu(int sensorChoice) {
    int choice;
    int isValid;
    
    do {
        printf("\n--- Data Menu ---\n");
        printf("0. Exit the program\n");
        printf("1. Water level graph\n");
        printf("2. Water level Statistics\n");
        printf("3. Flow graph\n");
        printf("4. Set water level alarm\n");
        printf("Choose where you want to go: ");
        isValid = scanf(" %d", &choice);

        // Removes the input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                water_level_graph(sensorChoice);
                break;
            case 2:
                water_level_statistics(sensorChoice);
                break;
            case 3:
                flow_graph(sensorChoice);
                break;
            case 4:
                set_water_level_alarm(sensorChoice);
                break;
            case 0:
                printf("Exiting program\n");
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("\n\x1B[31mInvalid choice!\x1B[0m\n");    // colors the printf statement in the terminal
        }
    } while (choice < 0 || choice > 4 || !isValid);
}

void water_level_graph(int sensorChoice) {
    printf("Water Level Graph, sensor %d\n", sensorChoice);
    // Code here
}

void water_level_statistics(int sensorChoice) {
    int arrLength;
    int timePeriod;
    int isValid;

    // sensorChoice-1 because the sensor id starts at 0
    flow *arr = flow_from_id(sensorChoice-1, &arrLength);

    printf("Water Level Statistics, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
    } while (timePeriod < 0 || timePeriod > 3600 || !isValid);
    printf("The average flow is %f mL/hour\n", average_flow(timePeriod, arr, arrLength));
    qsort(arr,arrLength,sizeof(flow), comp_asc);
    printf("The minimum flow was: %f\n", min_max_flow(timePeriod, 1, arr, arrLength));
    printf("The maximum flow was: %f\n", min_max_flow(timePeriod, 0, arr, arrLength));

    free(arr);

    // Clear input buffer
    while( getchar() != '\n' );

    // Wait for user to press enter
    printf("\nPress Enter to Continue...");
    while( getchar() != '\n' );
}

void flow_graph(int sensorChoice) {
    printf("Flow Graph, sensor %d\n", sensorChoice);
    // Code here
}

void set_water_level_alarm(int sensorChoice) {
    double threshold;
    int size;
    int timePeriod;
    int isValid;

    printf("Set Water Level Alarm, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
    } while (timePeriod < 0 || timePeriod > 3600 || !isValid);

    do {
        printf("Please set the: threshold: ");
        isValid = scanf(" %lf", &threshold);
    } while (threshold < 0 || !isValid);

    time_t currentTime = time(NULL);
    time_t interval = currentTime - (timePeriod * 3600);

    int overflowCount = 0;
    overflow_period *overflowArray;
    int totalAlarms = 0;
    
    overflowArray = overflow_occurrences_id(sensorChoice, threshold, &overflowCount);

    printf("Checking sensor %d with threshold %f\n", sensorChoice, threshold);
    totalAlarms = overflowCount;

    printf("Overflow periods for sensor %d: ", sensorChoice);

    if (overflowCount == 0) {
        printf("0\n");
    } else {
        printf("\n");
        for (int i = 0; i < overflowCount; i++) {
            printf("Start: %s", ctime(&overflowArray[i].start));
            printf("End: %s", ctime(&overflowArray[i].end));
        }
    }
    free(overflowArray);

    printf("Total number of alarms: %d\n", totalAlarms);

    // Clear input buffer
    while( getchar() != '\n' );

    // Wait for user to press enter
    printf("\nPress Enter to Continue...");
    while( getchar() != '\n' );
}

flow *read_data(const char *filename, int *size) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    int capacity = 10;
    flow *data = malloc(capacity * sizeof(flow));
    if (!data) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    long time;
    while (fscanf(file, "%lf %ld", &data[count].pulsecount, &time) == 2) {
        data[count].timestamp = reference_start_time + (time / 1000); // Convert milliseconds to seconds and add to reference start time
        data[count].total_quantity = time; // Assuming total_quantity is the time in milliseconds
        data[count].flow = ((1000.0 / data[count].total_quantity) * data[count].pulsecount) / 4.5;
        count++;
        if (count >= capacity) {
            capacity *= 2;
            data = realloc(data, capacity * sizeof(flow));
            if (!data) {
                perror("Failed to reallocate memory");
                exit(EXIT_FAILURE);
            }
        }
    }

    fclose(file);
    *size = count;
    return data;
}