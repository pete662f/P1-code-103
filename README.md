# Swer data prossing from sensor
This is a simple project to process data from a sensor. The sensor is a simple device that sends data to a file. The data is in the following format:
```
time volume
```
## Compile and run
To compile the project, run the following command:
`gcc main.c functions.c -o main`

To run the project, run the following command:
`./main`

## Testing
To compile the project, run the following command:
`gcc test.c CuTest.c functions.c -o test`

To run the project, run the following command:
`./test`
