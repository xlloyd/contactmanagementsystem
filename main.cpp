#include <iostream>
#include <fstream>
#include <vector>
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

std::vector<Contact> contacts;

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
    return (userInput == "abort" || userInput == "Abort"|| userInput == "ABORT");
}

// Function to search for contacts by name, email, or phone number
 void searchContacts(const std::string& searchQuery) {
    if (searchQuery == "abort") {
        std::cout << "Search process was aborted by the user.\n";
        return;
    }

    std::vector<Contact> searchResults;
    for (const auto& contact : contacts) {
        if (contact.name == searchQuery || contact.phoneNumber == searchQuery || contact.emailAddress == searchQuery) {
            searchResults.push_back(contact);
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

    auto duplicateContact = std::find_if(contacts.begin(), contacts.end(), [&newContact](const Contact& c) {
        return c.name == newContact.name;
    });

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
            auto duplicatePhone = std::find_if(contacts.begin(), contacts.end(), [&newContact](const Contact& c) {
                return c.phoneNumber == newContact.phoneNumber;
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
        std::cin >> newContact.emailAddress;

        if (!isValidEmailAddress(newContact.emailAddress)) {
            std::cout << "Invalid email address!\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        } else {
            auto duplicateEmail = std::find_if(contacts.begin(), contacts.end(), [&newContact](const Contact& c) {
                return c.emailAddress == newContact.emailAddress;
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

    std::set<std::string> additionalPhoneNumbers;
    std::string hasAnotherPhoneNumber;
    while (true) {
        clearScreen();
        std::cout << "Do you have another phone number? (yes/no): ";
        std::cin >> hasAnotherPhoneNumber;

        // Convert input to lowercase for case-insensitive comparison
        std::transform(hasAnotherPhoneNumber.begin(), hasAnotherPhoneNumber.end(), hasAnotherPhoneNumber.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (hasAnotherPhoneNumber == "yes" || hasAnotherPhoneNumber == "y") {
            std::string additionalPhoneNumber;
            std::cout << "Enter additional phone number (11 digits): ";
            std::cin >> additionalPhoneNumber;

            if (!isValidPhoneNumber(additionalPhoneNumber)) {
                std::cout << "Invalid phone number! Phone number must be 11 digits.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            if (additionalPhoneNumbers.find(additionalPhoneNumber) != additionalPhoneNumbers.end() ||
                newContact.phoneNumber.find(additionalPhoneNumber) != std::string::npos ||
                std::any_of(contacts.begin(), contacts.end(), [&additionalPhoneNumber](const Contact& c) {
                    return c.phoneNumber == additionalPhoneNumber || c.phoneNumber.find(additionalPhoneNumber) != std::string::npos;
                })) {
                std::cout << "Duplicate phone number! Please enter a uniquephone number.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            additionalPhoneNumbers.insert(additionalPhoneNumber);
            newContact.phoneNumber += ", " + additionalPhoneNumber;
        } else if (hasAnotherPhoneNumber == "no" || hasAnotherPhoneNumber == "n") {
            break;
        } else {
            std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

    std::set<std::string> additionalEmailAddresses;
    std::string hasAnotherEmailAddress;
    while (true) {
        clearScreen();
        std::cout << "Do you have another email address? (yes/no): ";
        std::cin >> hasAnotherEmailAddress;

        // Convert input to lowercase for case-insensitive comparison
        std::transform(hasAnotherEmailAddress.begin(), hasAnotherEmailAddress.end(), hasAnotherEmailAddress.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (hasAnotherEmailAddress == "yes" || hasAnotherEmailAddress == "y") {
            std::string additionalEmailAddress;
            std::cout << "Enter additional email address: ";
            std::cin >> additionalEmailAddress;

            if (!isValidEmailAddress(additionalEmailAddress)) {
                std::cout << "Invalid email address!\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            if (additionalEmailAddresses.find(additionalEmailAddress) != additionalEmailAddresses.end() ||
                newContact.emailAddress.find(additionalEmailAddress) != std::string::npos ||
                std::any_of(contacts.begin(), contacts.end(), [&additionalEmailAddress](const Contact& c) {
                    return c.emailAddress == additionalEmailAddress || c.emailAddress.find(additionalEmailAddress) != std::string::npos;
                })) {
                std::cout << "Duplicate email address! Please enter a unique email address.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                continue;
            }

            additionalEmailAddresses.insert(additionalEmailAddress);
            newContact.emailAddress += ", " + additionalEmailAddress;
        } else if (hasAnotherEmailAddress == "no" || hasAnotherEmailAddress == "n") {
            break;
        } else {
            std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
        }
    }

    contacts.push_back(newContact);
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

    auto contact = std::find_if(contacts.begin(), contacts.end(), [&searchQuery](const Contact& c) {
        return c.name == searchQuery || c.phoneNumber == searchQuery || c.emailAddress == searchQuery;
    });

    if (contact != contacts.end()) {
        contacts.erase(contact);
        saveContacts();
        std::cout << "Contact deleted successfully!\n";
    } else {
        std::cout << "Contact not found!\n";
    }

    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Function to modify an existing contact
void modifyContact() {
    std::string searchQuery;
    std::cout << "Enter the name, phone number, or email of the contact to modify or abort:";
    std::cin.ignore();
    std::getline(std::cin, searchQuery);

     if (searchQuery == "abort") {
        std::cout << "Contact modification process was aborted.\n";
        return;
    }

    auto contact = std::find_if(contacts.begin(), contacts.end(), [&searchQuery](const Contact& c) {
        return c.name == searchQuery || c.phoneNumber == searchQuery || c.emailAddress == searchQuery;
    });

    if (contact != contacts.end()) {
        Contact modifiedContact = *contact;

        clearScreen(); // Clear the screen

        std::cout << "Current Contact Details:\n";
        std::cout << std::left << std::setw(12) << "Name:" << modifiedContact.name << "\n";
        std::cout << std::left << std::setw(12) << "Phone:" << modifiedContact.phoneNumber << "\n";
        std::cout << std::left << std::setw(12) << "Email:" << modifiedContact.emailAddress << "\n\n";

        std::string newName, newPhoneNumber, newEmailAddress;

        while (true) {
            std::cout << "Enter new contact name (full name) or abort: ";
            std::getline(std::cin, newName);

            if (newName == "abort") {
                std::cout << "Contact modification process was aborted.\n";
                return;
            }

            // Check if the modified contact name consists of at least two words
            size_t spaceIndex = newName.find(' ');
            if (spaceIndex == std::string::npos) {
                std::cout << "Invalid name! Please enter the full name (first name and last name).\n";
                continue;
            } else if (std::any_of(contacts.begin(), contacts.end(), [&newName](const Contact& c) {
                return c.name == newName;
            })) {
                std::cout << "Name already exists!\n";
                continue;
            } else {
                modifiedContact.name = newName;
                break;
            }
        }

        while (true) {
            std::cout << "Enter new phone number (11 digits) or abort: ";
            std::getline(std::cin, newPhoneNumber);

            if (newPhoneNumber == "abort") {
                std::cout << "Contact modification process was aborted.\n";
                return;
            }

            // Perform input validation for the phone number
            if (!isValidPhoneNumber(newPhoneNumber)) {
                std::cout << "Invalid phone number! Phone number must be 11 digits.\n";
                continue;
            } else if (std::any_of(contacts.begin(), contacts.end(), [&newPhoneNumber](const Contact& c) {
                return c.phoneNumber == newPhoneNumber;
            })) {
                std::cout << "Phone number already exists!\n";
                continue;
            } else {
                modifiedContact.phoneNumber = newPhoneNumber;
                break;
            }
        }

        while (true) {
            std::cout << "Enter new email address or abort: ";
            std::getline(std::cin, newEmailAddress);

            if (newEmailAddress == "abort") {
                std::cout << "Contact modification process was aborted.\n";
                return;
            }

            // Perform input validation for the email address
            if (!isValidEmailAddress(newEmailAddress)) {
                std::cout << "Invalid email address!\n";
                continue;
            } else if (std::any_of(contacts.begin(), contacts.end(), [&newEmailAddress](const Contact& c) {
                return c.emailAddress == newEmailAddress;
            })) {
                std::cout << "Email address already exists!\n";
                continue;
            } else {
                modifiedContact.emailAddress = newEmailAddress;
                break;
            }
        }

        // Additional phone numbers
        std::set<std::string> additionalPhoneNumbers;
        std::string hasAnotherPhoneNumber;
        while (true) {
            clearScreen();
            std::cout << "Do you have another phone number? (yes/no): ";
            std::cin >> hasAnotherPhoneNumber;

            // Convert input to lowercase for case-insensitive comparison
            std::transform(hasAnotherPhoneNumber.begin(), hasAnotherPhoneNumber.end(), hasAnotherPhoneNumber.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            if (hasAnotherPhoneNumber == "yes" || hasAnotherPhoneNumber == "y") {
                std::string additionalPhoneNumber;
                std::cout << "Enter additional phone number (11 digits): ";
                std::cin.ignore();
                std::getline(std::cin, additionalPhoneNumber);

                if (!isValidPhoneNumber(additionalPhoneNumber)) {
                    std::cout << "Invalid phone number! Phone number must be 11 digits.\n";
                    std::cout << "Press enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    continue;
                }

                if (additionalPhoneNumbers.find(additionalPhoneNumber) != additionalPhoneNumbers.end() ||
                    modifiedContact.phoneNumber.find(additionalPhoneNumber) != std::string::npos ||
                    std::any_of(contacts.begin(), contacts.end(), [&additionalPhoneNumber](const Contact& c) {
                        return c.phoneNumber == additionalPhoneNumber || c.phoneNumber.find(additionalPhoneNumber) != std::string::npos;
                    })) {
                    std::cout << "Duplicate phone number! Please enter a unique phone number.\n";
                    std::cout << "Press enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    continue;
                }

                additionalPhoneNumbers.insert(additionalPhoneNumber);
                modifiedContact.phoneNumber += ", " + additionalPhoneNumber;
            } else if (hasAnotherPhoneNumber == "no" || hasAnotherPhoneNumber == "n") {
                break;
            } else {
                std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }

        // Additional email addresses
        std::set<std::string> additionalEmailAddresses;
        std::string hasAnotherEmailAddress;
        while (true) {
            clearScreen();
            std::cout << "Do you have another email address? (yes/no): ";
            std::cin >> hasAnotherEmailAddress;

            // Convert input to lowercase for case-insensitive comparison
            std::transform(hasAnotherEmailAddress.begin(), hasAnotherEmailAddress.end(), hasAnotherEmailAddress.begin(), [](unsigned char c) {
                return std::tolower(c);
            });

            if (hasAnotherEmailAddress == "yes" || hasAnotherEmailAddress == "y") {
                std::string additionalEmailAddress;
                std::cout << "Enter additional email address: ";
                std::cin.ignore();
                std::getline(std::cin, additionalEmailAddress);

                if (!isValidEmailAddress(additionalEmailAddress)) {
                    std::cout << "Invalid email address!\n";
                    std::cout << "Press enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    continue;
                }

                if (additionalEmailAddresses.find(additionalEmailAddress) != additionalEmailAddresses.end() ||
                    modifiedContact.emailAddress.find(additionalEmailAddress) != std::string::npos ||
                    std::any_of(contacts.begin(), contacts.end(), [&additionalEmailAddress](const Contact& c) {
                        return c.emailAddress == additionalEmailAddress || c.emailAddress.find(additionalEmailAddress) != std::string::npos;
                    })) {
                    std::cout << "Duplicate email address! Please enter a unique email address.\n";
                    std::cout << "Press enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    continue;
                }

                additionalEmailAddresses.insert(additionalEmailAddress);
               additionalEmailAddresses.insert(additionalEmailAddress);
                modifiedContact.emailAddress += ", " + additionalEmailAddress;
            } else if (hasAnotherEmailAddress == "no" || hasAnotherEmailAddress == "n") {
                break;
            } else {
                std::cout << "Invalid input! Please answer 'yes' or 'no'.\n";
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }

        *contact = modifiedContact;
        saveContacts();

        std::cout << "Contact modified successfully!\n";
     } else {
        std::cout << "Contact not found!\n";
    }

    std::cout << "Press enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


// Function to display all contacts
void displayContacts() {
    if (contacts.empty()) {
        std::cout << "No contacts found!\n";
    } else {
        std::cout << "Contacts:\n";
        std::vector<Contact> sortedContacts = contacts;  // Create a copy of contacts vector
        std::sort(sortedContacts.begin(), sortedContacts.end(), compareContacts);  // Sort the copy

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
    std::ifstream inputFile(FILE_PATH);
    if (!inputFile) {
        std::cout << "Contacts file not found. Creating a new file.\n";
        return;
    }

    contacts.clear();

    std::string line;
    while (std::getline(inputFile, line)) {
        Contact contact;
        contact.name = line;
        std::getline(inputFile, contact.phoneNumber);
        std::getline(inputFile, contact.emailAddress);
        contacts.push_back(contact);
    }

    inputFile.close();
}

// Function to save contacts to the DAT file
void saveContacts() {
    std::ofstream outputFile(FILE_PATH);
    if (!outputFile) {
        std::cout << "Failed to create or open the contacts file.\n";
        return;
    }

    for (const auto& contact : contacts) {
        outputFile << contact.name << "\n";
        outputFile << contact.phoneNumber << "\n";
        outputFile << contact.emailAddress << "\n";
    }

    outputFile.close();
}

// Function to display the menu options
void displayMenu() {
    clearScreen(); // Clear the screen
    std::cout << "Contact Management System\n";
    std::cout << "-------------------------\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. Modify Contact\n";
    std::cout << "3. Delete Contact\n";
    std::cout << "4. Display Contacts\n";
    std::cout << "5. Search Contacts\n";
    std::cout << "6. Exit\n";
}

// Function to clear the console screen
void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

// Function to validate a phone number
bool isValidPhoneNumber(const std::string& phoneNumber) {
    // Phone number must be 11 digits
    return std::regex_match(phoneNumber, std::regex("\\d{11}"));
}

// Function to validate an email address
bool isValidEmailAddress(const std::string& emailAddress) {
    // Simple email validation using a regular expression
    return std::regex_match(emailAddress, std::regex("[\\w-]+(\\.[\\w-]+)*@[\\w-]+(\\.[\\w-]+)*(\\.[a-zA-Z]{2,})"));
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
            std::cout << "Press enter to continue...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                std::cout << "Enter search query (name, email, or phone number) or enter 'abort' to cancel: ";
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
                std::cout << "Press enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
                break;
        }
    }

    return 0;
}
