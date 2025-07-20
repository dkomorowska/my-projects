#include <iostream>
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

class User {
	protected:
	    char correctPIN[5];
	    char cardNumber[20];
	    char name[50];
	    char address[100];
	    char email[50];
	    char phone[20];
	    double accountTotal;
    
    public:
	    User();
	    void displayUserInfo();
	    const char* getCorrectPIN();
	    void withdrawMoney();
	    void depositeMoney();
};

User::User()
{
    strcpy(correctPIN, "4444");
    strcpy(cardNumber, "9876543210123456");
    strcpy(name, "Lala La");
    strcpy(address, "Kipsalas iela 6a, Riga, Latvia");
    strcpy(email, "lalala@gmail.com");
    strcpy(phone, "+371 987 654 321");
    accountTotal=100;
}

const char* User::getCorrectPIN()
{
    return correctPIN;
}

void User::displayUserInfo() {
    gotoxy(10, 14); cout<<"\033[36mName:\033[0m "<<"				"<<name;
    gotoxy(10, 15); cout<<"\033[36mAddress:\033[0m "<<"			"<<address;
    gotoxy(10, 16); cout<<"\033[36mEmail:\033[0m "<<"			"<<email;
    gotoxy(10, 17); cout<<"\033[36mPhone:\033[0m "<<"			"<<phone;
    gotoxy(10, 18); cout<<"\033[36mCard Number:\033[0m "<<"			"<<cardNumber;
    gotoxy(10, 20); cout<<"\033[31mAccount Balance:\033[0m "<<"			"<<accountTotal<<"$";//euro sign needs to be corrected

}
void loadingBar()
{
    gotoxy(35, 10); cout<<"Loading: ";
    for (int i=0; i<6; i++) 
	{
        cout<<"#";
        this_thread::sleep_for(chrono::milliseconds(300));
    }
}

bool isMultipleOfTen(int number) {
  return number % 10 == 0;
}

void User::withdrawMoney() {
  int _amount = 0;

  system("cls");
  gotoxy(40, 5); cout<<" *****WITHDRAWEL*****"<<endl;
  gotoxy(40, 7); cout<<"Enter the amount:\n";
  gotoxy(40, 8); cin >> _amount;
system("cls");
  if(_amount >= 10 && isMultipleOfTen(_amount)) {
  int checkAccountTotal = accountTotal - _amount;
    if (checkAccountTotal > 0) {
        accountTotal -= _amount;
    }
    gotoxy(40, 5); cout << "Withdrawal Successful!"<< endl;
  } else {
    gotoxy(40, 5); cout << "The amount should be greater then and a multiple of 10!" << endl;
  }
  getch();
}


void User::depositeMoney(){
    bool attemts = true;
    int deposit = 0;
    system("cls");
    gotoxy(40, 5); cout<<" *****DEPOSIT*****"<<endl;
    gotoxy(40, 7); cout<<"Enter the amount:\n";
    gotoxy(40, 8); cin >> deposit;
    if (deposit > 0 && isMultipleOfTen(deposit)){
        accountTotal += deposit;
    }
    else{
        cout << "You`ve entered the wrong amount!\nTry again";
    }
}

int main() 
{
	User user;
    string enteredPIN;
    int attempts=0;

    while (true) 
	{
        system("cls");
        gotoxy(35, 5); cout<<"\033[36m********** ATM **********\033[0m";
        gotoxy(25, 7); cout<<"Enter your card 	-	press ENTER\n";
        gotoxy(25, 8); cout<<"Quit 			-	press ESC";
        char choice = _getch();
        
        if (choice==27) 
		{
			gotoxy(38, 15); cout<<"\033[31m"<<"Exiting ATM Goodbye!"<<" \033[0m"<<endl<<endl;
            break;
        } else if (choice==13) 
		{
            system("cls");
            loadingBar();
            
            do {
                system("cls");
                enteredPIN="";
                gotoxy(28, 8); cout<<"\033[36m"<<"Your trusted financial partner = Welcome!\n"<<"\033[0m"<<endl<<endl;
                gotoxy(31, 10);cout<<"Enter your 4-digit PIN: ";
                
                for (int i=0; i<4; i++) 
				{
                    char ch=_getch();
                    if (isdigit(ch)) 
					{
                        enteredPIN+=ch;
                        cout<<"*";
                    } else {
                        i--;// ignoring non-numeric inputs
                    }
                }
                
                if (enteredPIN==user.getCorrectPIN()) 
				{
                    gotoxy(20, 13); cout<<"PIN correct! Access granted\n";
                    break;
                } else {
                    attempts++;
                    gotoxy(30, 13); cout<<"Incorrect PIN - Attempts left: "<<(3 - attempts)<<"\n";
                    this_thread::sleep_for(chrono::seconds(1));
                }
                
            } while (attempts<3);
            
            if (attempts>=3) 
			{
				system ("cls");
				gotoxy(30, 8); cout<<"\033[31m"<<"Too many incorrect attempts - Card blocked\n"<<" \033[0m"<<endl<<endl;
                break;
            }
            while (true) 
			{
                system("cls");
                gotoxy(40, 5); cout<<" *****MENU*****"<<endl;
                gotoxy(40, 7); cout<<"1. Withdraw Money";
                gotoxy(40, 8); cout<<"2. Deposit Money";
                gotoxy(40, 9); cout<<"3. Exit";
                user.displayUserInfo();

                char option = _getch();
                switch (option) {
                    case '1':
                        gotoxy(5, 13); 
				//		cout<<"Withdrawing money";
                        user.withdrawMoney();
                        break;
                    case '2':
                        gotoxy(5, 13); 
				//		cout<<"Depositing money";
        user.depositeMoney();        
                        break;
                    case '3':
                    	system("cls");
                    	gotoxy(38, 15); cout<<"\033[31m"<<"Exiting ATM Goodbye!"<<" \033[0m"<<endl<<endl;
                        return 0;
                    default:
                        gotoxy(5, 14); 
						cout<<"Invalid choice, try again.";
                }
            }
        }
		else {
            cout<<"Invalid choice - Try again\n";
        }
    }
    
    return 0;
}
