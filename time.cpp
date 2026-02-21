#include<iostream>
#include<cmath>
using namespace std;
int timeFormat(double t)
{
 int Minutes,Seconds,Millis;
 Minutes=(int)t / 60;
 Seconds=(int)t%60;
 Millis = round((t - (int)t) * 1000);
 cout<<Minutes<<":"<<Seconds<<":"<<Millis;
 return 0;
}
