# Contact management system
The Contact Management System is a program designed to help you efficiently manage your contacts. It provides a user-friendly interface to add, modify, delete, search, and display contacts. The program utilizes various features and data structures to ensure smooth contact management.

the contents of the Contact Management System program:

1. Header Files:
   - The program includes several header files that provide necessary functionalities: `iostream` for input/output operations, `fstream` for file handling, `unordered_map` for storing contacts, `algorithm` for sorting, `regex` for pattern matching, `limits` for numeric limits, `set` for sets of elements, `cctype` for character classification, and `iomanip` for input/output formatting.

2. `Contact` Class:
   - The `Contact` class is defined to represent a single contact. It contains three member variables: `name`, `phoneNumber`, and `emailAddress`.

3. `std::unordered_map<std::string, Contact> contacts`:
   - This unordered map is used to store contacts. It maps contact names (strings) to `Contact` objects. It provides efficient lookup and storage of contacts based on their names.

4. Function Prototypes:
   - Function prototypes are declared to define the functions that will be implemented later in the code. These functions handle various contact management operations, such as adding, modifying, deleting, searching, and displaying contacts.

5. Utility Functions:
   - `compareContacts` is a utility function used to compare contacts based on their names. It is used for sorting contacts.
   - `checkAbort` checks if the user wants to abort a process by entering 'abort'.

6. Contact Management Functions:
   - `searchContacts` searches for contacts based on a given search query (name, phone number, or email) and displays the matching contacts with their details.
   - `addContact` allows the user to add a new contact by entering the contact's name, phone number, and email address.
   - `deleteContact` allows the user to delete a contact by searching for it and confirming the deletion.
   - `modifyContact` allows the user to modify an existing contact's details by searching for it and providing new information.
   - `displayContacts` displays all contacts in a tabular format, sorted by name.
   - `loadContacts` loads contacts from a file into the `contacts` map.
   - `saveContacts` saves contacts from the `contacts` map to a file.

7. File Path Constant:
   - The `FILE_PATH` constant stores the file path where the contacts will be saved and loaded from.

8. `main` Function:
   - The `main` function is the entry point of the program.
   - It starts by loading contacts from the file using `loadContacts`.
   - It then enters a loop to present the main menu to the user and handle user input.
   - Inside the loop, it calls the `displayMenu` function to show the menu options and prompts the user for a choice.
   - Based on the user's choice, the corresponding contact management function is called (e.g., `addContact`, `modifyContact`, etc.).
   - The loop continues until the user chooses to quit by selecting option 6.
   - Before quitting, the program saves the contacts to the file using `saveContacts` and displays a goodbye message.

9. Utility Functions:
   - `clearScreen` clears the console screen.
   - `isValidPhoneNumber` and `isValidEmailAddress` validate phone numbers and email addresses, respectively, using regular expressions.

The Contact Management System provides a user-friendly interface to interact with contacts, allowing the user to perform various operations efficiently. It ensures data integrity and provides functionalities like searching, adding, modifying, deleting, and displaying contacts.
