# Kaypad_uart
usa a  porta serial para controlar pinos GPIO da Raspberry pico W. É feito acionamento de LED  RGB, juntamente com o controle de sinal  sonoro de um buzze. Como forma de comunicação entre o  usuário e o sistema embarcado, deve-se escrever comandos para serem interpretados pelo microcontrolador. 

Vídeo de apresentação do código e da execução na placa BitDogLab: 
https://youtu.be/eblEMGYgz6Q

Ligar LED verde (GPIO 11) – desligar as demais GPIOs;
2) Ligar LED azul (GPIO 12) - desligar as demais GPIOs;
3) Ligar LED vermelho (GPIO 13) - desligar as demais GPIOs;
4) Ligar os três LEDs (luz branca);
5) Desligar todos os LEDs;
6) Acionar o buzzer por 2 segundos – emissão de sinal sonoro;
7) Sair do modo de execução e habilitar o modo de gravação via
software (reboot) – rotina opcional.

