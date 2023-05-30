Implementação paralelizada com CUDA do algoritmo de spigot, conforme descrito em:

The Calculation of e to Many Significant Digits por A. H. J. Sale

---

A versão serial inspirada de:
https://youtu.be/nleB7uPtQxQ

e adaptada de:
https://adamcrussell.livejournal.com/6924.html

Recursos que explicam muito melhor o algoritmo.

---

Usa a analogia do pente: de cada casa do vetor, é carregado (ou penteado) um valor para a próxima. 
É penteado da ultima casa para a primeira; a primeira carrega o valor direto para um arquivo, sendo este a próxima casa decimal do numero de euler.
Cada posição do vetor de N posições precisa ser penteada N vezes, e a condição para ser penteada é a anterior ter sido também.

Ambiente:
Google Colab (Nvidia Tesla T4)

3000001 digitos de precisão:

![image](https://github.com/titoco3000/Paralela/assets/28358812/9d03a130-d1dd-48c1-a4a1-8d27aa2b869a)

5000001 digitos de precisão:

![image](https://github.com/titoco3000/Paralela/assets/28358812/d9ca1d96-36a7-4847-881e-b68385b5cff2)

8000001 digitos de precisão:

![image](https://github.com/titoco3000/Paralela/assets/28358812/aba82cab-0433-48dd-ba70-95b6ad2d393c)

# Comparação com serial
(30001 digitos de precisão)

Serial:

![image](https://github.com/titoco3000/Paralela/assets/28358812/4c26b160-566a-451a-9583-0c6d07726e07)

Paralelo:

![image](https://github.com/titoco3000/Paralela/assets/28358812/ee2e64e6-0ebc-4acf-bffe-3ad6be0250c2)

Speedup = 7,95
