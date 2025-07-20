#define NOMINMAX
#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <limits>
#include <sstream> // For std::istringstream
#include <stdexcept> 
using namespace std;

bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Helper function to get days in a month
int daysInMonth(int month, int year) {
    if (month < 1 || month > 12) return 0; // Invalid month
    if (month == 2) {
        return isLeap(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    else {
        return 31;
    }
}

bool isValidDate(const std::string& dateStr, int& year, int& month, int& day) {
    if (dateStr.length() != 10) return false; // Basic length check for YYYY-MM-DD
    if (dateStr[4] != '-' || dateStr[7] != '-') return false; // Check delimiters

    try {
        year = std::stoi(dateStr.substr(0, 4));
        month = std::stoi(dateStr.substr(5, 2));
        day = std::stoi(dateStr.substr(8, 2));
    }
    catch (const std::invalid_argument& ia) {
        return false; // Not numbers
    }
    catch (const std::out_of_range& oor) {
        return false; // Numbers too large/small for int
    }

    if (year < 1900 || year > 2100) return false; // Arbitrary reasonable year range
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;

    return true;
}

void gotoxy(int x, int y) {
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Task {
private:
    string description;
    string dueDate;
    bool isDone;

public:
    Task(string desc, string due);
    void displayTask(int y, int index);
    bool getStatus();
    void markAsDone();
};

Task::Task(string desc, string due)
{
    description = desc;
    dueDate = due;
    isDone = false;
}

void Task::displayTask(int y, int index) {
    gotoxy(5, y); cout << index << ".";
    gotoxy(10, y); cout << "\033[36mDescription:\033[0m " << setw(35) << left << description;
    gotoxy(50, y); cout << "\033[36mDue:\033[0m " << setw(15) << left << dueDate;
    gotoxy(70, y); cout << (isDone ? "\033[32mCompleted\033[0m" : "\033[31mIncomplete\033[0m");
}

bool Task::getStatus() {
    return isDone;
}

void Task::markAsDone() {
    isDone = true;
}

class TaskManager {
private:
    vector<Task> tasks;

public:
    void mainMenu();
    void addTask();
    void viewTasks();
    void markTaskDone();
    void summary();
};

void TaskManager::addTask() {
    system("cls");
    string desc, dateInput;
    int year, month, day;
    gotoxy(30, 5); cout << "Enter task description:";
    // Inside addTask:
    do {
        gotoxy(30, 6); cout << "                                        "; // Clear previous input area
        gotoxy(30, 6); getline(cin, desc);
        if (desc.empty()) {
            gotoxy(30, 10); cout << "\033[31mDescription cannot be empty. Try again.\033[0m";
            _getch(); // Pause briefly
            gotoxy(30, 10); cout << "                                             "; // Clear message
        }
    } while (desc.empty());

    gotoxy(30, 7); cout << "Enter due date:";
    // Similarly for date:
    bool dateIsValid = false;
    do {
        gotoxy(30, 7); cout << "Enter due date (YYYY-MM-DD):            "; // Clear previous, prompt
        gotoxy(30 + 30, 7); // Position for input
        getline(cin, dateInput); // No ws needed after desc if that used cin >> ws

        if (isValidDate(dateInput, year, month, day)) {
            dateIsValid = true;
        }
        else {
            gotoxy(30, 10); cout << "\033[31mInvalid date format or value. Use YYYY-MM-DD.\033[0m";
            _getch(); // Pause
            gotoxy(30, 10); cout << "                                                      "; // Clear message
        }
    } while (!dateIsValid);
    gotoxy(30, 10); cout << "\033[32mTask added successfully!\033[0m";
    tasks.push_back(Task(desc, dateInput));
    _getch();
}

void TaskManager::viewTasks() {
    system("cls");
    gotoxy(30, 3); cout << "\033[36mAll Tasks:\033[0m";
    int y = 5;
    if (tasks.empty()) {
        gotoxy(30, 5); cout << "No tasks available.";
    }
    else {
        for (size_t i = 0; i < tasks.size(); ++i) {
            tasks[i].displayTask(y, i + 1);
            y++;
        }
    }
    gotoxy(30, y + 2); cout << "Press any key to return to menu...";
    _getch();
}

void TaskManager::markTaskDone() {
    system("cls");
    gotoxy(30, 3); cout << "\033[36mMark Task as Done:\033[0m";
    int y = 5;
    vector<int> pendingIndexes;
    for (size_t i = 0; i < tasks.size(); ++i) {
        if (!tasks[i].getStatus()) {
            tasks[i].displayTask(y, pendingIndexes.size() + 1);
            pendingIndexes.push_back(i);
            y++;
        }
    }

    if (pendingIndexes.empty()) {
        gotoxy(30, 6); cout << "No incomplete tasks.";
        _getch();
        return;
    }

    gotoxy(30, y + 2); cout << "Enter task number to mark as done: ";
    int choice;

    // Improved input validation loop
    while (true) {
        cin >> choice;
        if (cin.good() && choice >= 1 && choice <= (int)pendingIndexes.size()) {
            // Clear any remaining characters in the buffer, especially the newline
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break; // Valid input, exit loop
        }
        else {
            cin.clear(); // Clear error flags (e.g., if non-numeric input was entered)
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard the bad input line
            gotoxy(30, y + 4); cout << "\033[31mInvalid input. Please enter a valid number.\033[0m";
            gotoxy(30, y + 2); cout << "Enter task number to mark as done:          "; // Clear prompt
            gotoxy(30 + 35, y + 2); // Position cursor back for input (approx)
        }
    }

    // Now 'choice' is valid
    tasks[pendingIndexes[choice - 1]].markAsDone();
    gotoxy(30, y + 5); cout << "\033[32mTask marked as done!\033[0m"; // Adjusted y for error message
    _getch();
}

void TaskManager::summary() {
    system("cls");
    int completed = 0, pending = 0;
    for (Task& t : tasks) {
        if (t.getStatus())
            completed++;
        else
            pending++;
    }

    gotoxy(30, 5); cout << "\033[36mSession Summary:\033[0m";
    gotoxy(30, 7); cout << "Total Tasks: " << tasks.size();
    gotoxy(30, 8); cout << "\033[32mCompleted:\033[0m " << completed;
    gotoxy(30, 9); cout << "\033[31mIncomplete:\033[0m " << pending;
    gotoxy(30, 11); cout << "Press any key to exit...";
    _getch();
}

void TaskManager::mainMenu() {
    while (true) {
        system("cls");
        gotoxy(35, 5); cout << "\033[36m********** TO-DO TASK APP **********\033[0m";
        gotoxy(40, 7); cout << "1. Add Task";
        gotoxy(40, 8); cout << "2. View Tasks";
        gotoxy(40, 9); cout << "3. Mark Task as Done";
        gotoxy(40, 10); cout << "4. Exit";

        char choice = _getch();

        switch (choice) {
        case '1':
            addTask();
            break;
        case '2':
            viewTasks();
            break;
        case '3':
            markTaskDone();
            break;
        case '4':
            summary();
            return;
        default:
            gotoxy(40, 12); cout << "Invalid choice. Try again.";
            this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

int main() {
    TaskManager manager;
    manager.mainMenu();
    return 0;
}
