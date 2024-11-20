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