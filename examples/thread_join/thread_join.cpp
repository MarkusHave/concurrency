#include <iostream>
#include <thread>

using namespace std;

void runningNumber()
{
    cout << "runningNumber : entering" << endl;
    const thread::id id = this_thread::get_id();

    for (int i = 0; i < 15; i++)
    {
        cout << "runningNumber: thread id: " << id;
        cout << ", i=" << i << endl;
    }
    cout << "runningNumber: leaving" << endl;
}

int main()
{
    thread t1(runningNumber);
    cout << "main: started thread t1" << endl;

    //t1.join();
    t1.detach();
    if (t1.joinable())
    {
        cout << "main: joining thread t1" << endl;
        t1.join();
    }

    cout << "main: exiting" << endl;
    return 0;
}
