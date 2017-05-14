#include<dht.h>
#include<SoftwareSerial.h>
SoftwareSerial mySerial(9,10);//RX,TX
dht DHT
#define DHT11_PIN 3
#define echopin 5 //echo pin
#define trigpin 4//Trigger pin
const int MOISTURE = 0;
const int THRESHHOLD = 750;
int maximumRange = 55;
long duration, distance;
void setup()
{
mySerial.begin(9600);
Serial.begin(9600);
pinMode(13,OUTPUT);
pinMode(7,OUTPUT);
pinMode(echopin,INPUT);
}
void LedState(int state)
{
digitalWrite(13,state);
}
void loop()
{
digitalWrite(trigpin,LOW);
delayMicroseconds(2);
digitalWrite(trigpin,HIGH);
distance= duration/58.2;
delay(20);
Serial.println("Distance from the brim");
Serial.println(distance);
int chk=DHT.read11(DHT11_PIN);
Serial.println("Humidity");
Serial.println(DHT.humidity);
Serial.println("Temperature");
Serial.println(DHT.tempreature);
int moisture = analogRead(MOISTURE);
Serial.print("Moisture = ");
Serial.println(moisture);
if(moisture>THRESHHOLD)
{
	digitalWrite(7,HIGH);
	SendMessage1();

}
else
{
	digitWrite(7,LOW);
}
if(distance>=25)
{
	Serial.println("Going to be empty");
	LedState(HIGH);
	SendMessage2();
}
else if(distance <=10)
{
Serial.println("More than half filled");
LedState(LOW);
}
delay(2000);
}
}
void SendMessage1()
{
	mySerial.println("AT+CMGF=1");	
	mySerial.println("AT+CMGF=1"); //Set the GSM Module in Text Mode
	delay(1000);
	mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); //Replace x with mobile number
	delay(1000);
	mySerial.println("Moisture is low");//the SMS text you want to send
	delay(100);
	mySerial.println((char)26);// ASCII code of CTRL+Z
	delay(100);
}
void SendMessage2()
{
	mySerial.println("AY+CMGF=1");
	mySerial.println("AT+CMFG=1"); //Sets the GSM MOdule in Text-Mode
	delay(1000);
	mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); //Replace x with mobile number
	delay(1000);
	mySerial("Reservoir going to be empty - Please refill"); // The SMS text you want to send
	delay(100);
	mySerial.println((char)26)://ASCII code of CTRL+Z
	delay(1000);
}
	


