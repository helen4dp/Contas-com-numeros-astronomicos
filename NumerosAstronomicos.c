#include <stdio.h>
#include <stdlib.h>
#include "NumerosAstronomicos.h"

struct posicao
{
    int bloco;                    // Bloco de 0 até 9999
    struct posicao *prox_posicao; // Próximo bloco
    struct posicao *posicao_anterior;
};

typedef struct posicao Posicao;

typedef struct numero
{
    int sinal;                 // 0 - Negativo; 1 - Positivo
    Posicao *primeira_posicao; // Ponteiro para a primeira posicao
    Posicao *ultima_posicao;   // Ponteiro para a última posicao
} Numero;

int numero_inserir_bloco(Numero *numero, int bloco)
{
  if(numero == NULL) return 0;
  if(bloco < 0) bloco = bloco * -1;

  Posicao *novo = malloc(sizeof(Posicao));
  if(novo == NULL) return 0;

  novo->posicao_anterior = NULL;
  novo->prox_posicao = numero->primeira_posicao;
  novo->bloco = bloco;

  if(numero->primeira_posicao != NULL){
    numero->primeira_posicao->posicao_anterior = novo;
  } else{
    numero->ultima_posicao = novo;
  }

  numero->primeira_posicao = novo;
  return 1;
}

int numero_criar(Numero **numero, int sinal)
{
        if(sinal != 1 && sinal != 0) return 0;

    *numero = malloc(sizeof(Numero));
    if (*numero == NULL)
        return 0;

    (*numero)->primeira_posicao = NULL;
    (*numero)->ultima_posicao = NULL;
    (*numero)->sinal = sinal;
    return 1;
}

int numero_destruir(Numero **numero)
{
    if(numero == NULL || *numero == NULL) return 0;

    Posicao *tmp = (*numero)->primeira_posicao;

    while(tmp != NULL){
        Posicao *aux = tmp->prox_posicao;
        free(tmp);
        tmp = aux;
    }

    free(*numero);
    *numero = NULL;

    return 1;
}

int ler_numero(Numero *numero)
{

    // Analisando se o numero existe
    if (numero == NULL)
        return 0;

    // Criando um vetor dinamico e variaveis que indicam o tamanho atual e a capaidade
    char *vetor = NULL;
    size_t tamanho = 0, capacidade = 0;

    // Pulando caracteres não necessários
    int c = getchar();
    while (c == ' ' || c == '\n' || c == '\t' || c == '\r')
    { // Aqui a ideia é que tudo o que não for numero ou sinal seja pulado, já que o getchar lê um caractere, e o while faz ele continuar lendo (e apenas lendo) até que nseja um sinal ou um numero
        c = getchar();
    }

    // Checando o sinal
    numero->sinal = 1; // Colocamos 1 em sinal para indicar positivo, se não for, vai entrar no if
    if (c == '-')
    {
        numero->sinal = 0; // Se o primeiro caracter que não entra na lista do while foi ' - ', então o numero é negativo, e guardamos isso na variavel sinal da struct
        c = getchar();
    }

    while (c >= '0' && c <= '9') // como estamos analisando caracteres, '' é necessário, e a comparação feita aqui analisa os numeros referentes a esses caractes na tabela ASCII
    {
        if (tamanho == capacidade)
        { // Se vetor não tem mais espaço:

            // Se vetor vazio, reserva 64 bytes
            if (capacidade == 0)
            {
                capacidade = 64;
            }
            // Se vetor cheio, dobra os bits reservados
            else
            {
                capacidade = capacidade * 2;
            }

            char *tmp = realloc(vetor, capacidade); // alocando um vetor temporario com a nova capacidade que desejamos
            if (tmp == NULL)
            {                // Se esse vetor continua nulo apos a locacao, abemos que não existe mais memoria continua que suporte essa capacidade
                free(vetor); // liberamos nossa vetor pois nao e possivel ler o numero completo
                return 0;    // retorna 0 para indicar que a operacao deu errado
            }

            // Se não entra no if, quer dizer que o vetor foi alocado com sucesso, logo, ainda há memoria para tal
            vetor = tmp; // vetor aponta para tmp
        }
        vetor[tamanho++] = (char)c; // adicionando o proximo digito ao vetor
        c = getchar();              // proximo digito
    }

    if (c != EOF)
    {                     // Se houver outro numero depois e não for o final, precisamos preservar o digito que se segue
        ungetc(c, stdin); // por isso, devolvemos ele a entrada "deslendo" ele
    }

    if (tamanho == 0)
    {                // se o tamanho nao mudar, quer dizer que nao ha numero
        free(vetor); // entao podemos liberar o vetor
        return 0;
    }

    // Saindo do while, todo o numero foi alocado no vetor
    // Agora vamos verificar se exitem 0's a esquerda:

    size_t inicio_real = 0;
    while (inicio_real < tamanho - 1 && vetor[inicio_real] == '0')
    {
        inicio_real++;
    }

    // Caso o numero seja 0 (00000000 = 0000 = 0), 0 tem de ser sempre positivo
    if (tamanho - inicio_real == 1 && vetor[inicio_real] == '0')
    {
        numero->sinal = 1;
    }

    //
    size_t fim = tamanho;
    while (fim > inicio_real)
    {
        size_t inicio;

        if (fim - inicio_real >= 4)
        {
            inicio = fim - 4;
        }
        else
        {
            inicio = inicio_real;
        }

        // Tranformando os digitos em numeros:
        int bloco = 0;
        for (size_t j = inicio; j < fim; j++)
        {
            bloco = bloco * 10 + (vetor[j] - '0'); // Avança o numero uma casa para a esquerda e adiciona o proximo.
        } // vetor[j] - '0' faz: numero ASCII de j - numero ASCII de 0, essa subtração da j em numero

        if (!numero_inserir_bloco(numero, bloco))
        {                // se não deu certo de inserir o bloco
            free(vetor); // libera o vetor
            return 0;    // e retorna zero para avisar que a operacao deu errado
        }

        fim = inicio;
    }

    free(vetor);
    return 1; // avisa que deu certo
}

int imprimir_numero(const Numero *numero)
{
    if(numero == NULL) return 0;

    if (numero->sinal == 0)
    {
        printf("-");
    }

    Posicao *tmp = numero->ultima_posicao;
    printf("%d", tmp->bloco);
    tmp = tmp->posicao_anterior;

    while (tmp != NULL)
    {
        printf("%04d", tmp->bloco);
        tmp = tmp->posicao_anterior;
    }

    return 1;
}

// IMPORTANTE!
// Para todas as proximas funcoes, é preciso CRIAR UM NUMERO para o resultado. OU SEJA, chamem as funcoes: criar numero, ler numero e imprimir numero, para o resultado!

//-1	Módulo do primeiro é menor
// 0	Módulos iguais
// 1	Módulo do primeiro é maior




int numero_comparar_modulo(const Numero *numero1, const Numero *numero2, int *resultado)
{
    // verificando se os ponteiros são válidos
    if (numero1 == NULL || numero2 == NULL || resultado == NULL)
    {
        return 0;
    }

    // verificando se os números possuem blocos
    if (numero1->primeira_posicao == NULL || numero1->ultima_posicao == NULL ||
        numero2->primeira_posicao == NULL || numero2->ultima_posicao == NULL)
    {
        return 0;
    }

    // contando a quantidade de blocos de cada número
    size_t quantidade1 = 0;
    size_t quantidade2 = 0;

    const Posicao *tmp = numero1->primeira_posicao;

    while (tmp != NULL)
    {
        quantidade1++;
        tmp = tmp->prox_posicao;
    }

    tmp = numero2->primeira_posicao;

    while (tmp != NULL)
    {
        quantidade2++;
        tmp = tmp->prox_posicao;
    }

    // se um número possui mais blocos, seu módulo é maior
    if (quantidade1 > quantidade2)
    {
        *resultado = 1;
        return 1;
    }

    if (quantidade1 < quantidade2)
    {
        *resultado = -1;
        return 1;
    }

    // se possuem a mesma quantidade de blocos, precisamos comparar seus valores
    // começando pelo bloco mais significativo
    const Posicao *p1 = numero1->ultima_posicao;
    const Posicao *p2 = numero2->ultima_posicao;

    while (p1 != NULL && p2 != NULL)
    {
        if (p1->bloco > p2->bloco)
        {
            *resultado = 1;
            return 1;
        }

        if (p1->bloco < p2->bloco)
        {
            *resultado = -1;
            return 1;
        }

        // passando para o bloco anterior de cada número
        p1 = p1->posicao_anterior;
        p2 = p2->posicao_anterior;
    }

    // se todos os blocos forem iguais, os módulos também são iguais
    if (p1 != NULL || p2 != NULL)
    {
        return 0;
    }

    *resultado = 0;
    return 1;
}


int numero_igual(const Numero *numero1, const Numero *numero2, int *resultado)
{
    // verificando se os ponteiros são válidos
    if (numero1 == NULL || numero2 == NULL || resultado == NULL)
    {
        return 0;
    }

    // se os sinais forem diferentes, os números não são iguais
    if (numero1->sinal != numero2->sinal)
    {
        *resultado = 0;
        return 1;
    }

    // comparando os módulos dos números
    int comparacao;

    if (!numero_comparar_modulo(numero1, numero2, &comparacao))
    {
        return 0;
    }

    // se os módulos forem iguais, os números também são iguais
    *resultado = (comparacao == 0);

    return 1;
}


int numero_menor(const Numero *numero1, const Numero *numero2, int *resultado)
{
    // verificando se os ponteiros são válidos
    if (numero1 == NULL || numero2 == NULL || resultado == NULL)
    {
        return 0;
    }

    // se o primeiro for negativo e o segundo positivo, o primeiro é menor
    if (numero1->sinal == 0 && numero2->sinal == 1)
    {
        *resultado = 1;
        return 1;
    }

    // se o primeiro for positivo e o segundo negativo, o primeiro não é menor
    if (numero1->sinal == 1 && numero2->sinal == 0)
    {
        *resultado = 0;
        return 1;
    }

    // comparando os módulos quando os sinais são iguais
    int comparacao;

    if (!numero_comparar_modulo(numero1, numero2, &comparacao))
    {
        return 0;
    }

    // quando os dois são negativos, a comparação dos módulos é invertida
    if (numero1->sinal == 0)
    {
        *resultado = (comparacao == 1);
    }
    else
    {
        *resultado = (comparacao == -1);
    }

    return 1;
}


int numero_maior(const Numero *numero1, const Numero *numero2, int *resultado)
{
    // verificando se os ponteiros são válidos
    if (numero1 == NULL || numero2 == NULL || resultado == NULL)
    {
        return 0;
    }

    // se o primeiro for positivo e o segundo negativo, o primeiro é maior
    if (numero1->sinal == 1 && numero2->sinal == 0)
    {
        *resultado = 1;
        return 1;
    }

    // se o primeiro for negativo e o segundo positivo, o primeiro não é maior
    if (numero1->sinal == 0 && numero2->sinal == 1)
    {
        *resultado = 0;
        return 1;
    }

    // comparando os módulos quando os sinais são iguais
    int comparacao;

    if (!numero_comparar_modulo(numero1, numero2, &comparacao))
    {
        return 0;
    }

    // quando os dois são negativos, a comparação dos módulos é invertida
    if (numero1->sinal == 0)
    {
        *resultado = (comparacao == -1);
    }
    else
    {
        *resultado = (comparacao == 1);
    }

    return 1;
}








// Operações com módulos
int somar_modulos(
    const Numero *numero1,
    const Numero *numero2,
    Numero **resultado) {
        return 1;
    }

int subtrair_modulos(
    const Numero *numero1,
    const Numero *numero2,
    Numero **resultado) {
        return 1;
    }

// Soma considerando os sinais
int numero_somar(const Numero *numero1, const Numero *numero2, Numero **resultado)
{
    return 1;
}
