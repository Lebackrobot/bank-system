#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

//shared value
int SHARED_VALUE = 10000; 

void extract(char* option = NULL, int value = 0, int previusValue = 0, int currentValue = 0) {
    
    //sleep for 1 second 
    this_thread::sleep_for(chrono::milliseconds(1000));

    if (option){
        printf("\033[1;30;107m #SHARED_VALUE (%s) \033[0m\n", option);
        printf("------------------------\n");
        printf("Previus value:      %d\n", previusValue);
        printf("Deposited value:    %d\n", value);
        printf("VALUE:              %d\n", currentValue);
        cout << endl << endl;
    }

    else {
        printf("\033[0;35;107m #SHARED_VALUE (CONSULTA) \033[0m\n", option);
        printf("-------------------------\n");
        printf("VALUE:              %d\n", SHARED_VALUE);
        cout << endl << endl;
    }
 
    return;
}

void creditValue(int value) {
    int previusValue; 
    int currentValue; 

    previusValue = SHARED_VALUE; 
    SHARED_VALUE = SHARED_VALUE + value;
    currentValue = SHARED_VALUE;

    extract("CREDIT", value, previusValue, currentValue);
    return;
}

void debitValue(int value) {
    int previusValue;
    int currentValue; 

    previusValue = SHARED_VALUE;
    SHARED_VALUE = SHARED_VALUE - value;
    currentValue = SHARED_VALUE;

    extract("DEBIT", value, previusValue, currentValue); 
    return; 
}

int main() {

    //client 
    for(int i = 0; i < 100; i++) {
        creditValue(100);
    }

    return 0; 
}
