#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
    *state = (*state * 1103515245u) + 12345u;
    return *state;
}

static void build_dataset(void)
{
    unsigned int state;
    int i;

    state = SEED_VALUE;

    for (i = 0; i < DATASET_SIZE; i++)
        dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
    int i;
    int v;

    for (i = 0; i < DATASET_SIZE; i++)
    {
        v = dataset[i];
        v = (v * 3) + (v / 7) - (v % 11);
        if (v < 0)
            v = -v;
        dataset[i] = v;
    }
}

static unsigned long reduce_checksum(void)
{
    unsigned long sum;
    int i;

    sum = 0;
    for (i = 0; i < DATASET_SIZE; i++)
        sum = (sum * 131ul) + (unsigned long)dataset[i];

    return sum;
}

int main(void)
{
    unsigned long checksum;
    /* Chronomètres (les boîtes de stockage), t pour total, b pour build, p pour process et r pour reduces */
    clock_t t_start, t_end;
    clock_t b_start, b_end;
    clock_t p_start, p_end;
    clock_t r_start, r_end;
    /*double = boite  qui stocke le résultat final en secondes.*/
    double t_sec, b_sec, p_sec, r_sec;

    /* Students must add clock-based timing and print required lines. */
    /*Top départ chrono global*/
    t_start = clock();

    /*lancement chrono secteur 1 : génération de données*/
    b_start = clock();
    build_dataset();
    b_end = clock();

    /*lancement chrono secteur 2 : transformation de données*/
    p_start = clock();
    process_dataset();
    p_end = clock();

    /*lancement chrono secteur 3 : calcul de la signature*/
    r_start = clock();
    checksum = reduce_checksum();
    r_end = clock();

    /*Fin chrono global*/
    t_end = clock();

    /*on convertit ici les tics d'horloge en secondes humaines*/
    b_sec = (double)(b_end - b_start) / (double)CLOCKS_PER_SEC;
    p_sec = (double)(p_end - p_start) / (double)CLOCKS_PER_SEC;
    r_sec = (double)(r_end - r_start) / (double)CLOCKS_PER_SEC;
    t_sec = (double)(t_end - t_start) / (double)CLOCKS_PER_SEC;

    if (checksum == 0ul)
        printf("impossible\n");

    /* Required output (exact format, no extra lines):
     * TOTAL seconds: <float>
     * BUILD_DATA seconds: <float>
     * PROCESS seconds: <float>
     * REDUCE seconds: <float>
     * ici ils veulent 6 décimales après la virgule, d'où le %.6f
     */
     printf("TOTAL seconds: %.6f\n", t_sec);
     printf("BUILD_DATA seconds: %.6f\n", b_sec);
     printf("PROCESS seconds: %.6f\n", p_sec);
     printf("REDUCE seconds: %.6f\n", r_sec);

    return 0;
}
