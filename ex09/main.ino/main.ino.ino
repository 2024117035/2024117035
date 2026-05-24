#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "你的WiFi名称";
const char* password = "你的WiFi密码";

WebServer server(80);
int touchPin = 4;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  Serial.println(WiFi.localIP());

  // 主页：显示实时数值
  server.on("/", [](){
    String html = R"HTML(
<!DOCTYPE html>
<html>
<body style="text-align:center;font-size:40px;">
  <h1>触摸传感器数值</h1>
  <div id="num">0</div>
<script>
setInterval(()=>{
  fetch("/get")
  .then(r=>r.text())
  .then(v=>document.getElementById("num").innerText=v);
}, 200);
</script>
</body></html>
)HTML";
    server.send(200, "text/html", html);
  });

  // 返回触摸值
  server.on("/get", [](){
    int val = touchRead(touchPin);
    server.send(200, "text/plain", String(val));
  });

  server.begin();
}

void loop() {
  server.handleClient();
}