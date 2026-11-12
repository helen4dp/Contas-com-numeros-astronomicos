# Contas-com-numeros-astronomicos

Existem diversos contextos nos quais precisamos manipular números muito grandes.
Por exemplo, há números primos conhecidos com milhões de dígitos. Nesses casos, os tipos
inteiros primitivos não são suficientes para armazenar os valores completos.

Uma maneira de representar esses números é utilizar uma lista encadeada, distribuindo
os dígitos em blocos armazenados nos nós da lista. Por exemplo, o número 93.000.000.000
pode ser dividido nos blocos 930, 0000 e 0000.

Se o bloco menos significativo estiver no início da lista, a representação será:

                  (0000) −→ (0000) −→ (930) −→ NULL
                  início

Nesse exemplo, cada bloco representa quatro posições decimais, exceto o mais significativo,
que pode possuir menos dígitos. Os zeros são exibidos no desenho para evidenciar essas
posições; o valor inteiro armazenado em cada um dos dois primeiros nós é zero.

O objetivo deste trabalho é desenvolver um programa capaz de realizar somas e
comparações entre números inteiros de tamanho arbitrário utilizando essa representação.
