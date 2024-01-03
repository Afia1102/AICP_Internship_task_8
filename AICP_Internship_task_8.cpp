//created by Afia mushtaq
//Superior University Lahore
//AICP internship Task 8

#include <iostream>
using namespace std;
//creating and initializing variables
const int NUM_BOATS = 10;
const int OPENING_TIME = 10;
const int CLOSING_TIME = 17;
const double HOURLY_RATE = 20.0;
const double HALF_HOUR_RATE = 12.0;
int currentTime;
//function declaration
bool isTimeValid(int currentTime, int duration);
void displayTime(int hours, int minutes);
void task1(bool isAvailable[], int returnTimes[], double moneyTaken[], double totalHoursHired[], int boatNumber, int currentTime);
void task2(bool isAvailable[], int returnTimes[], int currentTime);
void task3(double moneyTaken[], double totalHoursHired[]);
int main() {
    bool isAvailable[NUM_BOATS] = {true};
    int returnTimes[NUM_BOATS] = {0};
    double moneyTaken[NUM_BOATS] = {0.0};
    double totalHoursHired[NUM_BOATS] = {0.0};

    
    cout << "Enter the current time in 24-hour format (e.g., 13:30): ";
    cin >> currentTime;

    // Testing Task 1 for Boat 1
    task1(isAvailable, returnTimes, moneyTaken, totalHoursHired, 0, currentTime);

    // Testing Task 1 for Boat 3
    task1(isAvailable, returnTimes, moneyTaken, totalHoursHired, 2, currentTime);

    // Task 2: Find the next boat available
    task2(isAvailable, returnTimes, currentTime);

    // Task 3: Calculate the money taken for all the boats at the end of the day
    task3(moneyTaken, totalHoursHired);

    return 0;
}
// Function to check if the entered time and duration are valid
bool isTimeValid(int currentTime, int duration) {
    return currentTime >= OPENING_TIME && currentTime + duration / 60.0 <= CLOSING_TIME;
}

// Function to display time in HH:MM format
void displayTime(int hours, int minutes) {
    cout << hours << ":" << (minutes < 10 ? "0" : "") << minutes;
}

// Task 1: Calculate the money taken in a day for one boat
void task1(bool isAvailable[], int returnTimes[], double moneyTaken[], double totalHoursHired[], int boatNumber, int currentTime) {
    int hireDuration;

    cout << "Enter the duration for Boat " << boatNumber + 1 << " in minutes: ";
    cin >> hireDuration;

     if (cin.fail()) {
        cin.clear();  // Clear the error flag
        cin.ignore(1000, '\n');  // Discard invalid input
        cout << "Invalid input. Please enter a valid number.\n";
        return;
    }

    // Validate if the entered time and duration are valid
    if (!isTimeValid(currentTime, hireDuration)) {
        cout << "Invalid time. Boat can't be hired before 10:00 or returned after 17:00.\n";
        return;
    }

    isAvailable[boatNumber] = false;
    returnTimes[boatNumber] = currentTime + hireDuration / 60.0;
    totalHoursHired[boatNumber] += hireDuration / 60.0;

    // Update money taken based on hourly or half-hourly rate
    if (hireDuration >= 60) {
        moneyTaken[boatNumber] += HOURLY_RATE;
    } else {
        moneyTaken[boatNumber] += HALF_HOUR_RATE;
    }
}

// Task 2: Find the next boat available
void task2(bool isAvailable[], int returnTimes[], int currentTime) {
    int availableBoats = 0;
    int nextAvailableTime = CLOSING_TIME + 1;

    // Count available boats and find the earliest return time
    for (int i = 0; i < NUM_BOATS; ++i) {
        if (isAvailable[i]) {
            ++availableBoats;
        } else {
            nextAvailableTime = min(nextAvailableTime, returnTimes[i]);
        }
    }

    // Display available boats or the next available time
    if (availableBoats > 0) {
        cout << "Number of available boats: " << availableBoats << endl;
    } else {
        cout << "No boats available. Next available time: ";
        displayTime(nextAvailableTime, 0);
        cout << endl;
    }
}

// Task 3: Calculate the money taken for all the boats at the end of the day
void task3(double moneyTaken[], double totalHoursHired[]) {
    double totalMoney = 0.0;
    double totalHours = 0.0;
    int unusedBoats = 0;
    int mostUsedBoat = 0;

    // Calculate total money, total hours, unused boats, and most used boat
    for (int i = 0; i < NUM_BOATS; ++i) {
        totalMoney += moneyTaken[i];
        totalHours += totalHoursHired[i];

        if (totalHoursHired[i] == 0.0) {
            ++unusedBoats;
        }

        if (totalHoursHired[i] > totalHoursHired[mostUsedBoat]) {
            mostUsedBoat = i;
        }
    }

    // Display the end-of-day report
    cout << "Total money taken for all boats: $" << totalMoney << endl;
    cout << "Total hours boats were hired: " << totalHours << " hours" << endl;
    cout << "Number of boats not used: " << unusedBoats << endl;
    cout << "Boat used the most: Boat " << mostUsedBoat + 1 << " (" << totalHoursHired[mostUsedBoat] << " hours)" << endl;
}



