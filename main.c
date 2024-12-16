#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

time_t referenceStartTime;

void water_level_statistics(int sensorChoice);
void set_water_level_alarm(int sensorChoice);
void data_menu(int sensorChoice);
void sensor_menu(void);

int main(void) {
    referenceStartTime = time(NULL); // Set the reference start time
    while (1) {
        sensor_menu(); 
    } 
    
    return 0;
}

void sensor_menu(void) {
    int choice;
    int numberOfSensors;
    int isValid;

    numberOfSensors = number_of_sensors("./data/");
    sensor *sensor = path_of_sensors("./data/");
        
    if (numberOfSensors < 0 || sensor == NULL) {
        printf("Failed to load sensors.\n");
        return;
    }

    // The code in the do-while loop runs until the conditions in the while-loop are fulfilled
    do {
        printf("\n--- Sensor Menu ---\n");
        printf("0. Exit the program\n");

        for (int i = 0; i < numberOfSensors; i++) {
            char *pch;
            // Pch removes file extensions (.txt) on sensor menu
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

    if (choice == 0) {
        printf("Exiting program\n");
        exit(EXIT_SUCCESS);
    }

    data_menu(choice);
}

void data_menu(int sensorChoice) {
    int choice;
    int isValid;
    
    do {
        printf("\n--- Data Menu ---\n");
        printf("0. Exit the program\n");
        printf("1. Water level Statistics\n");
        printf("2. Set water level alarm\n");
        printf("Choose where you want to go: ");
        isValid = scanf(" %d", &choice);

        // Removes the input buffer
        while (getchar() != '\n');

        switch (choice) {
            case 0:
                printf("Exiting program\n");
                exit(EXIT_SUCCESS);
                break;
            case 1:
                water_level_statistics(sensorChoice);
                break;
            case 2:
                set_water_level_alarm(sensorChoice);
                break;
            default:
                printf("\n\x1B[31mInvalid choice!\x1B[0m\n");    // colors the printf statement in the terminal
        }
    } while (choice < 0 || choice > 4 || !isValid);
}

void water_level_statistics(int sensorChoice) {
    int arrLength;
    int timePeriod;
    int isValid;
    double averageFlow;

    // sensorChoice-1 because the sensor id starts at 0
    flow *arr = flow_from_id(sensorChoice-1, &arrLength, referenceStartTime);

    printf("Water Level Statistics, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
        if (timePeriod <= 0 || timePeriod > 3600 || !isValid) {
            printf("\n\x1B[31mInvalid time period!\x1B[0m\n");
        }
    } while (timePeriod <= 0 || timePeriod > 3600 || !isValid);

    averageFlow = average_flow(timePeriod, arr, arrLength);

    if (averageFlow < 0.0) {
        printf("\n\x1B[31mAverage flow is invalid!\x1B[0m\n");
    } else {
        printf("\nThe average flow is %f mL/hour\n", averageFlow);
    }
    
    printf("The minimum flow was: %f mL/hour\n", min_max_flow(timePeriod, 1, arr, arrLength));
    printf("The maximum flow was: %f mL/hour\n", min_max_flow(timePeriod, 0, arr, arrLength));

    free(arr);

    // Clear input buffer
    while( getchar() != '\n' );

    // Wait for user to press enter
    printf("\nPress Enter to Continue...");
    while( getchar() != '\n' );
}

void set_water_level_alarm(int sensorChoice) {
    float threshold;
    int isValid;

    printf("Set Water Level Alarm, sensor %d\n", sensorChoice);

    do {
        printf("Please set the threshold: ");
        isValid = scanf(" %f", &threshold);
    } while (threshold < 0 || !isValid);

    int overflowCount = 0;
    overflow_period *overflowArray;
    
    overflowArray = overflow_occurrences_id(sensorChoice-1, threshold, &overflowCount, referenceStartTime); // sensorChoice-1 because the sensor id starts at 0

    printf("Checking sensor %d with threshold %f\n", sensorChoice, threshold);
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

    printf("Total number of alarms: %d\n", overflowCount);

    // Clear input buffer
    while( getchar() != '\n' );

    // Wait for user to press enter
    printf("\nPress Enter to Continue...");
    while( getchar() != '\n' );
}
