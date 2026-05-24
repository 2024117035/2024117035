#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Eggy 17p!";
const char* password = "asdf2580";

WebServer server(80);
int touchPin = 4;
int ledPin = 2;
bool armed = false;
bool isAlarm = false;  // 把 alarm 改成 isAlarm，避开系统冲突

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("正在连接WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi连接成功！IP地址：");
  Serial.println(WiFi.localIP());

  server.on("/", [](){
    String html = R"HTML(
<!DOCTYPE html>
<html>
<body style="text-align:center;">
  <h1>安防报警器</h1>
  <a href=" "><button style="font-size:20px;padding:10px 20px;background:red;color:white;">布防</button></a >
  <a href="/disarm"><button style="font-size:20px;padding:10px 20px;background:green;color:white;">撤防</button></a >
</body></html>
)HTML";
    server.send(200, "text/html", html);
  });

  server.on("/arm", [](){
    armed = true;
    isAlarm = false;
    server.send(200, "text/plain", "已布防");
  });

  server.on("/disarm", [](){
    armed = false;
    isAlarm = false;
    digitalWrite(ledPin, LOW);
    server.send(200, "text/plain", "已撤防");
  });

  server.begin();
}

void loop() {
  server.handleClient();

  if (armed && touchRead(touchPin) < 40) {
    isAlarm = true;
  }

  if (isAlarm) {
    digitalWrite(ledPin, HIGH); delay(100);
    digitalWrite(ledPin, LOW);  delay(100);
  }
}