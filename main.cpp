#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// =================== Task Management ===================
const int MAX_TASKS = 100;
string taskManagement[MAX_TASKS][6];
int taskCount = 0;

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
const int MAX_ITEMS = 100;
string inventoryManagement[MAX_ITEMS][5];
int inventoryCount = 0;

void addNewInventory() {
    if (inventoryCount >= MAX_ITEMS) {
        cout << "ERROR: Inventory list is full!" << endl;
        return;
    }

    cin.ignore();
    cout << "Enter item code: ";
    getline(cin, inventoryManagement[inventoryCount][0]);

    cout << "Enter item name: ";
    getline(cin, inventoryManagement[inventoryCount][1]);

    cout << "Enter quantity: ";
    getline(cin, inventoryManagement[inventoryCount][2]);

    cout << "Enter category: ";
    getline(cin, inventoryManagement[inventoryCount][3]);

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
        cout << "Item ID: " << i + 1 << ", Item Code: " << inventoryManagement[i][0] << ", Item Name: " << inventoryManagement[i][2] << ", Quantity: " << inventoryManagement[i][2] << ", Category: " << inventoryManagement[i][3]<< ", Status: " << inventoryManagement[i][4]<< endl;
    }
}

// =================== Tracking Peminjaman (Farisyah) ===================
const int MAX_BORROWS = 100;

// struct Inventory {
//     string item_code;
//     string item_name;
//     int quantity;
//     string status;
//     string category;
// };

// struct BorrowRecord {
//     string item_code;
//     string borrower_name;
//     string borrow_date;
//     string expected_return_date;
// };

// Inventory inventory[MAX_ITEMS];

// BorrowRecord borrowRecords[MAX_BORROWS];
string borrowRecords[MAX_BORROWS][4];

int borrowRecordCount = 0;

// Function to borrow a tool
void borrowTool() {
    if (borrowRecordCount >= MAX_BORROWS) {
        cout << "Borrow record limit reached!" << endl;
        return;
    }

    string item_code, borrower_name, borrow_date, expected_return_date;
    int quantity;

    cout << "Enter item code to borrow: ";
    cin >> item_code;

    bool found = false;
    for (int i = 0; i < inventoryCount; i++) {
        if (inventoryManagement[i][2] == item_code) {
            found = true;
            if (stoi(inventoryManagement[i][2]) > 0) {
                cout << "Enter quantity to borrow: ";
                cin >> quantity;
                if (quantity > stoi(inventoryManagement[i][2])) {
                    cout << "Not enough tools available." << endl;
                } else {
                    cout << "Enter borrower name: ";
                    cin.ignore();
                    getline(cin, borrower_name);

                    // Get current date for borrow date
                    time_t now = time(0);
                    tm* ltm = localtime(&now);
                    borrow_date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);

                    // Calculate expected return date (example: 7 days)
                    ltm->tm_mday += 7; // Adjust as needed
                    mktime(ltm);
                    expected_return_date = to_string(ltm->tm_mday) + "/" + to_string(1 + ltm->tm_mon) + "/" + to_string(1900 + ltm->tm_year);

                    inventoryManagement[borrowRecordCount][0] = item_code;
                    inventoryManagement[borrowRecordCount][1] = borrower_name;
                    inventoryManagement[borrowRecordCount][2] = borrow_date;
                    inventoryManagement[borrowRecordCount][3] = expected_return_date;
                    inventoryManagement[borrowRecordCount][4] = to_string(quantity);
                    borrowRecordCount++;

                    int currentQuantity = stoi(inventoryManagement[i][2]);
                    currentQuantity -= quantity;
                    inventoryManagement[i][2] = to_string(currentQuantity);

                    inventoryManagement[i][4] = "borrowed";
                    cout << "Tool borrowed successfully!" << endl;
                    cout << "Borrow Date: " << borrow_date << endl;
                    cout << "Expected Return Date: " << expected_return_date << endl;
                }
            } else {
                cout << "Tool is not available." << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Tool not found!" << endl;
    }
}

// Function to return a tool
void returnTool() {
    string item_code;
    int quantity;

    cout << "Enter tool code to return: ";
    cin >> item_code;

    bool found = false;
    for (int i = 0; i < inventoryCount; i++) {
        if (inventoryManagement[i][0] == item_code) { // Assuming [0] is the item code
            found = true;
            cout << "Enter quantity to return: ";
            cin >> quantity;

            int currentQuantity = stoi(inventoryManagement[i][2]); // Assuming [2] is the quantity
            currentQuantity += quantity;
            inventoryManagement[i][2] = to_string(currentQuantity);
            inventoryManagement[i][4] = "available"; // Assuming [4] is the status

            // Remove borrow record
            for (int j = 0; j < borrowRecordCount; j++) {
                if (borrowRecords[j][0] == item_code) { // Assuming [0] is the item code in borrowRecords
                    // Shift records to remove the borrowed one
                    for (int k = j; k < borrowRecordCount - 1; k++) {
                        borrowRecords[k][0] = borrowRecords[k + 1][0];
                        borrowRecords[k][1] = borrowRecords[k + 1][1];
                        borrowRecords[k][2] = borrowRecords[k + 1][2];
                        borrowRecords[k][3] = borrowRecords[k + 1][3];
                    }
                    borrowRecordCount--;
                    break;
                }
            }

            cout << "Tool returned successfully!" << endl;
            break;
        }
    }

    if (!found) {
        cout << "Tool not found!" << endl;
    }
}

// Function to display borrow records (optional)
void displayBorrowRecords() {
    if (borrowRecordCount == 0) {
        cout << "No borrow records found." << endl;
        return;
    }

    cout << "Borrow Records:" << endl;
    cout << "Item Code\tBorrower\tBorrow Date\tExpected Return Date" << endl;
    for (int i = 0; i < borrowRecordCount; i++) {
        cout << borrowRecords[i][0] << "\t" << borrowRecords[i][1] << "\t"
             << borrowRecords[i][2]<< "\t" << borrowRecords[i][3] << endl;
    }
}
// =================== Tracking Peminjaman (Farisyah) ===================

void inventoryManagementMenu() {
    int choice;
    do {
        cout << "\n=== Inventory Management ===\n";
        cout << "1. Add a new inventory\n";
        cout << "2. View inventory list\n";        
        cout << "3. Display Borrow Records\n";
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

// =================== Main Menu ===================
void adminMenu() {
    int choice;
    do {
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
        cout << "\n=== Technician Menu ===\n";
        cout << "1. View Task List\n";
        cout << "2. Borrow Tools\n";
        cout << "3. Return Tools\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                getDetailsTask();
                break;
            case 2:
                borrowTool();
                break;
            case 3:
                returnTool();
                break;
            case 4:
                cout << "Exiting Technician Menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// =================== Main Program ===================
int main() {
    int choice;
    do {
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