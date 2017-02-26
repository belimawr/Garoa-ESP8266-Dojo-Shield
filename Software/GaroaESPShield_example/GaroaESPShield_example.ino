#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

/* Milliseconds / 10 */
#define TIMEOUT 5000/10

const char* ssid = "garoa";
const char* password = "";

WiFiServer webServer(80);

void setup() {
  Serial.begin(115200);
  delay(10);

  int pins[] = {D0, D1,D2, D3, D4, D5, D6, D7, D8};
  for (int i=0; i < 9; i++){
    pinMode(pins[i], OUTPUT);
	digitalWrite(pins[i], LOW);
  }

  /* WiFi Setup */
  Serial.print("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("\nWiFi connected, IP: ");
  Serial.println(WiFi.localIP());

  /*
   * Set up mDNS responder:
   * - first argument is the domain name, in this example
   *   the fully-qualified domain name is "garoaespshield.local"
   * - second argument is the IP address to advertise
   *   we send our IP address on the WiFi network
   */
  if (!MDNS.begin("garoaespshield")) {
    Serial.println("Error setting up MDNS responder!");
    while(1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  /* Web Server setup */
  Serial.println("Starting Web Server ...");
  webServer.begin();
  Serial.println("Server started");

  /* Add service to MDNS-SD */
  MDNS.addService("http", "tcp", 80);
}

void loop() {
  WiFiClient client = webServer.available();
  if (!client) {
    return;
  }

  /* Wait the client to send data */
  Serial.print("Client connected, waiting for data");
  unsigned int timeout = 0;
  while(!client.available()) {
    if (timeout++ == TIMEOUT) {
      client.stop();
      Serial.println("TIMEOUT!!!\nDisconnecting client\n");
      return;
    }
    delay(10);
    Serial.print(".");
  }
  Serial.println("\nData Available");

  /* Read the first line of the request */
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  /* Spliting 'String', source: http://arduino.stackexchange.com/a/1033 */
  const char* tokens;
  tokens = request.c_str();

  unsigned short int count = 0;
  const char* token;
  const char* method;
  const char* path;
  const char* protocol;
  token = strtok((char*)tokens, " ");
  /*
   * If it is a valid HTTP Request, the struct is:
   * METHOD PATH PROTOCOL
   */
  while(token != NULL) {
    switch (count++) {
    case 0:
      method = token;
      break;
    case 1:
      path = token;
      break;
    case 2:
      protocol = token;
      break;
    }
    Serial.print("Token: ");
    Serial.println(token);
    token = strtok(NULL, " ");
  }
  Serial.println("Split tokens");

  Serial.print("Method: ");
  Serial.println(method);

  Serial.print("Path: ");
  Serial.println(path);

  Serial.print("Protocol: ");
  Serial.println(protocol);

  String strPath = String(path);

  /* "Routing" the request. */
  if (strPath == "/") {
    index(client);
  } else  if (strPath == "/D0=HIGH") {
	digitalWrite(D0, HIGH);
    index(client);
  } else  if (strPath == "/D0=LOW") {
	digitalWrite(D0, LOW);
    index(client);
  } else  if (strPath == "/D1=HIGH") {
	digitalWrite(D1, HIGH);
    index(client);
  } else  if (strPath == "/D1=LOW") {
	digitalWrite(D1, LOW);
    index(client);
  } else  if (strPath == "/D2=HIGH") {
	digitalWrite(D2, HIGH);
    index(client);
  } else  if (strPath == "/D2=LOW") {
	digitalWrite(D2, LOW);
    index(client);
  } else  if (strPath == "/D3=HIGH") {
	digitalWrite(D3, HIGH);
    index(client);
  } else  if (strPath == "/D3=LOW") {
	digitalWrite(D3, LOW);
    index(client);
  } else  if (strPath == "/D4=HIGH") {
	digitalWrite(D4, HIGH);
    index(client);
  } else  if (strPath == "/D4=LOW") {
	digitalWrite(D4, LOW);
    index(client);
  } else  if (strPath == "/D5=HIGH") {
	digitalWrite(D5, HIGH);
    index(client);
  } else  if (strPath == "/D5=LOW") {
	digitalWrite(D5, LOW);
    index(client);
  } else  if (strPath == "/D6=HIGH") {
	digitalWrite(D6, HIGH);
    index(client);
  } else  if (strPath == "/D6=LOW") {
	digitalWrite(D6, LOW);
    index(client);
  } else  if (strPath == "/D7=HIGH") {
	digitalWrite(D7, HIGH);
    index(client);
  } else  if (strPath == "/D7=LOW") {
	digitalWrite(D7, LOW);
    index(client);
  } else {
    return404(client);
  }

  delay(1);
  client.stop();
  Serial.println("Client disonnected");
  Serial.println("");
}


void index(WiFiClient client) {
  Serial.println("Sending response....");

  /* HTTP Status line */
  client.println("HTTP/1.1 200 OK");

  /* HTTP Headers */
  client.println("Content-Type: text/html");

  /* Blank line after headers*/
  client.println("");

  /* Response Body */
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head> <title>Garoa ESP8266 Shield</title></head>");
  client.println("<body>");

  client.print("<h2>O que voce quer fazer?</h2>");

  client.println("<a href=\"/D0=HIGH\"\"><button>Liga Led D0</button></a><br>");
  client.println("<a href=\"/D0=LOW\"\"><button>Desliga Led D0</button></a><br><br>");

  client.println("<a href=\"/D1=HIGH\"\"><button>Liga Led D1</button></a><br>");
  client.println("<a href=\"/D1=LOW\"\"><button>Desliga Led D1</button></a><br><br>");

  client.println("<a href=\"/D2=HIGH\"\"><button>Liga Led D2</button></a><br>");
  client.println("<a href=\"/D2=LOW\"\"><button>Desliga Led D2</button></a><br><br>");

  client.println("<a href=\"/D3=HIGH\"\"><button>Liga Led D3</button></a><br>");
  client.println("<a href=\"/D3=LOW\"\"><button>Desliga Led D3</button></a><br><br>");

  client.println("<a href=\"/D4=HIGH\"\"><button>Liga Led D4</button></a><br>");
  client.println("<a href=\"/D4=LOW\"\"><button>Desliga Led D4</button></a><br><br>");

  client.println("<a href=\"/D5=HIGH\"\"><button>Liga Led D5</button></a><br>");
  client.println("<a href=\"/D5=LOW\"\"><button>Desliga Led D5</button></a><br><br>");

  client.println("<a href=\"/D6=HIGH\"\"><button>Liga Led D6</button></a><br>");
  client.println("<a href=\"/D6=LOW\"\"><button>Desliga Led D6</button></a><br><br>");

  client.println("<a href=\"/D7=HIGH\"\"><button>Liga Led D7</button></a><br>");
  client.println("<a href=\"/D7=LOW\"\"><button>Desliga Led D7</button></a><br><br>");

  client.println("</body></html>");
}

void return404(WiFiClient client) {
  Serial.println("Sending response....");
  /* HTTP Status line */
  client.println("HTTP/1.1 404 Not Found");

  /* HTTP Headers */
  client.println("Content-Type: text/html");

  /* Blank line after headers*/
  client.println("");

  /* Response Body */
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head> <title>Garoa ESP8266 Shield</title></head>");
  client.println("<body>");

  client.println("<p><h1>404 - Página não encontrada</h1></p>");

  client.println("<a href=\"\\\">Retornar para a Home</a>");
  client.println("</p>");

  client.println("</body></html>");
}
