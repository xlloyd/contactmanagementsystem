#include "menu.h"
#include "inventory.h"
#include <map>

int main() {
    std::map<int, MenuItem> inventory;

    // Initial inventory items.
    // (ID, Price, Quantity)
    inventory[1] = { "Hawaiian Pizza", 250.00, 10 };
    inventory[2] = { "Pepperoni Pizza", 300.00, 10 };
    inventory[3] = { "Chicken BBQ Pizza", 350.00, 10 };
    inventory[4] = { "Margherita Pizza", 400.00, 10 };
    inventory[5] = { "Zinger Burger", 180.00, 10 };
    inventory[6] = { "Chicken Burger", 150.00, 10 };
    inventory[7] = { "Quesadilla Burger", 200.00, 10 };
    inventory[8] = { "Chicken Sandwich", 240.00, 10 };
    inventory[9] = { "Seafood Sandwich", 160.00, 10 };
    inventory[10] = { "Roast Beef Sandwich", 180.00, 10 };

    loginMenu(inventory, nullptr);

    return 0;
}
