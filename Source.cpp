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
        Temp = new Node(); 
        Temp->Next = NULL;
        Temp->Prev = NULL;

        
        if (!Len) { 
            if ((Head->Cont = Car::In_Car(ifst))) {
                Tail = Head;
                Len++;
            }
        }
        else { 
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
        Temp->Cont->Out_Data(Temp->Cont->Get_Motor_power(), ofst);

        ofst << "Load to capacity ratio is = " << Temp->Cont->Load_to_capacity_ratio(Temp->Cont->Get_Motor_power()) << endl << endl;

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

Car* Car::In_Car(ifstream& ifst) {
    Car* C;
    int K;

    ifst >> K;
    
    if (K == 1) {
        C = new Truck;

        ifst >> C->Motor_power; 
    }
    else if (K == 2) {
        C = new Bus;

        ifst >> C->Motor_power; 
    }
    else {
        return 0;
    }

    C->In_Data(ifst);

    return C;
}

int Car::Get_Motor_power() {
    return Motor_power;
}

bool Car::Compare(Car* Other) {
    return Load_to_capacity_ratio(Motor_power) > Other->Load_to_capacity_ratio(Other->Get_Motor_power());
}

void Truck::In_Data(ifstream& ifst) {
    ifst >> Load_cap;
}

void Truck::Out_Data(int Motor_power, ofstream& ofst) {
    ofst << "Truck with motor power = " << Motor_power << endl;
    ofst << "Load capacity is " << Load_cap << endl;
}

double Truck::Load_to_capacity_ratio(int Motor_power) {
    return (double)Load_cap / (double)Motor_power;
}

void Bus::In_Data(ifstream& ifst) {
    ifst >> Passenger_cap;
}

void Bus::Out_Data(int Motor_power, ofstream& ofst) {
    ofst << "Bus with motor power = " << Motor_power << endl;
    ofst << "Passenger capacity is " << Passenger_cap << endl;
}

double Bus::Load_to_capacity_ratio(int Motor_power) {
    return (double)(75 * Passenger_cap) / (double)Motor_power;
}
