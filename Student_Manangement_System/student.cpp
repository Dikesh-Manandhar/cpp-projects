#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<limits>
#ifdef _WIN32
#include <conio.h>
#endif
using namespace std;

// pause helper: waits for the user to press Enter
void pause(){
#ifdef _WIN32
    cout << "\nPress any key to continue...";
    // consume leftover newline if any
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    _getch();
#else
    cout << "\nPress Enter to continue...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
#endif
}

class student{
    char name[50];
    int roll;
    float marks;
    char grade;
    public:
        void input(){
            cout<<"Enter name, roll, marks and grade"<<endl;
            // keep simple whitespace-separated input for name to match original behavior
            string tmp;
            cin>>tmp>>roll>>marks>>grade;
            // copy into fixed buffer, ensure null-termination
            strncpy(name, tmp.c_str(), sizeof(name)-1);
            name[sizeof(name)-1] = '\0';
        }
        void display(){
            cout<<"Name:"<<string(name)<<" Roll:"<<roll<<" Marks:"<<marks<<" Grade:"<<grade<<endl;
        }
        int getRoll(){
            return roll;
        }
};

void addStudent(){
    student s;
    const char *dataFile = "student.bin";
    ofstream fout(dataFile,ios::binary|ios::app);
    if(!fout){
        cout<<"Unable to open data file for writing: "<<dataFile<<endl;
        return;
    }
    s.input();
    fout.write((char*)&s,sizeof(s));
    fout.close();
}

void displayAll(){
    student s;
    const char *dataFile = "student.bin";
    ifstream fin(dataFile,ios::binary);
    if(!fin){
        cout<<"No records found ("<<dataFile<<")."<<endl;
        return;
    }
    while(fin.read((char*)&s,sizeof(s)))
    {
        s.display();
    }
    fin.close();
    pause();
}

void searchStudent(int roll){
    student s;
    const char *dataFile = "student.bin";
    ifstream fin(dataFile,ios::binary);
    if(!fin){
        cout<<"No records found ("<<dataFile<<")."<<endl;
        return;
    }
    bool found = false;
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll() == roll){
            s.display();
            found = true;
            break;
        }
    }
    if(!found){
        cout<<"Student with roll "<<roll<<" not found."<<endl;
    }
    fin.close();
    pause();
}

void deleteStudent(int roll){
    student s;
    const char *dataFile = "student.bin";
    const char *tempFile = "temp.bin";
    ifstream fin(dataFile,ios::binary);
    ofstream fout(tempFile, ios::binary);
    if(!fin){
        cout<<"No records found ("<<dataFile<<")."<<endl;
        return;
    }
    bool found = false;
    while(fin.read((char*)&s,sizeof(s)))
    {
        if(s.getRoll() == roll){
            found = true;
            continue; // skip writing this record to delete it
        }
        fout.write((char*)&s,sizeof(s));
    }
    fin.close();
    fout.close();
    if(found){
        remove(dataFile);
        rename(tempFile, dataFile);
        cout<<"Student with roll "<<roll<<" deleted."<<endl;
    } else {
        remove(tempFile); // clean up temp file if no deletion
        cout<<"Student with roll "<<roll<<" not found."<<endl;
    }
}

void modifyStudent(int roll){
    student s;
    const char *dataFile = "student.bin";
    fstream file(dataFile, ios::in | ios::out | ios::binary);
    if(!file){
        cout<<"No records found ("<<dataFile<<")."<<endl;
        return;
    }
    bool found = false;
    while(file.read((char*)&s, sizeof(s))){
        if(s.getRoll() == roll){
            cout << "Current details: ";
            s.display();
            cout << "Enter new details:" << endl;
            s.input();
            // Move the file pointer back to the start of this record
            file.seekp(-static_cast<int>(sizeof(s)), ios::cur);
            file.write((char*)&s, sizeof(s));
            found = true;
            cout << "Record updated." << endl;
            break;
        }
    }
    if(!found){
        cout<<"Student with roll "<<roll<<" not found."<<endl;
    }
    file.close();
}

int main(){
    int option = 0;
    while(true){
        cout<<"\n--- Student Management ---\n";
        cout<<"1. Add new student\n2. Display all students\n3. Search by roll\n4. Delete by roll\n5. Modify by roll\n6. Exit\n";
        cout<<"Choose an option: ";
        if(!(cin >> option)){
            // handle non-integer input
            cin.clear();
            string junk;
            getline(cin, junk);
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }
        switch(option){
            case 1:
                addStudent();
                break;
            case 2:
                displayAll();
                break;
            case 3: {
                int roll;
                cout << "Enter roll number to search: ";
                if(cin >> roll) searchStudent(roll);
                else { cin.clear(); string junk; getline(cin, junk); cout<<"Invalid roll."<<endl; }
                break;
            }
            case 4: {
                int roll;
                cout << "Enter roll number to delete: ";
                if(cin >> roll) deleteStudent(roll);
                else { cin.clear(); string junk; getline(cin, junk); cout<<"Invalid roll."<<endl; }
                break;
            }
            case 5: {
                int roll;
                cout << "Enter roll number to modify: ";
                if(cin >> roll) modifyStudent(roll);
                else { cin.clear(); string junk; getline(cin, junk); cout<<"Invalid roll."<<endl; }
                break;
            }
            case 6:
                cout << "Exiting." << endl;
                return 0;
            default:
                cout << "Invalid option. Please enter a number between 1 and 6." << endl;
        }
    }
    return 0;
}
