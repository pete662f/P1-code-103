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
    sensor *sensor = parth_of_sensors("./data/");

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
    printf("Water Level Statistics, sensor %d\n", sensorChoice);
    // Code here
}

void flow_graph(int sensorChoice) {
    printf("Flow Graph, sensor %d\n", sensorChoice);
    // Code here
}

void set_water_level_alarm(int sensorChoice) {
    printf("Set Water Level Alarm, sensor %d\n", sensorChoice);
    // Code here
}

