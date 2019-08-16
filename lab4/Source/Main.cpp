#include "DataContainer.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"
#include <chrono>
#include <list>
#include <deque>
#include <fstream>
#include <random>
#include <ratio>
using namespace std::chrono;
typedef duration<unsigned int, std::nano> DurationNano;
typedef time_point<steady_clock, DurationNano> SteadyClockTimePoint;

int main()
{
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<unsigned int> distribution(0, 10000);
    std::ifstream wordsFile("Lab4_TestFile");
    int count = 0;
    SteadyClockTimePoint tot_IMPL_Linkedlist, tot_IMPL_V, IMPL_LinkedList100, IMPL_V100, push_IMPL_LinkedList, push_IMPL_V;
    SteadyClockTimePoint tot_IMPL_Linkedlistint, tot_IMPL_Vint, IMPL_LinkedList100int, IMPL_V100int, push_IMPL_LinkedListint, push_IMPL_Vint;

    SteadyClockTimePoint totLinkedList, totV, LinkedList100, V100, pushLinkedList, pushV;
    SteadyClockTimePoint totLinkedListint, totVint, LinkedList100int, V100int, pushLinkedListint, pushVint;

    std::string totsumIMPL_LinkedList, totsum_IMPL_V, sum100IMPL_LinkedList, sum100_IMPL_V;
    std::string totsuIMPL_LinkedList, totsumV, sum100LinkedList, sum100V;

    LinkedList<std::string> string_LinkedList;
    Vector<std::string> string_Vector;
    std::deque<std::string> std_string_Vector;
    std::list<std::string> std_string_LinkedList;

    int totsumIMPL_LinkedListint, totsum_IMPL_Vint, sum100IMPL_LinkedListint, sum100_IMPL_Vint;
    int totsuIMPL_LinkedListint, totsumVint, sum100LinkedListint, sum100Vint;

    LinkedList<int> int_LinkedList;
    Vector<int> int_Vector;
    std::deque<int> std_int_Vector;
    std::list<int> std_int_LinkedList;

    for (int i = 0; i < 10000; i++)
    {
        count = distribution(engine);
        if (i % 2 == 0)
        {
            SteadyClockTimePoint start;
            SteadyClockTimePoint end;

            start = steady_clock::now();
            int_LinkedList.PushBack(count);
            end = steady_clock::now();

            push_IMPL_LinkedListint += end - start;

            start = steady_clock::now();
            int_Vector.PushBack(count);
            end = steady_clock::now();

            push_IMPL_Vint += end - start;

            start = steady_clock::now();
            std_int_LinkedList.push_back(count);
            end = steady_clock::now();

            pushLinkedListint += end - start;

            start = steady_clock::now();
            std_int_Vector.push_back(count);
            end = steady_clock::now();

            pushVint += end - start;
        }
        else
        {
            SteadyClockTimePoint start;
            SteadyClockTimePoint end;

            start = steady_clock::now();
            int_Vector.PushFront(count);
            end = steady_clock::now();

            push_IMPL_Vint += end - start;

            start = steady_clock::now();
            int_LinkedList.PushFront(count);
            end = steady_clock::now();

            push_IMPL_LinkedListint += end - start;

            start = steady_clock::now();
            std_int_LinkedList.push_front(count);
            end = steady_clock::now();

            pushLinkedListint += end - start;

            start = steady_clock::now();
            std_int_Vector.push_front(count);
            end = steady_clock::now();

            pushVint += end - start;
        }
    }
    count = 0;
    if (wordsFile.is_open())
    {
        while (wordsFile.good())
        {
            std::string word = "";
            std::getline(wordsFile, word, '\n');
            SteadyClockTimePoint start;
            SteadyClockTimePoint end;
            if (count % 2 == 0)
            {
                start = steady_clock::now();
                string_LinkedList.PushBack(word);
                end = steady_clock::now();

                push_IMPL_LinkedList += end - start;

                start = steady_clock::now();
                string_Vector.PushBack(word);
                end = steady_clock::now();

                push_IMPL_V += end - start;

                start = steady_clock::now();
                std_string_LinkedList.push_back(word);
                end = steady_clock::now();

                pushLinkedList += end - start;

                start = steady_clock::now();
                std_string_Vector.push_back(word);
                end = steady_clock::now();

                pushV += end - start;
            }
            else
            {
                start = steady_clock::now();
                string_LinkedList.PushFront(word);
                end = steady_clock::now();

                push_IMPL_LinkedList += end - start;

                start = steady_clock::now();
                string_Vector.PushFront(word);
                end = steady_clock::now();

                push_IMPL_V += end - start;

                start = steady_clock::now();
                std_string_LinkedList.push_front(word);
                end = steady_clock::now();

                pushLinkedList += end - start;

                start = steady_clock::now();
                std_string_Vector.push_front(word);
                end = steady_clock::now();

                pushV += end - start;
            }
            count++;
        }
    }
    auto int_index = std_int_LinkedList.begin();
    auto string_index = std_string_LinkedList.begin();
    for (int i = 0; i < 10000; i++)
    {
        SteadyClockTimePoint start;
        SteadyClockTimePoint end;

        start = steady_clock::now();
        totsumIMPL_LinkedList += string_LinkedList[i];
        end = steady_clock::now();

        tot_IMPL_Linkedlist += end - start;

        start = steady_clock::now();
        totsum_IMPL_V += string_Vector[i];
        end = steady_clock::now();

        tot_IMPL_V += end - start;

        start = steady_clock::now();
        totsuIMPL_LinkedList += *string_index;
        end = steady_clock::now();

        totLinkedList += end - start;

        start = steady_clock::now();
        totsumV += std_string_Vector[i];
        end = steady_clock::now();

        totV += end - start;

        start = steady_clock::now();
        totsumIMPL_LinkedListint += int_LinkedList[i];
        end = steady_clock::now();

        tot_IMPL_Linkedlistint += end - start;

        start = steady_clock::now();
        totsum_IMPL_Vint += int_Vector[i];
        end = steady_clock::now();

        tot_IMPL_Vint += end - start;

        start = steady_clock::now();
        totsuIMPL_LinkedListint += *int_index;
        end = steady_clock::now();

        totLinkedListint += end - start;

        start = steady_clock::now();
        totsumVint += std_int_Vector[i];
        end = steady_clock::now();

        totVint += end - start;

        if (i % 100 == 0)
        {
            start = steady_clock::now();
            sum100IMPL_LinkedList += string_LinkedList[i];
            end = steady_clock::now();

            IMPL_LinkedList100 += end - start;

            start = steady_clock::now();
            sum100_IMPL_V += string_Vector[i];
            end = steady_clock::now();

            IMPL_V100 += end - start;
            /*
            start = steady_clock::now();
            sum100LinkedList += *string_index;
            end = steady_clock::now();

            LinkedList100 += end - start;
            */
            start = steady_clock::now();
            sum100V += std_string_Vector[i];
            end = steady_clock::now();

            V100 += end - start;

            start = steady_clock::now();
            sum100IMPL_LinkedListint += int_LinkedList[i];
            end = steady_clock::now();

            IMPL_LinkedList100int += end - start;

            start = steady_clock::now();
            sum100_IMPL_Vint += int_Vector[i];
            end = steady_clock::now();

            IMPL_V100int += end - start;
            /*
            start = steady_clock::now();
            sum100LinkedListint += *int_index;
            end = steady_clock::now();

            LinkedList100int += end - start;
            */

            start = steady_clock::now();
            sum100Vint += std_int_Vector[i];
            end = steady_clock::now();

            V100int += end - start;
        }
        int_index++;
        string_index++;
    }

   int_index = std_int_LinkedList.begin();
    for (int i = 0; i < 10000; i++)
    {
        SteadyClockTimePoint start;
        SteadyClockTimePoint end;
        start = steady_clock::now();
        
        if (i % 100 == 0){
            sum100LinkedListint += *int_index;
        }
        int_index++;
        end = steady_clock::now();
        LinkedList100int += end - start;
        
    }
    string_index = std_string_LinkedList.begin();
    for (int i = 0; i < 10000; i++)
    {
        SteadyClockTimePoint start;
        SteadyClockTimePoint end;
        start = steady_clock::now();
        if (i % 100 == 0){
            sum100LinkedList += *string_index;
        }
        string_index++;
        end = steady_clock::now();
        LinkedList100 += end - start;
    }

    //Test for Operator[](access operator)
    std::cout << "Test for access operator\n\n";

    if (totsuIMPL_LinkedList[10] == totsumIMPL_LinkedList[10])
        std::cout << "Operator[] works for LinkedList implementation" << std::endl;
    else
        std::cout << "Operator[] does not work for LinkedList implementation" << std::endl;

    if (totsumV[0] == totsum_IMPL_V[0])
        std::cout << "Operator[] works for Vector implementation" << std::endl;
    else
        std::cout << "Operator[] does not work for Vector implementation" << std::endl;

    std::cin.get();

    //Test for pushback operator
    std::cout << "Test for pushback operator\n";
    std::cout << "If access operator does not work this test wont work either\n\n";
    int_LinkedList.PushBack(count);
    std_int_LinkedList.push_back(count);

    if (int_LinkedList[int_LinkedList.Size() - 1] == std_int_LinkedList.back())
        std::cout << "The pushback operator works for the implemented LinkedList" << std::endl;
    else
        std::cout << "The pushback operator does not work for the implemented LinkedList" << std::endl;

    int_Vector.PushBack(count);
    std_int_Vector.push_back(count);
    if (int_Vector[int_Vector.Size() - 1] == std_int_Vector[std_int_Vector.size() - 1])
        std::cout << "The pushback operator works for the implemented Vector" << std::endl;
    else
        std::cout << "The pushback operator does not work for the implemented Vector" << std::endl;

    std::cin.get();

    //Test for pushfront operator
    std::cout << "\nTest for pushfront operator\n";
    std::cout << "If access operator does not work this test wont work either\n\n";

    string_LinkedList.PushFront("Test");
    std_string_LinkedList.push_front("Test");
    auto index2 = std_string_LinkedList.begin();
    if (string_LinkedList[0] == *index2)
        std::cout << "The pushfront operator works for the implemented LinkedList" << std::endl;
    else
        std::cout << "The pushfront operator does not work for the implemented LinkedList" << std::endl;

    string_Vector.PushFront("Test");
    std_string_Vector.push_front("Test");
    if (string_Vector[0] == std_string_Vector[0])
        std::cout << "The pushfront operator works for the implemented Vector" << std::endl;
    else
        std::cout << "The pushfront operator does not work for the implemented Vector" << std::endl;
    
    std::cin.get();

    std::cout << "\n\n";

    if (sum100IMPL_LinkedListint != sum100LinkedListint)
        std::cout << "The implemented LinkedList(int) is not identical with std LinkedList(int) for every 100th element" << std::endl;
    else std::cout << "The implemented LinkedList(int) is identical with std LinkedList(int) for every 100th element" << std::endl;
    if (sum100_IMPL_Vint != sum100Vint)
        std::cout << "The implemented Vector(int) is not identical with std Vector(int) for every 100th element" << std::endl;
    else std::cout << "The implemented Vector(int) is identical with std Vector(int) for every 100th element" << std::endl;
    if (sum100IMPL_LinkedList != sum100LinkedList)
        std::cout << "The implemented LinkedList(string) is not identical with std LinkedList(string) for every 100th element" << std::endl;
    else std::cout << "The implemented LinkedList(string) is identical with std LinkedList(string) for every 100th element" << std::endl;
    if (sum100_IMPL_V != sum100V)
        std::cout << "The implemented Vector(string) is not identical with std Vector(string) for every 100th element" << std::endl;
    else std::cout << "The implemented Vector(string) is identical with std Vector(string) for every 100th element" << std::endl;

    std::cin.get();

    if (totsumIMPL_LinkedListint != totsuIMPL_LinkedListint)
        std::cout << "The implemented LinkedList(int) is not identical with std LinkedList(int)" << std::endl;
    else std::cout << "The implemented LinkedList(int) is identical with std LinkedList(int)" << std::endl;
    if (totsum_IMPL_Vint != totsumVint)
        std::cout << "The implemented Vector(int) is not identical with std Vector(int)" << std::endl;
    else std::cout << "The implemented Vector(int) is identical with std Vector(int)" << std::endl;
    if (totsumIMPL_LinkedList != totsuIMPL_LinkedList)
        std::cout << "The implemented LinkedList(string) is not identical with std LinkedList(string)" << std::endl;
    else std::cout << "The implemented LinkedList(string) is identical with std LinkedList(string)" << std::endl;
    if (totsum_IMPL_V != totsumV)
        std::cout << "The implemented Vector(int) is not identical with std Vector(int)" << std::endl;
    else std::cout << "The implemented Vector(int) is  identical with std Vector(int)" << std::endl;
    unsigned long long totalTime;

    std::cin.get();

    //Own LinkedList with string
    std::cout << "Own LinkedList with string\n\n";
    std::cout << "Elapsed time for adding elements from own LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(push_IMPL_LinkedList.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from own LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(IMPL_LinkedList100.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from own LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(tot_IMPL_Linkedlist.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(tot_IMPL_Linkedlist.time_since_epoch()).count()) + (duration_cast<nanoseconds>(IMPL_LinkedList100.time_since_epoch()).count()) + (duration_cast<nanoseconds>(push_IMPL_LinkedList.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing own LinkedList(string) :\n";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\nstd::list with string\n\n";

    //std::list with string
    std::cout << "Elapsed time for adding elements from std::LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(pushLinkedList.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from std::LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(LinkedList100.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from std::LinkedList(string) :\n";
    std::cout << duration_cast<nanoseconds>(totLinkedList.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(totLinkedList.time_since_epoch()).count()) + (duration_cast<nanoseconds>(LinkedList100.time_since_epoch()).count()) + (duration_cast<nanoseconds>(pushLinkedList.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing std::LinkedList(string) :\n";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\n\n";

    std::cin.get();

    //Own LinkedList with int
    std::cout << "Own LinkedList with int\n\n";
    std::cout << "Elapsed time for adding elements from own LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(push_IMPL_LinkedListint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from own LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(IMPL_LinkedList100int.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from own LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(tot_IMPL_Linkedlistint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(tot_IMPL_Linkedlistint.time_since_epoch()).count()) + (duration_cast<nanoseconds>(IMPL_LinkedList100int.time_since_epoch()).count()) + (duration_cast<nanoseconds>(push_IMPL_LinkedListint.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing own LinkedList(int) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\nstd::list with int\n\n";

    //std::list with int
    std::cout << "Elapsed time for adding elements from std::LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(pushLinkedListint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from std::LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(LinkedList100int.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from std::LinkedList(int) :\t";
    std::cout << duration_cast<nanoseconds>(totLinkedListint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(totLinkedListint.time_since_epoch()).count()) + (duration_cast<nanoseconds>(LinkedList100int.time_since_epoch()).count()) + (duration_cast<nanoseconds>(pushLinkedListint.time_since_epoch()).count());

    std::cout << "Total elapsed implementing from std::LinkedList(int) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\n\n";

    std::cin.get();

    //Own Vetor with string
    std::cout << "Own Vetor with string\n\n";
    std::cout << "Elapsed time for adding elements from own Vector(string) :\t";
    std::cout << duration_cast<nanoseconds>(push_IMPL_V.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from own Vector(string) :\t";
    std::cout << duration_cast<nanoseconds>(IMPL_V100.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from own Vector(string) :\t";
    std::cout << duration_cast<nanoseconds>(tot_IMPL_V.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(tot_IMPL_V.time_since_epoch()).count()) + (duration_cast<nanoseconds>(IMPL_V100.time_since_epoch()).count()) + (duration_cast<nanoseconds>(push_IMPL_V.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing own Vector(string) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\nstd::queue with string\n\n";

    //std::queue with string
    std::cout << "Elapsed time for adding elements from std::deque(string) :\t";
    std::cout << duration_cast<nanoseconds>(pushV.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from std::deque(string) :\t";
    std::cout << duration_cast<nanoseconds>(V100.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from std::deque(string) :\t";
    std::cout << duration_cast<nanoseconds>(totV.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(totV.time_since_epoch()).count()) + (duration_cast<nanoseconds>(V100.time_since_epoch()).count()) + (duration_cast<nanoseconds>(pushV.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing std::deque(string) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\n\n";

    std::cin.get();

    //Own Vector with int
    std::cout << "Own Vector with int\n\n";
    std::cout << "Elapsed time for adding elements from own Vector (int) :\t";
    std::cout << duration_cast<nanoseconds>(push_IMPL_Vint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from own Vector (int) :\t";
    std::cout << duration_cast<nanoseconds>(IMPL_V100int.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from own Vector (int) :\t";
    std::cout << duration_cast<nanoseconds>(tot_IMPL_Vint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(tot_IMPL_Vint.time_since_epoch()).count()) + (duration_cast<nanoseconds>(IMPL_V100int.time_since_epoch()).count()) + (duration_cast<nanoseconds>(push_IMPL_Vint.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing own Vector (int) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\n\nstd::queue with int\n\n";

    //std::queue with int
    std::cout << "Elapsed time for adding elements from std::deque (int) :\t";
    std::cout << duration_cast<nanoseconds>(pushVint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every 100 element from std::deque (int) :\t";
    std::cout << duration_cast<nanoseconds>(V100int.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    std::cout << "Elapsed time for accessing every element from std::deque (int) :\t";
    std::cout << duration_cast<nanoseconds>(totVint.time_since_epoch()).count();
    std::cout << " nanoseconds."
              << "\n\n";

    totalTime = (duration_cast<nanoseconds>(totVint.time_since_epoch()).count()) + (duration_cast<nanoseconds>(V100int.time_since_epoch()).count()) + (duration_cast<nanoseconds>(pushVint.time_since_epoch()).count());

    std::cout << "Total elapsed time implementing std::deque (int) :\t";
    std::cout << totalTime;
    std::cout << " nanoseconds."
              << "\n\n";

    std::cin.get();
}
