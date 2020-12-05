#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <future>

using namespace std;
using namespace std::chrono;

string fetchDataFromDB(string recvdData)
{
    this_thread::sleep_for(seconds(5));
    return "DB_" + recvdData;
}

string fetchDataFromFile(string recvdData)
{
    this_thread::sleep_for(seconds(5));
    return "File_" + recvdData;
}

int main()
{
    system_clock::time_point start = system_clock::now();

    cout << "Starting to fetch data..." << endl;

    // string dbData = fetchDataFromDB("Data123");
    future<string> resultFromDB = async(launch::async, fetchDataFromDB, "Data123");

    // string fileData = fetchDataFromFile("Data456");
    future<string> resultFromFile = async(launch::async, fetchDataFromFile, "Data456");

    string data = resultFromDB.get() + "::" + resultFromFile.get();
    cout << "Data = " << data << endl;

    system_clock::time_point end = system_clock::now();
    cout << "Total time = " << duration_cast<seconds>(end - start).count() << " seconds" << endl;

    return 0;
}