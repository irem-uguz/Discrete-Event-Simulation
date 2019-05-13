//
// Created by ECEM on 20.11.2017.
//

#include "Barista.h"
Barista::Barista()  {
    this->currentCustomer= nullptr;
    this->totalWorkTime=0;
}
Barista::Barista(const Barista &a)  {
    this->currentCustomer= a.currentCustomer;
    this->totalWorkTime=a.totalWorkTime;
}
Barista& Barista::operator=(const Barista &x) {
    this->currentCustomer= x.currentCustomer;
    this->totalWorkTime=x.totalWorkTime;
    return *this;
}
Barista::~Barista(){
    this->currentCustomer= nullptr;
}
void Barista::takeCustomer(Customer &a) {
    this->currentCustomer=&a;
    a.currentTime=a.currentTime+a.brewTime;
    this->totalWorkTime+=a.brewTime;
    a.position=4;
}
void Barista::giveCustomer() {
    currentCustomer->barista=-1;
    currentCustomer->finishTime=currentCustomer->currentTime;
    this->currentCustomer= nullptr;
}