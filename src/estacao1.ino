#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>  //biblioteca do relogio

// Pino conectado ao pino de dados do sensor
#define DHTPIN 5
#define DHTTYPE DHT22   // Sensor DHT 22  (AM2302)

LiquidCrystal_I2C lcd(0x27,16,2);

DHT dht(DHTPIN, DHTTYPE);

RTC_DS1307 RTC;

void setup()
{

  Serial.begin(9600);
  Serial.println("Iniciando medições...");

  dht.begin();//aew
  RTC.begin();

  if (! RTC.isrunning()) {
	  	Serial.println("RTC não funcionando!");
	   	//Ajusta a data/hora do Clock com a data/hora em que o codigo foi compilado, basta descomentar a linha
	   	RTC.adjust(DateTime(__DATE__, __TIME__));
	}

  lcd.init();
  lcd.backlight();

}

void loop()
{

  // Aguarda 2 segundos entre as medicoes
  delay(1000);

  // Leitura da umidade
  float h = dht.readHumidity();
  // Leitura da temperatura (Celsius)
  float t = dht.readTemperature();

  // Verifica se o sensor esta respondendo
  if (isnan(h) || isnan(t))
  {
    Serial.println("Falha ao ler dados do sensor DHT !!!");
    return;
  }

  DateTime tempo = RTC.now();//instancia do rtc, recupera a data e hora atual

  int hora    = tempo.hour();
  int minuto  = tempo.minute();
  int dia     = tempo.day();
  int mes     = tempo.month();
  int ano     = tempo.year();

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(t);

  lcd.print(" U:");
  lcd.print(h);
  lcd.print("%");

  lcd.setCursor(0,1);
  lcd.print(hora);
  lcd.print(":");
  lcd.print(minuto);

  lcd.setCursor(6,1);
  lcd.print(dia);
  lcd.print("-");
  lcd.print(mes);
  lcd.print("-");
  lcd.print(ano);



}
