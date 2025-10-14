# pc-exercicio3

## Avaliação da corretude do programa:

Para testar a corretude do programa foi executado o programa com um N relativamente pequeno, como 100 e checamos se a quantidade de número primos totais achada está correta.

Por exemplo: `./lab8 100 25 4 # (N = 100; M = 25; Consumidores = 4)`
```
Configuração: N=100, M=90, Consumidores=10
Produtor: inseriu 90 números (1 a 90)
Consumidor 0: 2 é primo
Consumidor 0: 3 é primo
Consumidor 0: 5 é primo
Consumidor 1: 7 é primo
Consumidor 2: 13 é primo
Consumidor 2: 19 é primo
Consumidor 0: 11 é primo
Consumidor 0: 31 é primo
Consumidor 2: 29 é primo
Consumidor 0: 37 é primo
Consumidor 0: 47 é primo
Consumidor 1: 17 é primo
Consumidor 5: 59 é primo
Consumidor 5: 67 é primo
Consumidor 5: 73 é primo
Consumidor 7: 79 é primo
Consumidor 5: 83 é primo
Consumidor 3: 23 é primo
Consumidor 0: 53 é primo
Consumidor 4: 41 é primo
Consumidor 2: 43 é primo
Consumidor 6: 71 é primo
Consumidor 7: 89 é primo
Produtor: inseriu 10 números (91 a 100)
Consumidor 8 terminou: encontrou 0 primos
Consumidor 0 terminou: encontrou 8 primos
Consumidor 9 terminou: encontrou 0 primos
Consumidor 7 terminou: encontrou 2 primos
Consumidor 6 terminou: encontrou 1 primos
Consumidor 4: 97 é primo
Consumidor 1: 61 é primo
Consumidor 1 terminou: encontrou 3 primos
Consumidor 5 terminou: encontrou 4 primos
Consumidor 4 terminou: encontrou 2 primos
Consumidor 3 terminou: encontrou 1 primos
Consumidor 2 terminou: encontrou 4 primos

=== RESULTADOS FINAIS ===
Total de números processados: 100
Total de números primos encontrados: 25
Thread consumidora VENCEDORA: 0 (encontrou 8 primos)

Detalhamento por consumidor:
Consumidor 0: 8 primos
Consumidor 1: 3 primos
Consumidor 2: 4 primos
Consumidor 3: 1 primos
Consumidor 4: 2 primos
Consumidor 5: 4 primos
Consumidor 6: 1 primos
Consumidor 7: 2 primos
Consumidor 8: 0 primos
Consumidor 9: 0 primos

Fim.
```

Para verificar a sincronização foi feito um teste de mesa junto a diversos testes com diferentes parâmetros em busca de inconsistências.

## Alguns valores de entrada testados e seus outputs:

OBS.: Outputs cortados, mostrando apenas o resultado final para evitar muita informação.

1. `N = 1000; M = 100; Consumidores = 10;`
```
=== RESULTADOS FINAIS ===
Total de números processados: 1000
Total de números primos encontrados: 168
Thread consumidora VENCEDORA: 0 (encontrou 41 primos)

Detalhamento por consumidor:
Consumidor 0: 41 primos
Consumidor 1: 20 primos
Consumidor 2: 16 primos
Consumidor 3: 15 primos
Consumidor 4: 19 primos
Consumidor 5: 10 primos
Consumidor 6: 11 primos
Consumidor 7: 9 primos
Consumidor 8: 19 primos
Consumidor 9: 8 primos

Fim.
```
2. `N = 1000; M = 100; Consumidores = 2;`
```
=== RESULTADOS FINAIS ===
Total de números processados: 1000
Total de números primos encontrados: 168
Thread consumidora VENCEDORA: 0 (encontrou 91 primos)

Detalhamento por consumidor:
Consumidor 0: 91 primos
Consumidor 1: 77 primos

Fim.
```
3. `N = 2000000; M = 500; Consumidores = 10;`
```
=== RESULTADOS FINAIS ===
Total de números processados: 2000000
Total de números primos encontrados: 148933
Thread consumidora VENCEDORA: 8 (encontrou 15076 primos)

Detalhamento por consumidor:
Consumidor 0: 14935 primos
Consumidor 1: 14861 primos
Consumidor 2: 14882 primos
Consumidor 3: 14940 primos
Consumidor 4: 14895 primos
Consumidor 5: 14727 primos
Consumidor 6: 14800 primos
Consumidor 7: 14931 primos
Consumidor 8: 15076 primos
Consumidor 9: 14886 primos

Fim.
```

## Dificuldades

- Acertar toda a lógica de sincronização:
    - De início entender quando utilizar cada semáforo;
    - Muitos testes com tentativa e erro para conseguir chegar ao código ideal;