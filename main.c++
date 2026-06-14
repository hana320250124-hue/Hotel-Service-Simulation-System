#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Config.h"
#include "Department.h"
#include "Simulation.h"
#include "Statistics.h"

using namespace std;

int main() {

    srand(time(0));

    Department depts[3];

    depts[0].type       = FRONT_DESK;
    depts[0].numServers = 2;

    depts[1].type       = CONCIERGE;
    depts[1].numServers = 1;

    depts[2].type       = RESTAURANT;
    depts[2].numServers = 2;

    cout << "Simulation Started...\n";

    runSimulation(depts);

    printStats(depts);

    return 0;
}