<h1 align="center">MedicineNow</h1>
<p align="center">A MedicineNow é uma inovadora plataforma que visa conectar farmácias locais, proporcionando uma maneira eficiente e segura de enviar prescrições médicas eletronicamente.</p>

<img alt="Imagem de apresentação do projeto da medicinenow" src="assets/medicinenow.jpg" width="100%">

### 🎯 Objetivo:

Tornar o processo de distribuição de medicamentos mais seguro e conveniente.
<br /> <br />

### 🧾 Descriçao detalhada:

Plataforma conecta farmácias, enviando prescrições eletrônicas. Cofres inteligentes em locais estratégicos garantem segurança na retirada. Parcerias com farmácias locais reduzem custos. Identificação biométrica e QR code garantem usabilidade. Impacto positivo: redução de roubos, acesso facilitado a medicamentos em áreas remotas. Campanhas de conscientização e monitoramento remoto garantem eficiência. Inovação na descentralização da distribuição, tornando o processo seguro e acessível.

### ⚙️ Tecnologias:

- Arduino
- RFID
- Node-Red
  <br /> <br />

### 🛠️ Esquemas Eletrônicos:

- Protoboard
- Arduino
- Cabo Jumper Macho x Macho
- Cabo USB para arduino
- RFID
  <br /> <br />

### 🔴 Fluxos do Node-RED

- Serial In (COM5)
- FUNCTION
- DEBUG
  <br /> <br />

### 📂 Como rodar o projeto:

### Passo 1. Conectar o Arduino no computador através de um cabo USB

### Passo 2. Copiar o codigo para o aplicativo do Arduino

```
#include <MFRC522.h>
#include <SPI.h>
#define PINO_RST 9
#define PINO_SDA 10

MFRC522 rfid(PINO_SDA, PINO_RST);
void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Aproxime a sua tag...");
  Serial.println();
}

void loop() {
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
```

### Passo 3. Upload e execução do código

### Passo 4. Iniciar o Node-Red através dos comandos

```
npm install -g --unsafe-perm node-red
node-red
```

### Passo 5. Configurar o fluxo do Node-Red

#### 5.1 - Adicionar no fluxo o Serial In na mesma porta usada no arduino (COM5)

#### 5.2 - Configurar o Baud Rate em 9600

#### 5.3 - Adicionar uma function no fluxo do Node-Red

#### 5.4 - Configurar a function com o seguinte código

```
if(msg.hasOwnProperty("payload")){
  let conteudo = msg.payload.trim();

  if (conteudo === "UID RFID: Chaveiro") {
    msg.payload = "Chaveiro identificado";
  } else if (conteudo === UID RFID: Cartão) {
    msg.payload = Cartao identificado";
  } else {
      msg.payload = "Tag não reconhecida";
  }
return msg;
}
```

#### 5.5 - Adicionar o debug no fluxo do Node-Red

#### 5.6 - Interligar o SerialIn na function e no debug

#### 6 - Dar deploy no projeto e testar :)
