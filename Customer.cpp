//
// Created by ECEM on 20.11.2017.
//

#include "Customer.h"
Customer::Customer(){
    this->arrivalTime=0;
    this->currentTime=arrivalTime;
    this->price=0;
    this->orderTime=0;
    this->brewTime=0;
    this->position=0;
    this->finishTime=0;
    this->cashier=-1;
    this->barista=-1;
    this->index=-1;
}
Customer::Customer(double arrival, double price, double order, double brew) {
    this->arrivalTime=arrival;
    this->price=price;
    this->orderTime=order;
    this->brewTime=brew;
    this->currentTime=arrivalTime;
    this->position=0;
    this->finishTime=0;
    this->cashier=-1;
    this->barista=-1;
    this->index=-1;
}
Customer::Customer(const Customer &x) {
    this->price=x.price;
    this->arrivalTime=x.arrivalTime;
    this->orderTime=x.orderTime;
    this->brewTime=x.brewTime;
    this->currentTime=x.currentTime;
    this->position=x.position;
    this->finishTime=x.finishTime;
    this->cashier=x.cashier;
    this->barista=x.barista;
    this->index=x.index;
}
Customer& Customer::operator=(const Customer &x) {
    this->price=x.price;
    this->arrivalTime=x.arrivalTime;
    this->orderTime=x.orderTime;
    this->brewTime=x.brewTime;
    this->currentTime=x.currentTime;
    this->position=x.position;
    this->finishTime=x.finishTime;
    this->cashier=x.cashier;
    this->barista=x.barista;
    this->index=x.index;
    return *this;
}
Customer::~Customer() {}