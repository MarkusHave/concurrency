#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

// declare a class as a data container
class DataContainer
{
public:
    DataContainer() : number(0)
    {
    }

    void increment()
    {
        number++;
    }

    atomic<int> number;
};

// declare a function for the thread to run
// send data containers as a reference parameter
void threadProc(DataContainer& data)
{
    for (int i = 0; i < 10000000; i++)
    {
        data.increment();
    }
}

int main()
{
    // take start time
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    // declare only one data container
    DataContainer data;

    // start multiple threads that access the same data container
    thread t1(threadProc, ref(data));
    thread t2(threadProc, ref(data));

    // wait for the threads to complete
    t1.join();
    t2.join();

    // print the result
    cout << "threads done, result=" << data.number << endl;

    // take the end time
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    // print results
    cout << "Execution time: "
        << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
        << "[ms]" << endl;

    return 0;
}