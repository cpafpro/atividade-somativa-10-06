# Atividade PIF - Sistema de Manutencao de Contas

Sistema feito em C para controlar contas de clientes em um arquivo binario
(`contas.dat`), com registros de tamanho fixo (struct `Cliente`).

## Funcoes do menu

1. Cadastrar cliente em uma posicao do arquivo (fseek + fwrite)
2. Consultar cliente pelo numero da conta (fread em loop)
3. Atualizar saldo de um cliente (fread + fseek + fwrite)
4. Encerrar conta (marca o campo "ativo" como 0)
5. Listar todos os clientes
6. Voltar ao inicio do arquivo com rewind() e listar de novo
7. Sair

## Como rodar

```
gcc -o programa main.c
./programa
```
