#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(void)
{
    int i;
    int fd[2];
    pid_t pid; // Variável para armazenar o pid

    // Criando nosso Pipe
    if(pipe(fd)<0) {
        perror("pipe") ;
        return -1 ;
    }

    // Criando o processo filho
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    // Processo Pai
    if (pid > 0)
    {
        // fechar a leitura, porque no pai vamos escrever
        close(fd[0]);
        srand( (unsigned)time(NULL) );
        int var[2];
        for(i = 0;i<2;i++)
        {
          var[i] = rand()%101;
          printf("int gerado pelo processo pai: %d\n", var[i]);
        }

        /* Escrevendo o inteiro no pipe */
        write(fd[1], var, sizeof(var));
        exit(0);
    }
    /* Processo Filho*/
    else
    {
        int var2[2];

        // fechar a escrita porque no filho vamos ler
        close(fd[1]);

        // lendo o que foi escrito
        read(fd[0], var2, sizeof(var2));
        for(i = 0;i<2;i++)
        {
          var2[i] = var2[i]*2;
          printf("resultado multiplicado por 2: %d\n", var2[i]);
        }
      printf("\n");
      exit(0);
    }
    return(0);
}
