//
// Created by Hoarfroster on 21/7/2024.
//

#ifndef C_ALGORITHM_POLYNOMIALS_H
#define C_ALGORITHM_POLYNOMIALS_H

typedef struct Term Term;
struct Term {
    int coefficient;
    int exponent;
    Term *next;
};

typedef struct LinkedList {
    Term *head;
    int length;
} LinkedList;

typedef LinkedList Polynomial;

// Initialization
Polynomial *init();

// Destroy
void destroy(Polynomial *list);

void AddTerm(Polynomial *list, int coefficient, int exponent);

void PrintPolynomial(Polynomial *list);

Polynomial *Add(Polynomial *p1, Polynomial *p2);

Polynomial *Multiply(Polynomial *p1, Polynomial *p2);

#endif //C_ALGORITHM_POLYNOMIALS_H
