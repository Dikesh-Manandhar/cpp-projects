// Online C++ compiler to run C++ program online
#include <iostream>
#include<fstream>
#include<string>
using namespace std;

class stud{
    private:
        char name[50];
        int roll;
    public:
        void input(){
            cout<<"Enter name and roll:"<<endl;
            cin>>name>>roll;
        }
        void display(){
            cout<<"Name:"<<name<<" Roll"<<roll<<endl;
        }
    };

int main() {
    // Write C++ code here
    stud s;
    ofstream fout("student.dat",ios::binary);
    for(int i=0;i<2;i++){  
        s.input();
        fout.write((char*)&s,sizeof(s));
    }
    fout.close();
    ifstream fin("student.dat",ios::binary);
    while(fin.read((char*)&s,sizeof(s)))
        {
            s.display();
        }
    fin.close();
    return 0;
}
