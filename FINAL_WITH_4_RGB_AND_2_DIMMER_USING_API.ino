#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define LED_RED1   12
#define PWM1_RED1    0
#define LED_GREEN1   13
#define PWM1_GREEN1    1
#define LED_BLUE1   14
#define PWM1_BLUE1    2

#define LED_RED2  25
#define PWM1_RED2    3
#define LED_GREEN2   26
#define PWM1_GREEN2    4
#define LED_BLUE2   27
#define PWM1_BLUE2    5

#define LED_RED3   32
#define PWM1_RED3    6
#define LED_GREEN3   33
#define PWM1_GREEN3    7
#define LED_BLUE3   19
#define PWM1_BLUE3   8

#define LED_RED4   2
#define PWM1_RED4   9
#define LED_GREEN4   4
#define PWM1_GREEN4    10
#define LED_BLUE4   21
#define PWM1_BLUE4   11

#define LED_DIMMER1   22
#define PWM1_DIMMER1   12
#define LED_DIMMER2   23
#define PWM1_DIMMER2    13

#define PWM1_Res   8
#define PWM1_Freq  1000

int PWM1_DutyCycleR1 = 0;
int PWM1_DutyCycleG1 = 0;
int PWM1_DutyCycleB1 = 0;

int PWM1_DutyCycleR2 = 0;
int PWM1_DutyCycleG2 = 0;
int PWM1_DutyCycleB2 = 0;

int PWM1_DutyCycleR3 = 0;
int PWM1_DutyCycleG3 = 0;
int PWM1_DutyCycleB3 = 0;

int PWM1_DutyCycleR4 = 0;
int PWM1_DutyCycleG4 = 0;
int PWM1_DutyCycleB4 = 0;

int PWM1_DutyCycleD1 = 0;
int PWM1_DutyCycleD2 = 0;

int id;
const char* device_name;
int red, green, blue;


const char* ssid = "PLATFORUMA";
const char* password = "chetna@123";
String serverName = "https://ibsbus.herokuapp.com/rgbapi/rgb/";
unsigned long lastTime = 0;

// Set timer to 5 seconds (5000)
unsigned long timerDelay = 1000;
void setup() {
  ledcAttachPin(LED_RED1, PWM1_RED1);
  ledcSetup(PWM1_RED1, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_GREEN1, PWM1_GREEN1);
  ledcSetup(PWM1_GREEN1, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_BLUE1, PWM1_BLUE1);
  ledcSetup(PWM1_BLUE1, PWM1_Freq, PWM1_Res);

  ledcAttachPin(LED_RED2, PWM1_RED2);
  ledcSetup(PWM1_RED2, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_GREEN2, PWM1_GREEN2);
  ledcSetup(PWM1_GREEN2, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_BLUE2, PWM1_BLUE2);
  ledcSetup(PWM1_BLUE2, PWM1_Freq, PWM1_Res);

  ledcAttachPin(LED_RED3, PWM1_RED3);
  ledcSetup(PWM1_RED3, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_GREEN3, PWM1_GREEN3);
  ledcSetup(PWM1_GREEN3, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_BLUE3, PWM1_BLUE3);
  ledcSetup(PWM1_BLUE3, PWM1_Freq, PWM1_Res);

  ledcAttachPin(LED_RED4, PWM1_RED4);
  ledcSetup(PWM1_RED4, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_GREEN4, PWM1_GREEN4);
  ledcSetup(PWM1_GREEN4, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_BLUE4, PWM1_BLUE4);
  ledcSetup(PWM1_BLUE4, PWM1_Freq, PWM1_Res);

  ledcAttachPin(LED_DIMMER1, PWM1_DIMMER1);
  ledcSetup(PWM1_DIMMER1, PWM1_Freq, PWM1_Res);
  ledcAttachPin(LED_DIMMER2, PWM1_DIMMER2);
  ledcSetup(PWM1_DIMMER2, PWM1_Freq, PWM1_Res);

  Serial.begin(115200); WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  StaticJsonDocument<1200> doc;
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      String serverPath = serverName;
      http.begin(serverPath.c_str());
      int httpResponseCode = http.GET();

      if (httpResponseCode > 0) {
        String payload = http.getString();
        Serial.println(payload);

        DeserializationError error = deserializeJson(doc, payload);

        if (error) {
          Serial.print("deserializeJson() failed: ");
          Serial.println(error.c_str());
          return;
        }
        for (JsonObject root_0 : doc.as<JsonArray>())
        {
          //       JsonObject root_0 = doc[0];
          id = root_0["id"]; // 1,2,3,4,5,6
          device_name = root_0["device_name"]; //RGB1,RGB2,RGB3,RGB4,dimmer1,dimmer2
          red = root_0["red"]; // 0
          green = root_0["green"]; //0
          blue = root_0["blue"]; // 0


          //Serial.println(device_name);
          //Serial.println(red);
          //Serial.println(green);
          //Serial.println(blue);


          if (id == 1) {
            
            PWM1_DutyCycleR1 = red;
            PWM1_DutyCycleG1 = blue;
            PWM1_DutyCycleB1 = green;

            ledcWrite(PWM1_RED1, PWM1_DutyCycleR1);
            ledcWrite(PWM1_GREEN1, PWM1_DutyCycleG1);
            ledcWrite(PWM1_BLUE1, PWM1_DutyCycleB1);
          }
          else if (id == 2) {
            
            PWM1_DutyCycleR2 = red;
            PWM1_DutyCycleG2 = green;
            PWM1_DutyCycleB2 = blue;

            ledcWrite(PWM1_RED2, PWM1_DutyCycleR2);
            ledcWrite(PWM1_GREEN2, PWM1_DutyCycleG2);
            ledcWrite(PWM1_BLUE2, PWM1_DutyCycleB2);
          }
          else if (id == 3) {
           
            PWM1_DutyCycleR3 = red;
            PWM1_DutyCycleG3 = green;
            PWM1_DutyCycleB3 = blue;

            ledcWrite(PWM1_RED3, PWM1_DutyCycleR3);
            ledcWrite(PWM1_GREEN3, PWM1_DutyCycleG3);
            ledcWrite(PWM1_BLUE3, PWM1_DutyCycleB3);
          }
          else  if (id == 4) {
           
            PWM1_DutyCycleR4 = red;
            PWM1_DutyCycleG4 = green;
            PWM1_DutyCycleB4 = blue;

            ledcWrite(PWM1_RED4, PWM1_DutyCycleR4);
            ledcWrite(PWM1_GREEN4, PWM1_DutyCycleG4);
            ledcWrite(PWM1_BLUE4, PWM1_DutyCycleB4);
          }
          else if(id==5)
          {
              PWM1_DutyCycleD1 = red;
              ledcWrite(PWM1_DIMMER1, PWM1_DutyCycleD1);
            }
            else if(id==6)
          {
              PWM1_DutyCycleD2 = red;
              ledcWrite(PWM1_DIMMER2, PWM1_DutyCycleD2);
            }
        }

      }
    }

  }
}
