#include "library/library.cpp"
using namespace std;


int main() {

    Account account("Account 1", 100);
    Client client;

    client.getExtract(account);    
    client.creditToAccount(account, 100);

    return 0; 
}
