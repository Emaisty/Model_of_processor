#include <iostream>
#include <vector>

using namespace std;

class Proccesor {
public:
    void (Proccesor::*func[4])(int, int);
    vector<int> registers;

    Proccesor() {
        for (int i = 0; i < 4; ++i) {
            this->registers.push_back(0);
        }
        func[0] = &Proccesor::add_const;
        func[1] = &Proccesor::copy;
        func[2] = &Proccesor::plus;
        func[3] = &Proccesor::minus;

    }

    void add_const(int a, int b) {
        registers[a] = b;
    }

    void copy(int a, int b) {
        registers[b] = registers[a];
    }

    void plus(int a, int b) {
        registers[b] += registers[a];
    }

    void minus(int a, int b) {
        registers[b] -= registers[a];
    }

    friend ostream &operator<<(ostream &os, Proccesor proc) {
        cout << "R0: " << proc.registers[0] << ",R1: " << proc.registers[1] << ",R2: " << proc.registers[2] << ",R3: "
             << proc.registers[3] << ".\n";
        return os;
    }

    void exec(int code, int first, int second) {
        (this->*func[code - 1])(first, second);
    }


};

void b() {
    cout << "lol";
}

int main() {
    Proccesor proc;
    char code, first, second;


    while (cin >> code >> first >> second) {
        int cod, firs, secon;
        cod = (int) code - 48;
        firs = (int) first - 48;
        secon = (int) second - 48;
        proc.exec(cod, firs, secon);
        cout << proc;
    }
    return 0;
}
