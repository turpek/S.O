/*
Criação de processos em UNIX, com impressão de valores de variável.

Compilar com gcc -Wall fork-print.c -o fork-print

Carlos Maziero, DINF/UFPR 2020
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
  int retval, x;

  // 1. Inicialização no processo original (Pai):
  // A variável 'x' é alocada na pilha (stack) do processo pai com valor 0.
  x = 0;

  // 2. Chamada de sistema fork():
  // Duplica o processo. O Kernel cria uma cópia completa do espaço de endereçamento
  // do pai para o filho (incluindo código, dados e pilha).
  // A partir deste ponto, o processo Pai e o processo Filho possuem instâncias
  // SEPARADAS da variável 'x' em suas respectivas memórias virtuais.
  retval = fork();

  // 3. Primeira impressão executada por AMBOS os processos:
  // Tanto o pai quanto o filho leem suas próprias cópias de 'x', ambas valendo 0.
  // A ordem de quem imprime primeiro (45251 ou 45252) depende da CPU/escalonador.
  printf ("No processo %5d x vale %d\n", getpid(), x);

  if (retval < 0)
  {
    perror ("Erro");
    exit (1);
  }
  else if (retval > 0) // Fluxo do PROCESSO PAI
  {
    // O pai redefine explicitamente sua própria variável 'x' para 0.
    x = 0;

    // Entra em estado BLOQUEADO (waiting), aguardando o filho terminar.
    wait (0);
  }
  else // Fluxo do PROCESSO FILHO
  {
    // O filho incrementa a SUA cópia local de 'x', que passa a valer 1.
    // IMPORTANTE: Essa alteração NÃO afeta a variável 'x' do pai,
    // pois os processos possuem isolamento total de memória (Copy-on-Write).
    x++;

    // O filho dorme por 5 segundos antes de imprimir.
    sleep (5);
  }

  // 4. Segunda impressão:
  // - O Filho acorda após 5s, imprime x = 1 e encerra com exit(0).
  // - O término do filho desbloqueia o Pai em wait(0).
  // - O Pai retoma sua execução, imprime seu próprio x (que permaneceu 0) e encerra.
  printf ("No processo %5d x vale %d\n", getpid(), x);
  exit (0);
}
