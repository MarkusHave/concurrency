/* Home Assignment 3
1. Create a new console app.
2. Declare a std::vector as an dynamic array of numbers
3. Create two threads, another will add numbers to the vector and another will remove them
4. Synchronize the threads with a Mutex.
5. Copy your source code to the Moodle return box.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;


void addNumbers(vector<int>& v, mutex& m)
{
    m.lock();
    for (int i = 0; i < 1000; i++) v.push_back(i);
    cout << "Added 1000 elements" << endl;
    m.unlock();
}

void removeNumbers(vector<int>& v, mutex& m) 
{
    m.lock();
    for (int i = 0; i < 1000; i++) v.pop_back();
    cout << "Removed 1000 elements" << endl;
    m.unlock();
}


int main() 
{
    vector<int> v;
    mutex m;

    thread t1(addNumbers, ref(v), ref(m));
    thread t2(removeNumbers, ref(v), ref(m));

    t1.join();
    t2.join();

    return 0;
}
