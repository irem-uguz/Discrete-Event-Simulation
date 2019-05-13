//
// Created by ECEM on 20.11.2017.
//

#include "Cashier.h"
Cashier::Cashier() {
    this->currentCustomer= nullptr;
    this->totalWorkTime=0;
}
Cashier::Cashier(const Cashier &a) {
    this->currentCustomer= a.currentCustomer;
    this->totalWorkTime=a.totalWorkTime;
}
Cashier& Cashier::operator=(const Cashier &x) {
    this->currentCustomer= x.currentCustomer;
    this->totalWorkTime=x.totalWorkTime;
    return *this;
}
Cashier::~Cashier() {
    this->currentCustomer= nullptr;
}
void Cashier::takeCustomer(Customer &a) {
    this->currentCustomer=&a;
    a.currentTime=a.currentTime+a.orderTime;
    this->totalWorkTime+=a.orderTime;
    a.position=2;
}
void Cashier::giveCustomer() {
    currentCustomer->cashier=-1;
    this->currentCustomer= nullptr;
}