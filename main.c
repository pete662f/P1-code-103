#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"
#include <time.h>

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

    printf("Water Level Statistics, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
    } while (timePeriod < 0 || timePeriod > 3600 || !isValid);
    printf("The average flow is %f mL/hour\n", average_flow(timePeriod, arr, arrLength));
    qsort(arr,arrLength,sizeof(flow), comp_asc);
    printf("The minimum flow was: %f\n", min_max_flow(timePeriod, 1, arr, arrLength));
    printf("The maximum flow was: %f\n", min_max_flow(timePeriod, 0, arr, arrLength));
}

void flow_graph(int sensorChoice) {
    printf("Flow Graph, sensor %d\n", sensorChoice);
    // Code here
}

#define SENSOR_1_THRESHOLD 10.0
#define SENSOR_2_THRESHOLD 15.0
#define SENSOR_3_THRESHOLD 20.0

void set_water_level_alarm(int sensorChoice) {
    // CHANGE ME - Test array skal slettes -- Real array should be inputted to this function
    flow arr[] = {{0, 12}, {300000, 10}, {600000, 20}, {900000, 10}, {1200000, 5}, {1500000, 12}, {1800000, 8}, {2100000, 7}, {2400000, 13}, {2700000, 21}, {3000000, 24}, {3300000, 17}, {3600000, 15}};
    int arrLength = sizeof(arr) / sizeof(arr[0]); // CHANGE ME: this should be inputted to this function together with the real array.

    int timePeriod;
    int isValid;

    printf("Set Water Level Alarm, sensor %d\n", sensorChoice);
    do {
        printf("Please input number of hours to include data from: ");
        isValid = scanf(" %d", &timePeriod);
    } while (timePeriod < 0 || timePeriod > 3600 || !isValid);

    time_t currentTime = time(NULL);
    time_t interval = currentTime - (timePeriod * 3600);

    height *heightArray = height_array(arr, arrLength);
    float threshold;
    int totalAlarms = 0;

    if (sensorChoice == 0) {
        // Check all sensors
        for (int i = 1; i <= 3; i++) {
            switch (i) {
                case 1:
                    threshold = SENSOR_1_THRESHOLD;
                    break;
                case 2:
                    threshold = SENSOR_2_THRESHOLD;
                    break;
                case 3:
                    threshold = SENSOR_3_THRESHOLD;
                    break;
            }
            totalAlarms += count_alarms(heightArray, arrLength, interval, threshold);
        }
        printf("Total number of alarms in the last %d hours for all sensors: %d\n", timePeriod, totalAlarms);
    } else {
        // Check specific sensor
        switch (sensorChoice) {
            case 1:
                threshold = SENSOR_1_THRESHOLD;
                break;
            case 2:
                threshold = SENSOR_2_THRESHOLD;
                break;
            case 3:
                threshold = SENSOR_3_THRESHOLD;
                break;
            default:
                printf("Invalid sensor choice\n");
                free(heightArray);
                return;
        }
    int alarmCount = count_alarms(heightArray, arrLength, interval, threshold);
    printf("Number of alarms in the last %d hour(s): %d\n", timePeriod, alarmCount);
    }

    free(heightArray);
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
    while (fscanf(file, "%f %f", &data[count].pulsecount, &data[count].time) == 2) {
        data[count].time = time(NULL); // Assign current time for simplicity
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

   // int flowRate = ((1000.0 / time) * pulsecount) / 4.5;

    fclose(file);
    *size = count;
    return data;
}

void current_time(flow *data, int size) {
    time_t currentTime = time(NULL);
    printf("Current time: %s", ctime(&currentTime));
    if (size > 0) {
        printf("Last data point time: %s", ctime(&data[size - 1].time));
    }
}