#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

class Book {
public:
    string title;
    string author;
    string ISBN;
    bool isCheckedOut;

    Book(string t, string a, string isbn) {
        title = t;
        author = a;
        ISBN = isbn;
        isCheckedOut = false;
    }

    void displayBook() {
        cout << "Title: " << title << "\nAuthor: " << author << "\nISBN: " << ISBN;
        cout << "\nStatus: " << (isCheckedOut ? "Checked Out" : "Available") << endl;
    }
};

class Borrower {
public:
    string name;
    string borrowerID;

    Borrower(string n, string id) {
        name = n;
        borrowerID = id;
    }

    void displayBorrower() {
        cout << "Name: " << name << "\nBorrower ID: " << borrowerID << endl;
    }
};

class LibrarySystem {
private:
    vector<Book> books;
    vector<Borrower> borrowers;
    vector<pair<Book*, Borrower*>> transactions;

public:
    void addBook() {
        string title, author, ISBN;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Book Author: ";
        getline(cin, author);
        cout << "Enter ISBN: ";
        getline(cin, ISBN);
        books.push_back(Book(title, author, ISBN));
        cout << "Book added successfully!\n";
    }

    void searchBook() {
        string query;
        cout << "Enter title, author, or ISBN to search: ";
        cin.ignore();
        getline(cin, query);

        bool found = false;
        for (auto& book : books) {
            if (book.title == query || book.author == query || book.ISBN == query) {
                book.displayBook();
                found = true;
            }
        }
        if (!found) cout << "No matching books found.\n";
    }

    void checkoutBook() {
        string borrowerID;
        cout << "Enter Borrower ID: ";
        cin >> borrowerID;

        Borrower* borrower = nullptr;
        for (auto& b : borrowers) {
            if (b.borrowerID == borrowerID) {
                borrower = &b;
                break;
            }
        }

        if (!borrower) {
            cout << "Borrower not found. Please register first.\n";
            return;
        }

        string ISBN;
        cout << "Enter ISBN of the book to checkout: ";
        cin >> ISBN;

        Book* book = nullptr;
        for (auto& b : books) {
            if (b.ISBN == ISBN && !b.isCheckedOut) {
                book = &b;
                break;
            }
        }

        if (book) {
            book->isCheckedOut = true;
            transactions.push_back({book, borrower});
            cout << "Book checked out successfully.\n";
        } else {
            cout << "Book not available or does not exist.\n";
        }
    }

    void returnBook() {
        string borrowerID, ISBN;
        cout << "Enter Borrower ID: ";
        cin >> borrowerID;
        cout << "Enter ISBN of the book to return: ";
        cin >> ISBN;

        bool found = false;
        for (auto& transaction : transactions) {
            if (transaction.first->ISBN == ISBN && transaction.second->borrowerID == borrowerID) {
                transaction.first->isCheckedOut = false;
                transactions.erase(remove(transactions.begin(), transactions.end(), transaction), transactions.end());
                found = true;
                cout << "Book returned successfully.\n";
                break;
            }
        }

        if (!found) {
            cout << "No matching transaction found.\n";
        }
    }

    void calculateFine() {
        string ISBN;
        int overdueDays;
        cout << "Enter ISBN of the book: ";
        cin >> ISBN;
        cout << "Enter the number of overdue days: ";
        cin >> overdueDays;

        double fine = 0.5 * overdueDays; 
        cout << "Fine for book with ISBN " << ISBN << " is $" << fine << endl;
    }

    void registerBorrower() {
        string name, borrowerID;
        cout << "Enter Borrower Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Borrower ID: ";
        getline(cin, borrowerID);
        borrowers.push_back(Borrower(name, borrowerID));
        cout << "Borrower registered successfully!\n";
    }

    void displayMenu() {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Checkout Book\n";
        cout << "4. Return Book\n";
        cout << "5. Calculate Fine\n";
        cout << "6. Register Borrower\n";
        cout << "7. Exit\n";
    }
};

int main() {
    LibrarySystem library;
    int choice;

    while (true) {
        library.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.searchBook();
                break;
            case 3:
                library.checkoutBook();
                break;
            case 4:
                library.returnBook();
                break;
            case 5:
                library.calculateFine();
                break;
            case 6:
                library.registerBorrower();
                break;
            case 7:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
