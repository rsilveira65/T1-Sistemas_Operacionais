from random_words import RandomWords
import sys
rw = RandomWords()
entrada = "entradas/"+sys.argv[1]
file = open(entrada, "w")
print "Gerando arquivo ",sys.argv[1]
print "Linhas "+sys.argv[2]
print "Palavras "+sys.argv[3]
for i in range(int(sys.argv[2])):
    words = rw.random_words(letter='r', count=int(sys.argv[3]))

    for i in range(len(words)):
       file.write(words[i],)

    file.write("\n")
file.close()
