#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
using namespace std;

class Semaphore {
private:
    int count = 5;
    condition_variable cv;
    mutex mtx;

    mutex* mtxAccount;

public:
    Semaphore() {}

    void setMutex(mutex* mtxAccount_) {
        this->mtxAccount = mtxAccount_;
    }

    inline void notify(string id) {
        cout << "semaphore 🟩 (Done) :: " << id << endl << endl;

        // sleep for 100 miliseconds
        this_thread::sleep_for(std::chrono::milliseconds(100));
        

        count++;
        unique_lock <mutex> lock(mtx);

        
        //thread unlocked
        cv.notify_one();
    }

    inline void wait(string id) {
        unique_lock <mutex> lock(mtx);

        while (count == 0) {

            // sleep for 100 miliseconds
            this_thread::sleep_for(std::chrono::milliseconds(100));

            cout << endl << "semaphore 🟥 (wait) :: " << id << endl;

            //thread locked
            cv.wait(lock);

        }

        count--;

        // sleep for 100 miliseconds
        //this_thread::sleep_for(std::chrono::milliseconds(10));
        //cout << endl << "semaphore 🟩 (go) :: " << id << endl;
    }

    int getCount() {
        return count;
    }
};

//Class account
class Account {
private:
    string id; 
    mutex* mtx;
    int value;
    Semaphore semaphore;

    //callback function for debitValue and creditValue
    void _logExtract(string operation, int operationValue, int previusAccountValue) {

        //show values in terminal
        cout << "\033[1;30;107m #" << this->id << " (" << operation << ") \033[0m" << endl;
        cout << "--------------------" << endl;
        cout << "Previus value:      " << previusAccountValue << endl;
        cout << "Deposited value:    " << operationValue << endl;
        cout << "VALUE:              " << this->value << endl;
    }


public: 
    Account(string id, int value = 0) {
        this->id = id;
        this->value = value;

        this->mtx = new mutex;                  //account mutex
        this->semaphore.setMutex(this->mtx);    //account semaphore
    }



    void debitValue(string client, int value) {
        //sleep for one second
        this_thread::sleep_for(chrono::milliseconds(100));

        //critical region (mutex)
        mtx->lock();
            cout << endl << "❌ mutex lock " << endl << endl;

            int previusAccountValue = this->value;                  // previus account value
            this->value = this->value - value;                      // update value
            this->_logExtract("DEBIT", value, previusAccountValue); // log extract
        
            cout << "✅ mutex unlock" << endl << endl;
        mtx->unlock();

        return; 
    }

    void creditValue(string client, int value) {
        //sleep for one second
        this_thread::sleep_for(chrono::milliseconds(100));
        
        //critical region (mutex)
        mtx->lock();
            cout << endl << "❌ mutex lock" << endl ;

            int previusAccountValue = this->value;                   // previus account value
            this->value = this->value + value;                       // update value
            this->_logExtract("CREDIT", value, previusAccountValue); // log extract

            cout << endl << "✅ mutex unlock" << endl ;
        mtx->unlock();

        return;
    }

    void getExtract(string client) {

        //critical region (semaphore)
        semaphore.wait(client);
                // sleep for one second
                this_thread::sleep_for(chrono::milliseconds(100));

                mtx->lock();
                //cout << endl << "❌ mutex lock" << endl << endl;

                cout << "\033[1;30;107m #" << this->id << " (EXTRACT :: " << client << ") \033[0m" << endl;
                cout << "----------------------------------" << endl;
                cout << "VALUE              " << this->value;
                cout << endl << endl;

                //cout << endl << "✅ mutex unlock" << endl ;
                mtx->unlock();
        semaphore.notify(client);
    
        return;
    }
};