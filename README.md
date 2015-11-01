# Trabalho 1 de SO 2015/2

 - Nome: Rafael Silveira
 - E-mail: rsilveira@inf.ufpel.edu.br

## 1. Ambiente

- MacBook Air
- Processador: Intel Core i5 1.4 GHz (quatro núcleos)
- Memória: 4 GB
- SO: OSX Yosemite versão 10.10.5


## 2. Comandos
```bash
$ make  
$ ./paralelo entradas/500m.txt roots  (retorna número de ocorrência)
$ ./paralelo entradas/500m.txt roots -t (retorna tempo de execução)

```
## 2.1 Simulação:
```bash
$ sh script.sh
```

## 2.2 Gerar entradas:
```bash
$ pip install RandomWords
$ python gerador.py entrada.txt 50000 10
argumento 1 - nome arquivo;
argumento 2 - número de linhas;
argumento 3 - palavras por linha;
```

## 3. Metodologia

O Trabalho 1 foi desenvolvido adotando a estratégia de produtor-consumidor
onde a função main (thread principal) atua como produtor lendo o arquivo de entrada
e armazenando cada linha por vez em um buffer e disponibilizando trabalho para os threads consumidores processarem.
Foi criada uma seção crítica de código contendo array de contadores protegidos por mutex (para não ser executado simultaneamente), onde cada thread é encarregado de incrementar quando for encontrada uma ocorrência da string desejada ao processar o buffer. Ao final do programa, é realizado o join e somado todos os valores contidos nos indíces do array de contadores.


Para validação do trabalho, foi criado um gerador de entradas, o qual foi usado para criar entradas de tamanhos distintos de quantidades de linhas e variando o tamanho de palavras em cada linha. Foi então, criado um script para o auxilio nas simulações, o qual executa o programa 30 vezes e calcula seu tempo médio. Ao final das simulações, os resultados foram comparados.

## 4. Desafio Encontrado:
Durante o desenvolvimento do trabalho tive problemas envolvendo condição de corrida quando utilizado apenas uma variável global com função contador de ocorrências, protegida em uma área de exclusão mutua. Havendo inconsistência nos resultados obtidos.

## 5. Resultados:
Os resultados foram obtidos com uma entradas possuindo 50.000, 500.000 e 1.000.000 de linhas com tamanho de 10 e 30 palavras e 1, 4, 8, 16, 32, 64 e 128 threads trabalhando em conjunto.
Nestas simulações, como ilustrado na Figura 1. Foi possível perceber que com o aumento no tamanho de entrada, principalmente da linha, foi possível obter um aumento de desempenho. Entretanto, com o aumento de threads, o desempenho tendeu a cair. Com 128 threads o desempenho caiu consideravelmente (Figura 2). Possivelmente devido ao tempo gasto entre escalonamento e trocas de contexto entre threads
Por fim, A Figura 3, mostra o gráfico dos quatro núcleos da CPU  processando os dados do arquivo de simulação contendo 1 milhão de linhas.

![Picture](http://i.imgur.com/5aDQokT.png)

Figura 1: Tempos e Speedup

![Picture](http://i.imgur.com/5KbWeUP.png)

Figura 2: Gráfico Threads x Tempo

![Picture](http://i.imgur.com/8FnCXnQ.png)

Figura 3: Gráfico das CPUs

## 6. Referências

- POSIX Threads Programming https://computing.llnl.gov/tutorials/pthreads/
- Linux POSIX Threads http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
- Link Entradas https://drive.google.com/folderview?id=0B4Jh8KBHbjpeczBPbFFsTTU4NUk&usp=sharing
