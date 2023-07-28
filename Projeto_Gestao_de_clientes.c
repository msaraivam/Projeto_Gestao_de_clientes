/*Bibliotecas*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

char op ;/*variavel global para capturar em qual gerencia o usuario quer entrar*/

void getch(){
    system("read b ");
}

/*Estrutura Endereço*/
typedef struct 
{
    char logadouro[10];
    char complemento [20];
    char cep [10];
    char bairro[20];
    char cidade [20];
    char estado [3];
}End;



/*Estrutura Cliente*/
typedef struct 
{
    int codigo;
    char nome [30];
    char empresa [30];
    char cnpj [20],cpf [20];
    char bairro[20];
    char telefone [10];
    End endereco;
}Cli;


/*Estrutura Produto*/
typedef struct 
{
    int codigo;
    char nome [30];
    char fornecedor [30];
    char categoria[30];
    int quant;
    float valorUnit;
    
}Prod;


/*Estrutura Pedido*/
typedef struct 
{
    int codigo;
    int dia;
    int mes;
    int ano; 
    Cli clienteQuePediu;
    Prod *produtoPedido;
    int *qdtprodutoPedido;
    int qdt;
    
}Ped;

/*Declaração da função Menu para gerenciar o Programa*/

void menu();

/*Declarações das funções para gerenciar as ações relacionadas aos clientes*/

void gerenciaDeClientes(Cli*,int*,FILE*);
Cli cadastrarCliente(Cli, int);
void listarCliente(Cli*, int);
void ordenarClienteAlfabeticamente(Cli*, int);
void buscarCliente(Cli*, int);
void atualizarCliente(Cli*, int);
void excluirCliente(Cli*, int*);
void imprimirCliente(Cli);

/*Declarações das funções para gerenciar as ações relacionadas aos Produtos*/

void gerenciaDeProdutos(Prod*,int*,FILE*);
Prod cadastrarProduto(Prod, int);
void listarProdutosCadastrado(Prod*, int);
void ordenarProdutoPorNome(Prod*, int);
void filtrarCategoria();
void buscarProdutosCadastrado(Prod*, int);
void atualizarProdutosCadastrado(Prod*, int);
void atualizarEstoqueProduto(Prod*, int);
void imprimirProduto(Prod);

/*Declarações das funções para gerenciar as ações relacionadas aos Pedidos*/

void gerenciaDePedidos(Ped*,Cli*,Prod*,int*, int ,int);
void cadastrarPedido(Ped*,Cli*,Prod*,int*, int ,int);
void obterData(Ped*);
void listarPedidosDeUmCliente(Ped*, int);
void ordenarPedidosPorData(Ped*, int);
void ListarPedidosDeUmDia(Ped*, int);
void ordenarPorNomeCliente(Ped*, int);
void imprimirPedido(Ped);

/* Inicio da Função Principal*/

int main(){
    FILE *arquivo;/* Declarando um arquivo */ 
    Prod *produto;/* Ponteiro Produto */ 
    Cli  *cliente;/* Ponteiro Cliente */ 
    Ped  *pedido;/* Ponteiro Pedido */ 
    int contCliente=0,contProduto=0,contPedido=0;  /* inicializa os contadores em '0' */ 

/*Alocando memória para os Ponterios*/
produto = calloc(10,sizeof(Prod));
cliente = calloc(10,sizeof(Cli));
pedido = calloc(10,sizeof(Ped));

/*Chamando a função menu*/

menu();

do
{
    switch (op)
    {
        case 'C':
        case 'c':
            gerenciaDeClientes(cliente, &contCliente, arquivo);
            break;

        case 'P':
        case 'p':
            gerenciaDeProdutos(produto, &contProduto, arquivo);
            break;

        case 'E':
        case 'e':
            gerenciaDePedidos(pedido, cliente, produto, &contPedido, contCliente, contCliente);
            break;

        case 'S':
        case 's':
            exit(1);

        default:
            printf("    !! COMANDO INVALIDO !! \nEntre com o comando novamente\n");
            sleep(2);
            system("clear");
            menu();
        
     }

} while (1);
return 0 ;
}
/* Fim da Função Principal*/

/*Codígo da função menu*/
void menu(){
    printf("=======Gerenciamento=======\n");
    printf("C - Gerenciar Clientes\n");
    printf("P - Gerenciar Produtos\n");
    printf("E - Gerenciar Pedidos\n");
    printf("S - Sair\n");
    printf("Digite um comando para Prosseguir: ");
    scanf(" %c", &op);
    system("clear");
}
/*Codígo da função Gerenciar Clientes*/
void gerenciaDeClientes(Cli *cliente, int *contCliente, FILE *arquivo ){
    char opcao;
    do
    {
    printf("=======Gerenciar Clientes=======\n");
    printf("C - Cadastrar Clientes\n");
    printf("L - Listar clientes cadastrados\n");
    printf("B - Buscar cliente cadastrado\n");
    printf("A - Atualizar cliente cadastrado\n");
    printf("E - Excluir cliente cadastrado\n");
    printf("\nDigite uma opcao para Prosseguir: ");
    scanf(" %c", &opcao);
    system("clear");

switch (opcao)
{
        case 'C':
        case 'c':
            arquivo = fopen("Força de Vendas.txt","a+");
            if (arquivo == NULL)
            {
                printf("Não foi possivel abrir o arquivo.");
                return;
            }
            printf("======= Cadastro de Clientes =======\n");
            cliente[*contCliente] = cadastrarCliente(cliente[*contCliente], 0);
            fprintf(arquivo, "%d;%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", cliente[*contCliente].codigo,cliente[*contCliente].nome,
            cliente[*contCliente].cnpj, cliente[*contCliente].cpf, cliente[*contCliente].telefone,cliente[*contCliente].endereco.logadouro,
            cliente[*contCliente].endereco.complemento,cliente[*contCliente].endereco.cep,cliente[*contCliente].endereco.bairro,
            cliente[*contCliente].endereco.cidade,cliente[*contCliente].endereco.estado);
            fclose(arquivo);
            
        *contCliente+=1;
        if (*contCliente == 10)
        {
            cliente = realloc(cliente, (*contCliente + 1) * sizeof(Cli));
        }
            break;

        case 'L':
        case 'l':
           listarCliente(cliente, *contCliente);
            break;

        case 'B':
        case 'b':
            buscarCliente(cliente, *contCliente);;
            break;

        case 'A':
        case 'a':
            atualizarCliente(cliente, *contCliente);;
            break;

        case 'E':
        case 'e':
            excluirCliente(cliente, *contCliente);;
            break;

    default:
        printf("   !!OPCAO INVALIDA!!  \nDigite novamente outra opcao\n");
        sleep(2);
        system("clear");
        continue;
}
break;

    } while (1);
    

}


/*Codígo da função Cadastrar Clientes*/
Cli cadastrarCliente(Cli cliente, int identificador){
    char opcao;
    char codigoCliente[10];
    do
    {
       printf("Codigo do Cliente: ");
       scanf("%s",codigoCliente);
cliente.codigo = atoi(codigoCliente);
if (identificador == 0 )
{
    if(cliente.codigo == 0)
    {
        printf("\n!! CODIGO INVALIDO !! \n Apenas numeros para o codigo \n");
        sleep(2);
        system("clear");
        printf("===== Cadastro de Clientes =====\n");
        continue;
    }
    else{
        if (cliente.codigo == 0&& strlen(codigoCliente) > 0 )
        {
            printf("!!CODIGO INVALIDO!! \n Apenas numeros para o codigo \n");
            sleep(2);
            system("clear");
            continue;
        }
        
    }
    break;
}
    } while (1);
    printf("Nome do cliente: ");
    scanf(" %[^\n]s", cliente.nome);
    do{
        printf("Pessoa : Fisica(F) , Juridica (J) : ");
        scanf(" %c",&opcao);
        switch (opcao)
        {  /*Switch/case para determinar qual identificação pegar do usuario*/
        case 'F':
        case 'f':
        printf("CPF do cliente: ");
        scanf(" %[^\n]s", cliente.cpf);
        break;
        case 'J':
        case 'j':
        printf("CNPJ do cliente: ");
        scanf(" %[^\n]s", cliente.cnpj);
        break; 
        default:
        printf("\n     !! ATENCAO !! \n Digite (F) para pessoa Fisica ou (J) para pessoa juridica \n\n");
        continue;
        }
        break;
    }while(1);
    printf("Telefone do cliente: ");
    scanf("%[^\n]s", cliente.telefone);
    printf("Endereco do cliente: ");
    printf("Logradouro: ");
    scanf("%[^\n]s", cliente.endereco.logadouro);
    printf("Complemento: ");
    scanf("%[^\n]s", cliente.endereco.complemento);
    printf("CEP: ");
    scanf("%[^\n]s", cliente.endereco.cep);
    printf("Bairro: ");
    scanf("%[^\n]s", cliente.endereco.bairro);
    printf("Cidade: ");
    scanf("%[^\n]s", cliente.endereco.cidade);
    printf("Estado: ");
    scanf("%[^\n]s", cliente.endereco.estado);
    
    if (identificador == 0)
{
   printf("\n!! CADASTRO REALIZADO COM SUCESSO !! \n");
   sleep(2);
   system("clear");
   menu();
}
return cliente;
}

/*Função que lista um cliente selecionado*/

void listarCliente(Cli *cliente, int contCliente){
int i ;
if (contCliente == 0)
{
printf("    !!ERRO!! \n NEM UM CLIENTE CADASTRADO \n");
sleep(2);
system("clear");
menu();
return;
}
/* A função irá ordenar os clientes em ordem alfabetica*/
ordenarClienteAlfabeticamente(cliente, contCliente);

printf("LISTA DE CLIENTES CADASTRADOS \n\n");
for ( i = 0; i < contCliente; i++)
{
imprimirCliente(cliente[i]);
getch();
system("clear");
menu();

}

}


/*Função que ordena os clientes em ordem alfabetica*/

void ordenarClienteAlfabeticamente(Cli *cliente, int contcliente){
    int i , j , marcador;
    Cli aux;
    for ( i = 1; i < contcliente; i++)
    {
        aux = cliente[i];
        j = i-1;
        do
        {
            marcador = 0 ;
            if (strcmp(cliente[j].nome, aux.nome) > 0)
            {
                cliente[j+1] = cliente[j];
                j--;
                marcador = 1 ;
            }
            if (j < 0)
            {
                marcador = 0;
            }
        } while (marcador);
        cliente[j+1] = aux;
    } 
    
}

 
/*Função que imprime os dados de um cliente passado por parametro*/

void imprimirCliente(Cli cliente){
    printf ("Codigo: %d \n ", cliente.codigo);
    printf ("Nome: %s \n ", cliente.nome);
    if (strlen(cliente.cnpj) == 0)
    {
         printf ("CPF: %s \n ",cliente.cpf);
    }else{
         printf ("CNPJ: %s \n ", cliente.cnpj);
    }
    printf ("Telefone: %s \n ", cliente.telefone);
    printf ("Endereco: Logradouro %s / Complemento %s\n ", cliente.endereco.logadouro,cliente.endereco.complemento);
    printf ("CEP: %s \n" , cliente.endereco.cep);
    printf ("Bairro: %s \n ", cliente.endereco.bairro);
    printf ("Cidade: %s \n ", cliente.endereco.cidade);
    printf ("Estado: %s \n \n ", cliente.endereco.estado);
}


/*Função que busca um cliente selecionado*/

void buscarCliente(Cli *cliente, int contCliente){
int i , marcador = 0;
int codigoCliente;
char nomeCliente[30];
printf(" Digite o nome ou codigo do cliente que você deseja buscar . ");
scanf("%[^\n]s", nomeCliente);
printf("\n");
codigoCliente = atoi(nomeCliente);
for ( i = 0; i < contCliente; i++)
{
    if (cliente [ i]. codigo ==codigoCliente || strcmp (cliente [i].nome,nomeCliente) == 0 )
    {
    imprimirCliente(cliente[i]);
    getch();
    marcador = 1 ;
    break;
    }
}
if (!marcador)
{
    printf("        !!ERRO!! \n CLIENTE NAO CADASTRADO \n  ");
    sleep(2);
}
system("clear");

menu();

}

/*Função que busca um cliente selecionado*/

void atualizarCliente(Cli *cliente, int contCliente){
int codigo, i, marcador = 0;
Cli aux;
char codigoCliente[10];

do
{printf("Codigo do cliente que deseja atualizar : ");
scanf("%s",codigoCliente);
codigo = atoi (codigoCliente);
if(codigo == 0 ){
    printf("\n   !!ERRO!! \n Apenas numeros para o codigo \n");
    sleep(2);
    system("clear");
    continue;
}
   break;    
} while(1);
for ( i = 0; i < contCliente; i++)
{
    if (cliente[i].codigo == codigo)
    {
        marcador = 1;
    break;
}
}

if (!marcador)
{
    printf("\n!!ERRO!! \n CLIENTE NÃO CADASTRADO");

}else{

printf("\n ENTRE COM OS DADOS ATUALIAZADOS \n ");
aux = cadastrarCliente(aux,-1);
if (aux.codigo > 0 ) cliente[i].codigo = aux.codigo;
if(strlen(aux.nome) > 0 ) strcpy(cliente[i].nome, aux.nome);
if(strlen(aux.cpf) > 0 ) strcpy(cliente[i].cpf, aux.cpf);
if(strlen(aux.cnpj) > 0 ) strcpy(cliente[i].cnpj, aux.cnpj);
if(strlen(aux.telefone) > 0 ) strcpy(cliente[i].telefone, aux.telefone);
if(strlen(aux.endereco.logadouro) > 0 ) strcpy(cliente[i].endereco.logadouro, aux.endereco.logadouro);
if(strlen(aux.endereco.complemento) > 0 ) strcpy(cliente[i].endereco.complemento, aux.endereco.complemento);
if(strlen(aux.endereco.cep) > 0 ) strcpy(cliente[i].endereco.cep, aux.endereco.cep);
if(strlen(aux.endereco.bairro) > 0 ) strcpy(cliente[i].endereco.bairro, aux.endereco.bairro);
if(strlen(aux.endereco.cidade) > 0 ) strcpy(cliente[i].endereco.cidade, aux.endereco.cidade);
if(strlen(aux.endereco.estado) > 0 ) strcpy(cliente[i].endereco.estado, aux.endereco.estado);

printf("\nCLIENTE ATUALIZADO COM SUCESSO\n");
}

sleep(2);
system ("clear");
menu();

}

/*Função que exclui um cliente selecionado*/

void excluirCliente(Cli * cliente, int  *contCliente){
int codigo, i, marcador=0;
printf("Codigo do cliente que deseja excluir");
scanf("%d",&codigo);
for ( i = 0; i < *contCliente; i++)
{
    if (cliente -> codigo == codigo)
    {
        marcador = 1 ; 
        break;
    }
    
}
if(!marcador)
printf("\n     !!ERRO!! \n CLIENTE NAO CADASTRADO \n ");
else{
    for(i; i <*contCliente; i++)
    {
    cliente[i]= cliente[i+1];
    *contCliente -=1;
    printf ("\nCLIENTE EXCLUIDO COM SUCESSO\n");
    }
     
}

sleep(2);
system("clear");
menu();

}

/*função que gerencia ações relacionadas aos produtos*/

void gerenciaDeProdutos(Prod *produto,int* contProduto, FILE *arquivo){
    char opcao;
    do
    {
    printf("======= Gerenciar Produtos =======\n");
    printf("C - Cadastrar um produto\n");
    printf("L - Listar todos os produtos cadastrados\n");
    printf("B - Buscar produto ja cadastrado\n");
    printf("A - Atualizar um produto cadastrado\n");
    printf("S - Atualizar estoque de um produto\n");
    printf("Digite uma opcao para Prosseguir: ");
    scanf(" %c%*c", &opcao);
    system("clear");
    switch (opcao)
    {
        case 'C':
        case 'c':
        arquivo = fopen("Força de Vendas.txt","a+");
        if(arquivo == NULL){
            printf("Não foi possivel abrir o arquivo.");
            return;
        }
            printf("======= Cadastro de Produtos =======\n");
            produto[*contProduto] = cadastrarProduto(produto[*contProduto], 0 );

            fprintf(arquivo, "%d;%s;%s;%s;%d;%.2f\n", 
            produto[*contProduto].codigo, 
            produto[*contProduto].nome,
            produto[*contProduto].fornecedor,
            produto[*contProduto].categoria,
            produto[*contProduto].quant,
            produto[*contProduto].valorUnit);
            fclose(arquivo);

            
            *contProduto+=1;

            if (*contProduto==10)
            {
                produto = realloc(produto,(*contProduto+1) * sizeof(Prod));
                break;
            }
            case'L':
            case'l':
                listarProdutosCadastrado(produto, *contProduto);
            break;

            case'B':
            case'b':
            buscarProdutosCadastrado(produto,*contProduto);
            break;
            
            case'A':
            case'a':
            atualizarProdutosCadastrado(produto,*contProduto);
            break;

            case'S':
            case's':
            atualizarEstoqueProduto(produto,*contProduto);
            break;

    default:
     printf("!!OPCAO INVALIDA\n Digite novamente outraopcao");
        sleep(2);
        system("clear");
        continue;       
    }
    break;
    } while (1);
      
}


/*função que Cadastra produtos*/

Prod cadastrarProduto(Prod produto,int identificador){
    char aux [15];
    do
    {
        printf("Codigo do produto : ");
        scanf("%10s", aux );
        produto.codigo = atoi(aux);
        if (identificador == 0 )
        {
            if (produto.codigo == 0)
            {
                printf("\n!!CODIGO INVALIDO!!\n Apenas numeros para o codigo");
                sleep(2);
                system("clear");
                printf("======= Cadastro de Produtos ======= \n");
                continue;
            }
            else{
                if(produto.codigo==0 && strlen(aux) > 0 ){
                printf("\n!!CODIGO INVALIDO!!\n Apenas numeros para o codigo");
                sleep(3);
                system("clear");
                }
            }
            break;
        }
        
    } while (1);
    printf("Nome do produto:");
    scanf("%[^\n]s" , produto.nome);
     printf("Fornecedor:");
    scanf("%[^\n]s" , produto.fornecedor);
     printf("Categoria:");
    scanf("%[^\n]s" , produto.categoria);
    if (identificador == 0)
    { 
    
    printf("Quantidade:");
    scanf("%d" , &produto.quant);
}
      do
      { 
        printf("Valor unitario:");
    scanf("%s" , aux);
    produto.valorUnit = atof(aux);
    if (identificador == 0){
       if (produto.valorUnit == 0){
        printf("\n!!VALOR UNITARIO INVALIDO!!\n Apenas numeros para valor unitario");
        sleep(3);
        system("clear");
        continue;
       }
       
    }else{
         if (produto.valorUnit && strlen(aux) > 0){
        printf("\n!!VALOR UNITARIO INVALIDO!!\n Apenas numeros para valor unitario");
        sleep(3);
        system("clear");
        continue;
       }
    }
    break;
    
     } while (1);
        
        if (identificador == 0)
        {
        printf("\n!!PRODUTO CADASTRADO COM SUCESSO!!\n");
        sleep(2);
        system("clear");
        menu();
        }
        return produto;
        
        
        
}


/*função que lista produtos que estão cadastrados*/

void listarProdutosCadastrados(Prod *produto,int contProduto){

char filtrar;
/*Chamando função para ordenar produtos por nome*/
ordenarProdutoPorNome(produto,contProduto);
printf("Deseja filtrar por categoria [s/n]: ");
scanf("%c%*c",&filtrar);
switch (filtrar){/*Switch|case para verificar como o usuario deseja listar os produtos*/
    case'S':
    case's':
    filtrarCategoria(produto, contProduto);
    break;
    case'N':
    case'n':{
    int i ;
    printf("\n");
    if (contProduto > 0 )
    {
        for ( i = 0; i < contProduto; i++)
        {
            imprimirProduto(produto[i]);
            getch();
        }
    }
    else{
            printf("\n     !!ERRO!!  \n NENHUM CLIENTE CADASTRADO \n");
            sleep(2);
        }
        break;

    }
    
}
system("clear");
menu(); 
}


/*função que filtra a categoria do produto para imprimi-lo*/

void filtrarCategoria(Prod *produto,int contProduto){
int i ,j=0, indiceMesmaCategoria[30];
char categoria[30];

printf("Deseja visualizar os produtos de qual categoria: ");
scanf("%s",categoria);
printf("\n");
for ( i = 0; i < contProduto; i++)
{
    if (strcmp(produto[i].categoria,categoria) == 0)
    {
        indiceMesmaCategoria[j++]= i;
    }
    
}

if (!j)
{
    printf("\n !!ERRO!! \n CATEGORIA NAO CADASTRADA \n");
    sleep(2);
}
else{
    for ( i = 0; i < j; i++)
    {
        imprimirProduto(produto[indiceMesmaCategoria[i]]);
    getch();
    }
    
}
}

/*função que ordenar produto por nome*/
void ordenarProdutoPorNome(Prod *produto,int contProduto){
 int i , j , marcador;
    Prod aux;
    for ( i = 1; i < contProduto; i++)
    {
        aux = produto[i];
        j = i-1;
        do
        {
            marcador = 0 ;
            if (strcmp(produto[j].nome, aux.nome) > 0)
            {
                produto[j+1] = produto[j];
                j--;
                marcador = 1 ;
            }
            if (j < 0)
            {
                marcador = 0;
            }
        } while (marcador);
        produto[j+1] = aux;
    } 
    
}

/*função que busca produto cadastrado*/

void buscarProdutoCadastrado(Prod *produto,int contProduto){

int i , marcador = 0;
int codigoProduto;
char nomeProduto[30];
printf(" Digite o nome ou codigo do Produto que você deseja buscar . ");
scanf("%[^\n]s", nomeProduto);
printf("\n");
codigoProduto = atoi(nomeProduto);
for ( i = 0; i < contProduto; i++)
{
    if (produto [ i]. codigo ==codigoProduto || strcmp (produto [i].nome,nomeProduto) == 0 )
    {
    imprimirProduto(produto[i]);
    getch();
    marcador = 1 ;
    break;
    }
}
if (!marcador)
{
    printf("        !!ERRO!! \n PRODUTO NAO CADASTRADO \n  ");
    sleep(2);
}
system("clear");

menu();

}

/*função que imprime um produto */

void imprimirProduto(Prod produto){

    printf ("Codigo: %d\n ", produto.codigo);
    printf ("Nome: %s\n ", produto.nome);
    printf ("Categoria: %s\n ", produto.categoria);
    printf ("Fornecedor: %s\n ", produto.categoria);
    printf ("Quantidade: %d\n" , produto.quant);
    printf ("Valor unitario: %.2f\n\n", produto.valorUnit);
    
}

/*função que atualiza um produto já cadastrado */
void atualizarProdutoCadastrado(Prod *produto, int contProduto){
Prod aux;
int  i, marcador = 0;

{printf("Codigo do produto que deseja atualizar : ");
scanf("%d",&aux.codigo);

for ( i = 0; i < contProduto; i++)
{
    if (produto[i].codigo == aux.codigo)
    {
        marcador = 1;
    break;
}
}
if (!marcador)
{
    printf("\n  !!ERRO!! \n PRODUTO NÃO CADASTRADO");

}else{

printf("\n ENTRE COM OS DADOS ATUALIAZADOS \n ");

aux = cadastrarProduto(aux,-1);

if (aux.codigo > 0 ) 
produto[i].codigo = aux.codigo;

if(strlen(aux.nome) > 0 ) 
strcpy(produto[i].nome, aux.nome);

if(strlen(aux.fornecedor) > 0 ) 

strcpy(produto[i].fornecedor, aux.fornecedor);

if(strlen(aux.categoria) > 0 ) 
strcpy(produto[i].categoria, aux.categoria);

if(aux.valorUnit > 0 ) 
produto[i].valorUnit, aux.valorUnit;


printf("\n PRODUTO ATUALIZADO COM SUCESSO\n");
}
sleep(2);
system ("clear");
menu();

}}

/*função que atualiza o estoque de um produto já cadastrado */
void atualizarEstoqueProduto(Prod *produto, int contProduto){
int codigo, i, marcador = 0;

printf("Digite o codigo do produto que tera seu estoque atualizado : ");
scanf("%d",&codigo);

for ( i = 0; i < contProduto; i++)
{
    if (produto[i].codigo == codigo)
    {
        printf("\n Digite o estoque atualizado : \n");
        scanf("%d", &produto[i].quant);
        marcador = 1;
        printf("\nESTOQUE ATUALIZADO COM SUCESSO\n");
        break;
    }
}
if (!marcador)
{
    printf("\n  !!ERRO!! \n PRODUTO NÃO CADASTRADO");

}
sleep(2);
system ("clear");
menu();

}


/*função que gerencia açoes relacionadas a pedidos */
void gerenciaDePedidos(Ped *pedido, Cli *cliente, Prod *produto, int *contPedido, int contCliente, int contProduto){
  char opcao;
    do
    {
    printf("======= Gerenciar Pedidos =======\n");
    printf("C - Cadastrar um pedido\n");
    printf("L - Listar todos os pedidos de um cliente\n");
    printf("D - Listar todos os pedidos em um dia especifico\n");
    printf("\nDigite uma opcao para Prosseguir: ");
    scanf("%c", &opcao);
    system("clear");
    switch (opcao)
    {
            case 'C':
            case 'c':
            cadastrarPedido(pedido, cliente,produto,contPedido,contCliente,contProduto);
            break;
            case'L':
            case'l':
            listarPedidosDeUmCliente(pedido,*contPedido);
            break;
            case'D':
            case'd':
            ListarPedidosDeUmDia(pedido,*contPedido);
            break;
            default:
            printf("!!OPCAO INVALIDO\n Digite novamente outra opcao");
            sleep(2);
            system("clear");
            continue;       
    }
    break;
    } while (1);
      
}

/*função que gerencia açoes relacionadas a pedidos */
void CadastrarPedido(Ped *pedido, Cli *cliente, Prod *produto, int *contPedido, int contCliente, int contProduto){

    char nomeCliente[30];
    int codigoCliente, marcador = 0;
    int codigoProdutoParaCadastro;
    int qdtProduto;
    int i,j, auxindice=0;
    char opcao;
    printf("======= Cadastro de Pedidos ======= \n");
    printf("Digite o codigo ou o nome do cliente que esta fazendo o pedido : \n");
    scanf("%[^\n]s", nomeCliente);
    codigoCliente= atoi(nomeCliente);
    for ( i = 0; i < contCliente; i++)
    {
        if(codigoCliente == cliente[i].codigo|| strcmp(cliente[i].nome,nomeCliente)==0){
            pedido[*contPedido].clienteQuePediu = cliente [i];
            marcador= 1;
            break;
        }
    }
    if (!marcador && strlen(nomeCliente) !=0)
    {
        printf("\n  !! ERRO !! \n CLIENTE NÃO ENCONTRADO");
        sleep(2);
        system("clear");
        menu();
        return;
    }
    printf("Digite a quantidade de produtos que deseja pedir: ");
    scanf("%d", &pedido[*contPedido].qdt);

    pedido[*contPedido].produtoPedido= malloc(pedido[*contPedido].qdt * sizeof(Ped));
    
    pedido[*contPedido].qdtprodutoPedido= malloc(pedido[*contPedido].qdt * sizeof(int));

    do
    {
       marcador = 0;
       for ( i = auxindice; i < pedido[*contPedido].qdt; i++){
        printf("Digite o codigo do produto para cadastro : ");
        scanf("%d", &codigoProdutoParaCadastro);
        for ( j = 0; j < contProduto; j++){
            if (produto[j].codigo == codigoProdutoParaCadastro){
                printf("Digite a quantidade para cadastro: ");
                scanf("%d",&qdtProduto);
                        pedido[*contPedido].produtoPedido[i] = produto[j];
                        pedido[*contPedido].qdtprodutoPedido[i] = qdtProduto;
                        marcador = 1 ;
                        break;
                    }
                    
                }
                
            }
            
        
if (!marcador)
{
    printf("\n        !!ERRO!! \n  PRODUTO NÃO CADASTRADO\n");
    printf("O pedido sera descartado; ou deseja digitar novamente outro codigo de Produto S/N ");
    scanf("%c", &opcao);
    auxindice = i;
    system("cls");
    break;
    }

    
}while (opcao == 'S' || opcao == '1');


if (opcao =='N'|| opcao=='n')
{
    printf("PEDIDO NAO CADASTRADO\n");
    sleep(2);
}else{
    obterData(&pedido[*contPedido]);
    *contPedido+=1;
    if (*contPedido==10)
    {
        pedido = realloc(pedido,(*contPedido+1)* sizeof(Ped));
        printf("\nPEDIDO CADASTRADO COM SUCESSO\n");
        sleep(2);
    }
    system("clear");
    menu();
}

}

/*função que usa a biblioteca 'time.h' para implementar data */
void obterData(Ped *pedido){
    time_t t = time (NULL);
    struct tm data = *localtime(&t);
    pedido -> ano=data.tm_year + 1900;
    pedido -> mes=data.tm_mon + 1;
    pedido -> dia=data.tm_mday;

}

/*função que lista os pedidos de um cliente */
void listarPedidosDeUmCliente(Ped *pedido,int contPedido){
    char nomeCliente[30];
    int codigoCliente;
    int i , marcador = 0 ;
    printf("Digite o codigo ou nome do cliente para visualizar seus pedidos: ");
    scanf("%[^\n]s", nomeCliente);
    system("clear");
    codigoCliente = atoi(nomeCliente);
    for ( i = 0; i < contPedido; i++)/*ciclo que encontra ,ordena e mprime o pedido solicitado*/
    {
       if( pedido[i].clienteQuePediu.codigo == codigoCliente|| strcmp(pedido[i].clienteQuePediu.nome,nomeCliente)==0){
        ordenarPedidosPorData(pedido,contPedido);/*chamar função que ordena os pedidos por data*/
        imprimirPedido(pedido[i]);
        getch();
        marcador = 1;
        break;
        }
    }
    if (!marcador){/*caso o pedido não for encontrado */
printf("             !!ERRO!! \n NEM UM PEDIDO CADASTRADO PARA ESSE CLIENTE\n");
sleep(3);
    }
    system("clear");
menu();
}

/*Codigo da função que ordena os pedidos por Data*/
void ordenarPedidosPorData(Ped *pedido,int contPedido){
    int i , j ,marcador;
    Ped aux;
    
    for ( i = 1; i < contPedido; i++)/*laço que ordena por ano*/
    {
       aux = pedido[i];
       j = i-1;
       do
       {
        marcador = 0;
        if (pedido[j].ano>aux.ano)
        {
            pedido[j+1] = pedido[j];
            j--;
            marcador = 1;
        }
        if (j<0)
        {
            marcador = 0;
        }
        
       } while (marcador);
       pedido[j+1]=aux;
       
   }
    
for ( i = 1; i < contPedido; i++)/*laço que ordena por mes*/
    {
       aux = pedido[i];
       j = i-1;
       do
       {
        marcador = 0;
        if (pedido[j].mes>aux.mes&& pedido[j].ano == aux.ano)
        {
            pedido[j+1] = pedido[j];
            j--;
            marcador = 1;
        }
        if (j<0)
        {
            marcador = 0;
        }
        
       } while (marcador);
       pedido[j+1]=aux;
       
   }
for ( i = 1; i < contPedido; i++)/*laço que ordena por dia*/
    {
       aux = pedido[i];
       j = i-1;
       do
       {
        marcador = 0;
        if (pedido[j].dia>aux.dia&&pedido[i].ano == aux.ano && pedido[j].mes == aux.mes)
        {
            pedido[j+1] = pedido[j];
            j--;
            marcador = 1;
        }
        if (j<0)
        {
            marcador = 0;
        }
        
       } while (marcador);
       pedido[j+1]=aux;
       
   }

}

/*Função que imprima um pedido*/
void imprimirPedido(Ped pedido){
    int i ;
    printf("Nome do cliente : %s\n\n PEDIDOS",pedido.clienteQuePediu.nome);
    for(i=0; i <pedido.qdt;i++){
        printf("\nProduto:%s\n",pedido.produtoPedido[i].nome);
        printf("Quantidade:%d\n", pedido.qdtprodutoPedido[i]);
    }
printf("\n=====================================\n");
}

/*Codigo da função que lista todos os pedidos feitos em um dia */
void listarPedidoDeUmDia(Ped *pedido, int contPedido){
int i, dia,mes,ano,marcador=0;
char d[3];
char m[3];
char a[5];

printf("Para visualizar todos os pediddos de um determinado dia entre com a data OBS::(apenas numeros)\n");
printf("Dia: ");
scanf("%s",d);
printf("Mês: ");
scanf("%s",m);
printf("Ano: ");
scanf("%s",a);

system("clear");

dia =atoi(d);
mes = atoi(m);
ano = atoi(a);

ordenarPorNomeCliente(pedido,contPedido);/*Função que ordena os pedidos por nome dos cliente*/
for ( i = 0; i < contPedido; i++)
{
    if (pedido[i].ano == ano && pedido[i].mes == mes && pedido[i].dia == dia)
    {
        imprimirPedido(pedido[i]);
        marcador = 1;

    }

}

if (!marcador)
{
    printf("\n      !!NEM UM PEDIDO CADASTRADO NESSE DIA !! \n");
    sleep(2);
}else{
    getch();
    system("clear");
    menu();
}
}

/*Codigo da função que ordena os pedidos pelo nome dos clientes */
void ordenarPorNomeCliente(Ped *pedido, int contPedido){
int i , j , marcador;
Ped aux;

    for ( i = 1; i < contPedido; i++)
    {
        aux = pedido[i];
        j = i-1;
        do
        {
            marcador = 0;
            if (strcmp(pedido[j].clienteQuePediu.nome,aux.clienteQuePediu.nome)>0)
         {
                pedido[j+1] = pedido[j];
                j--;
                marcador = 1 ; 
            }
                if (j < 0)
                {
                marcador = 0 ;
                }
        
        
                 } while (marcador);
                    pedido[j+1]=aux;
    }

}

/*MATEUS SARAIVA MAGNO*/
