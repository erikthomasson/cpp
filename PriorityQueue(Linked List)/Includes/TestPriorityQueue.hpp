#ifndef TEST_VECTOR_HPP
#define TEST_VECTOR_HPP

/*******************************************************************
*						Here be Dragons
********************************************************************/

#include "TestingBase.hpp"
#include <cstdint>
#include <iostream>

#if __has_include("PriorityQueue.h")
#include "PriorityQueue.h"
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
namespace UnitTests::PRIORITYQUEUE
{
	/*
	*
	*   Operator and Constructors
	*
	*/
	static constexpr bool PriorityQueue_has_constructor = std::is_default_constructible<PriorityQueue<int>>::value;

	/*
	*
	*
	*   Functions
	*
	*
	*/
	GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(enqueue)
		GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(dequeue)
		GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(peek)
		GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(size)
		GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(isEmpty)
		GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(peek)
		GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(size)
		GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(isEmpty)

		static constexpr bool PriorityQueue_has_enqueue = (has_enqueue<PriorityQueue<int>, void, int>::value ||
			has_enqueue<PriorityQueue<int>, void, int &>::value ||
			has_enqueue<PriorityQueue<int>, void, const int &>::value) &&
		!has_enqueue<PriorityQueue<int>, void, int &&>::value;

	static constexpr bool PriorityQueue_has_dequeue = has_dequeue<PriorityQueue<int>, void>::value;
	static constexpr bool PriorityQueue_has_correct_peek = has_const_peek<PriorityQueue<int>, const int &>::value;
	static constexpr bool PriorityQueue_has_correct_size = has_const_size<PriorityQueue<int>, std::size_t>::value;
	static constexpr bool PriorityQueue_has_correct_isEmpty = has_const_isEmpty<PriorityQueue<int>, bool>::value;
	//REMEMBER! CONST OR NON-CONST => MESSAGE! RETURN TYPE FOR PEEK!
	static constexpr bool PriorityQueue_has_incorrect_peek = has_const_peek<PriorityQueue<int>, int &>::value ||
		has_const_peek<PriorityQueue<int>, int>::value ||
		has_peek<PriorityQueue<int>, const int &>::value ||
		has_peek<PriorityQueue<int>, int &>::value ||
		has_peek<PriorityQueue<int>, int>::value;

	static constexpr bool PriorityQueue_has_incorrect_size = has_size<PriorityQueue<int>, std::size_t>::value;
	static constexpr bool PriorityQueue_has_incorrect_isEmpty = has_isEmpty<PriorityQueue<int>, bool>::value;

	template <typename T = PriorityQueue<int>>
	bool TestEnqueue()
	{
		std::cout << "\n\tTesting function PriorityQueue::enqueue." << std::endl;
		
		if constexpr (PriorityQueue_has_enqueue)
		{
			std::mt19937 engine(0);
			std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
			T* queuePtr = nullptr;
			
			try
			{
				queuePtr = new T();

			}
			catch (const std::exception &e)
			{
				std::cerr << "\tError on default-construction of PriorityQueue<int>. Testing cannot continue. \n\t\tError message: " << e.what() << '\n';
				return false;
			}
			try
			{
				
				delete queuePtr;
				
			}
			catch (const std::exception& e)
			{
				std::cerr << "\tError on destruction of default-constructed PriorityQueue<int> object. Testing cannot continue. \n\t\tError message: " << e.what() << std::endl;
				return false;
			}

			T queue;
		
			std::cout << "\t\tTesting the function enqueue with insertion of 1000 random integers." << std::endl;
			int i = 0;
			try
			{
				std::cout << "\t\t\tStarting insertion." << std::endl;
				std::cout << "\t\t\t\t";
				
				
				for (i = 0; i < 1000; ++i)
				{
					
					
					queue.enqueue(dist(engine));
					
					

					if (!(i % 100))
						std::cout << ' ' << i / 10 << "%...";
				}
				std::cout << "\n\t\t\tLoop finished." << std::endl;
			}
			catch (const std::exception &e)
			{
				std::cerr << "\tError on call " << i << " to enqueue. Testing cannot continue. \n\t\tError message: " << e.what() << '\n';
				return false;
			}

			std::cout << "\tPriorityQueue::enqueue working as expected." << std::endl;
			return true;
		}
		else
		{
			std::cout << "\tTests cannot be conducted: No matching enqueue function found." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TestDequeue()
	{
		std::cout << "\n\tTesting function PriorityQueue::dequeue" << std::endl;
		if constexpr (PriorityQueue_has_dequeue)
		{
			if constexpr (PriorityQueue_has_enqueue && (PriorityQueue_has_correct_peek || PriorityQueue_has_incorrect_peek))
			{
				std::cout << "\t\tTesting function dequeue by inserting the sequence {10,9...1}. Expect to get the sequence {1,2...10} during dequeue." << std::endl;
				T queue;
				for (int i = 10; i != 0; --i)
					queue.enqueue(i);

				for (int i = 1; i != 11; ++i)
				{
					std::cout << "\t\t\tExpect to dequeue value " << std::setw(3) << i << ". To be dequeued: " << std::setw(3) << queue.peek();
					if (queue.peek() != i)
					{
						std::cout << "\tError on dequeue, wrong value extracted. Testing cannot continue." << std::endl;
						return false;
					}
					std::cout << std::endl;
					queue.dequeue();
				}
				std::cout << "\t\tFunction dequeue passed the first test, expected sequence provided." << std::endl;
				if constexpr (PriorityQueue_has_correct_isEmpty || PriorityQueue_has_incorrect_isEmpty)
				{
					std::mt19937 engine(0);
					std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

					std::cout << "\t\tFunction dequeue tested on a bigger dataset, elements enqueued and dequeued after set rules." << std::endl;
					std::vector<int> controll;
					std::cout << "\t\t\tInserting 1'000 elements through the use of enqueue." << std::endl;
					for (size_t i = 0; i < 1000; ++i)
					{
						int rand = dist(engine);
						controll.push_back(rand);
						queue.enqueue(rand);
					}
					std::cout << "\t\t\tInsertion done." << std::endl;

					std::sort(controll.begin(), controll.end());
					auto it = controll.begin();
					std::cout << "\t\t\tThis test will dequeue 100 elements at a time, before inserting 25 new ones. This will continue until the set is empty." << std::endl;
					std::uint8_t counter = 0;
					while (it != controll.end() && !queue.isEmpty())
					{
						if (counter == 100)
						{
							std::cout << "\t\t\t\t100 elements dequeued without errors, adding 25 new elements." << std::endl;
							controll.erase(controll.begin(), it);
							for (size_t i = 0; i < 25; ++i)
							{
								int rand = dist(engine);
								controll.push_back(rand);
								queue.enqueue(rand);
							}
							std::cout << "\t\t\t\t25 elements added to the PriorityQueue, dequeueing continues." << std::endl;
							std::sort(controll.begin(), controll.end());
							it = controll.begin();
							counter = 0;
						}
						if (*it != queue.peek())
						{
							std::cout << "\t\tError on dequeue. Expected value: " << std::setw(12) << *it << " Recieved value: " << std::setw(12) << queue.peek() << std::endl;
							std::cout << "\t\tTesting cannot be continued." << std::endl;
							it = controll.erase(controll.begin(), it);
							std::cout << "\t\tControll values remaining: " << controll.size() << " Queue values remaining: " << queue.size() << std::endl;
							std::cout << "\t\tPrinting all remaining values: " << std::endl;
							while (it != controll.end() && !queue.isEmpty())
							{
								std::cout << "\t\t\tExpected value: " << *it << " Queue value:" << queue.peek() << std::endl;
								queue.dequeue();
								++it;
							}
							std::cout << "\tPriorityQueue::dequeue not working as expected." << std::endl;
							return false;
						}
						++counter;
						++it;
						queue.dequeue();
					}
					if (it != controll.end())
					{
						std::cout << "\t\t\tError: Controll on 10'000 elements indicate that queue has dropped one or more elements. Testing cannot be continued." << std::endl;
						return false;
					}
					std::cout << "\t\t\tTest on alternating enqueue and dequeue done." << std::endl;
					std::cout << "\tPriorityQueue::dequeue working as expected." << std::endl;

					return true;
				}
				else
				{
					std::cout << "\t\tSecondary test on PriorityQueue::dequeue requires isEmpty to be implemented." << std::endl;
					std::cout << "\tSecondary test on PriorityQueue::dequeue cannot be conducted." << std::endl;
					return false;
				}
			}
			else
			{
				std::cout << "\t\tTest of PriorityQueue::dequeue requires enqueue and peek to be implemented." << std::endl;
				std::cout << "\tTesting of PriorityQueue::dequeue cannot be conducted." << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "\tTests cannot be conducted: no matching dequeue function found." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TestPeek()
	{
		std::cout << "\n\tStarting tests on PriorityQueue::peek." << std::endl;
		if constexpr (PriorityQueue_has_correct_peek || PriorityQueue_has_incorrect_peek)
		{
			if constexpr (PriorityQueue_has_incorrect_peek)
			{
				std::cout << "\t\tPriorityQueue::peek should be const-declared and return a const reference to the element with the lowest priority." << std::endl;
			}
			if constexpr (PriorityQueue_has_enqueue && PriorityQueue_has_dequeue)
			{
				T queue;
				std::cout << "\t\tEnqueueing 10 elements." << std::endl;
				for (int i = 10; i != 0; --i)
					queue.enqueue(i);

				std::cout << "\t\t\tControll that PriorityQueue::peek returns the minimum value inserted." << std::endl;
				if (queue.peek() != 1)
				{
					std::cout << "\t\tPriorityQueue::peek did not return expected value.\n\t\t\tExpected: 1 Recieved: " << queue.peek() << std::endl;
					std::cout << "\tPriorityQueue::peek does not work as expected. Testing cannot continue." << std::endl;
					return false;
				}
				else
				{
					std::cout << "\t\tPriorityQueue::peek returned expected value." << std::endl;
					std::cout << "\tPriorityQueue::peek working as expected." << std::endl;
					return true;
				}
			}
			else
			{
				std::cout << "\tTests cannot be conducted without enqueue and dequeue implemented." << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "\tTests cannot be conducted: no matching peek function found." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TestSize()
	{
		std::cout << "\n\tStarting tests on PriorityQueue::size." << std::endl;

		if constexpr (PriorityQueue_has_correct_size || PriorityQueue_has_incorrect_size)
		{
			if constexpr (PriorityQueue_has_incorrect_size)
			{
				std::cout << "\t\tPriorityQueue::size should be const-declared and return a size_t containing the number of elements in the queue." << std::endl;
			}
			if constexpr (PriorityQueue_has_enqueue)
			{
				T queue;
				std::cout << "\t\tEnqueing 10 elements." << std::endl;
				for (int i = 10; i != 0; --i)
					queue.enqueue(i);
				std::cout << "\t\tControll that PriorityQueue::size returns number of elements enqueued." << std::endl;
				if (queue.size() != 10)
				{
					std::cout << "\t\tPriorityQueue::size did not return expected value.\n\t\t\tExpected: 10 Recieved: " << queue.size() << std::endl;
					std::cout << "\tPriorityQueue::size not working as expected. Testing cannot continue." << std::endl;
					return false;
				}
				else
				{
					std::cout << "\t\tPriorityQueue::size returned expected value." << std::endl;
					std::cout << "\tPriorityQueue::size working as expected." << std::endl;
					return true;
				}
			}
			else
			{
				std::cout << "\t\tPriorityQueue::size cannot be tested correctly without enqueue implemented." << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "\tTests cannot be conducted: no matching size function found." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TestIsEmpty()
	{
		std::cout << "\n\tStarting tests on PriorityQueue::isEmpty." << std::endl;
		if constexpr (PriorityQueue_has_correct_isEmpty || PriorityQueue_has_incorrect_isEmpty)
		{
			if constexpr (PriorityQueue_has_incorrect_isEmpty)
			{
				std::cout << "\t\tPriorityQueue::isEmpty should be const-declared and return a bool returning whether the PriorityQueue is empty or not." << std::endl;
			}

			T queue;
			std::cout << "\t\tTesting PriorityQueue::isEmpty on empty queue." << std::endl;
			if (!queue.isEmpty())
			{
				std::cout << "\t\t\tPriorityQueue::isEmpty indicated not empty on empty queue." << std::endl;
				std::cout << "\t\tTesting cannot continue." << std::endl;
				std::cout << "\tPriorityQueue::isEmpty does not work as expected." << std::endl;
				return false;
			}
			else
			{
				std::cout << "\t\t\tPriorityQueue::isEmpty returned correctly on empty queue." << std::endl;
				if constexpr (PriorityQueue_has_enqueue)
				{
					std::cout << "\t\tEnqueueing 10 elements." << std::endl;
					for (int i = 10; i != 0; --i)
						queue.enqueue(i);
					std::cout << "\t\tEnqueueing done." << std::endl;

					std::cout << "\t\tTesting PriorityQueue::isEmpty on non-empty queue." << std::endl;
					if (queue.isEmpty())
					{
						std::cout << "\t\t\tPriorityQueue::isEmpty indicated empty on non-empty queue." << std::endl;
						std::cout << "\t\tTesting cannot continue." << std::endl;
						std::cout << "\tPriorityQueue::isEmpty does not work as expected." << std::endl;
						return false;
					}
					else
					{
						std::cout << "\t\t\tPriorityQueue::isEmpty indicated non-empty on non-empty queue." << std::endl;
						std::cout << "\tPriorityQueue::isEmpty working as expected." << std::endl;
						return true;
					}
				}
				else
				{
					std::cout << "\t\tFurther testing on PriorityQueue::isEmpty requires enqueue to be implemented." << std::endl;
					std::cout << "\tTest on PriorityQueue::isEmpty cannot continue." << std::endl;
					return false;
				}
			}
		}
		else
		{
			std::cout << "\tTests cannot be conducted: no matching size function found." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	long double TimeTest(size_t iterations, size_t elements)
	{
		if constexpr ((PriorityQueue_has_correct_isEmpty || PriorityQueue_has_incorrect_isEmpty) && PriorityQueue_has_enqueue && PriorityQueue_has_dequeue)
		{
			static std::mt19937 engine(0);
			static std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

			std::vector<int> randomedNumbers;

			constexpr const long double msConvertion = 1.0 / 1000000.0;

			for (size_t i = 0; i != elements; ++i)
				randomedNumbers.push_back(dist(engine));

			T queue;
			auto startTime = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i != iterations; ++i)
			{
				for (auto &&number : randomedNumbers)
				{
					queue.enqueue(number);
				}
				while (!queue.isEmpty())
					queue.dequeue();
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::uint64_t groundTruth = (endTime - startTime).count();

			return (static_cast<long double>(groundTruth) / iterations) * msConvertion;
		}
		else
		{
			/*Treat warnings as error fix: */
			iterations = elements;
			elements = iterations;
			return 0.0;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TestThrow()
	{
		std::cout << "\n\tTesting exception handling for PriorityQueue." << std::endl;

		if constexpr (PriorityQueue_has_correct_peek || PriorityQueue_has_incorrect_peek)
		{
			T queue;
			std::cout << "\t\tTesting exception handling on PriorityQueue::peek." << std::endl;
			try
			{
				std::cout << "\t\t\tCalling peek on newly-initialized queue." << std::endl;
				queue.peek();
				std::cout << "\t\tException handling not done correctly: No throw issued on empty queue." << std::endl;
				return false;
			}
			catch (std::exception &e)
			{
				std::cout << "\t\t\tException handling done correctly for newly-initialized queue. Exception caught: \n\t\t\t\t" << e.what() << std::endl;
			}
			catch (...)
			{
				std::cout << "\t\t\tException handling done correctly for newly-initialized queue." << std::endl;
			}
			if constexpr (PriorityQueue_has_enqueue && PriorityQueue_has_dequeue)
			{
				std::cout << "\t\t\tAdding elements to the queue." << std::endl;
				queue.enqueue(4);
				std::cout << "\t\t\tRemoving the same element." << std::endl;
				queue.dequeue();
				try
				{
					std::cout << "\t\t\tCalling peek on empty queue thas has had elements added and removed." << std::endl;

					queue.peek();
					std::cout << "\t\tException handling not done correctly: No throw issued on empty queue." << std::endl;
					return false;
				}
				catch (std::exception &e)
				{
					std::cout << "\t\t\tException handling done correctly for newly-initialized queue. Exception caught: \n\t\t\t\t" << e.what() << std::endl;
					std::cout << "\t\tPriorityQueue::peek handling exceptions as expected." << std::endl;
				}
				catch (...)
				{
					std::cout << "\t\t\tException handling done correctly for newly-initialized queue." << std::endl;
					std::cout << "\t\tPriorityQueue::peek handling exceptions as expected." << std::endl;
				}
			}
			else
			{
				std::cout << "\t\t\tFurther tests on exception handling on PriorityQueue::peek requires enqueue and dequeue to be implemented." << std::endl;
			}
		}
		else
		{
			std::cout << "\tException handling cannot be tested on PriorityQueue::peek." << std::endl;
		}
		if constexpr (PriorityQueue_has_dequeue)
		{
			T queue;
			std::cout << "\n\t\tTesting exception handling on PriorityQueue::dequeue." << std::endl;
			try
			{
				std::cout << "\t\t\tCalling delete on newly-initialized queue." << std::endl;
				queue.dequeue();
				std::cout << "\t\tException handling not done correctly: No throw issued on empty queue." << std::endl;
				return false;
			}
			catch (std::exception &e)
			{
				std::cout << "\t\t\tException handling done correctly for newly-initialized queue. Exception caught: \n\t\t\t\t" << e.what() << std::endl;
			}
			catch (...)
			{
				std::cout << "\t\t\tException handling done correctly for newly-initialized queue." << std::endl;
			}
			if constexpr (PriorityQueue_has_enqueue)
			{
				std::cout << "\t\t\tAdding elements to the queue." << std::endl;
				queue.enqueue(4);
				std::cout << "\t\t\tRemoving the same element." << std::endl;
				queue.dequeue();
				try
				{
					std::cout << "\t\t\tCalling dequeue on empty queue thas has had elements added and removed." << std::endl;
					queue.dequeue();
					std::cout << "\t\tException handling not done correctly: No throw issued on empty queue." << std::endl;
					return false;
				}
				catch (std::exception &e)
				{
					std::cout << "\t\t\tException handling done correctly for newly-initialized queue. Exception caught: \n\t\t\t\t" << e.what() << std::endl;
					std::cout << "\t\tPriorityQueue::dequeue handling exceptions as expected." << std::endl;
				}
				catch (...)
				{
					std::cout << "\t\t\tException handling done correctly for newly-initialized queue." << std::endl;
					std::cout << "\t\tPriorityQueue::dequeue handling exceptions as expected." << std::endl;
				}
				std::cout << "\tException handling working as expected." << std::endl;
				return true;
			}
			else
			{
				std::cout << "\t\tPriorityQueue::enqueue required for further throw-tests." << std::endl;
				std::cout << "\tException handling for PriorityQueue::dequeue cannot be further tested." << std::endl;
				return false;
			}
		}
		else
		{
			std::cout << "\tException handling cannot be tested on PriorityQueue::delete." << std::endl;
			return false;
		}
	}

	template <typename T = PriorityQueue<int>>
	bool TimeDiffComputation(size_t iterationsSmallerSet, size_t iterationsBiggerSet, long double timeSmallerSet, long double timeBiggerSet)
	{
		long double diff = timeBiggerSet / timeSmallerSet;
		long double nlognLimit = (iterationsBiggerSet * log2(iterationsBiggerSet)) / (iterationsSmallerSet * log2(iterationsSmallerSet));
		long double nSquaredLimit = static_cast<long double>(iterationsBiggerSet * iterationsBiggerSet) / (iterationsSmallerSet * iterationsSmallerSet);
		long double nCubicLimit = static_cast<long double>(iterationsBiggerSet * iterationsBiggerSet * iterationsBiggerSet) / (iterationsSmallerSet * iterationsSmallerSet * iterationsSmallerSet);
		if (diff < nlognLimit)
		{
			std::cout << "\t\tThe runtime complexity is approximately below O(n*log(n))." << std::endl;
			std::cout << "\t\t\tThis is not a probable runtime complexity." << std::endl;
			std::cout << "\t\t\tNote: due to std::chrono at times giving incorrect time, please redo the test, preferably with a higher iteration count." << std::endl;
		}
		else if (diff < nSquaredLimit)
		{
			std::cout << "\t\tThe runtime complexity is approximately O(n*log(n))." << std::endl;
		}
		else if (diff < nCubicLimit)
		{
			std::cout << "\t\tThe runtime complexity is approximately O(n^2)." << std::endl;
		}
		else
		{
			std::cout << "\t\tThe runtime complexity is approximately above O(n^3). The solution got a too high runtime complexity." << std::endl;
			std::cout << "\t\t\tNote: due to std::chrono at times giving incorrect time, please redo the test, preferably with a higher iteration count." << std::endl;
			std::cout << "\t\t\tReminder that this is not a runtime complexity that will be allowed." << std::endl;
			return false;
		}
		return true;
	}

	template <typename T = PriorityQueue<int>>
	bool TimeComplexityApproximation(size_t iterations = 100)
	{
		std::cout << "\n\tTime Complexity Approximation begins." << std::endl;

		std::cout << "\t\t\tEnqueue and Dequeue on 100 elements, " << iterations << " iterations." << std::endl;
		long double milliseconds100Elements = TimeTest(iterations, 100);
		std::cout << "\t\t\tEnqueue and Dequeue for 100 elements took on average: " << milliseconds100Elements << " ms." << std::endl;

		std::cout << "\t\tPushing the test to 1'000 elements." << std::endl;
		std::cout << "\t\t\tEnqueue and Dequeue on 1'000 elements, " << iterations << " iterations." << std::endl;
		long double milliseconds1000Elements = TimeTest(iterations, 1'000);
		std::cout << "\t\t\tEnqueue and Dequeue for 1'000 elements took on average: " << milliseconds1000Elements << " ms." << std::endl;

		std::cout << "\t\tPushing the test to 10'000 elements." << std::endl;
		std::cout << "\t\t\tEnqueue and Dequeue on 10'000 elements, " << iterations << " iterations." << std::endl;
		long double milliseconds10000Elements = TimeTest(iterations, 10'000);
		std::cout << "\t\t\tEnqueue and Dequeue for 10'000 elements took on average: " << milliseconds10000Elements << " ms." << std::endl;

		if (25.0 < milliseconds10000Elements)
		{
			std::cout << "\n\t\tAverage time above the given limit. Testing will not continue. Calculating runtime complexity." << std::endl;
			return TimeDiffComputation(1'000, 10'000, milliseconds1000Elements, milliseconds10000Elements);
		}

		std::cout << "\t\tPushing the test to 100'000 elements." << std::endl;
		std::cout << "\t\t\tEnqueue and Dequeue on 100'000 elements, " << iterations << " iterations." << std::endl;
		long double milliseconds100000Elements = TimeTest(iterations, 100'000);
		std::cout << "\t\t\tEnqueue and Dequeue for 100'000 elements took on average: " << milliseconds100000Elements << " ms." << std::endl;

		if (375.0 < milliseconds100000Elements)
		{
			std::cout << "\n\t\tAverage time above the given limit. Testing will not continue. Calculating runtime complexity." << std::endl;
			return TimeDiffComputation(10'000, 100'000, milliseconds10000Elements, milliseconds100000Elements);
		}

		std::cout << "\t\tPushing the test to 1'000'000 elements." << std::endl;
		std::cout << "\t\t\tEnqueue and Dequeue on 1'000'000 elements, " << iterations << " iterations." << std::endl;
		long double milliseconds1000000Elements = TimeTest(iterations, 1'000'000);
		std::cout << "\t\t\tEnqueue and Dequeue for 1'000'000 elements took on average: " << milliseconds1000000Elements << " ms." << std::endl;

		if (5'625.0 < milliseconds10000Elements)
		{
			std::cout << "\n\t\tAverage time above the given limit. Calculating runtime complexity." << std::endl;
		}
		else
		{
			std::cout << "\n\t\tAverage time below the given limit. Calculating runtime complexity." << std::endl;
		}
		return TimeDiffComputation(100'000, 1'000'000, milliseconds100000Elements, milliseconds1000000Elements);
	}

	template <typename T = PriorityQueue<int>>
	bool PriorityQueueUnitTests(size_t iterations)
	{
		if constexpr (PriorityQueue_has_constructor)
		{
			bool pass = true;
			std::cout << "Tests starting on PriorityQueue." << std::endl;
			if (!TestEnqueue())
			{
				std::cout << "Tests failed on PriorityQueue::enqueue." << std::endl;
				pass = false;
				//return false;
			}
			if (!TestSize())
			{
				std::cout << "Tests failed on PriorityQueue::size." << std::endl;
				pass = false;
				//return false;
			}
			if (!TestIsEmpty())
			{
				std::cout << "Tests failed on PriorityQueue::isEmpty." << std::endl;
				pass = false;
				pass = false;
				//return false;
			}
			if (!TestPeek())
			{
				std::cout << "Tests failed on PriorityQueue::peek.." << std::endl;
				pass = false;
				//return false;
			}
			if (!TestDequeue())
			{
				std::cout << "Tests failed on PriorityQueue::dequeue." << std::endl;
				pass = false;
				//return false;
			}
			if (!TestThrow())
			{
				std::cout << "Tests failed on exception handling." << std::endl;
				pass = false;
				//return false;
			}
			if(pass)
				return TimeComplexityApproximation(iterations);
			return false;
		}
		else
		{
			std::cout << "\tTests cannot be conducted: No default-constructor accessible." << std::endl;
			return false;
		}
	}
} // namespace UnitTests::PRIORITYQUEUE
#else
namespace UnitTests::PRIORITYQUEUE
{
	bool PriorityQueueUnitTests(size_t /*iterations*/)
	{
		std::cout << "File PriorityQueue.h non-existent." << std::endl;
		return false;
	}
} // namespace UnitTests::PRIORITYQUEUE
#endif

#endif