/*=================================================
NOME DO PROGRAMA: Alinhamento de Sequ�ncias
AUTOR: Amilton Fontoura de Camargo Junior
DATA: 08/10/2011
DISCIPLINA: T�cnicas de Programa��o - IF62A
TURMA: C21
OBJETIVO: Realizar o melhor alinhamento de duas sequ�ncias
DADOS DE ENTRADA: Duas sequ�ncias
DADOS DE SAIDA: Score e melhor alinhamento
OBS: Quest�o 1 - APS 2
=================================================*/

#include <stdio.h> // Cabe�alho com fun��es padr�es I/O

int main() { // Fun��o Principal

    //////////////////////////
    /// In�cio do Programa ///
    //////////////////////////

    //* Vari�veis *//

    int maximo=100, i=1, j, k, m=1, n, total1, total2, a, b, calculos[maximo][maximo],
    acima, esquerda, diagonal, score, tipo, match=1, mismatch=-1, gap=-2, resultado,
    menor, grande[1][3], p1=0, p2=0, p11=0, p22=0, t1=1, maiores[maximo], retirar=2,
    gap1=0, gap2=0, matches=0, mismatches=0, gaps=0;
    char letra, sequencia1[maximo], sequencia2[maximo], valor1, valor2, resposta,
    fita1[maximo], fita2[maximo], fita3[maximo];

    ///////////////
    /// Fun��es ///
    ///////////////

    // Fun��o que retorna o maior valor inteiro
    int maior(num1,num2,num3) {
        // Vari�veis auxiliares
        int ver1, ver2;
        // Obt�m o maior entre num1 e num2
        if (num1>num2) {
            ver1 = num1;
        } else {
            ver1 = num2;
        }
        ver2 = num3;
        // Verifica quais dos n�meros obtidos � maior e retorna na fun��o
        if (ver1>ver2) {
            return ver1;
        } else {
            return ver2;
        }
    }

    // Fun��o que retorna o maior valor inteiro de acordo com o alinhamento local
    int maior2(num1,num2,num3) {
        // Vari�veis auxiliares
        int ver1, ver2, num4=0;
        // Obt�m o maior entre num1 e num2
        if (num1>num2) {
            ver1 = num1;
        } else {
            ver1 = num2;
        }
        // Obt�m o maior entre num3 e num4
        if (num3>num4) {
            ver2 = num3;
        } else {
            ver2 = num4;
        }
        // Verifica quais dos n�meros obtidos � maior e retorna na fun��o
        if (ver1>ver2) {
            return ver1;
        } else {
            return ver2;
        }
    }

    // Fun��o que verifica e salva os valores na fita resultante
    void salvar(p11,p22,gap1,gap2) {
        // Match
        if (sequencia1[p11]==sequencia2[p22] && sequencia1[p11]!=' ') {
            fita1[t1] = sequencia1[p11];
            fita2[t1] = sequencia2[p22];
            fita3[t1] = '|';
            matches++;
        // Gap nas duas sequ�ncias
        } else if (gap1==1 && gap2==1) {
            fita1[t1] = '-';
            fita2[t1] = '-';
            fita3[t1] = ' ';
            p1++;
            p2++;
            gaps++;
        // Gap na sequ�ncia 1
        } else if (gap1==1 && gap2==0) {
            fita1[t1] = '-';
            fita2[t1] = sequencia2[p22];
            fita3[t1] = ' ';
            p1++;
            gaps++;
        // Gap na sequ�ncia 2
        } else if (gap2==1 && gap1==0) {
            fita1[t1] = sequencia1[p11];
            fita2[t1] = '-';
            fita3[t1] = ' ';
            p2++;
            gaps++;
        // Mismatch
        } else {
            fita1[t1] = sequencia1[p11];
            fita2[t1] = sequencia2[p22];
            fita3[t1] = ' ';
            mismatches++;
        }
        // Soma na vari�vel auxiliar
        t1++;
    }

    // Fun��o que retorna a pontua��o na posi��o atual
    int p(n1,n2) {
        // Match
        if (n1==n2) {
            return match;
        // Mismatch
        } else {
            return mismatch;
        }
    }

    /////////////////
    /// Cabe�alho ///
    /////////////////

    printf("\n\n - ALINHAMENTO DE SEQUENCIAS -\n\n");

    // Recebe a primeira sequ�ncia
    printf(" -> Digite abaixo a primeira sequencia: (ao terminar tecle Enter)\n\n ");
    i = 1;
    while(letra!='\n') { // Enquanto o usu�rio n�o digitar Enter, recebe os valores
      letra = getchar(); // Obt�m os valores digitados
      sequencia1[i] = toupper(letra); // Transforma as letras em mai�sculo e salva
      i++;
    }
    printf("\n");
    sequencia1[--i] = '\0'; // Fecha a string
    total1 = --i; // Salva o total de caracteres
    letra = '0'; // Reseta o valor da vari�vel auxiliar

    // Recebe a segunda sequ�ncia
    printf(" -> Digite abaixo a segunda sequencia: (ao terminar tecle Enter)\n\n ");
    i = 1;
    while(letra!='\n') { // Enquanto o usu�rio n�o digitar Enter, recebe os valores
      letra = getchar(); // Obt�m os valores digitados
      sequencia2[i++] = toupper(letra); // Transforma as letras em mai�sculo e salva
    }
    printf("\n");
    sequencia2[--i] = '\0'; // Fecha a string
    total2 = --i; // Salva o total de caracteres

    // Recebe (ou n�o) os valores para Match, Mismatch e Gap
    printf(" -> Deseja definir os valores para Match, Mismatch e Gap?\n(s/n) R= ");
    scanf("%c",&resposta);
    if (resposta=='s') {
        printf(" - Match: ");
        scanf("%d",&match);
        printf(" - Mismatch: ");
        scanf("%d",&mismatch);
        printf(" - Gap: ");
        scanf("%d",&gap);
        printf(" - Sequencia padrao - Razao positiva da progressao negativa: ");
        scanf("%d",&retirar);
    }
    printf("\n");

    // Questiona ao usu�rio que tipo de alinhamento deseja utilizar
    printf(" -> Que tipo de alinhamento deve ser utilizado?\n\n");
    printf(" 1 - Global\n");
    printf(" 2 - Local\n\n");
    printf(" Opcao desejada: R= ");
    scanf("%d",&tipo);
    printf("\n");

    ////////////////////////////////////////
    // C�lculos para o Alinhamento Global //
    ////////////////////////////////////////

    if (tipo==1) {

        // Reseta as vari�veis para utiliza��o
        m = 1;
        a = -(retirar);
        b = -(retirar);

        // Imprime a sequ�ncia de cima
        for (i=1;i<total2+3;i++) {
            for (j=1;j<total1+3;j++) {
                // Ponto nulo
                if (i==1 && j==1) {
                    printf("  ");
                // Gap
                } else if ((i==1 && j==2) || (i==2 && j==1)) {
                    printf("- ");
                // Sequ�ncia de cima
                } else if (i==1) {
                    printf("%c ",sequencia1[i,j-2]);
                // Sequ�ncia do lado
                } else if (j==1) {
                    printf("%c ",sequencia2[j,i-2]);
                // Valor nulo na posi��o (2,2)
                } else if (i==2 && j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("0");
                // Valores padr�es da sequ�ncia de cima
                } else if (i==2) {
                    calculos[i-1][j-1] = a;
                    a -= retirar;
                    printf(" %d",calculos[i-1][j-1]);
                // Valores padr�es da sequ�ncia do lado
                } else if (j==2) {
                    calculos[i-1][j-1] = b;
                    b -= retirar;
                    printf("%d ",calculos[i-1][j-1]);
                // Caso geral
                } else {
                    // Define os valores ao redor da posi��o atual
                    valor1 = sequencia1[j-2];
                    valor2 = sequencia2[i-2];
                    // Valor acimacima
                    acima = (calculos[i-2][j-1])+gap;
                    // Valor � esquerda
                    esquerda = (calculos[i-1][j-2])+gap;
                    // Calcula o valor da diagonal
                    diagonal = (calculos[i-2][j-2])+p(valor1,valor2);
                    // Obt�m o maior valor entre os tr�s n�meros e atribui � posi��o atual
                    calculos[i-1][j-1] = maior(acima,esquerda,diagonal);
                    // Imprime o resultado
                    printf("%d ",calculos[i-1][j-1]);
                    // Salva o score, que � a �ltima posi��o da matriz
                    score = calculos[i-1][j-1];
                }
            }
            printf("\n\n");
        }

        // Define as posi��es zero das sequ�ncias
        sequencia1[0] = ' ';
        sequencia2[0] = ' ';

        // Detecta o menor valor da fun��o e salva numa vari�vel auxiliar
        for (i=1;i<total2+2;i++) {
            for (j=1;j<total1+2;j++) {
                if (calculos[i][j]<menor) {
                    menor = calculos[i][j];
                }
            }
        }

        // Percorre o vetor na diagonal para verificar o score e melhor alinhamento
        i = total1+1;
        k = total2+1;
        // Determina os valores das posi��es x e y
        p1 = i;
        p2 = k;
        // Prossegue com os c�lculos
        for (j=i;j>0;j--) {
            // Vari�veis de aux�lio
            gap1 = 0;
            gap2 = 0;
            // Salva as poci��es das letras
            p11 = p1-1;
            p22 = p2-1;
            // Salva a posi��o diagonal
            n = calculos[p1][p2];
            // Verifica se a posi��o de cima � maior
            if (calculos[p11][p2]>n) {
                gap2 = 1;
            // Verifica se a posi��o da esquerda � maior
            } else if (calculos[p1][p22]>n) {
                gap1 = 1;
            }
            // Salva e verifica na fita resultante
            salvar(p11,p22,gap1,gap2);
            // Decrementa nas vari�veis auxiliares
            p1--;
            p2--;
        }

        // Imprime o score
        printf("\n\n -> Score do alinhamento: %d\n\n",score);

        // Imprime a fita resultado do alinhamento
        printf("\n -> Melhor alinhamento:\n\n");
        // Repete e imprime o resultado
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita1[i]);
        }
        printf("\n");
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita3[i]);
        }
        printf("\n");
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita2[i]);
        }
        printf("\n\n");

    ///////////////////////////////////////
    // C�lculos para o Alinhamento Local //
    ///////////////////////////////////////

    } else if (tipo==2) {

        // Reseta a vari�vel para utiliza��o
        m = 1;

        // Imprime a sequ�ncia de cima
        for (i=1;i<total2+3;i++) {
            for (j=1;j<total1+3;j++) {
                // Ponto nulo
                if (i==1 && j==1) {
                    printf("  ");
                // Gap
                } else if ((i==1 && j==2) || (i==2 && j==1)) {
                    printf("- ");
                // Sequ�ncia de cima
                } else if (i==1) {
                    printf("%c ",sequencia1[i,j-2]);
                // Sequ�ncia do lado
                } else if (j==1) {
                    printf("%c ",sequencia2[j,i-2]);
                // Valor nulo na posi��o (2,2)
                } else if (i==2 && j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("0");
                // Valores padr�es da sequ�ncia de cima
                } else if (i==2) {
                    calculos[i-1][j-1] = 0;
                    printf(" %d",calculos[i-1][j-1]);
                // Valores padr�es da sequ�ncia do lado
                } else if (j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("%d ",calculos[i-1][j-1]);
                // Caso geral
                } else {
                    // Calcula o valor da posi��o acima
                    acima = (calculos[i-2][j-1])+gap;
                    // Calcula o valor da posi��o � esquerda
                    esquerda = (calculos[i-1][j-2])+gap;
                    // Obt�m os caracteres correspondentes em cada sequ�ncia
                    valor1 = sequencia1[j-2];
                    valor2 = sequencia2[i-2];
                    // Calcula o valor da posi��o diagonal
                    diagonal = (calculos[i-2][j-2])+p(valor1,valor2);
                    // Obt�m o maior valor entre os tr�s n�meros e atribui � posi��o atual
                    calculos[i-1][j-1] = maior2(acima,esquerda,diagonal);
                    // Imprime o resultado
                    printf("%d ",calculos[i-1][j-1]);
                }
            }
            printf("\n\n");
        }

        // Define as posi��es zero das sequ�ncias
        sequencia1[0] = ' ';
        sequencia2[0] = ' ';

        // Detecta o menor valor da fun��o e salva numa vari�vel auxiliar
        for (i=1;i<total2+2;i++) {
            for (j=1;j<total1+2;j++) {
                if (calculos[i][j]<menor) {
                    menor = calculos[i][j];
                }
            }
        }

        // Detecta o maior valor da fun��o e salva numa vari�vel auxiliar
        grande[1][1] = menor;
        for (i=1;i<total2+2;i++) {
            for (j=1;j<total1+2;j++) {
                if (calculos[i][j]>grande[1][1]) {
                    // Salva o valor num�rico
                    grande[1][1] = calculos[i][j];
                    // Salva a posi��o x
                    grande[1][2] = j;
                    // Salva a posi��o y
                    grande[1][3] = i;
                }
            }
        }

        // Percorre o vetor na diagonal para verificar o score e melhor alinhamento
        k = grande[1][3];
        i = grande[1][2];
        // Determina os valores das posi��es x e y
        p1 = k;
        p2 = i;
        // Salva o score
        score = calculos[k][i];
        // Prossegue com os c�lculos
        for (j=k;j>0;j--) {
            // Vari�veis de aux�lio
            gap1 = 0;
            gap2 = 0;
            // Salva as posi��es das letras
            p11 = p2-1;
            p22 = p1-1;
            // Salva a posi��o diagonal
            n = calculos[p1][p2];
            // Verifica se a posi��o de cima � maior
            if (calculos[p11][p2]>n) {
                gap2 = 1;
            // Verifica se a posi��o da esquerda � maior
            } else if (calculos[p1][p22]>n) {
                gap1 = 1;
            }
            // Salva e verifica na fita resultante
            salvar(p11,p22,gap1,gap2);
            // Decrementa nas vari�veis auxiliares
            p1--;
            p2--;
        }

        // Imprime o score
        printf("\n\n -> Score do alinhamento: %d\n\n",score);

        // Imprime a fita resultado do alinhamento
        printf("\n -> Melhor alinhamento:\n\n");
        // Repete e imprime o resultado
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita1[i]);
        }
        printf("\n");
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita3[i]);
        }
        printf("\n");
        for (i=t1+1;i>0;i--) {
            printf("%c ",fita2[i]);
        }
        printf("\n\n");

    // Op��o inv�lida digitada, finaliza a execu��o
    } else {
        printf("\n -> OPCAO INVALIDA!\n\n");
    }

    ///////////////////////
    /// Fim do Programa ///
    ///////////////////////

    return 0;
}
