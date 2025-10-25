#include "Policy.h"
#include <iostream>
#include <string>

using namespace std;

Policy::Policy() {
    policyID = -1;
    startDate = "";
    endDate = "";
    cost = DEFAULT_POLICY_COST;
    payoutAmount = DEFAULT_PAYOUT_AMOUNT;
    policyTypeID = 0;
    payoutMade = false;
    completed = false;
    clientID = -1;
    employeeID = -1;
}

Policy::Policy(int policyID, string startDate, string endDate, int policyTypeID, int clientID, int employeeID) {
    this->policyID = policyID;
    this->startDate = startDate;
    this->endDate = endDate;
    cost = DEFAULT_POLICY_COST;
    payoutAmount = DEFAULT_PAYOUT_AMOUNT;
    this->policyTypeID = policyTypeID;
    payoutMade = false;
    completed = false;
    this->clientID = clientID;
    this->employeeID = employeeID;
}

int Policy::getPolicyID() {
    return policyID;
}

string Policy::getStartDate() {
    return startDate;
}

string Policy::getEndDate() {
    return endDate;
}

int Policy::getCost() {
    return cost;
}

int Policy::getPayoutAmount() {
    return payoutAmount;
}

int Policy::getPolicyTypeID() {
    return policyTypeID;
}

int Policy::getClientID() {
    return clientID;
}

int Policy::getEmployeeID() {
    return employeeID;
}

bool Policy::isCompleted() {
    return completed;
}

bool Policy::isPayoutMade() {
    return payoutMade;
}

void Policy::completePolicy() {
    completed = true;
    cout << "Policy " << policyID << " has been completed.\n";
}

void Policy::markPayout() {
    // Перевірка статусу поліса
    if (completed) {
        payoutMade = true;
        cout << "Payout of " << payoutAmount << "$ marked for policy " << policyID << "\n";
    } else {
        cerr << "Cannot mark payout for incomplete policy!\n";
        throw exception();
    }
}

void Policy::increaseCost(int amount) {
    cost += amount;
    cout << "Policy cost increased by " << amount << "$\n";
}

void Policy::increasePayoutAmount(int amount) {
    payoutAmount += amount;
    cout << "Payout amount increased by " << amount << "$\n";
}

void Policy::display() {
    cout << "==================================\n"
         << "Policy ID: " << getPolicyID() << "\n"
         << "Start Date: " << getStartDate() << "\n"
         << "End Date: " << getEndDate() << "\n"
         << "Cost: " << getCost() << "$\n"
         << "Payout Amount: " << getPayoutAmount() << "$\n"
         << "Policy Type ID: " << getPolicyTypeID() << "\n"
         << "Client ID: " << getClientID() << "\n"
         << "Employee ID: " << getEmployeeID() << "\n"
         << "Status: " << (completed ? "Completed" : "Active") << "\n"
         << "Payout: " << (payoutMade ? "Made" : "Not Made") << "\n"
         << "==================================\n\n";
}