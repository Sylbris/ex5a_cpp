#include "sources/OrgChart.hpp"
#include <iostream>
#include <stdexcept>
using namespace ariel;
using namespace std;

int main(){
    string manager;
    string sub;
    int choice;
    OrgChart organization;
    while(true){
        cout << "[-------------------Welcome to your Organizational builder scheme!--------------------]\n";
        cout << "Press 1 -> to add more subordiantes. \nPress 2 -> to add or change your head of company. \n";
        cout << "Press 3 -> to print your firm top down \nPress 4 -> to print your firm bottom up\n";
        cout << "Press 5 -> to print your firm in Preorder\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Now choose a manager from the firm, and his subordinate \n";
            cin >> manager >> sub;
            organization.add_sub(manager, sub);
            break;
        case 2:
            cin >> manager;
            organization.add_root(manager);
        break;
            case 3:
              for (auto it = organization.begin_level_order(); it != organization.end_level_order(); ++it)
                {
                    cout << (*it) << " " ;
                }
                cout << "\n";
        break;
                case 4:
        /* code */
        break;
                case 5:
        /* code */
        break;

        default:
            break;
        }
    }
    return 0;
}