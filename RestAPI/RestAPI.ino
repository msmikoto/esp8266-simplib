#include "RestAPI.h"


const char* ssid = "Your Wifi SSID";
const char* passwd = "Your WiFi password";
RestAPI restAPI = RestAPI(ssid,passwd);


const char* host = "ifconfig.co";
const char* url = "/json";
const int port = 80;




void setup()
{
    Serial.begin(115200);
    
    restAPI.connectWiFi();
}
void loop()
{
    Serial.println("This arduino project is test example of RestAPI :)");

    if(restAPI.connectAvailable())
    {
        String response = restAPI.callAPI(host,url,port);
        Serial.println("Result of callAPI: " + response);
        String value = restAPI.responseParser(response,"ip");
        Serial.println("Result of responseParser: " + value);
    }
    else
    {
        Serial.println("reconnecting WiFi");
        restAPI.connectWiFi();
    }
    delay(1000);
}