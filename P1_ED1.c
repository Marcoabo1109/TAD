//Marco Antônio Bicalho de Oliveira n° USP - 15474741 -------------------main.c

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

    // Lê os arquivos
    readFile("nro1.txt", nro1);
    readFile("nro2.txt", nro2);

    // Imprime os números lidos
    printf("Nro1 = ");
    printList(nro1);
    printf("Nro2 = ");
    printList(nro2);

    // Verifica o tipo de operação (inteiro ou decimal)
    char operationType = nro1->tail->digit;

    // Alinha as listas
    alignLists(nro1, nro2);

    int carryOut;
    if (operationType == 'I') {
        carryOut = sumIntegerDigits(nro1, nro2, result);
    } else if (operationType == 'D') {
        carryOut = sumDecimalDigits(nro1, nro2, result);
    } else {
        printf("Tipo de operação inválido.\n");
        return 1;
    }

    // Imprime o resultado
    printf("Resultado = ");
    printList(result);
    printf("Vai-um final = %d\n", carryOut);

    // Libera a memória
    freeList(nro1);
    freeList(nro2);
    freeList(result);

    return 0;
}



//Marco Antônio Bicalho de Oliveira n° USP - 15474741 ---------------------funcoes.c

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

    int digit;
    char c;
    while (fscanf(file, "%c", &c) != EOF) {
        if (isdigit(c)) {
            digit = c - '0';
            insertDigit(list, digit);
        } else if (c == 'I' || c == 'D') {
            insertDigit(list, c);
            break;
        }
    }

    fclose(file);
}

void printList(List* list) {
    Node* current = list->head;
    while (current != NULL) {
        if (current->digit == 'I' || current->digit == 'D') {
            printf("%c", current->digit);
        } else {
            printf("%d", current->digit);
        }
        current = current->next;
    }
    printf("\n");
}
    //Alinhamento dos números na lista
void alignLists(List* list1, List* list2) {
    int len1 = 0, len2 = 0;
    Node* current1 = list1->head;
    Node* current2 = list2->head;

    while (current1->next != NULL && current1->digit != 'I' && current1->digit != 'D') {
        len1++;
        current1 = current1->next;
    }

    while (current2->next != NULL && current2->digit != 'I' && current2->digit != 'D') {
        len2++;
        current2 = current2->next;
    }

    if (current1->digit == 'I') {
        // Alinhamento para números inteiros
        while (len1 < len2) {
            insertDigit(list1, 0);
            len1++;
        }
        while (len2 < len1) {
            insertDigit(list2, 0);
            len2++;
        }
    } else if (current1->digit == 'D') {
        // Alinhamento para números decimais
        while (len1 < len2) {
            current1 = list1->head;
            while (current1->next != NULL && current1->next->digit != 'D') {
                current1 = current1->next;
            }
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->digit = 0;
            newNode->next = current1->next;
            current1->next = newNode;
            len1++;
        }
        while (len2 < len1) {
            current2 = list2->head;
            while (current2->next != NULL && current2->next->digit != 'D') {
                current2 = current2->next;
            }
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->digit = 0;
            newNode->next = current2->next;
            current2->next = newNode;
            len2++;
        }
    }
}

    // soma_digitos_inteiros (Lista* li1,Lista* li2,Lista* li3), Retorna o vai um
int sumIntegerDigits(List* list1, List* list2, List* result) {
    Node* current1 = list1->tail;
    Node* current2 = list2->tail;
    int carry = 0;

    while (current1 != NULL && current1->digit != 'I' &&
           current2 != NULL && current2->digit != 'I') {
        int sum = current1->digit + current2->digit + carry;
        carry = sum / 10;
        insertDigit(result, sum % 10);
        current1 = current1->next;
        current2 = current2->next;
    }

    // Inverte a lista de resultado
    Node* prev = NULL;
    Node* current = result->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    result->head = prev;

    return carry;
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

void freeList(List* list) {
    Node* current = list->head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(list);
}



//Marco Antônio Bicalho de Oliveira n° USP - 15474741 -------------------header.h

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Estrutura para um nó da lista encadeada
typedef struct Node {
    int digit;
    struct Node* next;
} Node;

// Estrutura para a lista encadeada
typedef struct List {
    Node* head;
    Node* tail;
} List;

// Protótipos das funções
List* createList();
void insertDigit(List* list, int digit);
void readFile(const char* filename, List* list);
void printList(List* list);
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



