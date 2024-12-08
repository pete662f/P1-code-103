#include <time.h>

struct data {
    long time; // Time in seconds
    int rotations;
};

struct flow {
    time_t timestamp; // Timestamp provided by the Arduino
    double flow;
    double total_quantity;
    double pulsecount;
};

struct height {
    time_t timestamp; // Timestamp provided by the Arduino
    double height;
};

struct sensor {
    int id;
    char name[1024];
    char parth[1024];
};

struct overflow_period {
    time_t start;
    time_t end;
};

typedef struct data data;
typedef struct flow flow;
typedef struct height height;
typedef struct sensor sensor;
typedef struct overflow_period overflow_period;

// ------ DONE ------ //

// This function reads the data from a file and stores it in a two dimensional array.
data *array_from_file(char *filePath, int *size);

// This function calculates the flow rate using the formula Q=dv/dt
flow *flow_array(data *dataArray, int size);

// This function calculates the height of the water using the formula h=(Q^2)/(2*g*A^2)
height *height_array(flow *flowArray, int size);

// This function returns the number of sensors in a given folder
int number_of_sensors(char folderPath[1024]);

// This function returns the id, path and name of the sensors in a given folder
sensor *path_of_sensors(char folderPath[1024]);

//Compares Flow array and return lowest flow value at index 0.
int comp_asc(const void *, const void *);

// This function takes the average flow in a given time
double average_flow(int timePeriod, flow flowArray[], int arrayLength);

// This function gives the max or min flow in a given time
double min_max_flow(int timePeriod, int min_max_bit, flow flowArray[], int arrayLength);

// ------ DONE ------ //

// This function determines the overflow occurrences based on the threshold in a given time
overflow_period *overflow_occurrences(height *heightArray, int size, float threshold, int *overflowCount);

// this function reads the data from data.txt and stores it in a flow array
flow *read_data(const char *filename, int *size);

// Could use https://gr-framework.org/c.html for drawing graphs or 
void draw_graph(double *array);