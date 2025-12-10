## 👨‍💻 Who I Am

I am **Ali Mohamed Al-Sharqawi**, a C++ Developer specializing in building **high-fidelity, production-style systems** with a strong focus on **OOP architecture**, **modularity**, and **enterprise-grade workflow design**.

My work revolves around transforming raw ideas into **scalable**, **cleanly-engineered**, and **architecture-driven software**—the kind of systems that reflect real-world banking logic, structured data flow, and disciplined system boundaries.

I enjoy designing **multi-layered applications**, crafting **domain-driven modules**, and building software that feels like an actual product rather than a coding exercise.  
Every project I create is engineered with long-term maintainability, clarity, and system-level thinking in mind.

**This repository marks a major milestone in my engineering journey.**  
I fully completed this project on **30 / 11 / 2025** with the goal of building **practical, production-style experience** during the first semester of my second year at computer since.

It was designed as a **high-fidelity simulation of a real banking system**, developed with strict adherence to **SOLID principles**, **enterprise-grade modularity**, and a clean, boundary-driven architecture. Every module, workflow, and data path was engineered to behave like a real-world system — not a demo.

Throughout development, I focused on crafting a **scalable, extensible, and maintainable architecture**, emphasizing separation of concerns, consistent design patterns, reusable components, and long-term system reliability.

This project reflects my commitment to writing software that is not only functional, but **architecturally disciplined**, **workflow-centric**, and aligned with modern engineering standards.

# 🏦 **SmartBank System — ATM & Banking Management**

A fully functional **C++ banking system** featuring a powerful **Admin Dashboard**, an intuitive **ATM Client Interface**, complete **role-based access control**, comprehensive **transaction logging**, and seamless **session tracking**.

Built on top of a meticulously engineered, **high-fidelity modular architecture** grounded in **enterprise-hardened OOP principles** — delivering unmatched **clarity**, **extensibility**, and **long-term system reliability**.

This project is designed as a **portfolio-grade system** suitable for **GitHub**, **LinkedIn**, **technical interviews**, and high-end **personal branding**.

---

## 📖 Description

**SmartBank System** is an end-to-end, production-style banking application built in **C++**, engineered to accurately simulate real-world banking operations while showcasing high-fidelity architecture, clean OOP design, secure data handling, and fully structured workflow management.

The system provides **four entry points**, each representing a real banking scenario:

1. **Admin Account Registration**
2. **Client Account Registration**
3. **Admin Dashboard Login**
4. **Client ATM Login**

### 🛡️ Admin Workflow

Admins operate through a powerful, permission-driven dashboard where **each admin has a custom set of privileges**. A super-admin can access everything, including:

- Full **CRUD operations** on all clients  
- Full **CRUD operations** on other admins  
- Viewing **client session logs** (login / logout)  
- Viewing **admin session logs**  
- Viewing **their own session history**  
- Performing financial actions on client accounts (Deposit, Withdraw, Transfer)  
- Tracking **every admin action** through a unified transaction & activity log  

The architecture ensures strict **role-based access control**, guaranteeing that each admin sees only what they are authorized to manage.

### 💳 Client (ATM) Workflow

Clients interact with an intuitive ATM interface offering real banking features:

- **Quick Withdraw**  
- **Standard Withdraw**  
- **Deposit**  
- **Balance Inquiry**  
- **Money Transfer**  
- **Change PIN**  
- A complete **transaction history**, showing who sent money, who received, and all withdrawals/deposits.

Each user action is securely logged, ensuring full traceability and realistic financial record-keeping.

### 🧱 Architectural Highlights

The system is built with:

- A **modular, high-fidelity OOP architecture**
- Clean **separation of concerns** across all layers
- **Persistent data storage** for admins, clients, sessions, and transactions
- A workflow designed to reflect **real banking systems**, not demo-level logic

This makes SmartBank a **portfolio-grade system** ideal for GitHub, LinkedIn, technical interviews, and personal branding—showcasing deep understanding of architecture, workflow design, and enterprise-level system thinking.

---

## ✨ Features

### 🔐 Security & User Management

- Robust **Role-Based Access Control** for Admins & Clients.
- Fine-grained **permission system** implemented using efficient **bitwise flags**.
- Secure authentication through **PIN** (clients) and **passwords** (admins).
- Intelligent login handling with session recording and validation.

### 🛂 Admin Capabilities

- Full **CRUD operations** for all clients.
- Full **CRUD operations** for all admins, including permission assignment.
- View complete **Client Session Logs** (login/logout).
- View **Admin Session Logs** and personal activity history.
- Perform client-side banking actions (deposit, withdraw, transfer) with full traceability.

### 💳 Client (ATM) Operations

- **Quick Withdraw** and standard withdraw options.
- **Deposit**, **Balance Inquiry**, and **Money Transfer**.
- Change PIN securely.
- A complete **transaction history**, showing transfers, withdrawals, deposits, and received funds.

### 💵 Banking Transaction System

- Deposit & Withdraw (ATM + Admin execution).
- Transfer between accounts with linked **TRANSFER_IN / TRANSFER_OUT** events.
- Automatic creation of detailed **transaction logs**.
- Global **total balances** calculation across all clients.

### 💱 Currency Management (Admin)

- Add, update, delete supported currencies.
- Precise currency lookup.
- Real-time style **currency exchange** with conversion calculations.

### 📜 Unified Logging & Audit Trail

- Centralized **Transaction Logger** for all money operations.
- Full **Admin Session Log**.
- Full **Client Session Log**.
- Complete **transfer history** with sender/receiver tracking.

### 🖥️ Console-Based UI

- Hierarchical, clean, and modular menu system.
- Crystal-clear separation between **Admin Dashboard** and **ATM Interface**.
- Smooth screen navigation with a professional command-line user experience.

---

### 🧩 Architectural Principles

The **SmartBank System** is engineered around a set of high-fidelity architectural principles that ensure long-term stability, clarity, and scalability.  
Every module, service, and workflow follows strict guidelines to keep the system clean, predictable, and production-ready.

#### **1. Separation of Concerns**

Each layer handles a single responsibility:

- UI → Interaction & navigation  
- Controllers → Workflow coordination  
- Services → Business rules & domain logic  
- Repositories → Data access  
- Persistence → Storage layer  

This creates a system that is easier to extend, debug, and refactor.

#### **2. Modular, Boundary-Driven Design**

Every component is isolated behind clear boundaries.  
Admin logic, ATM logic, transactions, sessions, and currencies each reside in independent modules — preventing cross-contamination of responsibilities.

#### **3. Enterprise-Style OOP Discipline**

The system applies:

- Encapsulation  
- Abstraction  
- Inheritance (where appropriate)  
- Polymorphism  

to create maintainable, reusable, and scalable code.

#### **4. Workflow-First Architecture**

Core flows (Login, CRUD, Transactions, ATM operations) are treated as **first-class system components**.  
Each workflow is modeled to reflect the behavior of real banking systems.

#### **5. Persistent Data Integrity**

All data — clients, admins, transactions, sessions, currencies — is stored through structured, controllable repository layers, creating a clean separation from business logic.

#### **6. Full Auditability**

Every admin action, ATM interaction, session lifecycle, and financial event is tracked by a unified logging system — ensuring transparency and realistic bank-grade traceability.

#### **7. Extensibility by Design**

New features (e.g., loan system, online banking, card management) can be added with zero friction thanks to:

- Independent modules  
- Well-defined interfaces  
- Consistent design patterns  

This system is intentionally built to grow without breaking
---

## 📂 Project Structure (Overview)

```
SmartBank-System/
| 
|
+---_README.md                  # This file
|
+---📸 Screenshots.PDF          # All Project main Screens
|
+---core                        # business logic leyar
|       clsAdmin.h
|       clsBankClient.h
|       clsCurrency.h
|       clsPerson.h
|       clsTransactionLogger.h
|
|      
+---data                        # Storage data
|       Admins.text
|       AdminsSessionLog.txt
|       AllTransactions.txt
|       Clients.txt
|       ClientsSessionLog.txt
|       Currencies.txt
|       
+---src
|       SmartBank System & ATM.cpp
|       SmartBank System & ATM.exe
|       
+---utils                      # Helper utilities
|       clsDate.h
|       clsInputValidate.h
|       clsString.h
|       clsUtil.h
|       
\---Welcome_Screen                  # UI Modules & Screens
    |   clsStartUpBankSystem.h
    |   
    +---base_screen             # Base UI classes
    |
    |      Global.h           ==> Store Current (Admin/Client) Session
    |      clsScreen.h        ==> All project Screen inherit it
    |       
    \---startup
        +---1)Login_As_Admin
        |   |   clsAdminLoginScreen.h
        |   |   clsAdminDashboard_Menu.h
        |   |   
        |   \---Admin_Dashboard_Screens
        |       +---Manage_Clients_Menu
        |       |   |   clsManageClientsScreen.h
        |       |   |   
        |       |   \---Manage_Clients_Screens
        |       |           clsClientsListScreen.h
        |       |           clsAddNewClientScreen.h
        |       |           clsUpdateClientScreen.h
        |       |           clsFindClientScreen.h
        |       |           clsDeleteClientScreen.h
        |       |           clsTotalBalancesScreen.h
        |       |           clsClientsSessionLogScreen.h
        |       |           
        |       +---Manage_Admins_Menu
        |       |   |   clsManageAdminMenu.h
        |       |   |   
        |       |   \---Manage_Admins_Screens
        |       |           clsListAdminsScreen.h
        |       |           clsAddNewAdminScreen.h
        |       |           clsFindAdminScreen.h
        |       |           clsDeleteAdminScreen.h
        |       |           clsUpdateAdminScreen.h
        |       |           clsAdminsSessionLogScreen.h
        |       |           clsCurrentAdminSessionScreen.h
        |       |           
        |       +---Currency_Menu
        |       |   |   clsCurrencyMenu.h
        |       |   |   
        |       |   \---Currency_Screens
        |       |           clsAddNewCurrencyScreen.h
        |       |           clsCurrencyConverterScreen.h
        |       |           clsDeleteCurrencyScreen.h
        |       |           clsFindCurrencyScreen.h
        |       |           clsListCurrencysScreen.h
        |       |           clsUpdateCurrencyScreen.h
        |       |           
        |       \---Transactions_Menu
        |           |   clsTransactionsMenu.h
        |           |   
        |           \---Transactions_Screens
        |                   clsDepositScreen.h
        |                   clsTransferHistoryScreen.h
        |                   clsTransferScreen.h
        |                   clsWithdrawScreen.h
        |                   
        +---2)ATM
        |   |   clsClientLoginScreen.h
        |   |   clsClientDashboard_Menu.h
        |   |   
        |   \---ATM_Screens
        |           clsATMQuickWithdrawScreen.h
        |           clsATMNormalWithdrawScreen.h
        |           clsATMDepositScreen.h
        |           clsATMCheckBalanceScreen.h
        |           clsCurrentClientSessionScreen.h
        |           clsATMTransferHistoryScreen.h
        |           clsATMTransferScreen.h
        |           clsATMChangePINScreen.h
        |           
        +---3)Creat_Admin_Account
        |       clsCreatAdminAccout.h  =====> Go to clsAddNewAdminScreen.h
        |       
        \---4)Creat_Client_Account
                clsCreatClientAccount.h   =====> Go to clsAddNewClientScreen.h
---

## 🚀 How to Run the Project

(simply)jsut Download SmartBankSystem.exe

### 🖥️ Requirements
- C++ Compiler (g++, clang, MSVC)
- Windows / Linux / macOS terminal

### ▶️ Compilation (g++)
```bash
g++ "SmartBank System & ATM.cpp" -o SmartBankSystem
```

### ▶️ Run

```bash
./SmartBankSystem        # Linux / macOS
SmartBankSystem.exe      # Windows
```

Or simply open the project in **Visual Studio** and run/build.

---

## 🛠️ Technical Highlights

### 🔹 Object‑Oriented Architecture

- Inheritance hierarchy using `clsPerson → clsAdmin / clsBankClient`
- Encapsulation of all domain logic
- Polymorphic screens & reusable modules

### 🔹 Permission System

- Implemented using **bitwise flags** to allow flexible combinations of admin capabilities.

### 🔹 Unified Transaction Logger

A single logger handles:

- Deposits
- Withdrawals
- Transfers
- ATM operations
- Admin operations (optional)

### 🔹 Session Management

- Full login/logout history
- Session duration calculation
- Admin & client independent logs

### 🔹 File‑Based Persistence

All objects are stored in:

- Clients.txt
- Admins.text
- Currencies.txt
- AllTransactions.txt
- Session Log files

This allows transparency and easier debugging.

### 🔹 Input Validation Tools

- `clsInputValidate`
- `clsString`
- `clsDate`

These ensure cleaner, safer user input.

---

## 🎓 What I Learned

- Designing multi‑module systems in C++
- Applying OOP principles in real project structure
- Implementing secure login and role‑based access
- Managing data persistence using text files
- Handling financial operations safely and consistently
- Designing layered architecture similar to enterprise systems
- Building a structured console UI with dozens of screens
- Implementing session tracking and unified logging

---

## 📘 Also I have learned

- **Role‑Based Access Control (RBAC)**
- **Unified Transaction Logger**
- **Session Management**
- **File‑Based Persistence Layer**
- **Separation of Concerns**
- **Modular Architecture**
- **SOLID‑Oriented Design**
- **Bitwise Permission Flags**
- **Business Logic Layer**
- **Console UI Framework**

---

## 🔮 Future Enhancements

- Migrate to SQLite / MySQL database ===> I used .text f ile to do every this from
                                          scratch to learn prefectly

- Add GUI (Qt / wxWidgets / SFML)
- Implement client‑server architecture over network
- Add AES‑256 encryption for sensitive data
- Export reports to PDF
- Add email/sms notifications for transactions
- Multi‑language support

---
