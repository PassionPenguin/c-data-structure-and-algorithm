//
// Created by hoarfroster on 28/7/2024.
//

#include <stdio.h>
#include "hanoi-tower.h"

int steps = 0;

// move plate `n` from `x` to `y`
void move(char x, int n, char y) {
    printf("%d. Moving plate `%d` from %c to %c\n", ++steps, n, x, y);
}

// moving `x` => `y` while `z` is a helper tower
void hanoi(int n, char x, char y, char z) {
    if (n == 1) move(x, 1, z);
    else {
        hanoi(n - 1, x, z, y);
        move(x, n, z);
        hanoi(n - 1, y, x, z);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("Resolving a %d-sized hanoi tower\n", n);
    hanoi(n, 'x', 'y', 'z');
    printf("Total steps: %d", steps);

    return 0;
}