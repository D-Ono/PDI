#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leCabecalho(FILE *arq, int *altura, int *largura, char *str, int *corMax){
    char nmagic[3], coment[5], comentarios[50];

    fgets(nmagic, 4, arq);
    strcpy(str, nmagic);
    fscanf(arq, "%s", &coment);
    while (coment[0]== '#'){

        fgets(comentarios, 50, arq);
        fscanf(arq, "%s", &coment);
    }
    *largura = atoi(coment);
    fscanf(arq, "%d", altura);      ///fscanf(arq, "%d", &altura); NÃO PRECISA DO & PORQUE É POINTER
    fscanf(arq, "%d", corMax);      ///fscanf(arq, "%d", &corMax); NÃO PRECISA DO & PORQUE É POINTER
    return;
}

void leDados (FILE *arq,short int *M, int linha, int coluna){
    int dado;

    for(int i=0; i<linha; i++){
        for (int j=0; j<coluna; j++){
            for (int k=0; k<3; k++){
                fscanf(arq, "%d", &dado);
                *(M+i*coluna*3+j*3+k)= dado;
            }
        }
    }
    return;
}

void gravaCabecalho(FILE *arq, int altura, int largura, char *str, int corMax){
    fprintf(arq, "%s \n", str);     /// ARMAZENEI NUMERO MAGICO
    fprintf(arq, "%d \t", largura);
    fprintf(arq, "%d \n", altura);
    fprintf(arq, "%d \n", corMax);

    return;
}

void abreArquivo(FILE *arq){
    if(arq == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }

    return;
}

void convertePPM_PGM_Arq(FILE *arq, int altura, int largura, int corMax){        ///LENDO DIRETO DO ARQUIVO
    FILE *fRed, *fGreen, *fBlue;
    int dado;
    char str[3] = "P2";

    fRed = fopen("ImagemR.pgm", "w");
    abreArquivo(fRed);
    fGreen = fopen("ImagemG.pgm", "w");
    abreArquivo(fGreen);
    fBlue = fopen("ImagemB.pgm", "w");
    abreArquivo(fBlue);

    gravaCabecalho(fRed, altura, largura, &str, corMax);
    gravaCabecalho(fGreen, altura, largura, &str, corMax);
    gravaCabecalho(fBlue, altura, largura, &str, corMax);

    while(!feof(arq)){
        fscanf(arq, "%d", &dado);
        fprintf(fRed, "%d \n", dado);
        fscanf(arq, "%d", &dado);
        fprintf(fGreen, "%d \n", dado);
        fscanf(arq, "%d", &dado);
        fprintf(fBlue, "%d \n", dado);
    }

    fclose(fRed);
    fclose(fGreen);
    fclose(fBlue);

    return;
}

void convertePPM_PGM_Mat(FILE *arq, int altura, int largura, int corMax){        ///LENDO DA MATRIZ
    FILE *fRed, *fGreen, *fBlue;
    short int M[altura][largura][3];
    char str[3] = "P2";
    int a;

    fRed = fopen("ImagemR.pgm", "w");
    abreArquivo(fRed);
    fGreen = fopen("ImagemG.pgm", "w");
    abreArquivo(fGreen);
    fBlue = fopen("ImagemB.pgm", "w");
    abreArquivo(fBlue);

    gravaCabecalho(fRed, altura, largura, &str, corMax);
    gravaCabecalho(fGreen, altura, largura, &str, corMax);
    gravaCabecalho(fBlue, altura, largura, &str, corMax);

    leDados(arq, &M, altura, largura);

    for(int i=0; i<altura; i++){
        for (int j=0; j<largura; j++){
                fprintf(fRed, "%d \n", M[i][j][0]);
                fprintf(fGreen, "%d \n", M[i][j][1]);
                fprintf(fBlue, "%d \n", M[i][j][2]);
        }
    }

    fclose(fRed);
    fclose(fGreen);
    fclose(fBlue);

    return;
}

int main(){
    FILE *f1;
    int altura, largura, corMax, canal=3;
    char nmagic[4];

    f1= fopen("imagem2.ppm", "r");
    if (f1 == NULL){
        printf("Arquivo Nao Aberto Corretamente...");
        exit(0);
    }
    leCabecalho(f1, &altura, &largura, &nmagic, &corMax);
    convertePPM_PGM_Mat(f1, altura, largura, corMax);

    printf("Programa Gerou os Arquivos Com Sucesso!!!");

    return;
}
