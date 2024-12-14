#include "functions.h"
#include "CuTest.h"

#define L

void flowArrayTest(CuTest* tc)
{
    data dataArray[3] = {
        {1, 10},
        {2, 20},
        {3, 10}
    };
    
    flow *flowArray = flow_array(dataArray, 3);

    CuAssertIntEquals(tc, 1, flow[0].timestamp);
    CuAssertDblEquals(tc, 3, flow[0].flow. 0.001);

    CuAssertIntEquals(tc, 1, flow[1].timestamp);
    CuAssertDblEquals(tc, 3, flow[1].flow. 0.001);

    CuAssertIntEquals(tc, 1, flow[2].timestamp);
    CuAssertDblEquals(tc, 3, flow[2].flow. 0.001);
    
}


CuSuite* CuStringGetSuite(void)
{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, flowArrayTest);


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