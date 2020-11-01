#include <stdio.h>
#include <string.h>

struct SRegistro {
    int id_inscricao;
    char curso[20];
    char cpf[15];
    char dataNacimento[11];
    char sexo;
    char email[40];
    char opcaoQuadro;
};
typedef struct SRegistro Registro;

int buscaBinaria(FILE *arquivo, Registro registro)
{
    int fim, ini, meio, count = 0, achei;
    long tam;
    Registro buffer;
    ini = 0; //primeiro byte do arquivo
    fseek(arquivo, 0, SEEK_END); //Cabeça de leitura no final do arquivo.
    tam = ftell(arquivo); //tamanho do arquivo em bytes
    rewind(arquivo); //volta a cabeça de leitura pro inicio do arquivo

    fim = (tam/sizeof(Registro))-1;
    
    while (ini <= fim)
    {
        count++;
        meio = (fim+ini)/2; //calcula o meio
        fseek(arquivo, meio * sizeof(Registro), SEEK_SET); //posiciona a cabeça de leitura no meio
        fread(&buffer, sizeof(Registro), 1, arquivo); //Lê o registro do meio

        if(strncmp(registro.cpf,buffer.cpf, 15) == 0) //Se o cep do buffer for igual ao desejado
        {
            return 0;
        }
        else if (strncmp(registro.cpf,buffer.cpf, 15) > 0)
        {
            ini = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }
    return -1;
}

int main(int argc, char**argv)
{
	FILE *arquivoA, *arquivoB;
	Registro bufferA, bufferB;
	int registroA, registroB, achei;
	int c = 0;
    
    //abre arquivos
    if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO 1] [ARQUIVO 2].\n", argv[0]);
		return 1;
	}

	arquivoA = fopen(argv[1],"r");
	if(!arquivoA)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

    arquivoB = fopen(argv[2],"r");
	if(!arquivoB)
	{
		fclose(arquivoA);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

    //le primeiro registro do arquivo A
	registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);
	while(registroA > 0)
	{
		c++;
        achei = buscaBinaria(arquivoB, bufferA);
        if (achei == 0)
        {
            printf("%.40s\n",bufferA.email);
        }
		registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);	
	}

    printf("Total Lido: %d\n", c);
	fclose(arquivoA);
	fclose(arquivoB);
}

/*
Algoritmo:
    pega um registro do A
    faz busca binaria no B
    se existir no b
    imprime
    se não, passa pro proximo
*/