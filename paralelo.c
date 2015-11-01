//###################################################################
//#            autor:  Rafael Silveira										          #
//#	           data:	09-09-15							                        #
//#            trabalho-1 de SO								                      #
//###################################################################
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
//gcc paralelo.c -o trabso
//trabso 1m.txt a


#define  FALSE 0
#define  TRUE  1
#define  BUFFERVAZIO 1
#define  BUFFERCHEIO 0
#define TOTAL_THREADS 4
int TAM = 130;

pthread_mutex_t mutex[TOTAL_THREADS];
pthread_t threads[TOTAL_THREADS];

int estado = BUFFERCHEIO;
int conteudo_arquivo=1;
FILE *arquivo;

char string_entrada[80+1];
int what_len;
char linha_thread[TOTAL_THREADS][132+1];
int contador[TOTAL_THREADS];

void consumidor(void *ptr){
				//long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
				//printf ("%ld of processors online\n",nprocs);
				int thread_numero = (int)ptr;
				char *where;

				pthread_mutex_lock( &mutex[thread_numero] );  //Inicio da Seção crítica
				where = linha_thread[thread_numero];
				while ( (where = strstr( where, string_entrada ) ) ) {
							where += what_len;
							contador[thread_numero]++;
				}
				pthread_mutex_unlock(&mutex[thread_numero]);//Fim da Seção crítica
}

int main( int argc, char *argv[] ){

	int t, estado;
	int ret = 0;
	int total = 0;
	int thread_comecou[TOTAL_THREADS];
	char buffer[132+1] = "";
	clock_t end,start;

	start = clock(); //inicia contador de tempo

	strcpy( string_entrada, argv[2] ); //armazena a string de entrada na variavel string_entrada

	what_len = strlen(string_entrada); //salva tamanho da string de entrada

	for( t = 0; t < TOTAL_THREADS; t++ ) {  //inicializa variaveis
  				contador[t] = 0;
					pthread_mutex_init( &mutex[t], NULL );
					memset( linha_thread, 0, 132+1 );
					thread_comecou[t] = FALSE;
	}

	arquivo = fopen( argv[1], "r" ); //abre arquivo

	int  numero_thread = 0;
	conteudo_arquivo = fgets( buffer, TAM, arquivo ); //carrega a primeira linha do arquivo na variavel buffer

	while( conteudo_arquivo != FALSE ){  //loop enquanto existem linhas disponiveis no arquivo de entrada
			    estado = BUFFERCHEIO;
					while( estado == BUFFERCHEIO ){// enquanto nao achou thread vazia, continua aqui
									if( pthread_mutex_trylock( &mutex[numero_thread] ) == 0 ) { //testa se tem thread disponivel, retorna 0 caso de certo o lock
			        						pthread_mutex_unlock( &mutex[numero_thread] ); // libera para conseguir travar o consumidor
			        						if( thread_comecou[numero_thread] != FALSE ) {  //para não dar join na primeira execução
							  									pthread_join( threads[numero_thread], &ret ); //espera pelo termino da thread
			        						}else{
																	thread_comecou[numero_thread] = TRUE;
			        						}
			        						strcpy( linha_thread[numero_thread], buffer ); //copia buffer para linha da thread
			        						pthread_create( &threads[numero_thread], 0, consumidor, (void*)numero_thread ); //cria thread
			        						estado = BUFFERVAZIO; //sai do laço
									}
			      			numero_thread++; //incrementa o contador de threads
			      			if( numero_thread == TOTAL_THREADS ){  //caso seja o total de thread
													numero_thread = 0;  //volta a thread 0
									}

					}
					conteudo_arquivo = fgets( buffer, TAM, arquivo );  //carrega proxima linha no buffer
	}
	total = 0;


	for(t = 0; t < TOTAL_THREADS; t++ ) {
					if( thread_comecou[t] )
      						pthread_join(threads[t], &ret);
									total += contador[t]; //atualiza contador individual de cada thread na variavel total
	}

	end = clock();

	if (argv[3]){
					printf("%4.0f\n",1000*(double)(end-start)/(double)(CLOCKS_PER_SEC));
	}else{
					printf("%i \n", total);
	}

	return 0;

}
