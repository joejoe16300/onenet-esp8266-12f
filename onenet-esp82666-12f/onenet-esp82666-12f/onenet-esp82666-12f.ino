#include <ESP8266WiFi.h>
const char *AP_SSID = "Xiaomi";//这里是我的wifi，你使用时修改为你要连接的wifi ssid
const char *AP_PSW = "123456878";//你要连接的wifi密码

//以下三个定义为调试定义
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

void setup() {
	int i = 0;
	//设置串口波特率，以便打印信息
	DebugBegin(115200);
	//延时2s 为了演示效果
	delay(2000);
	DebugPrintln("Setup start");
	//启动STA模式，并连接到wifi网络
	WiFi.begin(AP_SSID, AP_PSW);
	delay(2000);

	DebugPrint(String("Connecting to ") + AP_SSID);
	//判断网络状态是否连接上，没连接上就延时500ms，并且打出一个点，模拟连接过程
	//笔者扩展：加入网络一直都连不上 是否可以做个判断，由你们自己实现
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		DebugPrint(".");
		i++;
		if (i > 5)
		{
			i = 0;
			const char *AP_SSID = "Xiaomi";//这里是我的wifi，你使用时修改为你要连接的wifi ssid
			const char *AP_PSW = "12345687";//你要连接的wifi密码
			WiFi.begin(AP_SSID, AP_PSW);
			DebugPrintln("Setup start2");
			delay(2000);

		}
	}

	DebugPrintln("");

	DebugPrint("Connected, IP address: ");
	//输出station IP地址，这里的IP地址由DHCP分配
	DebugPrintln(WiFi.localIP());
	DebugPrintln("Setup End");
}

void loop() {
}