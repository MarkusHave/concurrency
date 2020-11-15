/*Home Assignment 7
1. Create a new console app.
2. Declare a class Sensor.
    - Sensor uses a thread internally to read sensor values.
    - Simulate sensor values by generating random numbers in between 0-4095
3. Declare a class SensorReader.
    - SensorReader allocates 4 sensors and starts a thread to read sensor values.
    - SensorReader thread can be stopped by a function call to *SensorReader::stop*.
4. Assume situation that reader is only interested of sensor values larger than 4000.
    - Implement future-promise; reader will wait for the result of sensor value over 4000.
    - When SensorReader gets a sensor value over 4000, print it to the console.
5. On your main function, allocate a SensorReader and let it run until user presses a key in console.
*/
#include <iostream>
#include <thread>
#include <future>
#include <array>
#include <conio.h>

using namespace std;

class Sensor
{
private:
    future<int> sensorVal;

public:
    Sensor()
    {
        srand((unsigned int)time(0));
    }

    void readValues(promise<int>& p)
    {
        async(launch::async, [&p]()
        {
            int val = 0;
            while (val < 4000)
            {
                val = rand() % 4096;
                this_thread::sleep_for(chrono::milliseconds(2));
            }
            p.set_value(val);
        });
    }
};

class SensorReader
{
private:
    bool readerRunning = true;
    array<Sensor, 4> sensors;

public:
    void readSensors()
    {
        cout << "Starting sensor reader... press any key to stop" << endl;
        while (readerRunning)
        {
            array<promise<int>, 4> promises;

            for (int i = 0; i < sensors.size(); i++)
            {
                sensors[i].readValues(ref(promises[i]));
            }

            for (int i = 0; i < promises.size(); i++)
            {
                cout << "Sensor " << i + 1 << " value: "
                    << promises[i].get_future().get() << endl;                
            }

            cout << "====================" << endl;
        }
    }

    void stop()
    {
        readerRunning = false;
    }
};

int main()
{
    SensorReader reader;
    thread readerThread(&SensorReader::readSensors, ref(reader));
    
    // wait for user input
    _getch();
    reader.stop();

    readerThread.join();

    return 0;
}