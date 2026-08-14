#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ============================================================
// Book Class
// ============================================================

class Book {
private:
    string title;
    string author;
    string isbn;
    int copies;

public:

    // Constructor
    Book(string t, string a, string i, int c)
        : title(t), author(a), isbn(i), copies(c) {}

    // Getter methods
    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    string getISBN() const {
        return isbn;
    }

    int getCopies() const {
        return copies;
    }

    // Setter methods
    void setTitle(string t) {
        title = t;
    }

    void setAuthor(string a) {
        author = a;
    }

    void setCopies(int c) {
        copies = c;
    }

    // Display book details
    void display() const {
        cout << left
             << setw(25) << title
             << setw(20) << author
             << setw(15) << isbn
             << setw(10) << copies
             << "\n";
    }
};


// ============================================================
// Library Class
// ============================================================

class Library {

private:
    vector<Book> books;

public:

    // --------------------------------------------------------
    // Add Book
    // If ISBN already exists, update book details
    // --------------------------------------------------------

    void addBook(const Book& book) {

        auto it = find_if(
            books.begin(),
            books.end(),
            [&](const Book& b) {
                return b.getISBN() == book.getISBN();
            }
        );

        if (it != books.end()) {

            cout << "\nBook with same ISBN already exists.\n";
            cout << "Updating book details...\n";

            it->setTitle(book.getTitle());
            it->setAuthor(book.getAuthor());
            it->setCopies(book.getCopies());

            cout << "Book updated successfully.\n";

        } else {

            books.push_back(book);

            cout << "\nBook added successfully.\n";
        }
    }


    // --------------------------------------------------------
    // Remove Book by ISBN
    // --------------------------------------------------------

    void removeBook(const string& isbn) {

        auto it = remove_if(
            books.begin(),
            books.end(),
            [&](const Book& b) {
                return b.getISBN() == isbn;
            }
        );

        if (it != books.end()) {

            books.erase(it, books.end());

            cout << "\nBook removed successfully.\n";

        } else {

            cout << "\nNo book found with that ISBN.\n";
        }
    }


    // --------------------------------------------------------
    // Search Book by Title
    // --------------------------------------------------------

    void searchByTitle(const string& title) {

        bool found = false;

        for (const auto& b : books) {

            if (b.getTitle() == title) {

                if (!found) {

                    cout << "\n";
                    cout << left
                         << setw(25) << "Title"
                         << setw(20) << "Author"
                         << setw(15) << "ISBN"
                         << setw(10) << "Copies"
                         << "\n";

                    cout << string(70, '-') << "\n";
                }

                b.display();
                found = true;
            }
        }

        if (!found) {
            cout << "\nNo book found with that title.\n";
        }
    }


    // --------------------------------------------------------
    // Search Book by ISBN
    // --------------------------------------------------------

    void searchByISBN(const string& isbn) {

        auto it = find_if(
            books.begin(),
            books.end(),
            [&](const Book& b) {
                return b.getISBN() == isbn;
            }
        );

        if (it != books.end()) {

            cout << "\n";
            cout << left
                 << setw(25) << "Title"
                 << setw(20) << "Author"
                 << setw(15) << "ISBN"
                 << setw(10) << "Copies"
                 << "\n";

            cout << string(70, '-') << "\n";

            it->display();

        } else {

            cout << "\nNo book found with that ISBN.\n";
        }
    }


    // --------------------------------------------------------
    // Display All Books
    // Sorted by Title
    // --------------------------------------------------------

    void displayBooks() {

        if (books.empty()) {

            cout << "\nLibrary is empty.\n";
            return;
        }

        // Sort books alphabetically by title
        sort(
            books.begin(),
            books.end(),
            [](const Book& a, const Book& b) {
                return a.getTitle() < b.getTitle();
            }
        );

        cout << "\n";
        cout << left
             << setw(25) << "Title"
             << setw(20) << "Author"
             << setw(15) << "ISBN"
             << setw(10) << "Copies"
             << "\n";

        cout << string(70, '-') << "\n";

        for (const auto& b : books) {
            b.display();
        }
    }
};


// ============================================================
// Main Function
// ============================================================

int main() {

    Library lib;

    int choice;

    do {

        cout << "\n";
        cout << "============================================\n";
        cout << "       MINI LIBRARY MANAGEMENT SYSTEM       \n";
        cout << "============================================\n";

        cout << "1. Add Book\n";
        cout << "2. Remove Book by ISBN\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by ISBN\n";
        cout << "5. Display All Books\n";
        cout << "6. Exit\n";

        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";

        cin >> choice;
        cin.ignore();

        string title;
        string author;
        string isbn;
        int copies;

        switch (choice) {

        // ----------------------------------------------------
        // ADD BOOK
        // ----------------------------------------------------

        case 1:

            cout << "\nEnter Title: ";
            getline(cin, title);

            cout << "Enter Author: ";
            getline(cin, author);

            cout << "Enter ISBN: ";
            getline(cin, isbn);

            cout << "Enter Number of Copies: ";
            cin >> copies;

            lib.addBook(
                Book(title, author, isbn, copies)
            );

            break;


        // ----------------------------------------------------
        // REMOVE BOOK
        // ----------------------------------------------------

        case 2:

            cout << "\nEnter ISBN to remove: ";
            getline(cin, isbn);

            lib.removeBook(isbn);

            break;


        // ----------------------------------------------------
        // SEARCH BY TITLE
        // ----------------------------------------------------

        case 3:

            cout << "\nEnter Title to search: ";
            getline(cin, title);

            lib.searchByTitle(title);

            break;


        // ----------------------------------------------------
        // SEARCH BY ISBN
        // ----------------------------------------------------

        case 4:

            cout << "\nEnter ISBN to search: ";
            getline(cin, isbn);

            lib.searchByISBN(isbn);

            break;


        // ----------------------------------------------------
        // DISPLAY ALL BOOKS
        // ----------------------------------------------------

        case 5:

            lib.displayBooks();

            break;


        // ----------------------------------------------------
        // EXIT
        // ----------------------------------------------------

        case 6:

            cout << "\nExiting the program...\n";
            cout << "Thank you!\n";

            break;


        // ----------------------------------------------------
        // INVALID CHOICE
        // ----------------------------------------------------

        default:

            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 6);


    return 0;
}