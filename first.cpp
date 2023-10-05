#include <string>
#include <iostream>

using namespace std;

struct monster
{
    int health;
    int attack;
    int defense;
    string name;
};

int main()
{
monster dragon={100,50,5,"Mimi"};
cout  << " monster name=" << dragon.name << endl;
return 0;
}