#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct
{
	char nome [20];
	int codigo, tipo;
	float area, condominio;
}tipo_shopping;

tipo_shopping shopping;
FILE *p_shopping;

float condominio2 (int t_tipo,float t_area)
{
	switch(t_tipo)
	{
		case1: return t_area*50; break;
		case2: return t_area*65; break;
		case3: return t_area*80; break;
		case4: return t_area*95; break;
	}
}

void mostrar(void)
{
	printf("\n%6d     %-13s     %4.2f     %4d     %10.2f",shopping.codigo, shopping.nome, shopping.area, shopping.tipo, shopping.condominio);
}

void abre_arquivo (void)
{
	p_shopping=fopen("shopping_center.bin","a+b");
}

void procurar(int cod)
{
	rewind (p_shopping);
	do
	{
		fread(&shopping, sizeof(tipo_shopping), 1, p_shopping);
		if (cod==shopping.codigo) mostrar();
	}while ( feof(p_shopping)==0 && cod!=shopping.codigo );
	if (cod!=shopping.codigo) printf("\nLoja nao cadastrada\n");
}

void cadastrar(void)
{
	int continuar;
	do{
		system("cls");
		printf("\t\tCadastro");
		printf("\n\nShopping Center");
		printf("\n\nCadastro de Loja");
		printf("\n\nCodigo:\n");
		scanf("%d",&shopping.codigo);
		printf("\n\nNome:\n");
		fflush (stdin);
		gets(shopping.nome);
		printf("\n\nArea:\n");
		scanf("%f",&shopping.area);
		printf("\n\nTipo (1-Confeccoes, 2-Alimentacao, 3- Livros, 4- Serviços):\n");
		scanf("%d",&shopping.tipo);
		
		shopping.condominio=condominio2(shopping.tipo, shopping.area);
	
		fseek(p_shopping, 0, SEEK_END);
		fwrite(&shopping, sizeof(tipo_shopping), 1, p_shopping);

		printf("\n\nCadastrado com sucesso");
		printf("\n\nCadastrar outra:");	
		printf("\n\n1-Sim  /  0-Nao:");	
		scanf("%d",&continuar);
	}while(continuar==1);
}

void consultar (void)
{
	int t_codigo, continuar;
	do
	{
		system("cls");
		printf("\t\tConsultar");
		printf("\n\nShopping Centern");
		printf("\n\nConsultar Loja\n");
		printf("\n____________________________________________________\n");
		printf("\n\nCodigo da loja que deseja consultar:\n");
		scanf("%d",&t_codigo);
		printf("\n____________________________________________________\n");
		printf("\n  Codigo    Nome             Area      Tipo        Condominio\n");

		procurar(t_codigo);
	
		printf("\n____________________________________________________");
		printf("\n\nConsultar outra loja (1-Sim / 0-Nao\n");
		scanf("%d",&continuar);
	}while(continuar==1);
}

void listar(void)
{
	system("cls");
	printf("\t\tRelatorio Geral");
	printf("\n\nShopping Center");
	printf("\n\nListagem Geral\n");
	printf("\n____________________________________________________\n");
	printf("\n  Codigo    Nome             Area      Tipo        Condominio\n");

	rewind(p_shopping);

	do
	{
		fread(&shopping, sizeof(tipo_shopping), 1, p_shopping);
		if(feof(p_shopping)==0) mostrar();
	}while(feof(p_shopping)==0);
	printf("\nTecle enter para voltar ao menu...\n");
	getche();
}

main()
{
	int opcao;

	abre_arquivo();

	do
	{
		system("cls");
		printf("\t\tTela de Menu");
		printf("\n\nShopping Center");
		printf("\n\nOpcoes");
		printf("\n\n1-Cadastrar Loja");
		printf("\n\n2-Consultar Loja");
		printf("\n\n3-Listagem de todas as lojas");
		printf("\n\n0-Sair\n");
		scanf("%d",&opcao);

		if(opcao!=0)
		{
			switch(opcao)
			{
				case 1: cadastrar(); break;
				case 2: consultar(); break;
				case 3: listar (); break; 
				default: printf("\nOpcao Invalida\n"); break;
			}
		}
	}while(opcao!=0);
}
