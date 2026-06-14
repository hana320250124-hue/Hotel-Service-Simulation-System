#ifndef CUSTOMER_H
#define CUSTOMER_H

enum DeptType { FRONT_DESK, CONCIERGE, RESTAURANT };

struct Customer {
    int      id;
    DeptType department;
    bool     isVIP;

    int arrivalTime;
    int serviceTime;

    int startTime;
    int waitingTime;

    bool abandoned;
    int  rating;

    Customer() {
        id         = 0;
        department = FRONT_DESK;
        isVIP      = false;
        arrivalTime = 0;
        serviceTime = 1;
        startTime   = 0;
        waitingTime = 0;
        abandoned   = false;
        rating      = 0;
    }
};

#endif