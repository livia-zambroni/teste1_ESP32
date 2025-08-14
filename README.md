# teste1_ESP32
Este projeto tem como objetivo desenvolver um transmissor de dados de baixo custo para uma bomba de insulina, utilizando um microcontrolador ESP32 para enviar informações via Bluetooth Low Energy (BLE) para um aplicativo móvel.
Atualmente, o projeto está em uma fase de prova de conceito, onde um botão é utilizado para simular a entrada de dados. O tempo que o botão é pressionado é medido e enviado para o aplicativo.

Funcionalidades Atuais
 * Estabelece uma conexão de servidor BLE em um ESP32.
 * Detecta o pressionamento de um botão físico conectado a uma porta GPIO.
 * Calcula a duração (em segundos) que o botão foi mantido pressionado.
 * Envia a duração calculada para um cliente BLE (aplicativo móvel).

Hardware Necessário
 * 1x Microcontrolador ESP32 (qualquer variante, como ESP32-DevKitC)
 * 1x Push-button (botão de pressão)
 * 1x Protoboard
 * Jumpers (fios para conexão)
 * 1x Cabo Micro-USB para programação e alimentação

Software Necessário
 * Arduino IDE
 * Placas ESP32 configuradas na Arduino IDE. Siga este guia se ainda não o fez.
 * Um aplicativo cliente BLE para receber os dados.

Como Compilar e Usar
 * Abra na Arduino IDE:
   * Abra o arquivo .ino do projeto na Arduino IDE.
 * Selecione a Placa e a Porta:
   * Vá em Ferramentas > Placa e selecione o modelo do seu ESP32 (ex: "ESP32 Dev Module").
   * Vá em Ferramentas > Porta e selecione a porta COM à qual seu ESP32 está conectado.
	> No modelo utilizado: ESP32 Dev Module porta COM5
 * Carregue o Código:
   * Clique no botão "Carregar" (seta para a direita) na Arduino IDE.
   * Dica: Em algumas placas, pode ser necessário manter o botão "BOOT" pressionado durante o início do upload.
 * Teste a Comunicação:
   * Após o upload, o ESP32 iniciará o servidor BLE com o nome MeuESP32.
   * Abra o seu aplicativo no celular e conecte-se ao dispositivo.
   * Pressione e segure o botão.
   * Ao soltar o botão, o tempo em segundos que ele foi pressionado será enviado e exibido no seu aplicativo.

Status do Projeto
O projeto está em desenvolvimento. A funcionalidade atual serve como base para a integração de sensores e dados reais da bomba de insulina.