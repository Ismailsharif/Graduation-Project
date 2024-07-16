#define BLYNK_TEMPLATE_ID "TMPL2ktL8SxMi"
#define BLYNK_TEMPLATE_NAME "IOT based Flood monitoring and alerting system"
#define BLYNK_AUTH_TOKEN "H_3m_CxaFKqoWE1HywRwETVN0B6ZHtY_"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h> // need to install
LiquidCrystal_I2C lcd(0x27, 16,2); // 0x27 is the i2c address might different;you can check with Scanner

#define  trig  D5
#define  echo  D6

long duration;
int distance;

#define relay D7
#define  greenLed D3
#define  redled D4
#define  buzzer D8

// You should get Auth Token in the Blynk App.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "isma";   // your ssid 
char pass[] = "simad123"; // your pass

BlynkTimer timer;
#define VPIN_BUTTON_1    V4


void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Inpu
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

    lcd.begin();
//  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Float Detection");
 pinMode(relay,OUTPUT);
 pinMode(redled,OUTPUT);
 pinMode(greenLed,OUTPUT);
 pinMode(buzzer,OUTPUT);

  // Setup a function to be called every second
  timer.setInterval(100L, LevalSen);
  timer.setInterval(100L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay

  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  
  Blynk.virtualWrite(V0, distance); 


  if(distance>=15 && distance<25){
  //digitalWrite(relay,HIGH);
  digitalWrite(greenLed,HIGH);
  digitalWrite(redled,LOW);
    lcd.setCursor(0,1);
  lcd.print("F: LOW  ");
  digitalWrite(buzzer,LOW);
delay(100);
}// O %

else if(distance<=15 && distance>=6){
    digitalWrite(greenLed,HIGH);
   digitalWrite(redled,LOW);
     digitalWrite(buzzer,LOW);
    lcd.setCursor(0,1);
  lcd.print("F:Mediun");
 delay(100);
}//40%

 else if(distance>=2 &&  distance<6 ){
  digitalWrite(relay,LOW);
    digitalWrite(greenLed,LOW);
   digitalWrite(redled,HIGH);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,1);
     lcd.print("F: HIGH  ");
  delay(100);

}//100%

else{
    lcd.setCursor(0,1);
  lcd.print(" WELL ");
  digitalWrite(greenLed,HIGH);
   digitalWrite(redled,LOW);
     digitalWrite(buzzer,LOW); 
}
}

void LevalSen(){
     int value = analogRead(A0);
     Blynk.virtualWrite(V1, value);
   lcd.setCursor(9,1);
  lcd.print("Lev ");
  lcd.setCursor(13,1);
  lcd.print(value);

}

BLYNK_WRITE(VPIN_BUTTON_1) {
  int toggleState_1 = param.asInt();
  if(toggleState_1 == 1){
    digitalWrite(relay, HIGH);
   // Blynk.virtualWrite(V1, HIGH);    
  }
  else { 
    digitalWrite(relay, LOW);
   // Blynk.virtualWrite(V1, LOW);
  }
}