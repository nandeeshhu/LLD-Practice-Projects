# 🧱 LLD Practice Projects

This repository contains clean and modular **Low-Level Design (LLD)** implementations based on real-world interview patterns.  
Each project is built using **SOLID principles** and demonstrates good object-oriented design.

---

## 📂 Projects

### 🔹 1. [SOLID Notification System](./SOLID/NotificationSystem)

Implements Email, SMS, WhatsApp, and Push notifications in a pluggable, SOLID-compliant way.

- **Principles Used:** SRP, OCP, LSP, ISP, DIP  
- **Concepts:** Abstraction, Interface-based design, Extensibility

---

### 🔹 2. [Parking Lot System](./ParkingLot)

Implements a basic object-oriented Parking System using good class design, enums, and strategies.

- **Concepts:** Class hierarchy, encapsulation, modularity  
- **Techniques:** Enums, vehicle types, and slot logic

---

### 🔹 3. [Notification System — Design Patterns](./DesignPatterns/NotificationSystem)

Implements a complete Notification System using core design patterns:

- **Design Patterns Used:** Strategy, Observer, Singleton, Decorator, Factory  
- **Features:** Dynamic channel switching, observer-based service updates, runtime message decoration, singleton notification manager, decoupled creation logic

---

## 🚀 How to Run

All projects are written in **C++** and tested using **CLion** IDE.  
You can also compile individual `main.cpp` files manually using:

```bash
g++ main.cpp -o output && ./output
