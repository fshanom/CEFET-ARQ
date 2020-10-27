#include <stdio.h>

#define TAMANHO 4096

//92 bytes
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

/*
Registro buscaBinaria(FILE *arqOrigem, char cpfDesejado[15]){
	Registro buffer;
	int ini, fim, meio, count = 0;
	ini = 0; //primeiro byte do arquivo
    fseek(arqOrigem, 0, SEEK_END); //Cabeça de leitura no final do arquivo.
    long tam = ftell(arqOrigem); //tamanho do arquivo em bytes
    rewind(arqOrigem); //volta a cabeça de leitura pro inicio do arquivo

    fim = (tam/sizeof(Registro))-1;
    printf("Tamanho do arquivo total em bytes: %ld\nTamanho de cada registro: %ld\nQtd de registros: %d\n", tam, sizeof(Endereco), fim);

    
    while (ini <= fim)
    {
        count++;
        meio = (fim+ini)/2; //calcula o meio
        fseek(arqOrigem, meio * sizeof(Registro), SEEK_SET); //posiciona a cabeça de leitura no meio
        fread(&buffer, sizeof(Endereco), 1, arqOrigem); //Lê o registro do meio

        if(strncmp(cpfDesejado, buffer.cpf, 15) == 0) //Se o cep do buffer for igual ao desejado
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

	return registro;
}
*/

int main(int argc, char** argv)
{
    //struct tem 92 bytes, teste abaixo
	    //struct Registro r;
        //int tam = sizeof(r);
        //printf("%d",tam);

    FILE *arqOrigem, *arqDestino;
	char buffer[sizeof(Registro)];
	char registroAtual[sizeof(Registro)];
	long qtdRegistros, tamanhoArq;

    //valida uso do programa
	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

    //abre arquivo de entrada
	arqOrigem = fopen(argv[1],"r");
	if(!arqOrigem)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

    //abre arquivo de saida
	arqDestino = fopen(argv[2],"w");
	if(!arqDestino)
	{
		fclose(arqDestino);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

    //descobrir o número de registros


    fseek(arqOrigem,0,SEEK_END);
	tamanhoArq = ftell(arqOrigem);
	qtdRegistros = tamanhoArq/sizeof(Registro);

    
    //enquanto existirem registros (até o fim do arquivo)
        //pega CPF do registro atual (se cada linha tem 92 bytes, pega do byte)
	

	return 0;
}