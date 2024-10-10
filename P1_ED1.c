//Marco Antônio Bicalho de Oliveira n° USP - 15474741 ----------------------------------main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <ctype.h>

#include "header.h" //Inclui os Protótipos


int main() {
    List* nro1 = createList();
    List* nro2 = createList();
    List* result = createList();

    readFile("nro1.txt", nro1);
    readFile("nro2.txt", nro2);

    printf("Nro1 = ");
    printList(nro1);
    printf("Nro2 = ");
    printList(nro2);

    alignLists(nro1, nro2);

    int carryOut = sumIntegerDigits(nro1, nro2, result);

    printResult(result, carryOut);

    freeList(nro1);
    freeList(nro2);
    freeList(result);

    return 0;
}

//Marco Antônio Bicalho de Oliveira n° USP - 15474741 ----------------------------------funcoes.c

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h" //Inclui os Protótipos


List* createList() {
    List* list = (List*)malloc(sizeof(List));
    list->head = list->tail = NULL;
    return list;
}

void insertDigit(List* list, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->digit = digit;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void readFile(const char* filename, List* list) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", filename);
        exit(1);
    }

    char c;
    while (fscanf(file, "%c", &c) != EOF) {
        if (isdigit(c)) {
            insertDigit(list, c - '0');
        } else if (c == 'I') {
            break;
        }
    }

    fclose(file);
}

void printList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d", current->digit);
        current = current->next;
    }
    printf("\n");
}

void printResult(List* result, int carryOut) {
    printf("Resultado = ");
    if (result->head == NULL) {
        printf("(lista vazia)");
    } else {
        printList(result);
    }
    printf("Vai-um final = %d\n", carryOut);
}

void alignLists(List* list1, List* list2) {
    int len1 = 0, len2 = 0;
    Node* current1 = list1->head;
    Node* current2 = list2->head;

    while (current1 != NULL) {
        len1++;
        current1 = current1->next;
    }

    while (current2 != NULL) {
        len2++;
        current2 = current2->next;
    }

    while (len1 < len2) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->digit = 0;
        newNode->next = list1->head;
        list1->head = newNode;
        len1++;
    }

    while (len2 < len1) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->digit = 0;
        newNode->next = list2->head;
        list2->head = newNode;
        len2++;
    }
}
	//soma_digitos_inteiros (Lista* li1,Lista* li2,Lista* li3), Retorna o vai um
int sumIntegerDigits(List* list1, List* list2, List* result) {
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    int carry = 0;

    while (current1 != NULL && current2 != NULL) {
        int sum = current1->digit + current2->digit + carry;
        insertDigit(result, sum % 10);
        carry = sum / 10;
        current1 = current1->next;
        current2 = current2->next;
    }

    return carry;
}

void freeList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}

    //soma_digitos_decimais (Lista* li1,Lista* li2,Lista* li3), Retorna o vai um
int sumDecimalDigits(List* list1, List* list2, List* result) {
    Node* current1 = list1->head;
    Node* current2 = list2->head;
    int carry = 0;

    while (current1 != NULL && current1->digit != 'D' &&
           current2 != NULL && current2->digit != 'D') {
        int sum = current1->digit + current2->digit + carry;
        carry = sum / 10;
        insertDigit(result, sum % 10);
        current1 = current1->next;
        current2 = current2->next;
    }

    return carry;
}


//Marco Antônio Bicalho de Oliveira n° USP - 15474741 ----------------------------------header.h

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    int digit;
    struct Node* next;
} Node;

typedef struct List {
    Node* head;
    Node* tail;
} List;

List* createList();
void insertDigit(List* list, int digit);
void readFile(const char* filename, List* list);
void printList(List* list);
void printResult(List* result, int carryOut);
void alignLists(List* list1, List* list2);
int sumIntegerDigits(List* list1, List* list2, List* result);
int sumDecimalDigits(List* list1, List* list2, List* result);
void freeList(List* list);

#endif // HEADER_H

----------------------------------------------------------------------Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável
TARGET = funcoes

# Arquivos fonte
SOURCES = main.c funcoes.c

# Arquivos objeto
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão
all: $(TARGET)

# Criação do executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

# Regra genérica para criar arquivos objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -f $(OBJECTS) $(TARGET)

# Execução
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run



