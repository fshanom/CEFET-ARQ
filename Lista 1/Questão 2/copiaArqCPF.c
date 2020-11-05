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

int main(int argc, char** argv)
{
    FILE *arqOrigem, *arqDestino;
	char registroAtual[sizeof(Registro)];
	int qt, inscricoes = 0;
	long posicao, tamOrigem;
	Registro registro, registroSucessor, registroMaiorId;

    //valida uso do programa
	if(argc != 3)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO ORIGEM] [ARQUIVO DESTINO].\n", argv[0]);
		return 1;
	}

    //abre arquivo de entrada
	arqOrigem = fopen(argv[1],"rb+");
	if(!arqOrigem)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}

	//tamanho do arquivo original
	fseek(arqOrigem,0,SEEK_END);
	tamOrigem = ftell(arqOrigem);
	rewind(arqOrigem);
	
	//se o arquivo estiver vazio
	if(tamOrigem == 0)
	{
		printf("Arquivo Vazio.");
		return -1;
	}

    //abre arquivo de saida
	arqDestino = fopen(argv[2],"wb");
	if(!arqDestino)
	{
		fclose(arqDestino);
		fprintf(stderr,"Arquivo %s não pode ser aberto para escrita\n", argv[2]);
		return 1;
	}

	//pega o primeiro registro e seu sucessor
	qt = fread(&registro,sizeof(Registro),1,arqOrigem);

	fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
	while(qt > 0)
	{
		if(feof(arqOrigem))
		{
			break;
		}

		if(strncmp(registro.cpf,registroSucessor.cpf,15)==0)//se tiverem o mesmo cpf
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
			qt = fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
			if(qt == 0){
				break;
			}
			//loop para comparar todos os possíveis proximos registros que possuam o mesmo cpf
			if (strncmp(registroMaiorId.cpf,registroSucessor.cpf,15)==0)
			{
				while(strncmp(registroMaiorId.cpf,registroSucessor.cpf,15)==0)
				{
					if(registroSucessor.id_inscricao > registroMaiorId.id_inscricao)
					{
						registroMaiorId = registroSucessor;
					}

					qt = fread(&registroSucessor,sizeof(Registro),1,arqOrigem);
					if(qt == 0)
					{
						break;
					}
				}
			}

			registro = registroSucessor;
			inscricoes+=1;
			fwrite(&registroMaiorId,sizeof(Registro),1,arqDestino);
		}
		else
		{
			//escreve registro de cpf unico no arquivo de destino
			inscricoes+=1;
			fwrite(&registro,sizeof(Registro),1,arqDestino);
			registro = registroSucessor;

		}

		qt = fread(&registroSucessor,sizeof(Registro),1,arqOrigem);		
	}


	//se o arquivo foi totalmente lido, escreve o ultimo registro
	if(ftell(arqOrigem) == tamOrigem)
	{
		inscricoes+=1;
		fwrite(&registro,sizeof(Registro),1,arqDestino);
	}

	fseek(arqDestino,0,SEEK_END);
	posicao = ftell(arqDestino);
	printf("Tamanho do Arquivo origem em registros: %ld\n", tamOrigem/sizeof(Registro));
	printf("Tamanho do Arquivo destino em registros: %ld\n", posicao/sizeof(Registro));

	printf("registros inscritos: %d\n",inscricoes);
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
		compara e guarda o registro de maior id
		pega próximo registro (registro "sucessor" ao sucessor)
		se cpf do proximo registro == cpf do registro de maior id
			enquanto o cpf do proximo registro for igual: existirem mais registros com o mesmo cpf
				compara com o registro de maior id, se for maior guarda.
				pega próximo registro
		atualiza o registro atual do loop maior com o sucessor ao ultimo registro com o mesmo cpf encontrado
		escreve registro de maior id no arquivo destino
		volta loop
	se não: o primeiro cpf é unico
		escreve  registro no arquivo destino
		sucessor vira registro
		volta loop

se o arquivo estiver no fim
	escrever registroSucessor - no caso esse é o ultimo registro
*/