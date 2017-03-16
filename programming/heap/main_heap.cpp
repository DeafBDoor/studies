#include <iostream>
//#include <fstream>
#include "heap.h"

using namespace std;

int main() {
    Heap<unsigned, 100> myheap;

    /*ifstream istrm("randnumbers", ios::in);

    if (!istrm.is_open()) {
        cout << "Failure opening file!" << endl;
        return 1;
    }*/

    try {
        myheap.pop();
    } catch (HeapException he) {
        cout << he.what() << endl;
    }

    unsigned tmp;
    for (int i = 0; i < 100; i++) {
        cin >> tmp;
        myheap.push(tmp);
        //
    }

    try {
        myheap.push(1000);
    } catch (HeapException he) {
        cout << he.what() << endl;
    }

    /*myheap.push(20).push(10).push(5).push(1);

    for (auto v : myheap) {
        cout << v << " ";
    }
    cout << endl << endl;

    myheap.pop();
    myheap.pop();
    */

    for (auto v : myheap) {
        cout << v << endl;
    }
    //cout << endl;

    return 0;
}

