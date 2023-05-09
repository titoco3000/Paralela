# Programação Paralela
## Projeto

Atenção! Os títulos são links para as respectivas versões

### [V1: Serial](https://github.com/titoco3000/Paralela/blob/main/projeto/spigot/serial/main.c)

Foi usado o algorítmo de Spigot.

Tempo total (100000 digitos): 

    real    0m44.841s
    user    0m44.016s
    sys     0m0.016s

### [V2: Paralela](https://github.com/titoco3000/Paralela/blob/main/projeto/spigot/paralelo/main.c)

Versão paralela do Spigot, usando a analogia do pente

Tempo total (100000 digitos): 

    real    0m23.811s
    user    0m45.172s
    sys     0m0.516s
   
Speedup = 1.8832

O máximo de casas geradas foi 500000, em 9m41.782s
    
### DAG

*_Considerando aqui que o número de dígitos gerados N = 3_*

![DAGspigot drawio (4)](https://github.com/titoco3000/Paralela/assets/28358812/5fdf1602-52c8-497e-a919-024eedd66c85)

Limite Inferior de execução:  **3t + (N/2)t => (3+3/2)t** (sendo t o tempo para executar cada tarefa)

Processadores necessarios para se coseguir o tempo mínimo de execução: **2**

Grau máximo de concorrência: **2**

Paralelismo médio: **6/10 = 60%**
