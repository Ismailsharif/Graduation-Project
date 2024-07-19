#define BLYNK_TEMPLATE_ID "TMPL2vl75P_4r"
#define BLYNK_TEMPLATE_NAME "Flood Monitoring and Alerting System"
#define BLYNK_AUTH_TOKEN "FSZzs9tNK7ULYPSCJIurPR_92ijdJCx7"

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
#define relay2 D0
#define  greenLed D3
#define  redled D4
#define  buzzer D8

// You should get Auth Token in the Blynk App.
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Isma";   // your ssid 
char pass[] = "Simad123"; // your pass

BlynkTimer timer;

#define VPIN_BUTTON_1    V4

BLYNK_WRITE(VPIN_BUTTON_1) {
  int toggleState_1 = param.asInt();
  if(toggleState_1 == 1){
digitalWrite(relay,LOW);
  }
  else { 
digitalWrite(relay,HIGH);
  }
}


void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Inpu
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

   lcd.init();  
//  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Flood Monitoring");
 pinMode(relay,OUTPUT);
 pinMode(relay2,OUTPUT);
 pinMode(redled,OUTPUT);
 pinMode(greenLed,OUTPUT);
 pinMode(buzzer,OUTPUT);
digitalWrite(relay,HIGH);
  // Setup a function to be called every second
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


  if(distance<=18 && distance>=14){
  digitalWrite(greenLed,HIGH);
  digitalWrite(redled,LOW);
    lcd.setCursor(0,1);
  lcd.print("0%");
  digitalWrite(buzzer,LOW);
delay(100);
}// O %

else if(distance<=13 && distance>=10){
    digitalWrite(greenLed,HIGH);
   digitalWrite(redled,LOW);
     digitalWrite(buzzer,LOW);
    lcd.setCursor(0,1);
    lcd.print("50%");
 delay(100);
}//40%

 else if(distance<=9 &&  distance>=6 ){
    digitalWrite(greenLed,LOW);
   digitalWrite(redled,HIGH);
    digitalWrite(buzzer,HIGH);
    lcd.setCursor(0,1);
  lcd.print("100%");
  delay(100);
digitalWrite(relay2,LOW);

}//100%

else{
    lcd.setCursor(0,1);
  lcd.print("    ") ;
  digitalWrite(greenLed,HIGH);
   digitalWrite(redled,LOW);
     digitalWrite(buzzer,HIGH); 
     digitalWrite(relay2,HIGH);
}
}
