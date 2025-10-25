#pragma once
#include <iostream>
#include <string>

using namespace std;

const int DEFAULT_POLICY_COST = 5000;
const int DEFAULT_PAYOUT_AMOUNT = 10000;

class Policy {
private:
    int policyID; // Номер поліса
    string startDate; // Дата початку
    string endDate; // Дата закінчення
    int cost; // Вартість
    int payoutAmount; // Сума виплати
    int policyTypeID; // Код виду поліса
    bool payoutMade; // Відмітка про виплату
    bool completed; // Відмітка про закінчення
    int clientID; // Код клієнта
    int employeeID; // Код співробітника

public:
    // Конструктори
    Policy();
    Policy(int policyID, string startDate, string endDate, int policyTypeID, int clientID, int employeeID);

    // Геттери
    int getPolicyID();
    string getStartDate();
    string getEndDate();
    int getCost();
    int getPayoutAmount();
    int getPolicyTypeID();
    int getClientID();
    int getEmployeeID();
    bool isCompleted();
    bool isPayoutMade();
    
    // Методи
    void completePolicy();
    void markPayout();
    void increaseCost(int amount);
    void increasePayoutAmount(int amount);
    void display();
};