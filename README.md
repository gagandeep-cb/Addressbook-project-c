# Address Book Management System (C)

## Overview

The Address Book Management System is a command-line application developed using the C programming language. This project allows users to store and manage contact information efficiently.

The application provides features such as creating, searching, editing, deleting, saving, and loading contacts.

---

## Features

* Add a new contact
* Search for a contact
* Edit contact details
* Delete a contact
* Display all contacts
* Save contacts to a file
* Load contacts from a file
* Validate names, phone numbers, and email addresses

---

## Technologies Used

* C Programming
* Data Structures
* File Handling
* Linux
* Git and GitHub

---

## Project Structure

```text
AddressBook-NewDesign
│
├── main.c
├── contact.c
├── contact.h
├── file.c
├── file.h
├── populate.c
├── Makefile
└── README.md
```

---

## Validation Rules

### Name Validation

* Names must contain only alphabetic characters.
* Special characters and numbers are not allowed.

### Phone Number Validation

* The phone number must contain exactly ten digits.
* Duplicate phone numbers are not allowed.

### Email Validation

* The email address must contain exactly one '@' symbol.
* The email address must contain at least one '.' character.
* Consecutive dots are not allowed.
* Duplicate email addresses are not allowed.

---

## Functions Implemented

* createContact()
* searchContact()
* editContact()
* deleteContact()
* listContacts()
* saveContactsToFile()
* loadContactsFromFile()

---

## How to Run the Project

### Compile the program

```bash
gcc *.c -o addressbook
```

### Execute the program

```bash
./addressbook
```

---

## Author

**Gagandeep C. Banakar**
* Embedded Systems Intern at Emertxe
