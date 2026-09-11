/*
Criação de processos em UNIX, com execução de outro binário

Compilar com gcc -Wall fork-execve.c -o fork-execve

Carlos Maziero, DINF/UFPR 2020
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[], char *envp[])
{
int retval;

  // Identificação inicial do processo original (Pai):
  printf ("Ola, sou o processo %5d\n", getpid());

  // Criação do processo filho:
  // Duplica o processo pai criando um espaço de memória próprio para o filho.
  retval = fork();

  // Print mostrado por ambos os processos logo após o fork:
  // Pai imprime retval = PID_do_Filho; Filho imprime retval = 0.
  printf ("[retval: %5d] sou %5d, filho de %5d\n", retval, getpid(), getppid());

  if (retval < 0)       // Falha no fork()
  {
    perror ("Erro: ");
    exit (1);
  }
  else if (retval > 0)  // Fluxo do PROCESSO PAI
  {
    // O Pai suspende sua execução e aguarda o término do filho.
    wait (0);
  }
  else                  // Fluxo do PROCESSO FILHO
  {
    // A chamada execve(caminho, argumentos, ambiente) SUBSTITUI completamente
    // o espaço de endereçamento do filho pelo
    // binário executável "/bin/date". O PID permanece o mesmo.
    //
    // ATENÇÃO: Se o execve for bem-sucedido, ele NUNCA RETORNA!
    // Todo o código subsequente deste arquivo é descartado da memória do filho.
    execve ("/bin/date", argv, envp);

    // Esta linha SÓ será executada se o execve FALHAR (ex: arquivo não encontrado).
    perror ("Erro");
  }

  // Em execução NORMAL (sucesso do execve): APENAS O PAI chega aqui, pois o
  // filho virou o programa 'date' e encerrou dentro dele próprio.
  // Em caso de FALHA no execve: AMBOS (Pai e Filho) chegam aqui e imprimem o tchau.
  printf ("Tchau de %5d!\n", getpid());
  exit (0);
}
