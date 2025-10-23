#include <iostream>
#include <conio.h>
using namespace std;

class Time
{
    private:
        int sec,min,hr;
    public:
        void input()
        {
            cout<<"Enter time in hr:min:sec format\n";
            cin>>hr>>min>>sec;
        }

        Time sub(Time t1, Time t2)
        {
            int sec;
            Time temp;
            int sec1 = t1.hr * 3600 + t1.min * 60 + t1.sec;
            int sec2 = t2.hr * 3600 + t2.min * 60 + t2.sec;
            if(sec1 > sec2)
            {
                sec = sec1 - sec2;
            }
            else
            {
                sec = sec2 - sec1;
            }
            temp.hr = sec / 3600;
            sec = sec % 3600;
            temp.min = sec / 60;
            sec = sec % 60;
            temp.sec = sec;
            return temp;
        }

        void display()
        {
            cout<<"Time is: "<<hr<<":"<<min<<":"<<sec<<endl;
        }
};

int main()
{
    Time t3,t4,t5;
    t3.input();
    t4.input();
    t5 = t5.sub(t3,t4);
    t5.display();
    getch();
    return 0;
}