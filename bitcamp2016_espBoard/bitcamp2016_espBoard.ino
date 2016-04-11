#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
//////////////////////////////////////////////////////////////////
//Read in acceleraometer and save 60 sec of data and log event
//////////////////////////////////////////////////////////////////
const int user_id = 1;

//Analog read pins
const int xPin = A0;
const int yPin = 1;
const int zPin = 2;
int led = 13;
int button = 15;

int state = 0;

int DATA[50];
int runningavg10;
int runningavg5;
signed int avgdiff;
bool fall;

//to hold the caculated values
double x;
double y;
double z;

WiFiClient client;

void connectToWiFi()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin("TheyCallMeKing", "cheeseisking");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void sendData(bool emergency, bool fall, bool resolved)
{
  Serial.print("started to send data");
 if (client.connect("54.187.33.101", 8080))
  {
    //         client.print("GET /GuardianAPI/webresources/com.guardian.entitypackage.event?acceleration=");
    //    Serial.println(acceleration);
    Serial.println("Connected");
    String url = "/Event";
    /*
              Serial.println(url);

              client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + "54.187.33.101" + "\r\n" + "Connection: close\r\n\r\n");
           delay(10);

      // Read all the lines of the reply from server and print them to Serial
      Serial.println("Respond:");
      while(client.available()){
        String line = client.readStringUntil('\r');
        Serial.print(line);
      }*/
    String postStr = "heart_rate=";
       postStr += String(emergency);
       postStr += "&acceleration=";
       postStr += String(fall);
       postStr += "&resolved=";
       postStr += String(resolved);
       postStr += "&user_id=";
       postStr += String(user_id);
       postStr += "\r\n\r\n";

       Serial.println(postStr);
    //client.print(String("POST ") + url + " HTTP/1.1\r\n" + "Host: " + "54.187.33.101" + "\r\n" + "Connection: close\r\n\r\n");
    
    client.print("POST /Event HTTP/1.1\r\n");
    client.print("Host: 54.187.33.101\r\n");
    client.print("Connection: close\r\n");
    client.print("Content-Type: application/x-www-form-urlencoded\r\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\r\n\r\n");
    client.print(postStr);
    delay(400);

    Serial.println("Done");
  }

}

void blinkLED()
{
  if (digitalRead(led) == 1)
  {
    digitalWrite(led, LOW);
  }
  else if(digitalRead(led) == 0)
  {
    digitalWrite(led, HIGH);
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  client.connect("54.187.33.101", 8080);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT); //set the button pin as INPUT
}


void loop() {
  if (state == 0)
  {
    //read the analog values from the accelerometer
    int xRead = analogRead(xPin);
    //int yRead = analogRead(yPin);
    //int zRead = analogRead(zPin);
    for (int k = 49; k > 0; k--) {
      DATA[k] = DATA[k - 1];
    }
    DATA[0] = xRead;
    for (int k = 0; k < 10; k++) {
      runningavg10 = (runningavg10 * (k) + DATA[k]) / (k + 1);
    }
    for (int k = 0; k < 5; k++) {
      runningavg5 = (runningavg5 * (k) + DATA[k]) / (k + 1);
    }
    avgdiff = runningavg10 - runningavg5;
    if (avgdiff > 30) {
      fall = true;
      //digitalWrite(led, HIGH);
      //sendData(true, true, false);
      Serial.print("FALL DETECTED");
      Serial.print(" \n");
     
      runningavg10 = 0;
      runningavg5 = 0;
      for (int k = 49; k > 0; k--) {
        DATA[k] = 0;
      }
      
    }

    if (digitalRead(button) == 1)
    {
      digitalWrite(led, HIGH);
      state = 1;//read the state of the button
      delay(200);
      sendData(true, false, false);
    }
    if (fall == true)
    {
      digitalWrite(led, HIGH);
      state = 1;//read the state of the button
      delay(200);
      sendData(true, true, false);
    }
  }
  else if (state == 1) {
    blinkLED();
    int r = 0;
    int stateButton = digitalRead(button);
    for (int k = 0; k < 25; k++)
    {

      if (stateButton == 1) { //if is pressed
        r++;
      } else {
        r = 0;
      }
      delay(50);
      if (r == 24) {
        digitalWrite(led, LOW);
        state = 0;
        fall = false;
        sendData(false, false, true);
        delay(200);
        
      }
    }
  }
  Serial.println(state);
  delay(1);//just here to slow down the serial output - Easier to read

}
