#include <stdio.h>
#include <stdlib.h>

int TAM_POPULACAO = 20;

int **individuos;

int items;
int *beneficios;
int *pesos;
int capacidade;

void geraPopulacao();
int avaliacao(int indice);
int seleciona();
int *combina();
void muta();
void novaGeracao();

int main() {

    int i, j;

    srand(1);

    scanf("%d", &items);
    scanf("%d", &capacidade);

    beneficios = (int *) malloc(sizeof(int) * items);
    pesos = (int *) malloc(sizeof(int) * items);

    for (int i = 0; i < items; i++) {
        scanf("%d %d", &pesos[i], &beneficios[i]);
    }

    individuos = (int **) malloc(sizeof(int *) * TAM_POPULACAO);

    for (i = 0; i < TAM_POPULACAO; i++) {
        individuos[i] = (int *) malloc(sizeof(int) * items);
    }

    geraPopulacao();

    for (i = 0; i < items; i++) {
        printf("%d ", pesos[i]);
    }

    printf("\n");

    for (i = 0; i < items; i++) {
        printf("%d ", beneficios[i]);
    }

    printf("\n");

    for (i = 0; i < TAM_POPULACAO; i++) {
        for (j = 0; j < items; j++) {
            printf("%d ", individuos[i][j]);
        }
        printf("%d\n", avaliacao(i));
    }

    for (int k = 0; k < 10; k++) {
        novaGeracao();
        printf("\n\nGeracao %d: \n", k + 1);
        for (i = 0; i < TAM_POPULACAO; i++) {
            for (j = 0; j < items; j++) {
                printf("%d ", individuos[i][j]);
            }
            printf("%d\n", avaliacao(i));
        }
    }

    return 0;

}

void geraPopulacao() {
    int i, j;

    for (i = 0; i < TAM_POPULACAO; i++) {
        for (j = 0; j < items; j++) {
            if ((rand() % 10) % 2 == 0) {
                individuos[i][j] = 1;
            } else {
                individuos[i][j] = 0;
            }
        }
    }
}

int avaliacao(int indice) {
    int j;
    int soma_peso = 0;
    int soma_beneficio = 0;

    for (j = 0; j < items; j++) {
        if (individuos[indice][j] == 1) {
            soma_peso += pesos[j];
            soma_beneficio += beneficios[j];
        }
    }

    return soma_peso > capacidade ? 0 : soma_beneficio;
}

int seleciona() {
    int s1 = rand() % TAM_POPULACAO;
    int s2 = rand() % TAM_POPULACAO;

    int melhor;
    int pior;

    if (avaliacao(s1) > avaliacao(s2)) {
        melhor = s1;
        pior = s2;
    } else {
        melhor = s2;
        pior = s1;
    }

    //if ((rand() % 100) < 10) {
      //  return pior;
    //}

    return melhor;
}

int *combina(int *s1, int *s2) {
    int *ns;
    int ponto = rand() % items;

    ns = (int *) malloc(sizeof(int) * items);

    for (int i = 0; i < ponto; i++) {
        ns[i] = s1[i];    
    }

    for (int i = ponto; i < items; i++) {
        ns[i] = s2[i];
    } 

    return ns;
}

void muta(int *s) {
    int p = rand() % items;

    s[p] = s[p] == 1 ? 0 : 1;
}

void novaGeracao() {
    int i;
    int s1, s2;
    int **ng;

    ng = (int **) malloc(sizeof(int *) * TAM_POPULACAO);

    for (i = 0; i < TAM_POPULACAO; i++) {
        s1 = seleciona();
        s2 = seleciona();

        if ((rand() % 100) >= 15) {
            ng[i] = combina(individuos[s1], individuos[s2]);

            if ((rand() % 100) < 20) {
                muta(ng[i]);
            }
        } else {
            ng[i++] = individuos[s1];
            ng[i] = individuos[s2];
        }
    }

    free(individuos);

    individuos = ng;
}