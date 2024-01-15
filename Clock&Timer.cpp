#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

void showCurrentTime() {
    while (true) {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        cout << ctime(&currentTime) << endl;

        this_thread::sleep_for(chrono::seconds(1));
        system("cls"); 
    }
}

	void countdownTimer(int seconds) 
{
    if (seconds < 0) {
        cout << "Error: the number of seconds cannot be negative." << endl;
        return; 
    }

    while (seconds > 0) {
        cout << "Remaining time: " << seconds << " seconds" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        seconds--;
        system("cls"); 
    }

    cout << "End of time!" << endl;
}


int main() {
    int choice;
    cout << "Select an option: \n1. Show current time\n2. Set the timer\n";
    cin >> choice;

    if (choice == 1) {
        showCurrentTime();
    } else if (choice == 2) {
        int seconds;
        do
        {
        cout << "Enter the time in seconds: ";
        cin >> seconds;
        if (seconds < 0)
        {
        	cout<<"Error: Enter a number greater than 0"<<endl;
		}
    }
    while (seconds < 0);
    
        countdownTimer(seconds);
    } else {
        cout << "Incorrect choice." << endl;
    }

    return 0;
}
