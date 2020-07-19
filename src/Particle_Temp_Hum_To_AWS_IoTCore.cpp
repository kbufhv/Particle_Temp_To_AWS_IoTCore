/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/kathrinburtscher/Particle/Particle_Temp_Hum_To_AWS_IoTCore/src/Particle_Temp_Hum_To_AWS_IoTCore.ino"
/*
 * Project Particle_Temp_Hum_To_AWS_IoTCore
 */

#include "MQTT-TLS.h"
#include "Grove_Temperature_And_Humidity_Sensor.h"

//AWS MQTT
void setup();
void loop();
#line 9 "/Users/kathrinburtscher/Particle/Particle_Temp_Hum_To_AWS_IoTCore/src/Particle_Temp_Hum_To_AWS_IoTCore.ino"
const char awsRootCert[] = "-----BEGIN CERTIFICATE-----\r\nMIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\r\n********\r\nrqXRfboQnoZsG4q5WTP468SQvvG5\r\n-----END CERTIFICATE-----";
const char awsClientCert[] = "-----BEGIN CERTIFICATE-----\r\nMIIDWTCCAkGgAwIBAgIUN94dGYvsTJoeQvwxz6JgJcdOWjUwDQYJKoZIhvcNAQEL\r\n*******\r\nIdGvOolrrjKBhaGyutj4VsS3LZU8hraii+rQyfD5pJ7M8qQ+0ODV37b8Nb9Y\r\n-----END CERTIFICATE-----";
const char awsClientKey[] = "-----BEGIN RSA PRIVATE KEY-----\r\nMIIEowIBAAKCAQEA2dS+/HsIGCN6d0tz+BZQ8eNj18OiyjNBzevQEdJ4tRKcfXgk\r\r******\r\nJnrlUw37EZMHI6EFF8AaVHRGshoOge8X9Xg8WJelwTkTZo38lZzU\r\n-----END RSA PRIVATE KEY-----";

void callback(char *topic, byte *payload, unsigned int length);

//Create MQTT client with AWS IoT-Core endpoint as host
MQTT client("******************.iot.eu-central-1.amazonaws.com", 8883, callback);

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  String message(p);
}

//Temperature and Humidity Sensor
DHT sensor(D2);
String temp;
String hum;

// setup() runs once, when the device is first turned on.
void setup()
{
  //AWS
  client.enableTls(awsRootCert, sizeof(awsRootCert), awsClientCert, sizeof(awsClientCert), awsClientKey, sizeof(awsClientKey));
  //Use some kind of unique text for the connection
  client.connect("Particle_1");

  //Temperature and Humidity Sensor
  Serial.begin(9600);
  sensor.begin();
}

// loop() runs over and over again 
void loop()
{

  //get sensor data
  temp = String(sensor.getTempCelcius());
  hum = String(sensor.getHumidity());

  //AWS
  if (client.isConnected())
  {
    client.loop();
    client.publish("sensor/temperature", temp);
  }

  //wait for 30 seconds
  delay(30 * 1000);
}
