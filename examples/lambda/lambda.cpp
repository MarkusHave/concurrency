#include <iostream>
#include <thread>

using namespace std;

int main()
{
    thread t1([]
    {
        cout << "Thread executing within lambda expression" << endl;
    });

    t1.join();
    return 0;
}
