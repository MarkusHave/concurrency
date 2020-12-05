#include <iostream>
#include <thread>
#include <mutex>

// cout, thread, string, ref use 'std' namespace
using namespace std;


// declare a class as a data container
class DataContainer
{
public:
    int number;
    mutex m;

    DataContainer() : number(0) {}

    void increment()
    {
        m.lock();
        number++;
        m.unlock();
    }
};


// declare a function for the thread to run
// send data containers as a reference parameter
void threadProc(DataContainer& data)
{
    for (int i = 0; i < 10000; i++)
    {
        data.increment();
    }
}


int main()
{
    // declare only one data container
    DataContainer data;

    // Start multiple thread that access the same data container
    thread t1(threadProc, ref(data));
    thread t2(threadProc, ref(data));

    // wait for the threads to complete
    t1.join();
    t2.join();

    // print the result
    cout << "threads done, result=" << data.number << endl;

    return 0;
}