/*
    HTTP over TLS (HTTPS) example sketch

    This example demonstrates how to use
    WiFiClientSecure class to access HTTPS API.
    We fetch and display the status of
    esp8266/Arduino project continuous integration
    build.

    Limitations:
      only RSA certificates
      no support of Perfect Forward Secrecy (PFS)
      TLSv1.2 is supported since version 2.4.0-rc1

    Created by Ivan Grokhotkov, 2015.
    This example is in public domain.
*/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <NTPtimeESP.h>
NTPtime NTPch("ch.pool.ntp.org"); 
/*
 * The structure contains following fields:
 * struct strDateTime
{
  byte hour;
  byte minute;
  byte second;
  int year;
  byte month;
  byte day;
  byte dayofWeek;
  boolean valid;
};
 */
strDateTime dateTime;



float rainfall = 0;
float hujan = 0;
float hujan2 = 1.00;
int rain_sensor = 5;

const char* ssid = "BMKG";
const char* password = "bmkg1234";

const char* host = "api.telegram.org";
const int httpsPort = 443;

// Use web browser to view and copy
// SHA1 fingerprint of the certificate
const char* fingerprint = "c6 5b fa 5b f7 57 0c 6a 02 85 c1 6f a7 19 6c 36 32 b4 28 21";

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use WiFiClientSecure class to create TLS connection
  

  
}


float get_rainfall()
{

  
 a:  
        int baca_sensor = analogRead(A0);
      
       if (baca_sensor >= 1000)
       {
        return  0.20;
       }
       
    
 delay(200);         
 goto a;           
}


void peringatan()
{
   WiFiClientSecure client;
  //Serial.print("connecting to ");
  //Serial.println(host);
  if (!client.connect(host, httpsPort)) {
   // Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
   // Serial.println("certificate matches");
  } else {
   // Serial.println("certificate doesn't match");
  }

  String url = "/bot500005895:AAFp6NQpeqbiBROZl2kX3QTv6ubENblj3kw/sendMessage?chat_id=54366973&text=Hujan+Ekstrim+Gan+: "+String(hujan)+" mm";
 // Serial.print("requesting URL: ");
 // Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

 // Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("Send New Post to Subscribers");
      break;
    }
  }
  

}



void waktu()
{
   dateTime = NTPch. getNTPtime ( 8.0 , 0 );
  
  // Check the dateTime.valid before the time interval
  if (dateTime. valid ) {
    NTPch. printDateTime (dateTime);

    byte actualHour = dateTime. hour ;      // Gio
    byte actualMinute = dateTime. minute ;  // Phut
    byte actualsecond = dateTime. second ;  // Giay
    int actualyear = dateTime. year ;       // Nam
    byte actualMonth = dateTime. month ;    // ladder
    byte actualday = dateTime. day ;         // Right
    byte actualdayofWeek = dateTime. dayofWeek ;
  }
}


void loop() {

waktu();

  
hujan = hujan + get_rainfall();

Serial.println(hujan);
 
 if (hujan > hujan2)  
 {

  peringatan();
 
 }
 else
 {
  
 }
 delay(1000);
}
