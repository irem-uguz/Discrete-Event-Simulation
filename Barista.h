//
// Created by ECEM on 20.11.2017.
//

#ifndef PROJE2YEDEK_BARISTA_H
#define PROJE2YEDEK_BARISTA_H


#include "Customer.h"

class Barista {
public:
    Customer* currentCustomer;
    double totalWorkTime;
    Barista();
    Barista(const Barista& a);
    Barista& operator=(const Barista& x);
    ~Barista();
    void takeCustomer(Customer &a);
    void giveCustomer();
};


#endif //PROJE2YEDEK_BARİSTA_H
