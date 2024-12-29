#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib> 

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

const int MAX_TASKS = 100;
string taskManagement[MAX_TASKS][6];
int taskCount = 0;

const int MAX_BORROWS = 100;
string borrowRecords[MAX_BORROWS][7];
int borrowRecordCount = 0;

const int MAX_ITEMS = 100;
string inventoryManagement[MAX_ITEMS][5];
int inventoryCount = 0;

// =================== Task Management ===================
bool isNumeric(string str) {
    for (char ch : str) {
        if (ch < '0' || ch > '9') {
            return false;
        }
    }
    return true;
}

bool isValidDate(string date) {
    string year, month, day;
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < date.length(); ++i) {
        if (i < 4) {
            year += date[i];
        } else if (i > 4 && i < 7) {
            month += date[i];
        } else if (i > 7) {
            day += date[i];
        }
    }

    if (!isNumeric(year) || !isNumeric(month) || !isNumeric(day)) {
        return false;
    }

    if (month < "01" || month > "12") return false;
    if (day < "01" || day > "31") return false;

    return true;
}

void addNewTask() {
    if (taskCount >= MAX_TASKS) {
        cout << "ERROR: Task list is full!" << endl;
        return;
    }

    cin.ignore();

    do {
        cout << "Enter task title: ";
        getline(cin, taskManagement[taskCount][0]);
        if (taskManagement[taskCount][0].empty()) {
            cout << "Task title cannot be empty. Please try again." << endl;
        }
    } while (taskManagement[taskCount][0].empty());

    do {
        cout << "Enter task description: ";
        getline(cin, taskManagement[taskCount][1]);
        if (taskManagement[taskCount][1].empty()) {
            cout << "Task description cannot be empty. Please try again." << endl;
        }
    } while (taskManagement[taskCount][1].empty());

    do {
        cout << "Enter task deadline (YYYY-MM-DD): ";
        getline(cin, taskManagement[taskCount][2]);
        if (!isValidDate(taskManagement[taskCount][2])) {
            cout << "Invalid date format. Please use YYYY-MM-DD." << endl;
        }
    } while (!isValidDate(taskManagement[taskCount][2]));

    do {
        cout << "Enter task priority (normal/urgent): ";
        getline(cin, taskManagement[taskCount][3]);
        if (taskManagement[taskCount][3] != "normal" && taskManagement[taskCount][3] != "urgent") {
            cout << "Invalid task priority. Please enter 'normal' or 'urgent'." << endl;
        }
    } while (taskManagement[taskCount][3] != "normal" && taskManagement[taskCount][3] != "urgent");

    taskManagement[taskCount][4] = "New";

    do {
        cout << "Enter technician name: ";
        getline(cin, taskManagement[taskCount][5]);
        if (taskManagement[taskCount][5].empty()) {
            cout << "Technician name cannot be empty. Please try again." << endl;
        }
    } while (taskManagement[taskCount][5].empty());

    taskCount++;
    cout << "Task added successfully!" << endl;
}

void getDetailsTask() {
    if (taskCount == 0) {
        cout << "WARN: No tasks available." << endl;
        return;
    }

    cout << "\n=== Task List ===\n";
    for (int i = 0; i < taskCount; i++) {
        cout << "Task ID: " << i + 1 << ", Title: " << taskManagement[i][0] << ", Description: " << taskManagement[i][1] << ", Deadline: " << taskManagement[i][2] << ", Priority: " << taskManagement[i][3] << ", Status: " << taskManagement[i][4] << ", Technician: " << taskManagement[i][5] << endl;
    }
}

void taskManagementMenu() {
    clearScreen();
    int choice;
    do {
        cout << "\n=== Task Management ===\n";
        cout << "1. Add a new task\n";
        cout << "2. View task list\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewTask();
                break;
            case 2:
                getDetailsTask();
                break;
            case 3:
                cout << "Returning to previous menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// =================== Inventory Management ===================
void addNewInventory() {
    if (inventoryCount >= MAX_ITEMS) {
        cout << "ERROR: Inventory list is full!" << endl;
        return;
    }

    cin.ignore();
    do {
        cout << "Enter item code: ";
        getline(cin, inventoryManagement[inventoryCount][0]);
        if (inventoryManagement[inventoryCount][0].empty()) {
            cout << "Item code cannot be empty. Please try again." << endl;
        }
    } while (inventoryManagement[inventoryCount][0].empty());


    do {
        cout << "Enter item name: ";
        getline(cin, inventoryManagement[inventoryCount][1]);
        if (inventoryManagement[inventoryCount][1].empty()) {
            cout << "Item name cannot be empty. Please try again." << endl;
        }
    } while (inventoryManagement[inventoryCount][1].empty());

    do {
        cout << "Enter quantity: ";
        getline(cin, inventoryManagement[inventoryCount][2]);
        if (inventoryManagement[inventoryCount][2].empty()) {
            cout << "Quantity cannot be empty. Please try again." << endl;
        }
    } while (inventoryManagement[inventoryCount][2].empty());

    do {
        cout << "Enter category (tools/supplies): ";
        getline(cin, inventoryManagement[inventoryCount][3]);
        if (inventoryManagement[inventoryCount][3].empty()) {
            cout << "Category cannot be empty. Please try again." << endl;
        }
    } while (inventoryManagement[inventoryCount][3].empty());

    inventoryManagement[inventoryCount][4] = "Available";

    inventoryCount++;
    cout << "Inventory added successfully!\n";
}

void getDetailsInventory() {
    if (inventoryCount == 0) {
        cout << "WARN: Inventory list is empty.\n";
        return;
    }

    cout << "\n=== Inventory List ===\n";
    for (int i = 0; i < inventoryCount; i++) {
        cout << "Item ID: " << i + 1 << ", Item Code: " << inventoryManagement[i][0] << ", Item Name: " << inventoryManagement[i][1] << ", Quantity: " << inventoryManagement[i][2] << ", Category: " << inventoryManagement[i][3]<< ", Status: " << inventoryManagement[i][4]<< endl;
    }
}

void getDetailsTools() {
    if (inventoryCount == 0) {
        cout << "WARN: Inventory list is empty.\n";
        return;
    }

    cout << "\n=== Inventory List ===\n";
    for (int i = 0; i < inventoryCount; i++) {
        if (inventoryManagement[i][3] == "tools") {
           cout << "Item ID: " << i + 1 << ", Item Code: " << inventoryManagement[i][0] << ", Item Name: " << inventoryManagement[i][1] << ", Quantity: " << inventoryManagement[i][2] << ", Category: " << inventoryManagement[i][3] << ", Status: " << inventoryManagement[i][4]<< endl;
        }
     }
}

void displayBorrowRecords() {
    if (borrowRecordCount == 0) {
        cout << "WARN: borrowRecord is empty.\n";
        return;
    }

    cout << "\n=== BorrowRecord ===\n";
    for (int i = 0; i < borrowRecordCount; i++) {
        if (borrowRecords[i][6] == "borrowed") {
            string Created_at = borrowRecords[i][5];
            int duration = stoi(borrowRecords[i][4]);

            tm tm = {};
            sscanf(Created_at.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
            tm.tm_year -= 1900;
            tm.tm_mon -= 1;

            time_t startTime = mktime(&tm);
            time_t estimatedReturnTime = startTime + (duration * 24 * 60 * 60);

            tm = *localtime(&estimatedReturnTime);
            string estimatedReturnDate = to_string(1900 + tm.tm_year) + "-" + (tm.tm_mon + 1 < 10 ? "0" : "") + to_string(tm.tm_mon + 1) + "-" + (tm.tm_mday < 10 ? "0" : "") + to_string(tm.tm_mday);
 
            cout << "Item ID: " << i + 1 << ", Item Code: " << borrowRecords[i][0] << ", Item Name: " << borrowRecords[i][1] << ", Quantity: " << borrowRecords[i][2] << ", Borrower: " << borrowRecords[i][3] << ", Duration: " << borrowRecords[i][4] << ", Created_at: " << borrowRecords[i][5] << ", Estimated Return Date: " << estimatedReturnDate << ", Status: " << borrowRecords[i][6] << endl;
        }
     }
}

void inventoryManagementMenu() {
    clearScreen();
    int choice;
    do {
        cout << "\n=== Inventory Management ===\n";
        cout << "1. Add a new inventory\n";
        cout << "2. View inventory list\n";        
        cout << "3. View Borrow Records\n";
        cout << "4. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addNewInventory();
                break;
            case 2:
                getDetailsInventory();
                break;
            case 3:
                displayBorrowRecords();
                break;
            case 4:
                cout << "Returning to previous menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// =================== Tools Usage ===================
void borrowTool() {
    if (borrowRecordCount >= MAX_BORROWS) {
        cout << "ERROR: Borrow record limit is full!" << endl;
        return;
    }

    getDetailsTools();

    cin.ignore();
    do {
        cout << "Enter item code to borrow: ";
        getline(cin, borrowRecords[borrowRecordCount][0]);
        if (borrowRecords[borrowRecordCount][0].empty()) {
            cout << "Item code cannot be empty. Please try again." << endl;
        }
    } while (borrowRecords[borrowRecordCount][0].empty());

    bool found = false;
    for (int i = 0; i < inventoryCount; i++) {
        if (inventoryManagement[i][0] == borrowRecords[borrowRecordCount][0]) {
            found = true;
            
            borrowRecords[borrowRecordCount][1] = inventoryManagement[i][1];

            do {
                cout << "Enter quantity to borrow: ";
                getline(cin, borrowRecords[borrowRecordCount][2]);
                if (borrowRecords[borrowRecordCount][2].empty() || !isNumeric(borrowRecords[borrowRecordCount][2])) {
                    cout << "Quantity must be a valid number. Please try again." << endl;
                } else if (stoi(inventoryManagement[i][2]) < stoi(borrowRecords[borrowRecordCount][2])) {
                    cout << "Insufficient stock. Current stock: " << inventoryManagement[i][2] << endl;
                } else {
                    inventoryManagement[i][2] = to_string(stoi(inventoryManagement[i][2]) - stoi(borrowRecords[borrowRecordCount][2]));
                    if (stoi(inventoryManagement[i][2]) == 0) {
                        inventoryManagement[i][4] = "InUse";
                    }
                    break;
                }
            } while (true);

            do {
                cout << "Enter borrower name: ";
                getline(cin, borrowRecords[borrowRecordCount][3]);
                if (borrowRecords[borrowRecordCount][3].empty()) {
                    cout << "Borrower name cannot be empty. Please try again." << endl;
                }
            } while (borrowRecords[borrowRecordCount][3].empty());

            do {
                cout << "Enter duration in days (1/2): ";
                getline(cin, borrowRecords[borrowRecordCount][4]);
                if (borrowRecords[borrowRecordCount][4].empty() || !isNumeric(borrowRecords[borrowRecordCount][4])) {
                    cout << "Duration must be a valid number greater than 0. Please try again." << endl;
                }
            } while (borrowRecords[borrowRecordCount][4].empty());

            time_t now = time(0);
            tm *localTime = localtime(&now);
            string currentDate = to_string(1900 + localTime->tm_year) + "-" + (localTime->tm_mon + 1 < 10 ? "0" : "") + to_string(localTime->tm_mon + 1) + "-" + (localTime->tm_mday < 10 ? "0" : "") + to_string(localTime->tm_mday);

            borrowRecords[borrowRecordCount][5] = currentDate;
            borrowRecords[borrowRecordCount][6] = "borrowed";

            cout << "Tool borrowed successfully!" << endl;
            borrowRecordCount++;
            break;
        }
    }

    if (!found) {
        cout << "Tool not found!" << endl;
    }
}

void returnTool() {
    string Item_code;

    displayBorrowRecords();
    
    cin.ignore();
    do {
        cout << "Enter Item code to return: ";
        getline(cin, Item_code);
        if (Item_code.empty()) {
            cout << "Item code cannot be empty. Please try again." << endl;
        }
    } while (Item_code.empty());

    bool found = false;
    for (int i = 0; i < borrowRecordCount; i++) {
        if (borrowRecords[i][0] == Item_code) {
            found = true;
            if (borrowRecords[i][6] == "borrowed") {
                borrowRecords[i][6] = "returned";
            }

            if (inventoryManagement[i][4] == "InUse") {
                inventoryManagement[i][4] = "Available";
            }
            
            inventoryManagement[i][2] = to_string(stoi(inventoryManagement[i][2]) + stoi(borrowRecords[i][2]));

            cout << "Tool returned successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Tool not found!" << endl;
    }
}

void toolsUsageMenu() {
    clearScreen();
    int choice;
    do {
        cout << "\n=== Tools Usage ===\n";
        cout << "1. Borrow Tools\n";
        cout << "2. Return Tools\n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                borrowTool();
                break;
            case 2:
                returnTool();
                break;
            case 3:
                cout << "Returning to previous menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// =================== Task Operation ===================
void viewTasksByTechnician() {
    string technicianName;
    cin.ignore();
    do {
        cout << "Enter technician name to view assigned tasks: ";
        getline(cin, technicianName);
        if (technicianName.empty()) {
            cout << "Technician name cannot be empty. Please try again." << endl;
        }
    } while (technicianName.empty());    

    bool found = false;
    cout << "\n=== Tasks Assigned to " << technicianName << " ===\n";
    for (int i = 0; i < taskCount; i++) {
        if (taskManagement[i][5] == technicianName) {
            found = true;
            cout << "Task ID: " << i + 1 << ", Title: " << taskManagement[i][0] << ", Description: " << taskManagement[i][1] << ", Deadline: " << taskManagement[i][2] << ", Priority: " << taskManagement[i][3] << ", Status: " << taskManagement[i][4] << endl;
        }
    }

    if (!found) {
        cout << "No tasks found for technician " << technicianName << endl;
    }
}

void updateTaskStatus() {
    string taskIdStr, newStatus;
    int taskId;

    viewTasksByTechnician();

    cin.ignore();
    do {
        cout << "Enter task ID to update status: ";
        cin >> taskIdStr;
        if (taskIdStr.empty() || !isNumeric(taskIdStr)){
            cout << "Invalid task ID, Please try again." << endl;
            continue;
        }
        taskId = stoi(taskIdStr);
        if (taskId < 1 || taskId > taskCount) {
            cout << "Task ID out of range!" << endl;
            continue;
        }
        break;
    } while (true);

    cin.ignore();
    do {
        cout << "Enter new status (InProgress/Done): ";
        getline(cin, newStatus);
        if (newStatus != "InProgress" && newStatus != "Done") {
            cout << "Invalid status. Please enter 'InProgress' or 'Done'." << endl;
        }
    } while (newStatus != "InProgress" && newStatus != "Done");
    
    taskManagement[taskId - 1][4] = newStatus;
    cout << "Task status updated to " << newStatus << endl;
}

void taskOperationMenu() {
    clearScreen();
    int choice;
    do {
        cout << "\n=== Task Operation ===\n";
        cout << "1. View Taks\n";
        cout << "2. Update Task Status \n";
        cout << "3. Back\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewTasksByTechnician();
                break;
            case 2:
                updateTaskStatus();
                break;
            case 3:
                cout << "Returning to previous menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// =================== Main Menu ===================
void adminMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=== Admin Menu ===\n";
        cout << "1. Task Management\n";
        cout << "2. Inventory Management\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                taskManagementMenu();
                break;
            case 2:
                inventoryManagementMenu();
                break;
            case 3:
                cout << "Exiting Admin Menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void technicianMenu() {
    int choice;
    do {
        clearScreen();
        cout << "\n=== Technician Menu ===\n";
        cout << "1. Task Operation\n";
        cout << "2. Tools Usage\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                taskOperationMenu();
                break;
            case 2:
                toolsUsageMenu();
                break;
            case 3:
                cout << "Exiting Technician Menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// =================== Main Program ===================
int main() {
    int choice;
    do {
        clearScreen();
        cout << "\n=== Task and Inventory Management System ===\n";
        cout << "1. Login as Admin\n";
        cout << "2. Login as Technician\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                technicianMenu();
                break;
            case 3:
                cout << "Thank you for using the system!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}