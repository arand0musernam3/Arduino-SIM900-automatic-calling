#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM900
SoftwareSerial SIM900(7, 8); //SIM900 Tx & Rx is connected to Arduino #7 & #8

const int CONTACTE = 2; // digital pin where the switch is connected (normally closed)

int val = 0;

bool trucat = false;

void inicialitzacio_sim900() {
  
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM900
  SIM900.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  SIM900.println("AT"); //Handshaking with SIM900
  updateSerial();
  SIM900.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
  updateSerial();
  SIM900.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
  updateSerial();
  SIM900.println("AT+CREG?"); //Check whether it has registered in the network
  updateSerial();
  SIM900.println("AT+CLIP=1"); //ACTIVATING CALL RECEPTION MESSAGE
  updateSerial();
  SIM900.println("AT+MORING=1"); //ACTIVATING MORE DEBUGGING MESSAGES
  updateSerial();

  
  delay(1000);
}

void calls() {

  
  SIM900.println("ATD+ +XXxxxxxxxxx;"); //trucar a xxx
  updateSerial();
  delay(25000);

  SIM900.println("ATH"); //hang up after 10 seconds
  updateSerial();
  delay(2000); // 2 seconds between calls

  
  SIM900.println("ATD+ +XXxxxxxxxxx;"); //trucar a xxx
  updateSerial();
  delay(25000);
  
  SIM900.println("ATH"); //hang up after 10 seconds
  updateSerial();
  delay(2000); // 2 seconds between calls

  
  SIM900.println("ATD+ +XXxxxxxxxxx;"); //trucar a xxx
  updateSerial();
  delay(25000);
  
  SIM900.println("ATH"); //hang up after 10 seconds
  updateSerial();
  delay(2000); // 2 seconds between calls
  
}


void setup()
{
  //CONTACTE DE PROVA

  pinMode (CONTACTE, INPUT);

  delay(30000); //30 seconds delay in order to manually turn SIM900 on

  
  inicialitzacio_sim900();

}

void loop()
{
  val = digitalRead(CONTACTE); //READ CONTACT VALUE TO START CALLING IF OPEN

  if (val == LOW) { // LOW == OPEN
    if (!trucat) {
      calls();
    }
    trucat = true; //we set a global variable to true so that it won't call again
  }
  
  updateSerial();
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    SIM900.write(Serial.read()); //Forward what Serial received to Software Serial Port
  }
  while(SIM900.available()) 
  {
    Serial.write(SIM900.read()); //Forward what Software Serial received to Serial Port
  }
}
