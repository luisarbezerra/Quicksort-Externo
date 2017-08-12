#ifndef _FUNCOES_AUXILIARES
#define _FUNCOES_AUXILIARES
#include "qsexterno.h"

typedef struct PALAVRA {
    char palavra_binario[20];
    int conversa;
    int frequencia;
    int posicao;
} PALAVRA;

void atualiza_frequencia(FILE* arq_b, int j, int count, PALAVRA *atualizador);
void calcula_frequencia(FILE*arq_bin, int contador_palavras);
void LeiaDireita(FILE *arq_bin, int limite_bytes, PALAVRA *pivo, PALAVRA *comparador, int esquerda, int direita, int *LeituraEsq, int *LeituraDir, int *EscritaEsq, int *EscritaDir);
void LeiaEsquerda(FILE *arq_bin, int limite_bytes, PALAVRA *pivo, PALAVRA *comparador, int esquerda, int direita, int *LeituraEsq, int *LeituraDir, int *EscritaEsq, int *EscritaDir);

#endif
