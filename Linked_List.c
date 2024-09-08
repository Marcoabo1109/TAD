//Header.h -------------------------------------------------
#ifndef LINKED_LIST_ADT_H
#define LINKED_LIST_ADT_H

typedef struct node {
        void* data;
        struct node* next;
} Node;

Node* create_list();
void free_list(Node* list);
void insert_at_begin(Node** list, void* data);
void insert_at_end(Node** list, void* data);
void insert_sorted(Node** list, void* data, int (* compare_func)(void*, void*));                       
void print_list(Node* list, void (* print_func)(void *));                                               
#endif


// linked_list_adt.c -----------------------------------------------

#include "linked_list_adt.h"
#include <stdlib.h>
#include <stdio.h>

Node* create_list() {
    return NULL;
}

void free_list(Node* list) {
    Node* current = list;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void insert_at_begin(Node** list, void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = *list;
    *list = new_node;
}

void insert_at_end(Node** list, void* data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;

    if (*list == NULL) {
        *list = new_node;
    } else {
        Node* current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void insert_sorted(Node** list, void* data, int (*compare_func)(void*, void*)) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        exit(1);
    }
    new_node->data = data;

    if (*list == NULL || compare_func(data, (*list)->data) <= 0) {
        new_node->next = *list;
        *list = new_node;
    } else {
        Node* current = *list;
        while (current->next != NULL && compare_func(data, current->next->data) > 0) {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

void print_list(Node* list, void (*print_func)(void*)) {
    Node* current = list;
    while (current != NULL) {
        print_func(current->data);
        printf(" -> ");
        current = current->next;
    }
    printf("NULL\n");
}

// main.c -----------------------------------------------------
#include "linked_list_adt.h"
#include <stdio.h>
#include <stdlib.h>

void print_int(void* data) {
    printf("%d", *(int*)data);
}

int compare_int(void* a, void* b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    Node* list = create_list();

    int* num1 = malloc(sizeof(int));
    int* num2 = malloc(sizeof(int));
    int* num3 = malloc(sizeof(int));
    *num1 = 10;
    *num2 = 20;
    *num3 = 15;

    insert_at_begin(&list, num1);
    insert_at_end(&list, num2);
    insert_sorted(&list, num3, compare_int);

    printf("Lista: ");
    print_list(list, print_int);

    free_list(list);
    free(num1);
    free(num2);
    free(num3);

    return 0;
}
//Makefile ------------------------------------------------
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Nome do executável
TARGET = lista_encadeada

# Arquivos fonte
SOURCES = main.c linked_list_adt.c

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
