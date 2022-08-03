#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
using namespace std;

class Semaphore
{
private:
    std::mutex mtx;
    std::condition_variable cv;

    int count = 5;
    mutex *mtxAccount;

public:
    Semaphore(mutex *mtxAccount_)
    {
        mtxAccount = mtxAccount_;
    }

    inline void notify(string tid)
    {
        // this_thread::sleep_for(std::chrono::seconds(1));
        unique_lock<mutex> lock(mtx);

        // thread unlocked
        count++;
        cv.notify_one();
    }

    inline void wait(string tid)
    {
        unique_lock<mutex> lock(mtx);

        while (count == 0)
        {

            cout << endl
                 << "wait" << endl;

            this_thread::sleep_for(std::chrono::seconds(2));
            // thread locked

            mtxAccount->lock();
            cv.wait(lock);

            // this_thread::sleep_for(std::chrono::seconds(1));
        }

        count--;
        mtxAccount->unlock();
    }
};