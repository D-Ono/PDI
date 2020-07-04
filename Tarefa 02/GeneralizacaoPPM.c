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

void gravaCabecalho(FILE *arq, int altura, int largura, char *str, int corMax){
    fprintf(arq, "%s \n", str);     /// ARMAZENEI NUMERO MAGICO
    fprintf(arq, "%d \n", largura);
    fprintf(arq, "%d \n", altura);
    fprintf(arq, "%d \n", corMax);

    return;
}

void escureceFoto(unsigned char *M, int altura,int largura,int cor,char *nmagic){
    FILE *fescuro;
    int menos, escurecer;

    fescuro= fopen("fescuro.ppm", "w");
    if(fescuro == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fescuro, altura, largura, nmagic, cor);
    printf("Quanto maior o valor escolhido, mais escuro a foto ficara. \n")
    printf("Quanto escurecer?[0,%d]: ", cor);
    scanf("%d", &escurecer);

    for(int i=0; i<altura; i++){
        fprintf(fescuro, "\n");
        for (int j=0; j<largura; j++){
            for(int k =0; k<3; k++){
                menos = *(M+i*largura*3+j*3+k) - escurecer;
                if (menos < 0)
                    menos = 0;
                fprintf(fescuro, "%d \t", menos);
            }
        }
    }
    system("cls");
    fclose(fescuro);
    return;
}

void clareiaFoto(unsigned char *M, int altura,int largura,int cor,char *nmagic){
    int mais, clarear;
    FILE *fclaro;

    fclaro= fopen("fclaro.ppm", "w");
    if(fclaro == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }
    gravaCabecalho(fclaro, altura, largura, nmagic, cor);
    printf("Quanto maior o valor escolhido, mais claro a foto ficara. \n")
    printf("Quanto Clarear?[0,%d]: ", cor);
    scanf("%d", &clarear);

    for(int i=0; i<altura; i++){
        fprintf(fclaro, "\n");
        for (int j=0; j<largura; j++){
            for(int k =0; k<3; k++){
                mais = *(M+i*largura*3+j*3+k) + clarear;
                if (mais > cor)
                    mais = cor;
                fprintf(fclaro, "%d \t", mais);
            }
        }
    }
    fclose(fclaro);
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

    unsigned char matrizPrincipal[altura][largura][canal];
    leDados(f1, &matrizPrincipal, altura, largura);
    escureceFoto(&matrizPrincipal, altura, largura, corMax, &nmagic);
    clareiaFoto(&matrizPrincipal, altura, largura, corMax, &nmagic);
    return;
}
