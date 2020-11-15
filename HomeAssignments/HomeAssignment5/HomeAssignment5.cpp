/*Home Assignment 5
1. Create a new console app.
2. Create a worker thread with a long running task.
3. Use 5 condition variables within the worker thread to notify the main thread of the progress.
    * Each condition variable amounts to 20% of the total task done
4. In main thread, wait for the condition variables to complete and print the progress of the worker thread.
5. Copy your source code to the Moodle return box.
*/

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>

using namespace std;

void mainWorker(array<condition_variable, 5>& condVars, mutex& m_mutex)
{
    int progress = 0;
    unique_lock<mutex> mlock(m_mutex);
    for (int i = 0; i < condVars.size(); i++)
    {
        condVars[i].wait(mlock);
        progress += 20;
        cout << "Task " << progress << "% done" << endl;
    }
}

void worker(array<condition_variable, 5>& condVars)
{
    cout << "Worker started task" << endl;
    for (int i = 0; i < condVars.size(); i++)
    {
        cout << "Working... " << endl;
        this_thread::sleep_for(chrono::milliseconds(800));
        condVars[i].notify_one();
    }
    
    cout << "Worker done!" << endl;
}

int main()
{
    array<condition_variable, 5> condVars;
    mutex m_mutex;


    thread t_main(mainWorker, ref(condVars), ref(m_mutex));
    thread t_worker(worker, ref(condVars));
    t_main.join();
    t_worker.join();

    return 0;
}

