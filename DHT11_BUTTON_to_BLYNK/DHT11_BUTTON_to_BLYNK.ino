#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <dht11.h>
dht11 DHT11;

BlynkTimer timer;
WidgetLCD BLYNK_LCD(V0); 
int t,h;
char auth[] = "9eP97Lo7yeHfXP5zrARqgIIq6V14MQ9H";//rediff rajesh
//char auth[] = "8507cac915f04a1bb4b00987e420afa0";//rajesh
char ssid[] = "ESPServer_RAJ";
char pass[] = "RAJ@12345";
int BULB=D1;//D6
int FAN=D2;///
BLYNK_WRITE(V1)
{
  int BULB_VAL = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(BULB_VAL==HIGH)
  {
    //lcd.clear();
    digitalWrite(BULB,HIGH);
    digitalWrite(FAN,LOW);
    BLYNK_LCD.print(0,1,"BULB ON ");
    delay(10);
    }
   else
   {
    //lcd.clear();
    digitalWrite(BULB,LOW);
    digitalWrite(FAN,LOW);
    BLYNK_LCD.print(0,1,"BULB OFF");
    delay(10); 
    }
    
}

BLYNK_WRITE(V2)
{
  int FAN_VAL = param.asInt(); // assigning incoming value from pin V1 to a variable
  if(FAN_VAL==HIGH)
  {
   // lcd.clear();
    digitalWrite(BULB,LOW);
    digitalWrite(FAN,HIGH);
    BLYNK_LCD.print(0,1,"FAN ON  ");
    delay(10);
   }
   else
   {
   // lcd.clear();
    digitalWrite(BULB,LOW);
    digitalWrite(FAN,LOW);
    BLYNK_LCD.print(0,1,"FAN OFF");
    delay(10); 
    }
 }

void READ_SENSOR()
{
  int chk = DHT11.read();
  t=DHT11.temperature;
  h=DHT11.humidity;
  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V4, h);
  BLYNK_LCD.print(0,0,"T:");
  BLYNK_LCD.print(2,0,t);
  BLYNK_LCD.print(9,0,"H:");
  BLYNK_LCD.print(11,0,h);
}

void setup()
{
  Serial.begin(9600);
 // lcd.begin(20, 4);
  DHT11.attach(D5);
  Blynk.begin(auth, ssid, pass);
  pinMode(BULB,OUTPUT);//D6 pin of NodeMCU
  pinMode(FAN,OUTPUT);//D7 pin of NodeMCU
  timer.setInterval(1000L,READ_SENSOR);//// change
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
