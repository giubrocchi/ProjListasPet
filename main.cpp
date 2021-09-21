#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

struct no{
    char nome[30], especie[20], raca[20], sexo[2], carac[100];
    int idade, cod;
    struct tm cadastro, alteracao;
    struct no *prox;
};

void inserir_no(struct no **inicio, struct no **aux);
void retirar_n(struct no **inicio, struct no **apagados);
void achar(struct no *inicio);
void imprimir(struct no *inicio);
void alterar(struct no *inicio);
int contar(struct no *inicio);
void mudacor(int cor);
void mudafundo(int cor);
void adotar(struct no **adotados, struct no **inicio);
void recuperar(struct no **inicio, struct no **apagados);

int main()
{
    setlocale(LC_ALL, "");
    struct no *inicio=NULL, *adotados=NULL, *apagados=NULL;
    int i, total, codigo=1;
    system("color F0");
    do{
    cout<<"  --- CADASTRO DE PETS ---\n";
    cout<<"\n  OPÇÕES:\n  1 - Inserir animal\n  2 - Retirar animal\n  3 - Alterar informação\n  4 - Encontrar animal\n  5 - Imprimir lista\n  6 - Contagem\n  7 - Adotados\n  8 - Apagados\n  0 - Sair\n";
    mudacor(1);
    mudafundo(15);
    cout<<"Insira a sua opção: ";
    mudacor(0);
    mudafundo(15);
    cin>>i;
    switch(i){
        case 1:{
            struct no *aux;
            time_t atual;
            aux=(no *)malloc(sizeof(no));
            cout<<"\n------------------------------------\n";
            if(aux!=NULL){
                aux->cod=codigo;
                cin.ignore();
                mudacor(1);
                mudafundo(15);
                cout<<"Insira o nome do animal: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(aux->nome, 30);
                strupr(aux->nome);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a espécie do animal: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(aux->especie, 20);
                strupr(aux->especie);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a raça do animal: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(aux->raca, 20);
                strupr(aux->raca);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira o sexo do animal (M ou F): ";
                mudacor(0);
                mudafundo(15);
                cin.getline(aux->sexo, 2);
                strupr(aux->sexo);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a idade do animal: ";
                mudacor(0);
                mudafundo(15);
                cin>>aux->idade;
                mudacor(1);
                mudafundo(15);
                cout<<"Insira as características do animal: ";
                mudacor(0);
                mudafundo(15);
                cin.ignore();
                cin.getline(aux->carac, 100);
                cout<<"------------------------------------\n";
                time (&atual);
                aux->cadastro= *localtime(&atual);
                inserir_no(&inicio, &aux);
                codigo++;
            }
            else
            {
                mudacor(12);
                mudafundo(15);
                cout<<"\n\nHeap overflow\n\n";
                mudacor(0);
                mudafundo(15);
            }
        }break;
        case 2:retirar_n(&inicio, &apagados);break;
        case 3:alterar(inicio);break;
        case 4:achar(inicio);break;
        case 5:imprimir(inicio);break;
        case 6:{
            total=contar(inicio);
            if(total==-1)
            {
                mudacor(12);
                mudafundo(15);
                cout<<"\nOpção inválida!\n\n";
                mudacor(3);
                mudafundo(15);
                system("pause");
                mudacor(0);
                mudafundo(15);
            }
            else
            {
                cout<<"\n-------------------------\n";
                cout<<"  TOTAL DE ANIMAIS: "<<total<<"\n";
                cout<<"-------------------------\n\n";
                mudacor(3);
                mudafundo(15);
                system("pause");
                mudacor(0);
                mudafundo(15);
            }
        }break;
        case 7:adotar(&adotados, &inicio);break;
        case 8:{
            int m;
            cout<<"\n---------------------------------\n";
            cout<<" --   RECUPERAÇÃO DE ANIMAL   --\n";
            cout<<"  1 - Recuperar animal\n  2 - Imprimir lista de apagados\n";
            mudacor(1);
            mudafundo(15);
            cout<<"Insira a sua opção: ";
            mudacor(0);
            mudafundo(15);
            cin>>m;
            switch(m){
                case 1:recuperar(&inicio, &apagados);break;
                case 2:imprimir(apagados);break;
                default:{
                    mudacor(12);
                    mudafundo(15);
                    cout<<"\nOpção inválida!\n\n";
                    mudacor(3);
                    mudafundo(15);
                    system("pause");
                    mudacor(0);
                    mudafundo(15);
                }
            }
        }break;
        case 0:break;
        default:{
            mudacor(12);
            mudafundo(15);
            cout<<"\nOpção inválida!\n\n";
            mudacor(3);
            mudafundo(15);
            system("pause");
            mudacor(0);
            mudafundo(15);
        }
    }
    system("cls");
    }while(i!=0);
    mudacor(12);
    mudafundo(15);
    cout<<"\n\n\tProcesso encerrado!\n\n";
    mudacor(0);
    mudafundo(15);
    return 0;
}
void inserir_no(struct no **inicio, struct no **aux)
{
    struct no *aux2;
    if(*inicio==NULL)
    {
        (*aux)->prox=NULL;
        *inicio=*aux;
    }
    else
    {
        if(strcmp((*aux)->nome,(*inicio)->nome)<0)
        {
            (*aux)->prox=*inicio;
            *inicio=*aux;
        }
        else
        {
            if((*inicio)->prox==NULL)
            {
                (*inicio)->prox=*aux;
                (*aux)->prox=NULL;
            }
            else
            {
                aux2=*inicio;
                while(strcmp((aux2->prox)->nome, (*aux)->nome)<0 && (aux2->prox)->prox!=NULL)
                    aux2=aux2->prox;
                if((aux2->prox)->prox!=NULL)
                {
                    (*aux)->prox=aux2->prox;
                    aux2->prox=*aux;
                }
                else
                {
                    if(strcmp((*aux)->nome, (aux2->prox)->nome)>0)
                    {
                        aux2=aux2->prox;
                        (*aux)->prox=NULL;
                        aux2->prox=*aux;
                    }
                    else
                    {
                        (*aux)->prox=aux2->prox;
                        aux2->prox=*aux;
                    }
                }
            }
        }
    }
}
void retirar_n(struct no **inicio, struct no **apagados)
{
    if(*inicio!=NULL)
    {
        struct no *aux, *aux2;
        int procurar;
        mudacor(1);
        mudafundo(15);
        cout<<"Insira o código do animal a ser retirado: ";
        mudacor(0);
        mudafundo(15);
        cin>>procurar;
        if((*inicio)->cod==procurar)
        {
            aux=*inicio;
            *inicio=(*inicio)->prox;
            inserir_no(apagados, &aux);
        }
        else
        {
            if((*inicio)->prox!=NULL)
            {
                aux=*inicio;
                while(aux->prox->prox!=NULL && aux->prox->cod!=procurar)
                    aux=aux->prox;
                if(aux->prox->cod==procurar)
                {
                    if(aux->prox->prox==NULL)
                    {
                        inserir_no(apagados, &(aux->prox));
                        aux->prox=NULL;
                    }
                    else
                    {
                        aux2=aux->prox;
                        aux->prox=aux->prox->prox;
                        inserir_no(apagados, &aux2);
                    }
                }
                else
                {
                    mudacor(12);
                    mudafundo(15);
                    cout<<"\n  Animal não encontrado\n\n";
                    mudacor(3);
                    mudafundo(15);
                    system("pause");
                    mudacor(0);
                    mudafundo(15);
                }
            }
            else
            {
                mudacor(12);
                mudafundo(15);
                cout<<"\n  Animal não encontrado\n\n";
                mudacor(3);
                mudafundo(15);
                system("pause");
                mudacor(0);
                mudafundo(15);
            }
        }
    }
    else
    {
        cout<<"\n-------------------------\n";
        mudacor(12);
        mudafundo(15);
        cout<<"  Lista vazia!";
        mudacor(0);
        mudafundo(15);
        cout<<"\n-------------------------\n\n";
        mudacor(3);
        mudafundo(15);
        system("pause");
        mudacor(0);
        mudafundo(15);
    }
}
void achar(struct no *inicio)
{
    int n;
    char busca[30];
    if(inicio==NULL)
    {
        cout<<"\n-------------------------\n";
        mudacor(12);
        mudafundo(15);
        cout<<"  Lista vazia!";
        mudacor(0);
        mudafundo(15);
        cout<<"\n-------------------------\n\n";
        mudacor(3);
        mudafundo(15);
        system("pause");
        mudacor(0);
        mudafundo(15);
    }
    else{
        cout<<"\n-----------------------------\n";
        cout<<"    --  BUSCAR ANIMAL  --\n";
        cout<<"  1 - Buscar por nome\n  2 - Buscar por espécie\n  3 - Buscar por espécie e raça\n  4 - Buscar por espécie, raça e sexo\n";
        mudacor(1);
        mudafundo(15);
        cout<<"Insira o modo de busca: ";
        mudacor(0);
        mudafundo(15);
        cin>>n;
        switch(n){
            case 1:
            {
                mudacor(1);
                mudafundo(15);
                cout<<"Insira o nome a ser buscado: ";
                mudacor(0);
                mudafundo(15);
                cin.ignore();
                cin.getline(busca, 30);
                strupr(busca);
                cout<<"\n--------------------------\n";
                while(inicio!=NULL)
                {
                    if(strcmp(inicio->nome, busca)==0)
                    {
                        cout<<"Nome: "<<inicio->nome<<endl;
                        cout<<"Código: "<<inicio->cod<<endl;
                        cout<<"Espécie: "<<inicio->especie<<endl;
                        cout<<"Raça: "<<inicio->raca<<endl;
                        cout<<"Sexo: "<<inicio->sexo<<endl;
                        cout<<"Idade: "<<inicio->idade<<endl;
                        cout<<"Características: "<<inicio->carac<<endl;
                        cout<<"Data de cadastramento: ";
                        printf("%d/%d/%d  %d:%d", inicio->cadastro.tm_mday, inicio->cadastro.tm_mon +1, inicio->cadastro.tm_year+1900, inicio->cadastro.tm_hour, inicio->cadastro.tm_min);
                        if(inicio->alteracao.tm_mday!=0)
                        {
                            cout<<"\nData da última edição: ";
                            printf("%d/%d/%d  %d:%d", inicio->alteracao.tm_mday, inicio->alteracao.tm_mon +1, inicio->alteracao.tm_year+1900, inicio->alteracao.tm_hour, inicio->alteracao.tm_min);
                        }
                        cout<<"\n--------------------------\n";
                    }
                    inicio=inicio->prox;
                }
            }break;
            case 2:
            {
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a espécie a ser buscada: ";
                mudacor(0);
                mudafundo(15);
                cin.ignore();
                cin.getline(busca, 30);
                strupr(busca);
                cout<<"\n--------------------------\n";
                while(inicio!=NULL)
                {
                    if(strcmp(inicio->especie, busca)==0)
                    {
                        cout<<"Nome: "<<inicio->nome<<endl;
                        cout<<"Código: "<<inicio->cod<<endl;
                        cout<<"Espécie: "<<inicio->especie<<endl;
                        cout<<"Raça: "<<inicio->raca<<endl;
                        cout<<"Sexo: "<<inicio->sexo<<endl;
                        cout<<"Idade: "<<inicio->idade<<endl;
                        cout<<"Características: "<<inicio->carac<<endl;
                        cout<<"Data de cadastramento: ";
                        printf("%d/%d/%d  %d:%d", inicio->cadastro.tm_mday, inicio->cadastro.tm_mon +1, inicio->cadastro.tm_year+1900, inicio->cadastro.tm_hour, inicio->cadastro.tm_min);
                        if(inicio->alteracao.tm_mday!=0)
                        {
                            cout<<"\nData da última edição: ";
                            printf("%d/%d/%d  %d:%d", inicio->alteracao.tm_mday, inicio->alteracao.tm_mon +1, inicio->alteracao.tm_year+1900, inicio->alteracao.tm_hour, inicio->alteracao.tm_min);
                        }
                        cout<<"\n--------------------------\n";
                    }
                    inicio=inicio->prox;
                }
            }break;
            case 3:
            {
                char busca2[20];
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a espécie a ser buscada: ";
                mudacor(0);
                mudafundo(15);
                cin.ignore();
                cin.getline(busca, 30);
                strupr(busca);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a raça a ser buscada: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(busca2, 30);
                strupr(busca2);
                cout<<"\n--------------------------\n";
                while(inicio!=NULL)
                {
                    if(strcmp(inicio->especie, busca)==0 && strcmp(inicio->raca, busca2)==0)
                    {
                        cout<<"Nome: "<<inicio->nome<<endl;
                        cout<<"Código: "<<inicio->cod<<endl;
                        cout<<"Espécie: "<<inicio->especie<<endl;
                        cout<<"Raça: "<<inicio->raca<<endl;
                        cout<<"Sexo: "<<inicio->sexo<<endl;
                        cout<<"Idade: "<<inicio->idade<<endl;
                        cout<<"Características: "<<inicio->carac<<endl;
                        cout<<"Data de cadastramento: ";
                        printf("%d/%d/%d  %d:%d", inicio->cadastro.tm_mday, inicio->cadastro.tm_mon +1, inicio->cadastro.tm_year+1900, inicio->cadastro.tm_hour, inicio->cadastro.tm_min);
                        if(inicio->alteracao.tm_mday!=0)
                        {
                            cout<<"\nData da última edição: ";
                            printf("%d/%d/%d  %d:%d", inicio->alteracao.tm_mday, inicio->alteracao.tm_mon +1, inicio->alteracao.tm_year+1900, inicio->alteracao.tm_hour, inicio->alteracao.tm_min);
                        }
                        cout<<"\n--------------------------\n";
                    }
                    inicio=inicio->prox;
                }
            }break;
            case 4:
            {
                char busca2[20], busca3[20];
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a espécie a ser buscada: ";
                mudacor(0);
                mudafundo(15);
                cin.ignore();
                cin.getline(busca, 30);
                strupr(busca);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira a raça a ser buscada: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(busca2, 30);
                strupr(busca2);
                mudacor(1);
                mudafundo(15);
                cout<<"Insira o sexo a ser buscado: ";
                mudacor(0);
                mudafundo(15);
                cin.getline(busca3, 30);
                strupr(busca3);
                cout<<"\n--------------------------\n";
                while(inicio!=NULL)
                {
                    if(strcmp(inicio->especie, busca)==0 && strcmp(inicio->raca, busca2)==0 && strcmp(inicio->sexo, busca3)==0)
                    {
                        cout<<"Nome: "<<inicio->nome<<endl;
                        cout<<"Código: "<<inicio->cod<<endl;
                        cout<<"Espécie: "<<inicio->especie<<endl;
                        cout<<"Raça: "<<inicio->raca<<endl;
                        cout<<"Sexo: "<<inicio->sexo<<endl;
                        cout<<"Idade: "<<inicio->idade<<endl;
                        cout<<"Características: "<<inicio->carac<<endl;
                        cout<<"Data de cadastramento: ";
                        printf("%d/%d/%d  %d:%d", inicio->cadastro.tm_mday, inicio->cadastro.tm_mon +1, inicio->cadastro.tm_year+1900, inicio->cadastro.tm_hour, inicio->cadastro.tm_min);
                        if(inicio->alteracao.tm_mday!=0)
                        {
                            cout<<"\nData da última edição: ";
                            printf("%d/%d/%d  %d:%d", inicio->alteracao.tm_mday, inicio->alteracao.tm_mon +1, inicio->alteracao.tm_year+1900, inicio->alteracao.tm_hour, inicio->alteracao.tm_min);
                        }
                        cout<<"\n--------------------------\n";
                    }
                    inicio=inicio->prox;
                }
            }break;
            default:{
                mudacor(12);
                mudafundo(15);
                cout<<"\nOpção inválida!\n\n";
            }
        }
        mudacor(3);
        mudafundo(15);
        system("pause");
        mudacor(0);
        mudafundo(15);
    }
}
void imprimir(struct no *inicio)
{
    if(inicio==NULL){
        cout<<"\n-------------------------\n";
        mudacor(12);
        mudafundo(15);
        cout<<"  Lista vazia!";
        mudacor(0);
        mudafundo(15);
        cout<<"\n-------------------------\n\n";
    }
    while(inicio!=NULL)
    {
        cout<<"\n----------------------------------------\n";
        cout<<"Nome: "<<inicio->nome<<endl;
        cout<<"Código: "<<inicio->cod<<endl;
        cout<<"Espécie: "<<inicio->especie<<endl;
        cout<<"Raça: "<<inicio->raca<<endl;
        cout<<"Sexo: "<<inicio->sexo<<endl;
        cout<<"Idade: "<<inicio->idade<<endl;
        cout<<"Características: "<<inicio->carac<<endl;
        cout<<"Data de cadastramento: ";
        printf("%d/%d/%d  %d:%d", inicio->cadastro.tm_mday, inicio->cadastro.tm_mon +1, inicio->cadastro.tm_year+1900, inicio->cadastro.tm_hour, inicio->cadastro.tm_min);
        if(inicio->alteracao.tm_mday!=0)
        {
            cout<<"\nData da última edição: ";
            printf("%d/%d/%d  %d:%d", inicio->alteracao.tm_mday, inicio->alteracao.tm_mon +1, inicio->alteracao.tm_year+1900, inicio->alteracao.tm_hour, inicio->alteracao.tm_min);
        }
        cout<<"\n----------------------------------------\n";
        inicio=inicio->prox;
    }
    mudacor(3);
    mudafundo(15);
    system("pause");
    mudacor(0);
    mudafundo(15);
}
void alterar(struct no *inicio)
{
    if(inicio!=NULL)
    {
        int procurar;
        int n;
        time_t atual;
        mudacor(1);
        mudafundo(15);
        cout<<"Insira o código do animal que deseja alterar: ";
        mudacor(0);
        mudafundo(15);
        cin>>procurar;
        while(inicio->cod!=procurar && (inicio->prox)!=NULL)
                inicio=inicio->prox;
        if(inicio->cod==procurar)
        {
            cout<<"\n-----------------------------\n";
            cout<<" --  ALTERAR INFORMAÇÕES  --\n";
            cout<<"  1 - Nome\n  2 - Espécie\n  3 - Raça\n  4 - Sexo\n  5 - Idade\n  6 - Características";
            mudacor(1);
            mudafundo(15);
            cout<<"\nInsira o campo a ser alterado: ";
            mudacor(0);
            mudafundo(15);
            cin>>n;
            cin.ignore();
            switch(n)
            {
                case 1:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Novo nome: ";
                    mudacor(0);
                    mudafundo(15);
                    cin.getline(inicio->nome, 30);strupr(inicio->nome);
                    }break;
                case 2:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Nova espécie: ";
                    mudacor(0);
                    mudafundo(15);
                    cin.getline(inicio->especie, 20);strupr(inicio->especie);
                    }break;
                case 3:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Nova raça: ";
                    mudacor(0);
                    mudafundo(15);
                    cin.getline(inicio->raca, 20);strupr(inicio->raca);
                    }break;
                case 4:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Novo sexo: ";
                    mudacor(0);
                    mudafundo(15);
                    cin.getline(inicio->sexo, 2);strupr(inicio->sexo);
                    }break;
                case 5:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Nova idade: ";
                    mudacor(0);
                    mudafundo(15);
                    cin>>inicio->idade;
                    }break;
                case 6:{
                    mudacor(1);
                    mudafundo(15);
                    cout<<"Nova característica: ";
                    mudacor(0);
                    mudafundo(15);
                    cin.getline(inicio->carac, 100);
                    }break;
                default:{
                    mudacor(12);
                    mudafundo(15);
                    cout<<"\nOpção inválida!\n\n";
                    mudacor(3);
                    mudafundo(15);
                    system("pause");
                    mudacor(0);
                    mudafundo(15);
                }
            }
            time (&atual);
            inicio->alteracao= *localtime(&atual);
        }
        else
        {
            mudacor(12);
            mudafundo(15);
            cout<<"\n  Animal não encontrado\n\n";
            mudacor(3);
            mudafundo(15);
            system("pause");
            mudacor(0);
            mudafundo(15);
        }
    }
    else
    {
        cout<<"\n-------------------------\n";
        mudacor(12);
        mudafundo(15);
        cout<<"  Lista vazia!";
        mudacor(0);
        mudafundo(15);
        cout<<"\n-------------------------\n\n";
        mudacor(3);
        mudafundo(15);
        system("pause");
        mudacor(0);
        mudafundo(15);
    }
}
int contar(struct no *inicio)
{
    int i=0, n;
    cout<<"\n-----------------------------\n";
    cout<<" --  CONTAGEM DE ANIMAIS  --\n";
    cout<<"  1 - Contagem de todos\n  2 - Contagem por espécie";
    mudacor(1);
    mudafundo(15);
    cout<<"\nInsira a sua opção: ";
    mudacor(0);
    mudafundo(15);
    cin>>n;
    if(n==1)
    {
        while(inicio!=NULL)
        {
            i++;
            inicio=inicio->prox;
        }
        return i;
    }
    else
    {
        if(n==2)
        {
            char espc[20];
            mudacor(1);
            mudafundo(15);
            cout<<"Insira a especie a ser contada: ";
            mudacor(0);
            mudafundo(15);
            cin.ignore();
            cin.getline(espc, 20);
            strupr(espc);
            while(inicio!=NULL)
            {
                if(strcmp(inicio->especie, espc)==0)
                    i++;
                inicio=inicio->prox;
            }
            return i;
        }
        else
            return -1;
    }
}
void adotar(struct no **adotados, struct no **inicio)
{
    int n;
    int busca;
    struct no *aux;
    cout<<"\n-------------------------------------\n";
    cout<<"      --  ADOÇÃO DE ANIMAIS  --\n";
    cout<<"  1 - Realizar adoção de novo animal\n  2 - Imprimir lista de adotados\n  3 - Buscar animal adotado\n";
    mudacor(1);
    mudafundo(15);
    cout<<"Insira a sua opção: ";
    mudacor(0);
    mudafundo(15);
    cin>>n;
    switch(n)
    {
        case 1:
        {
            mudacor(1);
            mudafundo(15);
            cout<<"Insira o código do animal: ";
            mudacor(0);
            mudafundo(15);
            cin>>busca;
            aux=*inicio;
            if(aux!=NULL)
            {
                if(aux->cod==busca)
                {
                        *inicio=(*inicio)->prox;
                        inserir_no(adotados, &aux);
                }
                else
                {
                    if(aux->prox!=NULL)
                    {
                        while(aux->prox->cod!=busca && aux->prox->prox!=NULL)
                            aux=aux->prox;
                        if(aux->prox->cod==busca)
                        {
                            struct no *aux2;
                            aux2=aux->prox;
                            aux->prox=aux2->prox;
                            inserir_no(adotados, &aux2);
                        }
                        else
                        {
                            mudacor(12);
                            mudafundo(15);
                            cout<<"\n  Animal não encontrado\n\n";
                            mudacor(3);
                            mudafundo(15);
                            system("pause");
                            mudacor(0);
                            mudafundo(15);
                        }
                    }
                    else
                    {
                        mudacor(12);
                        mudafundo(15);
                        cout<<"\n  Animal não encontrado\n\n";
                        mudacor(3);
                        mudafundo(15);
                        system("pause");
                        mudacor(0);
                        mudafundo(15);
                    }
                }
            }
            else
            {
                cout<<"\n-------------------------\n";
                mudacor(12);
                mudafundo(15);
                cout<<"  Lista vazia!";
                mudacor(0);
                mudafundo(15);
                cout<<"\n-------------------------\n\n";
                mudacor(3);
                mudafundo(15);
                system("pause");
                mudacor(0);
                mudafundo(15);
            }
        }break;
        case 2:
        {
            struct no *aux2;
            aux2=*adotados;
            imprimir(aux2);
        }break;
        case 3:
        {
            struct no *aux2;
            aux2=*adotados;
            achar(aux2);
        }break;
        default:{
            mudacor(12);
            mudafundo(15);
            cout<<"\nOpção inválida!\n\n";
            mudacor(3);
            mudafundo(15);
            system("pause");
            mudacor(0);
            mudafundo(15);
        }
    }
}
void recuperar(struct no **inicio, struct no **apagados)
{
    struct no *aux;
    int busca;
    mudacor(1);
    mudafundo(15);
    cout<<"Insira o código do animal a ser recuperado: ";
    mudacor(0);
    mudafundo(15);
    cin>>busca;
    aux=*apagados;
    if(aux!=NULL)
    {
        if(aux->cod==busca)
        {
            *apagados=(*apagados)->prox;
            inserir_no(inicio, &aux);
        }
        else
        {
            if(aux->prox!=NULL)
            {
                while(aux->prox->cod!=busca && aux->prox->prox!=NULL)
                    aux=aux->prox;
                if(aux->prox->cod==busca)
                {
                    struct no *aux2;
                    aux2=aux->prox;
                    aux->prox=aux2->prox;
                    inserir_no(inicio, &aux2);
                }
                else
                {
                    mudacor(12);
                    mudafundo(15);
                    cout<<"\n  Animal não encontrado\n\n";
                    mudacor(3);
                    mudafundo(15);
                    system("pause");
                    mudacor(0);
                    mudafundo(15);
                }
            }
            else
            {
                mudacor(12);
                mudafundo(15);
                cout<<"\n  Animal não encontrado\n\n";
                mudacor(3);
                mudafundo(15);
                system("pause");
                mudacor(0);
                mudafundo(15);
            }
        }
    }
}
void mudacor(int cor)
{
    /*
    0 = Preto        8 = Cinza
    1. = Azul        9 = Azul Claro
    2. = Verde       A = Verde Claro
    3. = Verde-Agua  B = Verde-Agua Claro
    4. = Vermelho    C = Vermelho Claro
    5. = Roxo        D = Lilas
    6. = Amarelo     E = Amarelo Claro
    7. = Branco      F = Branco Brilhante
    */
    HANDLE Saida;
    Saida = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(Saida,cor);
}
void mudafundo (int cor)
{
    CONSOLE_SCREEN_BUFFER_INFO var;
    HANDLE Saida;
    Saida = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(Saida, &var);
    var.wAttributes &= 0x000F;
    SetConsoleTextAttribute (Saida, var.wAttributes |= (cor << 4));
}
