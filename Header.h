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
    virtual double Load_to_capacity_ratio(int Motor_power) = 0; 
    bool Compare(Car* Other); 
protected:
    Car() {};
};


class Truck : public Car {
    int Load_cap; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, ofstream& ofst); 
    double Load_to_capacity_ratio(int Motor_power); 
    Truck() {};
};

class Bus : public Car {
    short int Passenger_cap; 
public:
    void In_Data(ifstream& ifst); 
    void Out_Data(int Motor_power, ofstream& ofst); 
    double Load_to_capacity_ratio(int Motor_power); 
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
    void Sort(); 
    Container(); 
    ~Container() { Clear(); } 
};

#endif //HEADER_H