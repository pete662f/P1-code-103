#include "functions.h"
#include "CuTest.h"

#define LEN 3

void averageFlowTest(CuTest* tc)
{
    flow flowArray[LEN] = {
        {3600, 20},
        {3600*2, 30},
        {3600*3, 15}
    };

    double averageFlow = average_flow(2, flowArray, LEN);

    CuAssertDblEquals(tc, 25.0, averageFlow, 0.001);
    
}

CuSuite* CuStringGetSuite(void)

{
	CuSuite* suite = CuSuiteNew();

	SUITE_ADD_TEST(suite, averageFlowTest);


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