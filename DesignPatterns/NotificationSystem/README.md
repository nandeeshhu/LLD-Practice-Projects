# 📢 Notification System — Design Pattern Project

## 📌 Problem Statement

Build a modular **Notification System** for an e-commerce platform using classic **Object-Oriented Design Patterns**. The system should:

- Send notifications via **Email**, **SMS**, or **Push**
- Support **runtime selection** of notification types
- Notify **multiple services** (like OrderService, InventoryService) when an order is placed
- Apply **optional decorations** to messages like emojis, footers, or urgency tags — **dynamically**
- Ensure **only one NotificationManager instance**
- Use **clean object creation logic** decoupled from business logic

---

## ✅ Features

- Dynamic strategy to choose notification type at runtime
- Observer mechanism to notify multiple backend services
- Singleton Notification Manager
- Decorators for emojis, urgency flags, and footers
- Factory for clean creation of notifications
- Easy-to-extend and SOLID-compliant architecture

---

## 🧠 Design Patterns Used

| Pattern      | Role                                                                 |
|--------------|----------------------------------------------------------------------|
| **Strategy** | Switch between Email/SMS/Push notifications at runtime               |
| **Singleton**| Ensures one global `NotificationManager`                             |
| **Observer** | Notify multiple backend services (Order, Inventory) when triggered   |
| **Decorator**| Dynamically attach features like emojis or urgency                   |
| **Factory**  | Create notification objects without exposing creation logic          |

---

## 🗂️ Folder Structure

NotificationSystem/
├── main.cpp # All class implementations and main
├── CMakeLists.txt # CMake build file
└── README.md # Project documentation (this file)


---

## ⚙️ How to Run (Using CLion / CMake)

1. Make sure your project root is part of your CMake build
2. Add the following to your main `CMakeLists.txt`:

    ```cmake
    add_subdirectory(DesignPatterns/NotificationSystem)
    ```

3. Inside `NotificationSystem/CMakeLists.txt`:

    ```cmake
    add_executable(NotificationSystem main.cpp)
    ```

4. Build and Run the target `NotificationSystem` from CLion or terminal.

---

## 🧪 Sample Output

```bash
Order Service received: [URGENT] 🎉 Your order has been placed. - Thank you for shopping!
Inventory Service received: [URGENT] 🎉 Your order has been placed. - Thank you for shopping!
📧 Email: [URGENT] 🎉 Your order has been placed. - Thank you for shopping!
```

🙌 Author
Nandeesh H U

GitHub: @nandeeshhu

📝 License
This project is under the MIT License.

---

✅ Let me know if you'd like:

- A version split into multiple files for larger projects  
- Diagrams added (UML or flowchart)  
- A zipped version of the folder structure  

Once you save this, you can stage and push it like this:

```bash
git add DesignPatterns/NotificationSystem/README.md
git commit -m "Added README for NotificationSystem project"
git push origin main

