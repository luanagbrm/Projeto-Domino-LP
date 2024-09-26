# PROJETO: DOMINÓ
### Linguagens utilizadas:
<img src = "https://img.shields.io/badge/C-248a3f?style=for-the-badge&logo=c&logoColor=white" />

### Desenvolvido por:
@luanagbrm @GaiaOcean @bialim @Ferri-js

## OBJETIVOS
- Desenvolver um programa em C que permite ao usuário jogar o “jogo de dominó” com as regras simples.
- O jogo poderá ser jogado entre dois oponentes reais (pessoas) ou entre um jogador real e o computador (vamos simular um comportamento inteligente do computador por meio de regras implementadas em código).
- O programa deverá implementar as funções e estruturas de dados para a execução do jogo com as regras simples e com a interface com o usuário necessária para a interação dos jogadores. Vamos usar um padrão de projeto de sistemas interativos para construir o programa (arquitetura MVC).

## REQUISITOS FUNCIONAIS
<b>REQ01</b>: O sistema deverá montar as peças do dominó com a numeração correta do jogo

<b>REQ02</b>: O sistema deve permitir ao usuário embaralhar as peças do dominó

<b>REQ03</b>: O sistema deverá permitir ao usuário preparar para jogar novamente, embaralhando novamente as peças.

<b>REQ04</b>: O sistema deverá permitir ao usuário mostrar todas as peças do dominó na tela
de forma organizada (em ordem) e tambem embaralhada. (modo texto)

<b>REQNF05</b>: O sistema deverá estar estruturado no modelo MVC.

<b>REQNF06</b>: O sistema deverá ser projetado de forma suficientemente modularizada para facilitar a manutenção e alterações sem impactar os demais módulos do sistema.

<b>REQ07:</b> O sistema deve permitir ao usuário determinar a quantidade de jogadores. No
mínimo 1 e máximo 2 jogadores.

<b>REQ08</b>: O sistema deve distribuir aleatoriamente 7 peças para cada jogador.

<b>REQ09</b>: O sistema deverá criar uma mesa vazia para receber as jogadas.

<b>REQ10</b>: O sistema deverá definir o jogador que fará imediatamente a primeira jogada.

<b>REQ11</b>: O sistema deve permitir ao jogador pegar (“comprar”) uma peça das disponíveis.

<b>REQ12</b>: O sistema deve verificar se a jogada do jogador é válida (se a peça a ser colocada tem a mesma pontuação da peça da extremidade escolhida da mesa)

<b>REQ13</b>: O sistema deverá permitir ao usuário ver as suas peças na tela durante o jogo

<b>REQ14</b>: O sistema deverá permitir ao usuário esconder as peças dos demais jogadores

<b>REQ15</b>: O sistema deverá permitir ao usuário finalizar o jogo de dominó

<b>REQ16</b>: O sistema deverá permitir ao usuário comprar peças durante o jogo

<b>REQ17</b>: O sistema deverá permitir ao usuário visualizar as regras do jogo

<b>REQ18:</b> O sistema deverá permitir ao usuário salvar o jogo em um arquivo a qualquer
momento, para poder continuar jogando numa outra ocasião.

<b>REQ19:</b> O sistema deverá permitir ao usuário carregar um jogo que foi salvo em arquivo
para prosseguir jogando.

<b>REQ20:</b>  No caso de apenas um jogador jogando contra o computador (jogador 2), o sistema deverá simular um comportamento inteligente como um jogador real, sempre dentro das regras normais do jogo; um jogador nunca tem acesso as peças do seu adversário, nem as ainda disponíveis, somente pode deduzir... e aí está a inteligência a ser implementada.

## FUNCIONALIDADES ADICIONADAS PELO GRUPO
### Data e hora do save
- A data e hora em que o jogo foi salvo, são salvos junto a partida em si. Trazendo tanto uma confirmação da operação, quanto uma maior ciência sobre o que vai ser recuperado.
### Inteligência do jogador computador:
#### - Preferência de jogada:
- A jogada do computador sempre priorizará jogar a peça com o número de maior ocorrência entre as suas peças, considerando os os movimentos possíveis.
- Toda vez que o jogador 1 (pessoa) compra uma peça, o computador armazena quais eram os limites da mesa no momento da compra e, nas suas jogadas, busca deixar esses valores nas extremidades, o que forçaria o jogador 1 a comprar peças.
- Caso não tenha havido compra ou o computador não tenha nenhuma peça que possa ser jogada de acordo com a função anterior, ele então busca por uma peça dupla para ser jogada, uma vez que uma peça dupla apresenta apenas uma possibilidade de jogada, o que se torna desvantajoso em comparação a peças que possuem dois números distintos.
- Caso não seja possível jogar com nenhuma das especificações anteriores, o computador tenta fazer uma jogada com o número que o computador possui em maior quantidade na mão.


