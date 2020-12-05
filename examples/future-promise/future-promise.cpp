#include <iostream>
#include <thread>
#include <future>

using namespace std;

void threadFunc(promise<int>& p)
{
    cout << "threadFunc..." << endl;

    // simulate calculations
    int a = 10, b = 5;
    int result = a + b;
    this_thread::sleep_for(chrono::milliseconds(1000));

    // after the result is calculated set it to promise
    p.set_value(result);
}

int main()
{
    // declare a promise of type int
    promise<int> p;

    // create a thread and pass the promise to it
    // thread will set the value into the promise when its done
    thread t1(threadFunc, ref(p));

    cout << "Thread started" << endl;

    // every promise has a future object
    // the result of the promise can be fetched from its future::get function
    // the future::get will block the caller thread if value is not yet set into promise
    cout << "future::get: " << p.get_future().get() << endl;
    cout << "future::get done" << endl;

    t1.join();
    return 0;

}

