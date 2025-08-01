#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

class Student {
    string name;
    string id;
    float marks[4];
    float average;
    char grade;

public:
    void inputDetails() {
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student ID: ";
        cin >> id;
        cout << "Enter marks for 4 subjects:\n";
        cout << "Electrical Circuit - II: ";
        cin >> marks[0];
        cout << "Lab: ";
        cin >> marks[1];
        cout << "BCP: ";
        cin >> marks[2];
        cout << "Electronic - I: ";
        cin >> marks[3];
        calculateGrade();
    }

    void calculateGrade() {
        average = (marks[0] + marks[1] + marks[2] + marks[3]) / 4;
        if (average >= 80)
            grade = 'A';
        else if (average >= 70)
            grade = 'B';
        else if (average >= 60)
            grade = 'C';
        else if (average >= 50)
            grade = 'D';
        else
            grade = 'F';
    }

    void saveToFile() {
        ofstream outFile("student.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "Name : " << name << "\n";
            outFile << "ID   : " << id << "\n";
            outFile << "Marks:\n";
            outFile << "  Electrical Circuit - II : " << marks[0] << "\n";
            outFile << "  Lab                     : " << marks[1] << "\n";
            outFile << "  BCP                     : " << marks[2] << "\n";
            outFile << "  Electronic - I          : " << marks[3] << "\n";
            outFile << "Average : " << average << "\n";
            outFile << "Grade   : " << grade << "\n";
            outFile << "-----------------------------\n";
            outFile.close();
        } else {
            cout << "Error opening file!\n";
        }
    }
};

class StudentAccount {
public:
    void viewAllStudents() {
        ifstream inFile("student.txt");
        string line;
        cout << "\n--- All Student Records ---\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    }

    void searchByID(string searchID) {
        ifstream inFile("student.txt");
        string line;
        bool found = false;
        bool printRecord = false;

        while (getline(inFile, line)) {
            if (line.find("ID   : " + searchID) != string::npos) {
                found = true;
                printRecord = true;
                cout << "\nStudent found:\n";
            }

            if (printRecord) {
                cout << line << endl;
                if (line.find("-----------------------------") != string::npos) {
                    printRecord = false;
                }
            }
        }

        inFile.close();

        if (!found)
            cout << "Student with ID " << searchID << " not found.\n";
    }
};

int main() {
    int choice;
    StudentAccount account;

    do {
        cout << "\n--- Student Grade Management System ---\n";
        cout << "1. Add student record\n";
        cout << "2. View all student records\n";
        cout << "3. Search student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            Student s;
            s.inputDetails();
            s.saveToFile();
            break;
        }
        case 2:
            account.viewAllStudents();
            break;
        case 3: {
            string id;
            cout << "Enter ID to search: ";
            cin >> id;
            account.searchByID(id);
            break;
        }
        case 4:
            cout << "Exiting... \n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
