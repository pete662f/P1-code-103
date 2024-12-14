#include "functions.h"
#include "CuTest.h"

enum minMaxBit {
    MIN,
    MAX
};

void averageFlowTest(CuTest* tc)
{
    double averageFlow = 0;
    int len = 3;
    int time = 0;

    flow flowArray[3] = {
        {3600, 20},
        {3600*2, 30},
        {3600*3, 15}
    };

    time = 2;
    averageFlow = average_flow(time, flowArray, len);
    CuAssertDblEquals(tc, 25.0, averageFlow, 0.001);
}

void minFlowTest(CuTest* tc)
{
    double minFlow = 0;
    int len = 5;
    int time = 0;

    flow flowArray[5] = {
        {3600, 20},
        {3600*2, 30},
        {3600*3, 15},
        {3600*4, 35},
        {3600*4, 10}
    };

    time = 3;
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
    int time = 0;

    flow flowArray[5] = {
        {3600, 20},
        {3600*2, 30},
        {3600*3, 15},
        {3600*4, 35},
        {3600*4, 10}
    };

    time = 3;
    maxFlow = min_max_flow(time, MAX, flowArray, len);
    CuAssertDblEquals(tc, 30.0, maxFlow, 0.001);

    time = 5;
    maxFlow = min_max_flow(time, MAX, flowArray, len);
    CuAssertDblEquals(tc, 35.0, maxFlow, 0.001);
}

CuSuite* CuStringGetSuite(void)

{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, averageFlowTest);
    SUITE_ADD_TEST(suite, minFlowTest);
    SUITE_ADD_TEST(suite, maxFlowTest);


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