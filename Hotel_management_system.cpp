#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

class MenuItem {
public:
    string name;
    float price;

    MenuItem(const string& name, float price) : name(name), price(price) {}
};

class Menu {
private:
    vector<MenuItem> items;

public:
    Menu() {
        // Initialize with some default items
        items.push_back(MenuItem("Breakfast", 150.0));
        items.push_back(MenuItem("Lunch", 250.0));
        items.push_back(MenuItem("Dinner", 300.0));
        items.push_back(MenuItem("Snacks", 100.0));
    }

    void display() const {
        cout << "\n\t\t\t* Menu *";
        cout << "\n----------------------";
        for (const auto& item : items) {
            cout << "\n" << item.name << " - " << item.price << " NRS";
        }
        cout << "\n----------------------";
    }

    void update_price(const string& item_name, float new_price) {
        for (auto& item : items) {
            if (item.name == item_name) {
                item.price = new_price;
                cout << "\nPrice updated for " << item_name;
                return;
            }
        }
        cout << "\nItem not found.";
    }
};

class Hotel {
private:
    int room_no;
    string name;
    string address;
    string phone;
    string citizenship_number;
    int days;
    float fare;
    string bed_type;

    static vector<Hotel> records;
    static int room_count;
    static const int total_rooms = 10;
    static vector<int> all_rooms;
    static const float single_bed_rate;
    static const float double_bed_rate;

    static bool authenticate();
    static bool is_valid_room_number(int r);
    static int get_single_bed_count();
    static int get_double_bed_count();

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    void modify(int);
    void delete_rec(int);
    void search_by_name();
    static bool check(int);
    static void display_room_count();
    static void display_vacant_rooms();
    static void display_total_rooms();
    static void display_available_beds();
    static void display_bed_rates();
    static void display_menu();
    static void update_menu_price();
    static void save_records();
    static void load_records();
};

vector<Hotel> Hotel::records;
int Hotel::room_count = 0;
vector<int> Hotel::all_rooms = {101, 102, 103, 104, 105, 106, 107, 108, 109, 110};
const float Hotel::single_bed_rate = 800;
const float Hotel::double_bed_rate = 1200;

void clear_screen() {
    cout << "\033[2J\033[1;1H";
}

void pause() {
    cout << endl;
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}

void intro() {
    cout << "\n\n\t            ";
    cout << "     C++ Project On Hotel Management System";
    cout << "\n\n\t\t\t\t     MADE BY";
    cout << "\n//////////////////////////////////////////////////////////////////";
    cout << "\n/////////////////////////////////////////////////////////////////";
    cout << "\n||\t\t\t\t\t\t\t\t\t                ||";
    cout << "\n||\t\t\t\t\t\t\t\t\t                ||";
    cout << "\n||\t\t\t\t4R GROUP OF HOTEL\t\t\t                ||";
    cout << "\n||\t\t\t\t\t\t\t\t\t                ||";
    cout << "\n||\t\t\t\t\t  \t\t\t\t                ||";
    cout << "\n*";
    cout << "\n*";
}

void head() {
    clear_screen();
    cout << "///////////////////////////////////////////////////////////";
    cout << "\n////////////////////////////////////////////////////////////";
    cout << "\n\t\t\t\t\t\t\t\t\t       ";
    cout << "\n\t\t\t\t   4R Group of Hotels\t\t\t       ";
    cout << "\n\t\t\t\t\t\t\t\t\t       ";
    cout << "\n//////////////////////////////////////////////////////////";
    cout << "\n///////////////////////////////////////////////////////////";
}
void time_sync() {
    int i = 0;
    cout << "    \n\n\n    Connecting to Server\n    Syncing Data";
    while (i < 10) {
        for (long long j = 0; j < 99999999; ++j) {}
        cout << ".";
        ++i;
    }
    cout << "\n";
}

bool Hotel::authenticate() {
    string username, password;
    const string correct_username = "admin";
    const string correct_password = "******";
    int attempts=3;

while (attempts > 0) {
        clear_screen();
        intro();
        cout << "Login Page\n";
        cout << "----------------\n";
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        if (username == correct_username && password == correct_password) {
            return true;  // Authentication successful
        } else {
            attempts--;
            if (attempts > 0) {
                cout << "\nInvalid username or password. Please try again. Remaining attempts: " << attempts;
            } else {
                cout << "\nNo more attempts left. Exiting...";
                return false;  // No more attempts left
            }
            pause();  // Wait for user input before retrying
        }
    }

    return false;  // Should never reach here
}
bool Hotel::is_valid_room_number(int r) {
    return (r >= 101 && r <= 110);
}

int Hotel::get_single_bed_count() {
    int count = 0;
    for (const auto& record : records) {
        if (record.bed_type == "Single") {
            count++;
        }
    }
    return total_rooms - count; // Total rooms minus allocated single beds
}

int Hotel::get_double_bed_count() {
    int count = 0;
    for (const auto& record : records) {
        if (record.bed_type == "Double") {
            count++;
        }
    }
    return total_rooms - count; // Total rooms minus allocated double beds
}

void Hotel::main_menu() {
    if (!authenticate()) {
        cout << "Invalid username or password. Exiting...\n";
        return;
    }

    int choice = 0;
    while (choice != 13) { // Updated choice limit to include new options
        clear_screen();
        head();
        cout << "\n\t\t\t\t*";
        cout << "\n\t\t\t\t* MAIN MENU *";
        cout << "\n\t\t\t\t*";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Record";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Search by Name";
        cout << "\n\t\t\t6. Display Number of Rooms Allotted";
        cout << "\n\t\t\t7. Display Number of Vacant Rooms";
        cout << "\n\t\t\t8. Display Total Number of Rooms";
        cout << "\n\t\t\t9. Display Available Beds";
        cout << "\n\t\t\t10. Display Bed Rates";
        cout << "\n\t\t\t11. Display Menu";
        cout << "\n\t\t\t12. Update Menu Price";
        cout << "\n\t\t\t13. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: search_by_name(); break;
            case 6: display_room_count(); break;
            case 7: display_vacant_rooms(); break;
            case 8: display_total_rooms(); break;
            case 9: display_available_beds(); break;
            case 10: display_bed_rates(); break;
            case 11: display_menu(); break;
            case 12: update_menu_price(); break;
            case 13: save_records(); break; // Save records before exiting
            default:
                cout << "\n\n\t\t\tWrong choice.....!!!";
                pause();
        }
    }
}

void Hotel::add() {
    clear_screen();
    head();
    int r;

    if (records.size() >= total_rooms) {
        cout << "\nSorry, the system can only handle up to " << total_rooms << " records.";
        pause();
        return;
    }

    cout << "\n Enter Customer Details";
    cout << "\n ----------------------";
    cout << "\n\n Room no: ";
    cin >> r;

    if (!is_valid_room_number(r)) {
        cout << "\n Invalid room number. Please enter a number between 101 and 110.";
        pause();
        return;
    }

    if (check(r)) {
        cout << "\n Sorry..!!! Room is already booked";
    } else {
        Hotel new_record;
        new_record.room_no = r;
        cout << " Name: ";
        cin.ignore();
        getline(cin, new_record.name);
        cout << " Address: ";
        getline(cin, new_record.address);
        cout << " Phone No: ";
        getline(cin, new_record.phone);
        cout << " Citizenship Number: ";
        getline(cin, new_record.citizenship_number);
        cout << " Number of Days to Stay: ";
        cin >> new_record.days;
        cout << " Bed Type (Single/Double): ";
        cin.ignore();
        getline(cin, new_record.bed_type);

        if (new_record.bed_type == "Single") {
            new_record.fare = new_record.days * single_bed_rate;
        } else if (new_record.bed_type == "Double") {
            new_record.fare = new_record.days * double_bed_rate;
        } else {
            cout << "Invalid bed type. Defaulting to Single Bed rate.";
            new_record.fare = new_record.days * single_bed_rate;
        }

        records.push_back(new_record);
        save_records(); // Save changes to the file
        cout << "\n Room booked successfully.";
    }

    pause();
}

void Hotel::display() {
    clear_screen();
    head();
    cout << "\n Enter Room No: ";
    int room_no;
    cin >> room_no;

    auto it = find_if(records.begin(), records.end(), [room_no](const Hotel& record) {
        return record.room_no == room_no;
    });

    if (it != records.end()) {
        const Hotel& record = *it;
        cout << "\n Customer Details";
        cout << "\n ----------------";
        cout << "\n Room No: " << record.room_no;
        cout << "\n Name: " << record.name;
        cout << "\n Address: " << record.address;
        cout << "\n Phone No: " << record.phone;
        cout << "\n Citizenship Number: " << record.citizenship_number;
        cout << "\n Number of Days: " << record.days;
        cout << "\n Bed Type: " << record.bed_type;
        cout << "\n Fare: " << record.fare;
    } else {
        cout << "\n Record not found.";
    }

    pause();
}

void Hotel::rooms() {
    clear_screen();
    head();
    cout << "\n Room No";
    cout << "\n --------";
    for (const auto& record : records) {
        cout << "\n " << record.room_no;
    }
    pause();
}

void Hotel::edit() {
    clear_screen();
    head();
    cout << "\n Enter Room No to edit: ";
    int room_no;
    cin >> room_no;

    auto it = find_if(records.begin(), records.end(), [room_no](const Hotel& record) {
        return record.room_no == room_no;
    });

    if (it != records.end()) {
        modify(room_no);
        save_records(); // Save changes to the file after modification
    } else {
        cout << "\n Record not found.";
        pause();
    }
}

void Hotel::modify(int room_no) {
    clear_screen();
    head();

    auto it = find_if(records.begin(), records.end(), [room_no](const Hotel& record) {
        return record.room_no == room_no;
    });

    if (it != records.end()) {
        Hotel& record = *it;
        int choice;
        cout << "\n Modify Record";
        cout << "\n -------------";
        cout << "\n 1. Update Address";
        cout << "\n 2. Update Phone";
        cout << "\n 3. Update Citizenship Number";
        cout << "\n 4. Update Number of Days";
        cout << "\n 5. Update Bed Type";
        cout << "\n 6. Delete Record";
        cout << "\n 7. Exit";
        cout << "\n\n Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << " Enter new address: ";
                cin.ignore();
                getline(cin, record.address);
                cout << "\n Address updated.";
                break;
            }
            case 2: {
                cout << " Enter new phone number: ";
                cin.ignore();
                getline(cin, record.phone);
                cout << "\n Phone number updated.";
                break;
            }
            case 3: {
                cout << " Enter new citizenship number: ";
                cin.ignore();
                getline(cin, record.citizenship_number);
                cout << "\n Citizenship number updated.";
                break;
            }
            case 4: {
                cout << " Enter new number of days: ";
                cin >> record.days;
                if (record.bed_type == "Single") {
                    record.fare = record.days * single_bed_rate;
                } else if (record.bed_type == "Double") {
                    record.fare = record.days * double_bed_rate;
                }
                cout << "\n Number of days updated.";
                break;
            }
            case 5: {
                cout << " Enter new bed type (Single/Double): ";
                cin.ignore();
                getline(cin, record.bed_type);
                if (record.bed_type == "Single") {
                    record.fare = record.days * single_bed_rate;
                } else if (record.bed_type == "Double") {
                    record.fare = record.days * double_bed_rate;
                } else {
                    cout << "Invalid bed type. Defaulting to Single Bed rate.";
                    record.bed_type = "Single";
                    record.fare = record.days * single_bed_rate;
                }
                cout << "\n Bed type updated.";
                break;
            }
            case 6:
                delete_rec(room_no);
                break;
            case 7:
                return;
            default:
                cout << "\n Invalid choice.";
        }
    } else {
        cout << "\n Record not found.";
    }

    pause();
}

void Hotel::delete_rec(int room_no) {
    auto it = remove_if(records.begin(), records.end(), [room_no](const Hotel& record) {
        return record.room_no == room_no;
    });

    if (it != records.end()) {
        records.erase(it, records.end());
        save_records(); // Save changes to the file
        cout << "\n Record deleted.";
    } else {
        cout << "\n Record not found.";
    }
    pause();
}

void Hotel::search_by_name() {
    clear_screen();
    head();
    cout << "\n Enter name to search: ";
    string search_name;
    cin.ignore();
    getline(cin, search_name);

    bool found = false;
    for (const auto& record : records) {
        if (record.name == search_name) {
            cout << "\n Record Found:";
            cout << "\n Room No: " << record.room_no;
            cout << "\n Address: " << record.address;
            cout << "\n Phone No: " << record.phone;
            cout << "\n Citizenship Number: " << record.citizenship_number;
            cout << "\n Number of Days: " << record.days;
            cout << "\n Bed Type: " << record.bed_type;
            cout << "\n Fare: " << record.fare;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\n No record found for name: " << search_name;
    }

    pause();
}

bool Hotel::check(int r) {
    for (const auto& record : records) {
        if (record.room_no == r) {
            return true;
        }
    }
    return false;
}

void Hotel::display_room_count() {
    clear_screen();
    head();
    cout << "\n Total Rooms Allotted: " << records.size();
    pause();
}

void Hotel::display_vacant_rooms() {
    clear_screen();
    head();
    cout << "\n Vacant Rooms:";
    for (int room : all_rooms) {
        if (!check(room)) {
            cout << "\n Room No: " << room;
        }
    }
    pause();
}

void Hotel::display_total_rooms() {
    clear_screen();
    head();
    cout << "\n Total Number of Rooms: " << total_rooms;
    pause();
}

void Hotel::display_available_beds() {
    clear_screen();
    head();
    cout << "\n Single Beds Available: " << get_single_bed_count();
    cout << "\n Double Beds Available: " << get_double_bed_count();
    pause();
}

void Hotel::display_bed_rates() {
    clear_screen();
    head();
    cout << "\n Single Bed Rate: " << single_bed_rate << " NRS";
    cout << "\n Double Bed Rate: " << double_bed_rate << " NRS";
    pause();
}

void Hotel::display_menu() {
    clear_screen();
    head();
    Menu menu;
    menu.display();
    pause();
}

void Hotel::update_menu_price() {
    clear_screen();
    head();
    Menu menu;
    string item_name;
    float new_price;
    cout << "\n Enter Menu Item to Update Price: ";
    cin.ignore();
    getline(cin, item_name);
    cout << " Enter New Price: ";
    cin >> new_price;
    menu.update_price(item_name, new_price);
    pause();
}

void Hotel::save_records() {
    ofstream file("records.txt");
    if (file.is_open()) {
        for (const auto& record : records) {
            file << record.room_no << '\n';
            file << record.name << '\n';
            file << record.address << '\n';
            file << record.phone << '\n';
            file << record.citizenship_number << '\n';
            file << record.days << '\n';
            file << record.bed_type << '\n';
            file << record.fare << '\n';
        }
        file.close();
        cout << "\n Records saved successfully!";
    } else {
        cout << "\n Error opening file!";
    }
}

void Hotel::load_records() {
    ifstream file("records.txt");
    if (file.is_open()) {
        Hotel record;
        while (file >> record.room_no) {
            file.ignore();
            getline(file, record.name);
            getline(file, record.address);
            getline(file, record.phone);
            getline(file, record.citizenship_number);
            file >> record.days;
            file.ignore();
            getline(file, record.bed_type);
            file >> record.fare;
            file.ignore();
            records.push_back(record);
        }
        file.close();
    } else {
        cout << "\n Error opening file!";
    }
}

int main() {
    Hotel hotel;
    hotel.load_records(); // Load records at the start
    
    hotel.main_menu();
    return 0;
}
 