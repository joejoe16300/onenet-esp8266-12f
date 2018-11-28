#include <HttpPacket.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <WiFiServerSecureBearSSL.h>
#include <WiFiServerSecureAxTLS.h>
#include <WiFiServerSecure.h>
#include <WiFiServer.h>
#include <WiFiClientSecureBearSSL.h>
#include <WiFiClientSecureAxTLS.h>
#include <WiFiClientSecure.h>
#include <WiFiClient.h>
#include <ESP8266WiFiType.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFi.h>
#include <CertStoreBearSSL.h>
#include <BearSSLHelpers.h>
#include <SimpleDHT.h>
HttpPacketHead packet;
#define myPeriodic 2
//int sent = 0;



int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
char OneNetServer[] = "api.heclouds.com";       //不需要修改
const char ssid[] = "Xiaomi";     //修改为自己的路由器用户名
const char password[] = "12345687"; //修改为自己的路由器密码
char device_id[] = "505224058";    //修改为自己的设备ID
char API_KEY[] = "q2j=SV5weH=lMEBSA2IXxHtxzJ4=";    //修改为自己的API_KEY

char sensor_id1[] = "temp";
char sensor_id2[] = "hum";

void connectWifi()
{
	Serial.print("Connecting to " + *ssid);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.print(".");
	}
	Serial.println("");
	Serial.println("Connected");
	Serial.println("");

}
void postDataToOneNet(char* API_VALUE_temp, char* device_id_temp, char* sensor_id_temp, float thisData)
{
	WiFiClient client;
	StaticJsonBuffer<250> jsonBuffer;
	JsonObject& myJson = jsonBuffer.createObject();
	JsonArray& datastreams = myJson.createNestedArray("datastreams");
	JsonObject& id_datapoints = datastreams.createNestedObject();
	id_datapoints["id"] = sensor_id_temp;
	JsonArray& datapoints = id_datapoints.createNestedArray("datapoints");
	JsonObject& value = datapoints.createNestedObject();
	value["value"] = thisData;
	char p[180];
	myJson.printTo(p, sizeof(p));
	packet.setHostAddress(OneNetServer);
	packet.setDevId(device_id_temp);   //device_id
	packet.setAccessKey(API_VALUE_temp);  //API_KEY
	/*create the http message about add datapoint */
	packet.createCmdPacket(POST, TYPE_DATAPOINT, p);
	if (strlen(packet.content))
		Serial.print(packet.content);
	Serial.println(p);
	char cmd[400];
	memset(cmd, 0, 400);
	strcpy(cmd, packet.content);
	strcat(cmd, p);
	if (client.connect(OneNetServer, 80)) {
		Serial.println("WiFi Client connected ");
		client.print(cmd);
		delay(1000);
	}//end if
	//  Serial.println(cmd);
	client.stop();
}

void setup() {
	Serial.begin(115200);
	connectWifi();
	Serial.println("setup end!");

}

void loop() {



	// start working...
	Serial.println("=================================");
	Serial.println("Sample DHT11...");

	// read without samples.
	byte temperature = 0;
	byte humidity = 0;
	int err = SimpleDHTErrSuccess;
	if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
	{
		Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
		return;
	}

	Serial.print("Sample OK: ");
	Serial.print((int)temperature); Serial.print(" *C, ");
	Serial.print((int)humidity); Serial.println(" H");


	delay(1500);// DHT11 sampling rate is 1HZ.


	//int temp = random(10, 38); int hum = random(50, 70);//自动生成随机数模拟温湿度
	//发送数据到Onenet
	postDataToOneNet(API_KEY, device_id, sensor_id1, (int)temperature);
	delay(100);
	postDataToOneNet(API_KEY, device_id, sensor_id2, (int)humidity);
	//Serial.printf("N0 ", " Stream: was send"); //+String(sent) +
	//sent++;
	int count = myPeriodic;
	while (count--)
		delay(1000);

}