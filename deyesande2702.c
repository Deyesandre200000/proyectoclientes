/* 
   data: 26/02/2026
   autor: Deye
   objetivo: Sistema completo con validaciones
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

#define MAX_CLIENTES 100

// ===== ESTRUCTURA =====
typedef struct
{
    int CODIGO;
    char NOME[50];
    char ENDERECO[100];
    char TELEFONE[15];
    char EMAIL[50];
    char CPF[15];
    char DATA_NASC[11];
} CLIENTE;

typedef struct
{
    CLIENTE clientes[MAX_CLIENTES];
    int fim;
} lista;

// ===== GOTOXY =====
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// ===== VALIDACIONES =====
int soloLetras(char texto[])
{
    for(int i = 0; texto[i] != '\0'; i++)
        if(!((texto[i] >= 'A' && texto[i] <= 'Z') ||
             (texto[i] >= 'a' && texto[i] <= 'z') ||
              texto[i] == ' '))
            return 0;
    return 1;
}

int soloNumeros(char texto[])
{
    for(int i = 0; texto[i] != '\0'; i++)
        if(texto[i] < '0' || texto[i] > '9')
            return 0;
    return 1;
}

int validarEmail(char email[])
{
    int arroba = 0, punto = 0;

    for(int i = 0; email[i] != '\0'; i++)
    {
        if(email[i] == '@') arroba = 1;
        if(email[i] == '.') punto = 1;
    }

    return (arroba && punto);
}

// ===== MARCO =====
void dibujarMarco()
{
    system("cls");

    for(int i = 1; i <= 24; i++)
    {
        gotoxy(1,i); printf("|");
        gotoxy(80,i); printf("|");
    }

    for(int i = 1; i <= 80; i++)
    {
        gotoxy(i,1); printf("-");
        gotoxy(i,4); printf("-");
        gotoxy(i,22); printf("-");
        gotoxy(i,24); printf("-");
    }

    gotoxy(1,1); printf("+");
    gotoxy(80,1); printf("+");
    gotoxy(1,24); printf("+");
    gotoxy(80,24); printf("+");

    gotoxy(3,2); printf("SISTEMA DE CLIENTES - UNICV");
    gotoxy(58,3); printf("2026 - karmabeast_dev");
    gotoxy(3,23); printf("venezuela :v");
    gotoxy(55,23); printf("direitos reservados 2026");

}

// ===== BUSCAR =====
int buscarCliente(lista *l, int codigo)
{
    for(int i = 0; i < l->fim; i++)
        if(l->clientes[i].CODIGO == codigo)
            return i;
    return -1;
}

// ===== CADASTRO =====
void cadastroCliente(lista *l)
{
    if(l->fim >= MAX_CLIENTES)
    {
        gotoxy(5,23);
        printf("Limite atingido!");
        system("pause");
        return;
    }

    CLIENTE novo;
    dibujarMarco();
    gotoxy(5,6); printf("=== CADASTRO DE CLIENTE ===");

    // Codigo
    do{
        gotoxy(5,8); printf("Codigo: ");
        scanf("%d",&novo.CODIGO);
    }while(buscarCliente(l, novo.CODIGO) != -1);

    // Nome
    do{
        gotoxy(5,9); printf("Nome:                     ");
        gotoxy(11,9);
        scanf(" %[^\n]", novo.NOME);
    }while(!soloLetras(novo.NOME));

    // Endereco
    gotoxy(5,10); printf("Endereco: ");
    scanf(" %[^\n]", novo.ENDERECO);

    // Telefone
    do{
        gotoxy(5,11); printf("Telefone:                 ");
        gotoxy(15,11);
        scanf(" %[^\n]", novo.TELEFONE);
    }while(!soloNumeros(novo.TELEFONE));

    // Email
    do{
        gotoxy(5,12); printf("Email:                    ");
        gotoxy(12,12);
        scanf(" %[^\n]", novo.EMAIL);
    }while(!validarEmail(novo.EMAIL));

    // CPF
    do{
        gotoxy(5,13); printf("CPF:                      ");
        gotoxy(10,13);
        scanf(" %[^\n]", novo.CPF);
    }while(!soloNumeros(novo.CPF));

    // Data
    gotoxy(5,14); printf("Data Nasc (DD/MM/AAAA): ");
    scanf(" %[^\n]", novo.DATA_NASC);

    l->clientes[l->fim++] = novo;

    gotoxy(5,16);
    printf("Cliente cadastrado com sucesso!");
    system("pause");
}

// ===== CONSULTA =====
void consultarCliente(lista *l)
{
    int codigo;
    dibujarMarco();

    gotoxy(5,6); printf("=== CONSULTA ===");
    gotoxy(5,8); printf("Codigo: ");
    scanf("%d",&codigo);

    int pos = buscarCliente(l,codigo);

    if(pos == -1)
        gotoxy(5,10), printf("Cliente nao encontrado!");
    else
    {
        CLIENTE c = l->clientes[pos];
        gotoxy(5,10); printf("Nome: %s", c.NOME);
        gotoxy(5,11); printf("Telefone: %s", c.TELEFONE);
        gotoxy(5,12); printf("Email: %s", c.EMAIL);
    }

    system("pause");
}

// ===== ALTERAR =====
void alterarCliente(lista *l)
{
    int codigo;
    dibujarMarco();

    gotoxy(5,6); printf("=== ALTERACAO ===");
    gotoxy(5,8); printf("Codigo: ");
    scanf("%d",&codigo);

    int pos = buscarCliente(l,codigo);

    if(pos == -1)
    {
        gotoxy(5,10);
        printf("Cliente nao encontrado!");
        system("pause");
        return;
    }

    CLIENTE *c = &l->clientes[pos];

    do{
        gotoxy(5,10); printf("Novo Nome: ");
        scanf(" %[^\n]", c->NOME);
    }while(!soloLetras(c->NOME));

    gotoxy(5,11); printf("Novo Endereco: ");
    scanf(" %[^\n]", c->ENDERECO);

    system("pause");
}
// ===== EXCLUIR =====
void excluirCliente(lista *l)
{
    int codigo;
    dibujarMarco();

    gotoxy(5,6); printf("=== EXCLUSAO ===");
    gotoxy(5,8); printf("Codigo: ");
    scanf("%d",&codigo);

    int pos = buscarCliente(l,codigo);

    if(pos == -1)
    {
        gotoxy(5,10);
        printf("Cliente nao encontrado!");
        system("pause");
        return;
    }
    for(int i = pos; i < l->fim-1; i++)
        l->clientes[i] = l->clientes[i+1];

    l->fim--;
    gotoxy(5,10); printf("Cliente excluido!");
    system("pause");
}

// ===== VISUALIZAR =====
void visualizarClientes(lista *l)
{
    dibujarMarco();
    gotoxy(5,6); printf("=== LISTA DE CLIENTES ===");

    if(l->fim == 0)
    {
        gotoxy(5,8);
        printf("Nenhum cliente cadastrado.");
        system("pause");
        return;
    }

    int linha = 8;

    for(int i=0;i<l->fim;i++)
    {
        gotoxy(3,linha++);
        printf("Cod:%d Nome:%s Tel:%s",
               l->clientes[i].CODIGO,
               l->clientes[i].NOME,
               l->clientes[i].TELEFONE);
    }

    system("pause");
}

// ===== MENU =====
int menu()
{
    int op;

    do{
        dibujarMarco();
        gotoxy(30,8); printf("1 - INCLUSAO");
        gotoxy(30,10); printf("2 - ALTERACAO");
        gotoxy(30,12); printf("3 - CONSULTA");
        gotoxy(30,14); printf("4 - EXCLUSAO");
        gotoxy(30,16); printf("5 - VISUALIZACAO");
        gotoxy(30,18); printf("6 - SAIR");

        gotoxy(25,21);
        printf("Opcao: ");
        scanf("%d",&op);

    }while(op < 1 || op > 6);

    return op;
}

// ===== MAIN =====
int main()
{
    lista l;
    l.fim = 0;
    int op;

    system("color 0A");

    do{
        op = menu();

        switch(op)
        {
            case 1: cadastroCliente(&l); break;
            case 2: alterarCliente(&l); break;
            case 3: consultarCliente(&l); break;
            case 4: excluirCliente(&l); break;
            case 5: visualizarClientes(&l); break;
            case 6:
                dibujarMarco();
                gotoxy(30,12);
                printf("Saindo...");
                Sleep(1500);
        }

    }while(op != 6);

    return 0;
}