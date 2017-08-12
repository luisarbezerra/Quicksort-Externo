#ifndef _QSEXTERNO
#define _QSEXTERNO
#include "funcoes_auxiliares.h"

typedef struct PALAVRA palavra_def; //redefinição para dar certo.

void qsexterno (FILE *arq_bin, palavra_def *pivo, palavra_def *comparador, int limite_bytes, int esquerda, int direita);
void qsexterno_inicializacao (FILE *arq_bin, int limite_bytes, int esquerda, int direita);
int cmpfunc (const void *a, const void *b);

#endif
