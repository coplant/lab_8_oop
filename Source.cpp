#include "Header.h"

Container::Container() {
    Head = Tail = new Node();
    Head->Cont = Tail->Cont = NULL;
    Head->Next = Tail->Next = NULL;
    Head->Prev = Tail->Prev = NULL;
    Len = 0;
}

void Container::In(ifstream& ifst) {
    Node* Temp;

    while (!ifst.eof()) {
        Temp = new Node(); //Создаем новый узел
        //Инициализируем новый узел
        Temp->Next = NULL;
        Temp->Prev = NULL;

        
        if (!Len) { //Запись 1-го элемента
            if ((Head->Cont = Car::In_Car(ifst))) {
                Tail = Head;
                Len++;
            }
        }
        else { //Запись последующих элементов
            if ((Temp->Cont = Car::In_Car(ifst))) {
                Tail->Next = Temp;
                Temp->Prev = Tail;
                Tail = Temp;
                Len++;
            }
        }
    }
}

void Container:: Out(ofstream& ofst) {
    ofst << "Container contains " << Len
        << " elements." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        if (Temp->Cont->Get_Motor_power() == -1) {
            ofst << "Incorrect element!" << endl << endl;
        }
        else {
            Temp->Cont->Out_Data(Temp->Cont->Get_Motor_power(), Temp->Cont->Get_Fuel(), ofst);

            ofst << "Load to capacity ratio is = " << Temp->Cont->Load_to_capacity_ratio(Temp->Cont->Get_Motor_power()) << endl << endl;
        }

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

void Container::Clear() {
    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        free(Temp->Cont);

        if (Temp->Next) {
            Temp = Temp->Next;
            free(Temp->Prev);
        }

    }

    Len = 0;
}

void Container::Sort() {
    if (Len > 1) {
        Node* First = Head;
        Node* Second = Head->Next;
        Node* Temp = new Node;

        for (int i = 0; i < Len - 1; i++) {
            for (int j = 0; j < Len - i - 1; j++) {
                if (First->Cont->Compare(Second->Cont)) {
                    Temp->Cont = First->Cont;
                    First->Cont = Second->Cont;
                    Second->Cont = Temp->Cont;
                }

                Second = Second->Next;
            }

            First = First->Next;
            Second = First->Next;
        }
    }
}

void Container::Out_Only_Truck(ofstream& ofst) {
    ofst << "Only Trucks." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        if (Temp->Cont->Get_Motor_power() == -1) {
            ofst << "Incorrect element!" << endl << endl;
        }
        else {
            Temp->Cont->Out_Only_Truck(Temp->Cont->Get_Motor_power(), Temp->Cont->Get_Fuel(), ofst);
        }

        if (Temp->Next) {
            Temp = Temp->Next;
        }
    }
}

Car* Car::In_Car(ifstream& ifst) {
    Car* C;
    string Temp_Str = "";

    getline(ifst, Temp_Str);

    //Проверка того, что файл либо содержит ошибочный идентификтор Машины,
     //либо не содержит его вовсе
    if ((Temp_Str != "1") && (Temp_Str != "2") && (Temp_Str != "3")) {
        //Возможно идентификатора нет, потому что это конец файл
        if (ifst.peek() == EOF) {
            return 0;
        }
        else { //В ином случае идентификатор отсутствует вовсе, либо он ошибочен
            //Завершение программы с ошибкой
            cout << "Input data is incomplete or incorrect!";
            exit(1);
        }
    }

    int K = atoi(Temp_Str.c_str());
    
    if (K == 1) {
        C = new Truck;
    }
    else if (K == 2) {
        C = new Bus;
    }
    else if (K == 3) {
        C = new Passenger_car;
    }
    else {
        return 0;
    }

    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);

    if (Temp_Str == "") { //Если строка пустая
        //Завершение программы с ошибкой
        cout << "Input data is incomplete!";
        exit(1);
    }

    if (Temp_Str[0] == '0') { //Если число начинается с 0
        //Завершение программы с ошибкой
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.length(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }

    C->Motor_power = atoi(Temp_Str.c_str());

    C->In_Data(ifst);

    getline(ifst, Temp_Str);

    if (Temp_Str == "") { //Если строка пустая
        //Завершение программы с ошибкой
        cout << "Input data is incomplete!";
        exit(1);
    }

    //Проверка того, что строка не начианется с 0, точки или запятой, а также не заканчивается точкой или запятой
    if ((Temp_Str[0] == 0) || (Temp_Str[0] == ',') || (Temp_Str[0] == '.') ||
        (Temp_Str[Temp_Str.length() - 1] == ',') || (Temp_Str[Temp_Str.length() - 1] == '.')) {
        //Завершение программы с ошибкой
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл провреки корректности записи вещественного числа
    for (int i = 0; i < Temp_Str.length(); i++) {
        if ((Alph_num.find(Temp_Str[i]) == -1) && (Temp_Str[i] != ',') && (Temp_Str[i] != '.')) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }

        if ((Temp_Str[i] == ',') || (Temp_Str[i] == '.')) {
            if ((Temp_Str[i - 1] == ',') || (Temp_Str[i - 1] == '.') ||
                (Temp_Str[i + 1] == ',') || (Temp_Str[i + 1] == '.')) {
                //Завершение программы с ошибкой
                cout << "Input data is incorrect!";
                exit(1);
            }
        }
    }

    C->Fuel = strtod(Temp_Str.c_str(), NULL);

    return C;
}

void Car::Set_Motor_power(int _Motor_power) {
    Motor_power = _Motor_power;
}

int Car::Get_Motor_power() {
    return Motor_power;
}

double Car::Get_Fuel() {
    return Fuel;
}

bool Car::Compare(Car* Other) {
    return Load_to_capacity_ratio(Motor_power) > Other->Load_to_capacity_ratio(Other->Get_Motor_power());
}

void Car::Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << endl;
}

void Truck::In_Data(ifstream& ifst) {
    string Temp_Str = "";
    string Alph_num = "0123456789";
    
    getline(ifst, Temp_Str);

    if (Temp_Str == "") { //Если строка пустая
        //Завершение программы с ошибкой
        cout << "Input data is incomplete!";
        exit(1);
    }

    if (Temp_Str[0] == '0') { //Если число начинается с 0
        //Завершение программы с ошибкой
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.length(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }

    Load_cap = atoi(Temp_Str.c_str());
}

void Truck::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Truck with motor power = " << Motor_power << endl;
    ofst << "Its load capacity is " << Load_cap << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Truck::Load_to_capacity_ratio(int Motor_power) {
    return (double)Load_cap / (double)Motor_power;
}

void Truck::Out_Only_Truck(int Motor_power, double Fuel, ofstream& ofst) {
    Out_Data(Motor_power, Fuel, ofst);
}

void Bus::In_Data(ifstream& ifst) {
    string Temp_Str = "";
    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);

    if (Temp_Str == "") { //Если строка пустая
        //Завершение программы с ошибкой
        cout << "Input data is incomplete!";
        exit(1);
    }

    if (Temp_Str[0] == '0') { //Если число начинается с 0
        //Завершение программы с ошибкой
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.length(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }

    Passenger_cap = atoi(Temp_Str.c_str());
}

void Bus::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Bus with motor power = " << Motor_power << endl;
    ofst << "Its passenger capacity is " << Passenger_cap << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Bus::Load_to_capacity_ratio(int Motor_power) {
    return (double)(75 * Passenger_cap) / (double)Motor_power;
}

void Passenger_car::In_Data(ifstream& ifst) {
    string Temp_Str = "";
    string Alph_num = "0123456789";

    getline(ifst, Temp_Str);

    if (Temp_Str == "") { //Если строка пустая
        //Завершение программы с ошибкой
        cout << "Input data is incomplete!";
        exit(1);
    }

    if (Temp_Str[0] == '0') { //Если число начинается с 0
        //Завершение программы с ошибкой
        cout << "Input data is incorrect!";
        exit(1);
    }

    //Цикл проверки того, что строка содержит только цифры
    for (int i = 0; i < Temp_Str.length(); i++) {
        if (Alph_num.find(Temp_Str[i]) == -1) {
            //Завершение программы с ошибкой
            cout << "Input data is incorrect!";
            exit(1);
        }
    }

    Max_speed = atoi(Temp_Str.c_str());
}

void Passenger_car::Out_Data(int Motor_power, double Fuel, ofstream& ofst) {
    ofst << "It's a Passenger car with motor power = " << Motor_power << endl;
    ofst << "Its Max speed is " << Max_speed << endl;
    ofst << "Its fuel is " << Fuel << endl;
}

double Passenger_car::Load_to_capacity_ratio(int Motor_power) {
    return (double)(75 * 4) / (double)Motor_power; //4 пассажира по 75 кг
}