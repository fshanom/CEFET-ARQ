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

int main(int argc, char**argv)
{
	FILE *arquivoA, *arquivoB;
	Registro bufferA, bufferB;
	int registroA, registroB, achei;
	int c = 0;
    
    //abre arquivos
    if(argc != 2)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO 1]\n", argv[0]);
		return 1;
	}

	arquivoA = fopen(argv[1],"r");
	if(!arquivoA)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

    //le primeiro registro do arquivo A
	registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);
	while(registroA > 0)
	{
		c++;
		printf("%d // %.20s // %.15s // %.11s // %d // %.40s\n",bufferA.id_inscricao,bufferA.curso,bufferA.cpf,bufferA.dataNacimento,bufferA.sexo,bufferA.email);
		registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);	
	}

    printf("Total Lido: %d\n", c);
	fclose(arquivoA);
}

