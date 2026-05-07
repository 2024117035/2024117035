#define LED_PIN 2  // 你的LED引脚，ESP32板载LED一般是GPIO2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);  // 初始化串口，波特率115200
  Serial.println("=== SOS 求救信号程序启动 ===");
}

void loop() {
  // 第一步：发送 S 信号（三短闪，每次亮200ms）
  Serial.println("开始发送 S 信号");
  for(int i=0; i<3; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  Serial.println("S 信号发送完成");
  delay(500); // 字母间停顿

  // 第二步：发送 O 信号（三长闪，每次亮600ms）
  Serial.println("开始发送 O 信号");
  for(int i=0; i<3; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(600);
    digitalWrite(LED_PIN, LOW);
    delay(200); // 灭灯间隔，让“长亮”更明显
  }
  Serial.println("O 信号发送完成");
  delay(500); // 字母间停顿

  // 第三步：再发送一次 S 信号
  Serial.println("开始发送 S 信号");
  for(int i=0; i<3; i++){
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);
  }
  Serial.println("S 信号发送完成，一轮 SOS 结束");
  Serial.println("------------------------");

  delay(2000); // 一轮SOS结束后的长停顿
}