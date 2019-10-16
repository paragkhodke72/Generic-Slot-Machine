/*
The slot machine game contains 5 header files as slor machine,reel,pay,circularLl
This application as user to enter name --> give initial budged 100 as mentioned in problem --> ask to spin
This application gerenates random combination and if the user is lucky and got "AAA,BBB,CCC,777" -> his budges will increase in respected payScale
This applcation as user to quit the game if user Press 'n' for 'No'.
If the user is out of money, he will not able to play again
This application print and congratulate the user if user got any one from 4 combinations.
This application uses Classes using Templated and Vectots to push,pod the data.
This application is based on Circular LinkedList which consisit of Templates and two other classed excluding Structure Node.
*/

#include "PayoutTable.hpp"
#include "SlotMachine.hpp"
#include <iostream>
using namespace std;

// printing combination using Operator Overloading
ostream & operator << (ostream & Printing, const vector<char> & PrintCombination) {
    Printing << "\nYou Got: "<<'(';
    for (int i = 0; i < PrintCombination.size(); i++) {
        if (i) Printing << ',';
        Printing << PrintCombination[i];
    }
    Printing << ')';
    return Printing;
}

class SM_Game {
    private:
        int userBudget;
        PayOut<vector<char>, int> PaytableVectorName; // payout class of vector -> for adding the  char and int
        SlotMachine<Reel<char>> S_MachineVectorName; // slot machine of reel -> class of vector for adding the  char
    public:
        SM_Game(int amount = 100) : userBudget(amount), PaytableVectorName(PayOut<vector<char>, int>()),
            S_MachineVectorName(SlotMachine<Reel<char>>(3, Reel<char>({'A', 'A', 'A', 'A', 'B', 'B', 'B', 'C', 'C', '7'})))
        {   // adding Char data  and payScale using vectors
            PaytableVectorName.insert({ {'A', 'A', 'A'}, 14 });
            PaytableVectorName.insert({ {'B', 'B', 'B'}, 35 });
            PaytableVectorName.insert({ {'C', 'C', 'C'}, 100 });
            PaytableVectorName.insert({ {'7', '7', '7'}, 900 });
        }
        
        ~SM_Game() {}// De-Constructor
        
    int loop() { // loop ro get combination and ask users choice to Run
        char User_input;
        cout << "Your Budged  as :  $ " << userBudget << '\n';
        cout<<"\nKindly Look at the table, if you got any one of the 4 combinations listed above then you could possibly win the respected payout\n";
       
        while(userBudget > 0) {
            cout << "\nYour remaning amount/Budges is:  $ " << userBudget << '\n';
            cout<<"\n\n\n\t\t|-----------------------|\n";
            cout<<"\t\t| Combination | payout  |\n";
            cout<<"\t\t|-----------------------|\n";
            cout<<"\t\t|   A A A     |  $14    |\n";
            cout<<"\t\t|   B B B     |  $35    |\n";
            cout<<"\t\t|   C C C     |  $100   |\n";
            cout<<"\t\t|   7 7 7     |  $900   |\n";
            cout<<"\t\t|-----------------------|\n";
            cout << "\nDo you want to play the game and spin ? (y/n):\n";
            
            userBudget--;
            
            while (cin >> User_input) {
                if (!isalpha(User_input)) {
                    cout << "Invalid char, Please try agai with 'y', 'n'.\nNow Enter:-\n";
                    continue;
                }
            
                User_input = tolower(User_input);
            
                if (User_input != 'y' and User_input != 'n') {// checking for user choice
                    cout << "Invalid Char input for. Try with 'y', 'n' char. \nNow enter again: \n";
                    continue;
                }
                break;
            }
            
            if (tolower(User_input) == 'y') {// checking for user choice
                S_MachineVectorName.spin();
                
                vector<char> combination = { S_MachineVectorName.get(1), S_MachineVectorName.get(2), S_MachineVectorName.get(3) };
                auto item = PaytableVectorName.find(combination);
                
                if (item.first == combination){
                    userBudget += item.second;
                    cout<<"\ncongratulation !!!";
                }
                cout << combination << "\n\n";
            }
            else{
                cout<<"\nThank You for using slot machine application by parag khodke\n";
                break;
            }
        }
        return 0;
    }
};

int main()
{
    string username;
    cout<<"\n\n           SLOT MACHIEN GAME      \n\n";
    cout<<"\t\t|-----------------------|\n";
    cout<<"\t\t| Combination | payout  |\n";
    cout<<"\t\t|-----------------------|\n";
    cout<<"\t\t|   A A A     |  $14    |\n";
    cout<<"\t\t|   B B B     |  $35    |\n";
    cout<<"\t\t|   C C C     |  $100   |\n";
    cout<<"\t\t|   7 7 7     |  $900   |\n";
    cout<<"\t\t|-----------------------|\n";
    cout<<"\nHello and welcome to slot machine game,kindly enter your name to play\n";
    getline(cin, username);
    cout<<"\nHello , " << username <<" , Congratulation You got initial ";
    return SM_Game().loop();
}
