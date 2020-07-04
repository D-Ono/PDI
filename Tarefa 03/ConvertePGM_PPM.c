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

void leDados (FILE *arq,unsigned char *M, int linha, int coluna){
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

void gravaDados(FILE *arq,short int *M, int linha, int coluna){

    for(int i=0; i<linha; i++){
        fprintf(arq, "\n");
        for (int j=0; j<coluna; j++){
            for(int k=0; k<3; k++)
                fprintf(arq, "%d \t", *(M+i*coluna*3+j*3+k));
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

void convertePGM_PPM_Arq(FILE *fRed,FILE *fGreen,FILE *fBlue, int altura, int largura, int corMax){  ///LENDO DIRETO DO ARQUIVO
    FILE *arq;
    int dado;
    char str[3] = "P3";

    arq= fopen("imagemRGB.ppm", "w");
    abreArquivo(arq);

    gravaCabecalho(arq, altura, largura, &str, corMax);

    while(!feof(fRed)){
        fscanf(fRed, "%d", &dado);
        fprintf(arq, "%d \n", dado);
        fscanf(fGreen, "%d", &dado);
        fprintf(arq, "%d \n", dado);
        fscanf(fBlue, "%d", &dado);
        fprintf(arq, "%d \n", dado);
    }

    fclose(arq);

    return;
}

void convertePGM_PPM_Mat(FILE *fRed,FILE *fGreen,FILE *fBlue, int altura, int largura, int corMax){  ///LENDO DIRETO DO MATRIZ
    FILE *arq;
    int dado;
    short int M[altura][largura][3];
    char str[3] = "P3";

    arq= fopen("imagemRGBMat.ppm", "w");
    abreArquivo(arq);

    gravaCabecalho(arq, altura, largura, &str, corMax);


    for(int i=0; i< altura; i++)
        for(int j= 0; j<largura; j++){
            fscanf(fRed, "%d", &dado);
            M[i][j][0]= dado;
            fscanf(fGreen, "%d", &dado);
            M[i][j][1]= dado;
            fscanf(fBlue, "%d", &dado);
            M[i][j][2]= dado;
    }
    gravaDados(arq, &M, altura, largura);

    fclose(arq);

    return;
}

int main(){
    FILE *fRed, *fGreen, *fBlue;
    int altura, largura, corMax, canal=3;
    char nmagic[4];

    fRed = fopen("ImagemR.pgm", "r");
    abreArquivo(fRed);
    fGreen = fopen("ImagemG.pgm", "r");
    abreArquivo(fGreen);
    fBlue = fopen("ImagemB.pgm", "r");
    abreArquivo(fBlue);


    leCabecalho(fRed, &altura, &largura, &nmagic, &corMax);
    leCabecalho(fGreen, &altura, &largura, &nmagic, &corMax);
    leCabecalho(fBlue, &altura, &largura, &nmagic, &corMax);

    convertePGM_PPM_Mat(fRed, fGreen, fBlue, altura, largura, corMax);

    printf("Programa Gerou o Arquivo Com Sucesso!!!");

    return;
}
