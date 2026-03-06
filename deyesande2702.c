/*
Sistema de Cadastro de Clientes
Versao PRO
Desenvolvido por Karmabeast
UNICV - Estrutura de Dados
*/
//
#include <stdio.h>// Biblioteca padrao de entrada e saida
#include <stdlib.h>// Biblioteca padrao de funcoes utilitarias, como system, etc.
#include <windows.h>// Biblioteca para funcoes do Windows, como gotoxy, Sleep, etc.
#include <string.h>// Biblioteca para funcoes de manipulacao de strings, como strcmp, etc.
#include <ctype.h>// Biblioteca para funcoes de manipulacao de caracteres, como toupper, etc.
#include <time.h>// Biblioteca para funcoes de manipulacao de tempo, como time, localtime, etc.

#define MAX_CLIENTES 100 // Define o numero maximo de clientes que podem ser cadastrados
// A estrutura CLIENTE armazena os dados de cada cliente
// Pode ser personalizada para incluir outros campos, como genero, estado civil, etc.
typedef struct{
    int CODIGO;// Codigo unico do cliente, gerado automaticamente
    char NOME[50];// Nome do cliente, pode conter espacos, etc.
    char ENDERECO[100];// Endereco do cliente, pode conter espacos, etc.
    char TELEFONE[15];// Telefone do cliente, pode conter espacos, etc.
    char EMAIL[50];// Email do cliente, pode conter espacos, etc.
    char CPF[15];// CPF do cliente, pode conter espacos, etc.
    char DATA_NASC[11];// Data de nascimento do cliente, no formato DD/MM/AAAA
    char DATA_CADASTRO[11];// Data de cadastro do cliente, no formato DD/MM/AAAA, gerada automaticamente
}CLIENTE;
// A estrutura LISTA armazena os clientes cadastrados e o numero de clientes (fim)
// Pode ser personalizada para incluir outros campos, como total por faixa etaria, etc.
// O campo clientes e um array de CLIENTE com tamanho MAX_CLIENTES, que define o limite de clientes cadastrados
// O campo fim indica quantos clientes estao cadastrados atualmente, e tambem a posicao onde o proximo cliente sera adicionado
typedef struct{
    CLIENTE clientes[MAX_CLIENTES];
    int fim;
}LISTA;
// Funcao para posicionar o cursor no console
// Pode ser personalizada para incluir cores, etc.
void gotoxy(int x,int y){
    COORD coord;
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
// Funcao para limpar o buffer do teclado
// Necessaria para evitar problemas com fgets apos scanf, etc.
// Pode ser personalizada para incluir outras formas de limpar o buffer, etc.
void limparBuffer(){
    int c;
    while((c=getchar())!='\n' && c!=EOF);
}
// Funcao para pausar a execucao e esperar o usuario pressionar uma tecla
// Pode ser personalizada para incluir mensagens, etc.
void pausa(){
    gotoxy(5,23);
    system("pause");
}
// Funcao para confirmar acoes do usuario
// Pode ser personalizada para incluir mais opcoes, como "Cancelar", etc.
// A mensagem e mostrada na posicao (5,22) dentro do marco
int confirmar(char mensagem[]){
    char op;

    gotoxy(5,22);
    printf("%s (S/N): ",mensagem);// A resposta e lida como um caractere, e convertida para maiusculo para facilitar a comparacao

    scanf(" %c",&op);

    if(op=='S'||op=='s')
        return 1;

    return 0;
}
// Funcao para salvar clientes em arquivo binario
// Pode ser personalizada para salvar em outros formatos, como TXT, etc.
// O arquivo "clientes.dat" sera criado ou sobrescrito no mesmo diretorio do programa

void salvarClientes(LISTA *l){

    FILE *f=fopen("clientes.dat","wb");

    if(f==NULL) return;

    fwrite(l,sizeof(LISTA),1,f);

    fclose(f);
}
// Funcao para carregar clientes do arquivo binario
// Pode ser personalizada para carregar de outros formatos, como TXT, etc.
// O arquivo "clientes.dat" deve estar no mesmo diretorio do programa e conter os dados
void carregarClientes(LISTA *l){

    FILE *f=fopen("clientes.dat","rb");

    if(f==NULL){
        l->fim=0;
        return;
    }

    fread(l,sizeof(LISTA),1,f);

    fclose(f);
}
// Funcao para buscar cliente por codigo
// Pode ser personalizada para buscar por outros campos, como CPF, etc.
int buscarCliente(LISTA *l,int codigo){

    for(int i=0;i<l->fim;i++)
        if(l->clientes[i].CODIGO==codigo)
            return i;

    return -1;
}
// Funcao para desenhar o marco do sistema
// Pode ser personalizada para incluir mais decoracao, cores, etc.
// O marco e desenhado usando caracteres ASCII e posicoes fixas
void desenharMarco(){

    system("cls");
    system("color c");

    int largura=80;
    int altura=25;

    for(int i=1;i<=altura;i++){
        gotoxy(1,i); printf("|");
        gotoxy(largura,i); printf("|");
    }

    for(int i=1;i<=largura;i++){
        gotoxy(i,1); printf("-");
        gotoxy(i,4); printf("-");
        gotoxy(i,22); printf("-");
        gotoxy(i,25); printf("-");
    }

    gotoxy(28,2); printf("SISTEMA DE CADASTRO");
    gotoxy(32,3); printf("VERSAO BETA");

    gotoxy(3,2); printf("UNICV");
    gotoxy(3,3); printf("ESTRUTURA DE DADOS");

    gotoxy(3,23); printf("Copyright (c) 2026 Karmabeast.");
    gotoxy(3,24); printf("Desenvolvido por Karmabeast - 2026");
}
// Funcao para cadastrar cliente
// Pode ser personalizada para incluir mais campos, validacao, etc.
void cadastrarCliente(LISTA *l){

    if(l->fim>=MAX_CLIENTES){
        printf("Lista cheia.");
        pausa();
        return;
    }
// O cliente e criado a partir dos dados lidos do usuario, e o codigo e gerado automaticamente
    CLIENTE novo;
    // O codigo e gerado automaticamente como o ultimo codigo + 1, para evitar duplicados
    // Pode ser personalizado para permitir entrada manual ou usar outro criterio de geracao
    // Se a lista estiver vazia, o primeiro codigo sera 1
    desenharMarco();

    gotoxy(5,8); printf("Codigo: ");
    scanf("%d",&novo.CODIGO);

    limparBuffer();

    gotoxy(5,9); printf("Nome: ");
    fgets(novo.NOME,50,stdin);

    novo.NOME[strcspn(novo.NOME,"\n")]=0;

    gotoxy(5,10); printf("Endereco: ");
    fgets(novo.ENDERECO,100,stdin);
    novo.ENDERECO[strcspn(novo.ENDERECO,"\n")]=0;

    gotoxy(5,11); printf("Telefone: ");
    fgets(novo.TELEFONE,15,stdin);
    novo.TELEFONE[strcspn(novo.TELEFONE,"\n")]=0;

    gotoxy(5,12); printf("Email: ");
    fgets(novo.EMAIL,50,stdin);
    novo.EMAIL[strcspn(novo.EMAIL,"\n")]=0;

    gotoxy(5,13); printf("CPF: ");
    fgets(novo.CPF,15,stdin);
    novo.CPF[strcspn(novo.CPF,"\n")]=0;

    gotoxy(5,14); printf("Data Nascimento: ");
    fgets(novo.DATA_NASC,11,stdin);
    novo.DATA_NASC[strcspn(novo.DATA_NASC,"\n")]=0;
    // A data de cadastro e gerada automaticamente como a data atual do sistema, usando as funcoes da biblioteca time.h
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);

    sprintf(novo.DATA_CADASTRO,"%02d/%02d/%04d",
            tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);

    if(confirmar("Desea guardar este cliente?")){

        l->clientes[l->fim++]=novo;

        salvarClientes(l);

        printf("Cliente guardado.");
    }

    pausa();
}
// Funcao para consultar cliente por codigo
// Pode ser personalizada para consultar por outros campos, como CPF, etc.
// O cliente encontrado e mostrado com todos os seus dados formatados
// A busca e feita usando a funcao buscarCliente, que retorna a posicao do
// cliente na lista ou -1 se nao encontrado
void consultarCliente(LISTA *l){

    desenharMarco();

    int codigo;

    gotoxy(5,8);
    printf("Codigo: ");

    scanf("%d",&codigo);

    int pos=buscarCliente(l,codigo);

    if(pos==-1){

        printf("Cliente nao encontrado.");

    }else{

        CLIENTE c=l->clientes[pos];

        printf("\nNome: %s",c.NOME);
        printf("\nEndereco: %s",c.ENDERECO);
        printf("\nTelefone: %s",c.TELEFONE);
        printf("\nEmail: %s",c.EMAIL);
        printf("\nCPF: %s",c.CPF);
        printf("\nNascimento: %s",c.DATA_NASC);
        printf("\nCadastro: %s",c.DATA_CADASTRO);
    }

    pausa();
}
// Funcao para excluir cliente por codigo
// Pode ser personalizada para excluir por outros campos, como CPF, etc.
// O cliente e removido da lista e os clientes seguintes sao deslocados para preencher o espaco
void excluirCliente(LISTA *l){

    desenharMarco();

    int codigo;

    printf("Codigo: ");
    scanf("%d",&codigo);

    int pos=buscarCliente(l,codigo);

    if(pos==-1){

        printf("Cliente nao encontrado.");
        pausa();
        return;
    }

    if(!confirmar("Eliminar cliente?")){
        pausa();
        return;
    }

    for(int i=pos;i<l->fim-1;i++)
        l->clientes[i]=l->clientes[i+1];

    l->fim--;

    salvarClientes(l);

    printf("Cliente eliminado.");

    pausa();
}
// Funcao para visualizar todos os clientes cadastrados
// Pode ser personalizada para mostrar mais campos ou formatacao diferente
// Os clientes sao listados a partir da posicao (5,8) dentro do marco
void visualizarClientes(LISTA *l){

    desenharMarco();

    int linha=8;

    for(int i=0;i<l->fim;i++){

        gotoxy(5,linha++);

        printf("Cod:%d Nome:%s CPF:%s",
        l->clientes[i].CODIGO,
        l->clientes[i].NOME,
        l->clientes[i].CPF);
    }

    pausa();
}
// Funcao para mostrar o total de clientes cadastrados
// Pode ser personalizada para mostrar outros dados, como total por faixa etaria, etc.
// O total e mostrado na posicao (30,12) dentro do marco
void totalClientes(LISTA *l){

    desenharMarco();

    gotoxy(30,12);

    printf("Total clientes: %d",l->fim);

    pausa();
}
// Funcao para exportar clientes para arquivo TXT
// Pode ser personalizada para incluir mais campos ou formatacao diferente
// O arquivo "clientes.txt" sera criado ou sobrescrito no mesmo diretorio do programa
void exportarTXT(LISTA *l){

    FILE *f=fopen("clientes.txt","w");

    for(int i=0;i<l->fim;i++){

        fprintf(f,"%d %s %s\n",
        l->clientes[i].CODIGO,
        l->clientes[i].NOME,
        l->clientes[i].CPF);
    }

    fclose(f);
}
// Funcao de ordenacao por nome usando Bubble Sort
// Pode ser implementada de forma similar para CPF, Data Nasc e Data Cadastro
void ordenarPorNome(LISTA *l){

    CLIENTE temp;

    for(int i=0;i<l->fim-1;i++)
    for(int j=i+1;j<l->fim;j++)
    if(strcmp(l->clientes[i].NOME,l->clientes[j].NOME)>0){

        temp=l->clientes[i];
        l->clientes[i]=l->clientes[j];
        l->clientes[j]=temp;
    }

    salvarClientes(l);
}
// Funcao para mostrar o menu de ordenacao e chamar a funcao correspondente
// Pode ser personalizada para incluir mais opcoes, como ordenacao por outros campos, etc.
void menuOrdenar(LISTA *l){

    int op;

    desenharMarco();

    printf("\n1 Nome");
    printf("\n2 CPF");
    printf("\n3 Data Nasc");
    printf("\n4 Data Cadastro");

    printf("\nOpcao: ");

    scanf("%d",&op);

    switch(op){

        case 1: ordenarPorNome(l); break;
    }

    printf("Ordenado.");

    pausa();
}
// Implementacao de outras funcoes de ordenacao (CPF, Data Nasc,
// Data Cadastro) pode ser feita de forma similar a ordenarPorNome,
// comparando os campos correspondentes.
int menu(){

    int op;

    do{

        desenharMarco();

        gotoxy(30,7); printf("1 - Cadastrar");
        gotoxy(30,9); printf("2 - Consultar");
        gotoxy(30,11); printf("3 - Excluir");
        gotoxy(30,13); printf("4 - Visualizar");
        gotoxy(30,15); printf("5 - Buscar CPF");
        gotoxy(30,17); printf("6 - Total Clientes");
        gotoxy(30,19); printf("7 - Exportar TXT");
        gotoxy(30,21); printf("8 - Ordenar");
        gotoxy(30,23); printf("9 - Sair");

        gotoxy(42,24); printf("Opcao: ");

        scanf("%d",&op);

    }while(op<1||op>9);

    return op;
}
// Funcao principal do programa

int main(){

    LISTA l;

    carregarClientes(&l);

    int op;

    do{

        op=menu();

        switch(op){

        case 1: cadastrarCliente(&l); break;
        case 2: consultarCliente(&l); break;
        case 3: excluirCliente(&l); break;
        case 4: visualizarClientes(&l); break;
        case 6: totalClientes(&l); break;
        case 7: exportarTXT(&l); break;
        case 8: menuOrdenar(&l); break;

        case 9:

            if(confirmar("Salir del sistema?")){
                printf("Encerrando...");
                Sleep(2000);
            }else op=0;

        break;
        }

    }while(op!=9);

    return 0;
}
