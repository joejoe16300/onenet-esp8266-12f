#include <ESP8266WiFi.h>
const char *AP_SSID = "Xiaomi";//�������ҵ�wifi����ʹ��ʱ�޸�Ϊ��Ҫ���ӵ�wifi ssid
const char *AP_PSW = "123456878";//��Ҫ���ӵ�wifi����

//������������Ϊ���Զ���
#define DebugBegin(baud_rate)    Serial.begin(baud_rate)
#define DebugPrintln(message)    Serial.println(message)
#define DebugPrint(message)    Serial.print(message)

void setup() {
	int i = 0;
	//���ô��ڲ����ʣ��Ա��ӡ��Ϣ
	DebugBegin(115200);
	//��ʱ2s Ϊ����ʾЧ��
	delay(2000);
	DebugPrintln("Setup start");
	//����STAģʽ�������ӵ�wifi����
	WiFi.begin(AP_SSID, AP_PSW);
	delay(2000);

	DebugPrint(String("Connecting to ") + AP_SSID);
	//�ж�����״̬�Ƿ������ϣ�û�����Ͼ���ʱ500ms�����Ҵ��һ���㣬ģ�����ӹ���
	//������չ����������һֱ�������� �Ƿ���������жϣ��������Լ�ʵ��
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		DebugPrint(".");
		i++;
		if (i > 5)
		{
			i = 0;
			const char *AP_SSID = "Xiaomi";//�������ҵ�wifi����ʹ��ʱ�޸�Ϊ��Ҫ���ӵ�wifi ssid
			const char *AP_PSW = "12345687";//��Ҫ���ӵ�wifi����
			WiFi.begin(AP_SSID, AP_PSW);
			DebugPrintln("Setup start2");
			delay(2000);

		}
	}

	DebugPrintln("");

	DebugPrint("Connected, IP address: ");
	//���station IP��ַ�������IP��ַ��DHCP����
	DebugPrintln(WiFi.localIP());
	DebugPrintln("Setup End");
}

void loop() {
}