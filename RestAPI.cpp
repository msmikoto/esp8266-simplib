#include "RestAPI.h"

RestAPI::RestAPI(const char *ssid, const char *password)
{
    _ssid = (char *)ssid;
    _password = (char *)password;
}

String RestAPI::callAPI(const char *host, String url, int port, String method,String body)
{
    WiFiClient client;

    if (client.connect(host, port))
    {
        String header = "";
        header += method + " " + url + " HTTP/1.1 \n";
        header += "Host: " + (String)host + "\n";
        header += "Accept: application/json \n";
        header += "Content-Type: application/json\n";
        header += "User-Agent: Arduino/1.0 \n";
        header += "Connection: close \n";
        header +="Content-Length: "; header+=String(body.length()) + "\n";


        Serial.println(header+body);
        client.println(header + "\n" + body);
    }
    else
    {
        connectFail = true;
        return "";
    }

    String response = "";

    while (client.connected())
    {
        response += client.readString();
    }

    return response;
}

String RestAPI::callAPISSL(const char *host, String url, int port,String method,String body)
{
    WiFiClientSecure client;

    if (client.connect(host, port))
    {
        String header = "";
        header += method + " " + url + " HTTP/1.1 \n";
        header += "Host: " + (String)host + "\n";
        header += "Accept: application/json \n";
        header += "Content-Type: application/json\n";
        header += "User-Agent: Arduino/1.0 \n";
        header += "Connection: close \n";
        header +="Content-Length: "; header+=String(body.length()) + "\n";


        Serial.println(header+body);
        client.println(header + "\n" + body);
    }
    else
    {
        connectFail = true;
        return "";
    }

    String response = "";

    while (client.connected())
    {
        response += client.readString();
    }

    return response;
}


String RestAPI::responseParser(String rawString, String jsonKey)
{
    String buffer;
    buffer = rawString.substring(rawString.indexOf(jsonKey));
    buffer = buffer.substring(buffer.indexOf(':') + 1, buffer.indexOf(','));

    return buffer;
}

bool RestAPI::connectWiFi()
{
    Serial.println("WiFi connecting Start");
    WiFi.begin(_ssid, _password);
    for (int i = 0; i < 60; i++)
    {
        delay(500);

        Serial.print(".");

        if (WiFi.status() == WL_CONNECTED)
            break;
        if (i == 60)
        {

            Serial.println("WiFi Connectiong time out");

            return false;
        }
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC: ");
    Serial.println(WiFi.macAddress());

    connectFail = false;
    return true;
}

bool RestAPI::connectAvailable()
{
    return (WiFi.status() == WL_CONNECTED)&&!connectFail;
}