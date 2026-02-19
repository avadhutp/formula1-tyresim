#include<iostream>
#include"time.h"
using namespace std;
int Loopingcount()
{
    double Laptime, Basetime, lapcount, Degrate, TotalLaptime;
    cout<<"Enter the number of laps in the stint: ";
    cin>>lapcount;
    cout<<"Enter the current Lap time of the driver: ";
    cin>>Basetime;
    cout<<"Enter the current rate of degradation of the track: ";
    cin>>Degrate;
    for(int i=0; i<=lapcount; i++)
    {
        Laptime=Basetime+(i*Degrate);
        if(i==lapcount)
        {
            break;
        }
        else if(i==0)
        {
            continue;
        }
        else if(i==1)
        {
        cout<<"Laptime after "<<i<<" lap will be ";
        timeFormat(Laptime);
        cout<<"\n";
        }
        else{
        cout<<"Laptime after "<<i<<" laps will be ";
        timeFormat(Laptime);
        cout<<"\n";
        }
        TotalLaptime+=Laptime;
    }
    cout<<"Final laptime after a "<<lapcount<<" lap stint will be ";
    timeFormat(Laptime);
    cout<<"\n";
    cout<<"Total laptime of the stint will come out to ";
    timeFormat(TotalLaptime);
    cout<<"\n";
    return 0; 
}
int main()
{
    Loopingcount();
    return 0;
}
