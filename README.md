# Address Book Management System

## 📌 Overview


The **Address Book Management System** is a command-line application developed using the **C programming language**. This project allows users to store and manage contact information efficiently.

It allows users to create, search, edit, delete, and display contacts. The project also uses **file handling** to save contacts into a CSV file and load them when the program starts.

---

## 🚀 Features

* Create a new contact
* Validate contact name
* Validate 10-digit phone number
* Prevent duplicate phone numbers
* Validate email address
* Prevent duplicate email addresses
* Search contacts by:

  * Name
  * Phone number
  * Email
* Search name using substring matching
* Select a contact when multiple names match
* Edit contact:

  * Name
  * Phone number
  * Email
  * All details
* Delete contacts
* Display all contacts
* Sort contacts alphabetically by name
* Save contacts to CSV file
* Load contacts from CSV file
* Loading animation
* Saving animation

---

## 🛠️ Technologies Used

* **C Programming**
* **Structures**
* **Pointers**
* **Arrays**
* **Strings**
* **Functions**
* **File Handling**
* **Git & GitHub**
* **GCC Compiler**

---

## 📂 Project Structure

```text
AddressBook-NewDesign/
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── contacts.csv
├── contacts.txt
└── README.md
```

---

## 📋 Contact Structure

Each contact contains:

```c
typedef struct
{
    char name[50];
    char phone[11];
    char email[50];
} Contact;
```

The address book stores up to 100 contacts.

---

## 🔍 Search Functionality

The project supports three search methods:

### Search by Name

Name substring matching is supported.

For example, searching:

```text
gagan
```

can find contacts such as:

```text
Gagan
Gagandeep
Gagan Kumar
```

If multiple contacts are found, the user can select the required contact.

### Search by Phone

The complete phone number is searched.

### Search by Email

The complete email address is searched.

---

## ✏️ Edit Contact

Users can edit:

```text
1. Name
2. Phone
3. Email
4. All details
```

The selected contact is identified using its array index.

---

## 🗑️ Delete Contact

When a contact is deleted, the contacts after it are shifted one position to the left.

Example:

```text
Before:
0  Gagan
1  Rahul
2  Kiran
3  Ajay

Delete Rahul:

After:
0  Gagan
1  Kiran
2  Ajay
```

The `contactCount` is then decreased by one.

---

## 💾 File Handling

Contacts are stored in:

```text
contacts.csv
```

Example:

```text
#10
Alice Smith,0987654321,alice@example.com
Bob Johnson,1112223333,bob@company.com
Carol White,4445556666,carol@company.com
```

### Save

The `saveContactsToFile()` function writes contacts from the AddressBook to the CSV file.

### Load

The `loadContactsFromFile()` function reads contacts from the CSV file when the application starts.

---

## ▶️ How to Compile

Using GCC:

```bash
gcc -Wall -Wextra main.c contact.c file.c -o addressbook
```

---

## ▶️ How to Run

### Linux / WSL

```bash
gcc *.c
./a.out
```

### Windows PowerShell

```powershell
.\addressbook.exe
```

---

## 🖥️ Main Menu

```text
------------------------------------
|           ADDRESSBOOK MENU       |
------------------------------------
|   1   |   CREATE CONTACT         |
|   2   |   SEARCH CONTACT         |
|   3   |   EDIT CONTACT           |
|   4   |   DELETE CONTACT         |
|   5   |   LIST ALL CONTACTS      |
|   6   |   SAVE AND EXIT          |
|   7   |   EXIT                   |
------------------------------------
```

---

## 🧠 Concepts Practiced

This project helped in practicing:

* C structures
* Structure pointers
* Arrays of structures
* String handling
* `strcmp()`
* `strcpy()`
* `strstr()`
* Loops
* Conditional statements
* Functions
* Function return values
* Array indexing
* Bubble sort
* File I/O
* CSV file handling
* Input validation
* Git and GitHub

---

## 👨‍💻 Author

**Gagandeep C. Banakar**

---

## 🔮 Future Improvements

- Add a graphical user interface (GUI)
- Add password/user authentication
- Add contact groups such as Family, Friends, and Work
- Add backup and restore functionality
- Add import/export support for other formats
