#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// --- NOVO: Pino onde o botão está conectado ---
const int buttonPin = 4; // Você pode usar outra porta GPIO se desejar

// --- NOVO: Variáveis para controlar o tempo do botão ---
unsigned long startTime = 0;
bool isPressing = false;

// UUIDs para o serviço e característica, mantidos do seu código original
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect (BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Dispositivo conectado!");
  };
  void onDisconnect (BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Dispositivo desconectado!");
    pServer->getAdvertising()->start(); // Reinicia o advertising
  };
};

void setup() {
  Serial.begin (9600);

  // --- NOVO: Configura o pino do botão ---
  // INPUT_PULLUP ativa o resistor interno. O pino lerá HIGH quando o botão
  // não estiver pressionado e LOW quando estiver (conectado ao GND).
  pinMode(buttonPin, INPUT_PULLUP);

  BLEDevice::init("MeuESP32");
  BLEServer* pServer = BLEDevice::createServer(); // Cria o servidor BLE
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID); // Cria o serviço BLE

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY
                    ); // Cria a característica BLE

  pCharacteristic->addDescriptor(new BLE2902()); // Adiciona o descritor para notificações
  pService->start(); // Inicia o serviço

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID); // Linha crucial para o app encontrar o ESP32
  pAdvertising->start();
  Serial.println("Aguardando conexão de um cliente...");
};

void loop() {
  // Lê o estado atual do botão.
  // HIGH = solto, LOW = pressionado (devido ao INPUT_PULLUP)
  int buttonState = digitalRead(buttonPin);

  // --- LÓGICA DO BOTÃO ---

  // 1. Detecta o momento EXATO em que o botão é pressionado (transição de HIGH para LOW)
  if (buttonState == LOW && !isPressing) {
    isPressing = true;
    startTime = millis(); // `millis()` retorna o número de milissegundos desde que o ESP32 ligou
    Serial.println("Botão pressionado, cronômetro iniciado!");
  }

  // 2. Detecta o momento EXATO em que o botão é solto (transição de LOW para HIGH)
  if (buttonState == HIGH && isPressing) {
    isPressing = false;
    unsigned long pressDuration = millis() - startTime;
    float seconds = pressDuration / 1000.0; // Converte de milissegundos para segundos

    Serial.print("Botão solto! Duração: ");
    Serial.print(seconds);
    Serial.println(" segundos.");

    // 3. Se um dispositivo estiver conectado, envia o valor
    if (deviceConnected){
      char txString[10]; // Buffer para a string a ser enviada
      
      // Converte o valor float para uma string com 2 casas decimais
      // dtostrf(floatValue, minStringWidth, numDecimalPlaces, buffer)
      dtostrf(seconds, 1, 2, txString);

      pCharacteristic->setValue(txString);
      pCharacteristic->notify(); // Notifica o cliente conectado
      
      Serial.print("Valor enviado para o app: ");
      Serial.println(txString);
    }
  }

  // Pequeno delay para estabilizar a leitura e evitar "debounce" sem complexidade
  delay(50); 
}