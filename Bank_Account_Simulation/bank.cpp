#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
protected:
    string name;
    int accNo;
    float balance;
public:
    virtual void input() {
        cout << "Enter name, account number and initial balance: ";
        cin >> name >> accNo >> balance;
    }

    virtual void display() {
        cout << "Name: " << name << " | Acc No: " << accNo << " | Balance: " << balance;
    }

    virtual void deposit(float amt) {
        balance += amt;
        cout << "Deposited " << amt << ". New balance: " << balance << endl;
    }

    virtual void withdraw(float amt) {
        if (amt > balance)
            cout << "Insufficient balance!" << endl;
        else {
            balance -= amt;
            cout << "Withdrew " << amt << ". Remaining balance: " << balance << endl;
        }
    }

    virtual void update() {} // Overridden later
    virtual string getType() { return "Base"; }

    virtual void save(ofstream &out) = 0;
    virtual void load(ifstream &in) = 0;

    int getAccNo() const { return accNo; }

};
    
class SavingsAccount : public Account {
    float interestRate;
public:
    void input() override {
        Account::input();
        cout << "Enter interest rate (%): ";
        cin >> interestRate;
    }

    void update() override {
    float interest = balance * (interestRate / 100.0f);
    balance += interest;
    cout << "Interest of " << interest << " added. New balance: " << balance << endl;
    }

    void display() override {
        cout << "[Savings] ";
        Account::display();
        cout << " | Interest Rate: " << interestRate << "%" << endl;
    }

    string getType() override { return "S"; }

    void save(ofstream &out) override {
        out << "S " << name << " " << accNo << " " << balance << " " << interestRate << "\n";
    }

    void load(ifstream &in) override {
        in >> name >> accNo >> balance >> interestRate;
    }
};
    
class CurrentAccount : public Account {
    float overdraftLimit;
public:
    void input() override {
        Account::input();
        cout << "Enter overdraft limit: ";
        cin >> overdraftLimit;
    }

    void withdraw(float amt) override {
    if (balance - amt < -overdraftLimit) {
        cout << "Overdraft limit exceeded! Withdrawal denied.\n";
    } else {
        balance -= amt;
        cout << "Withdrew " << amt << ". New balance: " << balance << endl;
    }
    }

    void update() override {
        if (balance < 0) {
            balance -= 500; // apply penalty
            cout << "Penalty applied. New balance: " << balance << endl;
        } else {
            cout << "No penalty for " << name << ". Balance is fine.\n";
        }
    }

    void display() override {
        cout << "[Current] ";
        Account::display();
        cout << " | Overdraft Limit: " << overdraftLimit << endl;
    }

    string getType() override { return "C"; }

       void save(ofstream &out) override {
        out << "C " << name << " " << accNo << " " << balance << " " << overdraftLimit << "\n";
    }

    void load(ifstream &in) override {
        in >> name >> accNo >> balance >> overdraftLimit;
    }
};

class Bank {
    Account* accounts[20];
    int count;
public:
    Bank() : count(0) {}

    void addAccount() {
        cout << "1. Savings\n2. Current\nChoose: ";
        int ch; cin >> ch;

        if (ch == 1)
            accounts[count] = new SavingsAccount();
        else if (ch == 2)
            accounts[count] = new CurrentAccount();
        else {
            cout << "Invalid.\n";
            return;
        }
        accounts[count]->input();
        count++;
    }

    void showAll() {
        if (count == 0) { cout << "No accounts.\n"; return; }
        for (int i = 0; i < count; i++) accounts[i]->display();
    }

    void saveToFile() {
        ofstream fout("accounts.txt");
        for (int i = 0; i < count; i++)
            accounts[i]->save(fout);
        fout.close();
        cout << "Saved to file.\n";
    }

    void loadFromFile() {
        ifstream fin("accounts.txt");
        if (!fin) { cout << "No file found.\n"; return; }

        count = 0;
        char type;
        while (fin >> type) {
            if (type == 'S')
                accounts[count] = new SavingsAccount();
            else if (type == 'C')
                accounts[count] = new CurrentAccount();
            else continue;
            accounts[count]->load(fin);
            count++;
        }
        fin.close();
        cout << "Loaded " << count << " accounts.\n";
    }

    void depositOrWithdraw(bool isDeposit) {
    int acc;
    cout << "Enter account number: ";
    cin >> acc;

    for (int i = 0; i < count; i++) {
        if (accounts[i]->getAccNo() == acc) {
            float amt;
            cout << "Enter amount: ";
            cin >> amt;

            if (isDeposit)
                accounts[i]->deposit(amt);
            else
                accounts[i]->withdraw(amt);

            saveToFile(); // <-- new: save after every change
            cout << "Transaction complete and saved.\n";
            return;
        }
    }
        cout << "Account not found.\n";
    }

    void monthlyUpdate() {
        if (count == 0) {
            cout << "No accounts to update.\n";
            return;
        }

        cout << "--- Applying monthly updates ---\n";
        for (int i = 0; i < count; i++) {
            accounts[i]->update(); // polymorphic call
        }

        saveToFile(); // persist the changes
        cout << "All accounts updated and saved.\n";
    }


        ~Bank() {
            for (int i = 0; i < count; i++) delete accounts[i];
        }
    };

int main() {
    Bank b;
    b.loadFromFile();

    int ch;
    while (true) {
        cout << "\n--- BANK MENU ---\n"
            << "1. Add Account\n"
            << "2. Show All\n"
            << "3. Deposit\n"
            << "4. Withdraw\n"
            << "5. Monthly Update\n"
            << "6. Save\n"
            << "7. Exit\n"
            << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1: b.addAccount(); break;
            case 2: b.showAll(); break;
            case 3: b.depositOrWithdraw(true); break;
            case 4: b.depositOrWithdraw(false); break;
            case 5: b.monthlyUpdate(); break;
            case 6: b.saveToFile(); break;
            case 7: b.saveToFile(); cout << "Exiting...\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
