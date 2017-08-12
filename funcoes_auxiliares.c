#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_auxiliares.h"

void LeiaDireita(FILE *arq_bin, int limite_palavras, PALAVRA *pivo, PALAVRA *comparador, int esquerda, int direita, int *LeituraEsq, int *LeituraDir, int *EscritaEsq, int *EscritaDir){
    fseek(arq_bin, LeituraDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
    fread(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
    fread(&comparador[0].conversa, sizeof(int), 1, arq_bin);
    fread(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
    fread(&comparador[0].posicao, sizeof(int), 1, arq_bin);
    //printf("\nli direita: %s %d %d %d\n", comparador[0].palavra_binario, comparador[0].conversa, comparador[0].frequencia, comparador[0].posicao);
    int posicionamento_primeiro = strcmp(comparador[0].palavra_binario, pivo[0].palavra_binario); //retorno da função strcmp é sempre 1 se comparador é maior, -1 se ele é menor ou 0 se são iguais.

    int posicionamento_ultimo = strcmp(comparador[0].palavra_binario, pivo[limite_palavras-2].palavra_binario); 
    //análise dos retornos da strcmp segundo seu retorno (-1, 0, 1).
    if(posicionamento_primeiro < 0) { //antes do pivô que a palavra se encontra.
    //    printf("antes\n");
        fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
        fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
        fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
        EscritaEsq[0]++;
        LeituraDir[0]--; //leitura direita pra esquerda
    } else if(posicionamento_primeiro == 0){//caso igual ao primeiro do pivo, olha conversa e dps posicao
        if(comparador[0].conversa == pivo[0].conversa){//caso mesma conversa, olha posicao
            if(comparador[0].posicao > pivo[0].posicao){//posicao maior, no pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

                pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

                qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

                LeituraDir[0]--;
                EscritaEsq[0]++;
            } else{//posicao menor, antes do pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaEsq[0]++;
                LeituraDir[0]--;
            }
        } else if(comparador[0].conversa < pivo[0].conversa){//conversa menor, antes do pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaEsq[0]++;
                LeituraDir[0]--;
        } else if(comparador[0].conversa > pivo[0].conversa){//conversa maior, depois do pivo
            fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

            pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraDir[0]--;
            EscritaEsq[0]++;
        }
    } else if ((posicionamento_primeiro > 0) && (posicionamento_ultimo < 0)) {
        if ((LeituraEsq[0] - esquerda) <= (direita - LeituraDir[0])){
//printf("no pivo, ultimo\n");
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);

            pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraDir[0]--;
            EscritaDir[0]--; //ler a direita, escrever na direita, escrita direita -- para andar rumo ao centro.
        } else if ((LeituraEsq[0] - esquerda) > (direita - LeituraDir[0])){//TODO ENTENDER
//printf("no pivo, primeiro\n");
            fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

            pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraDir[0]--;
            EscritaEsq[0]++;
        }
    } else if (posicionamento_ultimo > 0) { //depois do pivô que a palavra se encontra.
//printf("depois\n");
        fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
        fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
        fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
        EscritaDir[0]--;
        LeituraDir[0]--;
    }else if(posicionamento_ultimo == 0){//caso igual ultimo do pivo, olha conversa e depois posicao
        if(comparador[0].conversa == pivo[limite_palavras - 2].conversa){//conversa igual, olhar posicao
            if(comparador[0].posicao < pivo[limite_palavras - 2].posicao){//posicao menor, no pivo
                fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
                fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);

                pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

                qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

                LeituraDir[0]--;
                EscritaDir[0]--;
            }else{//posicao maior, depois do pivo
                fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaDir[0]--;
                LeituraDir[0]--;
            }
        } else if(comparador[0].conversa < pivo[limite_palavras - 2].conversa){//conversa menor,  no pivo
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);

            pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraDir[0]--;
            EscritaDir[0]--;
        } else if(comparador[0].conversa > pivo[limite_palavras - 2].conversa){//conversa maior, depois do pivo
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
            EscritaDir[0]--;
            LeituraDir[0]--;
        }
    }

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LeiaEsquerda(FILE *arq_bin, int limite_palavras, PALAVRA *pivo, PALAVRA *comparador, int esquerda, int direita, int *LeituraEsq, int *LeituraDir, int *EscritaEsq, int *EscritaDir){
    fseek(arq_bin, LeituraEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
    fread(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
    fread(&comparador[0].conversa, sizeof(int), 1, arq_bin);
    fread(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
    fread(&comparador[0].posicao, sizeof(int), 1, arq_bin);
//printf("\nli esquerda:  %s %d %d %d\n", comparador[0].palavra_binario, comparador[0].conversa, comparador[0].frequencia, comparador[0].posicao);
    int posicionamento_primeiro = strcmp(comparador[0].palavra_binario, pivo[0].palavra_binario); //retorno da função strcmp é sempre 1 se comparador é maior, -1 se ele é menor ou 0 se são iguais.

    int posicionamento_ultimo = strcmp(comparador[0].palavra_binario, pivo[limite_palavras-2].palavra_binario); //TODO CONFERIR
    //análise dos retornos da strcmp segundo seu retorno (-1, 0, 1).
    if(posicionamento_primeiro < 0) { //antes do pivô que a palavra se encontra.
//printf("antes\n");
        fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
        fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
        fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
        EscritaEsq[0]++;
        LeituraEsq[0]++;
    }else if(posicionamento_primeiro == 0){//caso igual ao primeiro do pivo, olha conversa e dps posicao
        if(comparador[0].conversa == pivo[0].conversa){//caso mesma conversa, olha posicao
            if(comparador[0].posicao > pivo[0].posicao){//posicao maior, no pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

                pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

                qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

                LeituraEsq[0]++;
                EscritaEsq[0]++;
            } else{//posicao menor, antes do pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaEsq[0]++;
                LeituraEsq[0]++;
            }
        } else if(comparador[0].conversa < pivo[0].conversa){//conversa menor, antes do pivo
                fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaEsq[0]++;
                LeituraEsq[0]++;
        } else if(comparador[0].conversa > pivo[0].conversa){//conversa maior, no pivo
            fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

            pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraEsq[0]++;
            EscritaEsq[0]++;
        }
    } else if ((posicionamento_primeiro > 0) && (posicionamento_ultimo < 0)) {//TODO ENTENDER
        if ((LeituraEsq[0] - esquerda) <= (direita - LeituraDir[0])){
//printf("no pivo, ultimo\n");
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);
            pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraEsq[0]++;
            EscritaDir[0]--;
        } else if ((LeituraEsq[0] - esquerda) > (direita - LeituraDir[0])){//TODO ENTENDER
//printf("no pivo, primeiro\n");
            fseek(arq_bin, EscritaEsq[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[0].posicao, sizeof(int), 1, arq_bin);

            pivo[0] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraEsq[0]++;
            EscritaEsq[0]++;
        }
    } else if (posicionamento_ultimo > 0) { //depois do pivô que a palavra se encontra.
//printf("depois\n");
        fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
        fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
        fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
        fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);

        EscritaDir[0]--;
        LeituraEsq[0]++;
    } else if(posicionamento_ultimo == 0){//caso igual ultimo do pivo, olha conversa e depois posicao
        if(comparador[0].conversa == pivo[limite_palavras - 2].conversa){//conversa igual, olhar posicao
            if(comparador[0].posicao < pivo[limite_palavras - 2].posicao){//posicao menor, no pivo
                fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
                fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);

                pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

                qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

                LeituraEsq[0]++;
                EscritaDir[0]--;
            }else{//posicao maior, depois do pivo
                fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
                fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
                fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
                fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
                EscritaDir[0]--;
                LeituraEsq[0]++;
            }
        } else if(comparador[0].conversa < pivo[limite_palavras - 2].conversa){//conversa menor,  no pivo
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(pivo[limite_palavras - 2].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&pivo[limite_palavras - 2].conversa, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&pivo[limite_palavras - 2].posicao, sizeof(int), 1, arq_bin);

            pivo[limite_palavras-2] = comparador[0]; //coloco a palavra do auxiliar "comparador" no pivô.

            qsort(pivo, limite_palavras-1, sizeof(PALAVRA), cmpfunc);

            LeituraEsq[0]++;
            EscritaDir[0]--;
        } else if(comparador[0].conversa > pivo[limite_palavras - 2].conversa){//conversa maior, depois do pivo
            fseek(arq_bin, EscritaDir[0]*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fwrite(comparador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do comparador e coloco-a no arquivo com o tamanho ali especificado.
            fwrite(&comparador[0].conversa, sizeof(int), 1, arq_bin);
            fwrite(&comparador[0].frequencia, sizeof(int), 1, arq_bin);
            fwrite(&comparador[0].posicao, sizeof(int), 1, arq_bin);
            EscritaDir[0]--;
            LeituraEsq[0]++;
        }
    }
}


void calcula_frequencia(FILE*arq_bin, int contador_palavras){
//    printf("oi %d\n", contador_palavras );
    PALAVRA *buffer;
    buffer = (PALAVRA*)calloc(2, sizeof(PALAVRA));
    PALAVRA *atualizador;
    atualizador = (PALAVRA*)calloc(1, sizeof(PALAVRA));
    int count;
    int inicio, fim;
    int i = 0;
    while(i <  contador_palavras){
        count = 1;
        fseek(arq_bin, i*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
        fread(buffer[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
        fread(&buffer[0].conversa, sizeof(int), 1, arq_bin);
        fread(&buffer[0].frequencia, sizeof(int), 1, arq_bin);
        fread(&buffer[0].posicao, sizeof(int), 1, arq_bin);
        inicio = i;
        i++;
    //    printf("                palavra olhada  %s,c: %d inicio: %d i: %d\n\n", buffer[0].palavra_binario, buffer[0].conversa, inicio, i);
        if(i == contador_palavras){
            atualiza_frequencia(arq_bin, i-1, count, atualizador);
        }
        while(i <  contador_palavras){
            fseek(arq_bin, i*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
            fread(buffer[1].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
            fread(&buffer[1].conversa, sizeof(int), 1, arq_bin);
            fread(&buffer[1].frequencia, sizeof(int), 1, arq_bin);
            fread(&buffer[1].posicao, sizeof(int), 1, arq_bin);
        //    printf("                comparada %s,c: %d inicio: %d i: %d\n\n", buffer[1].palavra_binario, buffer[0].conversa, inicio, i);
            if((strcmp(buffer[0].palavra_binario, buffer[1].palavra_binario) == 0) && (buffer[0].conversa == buffer[1].conversa)){
                count++;
            }
            else{
                fim = i - 1;
                for(int j = inicio; j <= fim; j++){
                    atualiza_frequencia(arq_bin, j, count, atualizador);
                }
                break;
            }
            i++;
            if(i == contador_palavras){
                fim = i - 1;
                for(int j = inicio; j <= fim; j++){
                    atualiza_frequencia(arq_bin, j, count, atualizador);
                }
            }
        }
    }
    free(buffer);
    free(atualizador);
}

void atualiza_frequencia(FILE* arq_bin, int j, int count, PALAVRA *atualizador){//atualiza a frequencia no arquivo
    fseek(arq_bin, j*sizeof(char)*32, SEEK_SET);  //cada palavra tem tamanho 32, então estou andando por entre as palavras, fseek é uma função que posiciona o ponteiro no arquivo.
    fread(atualizador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
    fread(&atualizador[0].conversa, sizeof(int), 1, arq_bin);
    fread(&atualizador[0].frequencia, sizeof(int), 1, arq_bin);
    fread(&atualizador[0].posicao, sizeof(int), 1, arq_bin);

    atualizador[0].frequencia = count;

    fseek(arq_bin, j*sizeof(char)*32, SEEK_SET);
    fwrite(atualizador[0].palavra_binario, sizeof(char)*20, 1, arq_bin); //leio a palavra do arquivo e colo-a no comparador auxiliar com o tamanho ali especificado (de uma palavra).
    fwrite(&atualizador[0].conversa, sizeof(int), 1, arq_bin);
    fwrite(&atualizador[0].frequencia, sizeof(int), 1, arq_bin);
    fwrite(&atualizador[0].posicao, sizeof(int), 1, arq_bin);
    //printf("                atualizando %s,c: %d,f: %d inicio: %d i: %d\n\n", atualizador[0].palavra_binario, atualizador[0].conversa, atualizador[0].frequencia, inicio, i);
}
