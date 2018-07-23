/*=================================================
NOME DO PROGRAMA: Alinhamento de Sequências
AUTOR: Amilton Fontoura de Camargo Junior
DATA: 08/10/2011
DISCIPLINA: Técnicas de Programação - IF62A
TURMA: C21
OBJETIVO: Realizar o melhor alinhamento de duas sequências
DADOS DE ENTRADA: Duas sequências
DADOS DE SAIDA: Score e melhor alinhamento
OBS: Questão 1 - APS 2
=================================================*/

#include <stdio.h> // Cabeçalho com funções padrões I/O

int main() { // Função Principal

    //////////////////////////
    /// Início do Programa ///
    //////////////////////////

    //* Variáveis *//

    int maximo=100, i=1, j, k, m=1, n, total1, total2, a, b, calculos[maximo][maximo],
    acima, esquerda, diagonal, score, tipo, match=1, mismatch=-1, gap=-2, resultado,
    menor, grande[1][3], p1=0, p2=0, p11=0, p22=0, t1=1, maiores[maximo], retirar=2,
    gap1=0, gap2=0, matches=0, mismatches=0, gaps=0;
    char letra, sequencia1[maximo], sequencia2[maximo], valor1, valor2, resposta,
    fita1[maximo], fita2[maximo], fita3[maximo];

    ///////////////
    /// Funções ///
    ///////////////

    // Função que retorna o maior valor inteiro
    int maior(num1,num2,num3) {
        // Variáveis auxiliares
        int ver1, ver2;
        // Obtém o maior entre num1 e num2
        if (num1>num2) {
            ver1 = num1;
        } else {
            ver1 = num2;
        }
        ver2 = num3;
        // Verifica quais dos números obtidos é maior e retorna na função
        if (ver1>ver2) {
            return ver1;
        } else {
            return ver2;
        }
    }

    // Função que retorna o maior valor inteiro de acordo com o alinhamento local
    int maior2(num1,num2,num3) {
        // Variáveis auxiliares
        int ver1, ver2, num4=0;
        // Obtém o maior entre num1 e num2
        if (num1>num2) {
            ver1 = num1;
        } else {
            ver1 = num2;
        }
        // Obtém o maior entre num3 e num4
        if (num3>num4) {
            ver2 = num3;
        } else {
            ver2 = num4;
        }
        // Verifica quais dos números obtidos é maior e retorna na função
        if (ver1>ver2) {
            return ver1;
        } else {
            return ver2;
        }
    }

    // Função que verifica e salva os valores na fita resultante
    void salvar(p11,p22,gap1,gap2) {
        // Match
        if (sequencia1[p11]==sequencia2[p22] && sequencia1[p11]!=' ') {
            fita1[t1] = sequencia1[p11];
            fita2[t1] = sequencia2[p22];
            fita3[t1] = '|';
            matches++;
        // Gap nas duas sequências
        } else if (gap1==1 && gap2==1) {
            fita1[t1] = '-';
            fita2[t1] = '-';
            fita3[t1] = ' ';
            p1++;
            p2++;
            gaps++;
        // Gap na sequência 1
        } else if (gap1==1 && gap2==0) {
            fita1[t1] = '-';
            fita2[t1] = sequencia2[p22];
            fita3[t1] = ' ';
            p1++;
            gaps++;
        // Gap na sequência 2
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
        // Soma na variável auxiliar
        t1++;
    }

    // Função que retorna a pontuação na posição atual
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
    /// Cabeçalho ///
    /////////////////

    printf("\n\n - ALINHAMENTO DE SEQUENCIAS -\n\n");

    // Recebe a primeira sequência
    printf(" -> Digite abaixo a primeira sequencia: (ao terminar tecle Enter)\n\n ");
    i = 1;
    while(letra!='\n') { // Enquanto o usuário não digitar Enter, recebe os valores
      letra = getchar(); // Obtém os valores digitados
      sequencia1[i] = toupper(letra); // Transforma as letras em maiúsculo e salva
      i++;
    }
    printf("\n");
    sequencia1[--i] = '\0'; // Fecha a string
    total1 = --i; // Salva o total de caracteres
    letra = '0'; // Reseta o valor da variável auxiliar

    // Recebe a segunda sequência
    printf(" -> Digite abaixo a segunda sequencia: (ao terminar tecle Enter)\n\n ");
    i = 1;
    while(letra!='\n') { // Enquanto o usuário não digitar Enter, recebe os valores
      letra = getchar(); // Obtém os valores digitados
      sequencia2[i++] = toupper(letra); // Transforma as letras em maiúsculo e salva
    }
    printf("\n");
    sequencia2[--i] = '\0'; // Fecha a string
    total2 = --i; // Salva o total de caracteres

    // Recebe (ou não) os valores para Match, Mismatch e Gap
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

    // Questiona ao usuário que tipo de alinhamento deseja utilizar
    printf(" -> Que tipo de alinhamento deve ser utilizado?\n\n");
    printf(" 1 - Global\n");
    printf(" 2 - Local\n\n");
    printf(" Opcao desejada: R= ");
    scanf("%d",&tipo);
    printf("\n");

    ////////////////////////////////////////
    // Cálculos para o Alinhamento Global //
    ////////////////////////////////////////

    if (tipo==1) {

        // Reseta as variáveis para utilização
        m = 1;
        a = -(retirar);
        b = -(retirar);

        // Imprime a sequência de cima
        for (i=1;i<total2+3;i++) {
            for (j=1;j<total1+3;j++) {
                // Ponto nulo
                if (i==1 && j==1) {
                    printf("  ");
                // Gap
                } else if ((i==1 && j==2) || (i==2 && j==1)) {
                    printf("- ");
                // Sequência de cima
                } else if (i==1) {
                    printf("%c ",sequencia1[i,j-2]);
                // Sequência do lado
                } else if (j==1) {
                    printf("%c ",sequencia2[j,i-2]);
                // Valor nulo na posição (2,2)
                } else if (i==2 && j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("0");
                // Valores padrões da sequência de cima
                } else if (i==2) {
                    calculos[i-1][j-1] = a;
                    a -= retirar;
                    printf(" %d",calculos[i-1][j-1]);
                // Valores padrões da sequência do lado
                } else if (j==2) {
                    calculos[i-1][j-1] = b;
                    b -= retirar;
                    printf("%d ",calculos[i-1][j-1]);
                // Caso geral
                } else {
                    // Define os valores ao redor da posição atual
                    valor1 = sequencia1[j-2];
                    valor2 = sequencia2[i-2];
                    // Valor acimacima
                    acima = (calculos[i-2][j-1])+gap;
                    // Valor à esquerda
                    esquerda = (calculos[i-1][j-2])+gap;
                    // Calcula o valor da diagonal
                    diagonal = (calculos[i-2][j-2])+p(valor1,valor2);
                    // Obtém o maior valor entre os três números e atribui à posição atual
                    calculos[i-1][j-1] = maior(acima,esquerda,diagonal);
                    // Imprime o resultado
                    printf("%d ",calculos[i-1][j-1]);
                    // Salva o score, que é a última posição da matriz
                    score = calculos[i-1][j-1];
                }
            }
            printf("\n\n");
        }

        // Define as posições zero das sequências
        sequencia1[0] = ' ';
        sequencia2[0] = ' ';

        // Detecta o menor valor da função e salva numa variável auxiliar
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
        // Determina os valores das posições x e y
        p1 = i;
        p2 = k;
        // Prossegue com os cálculos
        for (j=i;j>0;j--) {
            // Variáveis de auxílio
            gap1 = 0;
            gap2 = 0;
            // Salva as pocições das letras
            p11 = p1-1;
            p22 = p2-1;
            // Salva a posição diagonal
            n = calculos[p1][p2];
            // Verifica se a posição de cima é maior
            if (calculos[p11][p2]>n) {
                gap2 = 1;
            // Verifica se a posição da esquerda é maior
            } else if (calculos[p1][p22]>n) {
                gap1 = 1;
            }
            // Salva e verifica na fita resultante
            salvar(p11,p22,gap1,gap2);
            // Decrementa nas variáveis auxiliares
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
    // Cálculos para o Alinhamento Local //
    ///////////////////////////////////////

    } else if (tipo==2) {

        // Reseta a variável para utilização
        m = 1;

        // Imprime a sequência de cima
        for (i=1;i<total2+3;i++) {
            for (j=1;j<total1+3;j++) {
                // Ponto nulo
                if (i==1 && j==1) {
                    printf("  ");
                // Gap
                } else if ((i==1 && j==2) || (i==2 && j==1)) {
                    printf("- ");
                // Sequência de cima
                } else if (i==1) {
                    printf("%c ",sequencia1[i,j-2]);
                // Sequência do lado
                } else if (j==1) {
                    printf("%c ",sequencia2[j,i-2]);
                // Valor nulo na posição (2,2)
                } else if (i==2 && j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("0");
                // Valores padrões da sequência de cima
                } else if (i==2) {
                    calculos[i-1][j-1] = 0;
                    printf(" %d",calculos[i-1][j-1]);
                // Valores padrões da sequência do lado
                } else if (j==2) {
                    calculos[i-1][j-1] = 0;
                    printf("%d ",calculos[i-1][j-1]);
                // Caso geral
                } else {
                    // Calcula o valor da posição acima
                    acima = (calculos[i-2][j-1])+gap;
                    // Calcula o valor da posição à esquerda
                    esquerda = (calculos[i-1][j-2])+gap;
                    // Obtém os caracteres correspondentes em cada sequência
                    valor1 = sequencia1[j-2];
                    valor2 = sequencia2[i-2];
                    // Calcula o valor da posição diagonal
                    diagonal = (calculos[i-2][j-2])+p(valor1,valor2);
                    // Obtém o maior valor entre os três números e atribui à posição atual
                    calculos[i-1][j-1] = maior2(acima,esquerda,diagonal);
                    // Imprime o resultado
                    printf("%d ",calculos[i-1][j-1]);
                }
            }
            printf("\n\n");
        }

        // Define as posições zero das sequências
        sequencia1[0] = ' ';
        sequencia2[0] = ' ';

        // Detecta o menor valor da função e salva numa variável auxiliar
        for (i=1;i<total2+2;i++) {
            for (j=1;j<total1+2;j++) {
                if (calculos[i][j]<menor) {
                    menor = calculos[i][j];
                }
            }
        }

        // Detecta o maior valor da função e salva numa variável auxiliar
        grande[1][1] = menor;
        for (i=1;i<total2+2;i++) {
            for (j=1;j<total1+2;j++) {
                if (calculos[i][j]>grande[1][1]) {
                    // Salva o valor numérico
                    grande[1][1] = calculos[i][j];
                    // Salva a posição x
                    grande[1][2] = j;
                    // Salva a posição y
                    grande[1][3] = i;
                }
            }
        }

        // Percorre o vetor na diagonal para verificar o score e melhor alinhamento
        k = grande[1][3];
        i = grande[1][2];
        // Determina os valores das posições x e y
        p1 = k;
        p2 = i;
        // Salva o score
        score = calculos[k][i];
        // Prossegue com os cálculos
        for (j=k;j>0;j--) {
            // Variáveis de auxílio
            gap1 = 0;
            gap2 = 0;
            // Salva as posições das letras
            p11 = p2-1;
            p22 = p1-1;
            // Salva a posição diagonal
            n = calculos[p1][p2];
            // Verifica se a posição de cima é maior
            if (calculos[p11][p2]>n) {
                gap2 = 1;
            // Verifica se a posição da esquerda é maior
            } else if (calculos[p1][p22]>n) {
                gap1 = 1;
            }
            // Salva e verifica na fita resultante
            salvar(p11,p22,gap1,gap2);
            // Decrementa nas variáveis auxiliares
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

    // Opção inválida digitada, finaliza a execução
    } else {
        printf("\n -> OPCAO INVALIDA!\n\n");
    }

    ///////////////////////
    /// Fim do Programa ///
    ///////////////////////

    return 0;
}
