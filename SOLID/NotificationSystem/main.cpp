/*
🧪 SOLID-Only Design Problem
📝 Problem Statement:
You’re building a notification system that sends alerts to users via Email, SMS, and Push Notification.
Right now, your system needs to:
Allow different types of notifications (Email, SMS, Push).
Allow adding new types of notifications in the future without changing the existing code.
Allow sending multiple notifications (e.g., Email + SMS together).
Ensure your high-level logic doesn't depend on specific notification channels.

Follow all five SOLID principles.

🧩 Requirements:
1. You should be able to do something like:
Notifier* notifier = new MultiNotifier({new EmailNotifier(), new SMSNotifier()});
notifier->send("Account created!");
2. Tomorrow, if a new notification type like WhatsAppNotifier is introduced, it should require no modification in existing classes.
3. You should avoid code duplication for common logic like logging or retrying failed sends.
4. The system should be testable with mock notifiers during unit testing.


✅ What You Need to Show:
Use Interface Segregation to make sure classes don’t depend on unused methods.
Apply Open/Closed Principle to make it extendable without modifying existing code.
Apply Single Responsibility Principle — no class should do too many things.
Apply Liskov Substitution — you should be able to replace Notifier* with any subclass.
Use Dependency Inversion — high-level logic should depend on INotifier interface, not concrete classes.

 */

#include <iostream>
#include <vector>
using namespace std;

class Notifier {
public:
    virtual void send(string message) = 0;
};

class EmailNotifier: public Notifier {
    public:
    void send(string message) override {
        cout<<"Email Notification: "<<message<<endl;
    }
};

class SMSNotifier: public Notifier {
    public:
    void send(string message) override {
        cout<<"SMS Notification: "<<message<<endl;
    }
};

class PushNotifier: public Notifier {
    public:
    void send(string message) override {
        cout<<"Push Notification: "<<message<<endl;
    }
};

// Extending to Whatsapp
class WhatsappNotifier: public Notifier {
    public:
    void send(string message) override {
        cout<<"Whatsapp Notification: "<<message<<endl;
    }
};
class MultiNotifier: public Notifier {
    vector<Notifier*> notifiers;
public:
    MultiNotifier(vector<Notifier*> notifiers) {
        this->notifiers = notifiers;
    }

    void send(string message) {
        for (Notifier* notifier : notifiers) {
            notifier->send(message);
        }
    }
    ~MultiNotifier() {
        for (Notifier* notifier : notifiers) {
            delete notifier;
        }
    }
};

int main() {
    Notifier* notifier = new MultiNotifier({new EmailNotifier(), new SMSNotifier()});
    notifier->send("Account created!");
    delete notifier;

    Notifier* notifier2 = new EmailNotifier();
    Notifier* notifier3 = new PushNotifier();
    notifier2->send("New offer");
    notifier3->send("Order placed");

    delete notifier2;
    delete notifier3;
    Notifier* notifier4 = new WhatsappNotifier();
    notifier4->send("Welcome to our app");
    delete notifier4;
    return 0;
}
