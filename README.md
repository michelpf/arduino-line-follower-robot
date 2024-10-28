# Robô Seguidor de Linha

Projeto básico de robô seguidor de linha baseado na estrutura FalconV2 da RoboCore, sensores analógicos de luminosidade e controle baseado em Arduíno.

O robô seguidor tem dois modos de utilização: limiar fixo de refletância de linha e outro por machine learning (experimental).

## Modo limiar fixo

Este é o modo mais comum.
Medimos os limiares na linha preta e fora dela para estabelecer um valor que com certeza define a linha. Valores inferiores ao limiar são considerados fora da linha.

## Modo com machine learning

Neste modo obtivemos uma série de exemplos para treinamento de valores dentro e fora da linha.

Treinamos um modelo simples com RandomForest, os passos do treinamento podem ser verificados em ```treinamento\treinamento-colab.ipynb```.

Depois do treinamento é necessário converter o modelo para instruções em C++ para ser lido no Arduíno. Fazemos isso com o micromlgen, conforme arquivo de treinamento.

A geração do modelo pelo micromlgen é o arquivo ```robot-line-follower\model.h```.

No Arduíno, por sua vez, é necessário baixar a biblioteca ```Eloquent```e utilizar a variável de acordo com o modelo treinado.

[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/michelpf/arduino-line-follower-robot/blob/main/treinamento/treinamento-colab.ipynb)


## Componentes utilizados

* 1 x [Plataforma robótica Falcon V2](https://www.robocore.net/robotica-robocore/plataforma-robotica-falcon-v2)
* 1 x [Controladora Vespa baseada em Arduíno](https://www.robocore.net/placa-robocore/vespa)
* 2 x [Sensor refletância QRE-113](https://www.robocore.net/sensor-robo/sensor-de-linha-qre-analogico)
* 1 x [Cabos de conexão fêmea-fêmea](https://www.robocore.net/cabo/jumpers-femea-femea-x40-unidades)

## Bibliotecas utilizadas

[RoboCore - Vespa v.1.3.0](https://github.com/RoboCore/)
[EloquentArduino v.2.1.3](https://github.com/eloquentarduino/EloquentArduino)

## Inspiração e referências

* [Robôs seguidores de linha da RoboCore](https://www.robocore.net/tutoriais/robo-seguidor-de-linha?srsltid=AfmBOoqUzbCHeBJA-cT_0MqPkqvbxXeD1cvFeGWeD1So9WrjO7PrLJ1o)
* [Controle de tensão de bateria](https://www.robocore.net/tutoriais/leitura-tensao-entrada-vespa)
* [Controle de motoroes](https://www.robocore.net/tutoriais/kit-iniciante-robotica-primeiros-movimentos)
* [Convertendo modelos do Scikit Learnig para Arduíno](https://eloquentarduino.github.io/2019/11/how-to-train-a-classifier-in-scikit-learn/)
* [Utilizando RandomForest no Arduíno](https://eloquentarduino.github.io/2020/10/decision-tree-random-forest-and-xgboost-on-arduino/)
* [ArduínoMicroML](https://github.com/TronixLab/ArduinoMicroML)