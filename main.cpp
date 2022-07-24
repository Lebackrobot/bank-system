#include "library/library.cpp"
using namespace std;


int main() {

    Account account("Account 1", 100);
    Client client;

    client.creditToAccount(account, 100);
    client.creditToAccount(account, 100);
    client.creditToAccount(account, 100);

    client.getExtract(account);

    return 0; 
}

