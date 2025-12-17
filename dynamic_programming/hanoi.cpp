#include <iostream>

void hanoi(int peg_number, char Source, char Dest, char Hold) {
    if(peg_number <= 0)
        return;
    hanoi(peg_number-1, Source, Hold, Dest);
    std::cout << "Move " << peg_number <<   " from " << Source << " to " << Dest << '\n';
    hanoi(peg_number-1, Hold, Dest, Source);
}

int main() {
    hanoi(3, 'S', 'D', 'I');
}
