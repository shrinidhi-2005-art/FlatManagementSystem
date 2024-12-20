
# Flat Payment Management System

A modular **C project** for managing flat bookings and payments for a construction company. This project features a menu-driven interface and leverages file handling for data persistence.

---

## 📖 Overview

This project allows users to:
- View flat details.
- Book new flats.
- Manage payment records for booked flats.
- Display booked and available flats.

With **data persistence** using `data.csv`, this program ensures that updates are saved and available for future use.

---

## 🚀 How to Use

### Compile the Program
```bash
gcc -o main dsa.c functions.c -lm
```

### Run the Program
- **Linux**:
  ```bash
  ./main
  ```
- **Windows**:
  ```cmd
  main
  ```

---

## 🛠 Features

### Menu Options

1. **View Flat Info**
   Displays detailed information about each flat, including size, cost, and payment status.

2. **Book a New Flat**
   Allows users to book available flats and updates the data accordingly.

3. **List Booked Flats**
   Displays a list of all flats that have already been booked.

4. **List Available Flats**
   Shows all flats that are still available for booking.

5. **Update Payment of a Flat**
   Updates the payment status for a booked flat.

6. **Save and Logout**
   Saves all changes to `data.csv` and exits the program.

---

## 📂 Project Structure

- **dsa.c**: Contains the main logic and menu implementation.
- **functions.c**: Implements helper functions like booking, payment update, etc.
- **functions.h**: Header file with function declarations and necessary macros.
- **flats.h**: Contains the data structure for flat information.
- **data.csv**: Stores flat information persistently.
- **dataCopy.csv**: A backup of the flat data.

---

## 📦 Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/dizziedbliss/FlatManagementSystem.git
   ```
2. Navigate to the project directory:
   ```bash
   cd FlatManagementSystem
   ```
3. Compile and run the program (commands above).

---

## 🌟 Features in Detail

- **Persistent Storage**: Changes are saved in `data.csv` for continuity.
- **Backup Support**: A `dataCopy.csv` file ensures data is not lost.
- **Easy Navigation**: Intuitive menu-driven interface.
- **Data Modularity**: Data is managed using structures (`flats.h`).

---

## 🛠 Tools and Technologies

- **Language**: C
- **Compiler**: GCC
- **Libraries**: `<stdio.h>`, `<stdlib.h>`, `<string.h>`

---

## 📜 Contribute (or just say "Hi" 😄)
This project is open for contributions, ideas, or just random comments (even if they’re about how cool flat booking systems are). You’re welcome to:

- Open an issue if you find a bug
- Fork the repo and create a PR with a fix or enhancement
- Suggest new features (like adding an AI to predict the best flats to book based on your preferences... who knows?)
- Share your thoughts in the Discussions (or just say "hi," we’re friendly)

---

## 📞 Contact

**Max!!**
- GitHub: [@dizziedbliss](https://github.com/dizziedbliss)
---

## 💡 Future Enhancements

- Add error handling for invalid inputs.
- Implement more robust file-handling techniques.
- Add features like:
  - Sorting flats by price or size.
  - Generating payment reports.
  - Advanced search filters for flats.
