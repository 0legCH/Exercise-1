#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

class Phone {
protected:
    string name;
    string brand;
    double price;
public:
    Phone(string n, string b, double p) : name(n), brand(b), price(p) {}
    virtual ~Phone() {}

    string getName() const { return name; }
    string getBrand() const { return brand; }
    double getPrice() const { return price; }
};

class MobilePhone : public Phone {
private:
    string color;
    int memory;
public:
    MobilePhone(string n, string b, double p, string c, int m)
        : Phone(n, b, p), color(c), memory(m) {}

    string getColor() const { return color; }
    int getMemory() const { return memory; }
};

class RadioPhone : public Phone {
private:
    double range;
    bool answeringMachine;
public:
    RadioPhone(string n, string b, double p, double r, bool a)
        : Phone(n, b, p), range(r), answeringMachine(a) {}

    double getRange() const { return range; }
    bool hasAnsweringMachine() const { return answeringMachine; }
};

int main() {
    const int MAX_PHONES = 100;
    Phone* phones[MAX_PHONES];
    int phoneCount = 0;

   
    ifstream file1("phones1.txt");
    string name, brand, type;
    double price;
    int memory;
    string color;
    double range;
    bool answeringMachine;
    while (file1 >> name >> brand >> type >> price) {
        if (type == "mobile") {
            file1 >> color >> memory;
            phones[phoneCount++] = new MobilePhone(name, brand, price, color, memory);
        }
        else if (type == "radio") {
            file1 >> range >> answeringMachine;
            phones[phoneCount++] = new RadioPhone(name, brand, price, range, answeringMachine);
        }
    }
    file1.close();

   
    ifstream file2("phones2.txt");
    while (file2 >> name >> brand >> type >> price) {
        if (type == "mobile") {
            file2 >> color >> memory;
            phones[phoneCount++] = new MobilePhone(name, brand, price, color, memory);
        }
        else if (type == "radio") {
            file2 >> range >> answeringMachine;
            phones[phoneCount++] = new RadioPhone(name, brand, price, range, answeringMachine);
        }
    }
    file2.close();

   
    sort(phones, phones + phoneCount, [](const Phone* a, const Phone* b) {
        return a->getPrice() < b->getPrice();
        });

    
    ofstream out1("phones_sorted_by_price.txt");
    double totalPrice = 0.0;
    for (int i = 0; i < phoneCount; i++) {
        out1 << phones[i]->getName() << " " << phones[i]->getBrand() << " " << phones[i]->getPrice() << endl;
        totalPrice += phones[i]->getPrice();
    }
    out1 << "Total price: " << totalPrice << endl;
    out1.close();
    
    ofstream out2("radiophones_with_answering_machine.txt");
    for (int i = 0; i < phoneCount; i++) {
        RadioPhone* radioPhone = dynamic_cast<RadioPhone*>(phones[i]);
        if (radioPhone && radioPhone->hasAnsweringMachine()) {
            out2 << radioPhone->getName() << " " << radioPhone->getBrand() << endl;
        }
    }
    out2.close();

   
    for (int i = 0; i < phoneCount; i++) {
        delete phones[i];
    }

    return 0;
}