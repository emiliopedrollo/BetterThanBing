# BetterThanBing

BetterThanBing é um projeto simples de ordenação de cartas desenvolvido como trabalho acadêmico por [Emílio B. Pedrollo] para a cadeira de Laboratório de Programação II pela UFSM.

[Emílio B. Pedrollo]: <https://github.com/emiliopedrollo>

## Obtenção do código fonte
O código-fonte está disponível publicamente online no endereço https://github.com/emiliopedrollo/BetterThanBing/tree/graphs e é possível efetuar o download do fonte compactado em *.zip* diretamente no site ou através do gerenciador de versões *git* com a seguinte linha de comando:
```sh
git clone https://github.com/emiliopedrollo/BetterThanBing/tree/graphs
```


## Compilando
Apesar de ser possível compilar o código fonte através do compilador padão *gcc* para *unix* é muito mais fácil utilizar o pacote *cmake* para automatizar o processo:

### Utilizando cmake
Caso não tenha o *cmake* instalado é possivel instalá-lo com a seguinte linha de comando como super usuário em distros baseadas no Debian (como o Ubuntu):
```sh
apt-get install -y cmake 
```
Para compilar basta ir até a pasta contendo o fonte e executar
```sh
cmake . && make
```
O compilador é esta instruído a utilizar o padrão C *ansi* para este projeto. Após a compilação o executável **btbg** estará na mesma pasta com os códigos-fonte.


### Utilizando gcc
Caso você não tenha o *cmake* instalado e não possua permissão administrativas para instala-lo ou simplismente queira utilizar um método mais pimitivo é possível utilizar o compilador padrão *gcc* com a seguinte linha:
```sh
gcc -o btbg -std=c11 -ansi main.c trie.h trie.c utils.c utils.h lists.c lists.h
```
