#include <stdio.h>


void water_level_graph();
void water_level_statistics();
void flow_graph();
void set_water_level_alarm();
void main_menu()
void sensor_menu();

int main(void) {

    main_menu();

    return 0;
}


void water_level_graph() {
    printf("       ");
    // Code here
}

void water_level_statistics() {
    printf("       ");
    // Code here
}

void flow_graph() {
    printf("       ");
    // Code here
}

void set_water_level_alarm() {
    printf("       ");
    // Code here
}

void sensor_menu() {
    int sensor_choice;

    printf("\n--- Sensor menu ---\n");
    printf("0. All sensors\n");
    printf("1. Sensor 1\n");
    printf("2. Sensor 2\n");
    printf("3. Sensor 3\n");
    printf("Choose sensor");
    scanf("%d", &sensor_choice);

    switch (sensor_choice) {
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

void main_menu() {
    int choice;
    while (1) {
        printf("\n--- Main menu ---\n");
        printf("1: Water level graph\n");
        printf("2: Water level Statistics\n");
        printf("3: Flow graph\n");
        printf("4: Set water level alarm\n");
        printf("5: Sensor menu\n");
        printf("0: finish\n");
        printf("Choose where you want to go\n");
        scanf("%d", &choice);
    }
    
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
        case 5:
            sensor_menu();
            break;
        case 0:
            printf("Finishing the program");   // hvis man skriver 0
            break;
        default:
            printf("Error: No choice!");
    }
}
