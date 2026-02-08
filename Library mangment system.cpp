#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

// ================= REGISTER page =================
void registerUser() {
    string email, password, role;

    cout << "\n=== Registration ===\n";
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;
    cout << "Enter Role (admin/user): ";
    cin >> role;

    ofstream file("users.txt", ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    file << email << " " << password << " " << role << "\n";
    file.close();

    cout << "Registration successful.\n";
}

// ================= LOGIN page =================
bool loginUser(string &role) {
    string email, password;

    cout << "\n=== Login ===\n";
    cout << "Enter Email: ";
    cin >> email;
    cout << "Enter Password: ";
    cin >> password;

    ifstream file("users.txt");
    if (!file) {
        cout << "No users found.\n";
        return false;
    }

    string fEmail, fPass, fRole;
    while (file >> fEmail >> fPass >> fRole) { // cut string into charchters compare
        if (email == fEmail && password == fPass) {
            role = fRole;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// ================= Book class node =================
class Book {
public:
    int id;
    string title;
    string author;
    Book* next;
    Book* prev;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        next = prev = nullptr;
    }
};

// ================= LIBRARY operations =================
class Library {
private:
    Book* head;
    Book* tail;

public:
    Library() {
        head = tail = nullptr;
    }

    bool isIdExist(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter ID: ";
        cin >> id;

        if (isIdExist(id)) {
            cout << "ID already exists.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        Book* newBook = new Book(id, title, author);

        if (!head) {
            head = tail = newBook;
        } else {
            tail->next = newBook;
            newBook->prev = tail;
            tail = newBook;
        }

        cout << "Book added successfully.\n";
    }

    void removeBook(int id) {
        if (head==nullptr) {
            cout << "Library is empty.\n";
            return;
        }

        Book* curr = head;
        while (curr && curr->id != id)
            curr = curr->next;

        if (curr==nullptr) {
            cout << "Book not found.\n";
            return;
        }

        if (curr == head && curr == tail) {
            head = tail = nullptr;
        } 
        else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        } 
        else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } 
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        delete curr;
        cout << "Book removed successfully.\n";
    }

    void searchById(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                displayBook(temp);
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void searchByTitle(string title) {
        Book* temp = head;
        while (temp) {
            if (temp->title == title) {
                displayBook(temp);
                return;
            }
            temp = temp->next;
        }
        cout << "Book not found.\n";
    }

    void displayBooks() {
        if (!head) {
            cout << "Library is empty.\n";
            return;
        }

        Book* temp = head;
        cout << "\n=== Library Books ===\n";
        while (temp) {
            displayBook(temp);
            cout << "------------------\n";
            temp = temp->next;
        }
    }

    bool borrow(int id)
    {
        Book *curr=head;
        while(curr)
        {
            if(curr->id!=id)
            {
            curr = curr->next;
            }
            else{
            return true;
            displayBooks();
            removeBook(id);
            }
        }
        return false;
    }

    void displayBook(Book* b) {
        cout << "ID: " << b->id << "\n";
        cout << "Title: " << b->title << "\n";
        cout << "Author: " << b->author << "\n";
    }
};

int main() {
    Library lib;
    string role;
    int choice;

    do {
        cout<<"===========MENU==========\n";
        cout << "1. Register\n2. Login\n0. Exit \n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
            registerUser();

        else if (choice == 2) {
            if (loginUser(role)) {
                cout << "Login successful (" << role << ")\n";

                if (role == "admin") {
                    int c;
                    do {
                        cout <<"====Menu of Admin===="<<" \n1.Add\n 2.Remove\n 3.SearchTitle\n 4.SearchID\n 5.Display\n 0.Logout\n";
                        cout<<"Enter your choice: ";
                        cin>>c;

                        if (c == 1) lib.addBook();
                        else if (c == 2) {
                            int id;
                            cout << "ID: ";
                            cin >> id;
                            lib.removeBook(id);
                        }
                        else if (c == 3) {
                            string t;
                            cin.ignore();
                            cout<<"Enter title of book to search it: ";
                            getline(cin, t);
                            lib.searchByTitle(t);
                        }
                        else if (c == 4) {
                            int id;
                            cout<<"Enter book id to search it: ";
                            cin >> id;
                            lib.searchById(id);
                        }
                        else if (c == 5)
                        cout<<"Book inside library is: ";
                            lib.displayBooks();

                    } while (c != 0);
                }

                else if (role == "user") {
                    int c;
                    do {
                        cout << "\n1.Display\n 2.Borrow\n 0.Logout\n";
                        cout<<"Enter your choice: ";
                        cin>>c;
                        if (c == 1){                           
                            cout<<"Book inside library now: ";
                            lib.displayBooks();}
                            else if(c==2)
                            {
                                int id;
                                cout<<"Enter book id: ";
                                cin>>id;
                                bool res=lib.borrow(id);
                                if(res==false)
                                {
                                    cout<<"Book cant borrow it not found :( \n";
                                }
                                else
                                cout<<"Book borrow successfuly :)\n";
                                //after borrow it i will remove it from data function borrow
                            }
                    } while (c != 0);
                }
            } else {
                cout << "Login failed.\n";
            }
        }

    } while (choice != 0);
                    cout<<"Thank You! \n";

    return 0;
}