#include "inventory.h"
#include <iostream>
#include <iomanip>
#include <limits>

void clearInputBuffer() {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //
    }

void showInventory(const std::map<int, MenuItem>& inventory) {
    std::cout << "\n\t\t\t\t\tCURRENT INVENTORY\n\n\n";
    std::cout << "\tID\t   Name\t\t\t          Price\t             Quantity\n";
    std::cout << "\t---------------------------------------------------------------------\n";
    for (const auto& item : inventory) {
        std::cout << "\t" << item.first << "\t" << std::setw(30) << std::left << item.second.name << "\tPHP " <<
        std::fixed << std::setprecision(2) << item.second.price << "\t\t" << item.second.quantity << "\n";
    }
    std::cout << "\t---------------------------------------------------------------------\n";
    std::cout << std::endl;
}

void addItem(std::map<int, MenuItem>& inventory) {
    system("CLS");

    int id;
    std::string name;
    double price;
    int quantity;

    std::cout << "\n\t\t\t\t\tCURRENT INVENTORY\n\n\n";
    std::cout << "\tID\t   Name\t\t\t          Price\t             Quantity\n";
    std::cout << "\t---------------------------------------------------------------------\n";
    for (const auto& item : inventory) {
        std::cout << "\t" << item.first << "\t" << std::setw(30) << std::left << item.second.name << "\tPHP " <<
        std::fixed << std::setprecision(2) << item.second.price << "\t\t" << item.second.quantity << "\n";
    }
    std::cout << "\t---------------------------------------------------------------------\n";
    std::cout << std::endl;
    std::cout << "\n\n\n\t\t\t\t\tADD ITEM\n";

    while (true) {
        std::cout << "\n\tEnter the ID of the new item: ";
        if (!(std::cin >> id)) {
            std::cout << "\n\tInvalid input. Please enter a valid ID.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (inventory.count(id) > 0) {
            std::cout << "\n\tThis ID already exists. Please enter a new ID.\n";
            continue;
        }

        break;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "\tEnter the name of the new item: ";
        std::getline(std::cin, name);

        bool isValid = true;
        for (char ch : name) {
            if (!std::isalpha(ch) && !std::isspace(ch)) {
                isValid = false;
                break;
            }
        }

        if (isValid && !name.empty()) {
            break;
        }

        std::cout << "\n\tInvalid input. Please enter a valid name (letters only).\n\n";
    }

    while (true) {
        std::cout << "\tEnter the price of the new item (in PHP): ";
        if (!(std::cin >> price)) {
            std::cout << "\n\tInvalid input. Please enter a valid price.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (price <= 0) {
            std::cout << "\n\tInvalid input. Price cannot be negative.\n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        break;
    }

    while (true) {
        std::cout << "\tEnter the quantity of the new item: ";
        if (!(std::cin >> quantity)) {
            std::cout << "\n\tInvalid input. Please enter a valid quantity.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (quantity <= 0) {
            std::cout << "\n\tInvalid input. Quantity cannot be negative.\n\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        break;
    }

    inventory[id] = {name, price, quantity};
    std::cout << "\n\tNew item added to the inventory.\n";

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n\tPress ENTER to continue... ";
    std::cin.get();

    system("CLS");
}

void deleteItem(std::map<int, MenuItem>& inventory) {
    system("CLS");

    int id;
    std::cout << "\n\t\t\t\t\tCURRENT INVENTORY\n\n\n";
    std::cout << "\tID\t   Name\t\t\t          Price\t             Quantity\n";
    std::cout << "\t---------------------------------------------------------------------\n";
    for (const auto& item : inventory) {
        std::cout << "\t" << item.first << "\t" << std::setw(30) << std::left << item.second.name << "\tPHP " <<
        std::fixed << std::setprecision(2) << item.second.price << "\t\t" << item.second.quantity << "\n";
    }
    std::cout << "\t---------------------------------------------------------------------\n";
    std::cout << std::endl;
    std::cout << "\n\t\t\t\t\tDELETE ITEM\n";
    std::cout << "\n\n\tEnter the ID of the item you wish to delete: ";
    std::cin >> id;

    if (std::cin.fail()) {
        std::cout << "\n\tInvalid input. Please enter a valid ID. ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        system("CLS");
        deleteItem(inventory);
        return;
    }

    auto it = inventory.find(id);
    if (it != inventory.end()) {
        inventory.erase(it);
        std::cout << "\n\tItem with ID " << id << " deleted from the inventory." << std::endl;
    }
}
void updateItem(std::map<int, MenuItem>& inventory) {
    system("CLS");
    int id;
    std::cout << "\n\t\t\t\t\tCURRENT INVENTORY\n\n\n";
    std::cout << "\tID\t   Name\t\t\t          Price\t             Quantity\n";
    std::cout << "\t---------------------------------------------------------------------\n";
    for (const auto& item : inventory) {
        // The setw(30) and left are used to format the output by setting a fixed width and aligning the text to the left.
        std::cout << "\t" << item.first << "\t" << std::setw(30) << std::left << item.second.name << "\tPHP " <<
        // The fixed and setprecision(2) ensure that the price is displayed with two decimal places.
        std::fixed << std::setprecision(2) << item.second.price << "\t\t" << item.second.quantity << "\n";
    }
    std::cout << "\t---------------------------------------------------------------------\n";
    std::cout << std::endl;
    std::cout << "\n\t\t\t\t\tUPDATE ITEM\n";
    std::cout << "\n\n\tEnter the ID of the item you wish to update: ";
    std::cin >> id;

    if (std::cin.fail()) {
        std::cout << "\n\tInvalid input. Please enter a valid ID. ";   // Error Handling.
        std::cin.clear();
        clearInputBuffer();
        std::cin.get(); // Wait for the user to press ENTER.
        system("CLS");
        updateItem(inventory);
        return;
    }

    auto it = inventory.find(id);
    if (it != inventory.end()) {
        std::cout << "\n\tEnter the new name for item " << id << ": ";
        clearInputBuffer();
        std::getline(std::cin, it->second.name);

        while (true) {
            std::cout << "\n\tEnter the new price for item " << id << ": ";
            if (!(std::cin >> it->second.price)) {   // Checks if the price entered is valid(Numerical values only).
                std::cout << "\n\tInvalid input. Please enter a valid price.\n\n";   // Error Handling.
                std::cin.clear();
                clearInputBuffer();
                continue;
            }

            if (it->second.price <= 0) {   // The price must not be zero or a negative number.
                std::cout << "\n\tInvalid input. Price cannot be negative.\n\n";   // Error Handling.
                clearInputBuffer();
                continue;
            }

            break;
        }

        while (true) {
            std::cout << "\n\tEnter the new quantity for item " << id << ": ";
            if (!(std::cin >> it->second.quantity)) {   // Checks if the quantity entered is valid(Numerical values only).
                std::cout << "\n\tInvalid input. Please enter a valid quantity.\n\n";   // Error Handling.
                std::cin.clear();
                clearInputBuffer();
                continue;
            }

            if (it->second.quantity <= 0) {   // The price must not be zero or a negative number.
                std::cout << "\n\tInvalid input. Quantity cannot be negative.\n\n";   // Error Handling.
                clearInputBuffer();
                continue;
            }

            break;
        }

        std::cout << "\n\tItem with ID " << id << " updated successfully." << std::endl;   // Successful Update.
    } else {
        std::cout << "\n\tItem with ID " << id << " not found in the inventory." << std::endl; // Appear when there is no corresponding ID in the inventory.
    }

    clearInputBuffer();

    std::cout << "\n\tPress ENTER to continue... ";
    std::cin.get();
    system("CLS");  // Clear the screen
}

