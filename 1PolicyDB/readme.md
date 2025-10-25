# ЛАБОРАТОРНА РОБОТА 1

## Технології розробки системних програм для POSIX сумісних (сертифікованих) операційних систем

**Виконав:** Семен Прохода ІП-з31

### Завдання до роботи

**Варіант 5:** Інформаційна система Страхової компанії.

1. Створити клас(створити заголовочний файл і файл реалізації): Поліси.
    - Номер поліса
    - Дата початку
    - Дата закінчення
    - Вартість
    - Сума виплати
    - Код виду поліса
    - Відмітка про виплату
    - Відмітка про закінчення
    - Код клієнта 
    - Код співробітника
2. Створити файл main.cpp для екземплярів класу на купі пам'яті і на стеку.
3. Зібрати проєкт через Makefile.
4. Протестувати за допомогою Makefile.

### Короткий опис реалізації

-   Клас `Policy`:
    -   відмітка про виплату (лише для завершених полісів)
    -   завершення полісу
    -   збільшення вартості та суми виплати
    -   вивід
-   Клас `PolicyDatabase`:
    -   додавання полісів з автоінкрементом ID
    -   отримання поліса
    -   вивід усіх, активних, завершених та з виплатою
-   Тестування:
    -   створення екземплярів на стеку та на купі через `test()`
    -   автоматичний ввід через `Makefile`

### Лістинг програми

#### [Policy.h](src/Policy.h)

```cpp
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
```

#### [Policy.cpp](src/Policy.cpp)

```cpp
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
```

#### [PolicyDatabase.h](src/PolicyDatabase.h)

```cpp
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
```

#### [PolicyDatabase.cpp](src/PolicyDatabase.cpp)

```cpp
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
```

#### [main.cpp](src/main.cpp)

```cpp
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
```

#### [Makefile](Makefile)

```make
app = policyDB
cpps = main.cpp Policy.cpp PolicyDatabase.cpp

$(app): $(cpps)
	g++ $(cpps) -o $(app)

all: $(app)

run: $(app)
	./$(app)

clean:
	rm -f $(app) testout.txt

test: $(app)
	./$(app) < testin.txt > testout.txt
```

#### [testin.txt](test/testin.txt)

```
1
01.01.2001
31.12.2001
1
1
1

1
01.01.2002
31.12.2002
1
2
1

1
01.01.2003
31.12.2003
1
3
2

6

2
0

3
0

4
1
1000

5
1
2000

6
7
8
9
0
```

### Збірка та запус (Linux)

```bash
make # збірка
make run # запуск
make test # авто тестування
cat testout.txt # перегляд виводу
make clean # очищення
```

### Результати тестування

#### Створення поліса на стеку і на купі, збільшення вартості та виплати, завершення та виплата

```
--- test policy on stack ---
==================================
Policy ID: 0
Start Date: 01.01.2020
End Date: 01.01.2021
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Active
Payout: Not Made
==================================

Policy cost increased by 2000$
Payout amount increased by 5000$
==================================
Policy ID: 0
Start Date: 01.01.2020
End Date: 01.01.2021
Cost: 7000$
Payout Amount: 15000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Active
Payout: Not Made
==================================

--- test policy on heap ---
==================================
Policy ID: 1
Start Date: 01.01.2021
End Date: 01.01.2022
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 2
Employee ID: 1
Status: Active
Payout: Not Made
==================================

Policy cost increased by 3000$
Payout amount increased by 7000$
Policy 1 has been completed.
Payout of 17000$ marked for policy 1
==================================
Policy ID: 1
Start Date: 01.01.2021
End Date: 01.01.2022
Cost: 8000$
Payout Amount: 17000$
Policy Type ID: 1
Client ID: 2
Employee ID: 1
Status: Completed
Payout: Made
==================================
```

#### Додавання 3 полісів через меню.

Частина [testin.txt](test/testin.txt)

```
1
01.01.2001
31.12.2001
1
1
1

1
01.01.2002
31.12.2002
1
2
1

1
01.01.2003
31.12.2003
1
3
2
```

Частина [testout.txt](test/testout.txt)

```
*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Start date (dd.mm.yyyy): End date (dd.mm.yyyy): Policy type ID: Client ID: Employee ID: Policy 0 has been activated.
Policy 0 created successfully!

*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Start date (dd.mm.yyyy): End date (dd.mm.yyyy): Policy type ID: Client ID: Employee ID: Policy 1 has been activated.
Policy 1 created successfully!

*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Start date (dd.mm.yyyy): End date (dd.mm.yyyy): Policy type ID: Client ID: Employee ID: Policy 2 has been activated.
Policy 2 created successfully!
```

Частина [testin.txt](test/testin.txt)

```
6
```

Частина [testout.txt](test/testout.txt)

```
*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

--->
*** ALL POLICIES ***
==================================
Policy ID: 0
Start Date: 01.01.2001
End Date: 31.12.2001
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Active
Payout: Not Made
==================================

==================================
Policy ID: 1
Start Date: 01.01.2002
End Date: 31.12.2002
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 2
Employee ID: 1
Status: Active
Payout: Not Made
==================================

==================================
Policy ID: 2
Start Date: 01.01.2003
End Date: 31.12.2003
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 3
Employee ID: 2
Status: Active
Payout: Not Made
==================================
```

#### Зміна станів, вартості та виплати

Частина [testin.txt](test/testin.txt)

```
2
0

3
0

4
1
1000

5
1
2000
```

Частина [testout.txt](test/testout.txt)

```
*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Policy ID: Policy 0 has been completed.

*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Policy ID: Payout of 10000$ marked for policy 0

*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Policy ID: Increase amount: Policy cost increased by 1000$

*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> Policy ID: Increase amount: Payout amount increased by 2000$
```

#### Демонстрація відбору: усі/активні/завершені/з виплатою.

Частина [testin.txt](test/testin.txt)

```
6
7
8
9
```

Частина [testout.txt](test/testout.txt)

```
*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> 
*** ALL POLICIES ***
==================================
Policy ID: 0
Start Date: 01.01.2001
End Date: 31.12.2001
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Completed
Payout: Made
==================================

==================================
Policy ID: 1
Start Date: 01.01.2002
End Date: 31.12.2002
Cost: 6000$
Payout Amount: 12000$
Policy Type ID: 1
Client ID: 2
Employee ID: 1
Status: Active
Payout: Not Made
==================================

==================================
Policy ID: 2
Start Date: 01.01.2003
End Date: 31.12.2003
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 3
Employee ID: 2
Status: Active
Payout: Not Made
==================================


*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> 
*** ACTIVE POLICIES ***
==================================
Policy ID: 1
Start Date: 01.01.2002
End Date: 31.12.2002
Cost: 6000$
Payout Amount: 12000$
Policy Type ID: 1
Client ID: 2
Employee ID: 1
Status: Active
Payout: Not Made
==================================

==================================
Policy ID: 2
Start Date: 01.01.2003
End Date: 31.12.2003
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 3
Employee ID: 2
Status: Active
Payout: Not Made
==================================


*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> 
*** COMPLETED POLICIES ***
==================================
Policy ID: 0
Start Date: 01.01.2001
End Date: 31.12.2001
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Completed
Payout: Made
==================================


*** MENU ***
1) Add a new policy
2) Complete a policy
3) Mark payout for policy
4) Increase policy cost
5) Increase policy payout
6) List all policies
7) List active policies
8) List completed policies
9) List policies with payout
0) Quit

---> 
*** POLICIES WITH PAYOUT ***
==================================
Policy ID: 0
Start Date: 01.01.2001
End Date: 31.12.2001
Cost: 5000$
Payout Amount: 10000$
Policy Type ID: 1
Client ID: 1
Employee ID: 1
Status: Completed
Payout: Made
==================================
```
### Висновок
У ході виконання лабораторної роботи було розроблено інформаційну систему для страхової компанії, реалізовано основні класи та функціонал згідно з вимогами завдання. Програма успішно проходить тестування, коректно працює з полісами, забезпечує додавання, зміну стану, збільшення вартості та суми виплати, а також фільтрацію за різними критеріями.
