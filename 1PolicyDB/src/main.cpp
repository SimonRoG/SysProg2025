#include "PolicyDatabase.h"
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

// Додвання поліса
void menuAddPolicy(PolicyDatabase& policyDB) {
    string startDate;
    string endDate;
    int policyTypeID;
    int clientID;
    int employeeID;

    cout << "Start date (dd.mm.yyyy): ";
    cin >> startDate;
    cout << "End date (dd.mm.yyyy): ";
    cin >> endDate;
    cout << "Policy type ID: ";
    cin >> policyTypeID;
    cout << "Client ID: ";
    cin >> clientID;
    cout << "Employee ID: ";
    cin >> employeeID;

    Policy& policy = policyDB.addPolicy(startDate, endDate, policyTypeID, clientID, employeeID);
    cout << "Policy " << policy.getPolicyID() << " created successfully!\n";
}

// Завершення поліса
void menuCompletePolicy(PolicyDatabase& policyDB) {
    int policyID;

    try {
        cout << "Policy ID: ";
        cin >> policyID;
        Policy& policy = policyDB.getPolicy(policyID);
        policy.completePolicy();
    } catch (exception& ex) {
        cerr << "Unable to complete policy!\n";
    }
}

// Відмітка про виплату
void menuMarkPayout(PolicyDatabase& policyDB) {
    int policyID;

    try {
        cout << "Policy ID: ";
        cin >> policyID;
        Policy& policy = policyDB.getPolicy(policyID);
        policy.markPayout();
    } catch (exception& ex) {
        cerr << "Unable to mark payout!\n";
    }
}

// Збільшення вартості поліса
void menuIncreaseCost(PolicyDatabase& policyDB) {
    int policyID;
    int amount;

    try {
        cout << "Policy ID: ";
        cin >> policyID;
        Policy& policy = policyDB.getPolicy(policyID);

        cout << "Increase amount: ";
        cin >> amount;
        policy.increaseCost(amount);
    } catch (exception& ex) {
        cerr << "Unable to increase cost!\n";
    }
}

// Збільшення суми виплати
void menuIncreasePayout(PolicyDatabase& policyDB) {
    int policyID;
    int amount;

    try {
        cout << "Policy ID: ";
        cin >> policyID;
        Policy& policy = policyDB.getPolicy(policyID);

        cout << "Increase amount: ";
        cin >> amount;
        policy.increasePayoutAmount(amount);
    } catch (exception& ex) {
        cerr << "Unable to increase payout!\n";
    }
}

// Тестування класу Policy
void test() {
    // Тестування поліса на стеку
    cout << "--- test policy on stack ---\n";
    Policy stackPolicy(0, "01.01.2020", "01.01.2021", 1, 1, 1);
    stackPolicy.display();

    stackPolicy.increaseCost(2000);
    stackPolicy.increasePayoutAmount(5000);
    stackPolicy.display();

    // Тестування поліса на купі
    cout << "--- test policy on heap ---\n";
    Policy* heapPolicy = new Policy(1, "01.01.2021", "01.01.2022", 1, 2, 1);
    heapPolicy->display();

    heapPolicy->increaseCost(3000);
    heapPolicy->increasePayoutAmount(7000);
    heapPolicy->completePolicy();
    heapPolicy->markPayout();
    heapPolicy->display();

    delete heapPolicy; // Звільнення пам'яті
}

// Меню користувача (рекурсивне)
void menu(PolicyDatabase& policyDB) {
    int selection;

    cout << "\n*** MENU ***\n"
         << "1) Add a new policy\n"
         << "2) Complete a policy\n"
         << "3) Mark payout for policy\n"
         << "4) Increase policy cost\n"
         << "5) Increase policy payout\n"
         << "6) List all policies\n"
         << "7) List active policies\n"
         << "8) List completed policies\n"
         << "9) List policies with payout\n"
         << "0) Quit\n"
         << "\n"
         << "---> ";
    cin >> selection;

    switch (selection) {
        case 1:
            menuAddPolicy(policyDB);
            break;
        case 2:
            menuCompletePolicy(policyDB);
            break;
        case 3:
            menuMarkPayout(policyDB);
            break;
        case 4:
            menuIncreaseCost(policyDB);
            break;
        case 5:
            menuIncreasePayout(policyDB);
            break;
        case 6:
            policyDB.displayAll();
            break;
        case 7:
            policyDB.displayActive();
            break;
        case 8:
            policyDB.displayCompleted();
            break;
        case 9:
            policyDB.displayWithPayout();
            break;
        case 0:
            return;
        default:
            cerr << "Unknown command.\n";
    }

    menu(policyDB);
}

int main(int argc, char** argv) {
    system("clear"); // Linux
    // system("cls"); // Windows

    PolicyDatabase policyDB;

    test();

    menu(policyDB);

    return 0;
}