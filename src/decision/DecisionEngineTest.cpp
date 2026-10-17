#include <iostream>
#include "DecisionEngine.h"

const char* recommendationName(Recommendation result)
{
    switch (result)
    {
        case LIGHT: return "LIGHT";
        case MEDIUM: return "MEDIUM";
        case HEAVY: return "HEAVY";
        default: return "NO_RECOMMENDATION";
    }
}

int main()
{
    DecisionEngine engine;

    // Prototype test data: installed RAM, average usage, peak usage
    SystemData tests[] =
    {
        {8,  40, 50},  // Expected: LIGHT
        {8,  70, 50},  // Expected: MEDIUM
        {8,  85, 95},  // Expected: HEAVY
        {8,  85, 70},  // Expected: MEDIUM
        {16, 80, 95},  // Expected: MEDIUM
        {16, 60, 99}   // Expected: LIGHT
    };

    Recommendation expected[] =
    {
        LIGHT,
        MEDIUM,
        HEAVY,
        MEDIUM,
        MEDIUM,
        LIGHT
    };

    int totalTests = sizeof(tests) / sizeof(tests[0]);
    int passed = 0;

    for (int i = 0; i < totalTests; i++)
    {
        Recommendation actual = engine.evaluate(tests[i]);

        std::cout << "Test " << i + 1
                  << " | Average: " << tests[i].averageUsage << "%"
                  << " | Peak: " << tests[i].peakUsage << "%"
                  << " | Expected: " << recommendationName(expected[i])
                  << " | Actual: " << recommendationName(actual);

        if (actual == expected[i])
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
              << "/" << totalTests << " tests passed.\n";

    return (passed == totalTests) ? 0 : 1;
}