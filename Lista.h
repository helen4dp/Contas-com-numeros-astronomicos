#ifndef NUMERO_H
#define NUMERO_H

typedef struct numero Numero;

// Criação e destruição
Numero *numero_criar(int sinal);
int numero_destruir(Numero **numero);

// Manipulação dos blocos
// UTILIZE ARMAZENAMENTO DO MENOS SIGNIFICATIVO PARA O MAIS SIGNIFICATIVO
int numero_inserir_bloco(Numero *n, int bloco); // Recebe um bloco e o insere no número

// Entrada e saída
int ler_numero(Numero *numero); // Lê um número e utiliza a função numero_inserir_bloco
int imprimir_numero(const Numero *numero);

// Comparações
int numero_comparar_modulo(
    const Numero *numero1,
    const Numero *numero2,
    int *resultado
);

int numero_igual(
    const Numero *numero1,
    const Numero *numero2,
    int *resultado
);

int numero_menor(
    const Numero *numero1,
    const Numero *numero2,
    int *resultado
);

int numero_maior(
    const Numero *numero1,
    const Numero *numero2,
    int *resultado
);

// Operações com módulos
Numero *somar_modulos(
    const Numero *numero1,
    const Numero *numero2
);

Numero *subtrair_modulos(
    const Numero *numero1,
    const Numero *numero2
);

// Soma considerando os sinais
Numero *numero_somar(
    const Numero *numero1,
    const Numero *numero2
);

#endif
