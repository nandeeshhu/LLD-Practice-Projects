#include <iostream>
#include <vector>
using namespace std;

///////////////////////
// Message & Decorator
///////////////////////

class Message {
public:
    virtual string get() = 0;
    virtual ~Message() {}
};

class PlainMessage : public Message {
    string text;
public:
    PlainMessage(string msg): text(msg) {}
    string get() override {
        return text;
    }
};

class MessageDecorator : public Message {
protected:
    Message* base;
public:
    MessageDecorator(Message* msg): base(msg) {}
    virtual string get() override {
        return base->get();
    }
};

class EmojiDecorator : public MessageDecorator {
    string emoji;
public:
    EmojiDecorator(Message* msg, string em): MessageDecorator(msg), emoji(em) {}
    string get() override {
        return emoji + " " + base->get();
    }
};

class FooterDecorator : public MessageDecorator {
    string footer;
public:
    FooterDecorator(Message* msg, string ft): MessageDecorator(msg), footer(ft) {}
    string get() override {
        return base->get() + " " + footer;
    }
};

class UrgentDecorator : public MessageDecorator {
public:
    UrgentDecorator(Message* msg): MessageDecorator(msg) {}
    string get() override {
        return "[URGENT] " + base->get();
    }
};

////////////////////////
// Observer - Services
////////////////////////

class Services {
public:
    virtual void update(Message* message) = 0;
    virtual ~Services() {}
};

class OrderService: public Services {
public:
    void update(Message* message) override {
        cout << "Order Service received: " << message->get() << endl;
    }
};

class InventoryService: public Services {
public:
    void update(Message* message) override {
        cout << "Inventory Service received: " << message->get() << endl;
    }
};

//////////////////////////
// Strategy - Notifications
//////////////////////////

class Notification {
public:
    virtual void send(Message* message) = 0;
    virtual ~Notification() {}
};

class EmailNotification: public Notification {
public:
    void send(Message* message) override {
        cout << "📧 Email: " << message->get() << endl;
    }
};

class SMSNotification: public Notification {
public:
    void send(Message* message) override {
        cout << "📩 SMS: " << message->get() << endl;
    }
};

class PushNotification: public Notification {
public:
    void send(Message* message) override {
        cout << "📲 Push: " << message->get() << endl;
    }
};

//////////////////////////
// Composite + Observer
//////////////////////////

class NewOrderNotification: public Notification {
    Notification* notification;
    vector<Services*> services = { new OrderService(), new InventoryService() };
public:
    NewOrderNotification(Notification* n): notification(n) {}

    void send(Message* message) override {
        for (auto service : services) {
            service->update(message);
        }
        notification->send(message);
    }

    ~NewOrderNotification() {
        for (auto s : services) delete s;
        delete notification;
    }
};

//////////////////////////
// Factory - NotificationFactory
//////////////////////////

class NotificationFactory {
public:
    static Notification* create(string type) {
        if (type == "SMS") return new SMSNotification();
        if (type == "Email") return new EmailNotification();
        return new PushNotification(); // default
    }
};

//////////////////////////
// Singleton - NotificationManager
//////////////////////////

class NotificationManager {
    static NotificationManager* instance;
    NotificationManager() {}

public:
    static NotificationManager* getInstance() {
        if (!instance)
            instance = new NotificationManager();
        return instance;
    }

    void sendNotification(string msg, string emoji = "", string foot = "", bool urgent = false, string notif = "Push") {
        Message* message = new PlainMessage(msg);
        if (!emoji.empty())
            message = new EmojiDecorator(message, emoji);
        if (!foot.empty())
            message = new FooterDecorator(message, foot);
        if (urgent)
            message = new UrgentDecorator(message);

        Notification* notification = NotificationFactory::create(notif);
        NewOrderNotification* orderNotif = new NewOrderNotification(notification);
        orderNotif->send(message);

        delete orderNotif;
        delete message;
    }
};

NotificationManager* NotificationManager::instance = nullptr;

//////////////////////////
// Main
//////////////////////////

int main() {
    auto manager = NotificationManager::getInstance();

    manager->sendNotification("Your order has been placed.",
                              "🎉",
                              "- Thank you for shopping!",
                              true,
                              "Email");

    return 0;
}
