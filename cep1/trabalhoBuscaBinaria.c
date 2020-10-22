#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};
typedef struct _Endereco Endereco;

int main(int argc, char const *argv[])
{
    FILE *f;
    int fim, ini, meio, count = 0, achei;
    long tam;

    if(argc != 2) //validação dos códigos de referencia reutilizada
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

    Endereco buffer;
    f = fopen("cep_ordenado_novo.dat", "r");
    ini = 0; //primeiro byte do arquivo
    fseek(f, 0, SEEK_END); //Cabeça de leitura no final do arquivo.
    tam = ftell(f); //tamanho do arquivo em bytes
    rewind(f); //volta a cabeça de leitura pro inicio do arquivo

    fim = (tam/sizeof(Endereco))-1;
    printf("Tamanho do arquivo total em bytes: %ld\nTamanho de cada registro: %ld\nQtd de registros: %d\n", tam, sizeof(Endereco), fim);

    
    while (ini <= fim)
    {
        count++;
        meio = (fim+ini)/2; //calcula o meio
        fseek(f, meio * sizeof(Endereco), SEEK_SET); //posiciona a cabeça de leitura no meio
        fread(&buffer, sizeof(Endereco), 1, f); //Lê o registro do meio

        if(strncmp(argv[1],buffer.cep, 8) == 0) //Se o cep do buffer for igual ao desejado
        {
            achei = 0;
            printf("Achei.\nPosicao Atual: %ld\n", ftell(f));
            break;
        }
        else if (strncmp(argv[1],buffer.cep, 8) > 0)
        {
            ini = meio + 1;
            //printf("IF Maior teste");
        }
        else
        {
            fim = meio - 1;
            //printf("IF Menor teste");
        }
    }
    
    printf("Quantidade de comparações: %d\n",count);

    if(achei != 0)
    {
        printf("Não achou.\n");

    }
    
    fclose(f);
    return 0;
}

//Trabalho de Organização e Estrutura de Arquivos
//Busca Binária em uma base de dados ordenada de CEP's
//Autor: Filipe Shanom Glathardt de Azeredo Xavier. filipeshanom@gmail.com
//Professor: Renato Mauro