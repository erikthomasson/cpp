#include "../Includes/TestPriorityQueue.h"
#include <string>

int main(int argc, const char *argv[])
{
    size_t iterations = 0;
    if (argc < 2)
    {
        std::cout << "Number of iterations missing., defaulting to 15" << std::endl;
        iterations = 15;
    }
    else
    {
        iterations = static_cast<size_t>(std::stoull(argv[1]));
    }
    if (UnitTests::PRIORITYQUEUE::PriorityQueueUnitTests(iterations))
    {
        std::cout << "\nAll Unit Tests passed." << std::endl;
    }
    else
    {
        std::cout << "\nUnit tests failed on one or more tests." << std::endl;
        std::cout << "Please note that all tests must pass for your submission to be assessed." << std::endl;
    }
}