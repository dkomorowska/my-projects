#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cstring>
#include <windows.h>
using namespace std;

void gotoxy(int x, int y) {
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Book {
protected:
    char title[100];
    char author[50];
    bool isAvailable;

public:
    Book(const char* _title = "", const char* _author = "");
    void displayInfo(int y, int index = -1);
    const char* getTitle();
    const char* getAuthor();
    bool getAvailability();
    void borrowBook();
    void returnBook();
};

Book::Book(const char* _title, const char* _author) {
    strcpy(title, _title);
    strcpy(author, _author);
    isAvailable = true;
}

void Book::displayInfo(int y, int index) {
    if (index != -1) {
        gotoxy(5, y); cout << index << ".";
    }
    gotoxy(10, y); cout << "\033[36mTitle:\033[0m " << left << setw(40) << title;
    gotoxy(55, y); cout << "\033[36mAuthor:\033[0m " << left << setw(20) << author;
    gotoxy(80, y); cout << (isAvailable ? "\033[32mAvailable\033[0m" : "\033[31mBorrowed\033[0m");
}

const char* Book::getTitle() 
{ return title; }
const char* Book::getAuthor() 
{ return author; }
bool Book::getAvailability() 
{ return isAvailable; }
void Book::borrowBook() 
{ isAvailable = false; }
void Book::returnBook() 
{ isAvailable = true; }

class Library {
private:
    Book books[10];
    int bookCount;

public:
    Library();
    void mainMenu();
    void searchBook();
    void borrowBook();
    void returnBook();
    void viewAllBooks();
    void sessionSummary();
};

Library::Library() {
    bookCount = 10;
    books[0] = Book("The Chronicles of Narnia", "C.S. Lewis");
    books[1] = Book("Percy Jackson & the Olympians", "Rick Riordan");
    books[2] = Book("The Hunger Games", "Suzanne Collins");
    books[3] = Book("The Hobbit", "J.R.R. Tolkien");
    books[4] = Book("Inkheart", "Cornelia Funke");
    books[5] = Book("Peter Pan", "J.M. Barrie");
    books[6] = Book("Alice's Adventures in Wonderland", "Lewis Carroll");
    books[7] = Book("His Dark Materials", "Philip Pullman");
    books[8] = Book("Fablehaven", "Brandon Mull");
    books[9] = Book("Charlie and the Chocolate Factory", "Roald Dahl");
}

void Library::searchBook() {
    system("cls");
    char query[50];
    gotoxy(35, 5); cout << "Enter title or author to search:";
    gotoxy(35, 6); cin.ignore();
    cin.getline(query, 50);

    system("cls");
    gotoxy(35, 3); cout << "\033[36mSearch Results:\033[0m";
    int y = 5;
    bool found = false;

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].getTitle(), query) || strstr(books[i].getAuthor(), query)) {
            books[i].displayInfo(y, i + 1);
            y++;
            found = true;
        }
    }

    if (!found) {
        gotoxy(35, 7); cout << "No matching books found.";
    }
    getch();
}

void Library::borrowBook() {
    system("cls");
    gotoxy(35, 3); cout << "\033[36mAvailable Books:\033[0m";
    int y = 5;
    int availableIndex[10];
    int availableCount = 0;

    for (int i = 0; i < bookCount; i++) {
        if (books[i].getAvailability()) {
            books[i].displayInfo(y, availableCount + 1);
            availableIndex[availableCount++] = i;
            y++;
        }
    }

    if (availableCount == 0) {
        gotoxy(35, 7); cout << "No available books.";
        getch();
        return;
    }

    gotoxy(35, y + 2); cout << "Enter number (1-" << availableCount << ") to borrow: ";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= availableCount) {
        books[availableIndex[choice - 1]].borrowBook();
        gotoxy(35, y + 4); cout << "\033[32mBook borrowed successfully!\033[0m";
    } else {
        gotoxy(35, y + 4); cout << "Invalid choice.";
    }
    getch();
}

void Library::returnBook() {
    system("cls");
    gotoxy(35, 3); cout << "\033[36mBorrowed Books:\033[0m";
    int y = 5;
    int borrowedIndex[10];
    int borrowedCount = 0;

    for (int i = 0; i < bookCount; i++) {
        if (!books[i].getAvailability()) {
            books[i].displayInfo(y, borrowedCount + 1);
            borrowedIndex[borrowedCount++] = i;
            y++;
        }
    }

    if (borrowedCount == 0) {
        gotoxy(35, 7); cout << "No borrowed books.";
        getch();
        return;
    }

    gotoxy(35, y + 2); cout << "Enter number (1-" << borrowedCount << ") to return: ";
    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= borrowedCount) {
        books[borrowedIndex[choice - 1]].returnBook();
        gotoxy(35, y + 4); cout << "\033[32mBook returned successfully!\033[0m";
    } else {
        gotoxy(35, y + 4); cout << "Invalid choice.";
    }
    getch();
}

void Library::viewAllBooks() {
    system("cls");
    gotoxy(35, 3); cout << "\033[36mAll Books:\033[0m";
    int y = 5;
    for (int i = 0; i < bookCount; i++) {
        books[i].displayInfo(y, i + 1);
        y++;
    }
    gotoxy(35, y + 2); cout << "Press any key to return to menu...";
    getch();
}

void Library::sessionSummary() {
    system("cls");
    gotoxy(35, 3); cout << "\033[36mSession Summary - Borrowed Books:\033[0m";
    int y = 5;
    for (int i = 0; i < bookCount; i++) {
        if (!books[i].getAvailability()) {
            books[i].displayInfo(y, i + 1);
            y++;
        }
    }
    if (y == 5) {
        gotoxy(35, 5); cout << "You have no borrowed books.";
    }
    gotoxy(35, y + 2); cout << "Press any key to exit...";
    getch();
}

void Library::mainMenu() {
    while (true) {
        system("cls");
        gotoxy(35, 5); cout << "\033[36m********** BOOK LIBRARY **********\033[0m";
        gotoxy(40, 7); cout << "1. Search Book";
        gotoxy(40, 8); cout << "2. Borrow Book";
        gotoxy(40, 9); cout << "3. Return Book";
        gotoxy(40, 10); cout << "4. View All Books";
        gotoxy(40, 11); cout << "5. Exit";

        char choice = _getch();

        switch (choice) {
            case '1':
                searchBook();
                break;
            case '2':
                borrowBook();
                break;
            case '3':
                returnBook();
                break;
            case '4':
                viewAllBooks();
                break;
            case '5':
                sessionSummary();
                return;
            default:
                gotoxy(40, 13); cout << "Invalid choice. Try again.";
                this_thread::sleep_for(chrono::seconds(1));
        }
    }
}

int main() {
    Library lib;
    lib.mainMenu();
    return 0;
}