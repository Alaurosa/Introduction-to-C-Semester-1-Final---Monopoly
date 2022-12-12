#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    double current_networth = 0;
    int num_players = 4;
    int players [4];
    int player_networth [4];
    int property_values [0];
    //create and store an array or dictionary of property values for each character
    //(to make it easier, we should create a property for each character and store relevant data in that property)
    string end;
    cout << "Do you want to end game? ";
    cin >> end;
    if(end == "yes" || end == "Yes")
    {
        for(int i = 0; i < num_players; i++)
        {
            cout << "Your current networth: " << current_networth << endl;
            //create a for loop that iterates through the property values associated with each character
            //in the for loop, print each property value for each character
        }
        
        exit(0);
    }
    else if(end == "No" || end == "no")
    {
        for(int i = 0; i < num_players; i++)
        {
            cout << "Your current networth: " << current_networth << endl;
            //create a for loop that iterates through the property values associated with each character
            //in the for loop, print each property value for each character
        }
    }
    else
    {
        cout << "Your answer is not sufficient, please try again" << endl;
    }

    cout << "game continues" << endl;
}