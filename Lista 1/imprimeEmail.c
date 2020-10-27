#include <stdio.h>

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
	int registroA, registroB;
	int c = 0;
    
    //abre arquivos
	arquivoA = fopen("candidatosA.dat","r");
    arquivoB = fopen("candidatosB.dat","r");

    //le primeiro registro dos arquivos
	registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);
	registroB = fread(&bufferB,sizeof(Registro),1,arquivoB);

	while(registroA > 0)
	{
		c++;
        printf("%.40s\n",bufferA.email);
		registroA = fread(&bufferA,sizeof(Registro),1,arquivoA);	
	}

	while(registroB > 0)
	{
		c++;
        printf("%.40s\n",bufferB.email);
        registroB = fread(&bufferB,sizeof(Registro),1,arquivoB);	
	}

    printf("Total Lido: %d\n", c);
	fclose(arquivoA);
	fclose(arquivoB);
}