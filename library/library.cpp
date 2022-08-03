//application libraries

//iostream and others
#include <iostream>
#include <string>
#include <cstdlib>

//thread libary
#include <thread>
#include <chrono>

//synchronization
#include <condition_variable>
#include <mutex>

//model classes
#include "../model/model.cpp"


//------------------------------------ Thread workers -------------------------------//

//_creditToAccount worker (Thread)
void _creditToAccount(string client, Account *account, int value) {
    account->creditValue(client, value);
    return;
}

//_debitToAccount worker (Thread)
void _debitToAccount(string client, Account *account, int value) {
    account->debitValue(client, value);
    return;
} 


//_getAccountExtract worker (Thread)
void _getAccountExtract(string client, Account *account) {
    account->getExtract(client);
    return;
}
//--------------------------------------------------------------------//

//helpers 
int getRandonNumber() {
    return rand() % 10 + 1;
}