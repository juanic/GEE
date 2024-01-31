/*------------------------------------------------------------------------
Raspberry Pi Pico pin                 Device
GP0 - TX                              RX - Thermal Printer
GP6 - GPIO Input                      Switch
GP14 - GPIO Output                    Buzzer
GP2 - GPIO Output                     Led
  ------------------------------------------------------------------------*/

#include "Adafruit_Thermal.h"
#include "excusasFH.h"
#include "excusasPM.h"
#include "excusasP.h"
#include "excusas_fun.h"
#include "StringSplitter.h"


#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "********" //Add WiFI to use OTA 
#define STAPSK  "********" //Add WiFI to use OTA 
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int pinBuzzer = 14; //Constante que contiene el numero del pin de Arduino al cual conectamos un buzzer pasivo

const int frecuencias[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 1000};
const int numFrecuencias = 11;

#define SWICTH       6    // GPIO6   PIN9   SWICTH
#define LED          2    // GPIO2   PIN9   LED


#define use_thermal

Adafruit_Thermal printer(&Serial1);      // Or Serial2, Serial3, etc.
int first, second, third, forth, fifth;
char buffer[40];
enum{FUN, SERIOUS};
uint8_t excuse_type = FUN;
// -----------------------------------------------------------------------


long sw_time_now;
long sw_time_before;

String myString;
char buf[100];
const int potPin = 26;

unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

void printCol(const char* s, const size_t nbCol = 32)
{
  char tmpBuffer[nbCol + 1];
  tmpBuffer[nbCol] = '\0'; // ensure null terminated C string

  size_t len = strlen(s);
  size_t pos = 0;
  Serial.println(s);
  while (pos < len) {
    strncpy(tmpBuffer, &(s[pos]), nbCol);
    char * lastSpace = strrchr(tmpBuffer, ' ');
    if (strlen(tmpBuffer) >= nbCol) {
      if (lastSpace) {
        *lastSpace = '\0';
        pos++; // +1 to start after the space
      }
    }
    pos += strlen(tmpBuffer);
    char * skipStartingSpace = tmpBuffer;
    while (*skipStartingSpace == ' ') skipStartingSpace++;
    #ifdef use_thermal
    printer.println(skipStartingSpace);
    #endif
  }
}

void technicalExcuse(void){

 printer.setFont('A');
 printer.justify('C');
 printer.setSize('M');        // Set type size, accepts 'S', 'M', 'L'
 switch(excuse_type){
  case FUN:
    printCol(excusas_fun[random(0,69)].c_str(), 32);
    excuse_type = SERIOUS;
  break;
  case SERIOUS:
    printCol(excusas_firmware_hardware[random(0,78)].c_str(), 32);
    excuse_type = FUN;
  break;
 }
 #ifdef use_thermal
 printer.feed(1);
 printer.setSize('S');
 printer.println("Generado por ChatGPT");
 printer.feed(1);
 printer.inverseOn();
 printer.println("---Destruya luego de usar---");
 printer.inverseOff();
 printer.feed(2);
  #endif
}

void projectManagerExcuse(void){

 printer.setFont('A');
 printer.justify('C');
 printer.setSize('M');        // Set type size, accepts 'S', 'M', 'L'
 
 printCol(excusas[random(0,82)].c_str(), 32);
 #ifdef use_thermal
 printer.feed(2);
 printer.setSize('S');
 printer.println("Generado por ChatGPT");
 printer.feed(1);
 printer.inverseOn();
 printer.println("---Destruya luego de usar---");
 printer.inverseOff();
 printer.feed(2);
#endif
}


void peñaExcuse(void){

 printer.setFont('A');
 printer.justify('C');
 printer.setSize('M');        // Set type size, accepts 'S', 'M', 'L'

 String sub_S = excusas[random(0,95)];
 Serial.println(sub_S);
 StringSplitter *splitter = new StringSplitter(sub_S, ' ', 10);  // new StringSplitter(string_to_split, delimiter, limit)
 int itemCount = splitter->getItemCount();
 //Serial.println("Item count: " + String(itemCount));
 int char_count=0; 
 for(int i = 0; i < 4; i++){
    String item = splitter->getItemAtIndex(i);
    //Serial.println("Item @ index " + String(i) + ": " + String(item));
    char_count+=item.length();
    char_count+=1;
    //Serial.println(char_count);
  }
  
 String cut_S = sub_S.substring(0, char_count);

 String str_printer = cut_S + excusasPeña[random(0,5)];

 Serial.println(str_printer);
#ifdef use_thermal
 printCol(str_printer.c_str(), 32);
 printer.feed(2);
 printer.setSize('S');
 printer.println("Generado por PeniaGPT");
 printer.feed(1);
 printer.inverseOn();
 printer.println("---Destruya luego de usar---");
 printer.inverseOff();
 printer.feed(2);
#endif
}

void readSwitch(void){
 tone(pinBuzzer, frecuencias[11]);
 delay(100);
 noTone(pinBuzzer);
 Serial.println("Button pressed...");
 pressedTime = millis();
 while(!digitalRead(SWICTH)){
  if(((millis()-pressedTime) > 1000)  && ((millis()-pressedTime) < 1100)){
      digitalWrite(LED, LOW);
      tone(pinBuzzer, frecuencias[5]);
      delay(100);
      digitalWrite(LED, HIGH);
      tone(pinBuzzer, frecuencias[9]);
      delay(100);
      digitalWrite(LED, LOW);
      tone(pinBuzzer, frecuencias[2]);
      delay(100);
      digitalWrite(LED, HIGH);
      noTone(pinBuzzer);
    }
   if(((millis()-pressedTime) > 5000)  && ((millis()-pressedTime) < 5100)){
      digitalWrite(LED, LOW);
      tone(pinBuzzer, frecuencias[11]);
      delay(100);
      digitalWrite(LED, HIGH);
      tone(pinBuzzer, frecuencias[2]);
      delay(100);
      digitalWrite(LED, LOW);
      tone(pinBuzzer, frecuencias[10]);
      delay(100);
      digitalWrite(LED, HIGH);
      tone(pinBuzzer, frecuencias[4]);
      delay(100);
      digitalWrite(LED, LOW);
      tone(pinBuzzer, frecuencias[9]);
      delay(100);
      digitalWrite(LED, HIGH);
      noTone(pinBuzzer);
    }
  }

  
 releasedTime = millis();

 long pressDuration = releasedTime - pressedTime;
 if((pressDuration>1000) && (pressDuration<5000)){
   projectManagerExcuse();
  }
 if(pressDuration<1000){
  tone(pinBuzzer, frecuencias[3]);
  delay(100);
  noTone(pinBuzzer);
  technicalExcuse();
  } 
if(pressDuration>5000){
   peñaExcuse();
  }
 
 //printer.sleep();      // Tell printer to sleep
}




void setup() {

  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
     for (int i = 0; i < 10; i++)
      {
       tone(pinBuzzer, frecuencias[2]);
        delay(150);
       tone(pinBuzzer, frecuencias[10]);
        delay(150); 
      }
  noTone(pinBuzzer);
    delay(5000);
    rp2040.restart();
  }

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  
  pinMode(SWICTH, INPUT_PULLUP);
  //attachInterrupt(digitalPinToInterrupt(SWICTH), readSwitch, FALLING);
  randomSeed(analogRead(potPin));
  pinMode(LED, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(LED, HIGH);
  Serial1.begin(9600); // Use this instead if using hardware serial
  //Serial.begin(115200);
  printer.begin();        // Init printer (same regardless of serial type)

  for (int i = 0; i < numFrecuencias; i++)
  {
   tone(pinBuzzer, frecuencias[i]);
   delay(150);
  }
  noTone(pinBuzzer);
}

void loop() {
    ArduinoOTA.handle();
    if(!digitalRead(SWICTH)){
      readSwitch();
    }
}
