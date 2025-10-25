#include "PolicyDatabase.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

PolicyDatabase::PolicyDatabase() {
    nextPolicyID = FIRST_POLICY_NUM;
}

Policy& PolicyDatabase::addPolicy(string startDate, string endDate, int policyTypeID, int clientID, int employeeID) {
    Policy newPolicy(nextPolicyID++, startDate, endDate, policyTypeID, clientID, employeeID);
    policies.push_back(newPolicy);
    cout << "Policy " << newPolicy.getPolicyID() << " has been activated.\n";
    return policies.back();
}

Policy& PolicyDatabase::getPolicy(int policyID) {
    for (Policy& policy : policies)
        if (policy.getPolicyID() == policyID)
            return policy;

    cerr << "No policy with ID " << policyID << "\n";
    throw exception();
}

void PolicyDatabase::displayAll() {
    cout << "\n*** ALL POLICIES ***\n";
    for (Policy& policy : policies)
        policy.display();
}

void PolicyDatabase::displayActive() {
    cout << "\n*** ACTIVE POLICIES ***\n";
    for (Policy& policy : policies)
        if (!policy.isCompleted())
            policy.display();
}

void PolicyDatabase::displayCompleted() {
    cout << "\n*** COMPLETED POLICIES ***\n";
    for (Policy& policy : policies)
        if (policy.isCompleted())
            policy.display();
}

void PolicyDatabase::displayWithPayout() {
    cout << "\n*** POLICIES WITH PAYOUT ***\n";
    for (Policy& policy : policies)
        if (policy.isPayoutMade())
            policy.display();
}