#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "Queue.h"
#include "Server.h"

struct Department {
    DeptType type;

    Queue vipQueue;
    Queue normalQueue;

    Server servers[2];   // max 2 servers per department
    int    numServers;

    int totalServed;
    int totalAbandoned;   // customers who left after waiting too long
    int totalRatingSum;   // sum of all ratings (for average)

    Department() {
        numServers     = 1;
        totalServed    = 0;
        totalAbandoned = 0;
        totalRatingSum = 0;
    }
};

#endif