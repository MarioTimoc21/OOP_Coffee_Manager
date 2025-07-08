# ☕ OOP Coffee Manager (C++ Project)

**OOP Coffee Manager** is a modular C++ application designed to simulate the internal management of a coffee shop using Object-Oriented Programming principles. It covers product inventory, customer orders, employees, events, and daily reporting — all managed via a console-based interface.

---

## 📌 Features

- 📦 Product inventory management (stock, cost, price, quantity)
- 🧾 Order placement, tracking, and storage
- 👥 Employee scheduling and salary management
- 📅 Event planning (e.g., promotions, parties)
- 📊 Daily report generation
- 📁 Data persistence through CSV files
- 🧠 Clean separation of concerns using OOP (classes, destructors, modular structure)

---

## 🧱 Project Structure

| Component      | Description |
|----------------|-------------|
| `Product`      | Base class representing a drink or item (name, cost, price, quantity) |
| `Stock`        | Manages the inventory: add, remove, load products from file |
| `Order`        | Handles order creation, storing customer purchases and linking with stock |
| `Employee`     | Stores employee data such as name, role, working hours, and salary |
| `Event`        | Represents promotional or private events (date, type, cost) |
| `Reports`      | Generates daily summary reports based on all data |
| `Menu`         | CLI-based menu system that links all modules together |

Each component is implemented in its own `.cpp` file inside the `src/` folder, with headers in the `include/` directory.

---

## 🔧 How to Compile

This project uses a `Makefile` for compilation.

### 🔁 Option 1: Using Make
```bash
make
./Main
### 🔁 Option 2: Manual Compilation

```bash
g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o CoffeeManager
./CoffeeManager
```

---

### 💬 Sample Menu Output

```text
=== Main Menu ===

1. Handle Employees
2. Handle Products and Stock
3. Handle Orders
4. Handle Events
5. Get Report
6. Exit
```

---

### 📁 Data Files

All data is read from and written to `.csv` files. You can find or generate:

- `products.csv` – product list  
- `orders.csv` – list of all orders  
- `employees.csv` – employee database  
- `events.csv` – scheduled events  
- `report.csv` – daily summaries  

---

### 🧠 OOP Concepts Used

- Classes and Objects  
- Constructors & Destructors  
- Polymorphism & Encapsulation  
- File I/O and Persistence  
- Separation of Interface (`.h`) and Implementation (`.cpp`)  
- Pointers and Dynamic Memory Management  

---

### 🚀 Future Improvements

- Add graphical user interface (GUI) using Qt or SFML
- Use SQLite or JSON for better data persistence
- Implement role-based access (manager vs barista)
