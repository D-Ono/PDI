#include <stdio.h>
#include <stdlib.h>

/*************************************************************/
/**                    GENERALIZAÇÕES                       **/
/*************************************************************/
void abreArquivo(FILE *arq){
    if(arq == NULL){
        printf("Arquivo Nao aberto corretamente");
        exit(0);
    }

    return;
}
/*************************************************************/
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
/*************************************************************/
void gravaCabecalho(FILE *arq, int altura, int largura, char *str, int corMax){
    fprintf(arq, "%s \n", str);     /// ARMAZENEI NUMERO MAGICO
    fprintf(arq, "%d \n", largura);
    fprintf(arq, "%d \n", altura);
    fprintf(arq, "%d \n", corMax);

    return;
}

/*************************************************************/
/**                     ATIVIDADE 03                        **/
/*************************************************************/
int arredonda(float valor){
    return (valor+0.5);
}
/*************************************************************/
void equalizaHistograma(FILE *f, int altura, int largura, char *str, int cor){
    FILE *saida;
    short int M[altura][largura];
    int vCinzas[cor+1], vNormal[cor+1], dado;
    float Probabilidades=0, vAcumulado[cor+1];

    for(int i=0; i< cor; i++){
        vCinzas[i]=0;
        vNormal[i]=0;
        vAcumulado[i]=0;
    }
    saida= fopen("saida.pgm", "w");
    abreArquivo(saida);
    gravaCabecalho(saida, altura, largura, str, cor);

    for(int i=0; i<altura; i++){
        for (int j=0; j<largura; j++){
            fscanf(f, "%d", &dado);
            M[i][j]= dado;
            vCinzas[dado]++;
        }
    }

    Probabilidades=(float)(vCinzas[0])/(largura*altura);
    vAcumulado[0]=Probabilidades;
    vNormal[0]=arredonda(vAcumulado[0]*cor);
    for(int i=1 ;i<=cor;i++){
        Probabilidades=(float)(vCinzas[i])/(largura*altura);
        vAcumulado[i]=(vAcumulado[i-1]+Probabilidades);
        vNormal[i]=arredonda(vAcumulado[i]*cor);
    }

    for(int i=0;i<altura;i++){
        for(int j=0;j<largura;j++){
            fprintf(saida, "%d \t", vNormal[M[i][j]]);
        }
    }
    fclose(saida);
}

/*************************************************************/
/**                          MAIN                           **/
/*************************************************************/
int main (){
    FILE *f;
    int altura, largura, corMax;
    char nmagic[4];

    f = fopen("quadrados.pgm", "r");

    abreArquivo(f);

    leCabecalho(f, &altura, &largura, &nmagic, &corMax);
    equalizaHistograma(f, altura, largura, &nmagic, corMax);

    printf("Imagem Gerada com Sucesso!!! \n\n");
    return;
}
