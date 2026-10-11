#include <iostream>
using namespace std;

int main() {
    int score = 100;
    int* ptr = &score;

    cout << "==== MEMORY & POINTER TEST ====" << endl;
    cout << "1. Value of score: " << score << endl;
    cout << "2. Memory Address of score (&score): " << &score << endl;
    cout << "3. Value stored in pointer (ptr): " << ptr << endl;
    cout << "4. Value at pointer address (*ptr): " << *ptr << endl;

    // *ptr = 999; // << Edit at ptr (Save RAM)
    // cout << "5. New Score value (after *ptr = 999): " << score << endl; // New Data
    return 0;
}