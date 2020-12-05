#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void print()
{
    cout << "Critical data" << endl;
}

int main()
{
    mutex mutex1, mutex2;

    thread t1([&mutex1, &mutex2]
    {
        cout << "Acquiring first mutex..." << endl;
        mutex1.lock();
        print();


        cout << "Acquiring second mutex..." << endl;
        mutex2.lock();
        print();

        mutex1.unlock();
        mutex2.unlock();
    });

    thread t2([&mutex1, &mutex2]
    {
        cout << "Acquiring first mutex..." << endl;
        mutex2.lock();
        print();


        cout << "Acquiring second mutex..." << endl;
        mutex1.lock();
        print();

        mutex2.unlock();
        mutex1.unlock();
    });

    t1.join();
    t2.join();

    cout << "All done, exiting" << endl;

    return 0;
}
