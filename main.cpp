#include <iostream>
#include <vector>

using namespace std;

class Proccesor {
public:
    //array of pointers to functions
    void (Proccesor::*func[10])(int, int);

    //register. Array of values
    vector<int> registers;

    //old values of registers
    vector<int> old_registers;

    //Constructor. Run with creating new value of this class
    Proccesor() {
        for (int i = 0; i < 4; ++i) {
            this->registers.push_back(0);
            this->old_registers.push_back(0);
        }
        func[0] = &Proccesor::Add_const;
        func[1] = &Proccesor::Copy;
        func[2] = &Proccesor::Plus;
        func[3] = &Proccesor::Minus;
        func[4] = &Proccesor::Multiplication;
        func[5] = &Proccesor::Division;
        func[6] = &Proccesor::And;
        func[7] = &Proccesor::Or;
        func[8] = &Proccesor::Xor;
        func[9] = &Proccesor::Unar_minus;
    }

    //all operations change second register (b)

    //write constant to register a
    void Add_const(int a, int b) {
        registers[a] = b;
    }

    // copy register a to b
    void Copy(int a, int b) {
        registers[b] = registers[a];
    }

    //plus register a to register b
    void Plus(int a, int b) {
        registers[b] += registers[a];
    }

    //minus register a from register b
    void Minus(int a, int b) {
        registers[b] -= registers[a];
    }

    //register * register a
    void Multiplication(int a, int b) {
        registers[b] *= registers[a];
    }

    // register b/ register a
    void Division(int a, int b) {
        if (registers[a] == 0)
            Panic(0);
        else
            registers[b] /= registers[a];
    }

    //logic block

    //binary Multiplication
    void And(int a, int b) {
        registers[b] = char(registers[a] & registers[b]);
    }

    //binary sum
    void Or(int a, int b) {
        registers[b] = char(registers[a] | registers[b]);
    }

    // xor _/(.-.)\_
    void Xor(int a, int b) {
        registers[b] = registers[a] ^ registers[b];
    }

    //b = a, a = -a
    void Unar_minus(int a, int b) {
        registers[b] = registers[a];
        registers[a] = -1 * registers[a];
    }

    //custom output
    friend ostream &operator<<(ostream &os, Proccesor proc) {
        cout << "R0: " << proc.registers[0] << ",R1: " << proc.registers[1] << ",R2: " << proc.registers[2] << ",R3: "
             << proc.registers[3] << ".\n";
        return os;
    }

    //start
    void exec(int code, int first, int second) {
        Save();
        if (code - 1 < 10)
            if ((first > 0 && first < 4) || (second > 0 && second < 4))
                (this->*func[code])(first, second);
            else
                Panic(2);
        else
            Panic(1);
    }

    //save values before change
    void Save() {
        for (int i = 0; i < 4; ++i) {
            this->old_registers[i] = this->registers[i];
        }
    }

    //Create Errors
    void Panic(int number) {
        if (number == 0)
            perror("ERROR. DEVISION BY ZERO");
        if (number == 1)
            perror("ERROR. UNDEFINED COMMAND");
        if (number == 2)
            perror("ERROR. WRONG REGISTER");
    }

};

//from hex to dec.
int from_hex_to_dec(char a) {
    if (a == 'f')
        return 15;
    if (a == 'e')
        return 14;
    if (a == 'd')
        return 13;
    if (a == 'c')
        return 12;
    if (a == 'b')
        return 11;
    if (a == 'a')
        return 10;
    return (int) a - 48;
}

//print help information
void Help() {
    cout << "Model of proccesor" << endl;
    cout << "Format of input: abc, where abc - digits. a - number of command and b and c - registers" << endl;
    cout << "---------Commands---------\n";
    cout << "(All commands saved values to the second(c) register)\n";
    cout
            << "0) Create constant, where c - constant\n1)copy value from b to c\n2) c = c+b\n3)c = c - b\n4)c = c * b\n5)c = c / b\n logic block\n6)c = c and b\n7)c = c or b\n8)c = xor b\n9)b = c, c = -c";
}

int main() {
    cout << "write \"help\" to see information\n";
    Proccesor proc;
    string str;
    cin >> str;
    while (str != "STOP") {
        if (str == "help")
            Help();
        else {
            char code = str[0], first = str[1], second = str[2];
            int cod, firs, secon;
            cod = from_hex_to_dec(code);
            firs = (int) first - 48;
            secon = (int) second - 48;
            proc.exec(cod, firs, secon);
            cout << proc;
        }

        cin >> str;
    }
    return 0;
}