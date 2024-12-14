#include "functions.h"
#include "CuTest.h"

#define LEN 3

void flowArrayTest(CuTest* tc)
{
    int hour = 60*60;

    flow flowArray[LEN] = {
        {hour, 20},
        {hour, 30},
        {hour, 15}
    };

    double averageFlow = average_flow(2, flowArray, LEN);

    CuAssertDblEquals(tc, 25.0, averageFlow, 0.001);
    
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