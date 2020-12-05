#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

class Application
{
private:
    vector<char>            m_data;
    mutex                   m_mutex;
    condition_variable      m_condVar;
    bool                    m_bDataLoaded;

public:
    Application() : m_bDataLoaded(false)
    {
        // set the random seed
        srand((unsigned int)time(0));
    }

    bool isDataLoaded() const
    {
        return m_bDataLoaded;
    }

    void loadData()
    {
        // protect the data with mutex
        lock_guard<mutex> guard(m_mutex);

        // simulate work
        for (int i = 0; i <= 100; i += 10)
        {
            for (int j = 0; j < 50; j++)
            {
                m_data.push_back((char)(rand() % 64 + 33));
            }
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "Loading data " << i << "%" << endl;
        }

        // set variable true
        m_bDataLoaded = true;

        // notify the condition variable
        m_condVar.notify_one();
    }

    void connectToServer()
    {
        // simulate connecting
        cout << "Connect to server..." << endl;
        for (int i = 0; i < 100; i += 25)
        {
            this_thread::sleep_for(chrono::milliseconds(100));
            cout << "Handshaking with server " << i << "%" << endl;
        }
        cout << "Connect to server complete" << endl;

        // Acquire the lock
        unique_lock<mutex> mlock(m_mutex);

        // start waiting for the condition variable to signal
        m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));

        // upload the data
        uploadData();
    }

    void uploadData()
    {
        cout << "Start uploading data" << endl;

        // simulate work
        for (int i = 0; i < m_data.size(); i++)
        {
            cout << m_data.at(i) << ",";
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl << "Upload complete" << endl;
    }
};

int main()
{
    Application app;
    thread t1(&Application::connectToServer, &app);
    thread t2(&Application::loadData, &app);
    t1.join();
    t2.join();

    return 0;
}