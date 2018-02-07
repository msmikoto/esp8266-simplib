#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>

class RestAPI
{
  public:
    RestAPI(const char* ssid,const char* password);

    String callAPI(const char* host, String url,int port); //retrun response if failed return null
    String callAPISSL(const char* host, String url,int port);

    String responseParser(String rawString, String jsonKey);
    bool connectWiFi();
    bool connectAvailable();
    

  private:
    
    char* _ssid = nullptr;
    char* _password = nullptr;
    bool connectFail = false;
};