#include <iostream>
#include <thread>

using namespace std;

class functorThread
{
public:
    void operator()()
    {
        cout << "Thread executing from functorThread object: " << number << endl;
    }

    int number;
};


int main()
{
    functorThread func;
    func.number = 12345;
    thread t1(func);

    if (t1.joinable())
    {
        t1.join();
    }
    return 0;
}

