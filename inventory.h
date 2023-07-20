#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>

// Representing Menu Items.
struct MenuItem {
    std::string name;  // Represents the name or description of the menu item.
    double price;      // Represents the price of the menu item.
    int quantity;      // Represents the quantity or stock of the menu item available in the inventory.
};

// Function declarations
void clearInputBuffer();
void showInventory(const std::map<int, MenuItem>& inventory);
void addItem(std::map<int, MenuItem>& inventory);
void deleteItem(std::map<int, MenuItem>& inventory);
void updateItem(std::map<int, MenuItem>& inventory);

#endif  // INVENTORY_H
