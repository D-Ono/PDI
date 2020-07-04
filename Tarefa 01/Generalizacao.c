#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void leCabecalho(FILE *arq, int *altura, int *largura, char *str, int *corMax){
    char nmagic[3], coment[5], comentarios[50];
    int col, alt,cor;

    fgets(nmagic, 4, arq);
    strcpy(str, nmagic);
    fscanf(arq, "%s", &coment);
    while (coment[0]== '#'){

        fgets(comentarios, 50, arq);
        fscanf(arq, "%s", &coment);
    }
    *largura = atoi(coment);
    fscanf(arq, "%d", &alt);
    *altura = alt;
    fscanf(arq, "%d", &cor);
    *corMax = cor;
    return;
}

void gravaCabecalho(FILE *arq, int altura, int largura, char *str, int corMax){
    fprintf(arq, "%s \n", str);     /// ARMAZENEI NUMERO MAGICO
    fprintf(arq, "%d \n", largura);
    fprintf(arq, "%d \n", altura);
    fprintf(arq, "%d \n", corMax);

    return;
}

void leDados (FILE *arq,short int *M, int linha, int coluna){
    int dado;

    for(int i=0; i<linha; i++){
        for (int j=0; j<coluna; j++){
            fscanf(arq, "%d", &dado);
            *(M+i*coluna+j)=dado;
        }
    }
    return;
}

void gravaDados(FILE *arq,short int *M, int linha, int coluna){

    for(int i=0; i<linha; i++){
        for (int j=0; j<coluna; j++){
            fprintf(arq, "%d \t", *(M+i*coluna+j));
        }
    }
    return;
}

void escureceFoto(short int *M, int altura,int largura,int cor,char *nmagic){
    FILE *fescuro;
    int menos, escurecer;

    fescuro= fopen("fescuro.pgm", "w");
    if(fescuro == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fescuro, altura, largura, nmagic, cor);
    printf("Quanto escurecer?[0,%d]: ", cor);
    scanf("%d", &escurecer);

    for(int i=0; i<altura; i++){
        fprintf(fescuro, "\n");
        for (int j=0; j<largura; j++){
            menos = *(M+i*largura+j) - escurecer;
            if (menos < 0)
                menos = 0;
            fprintf(fescuro, "%d \t", menos);
        }
    }
    fclose(fescuro);
    return;
}

void clareiaFoto(short int *M, int altura,int largura,int cor,char *nmagic){
    int mais, clarear;
    FILE *fclaro;

    fclaro= fopen("fclaro.pgm", "w");
    if(fclaro == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fclaro, altura, largura, nmagic, cor);
    printf("Quanto Clarear?[0,%d]: ", cor);
    scanf("%d", &clarear);

    for(int i=0; i<altura; i++){
        fprintf(fclaro, "\n");
        for (int j=0; j<largura; j++){
            mais = *(M+i*largura+j) + clarear;
            if (mais > cor)
                mais = cor;
            fprintf(fclaro, "%d \t", mais);
        }
    }
    fclose(fclaro);
    return;
}

void negativaFoto(short int *M, int altura,int largura,int cor,char *nmagic){
    int negativo;
    FILE *fnegativo;

    fnegativo= fopen("fnegativo.pgm", "w");
    if(fnegativo == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fnegativo, altura, largura, nmagic, cor);

    for(int i=0; i<altura; i++){
        fprintf(fnegativo, "\n");
        for (int j=0; j<largura; j++){
            negativo = cor - *(M+i*largura+j);
            fprintf(fnegativo, "%d \t", negativo);
        }
    }
    fclose(fnegativo);
    return;
}

void GirarParaDireita(short int *M, int altura,int largura,int cor,char *nmagic){
    FILE *fgiro;
    short int n[largura][altura];

    fgiro= fopen("fgiro.pgm", "w");
    if(fgiro == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fgiro, largura, altura, nmagic, cor);

    for(int i=0; i< altura; i++){
        for(int j=0; j<largura; j++){
            n[j][altura-i-1] = *(M+i*largura+j);
        }
    }
    for(int i=0; i< largura; i++){
        fprintf(fgiro, "\n");
        for(int j=0; j<altura; j++){
            fprintf(fgiro, "%d \t", n[i][j]);
        }
    }
    fclose(fgiro);
    return;
}

int main(){
    FILE *f1;
    int altura, largura, escurecer, corMax;
    char nmagic[4];

    f1= fopen("lena256.pgm", "r");
    if (f1 == NULL){
        printf("Arquivo Nao Aberto Corretamente...");
        exit(0);
    }
    leCabecalho(f1, &altura, &largura, &nmagic, &corMax);
    short int matrizPrincipal[altura][largura];
    leDados(f1, &matrizPrincipal, altura, largura);
    GirarParaDireita(&matrizPrincipal, altura, largura, corMax, &nmagic);

    return;
}
