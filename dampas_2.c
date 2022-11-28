#include <stdio.h>
#include <stdlib.h>

int num_pecas_cima=6, num_pecas_baixo=6; 
int main(){
    void printa_tab (int tab[6][6]);
    void trat_comando (char com[10]);
    void movimenta (char com[10], int tab[6][6]);
    int verifica();
    
    int tabuleiro[6][6];
    char comando[10];
       
    //0->-; 1->#; 2->o; 3->X(dama de #); 4->O(dama de o)
    tabuleiro[0][1] = tabuleiro[0][3] = tabuleiro[0][5] = 1; //preenche o tabuleiro com as peças
    tabuleiro[1][0] = tabuleiro[1][2] = tabuleiro[1][4] = 1;
    tabuleiro[4][1] = tabuleiro[4][3] = tabuleiro[4][5] = 2;
    tabuleiro[5][0] = tabuleiro[5][2] = tabuleiro[5][4] = 2;
    
    for (int i=0;i<6;i++){ //preenche o resto do tabuleiro com espaços vazios
        for (int k=0;k<6;k++){
            if (tabuleiro[i][k]!=1 && tabuleiro[i][k]!=2){
                tabuleiro[i][k]=0;
            }
        }
    }
    printa_tab(tabuleiro);

    while(1){
        fgets(comando , 10 , stdin);
        trat_comando(comando);
        printf("\npassou do tratamento\n");
        printf("%s",comando);
        movimenta(comando, tabuleiro);
        printf("\npassou do movimento\n");
        printa_tab(tabuleiro);
        printf("\npassou do printa\n");
    }

    return 0;
}
    void printa_tab (int tab[6][6]){
        for (int i=0;i<6;i++){ //printa tabuleiro
            for (int k=0;k<6;k++){
                if (tab[i][k]==0)
                    printf("-");
                else if (tab[i][k]==1)
                    printf("#");
                else if (tab[i][k]==2)
                    printf("o");
                else
                    printf("erro\n");
            }
            printf("\n");
        }
    }
    
    void trat_comando (char com[10]){ 
        switch (com[0]){//transforma o comando de caracter em inteiro
        case 'a':
            com[0]='0';
            break;
        case 'b':
            com[0]='1';
            break;
        case 'c':
            com[0]='2';
            break;
        case 'd':
            com[0]='3';
            break;
        case 'e':
            com[0]='4';
            break;
        case 'f':
            com[0]='5';
            break;
        default:
            com[0]='6'; //se colocar mais ou menos colunas que o permitido
            printf("Movimento invalido colunas\n");
            break;
        }

        switch (com[1]){ //organiza a ordem das linhas para começarem de cima para baixo
        case '1':
            com[1]='5';
            break;
        case '2':
            com[1]='4';
            break;
        case '3':
            com[1]='3';
            break;
        case '4':
            com[1]='2';
            break;
        case '5':
            com[1]='1';
            break;
        case '6':
            com[1]='0';
            break;   
        default:
            com[1]='6'; //se colocar mais ou menos linhas que o permitido
            printf("Movimento invalido linhas\n");
            break;
        }
    }

    int verifica(char com[10], int tab[6][6]){ //verifica se o movimento é valido(1: valido; 0: invalido)
        int print=0;
        int captura=0;
        if (com[0]=='6') //nº de colunas invalido
            print++;
        if (com[1]=='6') //nº de linha invalido
            print++;
        if (com[3]!='E' && com[3]!='D') //direção invalida
            print++;
        /*if (com[1]=='0' && com[5]=='F') //O na primeira linha e subindo
            print++;
        if (com[1]=='5' && com[5]=='F') //X na ultima linha e descendo
            print++;
        if ((com[0]=='0' && com[3]='E') || (com[0]=='5' && com[3]='D'))//saindo do tabuleiro pelas laterais
            print++;*/
        if (tab[com[1]-48][com[0]-48]==0) //local selecionado sem peças
            print++;

        //testar depois as verificações abaixo:
        /*if(com[3]='E' && (tab[com[1]][com[0]]==1 || tab[com[1]][com[0]]==3) && com[5]!='T'){//local ja tem uma peça aliada
            if (tab[com[1]-1][com[0]+1]==1 || tab[com[1]-1][com[0]+1]==3)
                print++;
            if (tab[com[1]-1][com[0]+1]==2 || tab[com[1]-1][com[0]+1]==4)
                if (tab[][]==0)
        }else if (com[3]='E' && (tab[com[1]][com[0]]==2 || tab[com[1]][com[0]]==4) && com[5]!='T'){
            if (tab[com[1]-1][com[0]+1]==2 || tab[com[1]-1][com[0]-1]==4)
                print++;
        }else if (com[3]='D' && (tab[com[1]][com[0]]==1 || tab[com[1]][com[0]]==3) && com[5]!='T')
            if (tab[com[1]+1][com[0]+1]==1 || tab[com[1]+1][com[0]+1]==3)
                print++;
        else if (com[3]='D' && (tab[com[1]][com[0]]==2 || tab[com[1]][com[0]]==4) && com[5]!='T'){
            if (tab[com[1]-1][com[0]+1]==2 || tab[com[1]-1][com[0]+1]==4)
                print++;
            }*/
        //O "-48" é para converter o valor na tabela ascii para numero inteiro
        if (tab[com[1]-48][com[0]-48]==1){ //peças #
            if (com[3]=='E'){
                if (tab[com[1]-48+1][com[0]-48-1]==1 || tab[com[1]-48+1][com[0]-48-1]==3) //posição tem uma peça amiga
                    print++; 
                else if (tab[com[1]-48+1][com[0]-48-1]==2 || tab[com[1]-48+1][com[0]-48-1]==4) //posição tem uma peça inimiga
                    captura--;
            }else if(com[3]=='D'){
                if (tab[com[1]-48+1][com[0]-48+1]==1 || tab[com[1]-48+1][com[0]-48+1]==3) //posição tem uma peça amiga
                    print++;
                else if (tab[com[1]-48+1][com[0]-48+1]==2 || tab[com[1]-48+1][com[0]-48+1]==4) //posição tem uma peça inimiga
                    captura--;
            }
        }else if(tab[com[1]-48][com[0]-48]==3){ //peças X
            if (com[5]=='F'){
                if (com[3]=='E'){
                    if (tab[com[1]-48+1][com[0]-48-1]==1 || tab[com[1]-48+1][com[0]-48-1]==3) //posição tem uma peça amiga
                        print++; 
                    else if (tab[com[1]-48+1][com[0]-48-1]==2 || tab[com[1]-48+1][com[0]-48-1]==4) //posição tem uma peça inimiga
                        captura--;
                }else if(com[3]=='D'){
                    if (tab[com[1]-48+1][com[0]-48+1]==1 || tab[com[1]-48+1][com[0]-48+1]==3) //posição tem uma peça amiga
                        print++;
                    else if (tab[com[1]-48+1][com[0]-48+1]==2 || tab[com[1]-48+1][com[0]-48+1]==4) //posição tem uma peça inimiga
                        captura;
                }
            } else if(com[5]=='T'){
                if (com[3]=='E'){
                    if (tab[com[1]-48-1][com[0]-48-1]==1 || tab[com[1]-48-1][com[0]-48-1]==3) //posição tem uma peça amiga
                        print++; 
                    else if (tab[com[1]-48-1][com[0]-48-1]==2 || tab[com[1]-48-1][com[0]-48-1]==4) //posição tem uma peça inimiga
                        captura--;
                }else if(com[3]=='D'){
                    if (tab[com[1]-48-1][com[0]-48+1]==1 || tab[com[1]-48-1][com[0]-48+1]==3) //posição tem uma peça amiga
                        print++;
                    else if (tab[com[1]-48-1][com[0]-48+1]==2 || tab[com[1]-48-1][com[0]-48+1]==4) //posição tem uma peça inimiga
                        captura--;
                }
            }
        }else if(tab[com[1]-48][com[0]-48]==2){ //peças o
        }else if(tab[com[1]-48][com[0]-48]==4){ //peças O
        }

        if (print==0){
            if (captura<0)
                return -1; //movimento valido de captura
            else
                return 1; //movimento valido sem captura
        }else if(print!=0)
            return 0; //movimento invalido

    }

    void movimenta (char com[10], int tab[6][6]){
        int tipo_peca = tab[com[1]-48][com[0]-48];
        if (com[3]=='E'){
            if (verifica(com,tab)>0){ //movimento normal sem captura
                tab[com[1]][com[0]] = 0;
                if (tipo_peca==1 || (tipo_peca==3 && com[5]=='F') || (tipo_peca==4 && com[5]=='T')) //Para baixo e esquerda
                    tab[com[1]-48+1][com[0]-48-1] = tipo_peca;
                else if(tipo_peca==2 || (tipo_peca==3 && com[5]=='T') || (tipo_peca==4 && com[5]=='F')) //Para cima e esquerda
                    tab[com[1]-48-1][com[0]-48-1] = tipo_peca;
            }else if(verifica(com,tab)<0){ //movimento de captura
                tab[com[1]-48][com[0]-48] = 0;
                if (tipo_peca==1 || (tipo_peca==3 && com[5]=='F') || (tipo_peca==4 && com[5]=='T')){ //Captura para baixo e esquerda
                    tab[com[1]-48+1][com[0]-48-1] = 0;
                    tab[com[1]-48+2][com[0]-48-2] = tipo_peca;
                    if (tipo_peca==1 || tipo_peca==3)
                        num_pecas_baixo--;
                    else
                        num_pecas_cima--;
                }else if(tipo_peca==2 || (tipo_peca==3 && com[5]=='T') || (tipo_peca==4 && com[5]=='F')){ //Captura para cima e esquerda
                    tab[com[1]-48-1][com[0]-48-1] = 0;
                    tab[com[1]-48-2][com[0]-48-2] = tipo_peca;
                    if (tipo_peca==3)
                        num_pecas_baixo--;
                    else
                        num_pecas_cima--;
                }
            }else
                printf("MOVIMENTO INVALIDO\n");
        }else if (com[3]=='D'){
            if (verifica(com,tab)>0){ //movimento normal sem captura
                tab[com[1]][com[0]] = 0;
                if (tipo_peca==1 || (tipo_peca==3 && com[5]=='F') || (tipo_peca==4 && com[5]=='T')) //Para baixo e direita
                    tab[com[1]-48+1][com[0]-48+1] = tipo_peca;
                else if(tipo_peca==2 || (tipo_peca==3 && com[5]=='T') || (tipo_peca==4 && com[5]=='F')) //Para cima e direita
                    tab[com[1]-48-1][com[0]-48+1] = tipo_peca;
            }else if(verifica(com,tab)<0){ //movimento de captura
                tab[com[1]-48][com[0]-48] = 0;
                if (tipo_peca==1 || (tipo_peca==3 && com[5]=='F') || (tipo_peca==4 && com[5]=='T')){ //Captura para baixo e direita
                    tab[com[1]-48+1][com[0]-48+1] = 0;
                    tab[com[1]-48+2][com[0]-48+2] = tipo_peca;
                    if (tipo_peca==1 || tipo_peca==3)
                        num_pecas_baixo--;
                    else
                        num_pecas_cima--;
                }else if(tipo_peca==2 || (tipo_peca==3 && com[5]=='T') || (tipo_peca==4 && com[5]=='F')){ //Captura para cima e direita
                    tab[com[1]-48-1][com[0]-48+1] = 0;
                    tab[com[1]-48-2][com[0]-48+2] = tipo_peca;
                    if (tipo_peca==3)
                        num_pecas_baixo--;
                    else
                        num_pecas_cima--;
                }
            }else 
                printf("MOVIMENTO INVALIDO\n");
        }
    }
