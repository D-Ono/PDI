#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/*************************************************************/
/**                    GENERALIZAÇÕES                       **/
/*************************************************************/
void abreArquivo(FILE *arq){
    if(arq == NULL){
        printf("Arquivo Nao Encontrado!");
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
    fprintf(arq, "%d \t", largura);
    fprintf(arq, "%d \n", altura);
    fprintf(arq, "%d \n", corMax);

    return;
}
/*************************************************************/
void copiaDadosArqMatriz(FILE *f, short int *M, int alt, int lar){
    int dado;

    for(int i=0; i<alt; i++){
        for (int j=0; j<lar; j++){
            fscanf(f, "%d", &dado);
            *(M+i*lar+j)= dado;
        }
    }
}
/*************************************************************/
void gravaDados(FILE *arq,short int *M, int linha, int coluna){

    for(int i=0; i<linha; i++){
        fprintf(arq, "\n");
        for (int j=0; j<coluna; j++){
            fprintf(arq, "%d \t", *(M+i*coluna+j));
        }
    }
    return;
}


/*************************************************************/
/**                     ATIVIDADE 03                        **/
/*************************************************************/
void FatiamentoNiveisIntervalo(FILE *f, int alt, int lar, char *str, int cormax){
    FILE *fniveis;
    int dado, intervaloInf, intervaloSup, valor;

    fniveis = fopen("Niveis.pgm", "w");
    abreArquivo(fniveis);
    gravaCabecalho(fniveis, alt, lar, str, cormax);

    printf("\n\t\t Fatiamento de Niveis Alterando só dentro do Intervalo \n\n ");
    printf("Novo Valor no Intervalo será: ");
    scanf("%d", &valor);
    printf("\n Insira o Valor Inferior do Intervalo: ");
    scanf("%d", &intervaloInf);
    printf("\n Insira o Valor Superior do Intervalo: ");
    scanf("%d", &intervaloSup);

    while(!(feof(f))){
        fscanf(f, "%d", &dado);
        if((dado>=intervaloInf) && (dado<=intervaloSup)){
            fprintf(fniveis, "%d \t", valor);
            continue;
        }
        fprintf(fniveis, "%d \t", dado);
    }
    fclose(fniveis);

    return;
}
/*************************************************************/
void FatiamentoNiveisBinario(FILE *f, int alt, int lar, char *str, int cormax){
    FILE *fniveis;
    int dado, valorDentro, valorFora, intervaloInf, intervaloSup;

    fniveis = fopen("NiveisBinario.pgm", "w");
    abreArquivo(fniveis);
    gravaCabecalho(fniveis, alt, lar, str, cormax);

    printf("\n\t\t Fatiamento de Niveis Binário \n\n ");
    printf("Novo Valor dentro do Intervalo será: ");
    scanf("%d", &valorDentro);
    printf("\n Novo Valor fora do Intervalo será: ");
    scanf("%d", &valorFora);
    printf("\n Insira o Valor Inferior do Intervalo: ");
    scanf("%d", &intervaloInf);
    printf("\n Insira o Valor Superior do Intervalo: ");
    scanf("%d", &intervaloSup);

    while(!(feof(f))){
        fscanf(f, "%d", &dado);
        if((dado>=intervaloInf) && (dado<=intervaloSup)){
            fprintf(fniveis, "%d \t", valorDentro);
        }
        else{
            fprintf(fniveis, "%d \t", valorFora);
        }
    }
    fclose(fniveis);

    return;
}
/*************************************************************/
void transformacaoGama_Arq(FILE *f, int alt, int lar, char *str, int cormax){
    FILE *gama;
    float dado, gam, resul;
    int c;

    gama = fopen("gama.pgm", "w");
    abreArquivo(gama);
    gravaCabecalho(gama, alt, lar, str, cormax);

    printf("\n\t\t Transformação de Potencia (Gama) \n\n ");
    printf("\t\t Formula: s = C * r ^ y \n\n");
    printf("\n Valor de C será: ");
    scanf("%d", &c);
    printf(" Valor de Gama será[Use Virgula para casas decimais]: ");
    scanf("%f", &gam);

    while(!feof(f)){
        fscanf(f, "%f", &dado);
        dado=dado/cormax;
        resul= c*(pow(dado, gam));
        resul= resul*cormax;
        fprintf(gama, "%d \t",(int)resul);
    }
    fclose(gama);

    return;
}
/*************************************************************/
void flipHorizontal_Arq(FILE *f, int alt, int lar, char *str, int cormax){  /// FLIP LENDO OS PIXELS DO ARQUIVO
    FILE *fflip;
    short int M[alt][lar];
    int dado;

    fflip= fopen("flipHorizontal.pgm", "w");
    abreArquivo(fflip);
    gravaCabecalho(fflip, alt, lar, str, cormax);

    for(int i=0; i<alt; i++){
        for(int j=lar-1; j>=0;j--){
            fscanf(f, "%d", &dado);
            M[i][j]= dado;
        }
    }
    gravaDados(fflip, &M, alt, lar);
    fclose(fflip);
    return;
}
/*************************************************************/
void flipHorizontal_Matriz(short int *A, int alt, int lar, char *str, int cormax){   /// FLIP LENDO OS PIXELS DA MATRIZ
    FILE *fflip;
    short int M[alt][lar];
    int k=0;

    fflip= fopen("flipHorizontal.pgm", "w");
    abreArquivo(fflip);
    gravaCabecalho(fflip, alt, lar, str, cormax);

    for(int i=0; i<alt; i++){
        k=0;
        for(int j=lar-1; j>=0;j--){
            M[i][j]= *(A+i*lar+k);
            k++;
        }
    }
    gravaDados(fflip, &M, alt, lar);

    return;
}
/*************************************************************/     ///TRANSFORMAÇÃO LOG NAO UTILIZADA
void transformacaoLog(FILE *f, int alt, int lar, char *str, int cormax){
    FILE *flog;
    float dado;
    float resul;
    int c=1;

    flog = fopen("Logaritmica.pgm", "w");
    abreArquivo(flog);
    gravaCabecalho(flog, alt, lar, str, cormax);

    while(!feof(f)){
        fscanf(f, "%f", &dado);
        dado=dado/cormax;
        resul = c*log(1+dado);
        resul = resul*cormax;
        fprintf(flog, "%d \t",(int)resul);
    }
    fclose(flog);

    return;
}

/*************************************************************/
/**                          MENU                           **/
/*************************************************************/
void menu(){
    FILE *f;
    int altura, largura, corMax, op, cont;
    char nmagic[4], img[11];
    setlocale(LC_ALL, "Portuguese");

    do{
        do{
            printf(" \n\n\t\t Bem Vindo a Atividade 03_PDI  \n\n\n");
            printf(" 01 - Fatiamento de Niveis Alterando só no Intervalo\n");
            printf(" 02 - Fatiamento de Niveis Binário \n");
            printf(" 03 - Transformação Gama \n" );
            printf(" 04 - Flip Horizontal \n\n");
            printf(" Qual Operação Deseja Realizar? ");
            scanf("%d", &op);
            system("cls");
        }while((op<1) || (op>4));

        do{
            printf(" \n\n\t\t Bem Vindo a Atividade 03_PDI \n\n");
            printf(" Escolha uma imagem para aplicar a operação: \n");
            printf(" 'aerial.pgm'  'Angio2.pgm'  'barbar.pgm'  'Casal4.pgm'  'spine5.pgm' \n\n");
            printf(" Digite o nome da Imagem que deseja aplicar a Operação: ");
            scanf("%s", &img);
            system("cls");
        }while((op<1) || (op>4));

        f=fopen(img,"r");
        abreArquivo(f);
        leCabecalho(f, &altura, &largura, &nmagic, &corMax);

        switch(op){
            case 1:
                FatiamentoNiveisIntervalo(f, altura, largura, &nmagic, corMax);
                printf("\n\n\t Arquivo 'Niveis.pgm' foi Gerado com Sucesso \n\n");
                system("pause");
                break;
            case 2:
                FatiamentoNiveisBinario(f, altura, largura, &nmagic, corMax);
                printf("\n\n\t Arquivo 'NiveisBinario.pgm' foi Gerado com Sucesso \n\n");
                system("pause");
                break;
            case 3:
                transformacaoGama_Arq(f, altura, largura, &nmagic, corMax);
                printf("\n\n\t Arquivo 'gama.pgm' foi Gerado Com Sucesso \n\n");
                system("pause");
                break;
            case 4:
                flipHorizontal_Arq(f, altura, largura, &nmagic, corMax);
                printf("\n\n\t Arquivo 'flipHorizontal.pgm' foi Gerado com Sucesso \n\n");
                system("pause");
                break;
        }
        fclose(f);
        system("cls");
        do{
            printf("\n\n\t Você Deseja Realizar Outra Operação?[1]Sim [0]Não: ");
            scanf("%d", &cont);
        }while(cont!=1 && cont!=0);
    }while(cont==1);

    printf(" \n\n\t Volte Sempre!!! \n\n ");

    return;
}
/*************************************************************/
/**                          MAIN                           **/
/*************************************************************/
int main (){

    menu();
return;
}
/*************************************************************/
