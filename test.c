#include <stdio.h>
#include "functions.h"
#include "CuTest.h"

enum minMaxBit {
    MIN,
    MAX
};

void averageFlowTest(CuTest* tc)
{
    double averageFlow = 0;
    double time = 2.5;
    int measurementsForPeriod;

    flow flowArray[10] = {
        {1800, 20},
        {1800*2, 30},
        {1800*3, 15},
        {1800*4, 25},
        {1800*5, 35},
        {1800*6, 10},
        {1800*7, 40},
        {1800*8, 20},
        {1800*9, 30},
        {1800*10, 25}
    };

    measurementsForPeriod = calculate_measurements_for_period(time,flowArray);
    CuAssertIntEquals(tc, 5, measurementsForPeriod);

    averageFlow = average_flow(measurementsForPeriod, flowArray, 10);
    CuAssertDblEquals(tc, 25, averageFlow, 0.001);
}

void minFlowTest(CuTest* tc)
{
    double minFlow = 0;
    int len = 5;
    int time = 3;

    flow flowArray[5] = {
        {3600, 10},
        {3600*2, 35},
        {3600*3, 20},
        {3600*4, 30},
        {3600*5, 15}
    };

    minFlow = min_max_flow(time, MIN, flowArray, len);
    CuAssertDblEquals(tc, 15.0, minFlow, 0.001);

    time = 5;
    minFlow = min_max_flow(time, MIN, flowArray, len);
    CuAssertDblEquals(tc, 10.0, minFlow, 0.001);
}

void maxFlowTest(CuTest* tc)
{
    double maxFlow = 0;
    int len = 5;
    int time = 3;

    flow flowArray[5] = {
        {3600, 10},
        {3600*2, 35},
        {3600*3, 20},
        {3600*4, 30},
        {3600*5, 15}
    };

    maxFlow = min_max_flow(time, MAX, flowArray, len);
    CuAssertDblEquals(tc, 30.0, maxFlow, 0.001);

    time = 5;
    maxFlow = min_max_flow(time, MAX, flowArray, len);
    CuAssertDblEquals(tc, 35.0, maxFlow, 0.001);
}

void overflowOccurrencesTest(CuTest* tc)
{
    overflow_period *overflow;
    int len = 10;
    float threshold = 0;
    int overflowCount = 0;

    height heightArray[10] = {
        {3600, 2.3},
        {3600*2, 3.4},
        {3600*3, 3.5},
        {3600*4, 2.4},
        {3600*5, 2.8},
        {3600*6, 2.3},
        {3600*7, 3.7},
        {3600*8, 3.5},
        {3600*9, 2.3},
        {3600*10, 2.4}
    };

    threshold = 3;
    overflow = overflow_occurrences(heightArray, len, threshold, &overflowCount);
    CuAssertIntEquals(tc, 2, overflowCount);
    CuAssertIntEquals(tc, 3600*2, overflow[0].start);
    CuAssertIntEquals(tc, 3600*4, overflow[0].end);

    CuAssertIntEquals(tc, 3600*7, overflow[1].start);
    CuAssertIntEquals(tc, 3600*9, overflow[1].end);
}

void flowFileTest(CuTest* tc)
{
    int size = 0;
    int referenceStartTime = 1000;
    int lineNumber;
    flow *flowArray;

    flowArray = flow_array_from_file("./data/testdata.txt", &size, referenceStartTime);

    lineNumber = 1;
    CuAssertIntEquals(tc, 110 + referenceStartTime, flowArray[lineNumber - 1].timestamp);
    CuAssertDblEquals(tc, 975062, flowArray[lineNumber - 1].flow, 0.001);

    lineNumber = 100;
    CuAssertIntEquals(tc, 605 + referenceStartTime, flowArray[lineNumber - 1].timestamp);
    CuAssertDblEquals(tc, 932307, flowArray[lineNumber - 1].flow, 0.001);

    lineNumber = 254;
    CuAssertIntEquals(tc, 1375 + referenceStartTime, flowArray[lineNumber - 1].timestamp);
    CuAssertDblEquals(tc, 980565, flowArray[lineNumber - 1].flow, 0.001);

    lineNumber = 999;
    CuAssertIntEquals(tc, 5100 + referenceStartTime, flowArray[lineNumber - 1].timestamp);
    CuAssertDblEquals(tc, 937841, flowArray[lineNumber - 1].flow, 0.001);

    lineNumber = 1000;
    CuAssertIntEquals(tc, 5105 + referenceStartTime, flowArray[lineNumber - 1].timestamp);
    CuAssertDblEquals(tc, 920924, flowArray[lineNumber - 1].flow, 0.001);
}


CuSuite* CuStringGetSuite(void)
{
    CuSuite* suite = CuSuiteNew();

    SUITE_ADD_TEST(suite, averageFlowTest);
    SUITE_ADD_TEST(suite, minFlowTest);
    SUITE_ADD_TEST(suite, maxFlowTest);
    SUITE_ADD_TEST(suite, overflowOccurrencesTest);
    SUITE_ADD_TEST(suite, flowFileTest);


	return suite;
}

CuSuite* CuStringGetSuite();
    
void RunAllTests(void) {
    CuString *output = CuStringNew();
    CuSuite* suite = CuSuiteNew();
    
    CuSuiteAddSuite(suite, CuStringGetSuite());

    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
}

int main(void) {
    RunAllTests();
}
