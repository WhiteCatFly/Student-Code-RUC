#include <iostream>
#include "string1.h"
const int Arsize = 10;
const int Maxlen = 81;
int main()
{
  using std::cout;
  using std::cin;
  using std::endl;
  String name;
  cout<<"Hi,what's your name?\n>>";
  cin>>name;

  cout << name << ",please enter up-to " <<Arsize
      <<" short sayings <empty line to quit>: \n";
  String saying[Arsize];
  int i;
  for (i=0;i<Arsize ;i++)
  {
    cout << i+1 << ": ";
    cin.get(temp, Maxlen);
    while ( cin && cin.get()!='\n')
      couotinue;
    if(!cin|| temp[0]== '\0')
      break;
  }
  int total = i;

  if(total>0)
  {
    cout << "Here are your sayings:\n";
    for(i = 0; i < total; i++)
    {
      cout<< sayings[i][0] <<": "<< sayings[i] << endl;
    }
    int shortest=0;
    int first = 0;
    for (i =1; i < total; i++)
    {
      if(saying[i].lenth() < sayings[shortest].length())
        shortest=i;
      if(sayings[i] < sayings[first])
        first=i;
    }
    cout << "Shortest saying:\n" << sayings[shortest] << endl;
    cout << "First alphbetically:\n" << sayings[first] << endl;
    cout << "This program used "<< String::HowMany()
         << " String objects. Bye.\n";
  }
  else
    cout << "No input! Bye.\n";
  return 0;
}
