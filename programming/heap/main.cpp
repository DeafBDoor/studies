#include <iostream>
//#include <fstream>
#include "heap.h"
#include "running_median.h"

using namespace std;

int main() {

    MedianCalculator<double, unsigned int, 200> medcalc;

    /*ifstream istrm("randnumbers", ios::in);

    if (!istrm.is_open()) {
        cout << "Failure opening file!" << endl;
        return 1;
    }*/

    unsigned tmp;
    double m;
    for (int i = 0; i < 100; i++) {
        cin >> tmp;
        m =  medcalc.addValue(tmp);
        //printf("%0.2f\n", m);
        cout << "N: " << tmp << " median: " << m << endl;
        cout << "lefth: " << medcalc.getlHeapHead() << " pivot: " << medcalc.getPivot() << " righth: " << medcalc.getgHeapHead() << endl;
        cout << endl;

    }

    return 0;
}
