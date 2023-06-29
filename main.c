#include <stdio.h>
#include <stdlib.h>
#include <string.h>


FILE * arqCliente;
FILE * arqProduto;
FILE * arqVenda;

// Todas as struct padr�o ---------------------------------------

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

typedef struct
{
    char rua[30];
    int numero;
    char cidade[30];
    char estado[30];
} Endereco;

typedef struct
{
    long long int cpf;
    char nome[50];
    long long int telefone;
    Endereco endereco;
    Data data;
} Cliente;

typedef struct
{
    int codigo;
    char descricao[100];
    int qteEstoque;
    float preco_unitario;
} Produto;

typedef struct
{
    int codVenda;
    long long int cpfC;
    int codProduto;
    int qteComprada; //Tem relacao com o estoque do produto
} Venda;

// Todas as listas encadeadas ----------------------------------

typedef struct noc
{
    Cliente cliente;
    struct noc *prox;
    struct noc *ant;
} noptrC;

typedef struct nop
{
    Produto produto;
    struct nop *prox;
    struct nop *ant;
} noptrP;

typedef struct nov
{
    Venda venda;
    struct nov *prox;
    struct nov *ant;
} noptrV;

// CADASTROS ------------------------
void crud_cliente(noptrC **inicioCliente, noptrV **inicioVenda);
void crud_produto(noptrP **inicioProduto, noptrV **inicioVenda);
void crud_venda(noptrC **inicioCliente, noptrP **inicioProduto, noptrV **inicioVenda);
// CLIENTE --------------------------
void cadastroCliente(noptrC **inicioCliente);
void consultarCliente(noptrC **inicioCliente,noptrV **inicioVenda,long long int cpf);
void alterarCliente(noptrC **inicioCliente, long long int cpf);
void deletarCliente(noptrC **inicioCliente, noptrV **inicioVenda, long long int cpf);
void mostrarClientes(noptrC **inicioCliente);
noptrC *existirCliente(noptrC *inicioCliente, long long int cpf);
void addCliente(noptrC **inicioCliente, Cliente cliente);
// PRODUTO --------------------------
void cadastroProduto(noptrP **inicioProduto);
void consultarProduto(noptrP **inicioProduto, int codigo);
void alterarProduto(noptrP **inicioProduto, int codigo);
void deletarProduto(noptrP **inicioProduto, noptrV **inicioVenda, int codigo);
void mostrarProdutos(noptrP **inicioProduto);
noptrP *existirProduto(noptrP *inicioProduto, int codigo);
void addProduto(noptrP **inicioProduto, Produto produto);
// VENDA --------------------------
void cadastroVenda(noptrC **inicioCliente, noptrP **inicioProduto, noptrV **inicioVenda);
void consultarVenda(noptrV **inicioVenda, int codigo);
void alterarVenda(noptrV **inicioVenda, noptrC **inicioCliente, noptrP **inicioProduto, int codigo);
void deletarVenda(noptrV **inicioVenda, int codigo);
void mostrarVendas(noptrV **inicioVenda);
noptrV *existirVenda(noptrV *inicioVenda, int codigo);
void addVenda(noptrV **inicioVenda, Venda venda);
int acimaValor(noptrV **inicioVenda, noptrP **inicioProduto);
float obterValorTotalVenda(noptrV *venda, noptrP *inicioProduto);
noptrP *existirProdutoVendaValor(noptrP *inicioProduto, int codProduto);


int verificarData(int dia, int mes, int ano)
{
    if(dia < 1 || dia > 30)
    {
        return 0; // Invalido
    }
    if(mes < 1 || mes > 12)
    {
        return 0; // Invalido
    }
    if(ano < 1930 || ano > 2023)
    {
        return 0; // Invalido
    }
    return 1; // Valido
}

int main()
{
    noptrC *inicioCliente = NULL;
    noptrP *inicioProduto = NULL;
    noptrV *inicioVenda = NULL;
    int op, op1, op2, op3;
    int cpf;

    do
    {
        //ADICIONAR LISTAS DOS CADASTROS E OUTRAS COISAS
        printf("\n ---------- ");
        printf("\n|1. Cliente|");
        printf("\n|2. Produto|");
        printf("\n| 3. Venda |");
        printf("\n| 0. Sair  |");
        printf("\n ---------- ");
        printf("\nOpcao: ");
        scanf("%d", &op);
        system("cls");

        switch(op)
        {
        case 1:
            crud_cliente(&inicioCliente, &inicioVenda);
            break;
        case 2:
            crud_produto(&inicioProduto, &inicioVenda);
            break;
        case 3:
            crud_venda(&inicioCliente, &inicioProduto, &inicioVenda);
            break;
        case 0:
            printf("\nSaindo...");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
    while(op != 0);

    return 0;
}

void crud_cliente(noptrC **inicioCliente, noptrV **inicioVenda)
{
    int op;
    long long int cpf;

    do
    {
        printf("\n -------------------- ");
        printf("\n|1. Cadastrar cliente|");
        printf("\n| 2. Alterar cliente |");
        printf("\n|3. Consultar cliente|");
        printf("\n| 4. Deletar cliente |");
        printf("\n| 5. Mostrar cliente |");
        printf("\n|     0. Voltar      |");
        printf("\n -------------------- ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cadastroCliente(inicioCliente);
            break;
        case 2:
            printf("\n--------------------ALTERAR---------------------\n");
            printf("Informe o CPF do cliente que deseja alterar: ");
            scanf("%lld", &cpf);
            alterarCliente(inicioCliente, cpf);
            break;
        case 3:
            printf("\n-------------------CONSULTAR--------------------\n");
            printf("Informe o CPF do cliente para ver: ");
            scanf("%lld", &cpf);
            consultarCliente(inicioCliente, inicioVenda, cpf);
            break;
        case 4:
            printf("\n--------------------DELETAR---------------------\n");
            printf("Informe o CPF do cliente para excluir: ");
            scanf("%lld", &cpf);
            deletarCliente(inicioCliente, inicioVenda, cpf);
            break;
        case 5:
            mostrarClientes(inicioCliente);
            break;
        case 0:
            printf("\nVoltando...");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
    while(op != 0);
}

// VERIFICAR SE JA EXISTE UM CLIENTE COM O MESMO CPF

noptrC *existirCliente(noptrC *inicioCliente, long long int cpf)
{
    noptrC *p = inicioCliente;

    while(p != NULL)
    {
        if(p->cliente.cpf == cpf)
        {
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

// CADASTRO OFICIAL DO CLIENTE ------------------------

void cadastroCliente(noptrC **inicioCliente)
{
    const char *nomeArquivo = "Clientes.txt";
    remove(nomeArquivo);
    arqCliente=fopen("Clientes.txt","a");

    int dia, mes, ano;
    Cliente c;

    printf("\n--------------------CADASTRO--------------------\n");
    printf("CPF: ");
    scanf("%lld", &c.cpf);

    setbuf(stdin, NULL);

    if(existirCliente(*inicioCliente, c.cpf) != NULL)
    {
        printf("Cliente ja existente, informe outro CPF!\n");
        return; // Encerra a funcao depois de ver que j� existe
    }
    printf("Nome: ");
    setbuf(stdin, NULL);
    fgets(c.nome, 50, stdin);
    fprintf(arqCliente,"----------------------------------------\n");
    fprintf(arqCliente,"Nome: %s \n",c.nome);


    printf("Telefone: ");
    scanf("%lld", &c.telefone);
    setbuf(stdin, NULL);
    fprintf(arqCliente,"Telefone: %lld \n",c.telefone);

    printf("Rua: ");
    setbuf(stdin, NULL);
    fgets(c.endereco.rua, 30, stdin);
    fprintf(arqCliente,"Rua: %s \n",c.endereco.rua);

    printf("Numero: ");
    scanf("%d", &c.endereco.numero);
    fprintf(arqCliente,"Numero: %d \n",c.endereco.numero);

    printf("Cidade: ");
    setbuf(stdin, NULL);
    fgets(c.endereco.cidade, 30, stdin);
    fprintf(arqCliente,"Cidade: %s \n",c.endereco.cidade);

    printf("Estado: ");
    setbuf(stdin, NULL);
    fgets(c.endereco.estado, 30, stdin);
    fprintf(arqCliente,"Cidade: %s \n",c.endereco.estado);

    printf("Data de nascimento - FORMATO (DD/MM/AAAA): \n");
    setbuf(stdin, NULL);
    scanf("%d/%d/%d", &dia, &mes, &ano);

     fprintf(arqCliente,"Data de nascimento - FORMATO (DD/MM/AAAA): %d/%d/%d \n",dia, mes, ano);
    // VERIFICAR SE A DATA � VALIDA
    fprintf(arqCliente,"----------------------------------------------------------------------------");
    while(!verificarData(dia, mes, ano))
    {
        printf("Data de nascimento invalida! Informe novamente:\n");
        scanf("%d/%d/%d", &dia, &mes, &ano);
    }
    c.data.dia = dia;
    c.data.mes = mes;
    c.data.ano = ano;

    printf("----------------------------------------------------------------------------------------\n");
    system("cls");

    addCliente(inicioCliente, c);
    printf("Cliente cadastrado!\n");
    fclose(arqCliente);
}

// CRIANDO O NO DO CLIENTE PARA SER CADASTRADO -----------------

void addCliente(noptrC **inicioCliente, Cliente cliente)
{
    noptrC *novo = (noptrC *) malloc(sizeof(noptrC));
    noptrC *p;
    novo->cliente = cliente;

    if(*inicioCliente == NULL)
    {
        novo->prox = NULL;
        *inicioCliente = novo;
    }
    else if(novo->cliente.cpf < (*inicioCliente)->cliente.cpf)
    {
        novo->prox = *inicioCliente;
        *inicioCliente = novo;
    }
    else
    {
        p = *inicioCliente;
        while(p->prox && novo->cliente.cpf > p->prox->cliente.cpf)
        {
            p = p->prox;
        }
        novo->prox = p->prox;
        p->prox = novo;
    }
}

// ALTERAR UM CLIENTE -------------------------

void alterarCliente(noptrC **inicioCliente, long long int cpf)
{
    int op;
    noptrC *p = existirCliente(*inicioCliente, cpf);

    if(p == NULL)
    {
        printf("Cliente nao cadastrado para alteracoes.\n");
    }
    else
    {
        printf("\n|  ALTERACAO |\n");
        printf("\n|1.   Nome   |");
        printf("\n|2. Telefone |");
        printf("\n|3. Endereco |");
        printf("\n ------------ ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        Cliente *c = &(p->cliente); // Ponteiro que pega o endere�o de mem�ria e aponta para o conte�do de cliente que � tudo
        switch(op)
        {
        case 1:
            printf("Novo nome: ");
            setbuf(stdin, NULL);
            gets(c->nome);
            printf("Nome alterado com sucesso!\n");
            break;
        case 2:
            printf("Novo telefone: ");
            setbuf(stdin, NULL);
            scanf("%lld", &c->telefone);
            printf("Telefone alterado com sucesso!\n");
            break;
        case 3:
            printf("Novo endereco:\n");
            printf("Estado: ");
            setbuf(stdin, NULL);
            gets(c->endereco.estado);
            printf("Cidade: ");
            gets(c->endereco.cidade);
            printf("Rua: ");
            gets(c->endereco.rua);
            printf("Numero: ");
            setbuf(stdin, NULL);
            scanf("%d", &c->endereco.numero);
            printf("Endereco alterado com sucesso!\n");
            break;
        default:
            printf("\nOpcao invalida!");
            break;

        }
    }
}

// MOSTRAR UM CLIENTE ESPECIFICO --------------

void consultarCliente(noptrC **inicioCliente,noptrV **inicioVenda,long long int cpf)
{
    noptrC *p = existirCliente(*inicioCliente, cpf);
    if(p == NULL)
    {
        printf("Cliente nao cadastrado!\n");
    }
    else
    {
        Cliente c = p->cliente;
        printf("CPF: %lld\n", c.cpf);
        printf("Nome: %s", c.nome);
        printf("Telefone: %lld\n", c.telefone);
        printf("Rua: %s", c.endereco.rua);
        printf("Numero: %d\n", c.endereco.numero);
        printf("Cidade: %s", c.endereco.cidade);
        printf("Estado: %s", c.endereco.estado);
        printf("Data de nascimento: %d/%d/%d\n", c.data.dia, c.data.mes, c.data.ano);
    }
}

// DELETAR UM CLIENTE ESPECIFICO POR CPF ---------------------

void deletarCliente(noptrC **inicioCliente, noptrV **inicioVenda, long long int cpf)
{
    if (*inicioCliente == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    noptrC *p = *inicioCliente;
    noptrC *a = NULL;
    int flag = 0;


    while (*inicioVenda != NULL)
    {
        noptrV *v = *inicioVenda;

        if (v->venda.cpfC == cpf)
        {
            printf("Cliente presente em uma venda. Nao eh possivel excluir.\n");
            return;
        }

        *inicioVenda = (*inicioVenda)->prox;
        free(v);
    }

    *inicioVenda = NULL;

    while (p != NULL && !flag)
    {
        if (p->cliente.cpf == cpf)
        {
            flag = 1;
        }
        else
        {
            a = p;
            p = p->prox;
        }
    }

    if (flag == 0)
    {
        printf("Cliente nao encontrado!\n");
        return;
    }

    if (a == NULL)
    {
        *inicioCliente = p->prox;
    }
    else
    {
        a->prox = p->prox;
    }

    free(p);
    printf("Cliente excluido com sucesso.\n");
}



// MOSTRAR TODOS OS CLIENTES NO TERMINAL ---------------------

void mostrarClientes(noptrC **inicioCliente)
{
    noptrC *p;
    Cliente c;
    printf("\n---------------------LISTA----------------------\n");

    if(*inicioCliente == NULL)
    {
        printf("Lista de clientes vazia!\n");
    }
    else
    {
        p = *inicioCliente;

        while(p != NULL)
        {
            c = p->cliente;

            printf("\nCPF: %lld\n", c.cpf);
            printf("Nome: %s\n", c.nome);
            printf("Telefone: %lld\n", c.telefone);
            printf("Rua: %s\n", c.endereco.rua);
            printf("Numero: %d\n", c.endereco.numero);
            printf("Cidade: %s\n", c.endereco.cidade);
            printf("Estado: %s\n", c.endereco.estado);
            printf("Data de nascimento: %d/%d/%d\n", c.data.dia, c.data.mes, c.data.ano);
            printf("------------------------------------------------\n");

            p = p->prox;
        }
    }
}

// PRODUTO ---------------------

void crud_produto(noptrP **inicioProduto, noptrV **inicioVenda)
{
    int op, codigo;

    do
    {
        printf("\n -------------------- ");
        printf("\n|1. Cadastrar produto|");
        printf("\n| 2. Alterar produto |");
        printf("\n|3. Consultar produto|");
        printf("\n| 4. Deletar produto |");
        printf("\n| 5. Mostrar produto |");
        printf("\n|     0. Voltar      |");
        printf("\n -------------------- ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cadastroProduto(inicioProduto);
            break;
        case 2:
            printf("\n--------------------ALTERAR---------------------\n");
            printf("Informe o codigo do produto que deseja alterar: ");
            scanf("%d", &codigo);
            alterarProduto(inicioProduto, codigo);
            break;
        case 3:
            printf("\n-------------------CONSULTAR--------------------\n");
            printf("Informe o codigo do produto para ver: ");
            scanf("%d", &codigo);
            consultarProduto(inicioProduto, codigo);
            break;
        case 4:
            printf("\n--------------------DELETAR---------------------\n");
            printf("Informe o codigo do produto para excluir: ");
            scanf("%d", &codigo);
            deletarProduto(inicioProduto, inicioVenda, codigo);
            break;
        case 5:
            mostrarProdutos(inicioProduto);
            break;
        case 0:
            printf("\nVoltando...");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
    while(op != 0);
}

// VERIFICA SE O PRODUTO J� EXISTE ---------------

noptrP *existirProduto(noptrP *inicioProduto, int codigo)
{
    noptrP *p = inicioProduto;

    while(p != NULL)
    {
        if(p->produto.codigo == codigo)
        {
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

// CADASTRA OFICIALMENTE O PRODUTO EM UM N� --------------

void cadastroProduto(noptrP **inicioProduto)
{
    const char *nomeArquivo = "Produto.txt";
    remove(nomeArquivo);
    arqProduto=fopen("Produto.txt","a");

    Produto p;
    printf("\n--------------------CADASTRO--------------------\n");
    printf("Codigo: ");
    scanf("%d", &p.codigo);
    fprintf(arqProduto,"----------------------------------------\n");
    fprintf(arqProduto,"Codigo: %d \n",p.codigo);


    setbuf(stdin, NULL);

    if(existirProduto(*inicioProduto, p.codigo) != NULL)
    {
        printf("Produto ja existente, informe outro codigo!\n");
        return; // Encerra a fun��o depois de ver que j� existe
    }
    printf("Descricao: ");
    setbuf(stdin, NULL);
    fgets(p.descricao, 100, stdin);
    fprintf(arqProduto,"Descricao: %s \n",p.descricao);

    printf("Quantidade em estoque: ");
    scanf("%d", &p.qteEstoque);
    fprintf(arqProduto,"Quantidade em estoque: %d \n",p.qteEstoque);

    printf("Preco unitario: ");
    scanf("%f", &p.preco_unitario);
    fprintf(arqProduto,"Preco unitario: %f \n",p.preco_unitario);

    printf("------------------------------------------------\n");
    system("cls");

    addProduto(inicioProduto, p);
    printf("Produto cadastrado!\n");

    fprintf(arqProduto,"----------------------------------------\n");
    fclose(arqProduto);
}

// CRIA O N� PARA CRIAR UM PRODUTO -------------

void addProduto(noptrP **inicioProduto, Produto produto)
{
    noptrP *novo = (noptrP *) malloc(sizeof(noptrP));
    noptrP *p;
    novo->produto = produto;

    if (*inicioProduto == NULL)
    {
        novo->prox = NULL;
        *inicioProduto = novo;
    }
    else if (novo->produto.codigo < (*inicioProduto)->produto.codigo)
    {
        novo->prox = *inicioProduto;
        *inicioProduto = novo;
    }
    else
    {
        p = *inicioProduto;
        while (p->prox && novo->produto.codigo > p->prox->produto.codigo)
        {
            p = p->prox;
        }
        novo->prox = p->prox;
        p->prox = novo;
    }
}

void alterarProduto(noptrP **inicioProduto, int codigo)
{
    int op;
    noptrP *p = existirProduto(*inicioProduto, codigo);
    if(p == NULL)
    {
        printf("Produto nao cadastrado para alteracoes.\n");
    }
    else
    {
        printf("\n|  ALTERACAO |\n");
        printf("\n|1. Descricao  |");
        printf("\n|2.  Estoque   |");
        printf("\n|3.   Preco    |");
        printf("\n ------------ ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        Produto *prod = &(p->produto); // Ponteiro que pega o endere�o de mem�ria e aponta para o conte�do de cliente que � tudo
        switch(op)
        {
        case 1:
            printf("Nova descricao: ");
            setbuf(stdin, NULL);
            gets(prod->descricao);
            printf("Descricao alterado com sucesso!\n");
            break;
        case 2:
            printf("Nova quantidade: ");
            setbuf(stdin, NULL);
            scanf("%d", &prod->qteEstoque);
            printf("Estoque alterado com sucesso!\n");
            break;
        case 3:
            printf("Novo preco:\n");
            scanf("%f", &prod->preco_unitario);
            printf("Preco alterado com sucesso!\n");
            break;
        default:
            printf("\nOpcao invalida!");
            break;

        }
    }
}

// MOSTRAR UM CLIENTE ESPECIFICO --------------

void consultarProduto(noptrP **inicioProduto, int codigo)
{
    noptrP *p = existirProduto(*inicioProduto, codigo);
    if(p == NULL)
    {
        printf("Produto nao cadastrado!\n");
    }
    else
    {
        Produto prod = p->produto;
        printf("Codigo: %d\n", prod.codigo);
        printf("Descricao: %s", prod.descricao);
        printf("Quantidade em estoque: %d\n", prod.qteEstoque);
        printf("Preco unitario: %.2f", prod.preco_unitario);
    }
}

// DELETAR UM PRODUTO EXISTENTE -----------------------

void deletarProduto(noptrP **inicioProduto, noptrV **inicioVenda ,int codigo)
{
    if (*inicioProduto == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    noptrP *p = *inicioProduto;
    noptrP *a = NULL;
    int flag = 0;


    while (*inicioVenda != NULL)
    {
        noptrV *v = *inicioVenda;

        if (v->venda.codProduto == codigo)
        {
            printf("Produto presente em uma venda. Nao eh possivel excluir.\n");
            return;
        }

        *inicioVenda = (*inicioVenda)->prox;
        free(v);
    }

    *inicioVenda = NULL;

    while (p != NULL && !flag)
    {
        if (p->produto.codigo == codigo)
        {
            flag = 1;
        }
        else
        {
            a = p;
            p = p->prox;
        }
    }

    if (flag == 0)
    {
        printf("Produto nao encontrado!\n");
        return;
    }

    if (a == NULL)
    {
        *inicioProduto = p->prox;
    }
    else
    {
        a->prox = p->prox;
    }

    free(p);
    printf("Produto excluido com sucesso.\n");

}
// MOSTRAR TODOS OS PRODUTOS --------------

void mostrarProdutos(noptrP **inicioProduto)
{
    noptrP *p;
    Produto prod;
    printf("\n---------------------LISTA----------------------\n");

    if(*inicioProduto == NULL)
    {
        printf("Lista de produtos vazia!\n");
    }
    else
    {
        p = *inicioProduto;

        while(p != NULL)
        {
            prod = p->produto;

            printf("\nCodigo: %d\n", prod.codigo);
            printf("Descricao: %s\n", prod.descricao);
            printf("Quantidade em estoque: %d\n", prod.qteEstoque);
            printf("Preco unitario: %.2f\n", prod.preco_unitario);
            printf("------------------------------------------------\n");

            p = p->prox;
        }
    }
}

// VENDA --------------------------

void crud_venda(noptrC **inicioCliente, noptrP **inicioProduto, noptrV **inicioVenda)
{
    int op;
    int codVenda;
    float valor;
    int estAbaixo;
    Cliente cliente;
    Produto produto;

    do
    {
        printf("\n -------------------- ");
        printf("\n|1. Cadastrar venda|");
        printf("\n| 2. Alterar venda |");
        printf("\n|3. Consultar venda|");
        printf("\n| 4. Deletar venda |");
        printf("\n| 5. Mostrar venda |");
        printf("\n| 6.  Acima valor  |");
        printf("\n| 7. Abaixo estoque|");
        printf("\n|     0. Voltar    |");
        printf("\n -------------------- ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        switch(op)
        {
        case 1:
            cadastroVenda(inicioCliente, inicioProduto, inicioVenda);
            break;
        case 2:
            printf("\n--------------------ALTERAR---------------------\n");
            printf("Informe o codigo da venda que deseja alterar: ");
            scanf("%d", &codVenda);
            alterarVenda(inicioVenda, inicioCliente, inicioProduto, codVenda);
            break;
        case 3:
            printf("\n-------------------CONSULTAR--------------------\n");
            printf("Informe o codigo da venda para ver: ");
            scanf("%d", &codVenda);
            consultarVenda(inicioVenda, codVenda);
            break;
        case 4:
            printf("\n--------------------DELETAR---------------------\n");
            printf("Informe o codigo da venda para excluir: ");
            scanf("%d", &codVenda);
            deletarVenda(inicioVenda, codVenda);
            break;
        case 5:
            mostrarVendas(inicioVenda);
            break;
        case 6:
            printf("\n--------------------VALORES---------------------\n");
            printf("Quatidade acima: %d\n",acimaValor(inicioVenda, inicioProduto));
            break;
        case 7:
            printf("\n--------------------ESTOQUE---------------------\n");
            printf("Informe um valor para ver quais produtos estao de estoque abaixo: ");
            scanf("%d", &estAbaixo);
            estoqueAbaixo(inicioProduto, estAbaixo);
            break;
        case 0:
            printf("\nVoltando...");
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
    while(op != 0);
}

// VERIFICA SE A VENDA J� EXISTE ---------------

noptrV *existirVenda(noptrV *inicioVenda, int codigoVenda)
{
    noptrV *p = inicioVenda;

    while(p != NULL)
    {
        if(p->venda.codVenda == codigoVenda)
        {
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

// Esse aqui � para verificar se o cliente existe no CADASTRO

int *existirClienteVenda(noptrC *inicioCliente, long long int cpf)
{
    noptrC *p = inicioCliente;
    while (p != NULL)
    {
        if (p->cliente.cpf == cpf)
        {
            return 0;
        }

        p = p->prox;
    }
    return 1;
}

// Esse aqui � para verificar se o produto existe no CADASTRO

int *existirProdutoVenda(noptrP *inicioProduto, int codProduto)
{
    noptrP *p = inicioProduto;
    while (p != NULL)
    {
        if (p->produto.codigo == codProduto)
        {
            return 0;
        }

        p = p->prox;
    }
    return 1;
}


// CADASTRA OFICIALMENTE A VENDA EM UM N� --------------

void cadastroVenda(noptrC **inicioCliente, noptrP **inicioProduto, noptrV **inicioVenda)
{

    const char *nomeArquivo = "Vendas.txt";
    remove(nomeArquivo);
    arqVenda=fopen("Vendas.txt","a");

    Cliente c;
    Produto p;
    Venda v;
    int codigoVenda, codigoProduto, quantidadeComprada;
    long long int cpfCliente;

    printf("\n--------------------CADASTRO--------------------\n");
    printf("Codigo da venda: ");
    scanf("%d", &codigoVenda);
    fprintf(arqVenda,"----------------------------------------\n");
    fprintf(arqVenda,"Codigo da venda: %d \n",codigoVenda);


    // Verificar se ja existe igual
    if(existirVenda(*inicioVenda, codigoVenda) != NULL)
    {
        printf("Codigo da venda ja existente, informe outro: ");
        return;
    }

    printf("Informe o CPF do cliente: ");
    scanf("%lld", &cpfCliente);
    fprintf(arqVenda,"CPF: %lld \n",cpfCliente);

    int retornoc = existirClienteVenda(*inicioCliente, cpfCliente); // Esse aqui eh para verificar se o cliente existe no CADASTRO
    if(retornoc == 1)
    {
        printf("Cliente nao encontrado!");
        return;
    }
    printf("Informe o codigo do produto: ");
    scanf("%d", &codigoProduto);
    fprintf(arqVenda,"codigo do produto: %d \n",codigoProduto);

    int retornop = existirProdutoVenda(*inicioProduto, codigoProduto); // Esse aqui eh para verificar se o produto existe no CADASTRO
    if(retornop == 1)
    {
        printf("Produto nao encontrado!");
        return;
    }

    printf("Informe a quantidade comprada: ");
    scanf("%d", &quantidadeComprada);
    fprintf(arqVenda,"Informe a quantidade comprada: %d \n",quantidadeComprada);

    int estoqueDisponivel = obterQuantidadeEstoque(*inicioProduto, codigoProduto);
    if (quantidadeComprada > estoqueDisponivel)
    {
        printf("Quantidade comprada excede o estoque disponivel!\n");
        return;
    }

    diminuirEstoque(inicioProduto, codigoProduto, quantidadeComprada);

    v.codVenda = codigoVenda;
    v.codProduto = codigoProduto;
    v.cpfC = cpfCliente;
    v.qteComprada = quantidadeComprada;

    addVenda(inicioVenda, v);
    printf("Venda cadastrada!\n");

    fprintf(arqVenda,"----------------------------------------\n");
    fclose(arqVenda);
}

// CRIA O NO PARA CRIAR UM PRODUTO INSER��O ORDENADA -------------

void addVenda(noptrV **inicioVenda, Venda venda)
{
    noptrV *novo = (noptrV *) malloc(sizeof(noptrV));
    noptrV *p;
    novo->venda = venda;

    if (*inicioVenda == NULL)
    {
        novo->prox = NULL;
        *inicioVenda = novo;
    }
    else if (novo->venda.codVenda < (*inicioVenda)->venda.codVenda)
    {
        novo->prox = *inicioVenda;
        *inicioVenda = novo;
    }
    else
    {
        p = *inicioVenda;
        while (p->prox && novo->venda.codVenda > p->prox->venda.codVenda)
        {
            p = p->prox;
        }
        novo->prox = p->prox;
        p->prox = novo;
    }
}

// Esse aqui eh para verificar se o cliente existe no ALTERAR

int existirClienteVenda2(noptrC **inicioCliente, long long int cpf)
{
    noptrC *p = *inicioCliente;

    while (p != NULL)
    {
        if (p->cliente.cpf == cpf)
        {
            return 1; // Cliente encontrado
        }

        p = p->prox;
    }

    return 0; // Cliente nao encontrado
}

// Esse aqui eh para verificar se o produto existe no ALTERAR

int existirProdutoVenda2(noptrP **inicioProduto, int codigoProduto)
{
    noptrP *p = *inicioProduto;

    while (p != NULL)
    {
        if (p->produto.codigo == codigoProduto)
        {
            return 1; // Produto encontrado
        }

        p = p->prox;
    }

    return 0; // Produto nao encontrado
}

// Esse aqui � para verificar se a quantidade no estoque � maior da que quero comprar que existe no ALTERAR

void alterarVenda(noptrV **inicioVenda, noptrC **inicioCliente, noptrP **inicioProduto, int codVenda)
{
    int op;
    long long int cpf;
    int codigoProduto;
    int quantidade;
    int quantidadeProduto;
    noptrV *p = existirVenda(*inicioVenda, codVenda);

    if (p == NULL)
    {
        printf("Venda nao cadastrada para alteracoes.\n");
    }
    else
    {
        printf("\n|    ALTERACAO |\n");
        printf("\n|1.   Cliente  |");
        printf("\n|2.   Produto  |");
        printf("\n|3. Quantidade |");
        printf("\n ------------ ");
        printf("\nOpcao: ");
        scanf("%d", &op);

        Venda *vend = &(p->venda); // Ponteiro que pega o endere�o de mem�ria e aponta para o conte�do de cliente que � tudo

        switch (op)
        {
        case 1:
            printf("Novo CPF do cliente: ");
            scanf("%lld", &cpf);

            // Verificar se o cliente existe
            if (existirClienteVenda2(inicioCliente, cpf))
            {
                vend->cpfC = cpf;
                printf("Cliente alterado com sucesso!\n");
            }
            else
            {
                printf("Cliente nao encontrado!\n");
            }
            break;
        case 2:
            printf("Novo codigo do produto: ");
            scanf("%d", &codigoProduto);
            // Verificar se o produto existe
            quantidade = existirProdutoVenda2(inicioProduto, codigoProduto);
            if (quantidade)
            {
                vend->codProduto = codigoProduto;
                printf("Produto alterado com sucesso!\n");
            }
            else
            {
                printf("Produto nao encontrado!\n");
            }
            break;
        case 3:
            printf("Nova quantidade do produto:\n");
            scanf("%d", &quantidadeProduto);
            if (quantidadeProduto < 0)
            {
                printf("Quantidade invalida!\n");
                return;
            }

            // Verificar se o produto existe na venda
            if (existirProdutoVenda2(inicioProduto, vend->codProduto))
            {
                int estoqueAtual = obterQuantidadeEstoque(*inicioProduto, vend->codProduto);
                int diferenca = quantidadeProduto - vend->qteComprada;

                if (quantidadeProduto >= vend->qteComprada) // Mais produtos adicionados à venda
                {
                    if (diferenca <= estoqueAtual) // Verificar se há estoque suficiente para adicionar os produtos
                    {
                        atualizarEstoque(inicioProduto, vend->codProduto, -diferenca); // Reduzir estoque
                        vend->qteComprada = quantidadeProduto;
                        printf("Quantidade do produto alterada com sucesso!\n");
                    }
                    else
                    {
                        printf("Quantidade insuficiente em estoque!\n");
                        printf("Estoque atual: %d\n", estoqueAtual);
                    }
                }
                else // Alguns produtos foram removidos da venda
                {
                    atualizarEstoque(inicioProduto, vend->codProduto, -diferenca); // Aumentar estoque
                    vend->qteComprada = quantidadeProduto;
                    printf("Quantidade do produto alterada com sucesso!\n");
                }
            }
            else
            {
                printf("Produto nao cadastrado!\n");
            }
            break;
        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
}

// MOSTRAR UMA VENDA ESPECIFICA --------------

void consultarVenda(noptrV **inicioVenda, int codVenda)
{
    noptrV *v = existirVenda(*inicioVenda, codVenda);

    if(v == NULL)
    {
        printf("Venda nao cadastrada!\n");
    }
    else
    {
        Venda vend = v->venda;
        printf("Codigo da venda: %d\n", vend.codVenda);
        printf("CPF: %lld\n", vend.cpfC); // MAS QUE BUCETA, N�O CONSIGO BOTAR A PORRA DO NOME
        printf("Codigo do produto: %d\n", vend.codProduto);
        printf("Quantidade comprada: %d\n", vend.qteComprada);
    }
}

// DELETAR UM PRODUTO EXISTENTE -----------------------

void deletarVenda(noptrV **inicioVenda, int codVenda)
{
    if (*inicioVenda == NULL)
    {
        printf("Lista vazia!\n");
        return;
    }

    noptrV *p = *inicioVenda;
    noptrV *a = NULL;
    int flag = 0;  // Flag para indicar se a venda foi encontrado

    while (p != NULL && !flag)
    {
        if (p->venda.codVenda == codVenda)
        {
            flag = 1;  // Produto encontrado, define a flag como verdadeira
        }
        else
        {
            a = p;
            p = p->prox;
        }
    }

    if (!flag)
    {
        printf("Venda nao encontrada!\n");
        return;
    }

    if (a == NULL)
    {
        *inicioVenda = p->prox;
    }
    else
    {
        a->prox = p->prox;
    }
    free(p);
    printf("Venda excluida com sucesso.\n");
}
// MOSTRAR TODOS OS PRODUTOS --------------

void mostrarVendas(noptrV **inicioVenda)
{
    noptrV *p;

    printf("\n---------------------LISTA----------------------\n");

    if(*inicioVenda == NULL)
    {
        printf("Lista de venda vazia!\n");
    }
    else
    {
        p = *inicioVenda;

        while(p != NULL)
        {
            Venda vend = p->venda;

            printf("Codigo da venda: %d\n", vend.codVenda);
            printf("CPF e nome do cliente: %lld\n", vend.cpfC);
            printf("Codigo do produto: %d\n", vend.codProduto);
            printf("Quantidade comprada: %d\n", vend.qteComprada);
            printf("------------------------------------------------\n");

            p = p->prox;
        }
    }
}

// OUTRAS FUNCOES AUXILIARES ------------------------

void atualizarEstoque(noptrP **inicioProduto, int codigoProduto, int diferenca)
{
    noptrP *p = existirProduto(*inicioProduto, codigoProduto);

    if (p == NULL)
    {
        printf("Produto nao encontrado!\n");
        return;
    }

    p->produto.qteEstoque += diferenca;

    if (p->produto.qteEstoque < 0)
    {
        p->produto.qteEstoque = 0;
    }

    printf("Estoque atualizado com sucesso!\n");
}

// Obtem a quantidade em estoque de um produto espec�fico
int obterQuantidadeEstoque(noptrP *inicioProduto, int codProduto)
{
    noptrP *p = inicioProduto;


    while (p != NULL)
    {
        if (p->produto.codigo == codProduto)
        {
            return p->produto.qteEstoque;
        }

        p = p->prox;
    }

    // Caso o produto nao seja encontrado, retorna -1
    return -1;
}

void diminuirEstoque(noptrP **inicioProduto, int codProduto, int qteComprada)
{
    noptrP *p = *inicioProduto;

    while (p != NULL)
    {
        if (p->produto.codigo == codProduto)
        {
            if (p->produto.qteEstoque >= qteComprada)
            {
                p->produto.qteEstoque -= qteComprada;
                printf("Estoque atualizado com sucesso!\n");
                return;
            }
            else
            {
                printf("Quantidade insuficiente em estoque!\n");
                return;
            }
        }

        p = p->prox;
    }

    printf("Produto nao encontrado!\n");
}

// Quantos clientes compraram acima de um determinado valor escolhido pelo usu�rio
int acimaValor(noptrV **inicioVenda, noptrP **inicioProduto)
{
    noptrV *pvenda = *inicioVenda;
    noptrP *pproduto = *inicioProduto;

    float valorEscolhido;
    printf("\nDigite o valor que deseja consultar: ");
    scanf("%f", &valorEscolhido);

    int quantidade = 0;

    while (pvenda && pproduto)
    {
        printf("Produto: %d  CodigoVenda: %d\n", pvenda->venda.codVenda, pproduto->produto.codigo);

        if (pvenda->venda.codVenda == pproduto->produto.codigo)
        {
            float valorTotal = pvenda->venda.qteComprada * pproduto->produto.preco_unitario;
            printf("---------------------------------------\n");
            printf("Valor: %.2f\n", valorEscolhido);
            printf("Valor Total: %.2f\n", valorTotal);
            printf("---------------------------------------\n");

            if (valorTotal > valorEscolhido)
            {
                quantidade++;
            }
            pproduto = pproduto->prox;
            pvenda = pvenda->prox;
        }
        else if (pvenda->venda.codVenda < pproduto->produto.codigo)
        {
            pvenda = pvenda->prox;
        }
        else
        {
            pproduto = pproduto->prox;
        }
    }
    return quantidade;
}



// Quais os produtos que estao com a quantidade em estoque abaixo de um determinado valor escolhido pelo usuario
void estoqueAbaixo(noptrP **inicioProduto, int valorBuscado)
{
    int obsever = 0;
    noptrP *produtoBuscado;
    produtoBuscado = *inicioProduto;

    printf("\nProdutos quantidade inferior: \n");
    while(produtoBuscado)
    {
        if(produtoBuscado->produto.qteEstoque < valorBuscado)
        {
            printf("--------------------------------------");
            printf("\nDescricao: %s", produtoBuscado->produto.descricao);
            printf("\nCodigo: %d", produtoBuscado->produto.codigo);
            printf("\nQuantidade em estoque: %d",produtoBuscado->produto.qteEstoque);
            printf("\n--------------------------------------\n");
            obsever++;
        }
        produtoBuscado=produtoBuscado->prox;
    }
    if(obsever == 0)
    {
        printf("\n--------------------------------------");
        printf("\nNenhum produto encontrado");
    }

}

float obterValorTotalVenda(noptrV *venda, noptrP *inicioProduto)
{
    float valorTotal = 0.0;
    noptrV *p = venda;
    Produto prod;
    int codProduto = p->venda.codProduto;
    int quantidadeComprada = p->venda.qteComprada;
    noptrP *produto = existirProdutoVendaValor(inicioProduto, codProduto);
    while (p != NULL)
    {
        if (produto != NULL)
        {
            float precoUnitario = prod.preco_unitario;
            float valorProduto = precoUnitario * quantidadeComprada;
            valorTotal += valorProduto;
        }

        p = p->prox;
    }

    return valorTotal;
}

noptrP *existirProdutoVendaValor(noptrP *inicioProduto, int codProduto)
{
    noptrP *p = inicioProduto;

    while (p != NULL)
    {
        if (p->produto.codigo == codProduto)
        {
            return p;
        }

        p = p->prox;
    }
    return NULL;
}



