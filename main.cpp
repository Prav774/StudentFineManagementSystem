#include <bits/stdc++.h>
using namespace std;

// ================= USER CLASS =================
class User {
protected:
    string UserId, Username, Password, Role;

public:
    User(string UI, string U, string P, string R) {
        UserId = UI;
        Username = U;
        Password = P;
        Role = R;
    }

    virtual ~User() {}

    string getUserId() { return UserId; }
    string getPassword() { return Password; }
    string getUsername() { return Username; }
    string getRole() { return Role; }

    virtual void viewprofile() {
        cout << "\nPROFILE";
        cout << "\nUserId: " << UserId;
        cout << "\nUsername: " << Username;
        cout << "\nRole: " << Role << endl;
    }
};

// ================= STUDENT CLASS =================
class Student : public User {
private:
    string Department;
    int Year;
    int Semester;
    string Email;

public:
    Student(string UI, string U, string P,
            string D, int Y, int S, string E)
        : User(UI, U, P, "Student") {
        Department = D;
        Year = Y;
        Semester = S;
        Email = E;
    }

    void viewprofile() override {
        cout << "\nPROFILE";
        cout << "\nUserId: " << UserId;
        cout << "\nUsername: " << Username;
        cout << "\nRole: Student";
        cout << "\nDepartment: " << Department;
        cout << "\nYear: " << Year;
        cout << "\nSemester: " << Semester;
        cout << "\nEmail: " << Email << endl;
    }

    void editProfile() {
        cout << "Enter New Department: ";
        cin >> Department;
        cout << "Enter New Year: ";
        cin >> Year;
        cout << "Enter New Semester: ";
        cin >> Semester;
        cout << "Enter New Email: ";
        cin >> Email;
        cout << "Profile Updated Successfully!\n";
    }
};

// ================= AUTHENTICATION =================
class Authentication {
private:
    vector<User*> users;

public:
    ~Authentication() {
        for (auto user : users)
            delete user;
    }

    void Register() {
        string ui, u, p, r;
        cout << "Enter UserId:\n"; cin >> ui;

        for (auto user : users) {
            if (user->getUserId() == ui) {
                cout << "UserId already exists!\n";
                return;
            }
        }

        cout << "Enter Username:\n"; cin >> u;
        cout << "Enter Password:\n"; cin >> p;
        cout << "Enter Role (Admin/Cashier/Student):\n"; cin >> r;

        if (r == "Student") {
            string d, e;
            int y, s;

            cout << "Enter Department:\n"; cin >> d;
            cout << "Enter Year:\n"; cin >> y;
            cout << "Enter Semester:\n"; cin >> s;
            cout << "Enter Email:\n"; cin >> e;

            users.push_back(new Student(ui, u, p, d, y, s, e));
        } else {
            users.push_back(new User(ui, u, p, r));
        }

        cout << "Registered Successfully!\n";
    }

    User* login() {
        string ui, p;
        cout << "Enter UserId:\n"; cin >> ui;
        cout << "Enter Password:\n"; cin >> p;

        for (auto user : users) {
            if (user->getUserId() == ui &&
                user->getPassword() == p) {
                cout << "Login Successful!\n";
                return user;
            }
        }

        cout << "Invalid Login!\n";
        return nullptr;
    }
};

// ================= PAYMENT CLASS =================
class Payment {
private:
    int Id;
    string Student;
    string FineType;
    string Date;
    double Amount;

public:
    Payment(int id, string s, string f, string d, double a) {
        Id = id;
        Student = s;
        FineType = f;
        Date = d;
        Amount = a;
    }

    int getId() { return Id; }
    string getStudent() { return Student; }
    string getFineType() { return FineType; }
    string getDate() { return Date; }

    void update(string f, string d, double a) {
        FineType = f;
        Date = d;
        Amount = a;
    }

    void display() {
        cout << "\nID: " << Id
             << "\nStudent: " << Student
             << "\nFine Type: " << FineType
             << "\nDate: " << Date
             << "\nAmount: " << Amount << "\n";
    }
};

// ================= PAYMENT SERVICE =================
class PaymentService {
private:
    vector<Payment> payments;
    int counter = 1;

public:
    void addPayment() {
        string s, f, d;
        double a;

        cout << "Student Name: ";
        cin >> s;
        cout << "Fine Type: ";
        cin >> f;
        cout << "Date (YYYY-MM-DD): ";
        cin >> d;
        cout << "Amount: ";
        cin >> a;

        payments.push_back(Payment(counter++, s, f, d, a));
        cout << "Payment Added!\n";
    }

    void updatePayment() {
        int id;
        cout << "Enter Payment ID: ";
        cin >> id;

        for (auto &p : payments) {
            if (p.getId() == id) {
                string f, d;
                double a;

                cout << "New Fine Type: ";
                cin >> f;
                cout << "New Date: ";
                cin >> d;
                cout << "New Amount: ";
                cin >> a;

                p.update(f, d, a);
                cout << "Updated Successfully!\n";
                return;
            }
        }

        cout << "Payment Not Found!\n";
    }

    void deletePayment() {
        int id;
        cout << "Enter Payment ID: ";
        cin >> id;

        for (int i = 0; i < payments.size(); i++) {
            if (payments[i].getId() == id) {
                payments.erase(payments.begin() + i);
                cout << "Deleted Successfully!\n";
                return;
            }
        }

        cout << "Payment Not Found!\n";
    }

    void viewAll() {
        for (auto &p : payments)
            p.display();
    }

    void filterByFineType() {
        string type;
        cout << "Fine Type: ";
        cin >> type;

        for (auto &p : payments)
            if (p.getFineType() == type)
                p.display();
    }

    void filterByStudent() {
        string name;
        cout << "Student Name: ";
        cin >> name;

        for (auto &p : payments)
            if (p.getStudent() == name)
                p.display();
    }

    void filterByDate() {
        string date;
        cout << "Date: ";
        cin >> date;

        for (auto &p : payments)
            if (p.getDate() == date)
                p.display();
    }

    void filterFineWithinDateRange() {
        string type, start, end;

        cout << "Fine Type: ";
        cin >> type;
        cout << "Start Date: ";
        cin >> start;
        cout << "End Date: ";
        cin >> end;

        for (auto &p : payments) {
            if (p.getFineType() == type &&
                p.getDate() >= start &&
                p.getDate() <= end)
                p.display();
        }
    }
};

// ================= MENUS =================
void AdminMenu(PaymentService &ps) {
    int ch;
    do {
        cout << "\n--- Admin Menu ---";
        cout << "\n1.View All";
        cout << "\n2.Filter by Fine Type";
        cout << "\n3.Filter by Student";
        cout << "\n4.Filter by Date";
        cout << "\n5.Filter Fine within Date Range";
        cout << "\n6.Add Payment";
        cout << "\n7.Update Payment";
        cout << "\n8.Delete Payment";
        cout << "\n9.Logout\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: ps.viewAll(); break;
            case 2: ps.filterByFineType(); break;
            case 3: ps.filterByStudent(); break;
            case 4: ps.filterByDate(); break;
            case 5: ps.filterFineWithinDateRange(); break;
            case 6: ps.addPayment(); break;
            case 7: ps.updatePayment(); break;
            case 8: ps.deletePayment(); break;
        }
    } while (ch != 9);
}

void CashierMenu(PaymentService &ps) {
    int ch;
    do {
        cout << "\n--- Cashier Menu ---";
        cout << "\n1.Add Payment";
        cout << "\n2.Update Payment";
        cout << "\n3.Delete Payment";
        cout << "\n4.Logout\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1: ps.addPayment(); break;
            case 2: ps.updatePayment(); break;
            case 3: ps.deletePayment(); break;
        }
    } while (ch != 4);
}

void StudentMenu(User *user) {
    Student* student = dynamic_cast<Student*>(user);
    if (student == nullptr) return;

    int ch;
    do {
        cout << "\n--- Student Menu ---";
        cout << "\n1.View Profile";
        cout << "\n2.Edit Profile";
        cout << "\n3.Logout\nChoice: ";
        cin >> ch;

        if (ch == 1)
            student->viewprofile();
        else if (ch == 2)
            student->editProfile();

    } while (ch != 3);
}

// ================= MAIN =================
int main() {
    Authentication auth;
    PaymentService paymentService;

    int ch;

    while (true) {
        cout << "\n1.Register\n2.Login\n3.Exit\nEnter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                auth.Register();
                break;

            case 2: {
                User* user = auth.login();
                if (user == nullptr) break;

                if (user->getRole() == "Admin")
                    AdminMenu(paymentService);
                else if (user->getRole() == "Cashier")
                    CashierMenu(paymentService);
                else if (user->getRole() == "Student")
                    StudentMenu(user);

                break;
            }

            case 3:
                return 0;

            default:
                cout << "Invalid choice\n";
        }
    }

    return 0;
}
