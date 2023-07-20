#include "menu.h"
#include "inventory.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>
#include <conio.h>

using namespace std;

// Implementation of showCustomerMenu function
void showCustomerMenu(map<int, MenuItem>& inventory) {
        while (true) {
            cout << "\n\t\t\t\t\tCUSTOMER'S MENU\n\n";
            cout << "\n\tFOODS AVAILABLE: \n\n";
            cout << "\t[1] Pizzas\n";
            cout << "\t[2] Burgers\n";
            cout << "\t[3] Sandwiches\n";
            cout << "\t[4] Back to Main Menu\n";
            cout << "\n\tEnter your choice [1-4]: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {
                cout << "\n\tInvalid input. Please enter a valid choice. ";
                cin.clear();
                clearInputBuffer();
                continue;
            }

            switch (choice) {
                case 1:
                case 2:
                case 3: {
                    double totalPrice = 0.0;
                    string itemName;

                    system("CLS");

                    switch (choice) {
                        case 1:
                            cout << "\n\t\t\t\t\tPIZZAS\n\n";
                            itemName = "Pizza";
                            break;
                        case 2:
                            cout << "\n\t\t\t\t\tBURGERS\n\n";
                            itemName = "Burger";
                            break;
                        case 3:
                            cout << "\n\t\t\t\t\tSANDWICHES\n\n";
                            itemName = "Sandwich";
                            break;
                    }

                    cout << "\tID\tName\t\t\t\tPrice\t\t       Stock\n";
                    cout << "\t---------------------------------------------------------------------\n";
                    for (const auto& item : inventory) {
                        if (item.second.name.find(itemName) != string::npos) {
                            // The setw(20) and left are used to format the output by setting a fixed width and aligning the text to the left.
                            cout << "\t" << item.first << "\t" << setw(20) << left << item.second.name << "\t\tPHP " <<
                            // The fixed and setprecision(2) ensure that the price is displayed with two decimal places.
                            fixed << setprecision(2) << item.second.price << "\t\t" << item.second.quantity << endl;
                        }
                    }
                    cout << "\t---------------------------------------------------------------------\n";

                    vector<pair<int, int>> orderItems;  // Vector to store the ordered items (ID, quantity).

                    while (true) {
                        cout << "\n\tPlease enter the ID of the " << itemName << " you would like to order: ";
                        int pchoice;
                        cin >> pchoice;

                        if (cin.fail()) {   // Checks if the user entered a valid ID.
                            cout << "\n\tInvalid input. Please enter a valid item ID.\n";
                            cin.clear();
                            clearInputBuffer();
                            continue;
                        }

                        auto it = inventory.find(pchoice);
                        if (it != inventory.end() && it->second.name.find(itemName) != string::npos) {
                            cout << "\tPlease enter the quantity: ";
                            int quantity;
                            cin >> quantity;

                            if (cin.fail()) {   // Checks if the user entered a valid numerical number.
                                cout << "\n\tInvalid input. Please enter a valid quantity.\n";
                                cin.clear();
                                clearInputBuffer();
                                continue;
                            }

                            if (quantity <= it->second.quantity) {   // Checks if the desired quantity is within the current stock.
                                totalPrice += it->second.price * quantity;
                                it->second.quantity -= quantity;
                                orderItems.push_back(make_pair(pchoice, quantity));
                            } else {
                                cout << "\n\tInsufficient stock available. Please try again." << endl;
                            }
                        } else {
                            cout << "\n\tInvalid choice. Please try again." << endl;
                        }

                        cout << "\n\tDo you want to order another " << itemName << "/s? [y/n]: ";   // Ask the user if he/she wants to order another item.
                        char choice;
                        cin >> choice;

                        if (choice == 'N' || choice == 'n') {   // If NO, it will go to the receipt area.
                            break;  // Finish ordering
                        } else if (choice != 'Y' && choice != 'y') {   // If YES, it will ask the ID and quantity of the product again.
                            cout << "\n\tInvalid choice. Returning to previous menu.\n";   // It the user enters other answer other than YES or NO (y/n)
                            cout << "\tPress ENTER to continue... ";
                            clearInputBuffer();
                            cin.get();

                            system("CLS");
                            showCustomerMenu(inventory);
                            return;
                        }
                    }

                    system("CLS");

                    // Display the receipt of the order

                    // Display the receipt of the order
if (!orderItems.empty()) {
    cout << "\t------------------------------ RECEIPT ------------------------------\n";
    cout << "\tID\tName\t\t\t\tPrice\t\t    Quantity\n";
    cout << "\t---------------------------------------------------------------------\n";
    for (const auto& item : orderItems) {
        auto it = inventory.find(item.first);
        // The setw(20) and left are used to format the output by setting a fixed width and aligning the text to the left.
        cout << "\t" << item.first << "\t" << setw(20) << left << it->second.name << "\t\tPHP " <<
            // The fixed and setprecision(2) ensure that the price is displayed with two decimal places.
            fixed << setprecision(2) << it->second.price << "\t\t" << item.second << endl;
    }
    cout << "\t---------------------------------------------------------------------\n";
    cout << "\n\tYour total bill is: PHP " << fixed << setprecision(2) << totalPrice;
    cout << "\n\n\tThank you for ordering from Underrated Fast Food\n";
} else {
    cout << "\n\tNo items ordered. Returning to the previous menu.\n";
}

cout << "\n\tPress ENTER to continue... ";
clearInputBuffer();
cin.get();

system("CLS");
break;

                }
                case 4:
                    system("CLS");
                    loginMenu(inventory, nullptr); // If the user select 4, it will go back to the Main Menu.
                    return;
                default:
                    cout << "\n\tInvalid choice. Please try again. "; // Error handling
                    clearInputBuffer();
                    getchar();
                    system("CLS");
            }
        }
    }

// Implementation of loginMenu function
void loginMenu(map<int, MenuItem>& inventory, void (*nextMenu)(map<int, MenuItem>&)) {
        string password = "admin";

        cout << "\n\t\t\t\t\tWelcome to Underrated Fast Food!\n\n\n";

        while (true) {
            string input;
            cout << "\t[1] Admin's Menu\n";
            cout << "\t[2] Customer's Menu\n";
            cout << "\t[3] Exit\n";
            cout << "\n\tEnter your choice [1-3]: ";
            cin >> input;

            if (cin.fail()) { // Error Handling.
                cout << "\n\tInvalid input. Please enter a valid choice.\n";
                cin.clear();
                clearInputBuffer();
                continue;
            }

            if (input == "1") {
                cout << "\n\tEnter the password: ";
                string enteredPassword;

                // Mask the password with asterisks.
                char ch;
                while ((ch = getch()) != '\r') {
                    if (ch == '\b') {
                        if (!enteredPassword.empty()) {
                            enteredPassword.pop_back();
                            cout << "\b \b";
                        }
                    } else {
                        enteredPassword += ch;
                        cout << '*';
                    }
                }

                if (enteredPassword == password) {
                    system("CLS");
                    // If password is correct, then it will proceed to the Admin's Menu.
                    showInventoryMenu(inventory);
                    return;
                } else {
                    cout << "\n\n\tInvalid password! "; // If password is wrong, it will reset the Main Menu.
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore remaining input.
                    cin.get();  // Wait for user to press Enter.
                    system("CLS");
                    cout << "\n\t\t\t\t\tWelcome to Underrated Fast Food!\n\n\n";
                }
            } else if (input == "2") {
                // It will redirect the user to the Customer Menu.
                system("CLS");
                showCustomerMenu(inventory);
                return;
            } else if (input == "3") {
                // It will exit the program.
                system("CLS");
                cout << "\n\tThank you for visiting Underrated Fast Food. Goodbye!\n";
                if (nextMenu == nullptr) {
                    return;
                }
                nextMenu(inventory);
                return;
            } else {
                cout << "\n\tInvalid choice. Please try again. "; // Error Handling.
                clearInputBuffer();
                getchar();
                system("CLS");
                cout << "\n\t\t\t\t\tWelcome to Underrated Fast Food!\n\n\n";
            }
        }
    }

void showInventoryMenu(std::map<int, MenuItem>& inventory) {
    while (true) {
            cout << "\n\t\t\t\t\tInventory Menu\n\n";
            cout << "\t[1] Show Inventory\n";
            cout << "\t[2] Add New Item to Inventory\n";
            cout << "\t[3] Delete Item from Inventory\n";
            cout << "\t[4] Update Item in Inventory\n";
            cout << "\t[5] Exit\n\n";
            cout << "\tEnter your choice: ";

            int choice;
            cin >> choice;

            if (cin.fail()) {
                cout << "\n\tInvalid input. Please enter a valid choice. "; // Error Handling.
                clearInputBuffer();
                getchar();
                system("CLS");
            }

            switch (choice) {
                case 1:
                    showInventory(inventory); // It will show the Current Inventory.
                    break;
                case 2:
                    addItem(inventory); // The ADMIN can add new items to the inventory.
                    break;
                case 3:
                    deleteItem(inventory); // The ADMIN can delete items from the inventory.
                    break;
                case 4:
                    updateItem(inventory); // The ADMIN can update items in the inventory.
                    break;
                case 5:
                    system("CLS");
                    loginMenu(inventory, nullptr); // It will go back to the Main Menu.
                    return;
                default:
                    cout << "\n\tInvalid choice. Please try again. "; // Error Handling.
                    clearInputBuffer();
                    getchar();
                    system("CLS");
            }
        }
}
