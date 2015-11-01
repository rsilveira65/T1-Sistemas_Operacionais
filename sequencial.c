#include <stdio.h>
#include <string.h>
#include <time.h>

//###################################################################
//# autor:  Rafael Silveira										#
//#	data:									                    #
//# trabalho de SO sequencial									#
//###################################################################
//gcc sequencial.c -o trabso
//time ./trabso arquivo.txt a
int TAM = 130;

int busca_linha(char linha[], char entrada[]) {
  int what_len = strlen(entrada);
  int count = 0;
  char *where = linha;
  if (what_len)
    while ((where = strstr(where, entrada))) {
      where += what_len;
      count++;
    }
//printf(" Apareceu %i vezes\n",count);
return (count);
}

int main( int argc, char *argv[] )
{
  clock_t end,start;

  start = clock();
  //char BUFFER[130] = "";
  int acumulador=0;
  char line[TAM];
  FILE *fp = fopen(argv[1],"r");
  printf("-->Nome arquivo entrada: %s\n", argv[1]);
  printf("-->Nome da string: %s \n", argv[2]);
  if( fp == NULL ) {
    return 1;
  }
  while( fgets(line,TAM,fp) ) {
    //strcat(BUFFER, line);
    printf("%s\n",line);
    acumulador += busca_linha(line, argv[2]);
  }

  printf(" A String apareceu %i vezes\n",acumulador);
  //printf("-->Nome da string: %s \n", BUFFER);
  end = clock();
  printf("Tempo gasto: %4.0f ms\n\n",1000*(double)(end-start)/(double)(CLOCKS_PER_SEC));
  return 0;
}
