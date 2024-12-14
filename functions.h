#include <time.h>

#define MAX_SIZE 1024
#define MAX_BUFFER 64

struct data {
    time_t timestamp; // Time in seconds
    int volume;
};

struct flow {
    time_t timestamp; // Timestamp provided by the Arduino
    double flow;
};

struct height {
    time_t timestamp; // Timestamp provided by the Arduino
    double height;
};

struct sensor {
    int id;
    char name[MAX_SIZE];
    char path[MAX_SIZE];
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

// This function reads the data from a file and stores it in a two dimensional array.
data *array_from_file(char *filePath, int *size, time_t referenceStartTime);

// This function calculates the flow rate using the formula Q=dv/dt
flow *flow_array(data *dataArray, int size);

// This function calculates the height of the water using the formula h=(Q^2)/(2*g*A^2)
height *height_array(flow *flowArray, int size);

// This function returns the number of sensors in a given folder
int number_of_sensors(char folderPath[MAX_SIZE]);

// This function returns the id, path and name of the sensors in a given folder
sensor *path_of_sensors(char folderPath[MAX_SIZE]);

//Compares Flow array and return lowest flow value at index 0.
int comp_asc(const void *, const void *);

// This function takes the average flow in a given time
double average_flow(int timePeriod, flow flowArray[], int arrayLength);

// This function gives the max or min flow in a given time
double min_max_flow(int timePeriod, int min_max_bit, flow flowArray[], int arrayLength);

// This function returns the flow array from a given id
flow *flow_from_id(int id, int *size, time_t referenceStartTime);

// This function returns the height array from a given id
height *height_from_id(int id, int *size, time_t referenceStartTime);

// This function counts the number of alarms in a given time
overflow_period *overflow_occurrences_id(int id, float threshold, int *overflowCount, time_t referenceStartTime);

// This function determines the overflow occurrences based on the threshold in a given time
overflow_period *overflow_occurrences(height *heightArray, int size, float threshold, int *overflowCount);
