/*Home Assignment 4
1. Create a class that simulates a bank account operations and holds the current balance of the account.
2. Add member functions for deposit, withdraw and balance.
3. Declare two bank account objects of aforementioned class and initialize with some balance.
4. Start 4 threads that will make random deposit and withdraw transactions between these two accounts.
5. Protect the bank account data with mutexes and avoid deadlocks.
*/
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mutex1;

class BankAccount
{
private:
    int balance;

public:
    BankAccount(int bal) : balance(bal) {}

    void deposit(int amount)
    {
        mutex1.lock();
        balance += amount;
        cout << "Deposited: $" << amount << endl;
        mutex1.unlock();
    }

    void withdraw(int amount)
    {
        mutex1.lock();
        balance -= amount;
        cout << "Withdrawn: $" << amount << endl;
        mutex1.unlock();
    }

    int showBalance() { return balance; }
};

void threadFunc(BankAccount& account1, BankAccount& account2, int threadNum)
{
    int amount;
    for (int i = 0; i < 100; i++)
    {
        amount = rand() % 100;
        account1.withdraw(amount);
        account2.deposit(amount);

        amount = rand() % 100;
        account2.withdraw(amount);
        account1.deposit(amount);
    }
    cout << "##### Thread " << threadNum << " finished!" << endl;
}

int main()
{
    BankAccount account1(10000);
    BankAccount account2(2000);

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

