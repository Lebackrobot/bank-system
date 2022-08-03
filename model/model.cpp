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

    inline void notify(string tid) {
        //this_thread::sleep_for(std::chrono::seconds(1));
        unique_lock <mutex> lock(mtx);
       
        //thread unlocked
        count++;
        cv.notify_one();
    }

    inline void wait(string tid) {
        unique_lock <mutex> lock(mtx);

        while (count == 0) {
            // sleep for one second
            this_thread::sleep_for(std::chrono::milliseconds(1000));

            
            cout << endl << "🚦wait" << endl << endl;
            
            //thread locked
            cv.wait(lock);

        }

        count--;
        //mtxAccount->unlock();
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

        //sleep for one second
        //this_thread::sleep_for(chrono::milliseconds(100));

        //show values in terminal
        cout << "\033[1;30;107m #" << this->id << " (" << operation << ") \033[0m" << endl;
        cout << "------------------------" << endl;
        cout << "Previus value:      " << previusAccountValue << endl;
        cout << "Deposited value:    " << operationValue << endl;
        cout << "VALUE:              " << this->value << endl;
        cout << endl << endl << endl;
    }


public: 
    Account(string id, int value = 0) {
        this->id = id;
        this->value = value;

        this->mtx = new mutex;                  //account mutex
        this->semaphore.setMutex(this->mtx);    //account semaphore
    }



    void debitValue(int value) {
        //critical region (mutex)
        mtx->lock();
            int previusAccountValue = this->value;                  //previus account value
            this->value = this->value - value;                      //update value
            this->_logExtract("DEBIT", value, previusAccountValue); //log extract
        mtx->unlock();

        return; 
    }

    void creditValue(int value) {
        //critical region (mutex)
        mtx->lock();
            int previusAccountValue = this->value;                     //previus account value
            this->value = this->value + value;                         //update value
            this->_logExtract("CREDIT", value, previusAccountValue);   //log extract 
        mtx->unlock();

        return;
    }

    void getExtract(string client) {

        //critical region (semaphore)
        semaphore.wait(id);
                // sleep for one second
                this_thread::sleep_for(chrono::milliseconds(100));
                mtx->lock();
                    cout << "\033[1;30;107m #" << this->id << " (EXTRACT :: " << client << ") \033[0m" << endl;
                    cout << "-----------------------------------" << endl;
                    cout << "VALUE              " << this->value;
                    cout << endl << endl;
                mtx->unlock();
        semaphore.notify(id);
    
        return;
    }
};

//Client Class
class Client {
public:
    void debitToAccount(Account &account, int value) {
        account.debitValue(value);
        return;
    }

    void creditToAccount(Account &account, int value) {
        account.creditValue(value);
        return;
    }

    void getExtract(string client, Account &account) {
        account.getExtract(client);
        return;
    }
};

//_creditToAccount worker (Thread)
void _creditToAccount(Account *account, int value) {
    account->creditValue(value);
    return;
}

//_debitToAccount worker (Thread)
void _debitToAccount(Account *account, int value) {
    account->debitValue(value);
    return;
}

//_getAccountExtract worker (Thread)
void _getAccountExtract(string client, Account *account) {
    account->getExtract(client);
    return;
}