# 🧠 SOLID-Based Notification System in C++

## 📌 Description

This project demonstrates a **notification delivery system** built using only the **SOLID principles** of object-oriented design. It allows sending alerts via different channels like **Email**, **SMS**, **Push Notification**, and **WhatsApp**, and is designed to be easily extendable, testable, and maintainable.

The core goal is to showcase how to:

- Apply the **Single Responsibility Principle** by separating responsibilities across different classes.
- Use the **Open/Closed Principle** to allow new notification types without modifying existing code.
- Maintain **Liskov Substitution** by ensuring all notifiers can be substituted safely.
- Follow the **Interface Segregation Principle** via minimal, focused interfaces.
- Implement the **Dependency Inversion Principle** so high-level modules rely on abstractions, not concrete implementations.

---

## ✅ Features

- Pluggable notification types: Email, SMS, Push, WhatsApp
- Combines multiple notification channels using `MultiNotifier`
- Fully interface-driven and dependency-inverted
- Easy to extend (e.g., add TelegramNotifier or SlackNotifier)
- Demonstrates real-world usage of all SOLID principles

---

## 📂 File Overview

- `main.cpp` — Demonstrates usage of all notifiers and system behavior

> (In a modular version, you might split each class into its own `.h`/`.cpp` pair)

---

## 🛠️ Technologies Used

- **C++**
- **CLion**
- **Git & GitHub**

---

## 🚀 Sample Usage

```cpp
Notifier* notifier = new MultiNotifier({
    new EmailNotifier(),
    new SMSNotifier(),
    new WhatsappNotifier()
});
notifier->send("Welcome to our app!");
delete notifier;
```
---
🔒 License
This project is for learning and demonstration purposes only.
You may fork, reuse, or adapt this code for educational or personal use.
For any commercial usage or redistribution, please provide appropriate credit to the original author.
