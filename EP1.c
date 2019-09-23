#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Vertice {
    double x;
    double y;
    struct Vertice *prox;
};

/*
Um polígono é definido como o ponteiro de um Struct de vértice. Afinal, saber a posição de memória de um vértice
permite saber a posição de memória de todos os vértices.
*/
typedef struct Vertice* Poligono;

struct Vertice* CriaVertice() {
    double a, b;
    scanf("%lf %lf", &a , &b);
    struct Vertice *vertice = (struct Vertice*) malloc(sizeof(struct Vertice*));
    vertice->x = a;
    vertice->y = b;
    return vertice;
}

void AdicionaVertice(Poligono poligono, struct Vertice* vertice) {
    struct Vertice* ultimovertice = poligono;

    while (ultimovertice->prox != poligono) {
        ultimovertice = ultimovertice->prox;
    }

    vertice->prox = poligono;
    ultimovertice->prox = vertice;
}

void CriaPoligono(int n, Poligono* poligono) {
    for (int i = 0; i < n; i++) {
        if (i == 0) { /* Vertice inicial */
            *poligono = CriaVertice();
            (*poligono)->prox = *poligono;
        } else {
            AdicionaVertice(*poligono, CriaVertice());
        }
    }
}

void PrintaLista(Poligono poligono) {
    struct Vertice* ultimovertice = poligono;
    printf("%lf %lf\n", ultimovertice->x, ultimovertice->y);

    while (ultimovertice->prox != poligono) {
        ultimovertice = ultimovertice->prox;
        printf("%lf %lf\n", ultimovertice->x, ultimovertice->y);

    }
}

int NumeroDeVertices(Poligono P) {
    int numero = 1;
    struct Vertice* vertice = P;

    while (vertice->prox != P) {
        numero += 1;
        vertice = vertice->prox;
    }

    return numero;
}

double Distancia(struct Vertice* A, struct Vertice* B) {
    return sqrt((A->x - B->x)*(A->x - B->x) + (A->y - B->y)*(A->y - B->y));
}

double Perimetro(Poligono P) {
    struct Vertice* vertice = P;
    double perimetro = 0;

    do {
        perimetro += Distancia(vertice, vertice->prox);
        vertice = vertice->prox;
    } while (vertice != P);

    return perimetro;
}

double Area(Poligono P) {
    double area = 0;
    struct Vertice* vertice = P;

    do {
        area += (vertice->y)*(vertice->prox->x) / 2;
        area -= (vertice->x)*(vertice->prox->y) / 2;
        vertice = vertice->prox;
    } while (vertice != P);

    if (area < 0) {
        area = area * (-1);
    }

    return area;
}


int main() {
    int numerodevertices;
    Poligono poligono; /* Já é o endereço de memória de um vértice inicial */

    scanf("%d", &numerodevertices);
    CriaPoligono(numerodevertices, &poligono);
    printf("Perimetro: %.1lf\n", Perimetro(poligono));
    printf("Area: %.1lf\n", Area(poligono));
}