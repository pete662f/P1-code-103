#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <dirent.h>

struct data {
    int time;
    int rotations;
};

struct flow {
    int time;
    double flow;
};

struct height {
    int time;
    double height;
};

struct sensor {
    int id;
    char name[1024];
    char parth[1024];
};

typedef struct data data;
typedef struct flow flow;
typedef struct height height;
typedef struct sensor sensor;

// This function reads the data from a file and stores it in a two dimensional array.
data *array_from_file(char *filePath, int *size);

// This function calculates the flow rate using the formula Q=dv/dt
flow *flow_array(data *dataArray, int size);

// This function calculates the height of the water using the formula h=(Q^2)/(2*g*A^2)
height *height_array(flow *flowArray, int size);

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

int number_of_sensors(char folderParth[100]);

sensor *parth_of_sensors(char folderParth[100]);

int main(void) {
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

    stringParths = parth_of_sensors("./data/");

    size = number_of_sensors("./data/");

    for (int i = 0; i < size; i++)
    {
        printf("%d %s\n",stringParths[i].id,stringParths[i].name);
    }
    

    free(array);

    return 0;
}

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

int number_of_sensors(char folderParth[1024]) {
    DIR *d;
    struct dirent *dir;
    int count = 0;

    d = opendir(folderParth);

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

sensor *parth_of_sensors(char folderParth[1024]) {
    DIR *d;
    struct dirent *dir;
    int size = number_of_sensors(folderParth);
    sensor *parth = malloc(sizeof(sensor) * size);
    int i = 0;

    d = opendir(folderParth);

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