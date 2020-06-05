#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>





using namespace std;



//BANK ACCOUNT SYSTEM by Rajeev Thundiyil. ID: 1718515



//HASHTABLE ENTRY
class HashEntry {
private:
    int key;
    int value;
    char  acctype;
    int bal;
    string nm;
    HashEntry* next;
public:
    HashEntry(int key, int value, char acctype, int bal, string nm) {
        this->key = key;
        this->value = value;
        this->acctype = acctype;
        this->bal = bal;
        this->nm = nm;
        this->next = NULL;
    }

    int getKey() {
        return key;
    }

    int getValue() {
        return value;
    }
    char getType() {

        return acctype;
    }

    int getbal() {

        return bal;
    }

    string getName() {

        return nm;
    }
    void setValue(int value) {
        this->value = value;
    }
    void setName(string nm) {
        this->nm = nm;
    }
    void setBal(int bal) {
        this->bal = bal;
    }
    void setType(char acctype ) {
        this->acctype = acctype;
    }
    void addBal(int num) {

        bal = bal + num;
        setBal(bal);
    }
    void subBal(int num) {
        if (num < bal) {
            bal = bal - num;
            setBal(bal);
        }
        else {
            cout << "Balance is too small for such withdrawal. " << endl;
        }
    }
    HashEntry* getNext() {
        return next;
    }

    void setNext(HashEntry* next) {
        this->next = next;
    }
};



const int TABLE_SIZE = 10; // amount of buckets in the table. 0-9

//HASHMAP
class HashMap {
private:
    HashEntry** table;
public:
    HashMap() {
        table = new HashEntry * [TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; i++)
            table[i] = NULL;
    }

    int get(int key) {
        int hash = (key % TABLE_SIZE);
        if (table[hash] == NULL)
            return -1;
        else {
            HashEntry* entry = table[hash];
            while (entry != NULL && entry->getKey() != key)
                entry = entry->getNext();
            if (entry == NULL) {
                return -1;
            }
            else {

                cout << "Account Number: " << entry->getValue() << endl;
                cout << "Account Name: " << entry->getName() << endl;
                cout << "Account Type: " << entry->getType() << endl;
                cout << "Account Balance: " << entry->getbal() << endl;
                return entry->getValue();
            }
        }
    }

    void put(int key, int value,char acctype, int bal, string nm) {
        int hash = (key % TABLE_SIZE);
        if (table[hash] == NULL)
            table[hash] = new HashEntry(key, value, acctype,  bal,  nm);
        else {
            HashEntry* entry = table[hash];
            while (entry->getNext() != NULL)
                entry = entry->getNext();
            if (entry->getKey() == key) {
                entry->setValue(value);
                entry->setBal(bal);
                entry->setName(nm);
                entry->setType(acctype);
            }
            else
                entry->setNext(new HashEntry(key, value, acctype, bal, nm));
        }
    }

    void deposit(int key, int value, int num) {
        int hash = (key % TABLE_SIZE);
        if (table[hash] != NULL){
            HashEntry* entry = table[hash];
            entry->addBal(num);

 
        
        
        }
    
 
  
    }
    void withdrawal(int key, int value, int num) {
    
        int hash = (key % TABLE_SIZE);
        if (table[hash] != NULL) {
            HashEntry* entry = table[hash];
            entry->subBal(num);




        }
    
    
    
    
    }
    void remove(int key) {
        int hash = (key % TABLE_SIZE);
        if (table[hash] != NULL) {
            HashEntry* prevEntry = NULL;
            HashEntry* entry = table[hash];
            while (entry->getNext() != NULL && entry->getKey() != key) {
                prevEntry = entry;
                entry = entry->getNext();
            }
            if (entry->getKey() == key) {
                if (prevEntry == NULL) {
                    HashEntry* nextEntry = entry->getNext();
                    delete entry;
                    table[hash] = nextEntry;
                }
                else {
                    HashEntry* next = entry->getNext();
                    delete entry;
                    prevEntry->setNext(next);
                }
            }
        }
    }

    ~HashMap() {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL) {
                HashEntry* prevEntry = NULL;
                HashEntry* entry = table[i];
                while (entry != NULL) {
                    prevEntry = entry;
                    entry = entry->getNext();
                    delete prevEntry;
                }
            }
        delete[] table;
    }
};

















int main() {
    HashMap hash;
    int k, v;
    int c, counter;
    string name;
    char type;
    int balance;
    int num;
    counter = 0;
    while (1) {
        //Input area for the program//
        counter++;
        cout << endl; 
        cout << "1.Create Bank Account" << endl;
        cout << "2.Display Account" << endl;
        cout << "3.Delete Account" << endl;
        cout << "4.Deposit" << endl;
        cout << "5.Withdrawal" << endl;
        cout << "6.Exit" << endl;
        cout << "Enter your choice: " << endl;
        cin >> c;
        switch (c) {
        case 1:
            cout << "Your account number is " << counter<< endl;

            v = counter;
            k = v % 10;
            
            cout << "Enter your name: " << endl;
            cin >> name;

            cout << "Enter type of account: (Type C for Checkings, S for Savings)" << endl;
            cin >> type;

            cout << "Enter balance: " << endl;
            cin >> balance;


           
            hash.put(k, v,type,balance,name);
            


            break;
        case 2:
            
            cout << "Enter account number: " << endl;
            cin >> v;
            k = v % 10;
            if (hash.get(k) == -1) {
                cout << "No element found at key " << k << endl;
                continue;
            }
        
            break;
        case 3:
            cout << "Enter key of the element to be deleted: ";
            cin >> k;
            hash.remove(k);
            break;
        case 4:
            cout << "Enter the id of your account: " << endl;
            cin >> v;
            k = v % 10;
            cout << "Enter the amount you wish to deposit: " << endl;
            cin >> num;

            if (hash.get(k) == -1) {
                cout << "Account not found " << endl;
            }
            else{
                hash.deposit(k, v, num); 
                
                cout << "Your new account details: " << endl;
                hash.get(k);
            
            }
            break;

        case 5:
            cout << "Enter the id of your account: " << endl;
            cin >> v;
            k = v % 10;
            cout << "Enter the amount you wish to withdraw: " << endl;
            cin >> num;

            if (hash.get(k) == -1) {
                cout << "Account not found " << endl;
            }
            else {
                hash.withdrawal(k, v, num);

                cout << "Your new account details: " << endl;
                hash.get(k);

            }
            break;
        case 6:
            exit(1);
        default:
            cout << "\nEnter correct option\n";
        }
    }
    return 0;
}