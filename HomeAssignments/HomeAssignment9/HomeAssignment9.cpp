/*Home Assignment 9

Airport

4 people are at the airport. To prepare for departure, each of them has to first scan their boarding pass (which takes 1 min), 
and then to do the security check (which takes 10 minutes).

1. Assume that there is only one machine for scanning the boarding pass and only one security line. Explain why this pipeline is unbalanced. Compute its throughput.
2. Now assume that there are 2 security lines. Which is the new throughput?
3. If there were 4 security lines opened, would the pipeline be balanced?

Implement a test program to verify your findings.

Tip: You can simulate the throughput faster than 1/10 minutes. But after simulation, show the results based on original 1/10 minutes.

*/

#include <iostream>
#include <thread>
#include <atomic>
#include <condition_variable>

using namespace std;

class Airport
{
private:
    atomic<int> scannerQue;
    atomic<int> securityQueue = 0;
    condition_variable condVar;
    mutex m;

public:
    Airport(int queSize)
    {
        scannerQue.store(queSize);
    }

    void Scanner()
    {
        cout << "Starting scanner checks..." << endl;
        while (scannerQue.load() > 0)
        {
            scannerQue--;
            this_thread::sleep_for(chrono::seconds(1));
            securityQueue++;
            cout << "Popped in scanner line" << endl;
            condVar.notify_one();
        }
        cout << "Scanner done!" << endl;
    }

    void SecurityCheck()
    {
        unique_lock<mutex> mLock(m);
        condVar.wait(mLock);
        mLock.unlock();
        cout << "Starting security checks..." << endl;

        while (securityQueue.load() > 0)
        {
            securityQueue--;
            this_thread::sleep_for(chrono::seconds(10));
            cout << "Popped in security line" << endl;
        }
        cout << "Security done!" << endl;
    }
};


int main()
{
    // Start clock
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    Airport airport1(4);

    thread t1(&Airport::Scanner, ref(airport1));
    thread t2(&Airport::SecurityCheck, ref(airport1));
    thread t3(&Airport::SecurityCheck, ref(airport1));
    thread t4(&Airport::SecurityCheck, ref(airport1));
    thread t5(&Airport::SecurityCheck, ref(airport1));

    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    
    // End clock
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Done!" << endl;
    cout << "Execution time: "
        << chrono::duration_cast<chrono::milliseconds>(end - begin).count()
        << "ms" << endl;

    return 0;
}

// RESULTS:
// One scanner and security check: 41000ms - line is unbalanced because there is only one security check.
// One scanner and two security checks: 22000ms - better but not enough.
// One scanner and four security checks: 14000ms - line is now balanced.
