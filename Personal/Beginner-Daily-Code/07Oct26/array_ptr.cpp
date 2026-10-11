#include <iostream>
using namespace std;

int main() {
    int numbers [3] = {10, 20, 30};
    int* ptr = numbers; // Not need to fill "&" cause of Array is Addr of first Element.

    cout << "=== POINTER ARITHMETIC ===" << endl;
    cout << "1. Address of Number[0]: " << ptr << " | Value: " << *ptr << endl;
    cout << "2. Address of Number[1]: " << (ptr + 1) << " | Value: " << *(ptr + 1) << endl;
    cout << "3. Address of Number[2]: " << (ptr + 2) << " | Value: " << *(ptr + 2) << endl;

    return 0;
}