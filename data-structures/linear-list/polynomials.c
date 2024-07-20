//
// Created by Hoarfroster on 20/7/2024.
//

#include <stdio.h>
#include <stdlib.h>

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
Polynomial *init() {
    Polynomial *list = (Polynomial *) malloc(sizeof(Polynomial));
    if(list == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    list->head = NULL;
    list->length = 0;
    return list;
}

// Destroy
void destroy(Polynomial *list) {
    Term *current = list->head;
    Term *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}

void AddTerm(Polynomial *list, int coefficient, int exponent) {
    Term *newTerm = (Term *) malloc(sizeof(Term));
    newTerm->coefficient = coefficient;
    newTerm->exponent = exponent;
    newTerm->next = NULL;

    if (list->head == NULL) {
        list->head = newTerm;
    } else {
        // always add the term so that the list is sorted by exponent ascending
        Term *current = list->head;
        Term *prev = NULL;
        while (current != NULL && current->exponent < exponent) {
            prev = current;
            current = current->next;
        }

        // if already exists a term with the same exponent, add the coefficients
        if (current != NULL && current->exponent == exponent) {
            current->coefficient += coefficient;
            free(newTerm);
            return;
        } else {
            newTerm->next = (struct Term *) current;
            if (prev == NULL) {
                list->head = newTerm;
            } else {
                prev->next = (struct Term *) newTerm;
            }
        }
    }
    list->length++;
}

void PrintPolynomial(Polynomial *list) {
    Term *current = list->head;
    while (current != NULL) {
        if (current->coefficient != 0) {
            if (current->exponent == 0) {
                printf("%d", current->coefficient);
            } else if (current->exponent == 1) {
                printf("%dx", current->coefficient);
            } else {
                printf("%dx^%d", current->coefficient, current->exponent);
            }
            if (current->next != NULL) {
                if ((current->next)->coefficient > 0) {
                    printf(" + ");
                } else {
                    printf(" ");
                }
            }
        }
        current = current->next;
    }
    printf("\n");
}

Polynomial *Add(Polynomial *p1, Polynomial *p2) {
    Polynomial *result = init();
    Term *current1 = p1->head;
    Term *current2 = p2->head;

    while (current1 != NULL && current2 != NULL) {
        if (current1->exponent > current2->exponent) {
            AddTerm(result, current1->coefficient, current1->exponent);
            current1 = current1->next;
        } else if (current1->exponent < current2->exponent) {
            AddTerm(result, current2->coefficient, current2->exponent);
            current2 = current2->next;
        } else {
            AddTerm(result, current1->coefficient + current2->coefficient, current1->exponent);
            current1 = current1->next;
            current2 = current2->next;
        }
    }

    while (current1 != NULL) {
        AddTerm(result, current1->coefficient, current1->exponent);
        current1 = current1->next;
    }

    while (current2 != NULL) {
        AddTerm(result, current2->coefficient, current2->exponent);
        current2 = current2->next;
    }

    return result;
}

Polynomial *Multiply(Polynomial *p1, Polynomial *p2) {
    Polynomial *result = init();
    Term *current1 = p1->head;
    while (current1 != NULL) {
        Term *current2 = p2->head;
        while (current2 != NULL) {
            int coefficient = current1->coefficient * current2->coefficient;
            int exponent = current1->exponent + current2->exponent;
            AddTerm(result, coefficient, exponent);
            current2 = current2->next;
        }
        current1 = current1->next;
    }
    return result;
}

int main() {
    Polynomial *p1 = init();
    Polynomial *p2 = init();

    AddTerm(p1, 3, 2);
    AddTerm(p1, 4, 1);
    AddTerm(p1, 5, 0);

    AddTerm(p2, 2, 3);
    AddTerm(p2, 3, 2);
    AddTerm(p2, 4, 1);
    AddTerm(p2, 5, 0);

    PrintPolynomial(p1);
    PrintPolynomial(p2);

    Polynomial *sum = Add(p1, p2);
    PrintPolynomial(sum);

    Polynomial *product = Multiply(p1, p2);
    PrintPolynomial(product);

    destroy(p1);
    destroy(p2);
    destroy(sum);

    return 0;
}