
#include <MFRC522.h>

#include <SPI.h>

#define PINO_RST 9

#define PINO_SDA 10
 
MFRC522 rfid(PINO_SDA, PINO_RST);
 
void setup() 

{

  Serial.begin(9600);
 
  SPI.begin();      

  rfid.PCD_Init();

  Serial.println("Aproxime a sua tag...");

  Serial.println();

}
 
void loop() 

{

  if (!rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }


  if (!rfid.PICC_ReadCardSerial()) 
  {
    return;
  }


  String conteudo= "";
 
  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " ")); 
     conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
  }
 
  Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "a9 f6 00 98") //UID 1 - Chaveiro
  {
    Serial.println("Chaveiro");
  }

  else if (conteudo.substring(1) == "35 61 23 20") //UID 2 - Cartao
  {
    Serial.println("Cartão");
  }

  else
  {
    Serial.println("Não registrada");
  }
}