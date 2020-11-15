/*Home Assignment 6
In home assignment 4 you did a simulation of bank account and used mutexes to protect the data.

1. Take the code from home assignment 4 to modify it for this assignment.
2. Add function **addInterest** to bank account class.
3. After 100 deposit or withdraw operations, an addInterest function is called:
    * **addInterest** adds 0.05 per cent interest to account balance (based on current balance).
4. Modify the app to operate lock-free using atomics.

Tips:
1. Its not as simple as changing balance to *std::atomic<double>* as you will need computations in addInterest function that are not 
   supported by the atomic type (multipication, division of floating point values).
2. Your options are:
    * use new atomic variable as a barrier or as a light weight DIY mutex.
    * perform atomic operations to account balance using Compare and Swap technique with compare_exchange.. functions.
3. Avoid busy loops if using atomic variable for synchronizing.
*/

#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

class BankAccount
{
private:
    atomic<double> balance;

public:
    BankAccount(double bal) : balance(bal) {}

    void deposit(double amount)
    {
        double current = balance.load();
        while (!balance.compare_exchange_weak(current, current + amount));

        cout << "Deposited: $" << amount << endl;
    }

    void withdraw(int amount)
    {
        double current = balance.load();
        while (!balance.compare_exchange_weak(current, current - amount));

        cout << "Withdrawn: $" << amount << endl;
    }

    void addInterest() 
    {
        double current = balance.load();
        while (!balance.compare_exchange_weak(current, current + (current * 0.005f)));
    }

    double showBalance() { return balance; }
};

void threadFunc(BankAccount& account1, BankAccount& account2, int threadNum)
{
    double amount;
    srand((unsigned int)time(0));
    
    for (int i = 0; i < 100; i++)
    {
        amount = rand() % 100;
        account1.withdraw(amount);
    }

    account1.addInterest();

    for (int i = 0; i < 100; i++) 
    {
        amount = rand() % 100;
        account2.deposit(amount);
    }

    account2.addInterest();

    for (int i = 0; i < 100; i++)
    {
        amount = rand() % 50;
        account2.withdraw(amount);
    }

    account2.addInterest();

    for (int i = 0; i < 100; i++)
    {
        amount = rand() % 100;
        account1.deposit(amount);
    }

    account1.addInterest();

    cout << "##### Thread " << threadNum << " finished!" << endl;
}

int main()
{
    BankAccount account1(10000.0f);
    BankAccount account2(2000.0f);

    thread t1(threadFunc, ref(account1), ref(account2), 1);
    thread t2(threadFunc, ref(account1), ref(account2), 2);
    thread t3(threadFunc, ref(account1), ref(account2), 3);
    thread t4(threadFunc, ref(account1), ref(account2), 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    cout << "Account 1 balance: $" << account1.showBalance() << endl;
    cout << "Account 2 balance: $" << account2.showBalance() << endl;

    return 0;
}


