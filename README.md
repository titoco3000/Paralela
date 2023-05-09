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
    
### DAG

![DAGspigot drawio (3)](https://github.com/titoco3000/Paralela/assets/28358812/bf2cd97b-1203-4148-8aaf-281ae6471fb2)
