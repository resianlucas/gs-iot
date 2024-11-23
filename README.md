# gs-iot
https://youtu.be/2OfiyjI1UvI


Passos para Replicar

Configuração do Broker MQTT:
Use o broker Mosquitto local ou o serviço online test.mosquitto.org.
Código para os ESP32:

Faça o upload do código de ambos os ESP32 utilizando a Arduino IDE.
Configure as credenciais Wi-Fi e o broker MQTT no código.
Configuração do Node-RED:

Importe o fluxo JSON fornecido.
Configure o broker MQTT no Node-RED para o mesmo broker utilizado nos ESP32.

Testando:
Conecte o potenciômetro ao primeiro ESP32 e o relé ao segundo.
Observe o comportamento do ventilador no Node-RED, onde você verá a potência e o consumo exibidos em tempo real.
