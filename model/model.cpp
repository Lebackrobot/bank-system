#include <iostream>
#include <thread>
#include <chrono>
using namespace std; 

//Class account
class Account {
private:
    string id; 
    int value;

    //callback function for debitValue and creditValue
    void _logExtract(string operation, int operationValue, int previusAccountValue) {

        //sleep for one second
        this_thread::sleep_for(chrono::milliseconds(1000));

        //show values in terminal
        cout << "\033[1;30;107m #" << this->id << " (" << operation << ") \033[0m" << endl;
        cout << "------------------------" << endl;
        cout << "Previus value:      " << previusAccountValue << endl;
        cout << "Deposited value:    " << operationValue << endl;
        cout << "VALUE:              " << this->value << endl;
        cout << endl << endl;
    }

public: 
    Account(string id, int value = 0) {
        this->id = id;
        this->value = value;
    }

    void debitValue(int value) {
        int previusAccountValue = this->value;    //previus account value

        //critical region
        this->value = this->value - value;
        this->_logExtract("DEBIT", value, previusAccountValue);

        return; 
    }

    void creditValue(int value) {
        int previusAccountValue = this->value;    //previus account value

        //critical region
        this->value = this->value + value;                         //update value
        this->_logExtract("CREDIT", value, previusAccountValue);  //log extract 

        return;
    }

    void getExtract() {

        //sleep for one second
        this_thread::sleep_for(chrono::milliseconds(1000));

        cout << "\033[1;30;107m #" << this->id << " (CONSULTA) \033[0m" << endl;
        cout << "-------------------------" << endl;
        cout << "VALUE              " << this->value;
        cout << endl << endl;
    
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

    void getExtract(Account &account) {
        account.getExtract();
        return;
    }
};