
#include "stdlib.h"
#include "stdio.h"

int insertion(int a, int *tab, int size)
{
    if (size == 0)
        return 0;
    int s = size / 2;
    if (a <= tab[s])
        return insertion(a, tab, s);
    else
        return s + 1 + insertion(a, tab + s + 1, size - s - 1);
}

void ordonner(int *tab, int size, int **ordre)
{
    if (size == 0)
        return;
    if (size == 1)
    {
        (*ordre)[0] = 0;
        return;
    }
    int *aux = NULL;
    aux = malloc(size * 4);
    if (aux == NULL)
        exit(0);
    int s = size / 2;
    for (int i = 0; i < size; i++)
        aux[i] = i;
    for (int i = 0; i < s; i++)
    {
        if (tab[2 * i] > tab[2 * i + 1])
        {
            aux[2 * i + 1] = 2 * i;
            aux[2 * i] = 2 * i + 1;
        }
    }
    int *grand = NULL;
    grand = malloc(s * 4);
    if (grand == NULL)
        exit(0);
    for (int i = 0; i < s; i++)
        grand[i] = tab[aux[2 * i + 1]];
    int *ordregrand = NULL;
    ordregrand = malloc(s * 4);
    if (ordregrand == NULL)
        exit(0);
    ordonner(grand, s, &ordregrand);
    free(grand);
    (*ordre)[0] = aux[2 * ordregrand[0]];
    for (int i = 0; i < s; i++)
        (*ordre)[i + 1] = aux[2 * ordregrand[i] + 1];
    for (int i = 1; i < s; i++)
        (*ordre)[s + i] = aux[2 * ordregrand[i]];
    if (size % 2 == 1)
        (*ordre)[size - 1] = size - 1;
    free(ordregrand);
    int m = 2;
    int t = s + 1;
    int c = 4;
    int u;
    while (t < size)
    {
        u = c - m;
        if (t + u > size)
        {
            u = size - t;
            c = t + 1;
        }
        for (int i = 0; i < u; i++)
        {
            for (int j = 0; j < c - 1; j++)
                aux[j] = tab[(*ordre)[j]];
            int r = (*ordre)[t + u - 1];
            int rr = insertion(tab[r], aux, c - 1);
            for (int j = t + u - 2; j >= rr; j--)
                (*ordre)[j + 1] = (*ordre)[j];
            (*ordre)[rr] = r;
        }
        m = m + 2u;
        t = t + u;
        c = 2 * c;
    }
    free(aux);
}


int main(int argc, const char *argv[])
{
    int size = 11;
    int tab[11] = {3, 17, 12, 0, 2, 4, 10, 20, 8, 6, 5};
    int *ordre = NULL;
    ordre = malloc(size * 4);
    if (ordre == NULL)
        exit(0);
    ordonner(tab, size, &ordre);
    for (int i = 0; i < size; i++)
        printf("%d ", tab[i]);
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%d ", ordre[i]);
    printf("\n");
    for (int i = 0; i < size; i++)
        printf("%d ", tab[ordre[i]]);
    printf("\n");
    free(ordre);
    return 0;
}