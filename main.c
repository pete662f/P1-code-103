#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "functions.h"

void water_level_graph();
void water_level_statistics();
void flow_graph();
void set_water_level_alarm();
void main_menu();
void sensor_menu();

int main(void) {

    main_menu();

    return 0;
}

void main_menu() {
    int choice;
    while (1) {
        printf("\n--- Main menu ---\n");
        printf("1: Water level graph\n");
        printf("2: Water level Statistics\n");
        printf("3: Flow graph\n");
        printf("4: Set water level alarm\n");
        printf("0: finish\n");
        printf("Choose where you want to go:");
        scanf("%d", &choice);
    
    
        switch (choice) {
            case 1:
                water_level_graph();
                break;
            case 2:
                water_level_statistics();
                break;
            case 3:
                flow_graph();
                break;
            case 4:
                set_water_level_alarm();
                break;
            case 0:
                printf("Finishing the program");   // hvis man skriver 0
                exit(EXIT_SUCCESS);
                break;
            default:
                printf("Error: No choice!");
        
        }
    }
}

void sensor_menu() {
    int sensorChoice;
    int numberOfSensors;


    numberOfSensors = number_of_sensors("./data/");
    sensor *sensor = parth_of_sensors("./data/");

    printf("\n--- Sensor menu ---\n");
    printf("0. All sensors\n");

    for (int i = 0; i < numberOfSensors; i++){
        char *pch;
        pch = strtok(sensor[i].name,".");
        printf("%d. %s\n", i + 1, pch);
    }

    free(sensor);

    printf("Choose sensor: ");
    scanf("%d", &sensorChoice);

    switch (sensorChoice) {
        case 0:
            printf("0. All sensors\n");
            break;
        case 1:
            printf("1. Sensor 1\n");
            break;
        case 2:
            printf("2. Sensor 2\n");
            break;
        case 3:
            printf("3. Sensor 3\n");
            break;
        default:
            printf("Error: No sensor chosen!");
    }
}

void water_level_graph() {
    sensor_menu();
    printf("       ");
    // Code here
}

void water_level_statistics() {
    sensor_menu();
    printf("       ");
    // Code here
}

void flow_graph() {
    sensor_menu();
    printf("       ");
    // Code here
}

void set_water_level_alarm() {
    sensor_menu();
    printf("       ");
    // Code here
}

