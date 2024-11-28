// tree_header.h

#ifndef TREE_HEADER_H
#define TREE_HEADER_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó da árvore
struct Node {
    int info;
    struct Node* left;
    struct Node* right;
};

// Tipo para facilitar a manipulação da árvore
typedef struct Node* Tree;

// Funções de criação e liberação de árvore
Tree* seed_tree();
void free_tree(Tree* root);

// Funções de verificação e inserção
int is_empty_tree(Tree *root);
int insertion(Tree* root, int value);

// Funções de busca e remoção
int search(Tree* root, int value);
struct Node* remove_current(struct Node* current);
int remove_node(Tree* root, int value);

// Funções de contagem e profundidade
int total_nodes(Tree* root);
int height(Tree* root);
int depth(Tree* root, int value);

// Funções de travessia
void pre_order(Tree* root);
void in_order(Tree* root);
void post_order(Tree* root);

// Funções adicionais de busca e exibição
void search_pre_order(Tree* root, int value, int* find);
void show_in_order(Tree* root);

#endif // TREE_HEADER_H
