import sys

nomeArq = sys.argv[1]
arq = open(nomeArq,'r')
conteudoArq = arq.read()
vetorPalavras = conteudoArq.split()

linhas = 1

for caractere in conteudoArq:
    if caractere == '\n':
        linhas += 1

print(len(vetorPalavras))
print(linhas)

arq.close()
