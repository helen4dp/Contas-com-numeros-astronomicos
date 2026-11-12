#ifndef NUMERO_H
#define NUMERO_H

typedef struct numero Numero;

// Criação e destruição
int numero_criar(Numero **numero, int sinal);
int numero_destruir(Numero **numero);

// Manipulação dos blocos
// UTILIZE ARMAZENAMENTO DO MENOS SIGNIFICATIVO PARA O MAIS SIGNIFICATIVO
int numero_inserir_bloco(Numero *numero, int bloco); // Recebe um bloco e o insere no número

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
int somar_modulos(
    const Numero *numero1,
    const Numero *numero2,
    Numero **resultado
);

int subtrair_modulos(
    const Numero *numero1,
    const Numero *numero2,
    Numero **resultado
);

// Soma considerando os sinais
int numero_somar(
    const Numero *numero1,
    const Numero *numero2,
    Numero **resultado
);

#endif
