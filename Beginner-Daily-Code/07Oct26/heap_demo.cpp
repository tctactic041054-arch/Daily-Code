#include <iostream>
using namespace std;

int main() {
    // Start Mem RAM in Heap
    int* heapPtr = new int;
    *heapPtr = 777;

    cout << "=== HEAP MEMORY ALLOCATION ===" << endl;
    cout << "1. Address in Heap: " << heapPtr << endl;
    cout << "2. Value in Heap: " << *heapPtr << endl;

    delete heapPtr; // Take RAM to OS (owner)
    heapPtr = nullptr; // delete trash point to protect wild pointer
    return 0;
}