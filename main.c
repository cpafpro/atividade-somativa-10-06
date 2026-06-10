#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARQUIVO "contas.dat"

typedef struct {
    int numero;
    char nome[50];
    float saldo;
    int ativo;
} Cliente;

void limpaBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrar(FILE *arq) {
    Cliente c;
    int pos;

    printf("Digite a posicao do registro: ");
    scanf("%d", &pos);
    limpaBuffer();

    printf("Numero da conta: ");
    scanf("%d", &c.numero);
    limpaBuffer();

    printf("Nome do cliente: ");
    fgets(c.nome, 50, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Saldo inicial: ");
    scanf("%f", &c.saldo);
    limpaBuffer();

    c.ativo = 1;

    fseek(arq, pos * sizeof(Cliente), SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arq);

    printf("Cliente cadastrado na posicao %d!\n", pos);
}

void consultar(FILE *arq) {
    Cliente c;
    int numero, achou = 0;

    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    limpaBuffer();

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo == 1 && c.numero == numero) {
            printf("Numero: %d\n", c.numero);
            printf("Nome: %s\n", c.nome);
            printf("Saldo: %.2f\n", c.saldo);
            achou = 1;
            break;
        }
    }

    if (achou == 0)
        printf("Conta nao encontrada.\n");
}

void atualizarSaldo(FILE *arq) {
    Cliente c;
    int numero, achou = 0;
    float novoSaldo;
    long pos;

    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    limpaBuffer();

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo == 1 && c.numero == numero) {
            achou = 1;
            break;
        }
    }

    if (achou == 0) {
        printf("Conta nao encontrada.\n");
        return;
    }

    printf("Saldo atual: %.2f\n", c.saldo);
    printf("Novo saldo: ");
    scanf("%f", &novoSaldo);
    limpaBuffer();

    c.saldo = novoSaldo;

    pos = ftell(arq) - sizeof(Cliente);
    fseek(arq, pos, SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arq);

    printf("Saldo atualizado!\n");
}

void encerrarConta(FILE *arq) {
    Cliente c;
    int numero, achou = 0;
    long pos;

    printf("Digite o numero da conta: ");
    scanf("%d", &numero);
    limpaBuffer();

    rewind(arq);
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo == 1 && c.numero == numero) {
            achou = 1;
            break;
        }
    }

    if (achou == 0) {
        printf("Conta nao encontrada.\n");
        return;
    }

    c.ativo = 0;

    pos = ftell(arq) - sizeof(Cliente);
    fseek(arq, pos, SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arq);

    printf("Conta encerrada!\n");
}

void listar(FILE *arq) {
    Cliente c;

    rewind(arq);

    printf("\n--- Lista de clientes ---\n");
    while (fread(&c, sizeof(Cliente), 1, arq) == 1) {
        if (c.ativo == 1) {
            printf("Numero: %d | Nome: %s | Saldo: %.2f\n", c.numero, c.nome, c.saldo);
        }
    }
}

int main() {
    FILE *arq;
    int opcao;

    arq = fopen(ARQUIVO, "rb+");
    if (arq == NULL) {
        arq = fopen(ARQUIVO, "wb+");
    }

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Consultar cliente\n");
        printf("3 - Atualizar saldo\n");
        printf("4 - Encerrar conta\n");
        printf("5 - Listar clientes\n");
        printf("6 - Voltar ao inicio (rewind) e listar\n");
        printf("7 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1:
                cadastrar(arq);
                break;
            case 2:
                consultar(arq);
                break;
            case 3:
                atualizarSaldo(arq);
                break;
            case 4:
                encerrarConta(arq);
                break;
            case 5:
                listar(arq);
                break;
            case 6:
                rewind(arq);
                listar(arq);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 7);

    fclose(arq);
    return 0;
}
