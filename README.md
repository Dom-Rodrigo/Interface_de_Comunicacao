# Interrupções e matriz de led da BitDogLab

## Como funciona o código?

[![FUNCIONAMENTO NA PLACA](https://img.youtube.com/vi/DcNJFS9BQgY/0.jpg)](https://www.youtube.com/watch?v=DcNJFS9BQgY)

O código possui as seguintes funções:

- Possui o desenho de **digitos similares a um display de 7 segmentos** na matriz de LED (gpio 7)

- Utilizando de interrupções, **sem interferir no led que pisca em vermelho**, pode se fazer:
  
  - Incrementar o digito da matriz **clicando no botão A** (gpio 5)
  
  - Decrementar o dígito da matriz **clicando no botão B** (gpio 5)

## Funções

<mark>void desenha_numero_vermelho(int array_pixels[], int size)</mark>

Desenha um só numero na matrix, recebendo um array com os índices do leds que precisam ser acesos, e o tamanho do array.

<mark>void desenha_numeros(int numero)</mark>

Implementa <u>desenha_numero_vermelho</u> com base no número dado de 0 a 9

<mark>gpio_irq_handler</mark>

Função que manuseia a interrupção, incrementando o valor do digito ao clicar no A e decrementando ao clicar no B, além de implementar um deboucing

## Como compilar?

### No VSCode

Importe um projeto Raspberry Pi Pico, com a versão Pico SDK 2.1.0. É necessário ter instalado a extensões Raspberry Pi Pico.

### Manualmente

- > mkdir build/

- > cd build

- > cmake ..

- > make
