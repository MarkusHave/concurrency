#include <iostream>
#include <thread>
#include <chrono>
#include <process.h>

using namespace std;

void cpu_waster()
{
    cout << "cpu_waster process id: " << _getpid() << endl;
    cout << "cpu_waster thread id: " << this_thread::get_id() << endl;

    while (true)
    {
    }
}

int main() {
    cout << "cpu_waster process id: " << _getpid() << endl;
    cout << "cpu_waster thread id: " << this_thread::get_id() << endl;

    thread thread1(cpu_waster);
    thread thread2(cpu_waster);

    while (true)
    {
        this_thread::sleep_for(std::chrono::seconds(1));
        cout << "Running..." << endl;

    }

    return 0;
}