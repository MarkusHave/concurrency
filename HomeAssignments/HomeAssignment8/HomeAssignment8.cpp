/*Home Assignment 8
1. Create a new console app.
2. Declare a class 'RandomNumberGenerator'. In class, specify *enum* of task type as *LIGHT* or *HEAVY*.
    - If RandomNumberGenerator is *LIGHT*, it will generate 100 random numbers.
    - If RandomNumberGenerator is *HEAVY*, it will generate 10 000 000 random numbers.
3. Allocate 100 RandomNumberGenerators and set the task type to *LIGHT* or *HEAVY* randomly.
4. Run the allocated RandomNumberGenerators as async tasks.
    - If generator is *LIGHT*, use deferred launching.
    - If generator is *HEAVY*, use async launching.
5. Measure how long it takes to complete all generators.
6. Switch to run all tasks with async launching.
7. Measure how long it takes to complete all generators.
8. Add comments into the source code of your findings. Which way is faster? Why?
*/
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <random>
#include <chrono>
#include <functional>

using namespace std;

class RandomNumberGenerator
{
public:
    enum TaskType { LIGHT, HEAVY };
    TaskType type;

    RandomNumberGenerator(TaskType taskType)
    {
        type = taskType;
        srand((unsigned int)time(0));
    }

    void generateNumbers()
    {
        //cout << "Thread ID: " << this_thread::get_id() << endl;
        if (type == LIGHT)
        {
            for (int i = 0; i < 100; i++) rand();
        }
        else
        {
            for (int i = 0; i < 10000000; i++) rand();

        }
    }
};

int main()
{
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // random bool generator
    auto randBool = bind(uniform_int_distribution<>(0, 1), default_random_engine());

    vector<future<void>> futs;
    vector<RandomNumberGenerator> generators;
    generators.reserve(100);

    // generate 100 RandomNumberGenerator objects
    for (int i = 0; i < 100; i++)
    {
        generators.push_back(RandomNumberGenerator(randBool() ?
            RandomNumberGenerator::LIGHT : RandomNumberGenerator::HEAVY));
    }

    // queue tasks
    for (auto&& g : generators)
    {
        futs.push_back(async(g.type == RandomNumberGenerator::LIGHT ?
            launch::deferred : launch::async, &RandomNumberGenerator::generateNumbers, ref(g)));
    }

    // start tasks
    for (auto&& fut : futs) fut.get();

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Done!" << endl;
    cout << "Execution time: "
        << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
        << "ms" << endl;

    return 0;
}

// RESULTS:
// Test 1: 8700ms
// Test 2 (all tasks async): 8883ms

// The tests took almost the same amount of time. 
// It looks like that light tasks are so fast that it doesn't matter if they are deferred or async.
