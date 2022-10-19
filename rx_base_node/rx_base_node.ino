//library yang dibutuhkan
#include <RF24.h>
#include <RF24Network.h>

//radio
RF24 radio(9, 10);
RF24Network network(radio);

//pengalamatan node
const uint16_t alamatNodeIni = 00;
//const uint16_t alamatNodeLain = 01;

//variabel penampung data yang diterima
struct data {
  float temperature;
  float humidity;
  char notif[4];
} receivedData;

//setup
void setup(void) {

  Serial.begin(9600);
  if (!Serial) {
    Serial.println(F("Serial error..."));
  }
  //Serial.println(F("Terima Data ... "));

  if (!radio.begin()) {
    Serial.println(F("Radio tidak bekerja"));
    while (1) {
      Serial.println(F("Radio sedang diproses"));
    }
  }
  network.begin(90, alamatNodeIni);
}

//loop
void loop(void) {
  network.update();
  while (network.available()) {
    RF24NetworkHeader header;
    uint16_t payloadSize = network.peek(header);
    network.read(header, &receivedData, payloadSize);
    if (header.from_node == 01) {
      Serial.print("node1");
      Serial.print("\t");
      Serial.print(receivedData.temperature);
      Serial.print("\t");
      Serial.print(receivedData.humidity);
      Serial.print("\t");
      Serial.print(receivedData.notif);
      Serial.print("\n");
    }
    if (header.from_node == 02) {
      Serial.print("node2");
      Serial.print("\t");
      Serial.print(receivedData.temperature);
      Serial.print("\t");
      Serial.print(receivedData.humidity);
      Serial.print("\t");
      Serial.print(receivedData.notif);
      Serial.print("\n");
    }
  }
}
