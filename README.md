# ATM System Project – Console ATM Banking System (C++)

This repository contains an **ATM System Project**, a **console-based ATM simulation** written in **C++**, allowing bank clients to perform essential banking operations after secure authentication.

The project represents a **client-side ATM interface**, focusing on usability, transaction accuracy, and file-based data persistence.

It is part of the practical learning path of  
**Cplusplus Problems V3**, emphasizing real-world banking workflows and clean procedural design.

---

## 📂 Project Overview
The ATM system simulates a real ATM machine where clients can log in using:
- **Account Number**
- **PIN Code**

After successful authentication, clients can perform multiple banking operations through a menu-driven interface.

Client data is stored persistently using a text file:
- **ClientsRecords.txt**

---

## 🧱 Core Features

### 🔹 Authentication System
- Secure login using account number and PIN
- Continuous validation until correct credentials are entered
- Loads client data directly from file

### 🔹 ATM Operations
- Quick Withdraw (predefined amounts)
- Normal Withdraw (custom amounts – multiples of 5)
- Deposit money
- Check account balance
- Logout safely from the system

---

## ⚡ Quick Withdraw Options
Clients can instantly withdraw predefined amounts:
- 20, 50, 100, 200
- 400, 600, 800, 1000

---

## 🧾 Data Persistence
- Client data is stored in **ClientsRecords.txt**
- File format uses a custom delimiter (`#//#`)
- Data flow:
  - Load data from file
  - Modify in memory
  - Rewrite updated data back to file

📌 **Note:**  
This repository includes a ready-to-use **ClientsRecords.txt** file,  
which you can **copy directly** and use without modification.

---

## 🛠️ Technologies Used
- **Language:** C++
- **File Handling:** `<fstream>`
- **Data Structures:** `struct`, `vector`
- **Enums:** Menu & operation handling
- **Formatting:** `<iomanip>`
- **Standard Libraries:** `<iostream>`, `<string>`, `<cctype>`

---

## 📐 System Design
- Divide & Conquer approach
- Clear separation between:
  - Logic functions
  - UI / screen functions
- Global current-client session handling
- Loop-based menu navigation
- Safe synchronization between memory and file data

---

## 🎯 Learning Objectives
This project helps reinforce:

- File-based data management
- Building authentication systems
- Designing ATM-style user interfaces
- Applying modular programming principles
- Writing clean, readable, and maintainable C++ code

---

## 🧪 Recommended Development Environment
- **Visual Studio (Windows)**

---

## 📌 Important Notes
- This project is **educational**, not production-ready
- No database is used (file-based storage only)
- Ensure **ClientsRecords.txt** exists in the same directory

---

## 🙏 Acknowledgment
Special thanks to:
- **Professor Abouhodhoud**
- **Programming Advices**
- **Berry 🍓** – Thank you for your encouragement and support.

---

⭐ If you find this project helpful, feel free to star the repository and use it as a reference for building advanced C++ console applications.
