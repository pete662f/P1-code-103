#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

void water_level_graph(int sensorChoice);
void water_level_statistics(int sensorChoice);
void flow_graph(int sensorChoice);
void set_water_level_alarm(int sensorChoice);
void data_menu(int sensorChoice);
void sensor_menu();

int main(void) {
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

// The code in the do-while loop runs until the conditions in the while-loop are fullfilled
    do {
        printf("\n--- Sensor Menu ---\n");
        printf("0. All sensors\n");

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
        printf("1: Water level graph\n");
        printf("2: Water level Statistics\n");
        printf("3: Flow graph\n");
        printf("4: Set water level alarm\n");
        printf("0: Exit the program\n");
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
                printf("Exiting the program\n");       // If you type 0
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
    // CHANGE ME - Test array skal slettes -- Real array should be inputted to this function
    flow arr[]={{0, 12},{300000, 10},{600000, 20}, {900000, 10}, {1200000, 5}, {1500000, 12}, {1800000, 8}, {2100000, 7}, {2400000, 13}, {2700000, 21}, {3000000, 24}, {3300000, 17}, {3600000, 15}};
    int arrLength = sizeof(arr) / sizeof(arr[0]); //CHANGE ME: this should be inputted to this function together with the real array.

    int timePeriod;
    int isValid;
    qsort(arr,arrLength,sizeof(flow), comp_asc);

    printf("Water Level Statistics, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
    } while (timePeriod < 0 || timePeriod > 3600 || !isValid);
    printf("The average flow is %f mL/hour\n", average_flow(timePeriod, arr, arrLength));
    printf("The minimum flow was: %f\n", min_max_flow(timePeriod, 1, arr, arrLength));
    printf("The maximum flow was: %f\n", min_max_flow(timePeriod, 0, arr, arrLength));
}

void flow_graph(int sensorChoice) {
    printf("Flow Graph, sensor %d\n", sensorChoice);
    // Code here
}

void set_water_level_alarm(int sensorChoice) {
    printf("Set Water Level Alarm, sensor %d\n", sensorChoice);
    // Code here
}

