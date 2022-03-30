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
    ofst << "Container have " << Len
        << " elems." << endl << endl;

    Node* Temp = Head;

    for (int i = 0; i < Len; i++) {
        ofst << i << ": ";
        Temp->Cont->Out_Data(Temp->Cont->Get_Motor_power(), ofst);

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

void Truck::In_Data(ifstream& ifst) {
    ifst >> Load_cap;
}

void Truck::Out_Data(int Motor_power, ofstream& ofst) {
    ofst << "Truck with motor power = " << Motor_power << endl;
    ofst << "Load capacity is " << Load_cap << endl << endl;
}

void Bus::In_Data(ifstream& ifst) {
    ifst >> Passenger_cap;
}

void Bus::Out_Data(int Motor_power, ofstream& ofst) {
    ofst << "Bus with motor power = " << Motor_power << endl;
    ofst << "Passenger capacity is " << Passenger_cap << endl << endl;
}