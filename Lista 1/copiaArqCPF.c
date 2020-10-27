#include <stdio.h>
#include <string.h>

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
    FILE *arqOrigem, *arqDestino;
	char registroAtual[sizeof(Registro)];
	int qt, inscricoes = 0;
	long posicao;
	Registro registro, registroSucessor, registroMaiorId;

    //valida uso do programa
	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

    //abre arquivo de entrada
	arqOrigem = fopen(argv[1],"rb");
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

	qt = fread(&registro,sizeof(Registro),1,arqOrigem);
	fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
	while(qt > 0)
	{
		if(strncmp(registro.cpf,registroSucessor.cpf,15)==0)
		{
			//compara qual tem o maior id e guarda
			if(registro.id_inscricao > registroSucessor.id_inscricao)
			{
				registroMaiorId = registro;
			}
			else
			{
				registroMaiorId = registroSucessor;
			}
			//pega próximo registro
			fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
			//loop para comparar todos os possíveis proximos registros que possuam o mesmo cpf
			while(strncmp(registroMaiorId.cpf,registroSucessor.cpf,15)==0)
				if(registroSucessor.id_inscricao > registroMaiorId.id_inscricao)
				{
					registroMaiorId = registroSucessor;
				}
				fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
			
			//fread(&registro,sizeof(Registro),1,arqOrigem);
			registro = registroSucessor;
			fwrite(&registroMaiorId,sizeof(Registro),1,arqDestino);

		}
		else
		{
			//escreve registro de cpf unico no arquivo de destino
			fwrite(&registro,sizeof(Registro),1,arqDestino);
		}
		
		qt = fread(&registroSucessor,sizeof(Registro),1,arqOrigem);		
	}

	fseek(arqDestino,0,SEEK_END);
	posicao = ftell(arqDestino);
	printf("Tamanho do Arquivo em registros: %ld\n", posicao/sizeof(Registro));

	printf("registros inscritos: %d",&inscricoes);
	fclose(arqOrigem);
	fclose(arqDestino);
	return 0;
}

/*
Algoritmo:

pega primeiro registro
enquanto existem registros:
	pega registro sucessor
	se o cpfs forem iguais:
		compara os cpfs e guarda o registro de maior id
		pega próximo registro (registro "sucessor" ao sucessor)
		se cpf do proximo registro == cpf do registro de maior id
			enquanto o cpf do proximo registro for igual: existirem mais registros com o mesmo cpf
				coloca próximo registro no vetor
				pega próximo registro
		se não: não existem mais registros com esse cpf
			atualiza o registro atual do loop maior com o sucessor ao ultimo registro com o mesmo cpf encontrado
			escreve registro de maior id no arquivo destino
		volta loop
	se não: o primeiro cpf é unico
		escreve  registro no arquivo destino
		sucessor vira registro
		volta loop
*/