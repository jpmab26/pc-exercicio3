/**
 * Disciplina: Programacao Concorrente
 * Nome: João Pedro Mendes Alves Bianco
 * DRE: 120064499
 * Laboratório 8 - Produtor/Consumidor com Semáforos 
**/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <math.h>

int N; // total de números a serem gerados
int M; // tamanho do buffer
int nConsumidores;

int *buffer;
int nextNum = 1;
int numsProduzidos = 0;
int numsConsumidos = 0;

sem_t slotCheio;
sem_t slotVazio;
sem_t mutexBuffer;
sem_t mutexStats;

int *primosEncontrados;
int totalPrimos = 0;

int ehPrimo(long long int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (i = 3; i < sqrt(n) + 1; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

void *produtor(void *arg) {
    while (numsProduzidos < N) {
        // Espera o buffer ficar completamente vazio
        for (int i = 0; i < M; i++) {
            sem_wait(&slotVazio);
        }
        // Preenche todo o buffer de uma vez
        sem_wait(&mutexBuffer);
        int numsPreencher = (N - numsProduzidos < M) ? (N - numsProduzidos) : M;
        for (int i = 0; i < numsPreencher; i++) {
            buffer[i] = nextNum++;
            numsProduzidos++;
        }
        printf("Produtor: inseriu %d números (%d a %d)\n", numsPreencher, nextNum - numsPreencher, nextNum - 1);
        sem_post(&mutexBuffer);
        // Sinaliza que há slots cheios
        for (int i = 0; i < numsPreencher; i++) {
            sem_post(&slotCheio);
        }
    }
    pthread_exit(NULL);
}

void *consumidor(void *arg) {
    int id = *(int*)arg;
    int primosLocal = 0;    
    while (1) {
        // Verifica se ainda há números para consumir
        sem_wait(&mutexStats);
        if (numsConsumidos >= N) {
            sem_post(&mutexStats);
            break;
        }
        numsConsumidos++;
        sem_post(&mutexStats);
        // Aguarda um slot cheio
        sem_wait(&slotCheio);
        // Retira um número do buffer
        sem_wait(&mutexBuffer);
        int numero = -1;
        // Procura o primeiro slot não vazio
        for (int i = 0; i < M; i++) {
            if (buffer[i] != 0) {
                numero = buffer[i];
                buffer[i] = 0;
                break;
            }
        }
        sem_post(&mutexBuffer);
        sem_post(&slotVazio);
        if (numero != -1) {
            // Verifica se é primo
            if (ehPrimo(numero)) {
                primosLocal++;
                printf("Consumidor %d: %d é primo\n", id, numero);
            }
        }
    }
    // Atualiza estatísticas
    sem_wait(&mutexStats);
    primosEncontrados[id] = primosLocal;
    totalPrimos += primosLocal;
    sem_post(&mutexStats);
    printf("Consumidor %d terminou: encontrou %d primos\n", id, primosLocal);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso: %s <N> <M> <nConsumidores>\n", argv[0]);
        printf("N: total de números a serem gerados\n");
        printf("M: tamanho do buffer (deve ser menor que N)\n");
        printf("nConsumidores: número de threads consumidoras\n");
        return 1;
    }
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    nConsumidores = atoi(argv[3]);
    if (M >= N) {
        printf("Erro: M deve ser menor que N\n");
        return 1;
    }
    printf("Configuração: N=%d, M=%d, Consumidores=%d\n", N, M, nConsumidores);
    buffer = (int*)calloc(M, sizeof(int));
    primosEncontrados = (int*)calloc(nConsumidores, sizeof(int));    

    sem_init(&slotCheio, 0, 0);
    sem_init(&slotVazio, 0, M);
    sem_init(&mutexBuffer, 0, 1);
    sem_init(&mutexStats, 0, 1);
    
    pthread_t produtorThread;
    pthread_t *consumidorThreads = (pthread_t*)malloc(nConsumidores * sizeof(pthread_t));
    int *ids = (int*)malloc(nConsumidores * sizeof(int));
    
    pthread_create(&produtorThread, NULL, produtor, NULL);
    
    for (int i = 0; i < nConsumidores; i++) {
        ids[i] = i;
        pthread_create(&consumidorThreads[i], NULL, consumidor, &ids[i]);
    }

    pthread_join(produtorThread, NULL);
    
    for (int i = 0; i < nConsumidores; i++) {
        pthread_join(consumidorThreads[i], NULL);
    }
    
    // Encontra a thread vencedora
    int vencedora = 0;
    int maxPrimos = primosEncontrados[0];
    for (int i = 1; i < nConsumidores; i++) {
        if (primosEncontrados[i] > maxPrimos) {
            maxPrimos = primosEncontrados[i];
            vencedora = i;
        }
    }
    
    printf("\n=== RESULTADOS FINAIS ===\n");
    printf("Total de números processados: %d\n", N);
    printf("Total de números primos encontrados: %d\n", totalPrimos);
    printf("Thread consumidora VENCEDORA: %d (encontrou %d primos)\n", vencedora, maxPrimos);
    
    printf("\nDetalhamento por consumidor:\n");
    for (int i = 0; i < nConsumidores; i++) {
        printf("Consumidor %d: %d primos\n", i, primosEncontrados[i]);
    }
    
    sem_destroy(&slotCheio);
    sem_destroy(&slotVazio);
    sem_destroy(&mutexBuffer);
    sem_destroy(&mutexStats); 
    free(buffer);
    free(primosEncontrados);
    free(consumidorThreads);
    free(ids);
    printf("\nFim.\n");
    return 0;
}
