//library yang dibutuhkan
#include <SPI.h>
#include <RF24.h>
#include <RF24Network.h>
#include <DHT.h>

//sensor DHT
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//pin untuk humidifier
int sprayer = 6;

//Radio
RF24 radio(9, 10);
RF24Network network(radio);

//Pengalamatan (format oktal)
//const uint16_t alamatNodeIni = 01;
const uint16_t alamatNodeIni = 02;
const uint16_t alamatBaseNode = 00;

//Jeda
const unsigned long jedaPengiriman = 1000;
unsigned long waktuPengirimanTerakhir;
//____________________________________________________________________________________________________________________________________________________________________

//variabel penampung data
struct data {
  float suhu;
  float kelembaban;
  char notif[4];
} kirimData;
//____________________________________________________________________________________________________________________________________________________________________

//setup
void setup(void) {
  pinMode(sprayer, OUTPUT);
  dht.begin();
  Serial.begin(9600);
  if (!Serial) {
    Serial.println("serial tidak bekerja");
  }
  Serial.println("Mengirim data ... ");
  if (!radio.begin()) {
    Serial.println("radio tidak bekerja");
    while (1) {
      Serial.println("cek modul nrf nya");
    }
  }
  network.begin(90, alamatNodeIni); //channel dan alamat node ini
}

//loop
void loop() {
  network.update();
  unsigned long waktuSekarang = millis();
  if ( waktuSekarang - waktuPengirimanTerakhir >= jedaPengiriman) {
    waktuPengirimanTerakhir = waktuSekarang;

    //suhu dan kelembaban dimasukkan ke dalam struct
    kirimData.suhu = dht.readTemperature();
    kirimData.kelembaban = dht.readHumidity();

    //menyalakan dan mematikan humidifier
    if (kirimData.kelembaban < 80) {
      digitalWrite(sprayer, LOW);
      strcpy(kirimData.notif, "on");
    } else {
      digitalWrite(sprayer, HIGH);
      strcpy(kirimData.notif, "off");
    }

    //Kirim data ke base node
    RF24NetworkHeader header(alamatBaseNode);
    bool ok = network.write(header, &kirimData, sizeof(kirimData));

    if (ok) {
      Serial.println("data yang dikirim adalah : ");
      Serial.println(kirimData.suhu);
      Serial.println(kirimData.kelembaban);
      Serial.println(kirimData.notif);
    }
    else {
      Serial.println("data gagal dikirimkan");
    }
  }
}
