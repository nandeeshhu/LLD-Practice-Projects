# 🅿️ Parking Lot Management System (LLD in C++)

This is a Low-Level Design (LLD) implementation of a **Parking Lot Management System** in **C++**, simulating a real-world parking infrastructure.

It supports:
- Multiple vehicle types
- Billing per day
- Ticket generation
- Spot allocation logic with fallback
- Search functionality
- Singleton pattern usage

---

## 📌 Features

- 🚗 **Vehicle Parking & Unparking**
  - Supports 2W, 3W, 4W, and heavy 4W.
  - Automatically assigns nearest available slot.
  - Fallback: if no slot available for that type, tries next larger one.

- 🎫 **Ticket Generation**
  - Ticket includes vehicle number, timestamp, and allocated spot.
  - Publicly accessible ticket info.

- 🧾 **Billing System**
  - Charges based on vehicle type and total full days parked.
  - Minimum 1 day is charged for any parking.

- 🔎 **Vehicle Search**
  - Given a plate number, return the current parking spot (if parked).
  - Returns `Null` if not found.

- 🧠 **Singleton Pattern**
  - Only one instance of `ParkingLot` exists in the entire system.

- 🧪 **Simulated Testing**
  - Parks 100 vehicles of varying types.
  - Unparks 30 at random and prints total cost.
  - Searches 10 parked vehicles and 3 non-parked vehicles.

---

## 📦 Class Design Overview

- `Vehicle`  
  Holds vehicle information like number, color, and type.

- `Ticket`  
  Stores entry time, plate number, and parking spot.

- `ParkingLot`  
  Singleton class managing parking slots, billing, ticketing, and search.

---

## 🧱 Technologies Used

- Language: **C++ (C++17)**
- Libraries: `<ctime>`, `<unordered_map>`, `<queue>`, `<iomanip>`, `<random>`, `<sstream>`

---

## 🖥️ How to Compile and Run

### Compile

```bash
g++ -std=c++17 main.cpp -o parking-lot
