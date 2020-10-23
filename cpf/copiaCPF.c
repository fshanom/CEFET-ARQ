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