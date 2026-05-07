const int ledPin = 2;
unsigned long previousMillis = 0;  // 记录上次状态切换的时间
const long interval = 500;        // 闪烁间隔（500ms，1Hz）
bool ledState = LOW;              // LED当前状态

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  unsigned long currentMillis = millis(); // 获取当前时间

  // 检查是否到了切换状态的时间
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // 更新上次切换时间
    ledState = !ledState;            // 翻转LED状态
    digitalWrite(ledPin, ledState); // 更新LED状态
    Serial.print("LED State: ");
    Serial.println(ledState ? "ON" : "OFF");
  }
}