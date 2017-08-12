#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qsexterno.h"
#include "funcoes_auxiliares.h"
//#include "time.h"

int main(){
    //clock_t inicio, fim;
    //double t;
    //inicio = clock();
    int numero_conversas, limite_palavras;
    char *entrada, *saida;
    entrada = (char*)calloc(32,sizeof(char));
    saida = (char*)calloc(32,sizeof(char));

    scanf("%d %d %s %s", &numero_conversas, &limite_palavras, entrada, saida);
    //printf("%ld\n", sizeof(PALAVRA));
    limite_palavras = limite_palavras / sizeof(PALAVRA);
//    printf("%d\n", limite_palavras);
    int i;
    FILE *arquivo;

    char *arquivo_entrada;
    arquivo_entrada = (char*)calloc(32,sizeof(char));
    char *indice_arquivo;
    indice_arquivo = (char*)calloc(32,sizeof(char));

    char caracter;
    FILE *arquivo_txt;
    FILE *arq_bin;
    arq_bin = fopen("bin", "w+b");
    char *arquivo_saida;
    arquivo_saida = (char*)calloc(32,sizeof(char));
    char *palavra;
    palavra = (char*)calloc(32,sizeof(char));
    char *palavra_binario;//usado no strtok para a palavra
    char *token;//usado no strtok para comversa, frequencia e posicao
    int conversa, frequencia, posicao;
    sprintf(arquivo_saida, "%sindice", saida);
    arquivo_txt = fopen(arquivo_saida, "w+t");

    int contador_palavras = 0;
    for (i = 1; i <= numero_conversas; i++){

      //  snprintf(indice_arquivo, 25, "%d", i);
        sprintf(arquivo_entrada, "%s%d", entrada, i);
        arquivo = fopen(arquivo_entrada, "r+t");

    //    printf("%s\n", arquivo_entrada);
        int contador_bytes = 0;
        int primeiro_byte = 0;
        int numero_caracteres = 0;

        while(!feof(arquivo)){
            fscanf(arquivo, "%c", &caracter);
            numero_caracteres ++;
        }

        fseek(arquivo, 0, SEEK_SET);

        while(!feof(arquivo)){
            fscanf(arquivo, "%c", &caracter);
            if (caracter != ' ' && caracter != '\n'){
                contador_bytes ++;
                fprintf(arquivo_txt,"%c", caracter);
            } else if(caracter == ' ' || caracter == '\n'){
                contador_bytes ++;
                if(contador_bytes < numero_caracteres){
                    fprintf(arquivo_txt, ",%d,0,%d\n", i, primeiro_byte);
                    contador_palavras++;
                }
                primeiro_byte = contador_bytes;
            }
        }
        fclose(arquivo);
    }
    fclose(arquivo_txt);
    arquivo_txt = fopen(arquivo_saida, "r+t");
    while(!feof(arquivo_txt)){
        fscanf(arquivo_txt, "%[^\n]\n", palavra);
        palavra_binario = strtok(palavra, ",");
        token = strtok(NULL, ",");
        conversa = atoi(token);
        token = strtok(NULL, ",");
        frequencia = atoi(token);
        token = strtok(NULL, "\n");
        posicao = atoi(token);
    //    printf("%s\n", palavra);
        fwrite(palavra_binario, 20*sizeof(char), 1, arq_bin);
        fwrite(&conversa, sizeof(int), 1, arq_bin);
        fwrite(&frequencia, sizeof(int), 1, arq_bin);
        fwrite(&posicao, sizeof(int), 1, arq_bin);
        for(int i = 0; i < 32; i++){
            palavra[i] = 0;
        }
        for(i = 0; i < 20;i++){
            palavra_binario[i] = 0;
        }
    }

    //printf("%d\n", contador_palavras);
    qsexterno_inicializacao(arq_bin, limite_palavras, 0, contador_palavras);
    arquivo = fopen(arquivo_saida, "w+t");

    calcula_frequencia(arq_bin, contador_palavras);


    //conversão binário para txt ( para a escrita no arquivo )
    PALAVRA *buffer; //buffer para transitar de um file para o outro
    buffer = (PALAVRA*)calloc(1, sizeof(PALAVRA));
    int k;
    for (k = 0; k < contador_palavras; k++){
        fseek(arq_bin, k*sizeof(char)*32, SEEK_SET);
        fread(buffer[0].palavra_binario, sizeof(char)*20, 1, arq_bin);
        fread(&buffer[0].conversa, sizeof(int), 1, arq_bin);
        fread(&buffer[0].frequencia, sizeof(int), 1, arq_bin);
        fread(&buffer[0].posicao, sizeof(int), 1, arq_bin);
        fprintf(arquivo, "%s,%d,%d,%d\n", buffer[0].palavra_binario, buffer[0].conversa, buffer[0].frequencia, buffer[0].posicao);
    }


    fclose(arq_bin);
    remove("bin");
    fclose(arquivo_txt);
    fclose(arquivo);
    free(buffer);
    free(arquivo_saida);
    free(arquivo_entrada);
    free(indice_arquivo);
    free(palavra);
    free(entrada);
    free(saida);

  //  fim = clock();
  //  t = (fim - inicio)/(double)CLOCKS_PER_SEC;

  //  printf("time = %f\n", t);
    return 0;
}
