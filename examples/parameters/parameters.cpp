#include <iostream>
#include <thread>
#include <string>

using namespace std;

void runningNumber(int count, const string& msg)
{
    for (int i = 0; i < count; i++)
    {
        cout << msg << ", i=" << i << endl;
    }
}

void increaseNumber(int& number, int count)
{
    while (count--)
    {
        number++;
        cout << "increaseNumber: " << number << endl;
    }
}

int main()
{
    const string msg = "Hello from main";
    thread t1(runningNumber, 100, msg);
    t1.join();

    int number = 0;
    thread t2(increaseNumber, ref(number), 100);
    t2.join();

    cout << "t2 done, number=" << number << endl;

    return 0;
}


