#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Item class
class Item {
public:
    int id;
    string name;
    int quantity;
    float price;

    // Constructor
    Item(int id, const string& name, int quantity, float price) {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
    }

    // Display item details
    void display() const {
        cout << left
             << setw(5) << id
             << setw(20) << name
             << setw(10) << quantity
             << "Rs. " << fixed << setprecision(2) << price
             << endl;
    }
};


// Inventory class
class Inventory {
private:
    vector<Item> items;
    int nextId = 1;

public:

    // Add new item
    void addItem(const string& name, int quantity, float price) {
        Item newItem(nextId, name, quantity, price);
        items.push_back(newItem);
        nextId++;

        cout << "Item added successfully!\n";
    }

    // Remove item by name
    void removeItemByName(const string& name) {

        for (auto it = items.begin(); it != items.end(); ++it) {

            if (it->name == name) {
                items.erase(it);

                cout << "Item removed successfully!\n";
                return;
            }
        }

        cout << "Item not found!\n";
    }

    // Search item by name
    void searchItemByName(const string& name) const {

        for (const Item& item : items) {

            if (item.name == name) {
                cout << "\nItem Found:\n";

                cout << left
                     << setw(5) << "ID"
                     << setw(20) << "Name"
                     << setw(10) << "Quantity"
                     << "Price\n";

                cout << "---------------------------------------------\n";

                item.display();
                return;
            }
        }

        cout << "Item not found!\n";
    }

    // Display complete inventory
    void displayInventory() const {

        if (items.empty()) {
            cout << "\nInventory is empty!\n";
            return;
        }

        cout << "\n--------------- Inventory ---------------\n";

        cout << left
             << setw(5) << "ID"
             << setw(20) << "Name"
             << setw(10) << "Quantity"
             << "Price\n";

        cout << "---------------------------------------------\n";

        for (const Item& item : items) {
            item.display();
        }

        cout << "---------------------------------------------\n";
    }
};


// Menu function
void showMenu() {

    cout << "\n--- Inventory System ---\n"
         << "1. Add Item\n"
         << "2. Remove Item\n"
         << "3. Search Item\n"
         << "4. Display Inventory\n"
         << "5. Exit\n"
         << "Enter your choice: ";
}


// Main function
int main() {

    Inventory inventory;

    int choice;

    do {

        showMenu();

        cin >> choice;
        cin.ignore();

        string name;
        int quantity;
        float price;

        switch (choice) {

            case 1:

                cout << "Enter item name: ";
                getline(cin, name);

                cout << "Enter quantity: ";
                cin >> quantity;

                cout << "Enter price: ";
                cin >> price;

                cin.ignore();

                inventory.addItem(name, quantity, price);

                break;


            case 2:

                cout << "Enter item name to remove: ";
                getline(cin, name);

                inventory.removeItemByName(name);

                break;


            case 3:

                cout << "Enter item name to search: ";
                getline(cin, name);

                inventory.searchItemByName(name);

                break;


            case 4:

                inventory.displayInventory();

                break;


            case 5:

                cout << "Exiting program.\n";

                break;


            default:

                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);


    return 0;
}