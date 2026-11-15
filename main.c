/*
 * Trabalho 3 - Números Astronômicos
 * Estruturas de Dados I - ICMC-USP - 2026
 *
 * Integrantes:
 *   Mariana Alvares - Nº USP 17913006  
 *   Helena Domingues Perusso - Nº USP 17895380  
 *   Vitória Luiza Brasil Barbosa - Nº USP 18188963
 *   Adriana Rodrigues de Araujo - Nº USP 17991147
 *   Renan Freire Pereira - Nº USP 17921902
 *
 * Programa principal: lê n comandos (soma, maior, menor, igual), cada um seguido de dois números inteiros de tamanhos variáveis, e imprime o
 * resultado de cada operação. Os números são manipulados apenas pelas funções da interface do TAD (Lista.h).
 */

#include <stdio.h>
#include <string.h>
#include "Lista.h"

#define TAM_COMANDO 16 // Maior comando cabe sobrando espaço.

// Usei static para as duas funções para que só main.c consiga acessar.

/*
 * Executa uma comparação (igual, maior ou menor) entre a e b
 * e imprime True ou False.
 * Retorna 1 em caso de sucesso e 0 em caso de erro.
 */
static int executar_comparacao(const char *comando, const Numero *a, const Numero *b)
{
    int resultado = 0;
    int ok;

    if (strcmp(comando, "igual") == 0) // strcmp usado para verificar se as strings são iguais 
        ok = numero_igual(a, b, &resultado);
    else if (strcmp(comando, "maior") == 0)
        ok = numero_maior(a, b, &resultado);
    else if (strcmp(comando, "menor") == 0)
        ok = numero_menor(a, b, &resultado);
    else
        return 0; // comando desconhecido

    if (!ok)
        return 0;

    printf("Resultado:: %s\n", resultado ? "True" : "False"); // se o resultado for != de 0 usa True
    return 1;
}

/*
 * Calcula a + b e imprime o resultado.
 * O número da soma é criado dentro de numero_somar e liberado aqui.
 * Retorna 1 em caso de sucesso e 0 em caso de erro.
 */
static int executar_soma(const Numero *a, const Numero *b)
{
    Numero *soma = numero_somar(a, b);
    if (soma == NULL)
        return 0;

    printf("Resultado:: ");
    imprimir_numero(soma);
    printf("\n");

    numero_destruir(&soma); // passa o end. do ponteiro para que a numero_destruir faça soma=NULL depois do free !! importante 
    return 1;
}

int main(void)
{
    int n;

    // primeira linha: quantidade de operações
    if (scanf("%d", &n) != 1)
        return 1; // proteção caso scanf falhe 

    for (int i = 0; i < n; i++)
    {
        char comando[TAM_COMANDO];

        // le o nome do comando (limite de 15 caracteres evita estouro do vetor)
        if (scanf("%15s", comando) != 1)
            return 1;

        // cria os dois números: o sinal é definido durante a leitura, o 1 aqui funciona de placeholder
        Numero *a = numero_criar(1);
        Numero *b = numero_criar(1);

        if (a == NULL || b == NULL || !ler_numero(a) || !ler_numero(b))
        {
            // falha de alocação ou de leitura: libera o que existir e encerra
            numero_destruir(&a);
            numero_destruir(&b);
            return 1;
        }

        int ok;
        if (strcmp(comando, "soma") == 0)
            ok = executar_soma(a, b);
        else
            ok = executar_comparacao(comando, a, b);

        // os números desta linha não são mais necessários
        numero_destruir(&a);
        numero_destruir(&b);

        if (!ok)
            return 1;
    }

    return 0;
}
