#include "library/library.cpp"
using namespace std;

//drivem code
int main() {
    Account account("Account 1", 100);

    //debit clients
    thread client_debitToAccount1(_debitToAccount, "clientDebit 1", &account, getRandonNumber());
    thread client_debitToAccount2(_debitToAccount, "clientDebit 2", &account, getRandonNumber());
    thread client_debitToAccount3(_debitToAccount, "clientDebit 3", &account, getRandonNumber());
    thread client_debitToAccount4(_debitToAccount, "clientDebit 4", &account, getRandonNumber());
    thread client_debitToAccount5(_debitToAccount, "clientDebit 5", &account, getRandonNumber());
    
    //credit clients
    /* thread client_creditToAccount1(_creditToAccount, "cleintCredit 1", &account, getRandonNumber());
    thread client_creditToAccount2(_creditToAccount, "clientCreditAccount 2", &account, getRandonNumber());
    thread client_creditToAccount3(_creditToAccount, "clientCreditAccount 3", &account, getRandonNumber());
    thread client_creditToAccount4(_creditToAccount, "clientCreditAccount 4", &account, getRandonNumber());
    thread client_creditToAccount5(_creditToAccount, "clientCreditAccount 5", &account, getRandonNumber()); */

    //extract clients
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

    //join threads
    client_debitToAccount1.join();
    client_debitToAccount2.join();
    client_debitToAccount3.join();
    client_debitToAccount4.join();
    client_debitToAccount5.join();

    /* client_creditToAccount1.join();
    client_creditToAccount2.join();
    client_creditToAccount3.join();
    client_creditToAccount4.join();
    client_creditToAccount5.join(); */


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
