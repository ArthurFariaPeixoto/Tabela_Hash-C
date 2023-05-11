#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Macro ~ é substituição de palavras por isso não chega a ser uma função
#define HASH(t_string, t_table) (t_string % t_table)

// Retire o comentario da linha abaixo para ativar o debug visual
 #define DEBUG 1

// Estrutura HASH
typedef struct Hash{ // ESTRUTURA COM CHAVE PRIMARIA, DADOS SATELITES E UM PONTEIRO APONTANDO PARA O PROXIMO VALOR DA TABELA
    char* chave;
    char* texto;
    struct Hash *prox;
}*Hash, noHash;

Hash* Make_Table(int tam){ // FUNCAO PARA CRIAR A TABELA
    int i;
    Hash *aux = (Hash*) calloc (sizeof(Hash) * tam, sizeof(Hash));
    for(i = 0; i < tam ; i++) {
        aux[i] = NULL;
    }
    return aux;
}

_Bool Insert_Table(char *chave, Hash *table, int tam, char *dados){ // FUNCAO PARA INSERIR O VALOR NA TABELA
    int t_chave = strlen(chave);
    char *aux;
    noHash *t_aux, *novo;

#ifdef DEBUG
    printf("!!INSERINDO!!\n");
#endif

    if(!(aux = (char*) calloc(sizeof(char)*strlen(chave), sizeof(char))))
        return false;

    if(!(novo = (noHash*) malloc(sizeof(noHash))))
        return false;

    //CASO NAO DE ERRO NA ALOCACAO DE MEMORIA, OS VALORES SERAO INSERIDOS
    strcpy(aux, chave);
    novo->chave = aux;
    novo->texto = dados;
    novo->prox = NULL;

    if(!table[HASH(t_chave, tam)]){
        table[HASH(t_chave, tam)] = novo;

#ifdef DEBUG
        printf("!!'INSERE SE VAZIO' OK!!\n");
#endif
        return true;
    }

    for(t_aux = table[HASH(t_chave, tam)]; t_aux && (strcmp(t_aux->chave, chave) != 0); t_aux = t_aux->prox){ //PASSA PARA A PROXIMA POSICAO DA TABELA
        if(t_aux->prox == NULL){
            t_aux->prox = novo;
            break;
        }
    }

#ifdef DEBUG
    printf("!!TUDO CERTO!!\n");
#endif

    return true;
}

_Bool Remove_Table(char *str, Hash *table, int tam){
    noHash *t_aux, *ant;

#ifdef DEBUG
    printf("!!RETIRANDO!!\n");
#endif

    if(!table[HASH(strlen(str),tam)]){

#ifdef DEBUG
        printf("!!CHAVE NAO FOI ENCONTRADA!!\n");
#endif
        return false;
    }

#ifdef DEBUG
    printf("!!PROCURANDO NA LISTA!!\n");
        printf("!!ENTRANDO NO LOOP!!\n");
#endif

    for(t_aux = table[HASH(strlen(str),tam)], ant = NULL; t_aux; ant = t_aux, t_aux = t_aux->prox){
        if(strcmp(str, t_aux->chave) == 0){
            if(!t_aux->prox && !ant)
                table[HASH(strlen(str),tam)] = NULL;
            else if(t_aux->prox && !ant)
                table[HASH(strlen(str),tam)] = t_aux->prox;
            else
                ant->prox = t_aux->prox;

#ifdef DEBUG
            printf("!!CHAVE ENCONTRADA NA TABELA!!\n");
            printf("!!TUDO CERTO!!\n");
#endif
            free(t_aux->chave);
            free(t_aux->texto);
            free(t_aux);
            return true;
        }
    }

#ifdef DEBUG
    printf("!!CHAVE NAO FOI ENCONTRADA!!\n");
#endif

    return false;
}

void Search_Table(char *chave, Hash *table, int tam){
    noHash *t_aux;

#ifdef DEBUG
    printf("!!PROCURANDO!!\n");
#endif

    for(t_aux = table[HASH(strlen(chave), tam)]; t_aux; t_aux = t_aux->prox){ // LOOP PERCORRENDO TODA A TABELA A PROCURA DA CHAVE
        if(strcmp(chave, t_aux->chave) == 0){ // SE O VALOR ATUAL FOI IGUAL AO VALOR DESEJADO, O LOOP IRA SE ENCERRAR AQUI, CASO CONTRARIO SEGUIRA PARA O PROXIMO VALOR

#ifdef DEBUG
            printf("!!CHAVE ENCONTRADA NA TABELA!!\n");
            printf("!!TUDO CERTO!!\n");
#endif
            printf("Dados da chave %s: ", chave);
            printf(t_aux->texto);
            printf("\n");
            return;
        }
    }

#ifdef DEBUG
    printf("!!CHAVE NAO FOI ENCONTRADA!!\n");
#endif

    printf("Nao foi encontrado essa chave na tabela!\n");
}

int main(){
    int n;
    char opcao, chave[100], dados[128];

    printf("Bem-vindo ao meu programa de Tabela Hash\n");
    printf("Digite o tamanho da sua Tabela Hash:");
    scanf("%d" , &n);


    // SE O TAMANHO DESEJADO FOR MAIOR QUE 50000000 OU MENOR QUE 1 O PROGRAMA NAO IRA RODAR E VAI SE ENCERRAR
    if(n<=50000000 && n>=1){
        Hash *table;
        table = Make_Table(n); // CRIA TABELA DE TAMANHO N

        printf("\nDIGITE\n");
        printf("1 para inserir dados\n");
        printf("2 para procurar um dado\n");
        printf("3 para retirar um dado\n");
        printf("4 para conferir o hash que sera gerado\n");
        printf("0 para sair do programa\n");

    // LOOP INFINITO PARA MENU DA APLICACAO ENQUANTO A OPCAO FOR DIFERENTE DE 0
    for(;;){
        scanf("%c", &opcao);

        if(opcao == '0') // SE O VALOR FOR 0 O LOOP IRA SE ENCERRAR
            break;

        switch (opcao){ // SE O VALOR FOR DIFERENTE DE 0 IRA ENTRAR NO SWITCH
            case '1':
                // PARA INSERIR OS DADOS PRIMEIRAMENTE SERA INFORMADO A CHAVE E DEPOIS OS DADOS SATELITES
                // APOS A INSERCAO, A FUNCAO BOOLEANA Insert_Table IRA IMPRIMIR NA TELA SE A INSERCAO OCORREU OU NAO

                scanf("%s", chave);
                scanf("%*c");
                scanf("%s", dados);
                scanf("%*c");

                printf("%s\n", Insert_Table(chave, table, n, dados) ? "Inserido com sucesso" : "Erro ao inserir, caso o erro persista consulte o debug do codigo");
                break;

            case '2':
                /*
                  PARA PROCURAR UM DADO NA TABELA SERA INFORMADO A CHAVE E A FUNCAO Search_Table IRA IMPRIMIR NA TELA UMA MENSAGEM
                  DE ERRO OU O VALOR ENCONTRADO NA TABELA
                */

                scanf("%s", chave);
                scanf("%*c");
                Search_Table(chave, table, n);
                break;

            case '3':
                // PARA REMOVER OS DADOS SERA INFORMADO A CHAVE
                // APOS A REMOCAO, A FUNCAO BOOLEANA Remove_Table IRA IMPRIMIR NA TELA SE A REMOCAO OCORREU OU NAO

                scanf("%s", chave);
                scanf("%*c");

                printf("%s\n", Remove_Table(chave, table, n) ? "Removido com sucesso" : "Erro ao remover, caso o erro persista consulte o debug do codigo");
                break;

            case '4':
                // PARA CONFERIR O HASH GERADO SERA INFORMADO A CHAVE
                // E O HASH SERA GERADO NOVAMENTE SEM GUARDAR NA TABELA (ASSIM SERA POSSIVEL SABER QUAL VALOR FOI PARA A TABELA)
                scanf("%s", chave);
                scanf("%*c");
                printf("Hash gerado: %d\n", HASH(strlen(chave) , n));
                break;
        }
    }// FIM DO LOOP

        // TABELA HASH DESTRUIDA
        free(table);
    }
    else{
        printf("Tamanho invalido!\n"); // CASO A TABELA SEJA MENOR QUE 1 OU MAIOR QUE 50000000
        return -1;
    }

    return EXIT_SUCCESS;
}