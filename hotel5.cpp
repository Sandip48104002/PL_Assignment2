#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

int room_no;
char name[30];
char address[50];
char phone[15];
long days;
long cost;

class HOTEL {
private:
    char rtype[30];
    long pay;

public:
    void main_menu();
    void cancel();
    void rooms();
    void edit();
    int check(int);
} h;

class ROOM {
private:
    char rtype[30];

public:
    void display();
    void delete_rec();
} z;

class CUSTOMER {
private:
    int r;
    int flag = 0;
    char rtype[30];

public:
    void add();
    int check(int);
} y;

void HOTEL::main_menu() {
    int choice = 0;
    while (choice != 6) {
        cout << "\n\t\t\t\t *************";
        cout << "\n\t\t\t\t **HOTEL IIT**";
        cout << "\n\t\t\t\t *************";
        cout << "\n\t\t\t\t * MAIN MENU *";
        cout << "\n\t\t\t\t *************";
        cout << "\n\n\n\t\t\t\t1. Book A Room";
        cout << "\n\t\t\t\t2. Customer Information";
        cout << "\n\t\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t\t4. Check out";
        cout << "\n\t\t\t\t5. Cancel booking";
        cout << "\n\t\t\t\t6. Exit";
        cout << "\n\n\t\t\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                y.add();
                break;
            case 2:
                z.display();
                break;
            case 3:
                rooms();
                break;
            case 4:
                edit();
                break;
            case 5:
                cancel();
                break;
            case 6:
                cout << "Exiting the system." << endl;
                return;
            default:
                cout << "\n\n\t\t\tWrong choice. Please try again.";
                break;
        }
    }
}

void CUSTOMER::add() {
    int r, flag;
    ofstream fout("Record.txt", ios::app | ios::binary);
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\t\t\t | Rooms  |   Room Type  |";
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\t\t\t |   1-50 |Single Non AC |";
    cout << "\n\t\t\t |  51-80 |  Single AC   |";
    cout << "\n\t\t\t | 81-100 | Double Non AC|";
    cout << "\n\t\t\t | 101-150 | Double AC   |";
    cout << "\n\t\t\t +-----------------------+";
    cout << "\n\n ENTER CUSTOMER DETAILS";
    cout << "\n ----------------------";
    cout << "\n\n Room Number: ";
    cin >> r;
    flag = check(r);

    if (flag == 1)
        cout << "\n Sorry, Room is already booked.\n";
    else if (flag == 2)
        cout << "\n Sorry, Room does not exist.\n";
    else {
        room_no = r;
        cout << " Name: ";
        cin.ignore();
        cin.getline(name, 30);
        cout << " Address: ";
        cin.getline(address, 50);
        cout << " Phone Number: ";
        cin.getline(phone, 15);
        cout << " Number of Days: ";
        cin >> days;

        if (room_no >= 1 && room_no <= 50) {
            strcpy(rtype, "Single non AC");
            cost = days * 1000;
        } else if (room_no >= 51 && room_no <= 80) {
            strcpy(rtype, "Single AC");
            cost = days * 1500;
        } else if (room_no >= 81 && room_no <= 100) {
            strcpy(rtype, "Double non AC");
            cost = days * 2000;
        } else if (room_no >= 101 && room_no <= 150) {
            strcpy(rtype, "Double AC");
            cost = days * 2500;
        } else {
            cout << "Invalid room number.\n";
            return;
        }

        fout.write((char*)this, sizeof(HOTEL));
        cout << "\n Room has been booked.";
    }

    fout.close();
}

void ROOM::display() {
    ifstream fin("Record.txt", ios::in | ios::binary);
    int r, flag = 0;
    cout << "\n Enter Room Number: ";
    cin >> r;

    while (fin.read((char*)this, sizeof(HOTEL))) {
        if (room_no == r) {
            cout << "\n Customer Details";
            cout << "\n ----------------";
            cout << "\n\n Room Number: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone Number: " << phone;
            cout << "\n Staying for " << days << " days.";
            cout << "\n Room Type: " << rtype;
            cout << "\n Total cost of stay: " << cost;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
        cout << "\n Room is Vacant.";

    fin.close();
}

void HOTEL::rooms() {
    const char separator = ' ';
    const int NoWidth = 8;
    const int GuestWidth = 17;
    const int AddressWidth = 16;
    const int RoomWidth = 13;
    const int ContactNoWidth = 13;

    ifstream fin("Record.txt", ios::in | ios::binary);
    cout << "\n\t\t\t    LIST OF ROOMS ALLOTED";
    cout << "\n\t\t\t   -----------------------";
    cout << "\n\n +---------+------------------+-----------------+--------------+--------------+";
    cout << "\n | Room No.|    Guest Name    |      Address    |   Room Type  |  Contact No. |";
    cout << "\n +---------+------------------+-----------------+--------------+--------------+";

    while (fin.read((char*)this, sizeof(HOTEL))) {
        cout << "\n |" << setw(NoWidth) << setfill(separator) << room_no << " |";
        cout << setw(GuestWidth) << setfill(separator) << name << " |";
        cout << setw(AddressWidth) << setfill(separator) << address << " |";
        cout << setw(RoomWidth) << setfill(separator) << rtype << " |";
        cout << setw(ContactNoWidth) << setfill(separator) << phone << " |";
    }
    cout << "\n +---------+------------------+-----------------+--------------+--------------+";
    cout << "\n\n\n\t\t\tPress any key to continue.";
    cin.ignore();
    cin.get();
    fin.close();
}

void HOTEL::edit() {
    z.delete_rec();
    cout << "\n Press any key to continue.";
    cin.ignore();
    cin.get();
}

int CUSTOMER::check(int r) {
    int flag = 0;
    ifstream fin("Record.txt", ios::in | ios::binary);
    while (fin.read((char*)this, sizeof(HOTEL))) {
        if (room_no == r) {
            flag = 1;
            break;
        } else if (r > 150) {
            flag = 2;
            break;
        }
    }
    fin.close();
    return flag;
}

void ROOM::delete_rec() {
    int r, flag = 0;
    char ch;
    cout << "\n Enter Room Number: ";
    cin >> r;

    ifstream fin("Record.txt", ios::in | ios::binary);
    ofstream fout("temp.txt", ios::out | ios::binary);

    while (fin.read((char*)this, sizeof(HOTEL))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone Number: " << phone;
            cout << "\n Room Type: " << rtype;
            cout << "\n Your total bill is: Rs. " << cost;
            cout << "\n\n Do you want to check out this customer (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char*)this, sizeof(HOTEL));
            else
                cout << "\n Customer Checked Out.";
            flag = 1;
        } else {
            fout.write((char*)this, sizeof(HOTEL));
        }
    }
    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Sorry, Room is Vacant.";
    else {
        remove("Record.txt");
        rename("temp.txt", "Record.txt");
    }

    cin.ignore();
    cin.get();
}

void HOTEL::cancel() {
    int r, flag = 0;
    char ch;
    cout << "\n Enter Room Number: ";
    cin >> r;

    ifstream fin("Record.txt", ios::in | ios::binary);
    ofstream fout("temp.txt", ios::out | ios::binary);

    while (fin.read((char*)this, sizeof(HOTEL))) {
        if (room_no == r) {
            cout << "\n\n Do you want to cancel the booking (y/n): ";
            cin >> ch;
            if (ch == 'n')
                fout.write((char*)this, sizeof(HOTEL));
            else
                cout << "\n Booking Cancelled.";
            flag = 1;
        } else {
            fout.write((char*)this, sizeof(HOTEL));
        }
    }
    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Enter Valid room number.";
    else {
        remove("Record.txt");
        rename("temp.txt", "Record.txt");
    }

    cin.ignore();
    cin.get();
}

int main() {
    h.main_menu();
    return 0;
}
