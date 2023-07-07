#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <regex>
#include <limits>
#include <set>
#include <cctype>
#include <iomanip>

class Contact {
public:
    std::string name;
    std::string phoneNumber;
    std::string emailAddress;
};

std::unordered_map<std::string, Contact> contacts;

// Function prototypes
bool compareContacts(const Contact& contact1, const Contact& contact2);
void addContact();
void modifyContact();
void deleteContact();
void displayContacts();
void searchContacts(const std::string& searchQuery);
void loadContacts();
void saveContacts();
void displayMenu();
void clearScreen();
bool isValidPhoneNumber(const std::string& phoneNumber);
bool isValidEmailAddress(const std::string& emailAddress);

// File path for the DAT file
const std::string FILE_PATH = "contacts.dat";

// Function to compare contacts by name for sorting
bool compareContacts(const Contact& contact1, const Contact& contact2) {
    return contact1.name < contact2.name;
}

bool checkAbort() {
    std::string userInput;
    std::cout << "Enter 'abort' to cancel: ";
    std::cin >> userInput;
    return (userInput == "abort" || userInput == "Abort" || userInput == "ABORT");
}

// Function to search for contacts by name, email, or phone number
void searchContacts(const std::string& searchQuery) {
    if (searchQuery == "abort") {
        std::cout << "Search process was aborted by the user.\n";
        return;
    }

    std::vector<Contact> searchResults;
    for (const auto& contact : contacts) {
        const Contact& currentContact = contact.second;
        if (currentContact.name == searchQuery || currentContact.phoneNumber == searchQuery || currentContact.emailAddress == searchQuery) {
            searchResults.push_back(currentContact);
        }
    }

    if (searchResults.empty()) {
        std::cout << "No matching contacts found!\n";
    } else {
        std::cout << "Matching Contacts:\n";

        std::size_t maxPhoneNumberLength = 0;
        for (const auto& contact : searchResults) {
            maxPhoneNumberLength = std::max(maxPhoneNumberLength, contact.phoneNumber.length());
        }

        std::cout << std::left << std::setw(20) << "Name:" << std::setw(maxPhoneNumberLength + 5) << "Phone:" << "Email:\n";
        for (const auto& contact : searchResults) {
            std::cout << std::left << std::setw(20) << contact.name << std::setw(maxPhoneNumberLength + 5) << contact.phoneNumber << contact.emailAddress << "\n";
        }
    }

    std::cout << "\nPress enter to continue or enter 'abort' to cancel: ";
    std::string input;
    std::getline(std::cin, input);

    // Convert input to lowercase for case-insensitive comparison
    std::transform(input.begin(), input.end(), input.begin(), [](unsigned char c) {
        return std::tolower(c);
    });

    if (input == "abort") {
        std::cout << "Search process was aborted by the user.\n";
        return;
    }
}

// Function to add a new contact
void addContact() {
    Contact newContact;

    while (true) {
        clearScreen();
        std::cout << "Enter contact name (full name): ";
        std::cin.ignore();
        std::getline(std::cin, newContact.name);

        size_t spaceIndex = newContact.name.find(' ');
        if (spaceIndex == std::string::npos) {
            std::cout << "Invalid name! Please enter the full name (first name and last name).\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        } else {
            break;
        }
    }

    auto duplicateContact = contacts.find(newContact.name);
    if (duplicateContact != contacts.end()) {
        std::cout << "Contact with the same name already exists!\n";
        std::cout << "Press enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    do {
        clearScreen();
        std::cout << "Enter contact phone number (11 digits): ";
        std::cin >> newContact.phoneNumber;

        if (!isValidPhoneNumber(newContact.phoneNumber)) {
            std::cout << "Invalid phone number! Phone number must be 11 digits.\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        } else {
            auto duplicatePhone = std::find_if(contacts.begin(), contacts.end(), [&newContact](const std::pair<std::string, Contact>& c) {
                return c.second.phoneNumber == newContact.phoneNumber;
            });

            if (duplicatePhone != contacts.end()) {
                std::cout << "Contact with the same phone number already exists!\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            break;
        }
    } while (true);

    do {
        clearScreen();
        std::cout << "Enter contact email address: ";
        std::cin.ignore();
        std::getline(std::cin, newContact.emailAddress);

        if (!isValidEmailAddress(newContact.emailAddress)) {
            std::cout << "Invalid email address!\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        } else {
            auto duplicateEmail = std::find_if(contacts.begin(), contacts.end(), [&newContact](const std::pair<std::string, Contact>& c) {
                return c.second.emailAddress == newContact.emailAddress;
            });

            if (duplicateEmail != contacts.end()) {
                std::cout << "Contact with the same email address already exists!\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            break;
        }
    } while (true);

    contacts[newContact.name] = newContact;
    saveContacts();

    std::cout << "Contact added successfully!\n";
    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to delete a contact
void deleteContact() {
    std::string searchQuery;
    std::cout << "Enter the name, phone number, or email of the contact to delete: ";
    std::cin.ignore();
    std::getline(std::cin, searchQuery);

    auto contact = contacts.find(searchQuery);
    if (contact != contacts.end()) {
        std::cout << "Are you sure you want to delete the following contact?\n";
        std::cout << "Name: " << contact->second.name << "\n";
        std::cout << "Phone: " << contact->second.phoneNumber << "\n";
        std::cout << "Email: " << contact->second.emailAddress << "\n";
        std::cout << "Enter 'delete' to confirm deletion: ";
        std::string confirmation;
        std::cin >> confirmation;

        if (confirmation == "delete") {
            contacts.erase(contact);
            saveContacts();
            std::cout << "Contact deleted successfully!\n";
        } else {
            std::cout << "Contact deletion canceled!\n";
        }
    } else {
        std::cout << "No matching contact found!\n";
    }

    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to modify an existing contact
void modifyContact() {
    std::string searchQuery;
    std::cout << "Enter the name, phone number, or email of the contact to modify: ";
    std::cin.ignore();
    std::getline(std::cin, searchQuery);

    auto contact = std::find_if(contacts.begin(), contacts.end(), [&searchQuery](const std::pair<std::string, Contact>& c) {
        const Contact& currentContact = c.second;
        return currentContact.name == searchQuery || currentContact.phoneNumber == searchQuery || currentContact.emailAddress == searchQuery;
    });

    if (contact != contacts.end()) {
        std::cout << "Current contact information:\n";
        std::cout << std::setw(10) << std::left << "Name:" << contact->second.name << "\n";
        std::cout << std::setw(10) << std::left << "Phone:" << contact->second.phoneNumber << "\n";
        std::cout << std::setw(10) << std::left << "Email:" << contact->second.emailAddress << "\n\n";

        Contact modifiedContact = contact->second;

        std::cout << "Enter new contact name (or enter 'skip' to keep the current name): ";
        std::string newName;
        std::getline(std::cin, newName);
        if (newName != "skip") {
            modifiedContact.name = newName;
        }

        std::cout << "Enter new contact phone number (or enter 'skip' to keep the current number): ";
        std::string newPhoneNumber;
        std::getline(std::cin, newPhoneNumber);
        if (newPhoneNumber != "skip" && isValidPhoneNumber(newPhoneNumber)) {
            modifiedContact.phoneNumber = newPhoneNumber;
        }

        std::cout << "Enter new contact email address (or enter 'skip' to keep the current address): ";
        std::string newEmailAddress;
        std::getline(std::cin, newEmailAddress);
        if (newEmailAddress != "skip" && isValidEmailAddress(newEmailAddress)) {
            modifiedContact.emailAddress = newEmailAddress;
        }

        contacts.erase(contact);
        contacts[modifiedContact.name] = modifiedContact;
        saveContacts();

        std::cout << "Contact modified successfully!\n";
    } else {
        std::cout << "No matching contact found!\n";
    }

    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to display all contacts
void displayContacts() {
    if (contacts.empty()) {
        std::cout << "No contacts found!\n";
    } else {
        std::cout << "Contacts:\n";

        std::vector<Contact> sortedContacts;
        for (const auto& contact : contacts) {
            sortedContacts.push_back(contact.second);
        }

        std::sort(sortedContacts.begin(), sortedContacts.end(), compareContacts);

        std::size_t maxPhoneNumberLength = 0;
        for (const auto& contact : sortedContacts) {
            maxPhoneNumberLength = std::max(maxPhoneNumberLength, contact.phoneNumber.length());
        }

        std::cout << std::left << std::setw(20) << "Name:" << std::setw(maxPhoneNumberLength + 5) << "Phone:" << "Email:\n";
        for (const auto& contact : sortedContacts) {
            std::cout << std::left << std::setw(20) << contact.name << std::setw(maxPhoneNumberLength + 5) << contact.phoneNumber << contact.emailAddress << "\n";
        }
    }

    std::cout << "\nPress enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to load contacts from the DAT file
void loadContacts() {
    std::ifstream file(FILE_PATH);

    if (!file) {
        std::cerr << "Error opening file for reading.\n";
        return;
    }

    contacts.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, phoneNumber, emailAddress;
        if (std::getline(iss, name, '\t') && std::getline(iss, phoneNumber, '\t') && std::getline(iss, emailAddress)) {
            Contact contact;
            contact.name = name;
            contact.phoneNumber = phoneNumber;
            contact.emailAddress = emailAddress;
            contacts[contact.name] = contact;
        }
    }

    file.close();
}

// Function to save contacts to the DAT file
void saveContacts() {
    std::ofstream file(FILE_PATH);

    if (!file) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    for (const auto& contact : contacts) {
        file << contact.second.name << '\t' << contact.second.phoneNumber << '\t' << contact.second.emailAddress << '\n';
    }

    file.close();
}
// Function to display the main menu
void displayMenu() {
    clearScreen();
    std::cout << "Contact Management System\n";
    std::cout << "-------------------------\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. Modify Contact\n";
    std::cout << "3. Delete Contact\n";
    std::cout << "4. Display Contacts\n";
    std::cout << "5. Search Contacts\n";
    std::cout << "6. Quit\n";
    std::cout << "Enter your choice: ";
}

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to validate a phone number
bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Match exactly 11 digits
    std::regex regex("\\d{11}");
    return std::regex_match(phoneNumber, regex);
}

// Function to validate an email address
bool isValidEmailAddress(const std::string& emailAddress) {
    // Match email address format using a simple regex pattern
    std::regex regex("[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)*\\.[a-zA-Z]{2,}");
    return std::regex_match(emailAddress, regex);
}

int main() {
    loadContacts();

    int choice;

    while (true) {
        displayMenu();
        std::cout << "Enter your choice (1-6): ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in input buffer
            clearScreen(); // Clear the screen
            std::cout << "Invalid choice! Please try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Press enter to continue...";
            std::cin.get();
            continue;
        }

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                modifyContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                displayContacts();
                break;
            case 5: {
                std::string searchQuery;
                clearScreen();
                std::cout << "Enter search query (name, email, or phone number): ";
                std::cin.ignore();
                std::getline(std::cin, searchQuery);
                searchContacts(searchQuery);
                break;
            }
            case 6:
                clearScreen();
                saveContacts();
                std::cout << "Thank you for using the Contact Management System!\n";
                return 0;
            default:
                clearScreen();
                std::cout << "Invalid choice! Please try again.\n";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Press enter to continue...";
                std::cin.get();
                break;
        }
    }

    return 0;
}
