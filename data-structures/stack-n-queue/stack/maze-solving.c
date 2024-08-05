//
// Created by Hoarfroster on 21/7/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include "maze-solving.h"

// Clear the stack
void clear(LinkedStack *stack) {
    Node *current = stack->top;
    Node *nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    stack->top = NULL;
    stack->length = 0;
}

// Whether the stack is empty
int empty(LinkedStack *stack) {
    return stack->top == NULL;
}

// Length of the stack
int length(LinkedStack *stack) {
    return stack->length;
}

// Initialization
LinkedStack *init() {
    LinkedStack *stack = (LinkedStack *) malloc(sizeof(LinkedStack));
    if (stack == NULL) {
        printf("Failed to allocate memory\n");
        exit(1);
    }

    stack->top = NULL;
    stack->length = 0;
    return stack;
}

// Destroy
void destroy(LinkedStack *stack) {
    clear(stack);
    stack->top = NULL;
    stack->length = 0;
}

// Push an element to the top
int push(LinkedStack *stack, int x, int y, int fromDirection) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // failed to allocate memory - i.e. stack overflow
    }
    newNode->x = x;
    newNode->y = y;
    newNode->fromDirection = fromDirection;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->length++;
    return 1;
}

// Pop the top element
int pop(LinkedStack *stack) {
    if (stack->top == NULL) {
        return 0; // stack already empty
    }
    Node *temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->length--;
    return 1;
}

// return 1 if movable to the right, 2 if movable to the bottom, 3 if movable to the left, 4 if movable to the top, 0 if not movable
int movable(int x, int y, int visitable[8][8]) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
        if (x + 1 < 8 && visitable[x + 1][y]) {
            return 1; // movable - to the right
        } else if (y + 1 < 8 && visitable[x][y + 1]) {
            return 2; // movable - to the bottom
        } else if (x - 1 >= 0 && visitable[x - 1][y]) {
            return 3; // movable - to the left
        } else if (y - 1 >= 0 && visitable[x][y - 1]) {
            return 4; // movable - to the top
        } else {
            return 0; // no movable adjacent cell
        }
    } else {
        return 0; // out of bounds
    }
}

// note: this will also pop all elements of the stack
void printMazeSteps(const int maze[8][8], LinkedStack *stack) {
    int steps[8][8], directions[64], cursor = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            steps[i][j] = directions[i * 8 + j] = 0;
        }
    }
    while (!empty(stack)) {
        int x = stack->top->x, y = stack->top->y;
        steps[x][y] = 1;
        directions[cursor++] = stack->top->fromDirection;
        pop(stack);
    }

    cursor = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (!maze[i][j]) { // unmovable
                printf("◼︎");
            } else if (steps[i][j]) {
                if(cursor == 0){
                    printf("○");
                    cursor++;
                    continue;
                }
                switch (directions[(cursor++)-1]) {
                    case 1:
                        printf("→");
                        break;
                    case 2:
                        printf("↓");
                        break;
                    case 3:
                        printf("←");
                        break;
                    case 4:
                        printf("↑");
                        break;
                }
            } else printf("◻︎");
        }

        printf("\n");
    }
}

void solveMaze(int startX, int startY, int destX, int destY, const int maze[8][8]) {
    int visitable[8][8]; // for the 2D map `visitable`, value 1 represents visitable.
    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            visitable[i][j] = maze[i][j];
        }
    }
    int currentX = startX, currentY = startY, lastDirection = -1; // lastDirection: 1 - right, 2 - bottom, 3 - left, 4 - top

    LinkedStack *stack = init();

    do {
        if (visitable[currentX][currentY]) {
            printf("visiting (%d, %d) from direction %d\n", currentX, currentY, lastDirection);
            visitable[currentX][currentY] = 0; // marks it unvisitable - have been visited
            push(stack, currentX, currentY, lastDirection);

            if (currentX == destX && currentY == destY) {
                printf("The path is: \n");
                printMazeSteps(maze, stack);
                break;
            }
        }

        switch (movable(currentX, currentY, visitable)) {
            case 1:
                currentX++;
                lastDirection = 1;
                break;
            case 2:
                currentY++;
                lastDirection = 2;
                break;
            case 3:
                currentX--;
                lastDirection = 3;
                break;
            case 4:
                currentY--;
                lastDirection = 4;
                break;

            default: // 0 - unmovable, should backtrack
                switch (stack->top->fromDirection) {
                    case 1:
                        currentX--;
                        break;
                    case 2:
                        currentY--;
                        break;
                    case 3:
                        currentX++;
                        break;
                    case 4:
                        currentY++;
                        break;
                }
                printf("Backtracking to (%d, %d)\n", currentX, currentY);
                pop(stack); // backtrack
        }
    } while (!empty(stack));

    destroy(stack);
}

int main() {
    const int maze[8][8] = {
            {1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 1, 1},
            {1, 0, 0, 0, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 0, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 1},
            {0, 1, 1, 1, 1, 1, 1, 1}
    };
    solveMaze(0, 0, 7, 7, maze);

    return 0;
}