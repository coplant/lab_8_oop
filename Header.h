#ifndef HEADER_H
#define HEADER_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;


class Car {
    int Motor_power; 
public:
    int Get_Motor_power();

    static Car* In_Car(ifstream& ifst); 
    virtual void In_Data(ifstream& ifst) = 0; 
    virtual void Out_Data(int Motor_power, ofstream& ofst) = 0; 
protected:
    Car() {};
};


class Truck : public Car {
    int Load_cap; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, ofstream& ofst); 
    Truck() {};
};


class Bus : public Car {
    short int Passenger_cap; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, ofstream& ofst); 
    Bus() {};
};


struct Node {
    Node* Next, * Prev; 
    Car* Cont; 
};

class Container {
    Node* Head, *Tail; 
    int Len; 
public:
    void In(ifstream& ifst); 
    void Out(ofstream& ofst); 
    void Clear(); 
    Container(); 
    ~Container() { Clear(); } 
};

#endif //HEADER_H