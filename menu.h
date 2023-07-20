#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>

// Forward declaration
struct MenuItem;

// Function declaration
void showCustomerMenu(std::map<int, MenuItem>& inventory);
void loginMenu(std::map<int, MenuItem>& inventory, void (*nextMenu)(std::map<int, MenuItem>&));
void showInventoryMenu(std::map<int, MenuItem>& inventory);

#endif  // MENU_H
