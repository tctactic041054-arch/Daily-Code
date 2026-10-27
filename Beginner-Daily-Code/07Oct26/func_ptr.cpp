#include <iostream>
#include <ostream>
using namespace std;

// This fn Resive "Addr" of score in through pointer
void addBonus(int* scorePtr) {
    *scorePtr += 500; // through to add 500 at that Mem.
}

int main () {
    int player32 = 1000;

    cout << "1. Befor Bonus: " << player32 << endl;

    //Send Address (&player32) in fn
    addBonus(&player32);

    cout << "2. After Bonus: " << player32 << endl;
    
    return 0;
}