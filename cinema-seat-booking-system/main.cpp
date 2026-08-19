#include <iostream>
using namespace std;

// Constants for seat layout
const int ROWS = 5;
const int COLS = 7;

// 2D array to store seat booking status
// 0 = Available
// 1 = Booked
int seats[ROWS][COLS] = {0};


// --------------------------------------------------
// Function 1: View complete seat layout
// --------------------------------------------------
void viewSeats() {
    cout << "\n========== SEAT LAYOUT ==========\n";
    cout << "0 = Available | 1 = Booked\n\n";

    // Column numbers
    cout << "    ";
    for (int j = 0; j < COLS; j++) {
        cout << j << " ";
    }
    cout << "\n";

    for (int i = 0; i < ROWS; i++) {
        cout << i << " : ";

        for (int j = 0; j < COLS; j++) {
            cout << seats[i][j] << " ";
        }

        cout << "\n";
    }
}


// --------------------------------------------------
// Function 2: Book a single seat
// --------------------------------------------------
void bookSingleSeat() {
    int r, c;

    cout << "\nEnter row and column to book (0-based): ";
    cin >> r >> c;

    // Check whether row and column are valid
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        cout << "Invalid row or column.\n";
        return;
    }

    // Check whether seat is already booked
    if (seats[r][c] == 1) {
        cout << "Seat is already booked.\n";
        return;
    }

    // Book the seat
    seats[r][c] = 1;

    cout << "Seat (" << r << "," << c
         << ") booked successfully.\n";
}


// --------------------------------------------------
// Function 3: Book a block of adjacent seats
// --------------------------------------------------
void bookBlockSeats() {
    int row, startCol, count;

    cout << "\nEnter row: ";
    cin >> row;

    cout << "Enter starting column: ";
    cin >> startCol;

    cout << "Enter number of seats: ";
    cin >> count;

    // Validate row
    if (row < 0 || row >= ROWS) {
        cout << "Invalid row.\n";
        return;
    }

    // Validate count
    if (count <= 0) {
        cout << "Number of seats must be greater than 0.\n";
        return;
    }

    // Validate column range
    if (startCol < 0 || startCol >= COLS ||
        startCol + count > COLS) {
        cout << "Invalid seat range.\n";
        return;
    }

    // Check whether all seats are available
    for (int i = 0; i < count; i++) {
        if (seats[row][startCol + i] == 1) {
            cout << "Cannot book block.\n";
            cout << "Seat (" << row << ","
                 << startCol + i
                 << ") is already booked.\n";
            return;
        }
    }

    // Book all seats
    for (int i = 0; i < count; i++) {
        seats[row][startCol + i] = 1;
    }

    cout << "Block of " << count
         << " seats booked successfully.\n";
}


// --------------------------------------------------
// Function 4: Cancel a seat booking
// --------------------------------------------------
void cancelSeat() {
    int r, c;

    cout << "\nEnter row and column to cancel (0-based): ";
    cin >> r >> c;

    // Validate row and column
    if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
        cout << "Invalid row or column.\n";
        return;
    }

    // Check whether seat is booked
    if (seats[r][c] == 0) {
        cout << "This seat is not booked.\n";
        return;
    }

    // Cancel booking
    seats[r][c] = 0;

    cout << "Booking for seat (" << r << ","
         << c << ") cancelled successfully.\n";
}


// --------------------------------------------------
// Function 5: Display only available seats
// --------------------------------------------------
void displayAvailableSeats() {
    cout << "\n========== AVAILABLE SEATS ==========\n";

    bool found = false;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (seats[i][j] == 0) {
                cout << "Seat (" << i << "," << j
                     << ") is available\n";

                found = true;
            }
        }
    }

    if (!found) {
        cout << "No seats are available.\n";
    }
}


// --------------------------------------------------
// Function 6: Display only booked seats
// --------------------------------------------------
void displayBookedSeats() {
    cout << "\n========== BOOKED SEATS ==========\n";

    bool found = false;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (seats[i][j] == 1) {
                cout << "Seat (" << i << "," << j
                     << ") is booked\n";

                found = true;
            }
        }
    }

    if (!found) {
        cout << "No seats are booked.\n";
    }
}


// --------------------------------------------------
// Function 7: Count available seats
// --------------------------------------------------
int countAvailableSeats() {
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (seats[i][j] == 0) {
                count++;
            }
        }
    }

    return count;
}


// --------------------------------------------------
// Function 8: Count booked seats
// --------------------------------------------------
int countBookedSeats() {
    int count = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {

            if (seats[i][j] == 1) {
                count++;
            }
        }
    }

    return count;
}


// --------------------------------------------------
// Function 9: Display booking statistics
// --------------------------------------------------
void displayStatistics() {
    int totalSeats = ROWS * COLS;
    int booked = countBookedSeats();
    int available = countAvailableSeats();

    cout << "\n========== BOOKING STATISTICS ==========\n";

    cout << "Total Seats     : " << totalSeats << "\n";
    cout << "Booked Seats    : " << booked << "\n";
    cout << "Available Seats : " << available << "\n";
}


// --------------------------------------------------
// Main Function
// --------------------------------------------------
int main() {

    int choice;

    while (true) {

        cout << "\n";
        cout << "========================================\n";
        cout << "      CINEMA SEAT BOOKING SYSTEM\n";
        cout << "========================================\n";

        cout << "1. View Seat Layout\n";
        cout << "2. Book a Single Seat\n";
        cout << "3. Book a Block of Seats\n";
        cout << "4. Cancel a Seat Booking\n";
        cout << "5. Display Available Seats\n";
        cout << "6. Display Booked Seats\n";
        cout << "7. Display Booking Statistics\n";
        cout << "8. Exit\n";

        cout << "----------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice) {

            case 1:
                viewSeats();
                break;

            case 2:
                bookSingleSeat();
                break;

            case 3:
                bookBlockSeats();
                break;

            case 4:
                cancelSeat();
                break;

            case 5:
                displayAvailableSeats();
                break;

            case 6:
                displayBookedSeats();
                break;

            case 7:
                displayStatistics();
                break;

            case 8:
                cout << "\nExiting system...\n";
                cout << "Thank you for using Cinema Seat Booking System!\n";
                return 0;

            default:
                cout << "\nInvalid choice! Please enter 1 to 8.\n";
        }
    }

    return 0;
}