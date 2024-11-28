#include <stdio.h>
#include <stdlib.h>
#include "tree_header.h"

//Criação da tree.
Tree* seed_tree(){
    Tree* root=(Tree*)malloc(sizeof(Tree));
    if(root != NULL){
        *root = NULL;
    }
    return root;
}

void free_tree(Tree* root) {
    if (root == NULL || *root == NULL) return;

    // Liberar subárvore esquerda
    free_tree(&(*root)->left);

    // Liberar subárvore direita
    free_tree(&(*root)->right);

    // Liberar o nó raiz atual
    free(*root);
    *root = NULL; // Define o ponteiro raiz como NULL após liberar
}

int is_empty_tree(Tree *root){
 if (root == NULL || *root == NULL) return 1;

    return 0;
}

int insertion(Tree* root, int value) {
    if (root == NULL) {
        return 0; // Ponteiro para a árvore é nulo
    }

    // Alocar memória para o novo nó
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return 0; // Falha na alocação de memória
    }
    
    // Inicializar o novo nó
    new_node->info = value;
    new_node->left = NULL;
    new_node->right = NULL;

    // Inserção do primeiro nó
    if (*root == NULL) {
        *root = new_node;
    } else {
        struct Node* current = *root;
        struct Node* prev = NULL;
        
        // Procurar posição para inserir o novo nó
        while (current != NULL) {
            prev = current;
            if (value == current->info) {
                free(new_node); // Elemento já existe, liberar o nó
                return 0;       // Não permite duplicatas
            }
            if (value > current->info) {
                current = current->right;
            } else {
                current = current->left;
            }
        }

        // Inserir o novo nó como filho esquerdo ou direito
        if (value > prev->info) {
            prev->right = new_node;
        } else {
            prev->left = new_node;
        }
    }

    return 1; // Inserção bem-sucedida
}

int search(Tree* root,int value){
    if(root == NULL) return 0;

    struct Node* current = *root;
    while( current != NULL){
        if(value == current->info){
            return 1;
        }
        if(value > current->info){
            current = current->right;
        }else{
            current =current->left;
        }
    }

    return 0;
}

struct Node* remove_current(struct Node* current){
    struct Node *no1,*no2;

    if(current->left == NULL){
        no2 = current->right;
        free(current);
        return no2;
    }
     
    no1 = current;
    no2 = current->left;

    while(no2->right != NULL){
        no1 = no2;
        no2 = no2->right;
    }
    // no2 é o nó anterior a root na ordem left-root-right
    //no1 é o pai de no2

    if(no1 != current){
        no1->right = no2->left;
        no2->left = current->left;
    }

    no2->right = current->right;
    free(current);
    return no2;

}

int remove_node(Tree* root, int value){
    if(root == NULL){
        return 0;
    }

    struct Node* prev = NULL;
    struct Node* current = *root;

    while( current != NULL){
        if(value == current->info){
            *root = remove_current(current);
        }else{
            if(prev->right == current){
                prev->right = remove_current(current);
            }else{ prev->left = remove_current(current);}
        }
        return 1;
    
        prev = current;
        if(value > current->info){
            current = current->right;
        }else{ current = current->left;}
    }
    return 0;
}

int total_nodes(Tree* root) {
    if (root == NULL || *root == NULL) return 0;

    int cont_left = total_nodes(&((*root)->left));
    int cont_right = total_nodes(&((*root)->right));

    return cont_left + cont_right + 1;
}

int height(Tree* root) {
    if (root == NULL || *root == NULL) return 0;

    int height_left = height(&((*root)->left));
    int height_right = height(&((*root)->right));

    return (height_left > height_right ? height_left : height_right) + 1;
}

int depth(Tree* root, int value) {
    if (root == NULL || *root == NULL) return -1;

    if ((*root)->info == value) {
        return 0;
    }

    int depth_left = depth(&((*root)->left), value);
    int depth_right = depth(&((*root)->right), value);

    // Se o valor foi encontrado em uma das subárvores, incrementa a profundidade
    if (depth_left != -1) {
        return depth_left + 1;
    } else if (depth_right != -1) {
        return depth_right + 1;
    } else {
        return -1; // Valor não encontrado na árvore
    }
}

void pre_order(Tree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        printf("%d\n", (*root)->info);      // Visita o nó raiz
        pre_order(&((*root)->left));        // Travessia na subárvore esquerda
        pre_order(&((*root)->right));       // Travessia na subárvore direita
    }
}

void in_order(Tree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        in_order(&((*root)->left));         // Travessia na subárvore esquerda
        printf("%d\n", (*root)->info);      // Visita o nó raiz
        in_order(&((*root)->right));        // Travessia na subárvore direita
    }
}

void post_order(Tree* root) {
    if (root == NULL) return;
    if (*root != NULL) {
        post_order(&((*root)->left));       // Travessia na subárvore esquerda
        post_order(&((*root)->right));      // Travessia na subárvore direita
        printf("%d\n", (*root)->info);      // Visita o nó raiz
    }
}

// funções adiconais de árvore.

void search_pre_order(Tree *root, int value, int *find){
    if(root == NULL)
        return;
    if(*find)
        return;
    if(*root != NULL){
        if(value == (*root)->info){
        printf("Achou: %d! \n", (*root)->info);
        *find = 1;
        }
        search_pre_order(& ((*root)->left),value,find);
        search_pre_order(& ((*root)->right),value,find);

    }
}

void show_in_order(Tree *root){
    if(root == NULL)
        return;
    if(*root != NULL){
        printf("Atual: %d - vai para a esquerda \n", (*root)->info);
        show_in_order(& ((*root)->left));
        printf("Dado: %d\n", (*root)->info);
        printf("Atual: %d - vai para a direita \n",(*root)->info);
        show_in_order(& ((*root)->right));
        printf("Feito: %d \n", (*root)->info);
    }
}