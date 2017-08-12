#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qsexterno.h"
#include "funcoes_auxiliares.h"

void printa_pivo(PALAVRA*pivo, int limite_palavras){
    int i;
    for(i = 0; i < limite_palavras-1; i++){
        printf("%s %d %d %d\n", pivo[i].palavra_binario, pivo[i].conversa, pivo[i].frequencia, pivo[i].posicao);
    }
}

int cmpfunc (const void *a, const void *b){ //função usada no qsort para ordenação após comparar 2 strings.
    PALAVRA *p1 = (PALAVRA *)a, *p2 = (PALAVRA *)b; //fazendo cast
    int compara = strcmp(p1->palavra_binario, p2->palavra_binario);
    if(compara == 0){
        if(p1->conversa > p2->conversa){
            compara = 1;
        } else if(p1->conversa < p2->conversa){
            compara = -1;
        } else if(p1->conversa == p2->conversa){
            if(p1->posicao > p2->posicao){
                compara = 1;
            } else if(p1->posicao < p2->posicao){
                compara = -1;
            }
        }
    }
    return compara;
}

void qsexterno_inicializacao (FILE *arq_bin, int limite_palavras, int esquerda, int direita) {
    PALAVRA *pivo;
    pivo = (PALAVRA*)calloc(limite_palavras-1, sizeof(PALAVRA));

    PALAVRA *comparador;
    comparador = (PALAVRA*)calloc(1,sizeof(PALAVRA));

    qsexterno(arq_bin, pivo, comparador, limite_palavras, esquerda, direita);

    free(pivo);
    free(comparador);
}

void qsexterno (FILE *arq_bin, PALAVRA *pivo, PALAVRA *comparador, int limite_palavras, int esquerda, int direita) {
    int pivo_cheio = 0;
    int i;
    int escrita_pivo_arquivo; //este inteiro guarda a posição, da esquerda pra direita, de onde será escrito o pivô no arquivo. usamos isso quando já foi ordenado todo o resto, faltando somente os elementos do próprio pivô a serem ordenados e inseridos no arquivo.
    int LeituraEsq = esquerda, LeituraDir = direita-1, EscritaEsq = esquerda, EscritaDir = direita-1;
//    printf("chamada qsort:\nesquerda:%d direita:%d\nLeituraEsq:%d LeituraDir:%d\nEscritaEsq:%d EscritaDir:%d\n", esquerda, direita, LeituraEsq, LeituraDir, EscritaEsq, EscritaDir);
    int tamanho_particao = direita - esquerda; //tamanho da parte do arquivo que estou analisando.

// análise do que fazer com a partição
    if(tamanho_particao <= 1){
        return; //quando o quicksort está em seu menor tamanho, condição de parada após ir diminuindo. 1 ou 0.
    } else if (limite_palavras > (tamanho_particao)) { //partição analisada maior que o pivô.
        for(i = 0; i < (tamanho_particao); i++) { //preenche o pivô.
            LeituraEsq = i + esquerda; //preenchendo o pivô
            fseek(arq_bin, LeituraEsq*sizeof(char)*32, SEEK_SET); //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fread(pivo[i].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no pivô com o tamanho ali especificado (de uma palavra).
            fread(&pivo[i].conversa, sizeof(int), 1, arq_bin);
            fread(&pivo[i].frequencia, sizeof(int), 1, arq_bin);
            fread(&pivo[i].posicao, sizeof(int), 1, arq_bin);
        }
//        printf("1\n");
        qsort(pivo, tamanho_particao, sizeof(PALAVRA), cmpfunc);
//        printa_pivo(pivo, limite_palavras);

        for (i = 0; i < tamanho_particao; i++) {
            EscritaEsq = i + esquerda; //preenchendo o arquivo com o pivô
            fseek(arq_bin, EscritaEsq*sizeof(char)*32, SEEK_SET); //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[i].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do pivô e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[i].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[i].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[i].posicao, sizeof(int), 1, arq_bin);
        }
    } else if (tamanho_particao >= limite_palavras) {
        while (pivo_cheio < (limite_palavras - 1)) { //preenchendo o pivô até ele ficar cheio
            //lendo a palavra à esquerda
            fseek(arq_bin, LeituraEsq*sizeof(char)*32, SEEK_SET); //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fread(pivo[pivo_cheio].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no pivô com o tamanho ali especificado (de uma palavra).
            fread(&pivo[pivo_cheio].conversa, sizeof(int), 1, arq_bin);
            fread(&pivo[pivo_cheio].frequencia, sizeof(int), 1, arq_bin);
            fread(&pivo[pivo_cheio].posicao, sizeof(int), 1, arq_bin);
    //        printf("leu esquerda %s\n", pivo[pivo_cheio].palavra_binario);
            pivo_cheio++;
            LeituraEsq++;


            if (pivo_cheio < (limite_palavras - 1)) {
                //lendo a palavra à direita
                fseek(arq_bin, LeituraDir*sizeof(char)*32, SEEK_SET); //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fread(pivo[pivo_cheio].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no pivô com o tamanho ali especificado (de uma palavra).
                fread(&pivo[pivo_cheio].conversa, sizeof(int), 1, arq_bin);
                fread(&pivo[pivo_cheio].frequencia, sizeof(int), 1, arq_bin);
                fread(&pivo[pivo_cheio].posicao, sizeof(int), 1, arq_bin);
        //        printf("leu direita %s\n", pivo[pivo_cheio].palavra_binario);
                pivo_cheio++;
                LeituraDir--;
            }
        }
        //pivô cheio, ordeno ele.
    //    printf("2\n");
        qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc );
    //    printa_pivo(pivo, limite_palavras);

        while (LeituraEsq <= LeituraDir) { //enquanto os leitores não se cruzaram (quando eles cruzam, termina aquela interação do quicksort)
            if (EscritaDir == LeituraDir) {
                LeiaDireita(arq_bin, limite_palavras, pivo, comparador, esquerda, direita, &LeituraEsq, &LeituraDir, &EscritaEsq, &EscritaDir);
            } else if (EscritaEsq == LeituraEsq) { //a escrita não pode passar a leitura, então dou uma "andadinha" na leitura, pois o item não terá sido lido e pode causar problemas caso ele venha a ser substituido sem ter sido ainda lido.
                LeiaEsquerda(arq_bin, limite_palavras, pivo, comparador, esquerda, direita, &LeituraEsq, &LeituraDir, &EscritaEsq, &EscritaDir);
            }

            while (LeituraEsq <= LeituraDir && EscritaEsq != LeituraEsq && EscritaDir != LeituraDir) { //ainda não se cruzaram, o vetor de escrita está também antes do seu de leitura.
                LeiaEsquerda(arq_bin, limite_palavras, pivo, comparador, esquerda, direita, &LeituraEsq, &LeituraDir, &EscritaEsq, &EscritaDir);
                if (EscritaEsq == LeituraEsq || EscritaDir == LeituraDir || LeituraEsq > LeituraDir) { //se forem iguais, saio deste while e volto pras condicionais anteriores, se for maior, é pq cruzaram e acabou aquela interaçãp de quicksort.
                    break;
                }
                LeiaDireita(arq_bin, limite_palavras, pivo, comparador, esquerda, direita, &LeituraEsq, &LeituraDir, &EscritaEsq, &EscritaDir);
            }
        }

        //escrevendo o pivô no arquivo
        for (i = 0; i < (limite_palavras-1); i++){
            escrita_pivo_arquivo = EscritaEsq + i; //partindo de onde parei de escrever por parte da esquerda, coloco as palavras do pivo após isso seguindo o fluxo abaixo.
            fseek(arq_bin, escrita_pivo_arquivo*sizeof(char)*32, SEEK_SET); //pulando de palavra em palavra
            fwrite(pivo[i].palavra_binario, sizeof(char)*20, 1, arq_bin);
            fwrite(&pivo[i].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[i].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[i].posicao, sizeof(int), 1, arq_bin);
        }
    //    printf("\npivo antes da recursão\n");
    //    printa_pivo(pivo, limite_palavras);
        if((EscritaEsq - 0) < (direita - EscritaDir)){
            qsexterno(arq_bin, pivo, comparador, limite_palavras, esquerda, EscritaEsq);
            qsexterno(arq_bin, pivo, comparador, limite_palavras, EscritaDir+1, direita);
        } else {
            qsexterno(arq_bin, pivo, comparador, limite_palavras, EscritaDir+1, direita);
            qsexterno(arq_bin, pivo, comparador, limite_palavras, esquerda, EscritaEsq);
        }
    }
}
