#include<iostream>
#include<fstream>
using namespace std;

class books{
    char name[50];
    char author[50];
    float price;
    public:
        void input(){
            cout<<"Enter book name, author and price"<<endl;
            cin>>name>>author>>price;
        }
        void display(){
            cout<<"Name:"<<name<<"Author:"<<author<<"Price:"<<price<<endl;
        }
};

int main(){
    books b;
    ofstream fout("books.bin",ios::binary);
    for(int i=0; i<2; i++)
    {
        b.input();
        fout.write((char*)&b,sizeof(b));
    }
    fout.close();
    ifstream fin("books.bin",ios::binary);
    while(fin.read((char*)&b,sizeof(b)))
    {
        b.display();
    }
    fin.close();
    return 0;
}

