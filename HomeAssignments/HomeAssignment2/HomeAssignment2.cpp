/*Home Assignment 2
1. Create new console app.
2. Ask user of how many numbers to allocate.
3. Allocate an array of numbers and pass it to thread that sets array elements to random numbers.
4. In main, wait for the thread to finish and print the contents of the array.
5. Copy your source code to Moodle return box.
*/

#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

void randNumbers(vector<int>& numbers) 
{
    // Generate random numbers between 0 - 99
    generate(numbers.begin(), numbers.end(), [] { return rand() % 100; });
}

int main()
{
    int value;
    vector<int> numbers;

    cout << "How many numbers you want allocate?\n>>";
    cin >> value;

    // Resize vector
    numbers.resize(value);

    // Create and run new thread
    thread t1(randNumbers, ref(numbers));
    t1.join();

    // Print vector
    cout << "Vector contents:\n";
    for (int i : numbers) cout << i << " ";

    return 0;
}


