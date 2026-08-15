#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

// =====================================================
// Check whether file exists in vector
// =====================================================
bool fileExistsInVector(const vector<string>& files, const string& filename) {
    return find(files.begin(), files.end(), filename) != files.end();
}

// =====================================================
// Check whether file is empty
// =====================================================
bool isFileEmpty(const string& filename) {
    ifstream inFile(filename);

    if (!inFile) {
        return true;
    }

    return inFile.peek() == ifstream::traits_type::eof();
}

// =====================================================
// Create a new file
// =====================================================
void createFile(vector<string>& files) {

    string filename;

    cout << "\nEnter file name to create: ";
    cin >> filename;

    // Check if file already exists in our list
    if (fileExistsInVector(files, filename)) {
        cout << "File already exists!\n";
        return;
    }

    // Create file
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Error creating file!\n";
        return;
    }

    outFile.close();

    // Add file name to vector
    files.push_back(filename);

    cout << "File created successfully!\n";
}

// =====================================================
// Write data into file
// =====================================================
void writeFile(const vector<string>& files) {

    string filename;

    cout << "\nEnter file name to write into: ";
    cin >> filename;

    // Check file
    if (!fileExistsInVector(files, filename)) {
        cout << "File not found!\n";
        return;
    }

    // Open file in append mode
    ofstream outFile(filename, ios::app);

    if (!outFile) {
        cout << "Error opening file!\n";
        return;
    }

    string data;

    cout << "Enter data to write: ";

    cin.ignore();
    getline(cin, data);

    // Write data
    outFile << data << "\n";

    outFile.close();

    cout << "Data written successfully!\n";
}

// =====================================================
// Read data from file
// =====================================================
void readFile(const vector<string>& files) {

    string filename;

    cout << "\nEnter file name to read: ";
    cin >> filename;

    // Check file
    if (!fileExistsInVector(files, filename)) {
        cout << "File not found!\n";
        return;
    }

    // Check empty
    if (isFileEmpty(filename)) {
        cout << "File is empty.\n";
        return;
    }

    // Open file
    ifstream inFile(filename);

    if (!inFile) {
        cout << "Error opening file!\n";
        return;
    }

    string line;

    cout << "\n====================================\n";
    cout << "           FILE CONTENTS\n";
    cout << "====================================\n";

    // Read line by line
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    cout << "====================================\n";

    inFile.close();
}

// =====================================================
// Copy contents of one file to another
// =====================================================
void copyFile(const vector<string>& files) {

    string source;
    string destination;

    cout << "\nEnter source file name: ";
    cin >> source;

    cout << "Enter destination file name: ";
    cin >> destination;

    // Check source
    if (!fileExistsInVector(files, source)) {
        cout << "Source file not found!\n";
        return;
    }

    // Check destination
    if (!fileExistsInVector(files, destination)) {
        cout << "Destination file not found!\n";
        return;
    }

    // Prevent copying file into itself
    if (source == destination) {
        cout << "Source and destination cannot be the same!\n";
        return;
    }

    ifstream inFile(source);

    // Open destination in overwrite mode
    ofstream outFile(destination);

    if (!inFile || !outFile) {
        cout << "Error opening files!\n";
        return;
    }

    string line;

    // Copy content
    while (getline(inFile, line)) {
        outFile << line << "\n";
    }

    inFile.close();
    outFile.close();

    cout << "File copied successfully!\n";
}

// =====================================================
// Delete a file
// =====================================================
void deleteFile(vector<string>& files) {

    string filename;

    cout << "\nEnter file name to delete: ";
    cin >> filename;

    // Find file in vector
    auto it = find(files.begin(), files.end(), filename);

    if (it == files.end()) {
        cout << "File not found!\n";
        return;
    }

    // Delete actual file
    if (remove(filename.c_str()) != 0) {
        cout << "Error deleting file!\n";
        return;
    }

    // Remove from vector
    files.erase(it);

    cout << "File deleted successfully!\n";
}

// =====================================================
// List all files
// =====================================================
void listFiles(const vector<string>& files) {

    if (files.empty()) {
        cout << "\nNo files created yet.\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "            FILE LIST\n";
    cout << "====================================\n";

    for (int i = 0; i < files.size(); i++) {
        cout << i + 1 << ". " << files[i] << "\n";
    }

    cout << "====================================\n";
}

// =====================================================
// Delete all files
// =====================================================
void cleanupFiles(vector<string>& files) {

    for (const auto& file : files) {
        remove(file.c_str());
    }

    files.clear();
}

// =====================================================
// Main Function
// =====================================================
int main() {

    vector<string> files;

    int choice;

    while (true) {

        cout << "\n\n";
        cout << "============================================\n";
        cout << "        FILE MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Create File\n";
        cout << "2. Write to File\n";
        cout << "3. Read from File\n";
        cout << "4. Copy File\n";
        cout << "5. Delete File\n";
        cout << "6. List Files\n";
        cout << "7. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            // Create file
            case 1:
                createFile(files);
                break;

            // Write file
            case 2:
                writeFile(files);
                break;

            // Read file
            case 3:
                readFile(files);
                break;

            // Copy file
            case 4:
                copyFile(files);
                break;

            // Delete file
            case 5:
                deleteFile(files);
                break;

            // List files
            case 6:
                listFiles(files);
                break;

            // Exit
            case 7:

                cout << "\nExiting program...\n";

                cleanupFiles(files);

                cout << "All files deleted.\n";
                cout << "Thank you!\n";

                return 0;

            // Invalid choice
            default:
                cout << "\nInvalid choice! Please enter 1-7.\n";
        }
    }

    return 0;
}