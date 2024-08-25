#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

// Book class
class Book {
    string id;
    string title;
    bool issued;

public:
    Book(const string& id, const string& title)
        : id(id), title(title), issued(false) {}

    string getId() const { return id; }
    string getTitle() const { return title; }
    bool isIssued() const { return issued; }

    void issueBook() {
        if (issued) throw runtime_error("Book is already issued.");
        issued = true;
    }

    void returnBook() {
        if (!issued) throw runtime_error("Book was not issued.");
        issued = false;
    }
};

// Member class
class Member {
    string id;
    string name;

public:
    Member(const string& id, const string& name)
        : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
};

// Library class
class Library {
    vector<Book> books;
    vector<Member> members;

    void saveLibraryData() {
        ofstream file("library_data.txt");
        for (const auto& book : books) {
            file << book.getId() << " " << book.getTitle() << " " << book.isIssued() << endl;
        }
        file.close();
    }

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void removeBook(const string& bookId) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getId() == bookId) {
                books.erase(it);
                saveLibraryData();
                return;
            }
        }
        throw runtime_error("Book not found.");
    }

    void updateBook(const string& bookId, const string& newTitle) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                book = Book(bookId, newTitle);
                saveLibraryData();
                return;
            }
        }
        throw runtime_error("Book not found.");
    }

    void addMember(const Member& member) {
        members.push_back(member);
    }

    void issueBook(const string& bookId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                book.issueBook();
                saveLibraryData();
                return;
            }
        }
        throw runtime_error("Book not found.");
    }

    void returnBook(const string& bookId) {
        for (auto& book : books) {
            if (book.getId() == bookId) {
                book.returnBook();
                saveLibraryData();
                return;
            }
        }
        throw runtime_error("Book not found.");
    }
};

// Librarian class (optional)
class Librarian {
    string id;
    string name;

public:
    Librarian(const string& id, const string& name)
        : id(id), name(name) {}

    string getId() const { return id; }
    string getName() const { return name; }
};

// Loan class (optional)
class Loan {
    string bookId;
    string memberId;

public:
    Loan(const string& bookId, const string& memberId)
        : bookId(bookId), memberId(memberId) {}

    string getBookId() const { return bookId; }
    string getMemberId() const { return memberId; }
};

int main() {
    Library library;
    int choice;
    string bookId, bookTitle, memberId, memberName;

    do {
        cout << "\nLibrary Management System";
        cout << "\n1. Add Book";
        cout << "\n2. Remove Book";
        cout << "\n3. Update Book";
        cout << "\n4. Add Member";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nEnter Book ID: ";
                cin >> bookId;
                cout << "Enter Book Title: ";
                cin.ignore();  // to ignore the newline character after cin
                getline(cin, bookTitle);
                library.addBook(Book(bookId, bookTitle));
                cout << "Book added successfully." << endl;
                break;
            }
            case 2: {
                cout << "\nEnter Book ID to remove: ";
                cin >> bookId;
                try {
                    library.removeBook(bookId);
                    cout << "Book removed successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 3: {
                cout << "\nEnter Book ID to update: ";
                cin >> bookId;
                cout << "Enter new Book Title: ";
                cin.ignore();  // to ignore the newline character after cin
                getline(cin, bookTitle);
                try {
                    library.updateBook(bookId, bookTitle);
                    cout << "Book updated successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 4: {
                cout << "\nEnter Member ID: ";
                cin >> memberId;
                cout << "Enter Member Name: ";
                cin.ignore();  // to ignore the newline character after cin
                getline(cin, memberName);
                library.addMember(Member(memberId, memberName));
                cout << "Member added successfully." << endl;
                break;
            }
            case 5: {
                cout << "\nEnter Book ID to issue: ";
                cin >> bookId;
                try {
                    library.issueBook(bookId);
                    cout << "Book issued successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 6: {
                cout << "\nEnter Book ID to return: ";
                cin >> bookId;
                try {
                    library.returnBook(bookId);
                    cout << "Book returned successfully." << endl;
                } catch (const exception& e) {
                    cerr << e.what() << endl;
                }
                break;
            }
            case 7: {
                cout << "Exiting the system..." << endl;
                break;
            }
            default: {
                cout << "Invalid choice! Please choose again." << endl;
                break;
            }
        }
    } while (choice != 7);

    return 0;
}

