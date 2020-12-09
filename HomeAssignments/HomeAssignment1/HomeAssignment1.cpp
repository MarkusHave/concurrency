/* Home Assignment 1
1. Make a new console app.
2. Detect amount of logical processors at app runtime.
3. Create as many threads as your computer has logical processors.
4. Each thread runs simultaneously a for loop for 1000 iterations and print the current loop value while running.
5. In main, wait for all threads to finish.
6. Copy the source code to Moodle return box.
*/

#include <iostream>
#include <thread>
#include <process.h>
#include <vector>

using namespace std;

void threadFunction(int threadNum)
{
  for (int i = 0; i < 1000; i++)
  {
    cout << "Thread: " << threadNum << ", loop: " << i << endl;
  }
}

int main()
{
  const int processor_count = thread::hardware_concurrency();
  cout << "Hardware concurrency: " << processor_count << endl;
  vector<thread> threads;

  threads.reserve(processor_count);

  // Create 4 thread objects into array
  for (int i = 0; i < processor_count; i++)
  {
    threads.push_back(thread(threadFunction, i));
  }

  // Run all threads simultaneously
  for (auto &t : threads)
    t.join();

  cout << "MAIN: all threads finished\n";

  return 0;
}
