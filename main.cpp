#include "library/library.cpp"
using namespace std;

Semaphore SEMAPHORE;

void task(string tid) {

    SEMAPHORE.wait(tid);


    SEMAPHORE.notify(tid);
    return;
}

int main() {
    Account account("Account 1", 100);

    Client client1;
    Client client2; 
    Client client3;

    //thread threadCredit(_creditToAccount, &account, 500);
    //thread threadDebit(_debitToAccount, &account, 600);

    //threadCredit.join(); 
    //threadDebit.join();

    

    /* thread client_getExtract1(_getAccountExtract, "client 1", &account);
    thread client_getExtract2(_getAccountExtract, "client 2", &account);
    thread client_getExtract3(_getAccountExtract, "client 3", &account);
    thread client_getExtract4(_getAccountExtract, "client 4", &account);
    thread client_getExtract5(_getAccountExtract, "client 5", &account);
    thread client_getExtract6(_getAccountExtract, "client 6", &account);
    thread client_getExtract7(_getAccountExtract, "client 7", &account);
    thread client_getExtract8(_getAccountExtract, "client 8", &account);
    thread client_getExtract9(_getAccountExtract, "client 9", &account);
    thread client_getExtract10(_getAccountExtract, "client 10", &account); */

    /* client_getExtract1.join();
    client_getExtract2.join();
    client_getExtract3.join();
    client_getExtract4.join();
    client_getExtract5.join();
    client_getExtract6.join();
    client_getExtract7.join();
    client_getExtract8.join();
    client_getExtract9.join();
    client_getExtract10.join(); */
    return 0; 

}

