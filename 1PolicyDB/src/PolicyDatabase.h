#pragma once
#include "Policy.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int FIRST_POLICY_NUM = 0;

class PolicyDatabase {
private:
    vector<Policy> policies;
    int nextPolicyID;

public:
    PolicyDatabase();

    Policy& addPolicy(string startDate, string endDate, int policyTypeID, int clientID, int employeeID);
    Policy& getPolicy(int policyID);

    void displayAll();
    void displayActive();
    void displayCompleted();
    void displayWithPayout();
};