#include <stdio.h>
#include <stdlib.h>
#include "tree_header.h"

int main() {
    Tree* root = seed_tree();
    int option, value;

    while (1) {
        printf("\n=== Menu ===\n");
        printf("1. Inserir valor\n");
        printf("2. Remover valor\n");
        printf("3. Buscar valor\n");
        printf("4. Verificar se a árvore está vazia\n");
        printf("5. Contar total de nós\n");
        printf("6. Altura da árvore\n");
        printf("7. Profundidade de um nó\n");
        printf("8. Exibir em pré-ordem\n");
        printf("9. Exibir em em-ordem\n");
        printf("10. Exibir em pós-ordem\n");
        printf("11. Mostrar árvore detalhada (em-ordem)\n");
        printf("12. Liberar árvore e sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &value);
                if (insertion(root, value))
                    printf("Valor %d inserido com sucesso.\n", value);
                else
                    printf("Falha ao inserir ou valor já existe.\n");
                break;

            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &value);
                if (remove_node(root, value))
                    printf("Valor %d removido com sucesso.\n", value);
                else
                    printf("Valor %d não encontrado.\n", value);
                break;

            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &value);
                if (search(root, value))
                    printf("Valor %d encontrado na árvore.\n", value);
                else
                    printf("Valor %d não encontrado.\n", value);
                break;

            case 4:
                if (is_empty_tree(root))
                    printf("A árvore está vazia.\n");
                else
                    printf("A árvore não está vazia.\n");
                break;

            case 5:
                printf("Total de nós: %d\n", total_nodes(root));
                break;

            case 6:
                printf("Altura da árvore: %d\n", height(root));
                break;

            case 7:
                printf("Digite o valor para verificar profundidade: ");
                scanf("%d", &value);
                int depth_value = depth(root, value);
                if (depth_value == -1)
                    printf("Valor %d não encontrado.\n", value);
                else
                    printf("Profundidade do valor %d: %d\n", value, depth_value);
                break;

            case 8:
                printf("Exibindo em pré-ordem:\n");
                pre_order(root);
                break;

            case 9:
                printf("Exibindo em em-ordem:\n");
                in_order(root);
                break;

            case 10:
                printf("Exibindo em pós-ordem:\n");
                post_order(root);
                break;

            case 11:
                printf("Mostrando árvore detalhada em em-ordem:\n");
                show_in_order(root);
                break;

            case 12:
                free_tree(root);
                printf("Árvore liberada. Encerrando o programa.\n");
                return 0;

            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    }

    return 0;
}

