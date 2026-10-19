
#include <iostream>
#include "DecisionEngine.h"

const char* riskName(RiskLevel risk)
{
    switch (risk)
    {
        case LOW_RISK: return "LOW_RISK";
        case MODERATE_RISK: return "MODERATE_RISK";
        case HIGH_RISK: return "HIGH_RISK";
        case INSUFFICIENT_DATA: return "INSUFFICIENT_DATA";
        default: return "UNKNOWN";
    }
}

int main()
{
    DecisionEngine engine;

    SystemData tests[] =
    {
        {8,  40, 50, true,  false, false}, // LOW
        {8,  70, 50, true,  false, false}, // MODERATE
        {8,  85, 95, true,  false, false}, // HIGH
        {8,  85, 70, true,  false, false}, // MODERATE
        {8,  40, 50, false, false, false}, // INSUFFICIENT
        {8,  40, 50, true,  true,  false}, // MODERATE
        {8,  40, 50, true,  true,  true}   // HIGH
    };

    RiskLevel expected[] =
    {
        LOW_RISK,
        MODERATE_RISK,
        HIGH_RISK,
        MODERATE_RISK,
        INSUFFICIENT_DATA,
        MODERATE_RISK,
        HIGH_RISK
    };

    int total = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < total; i++)
    {
        RiskAssessment result = engine.evaluate(tests[i]);

        std::cout << "Test " << i + 1
                  << " | Expected: " << riskName(expected[i])
                  << " | Actual: " << riskName(result.risk)
                  << " | Explanation: " << result.explanation;

        if (result.risk == expected[i])
        {
            std::cout << " | PASS\n";
            passed++;
        }
        else
        {
            std::cout << " | FAIL\n";
        }
    }

    std::cout << "\nResults: " << passed
              << "/" << total << " tests passed.\n";

    return (passed == total) ? 0 : 1;
}
