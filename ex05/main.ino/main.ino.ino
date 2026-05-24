#define TOUCH_PIN 4
#define LED_PIN 2

int brightness = 0;
int fadeAmount = 5;
int mode = 0;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 触摸检测（带防抖）
  if (touchRead(TOUCH_PIN) < 40) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      mode = (mode + 1) % 3; // 循环切换3种模式
      lastDebounceTime = millis();
      Serial.print("切换到模式：");
      Serial.println(mode + 1);
    }
  }

  // 根据模式执行不同效果
  switch (mode) {
    case 0: // 模式1：LED常灭
      analogWrite(LED_PIN, 0);
      break;
    case 1: // 模式2：固定亮度（50%）
      analogWrite(LED_PIN, 127);
      break;
    case 2: // 模式3：呼吸灯效果
      analogWrite(LED_PIN, brightness);
      brightness += fadeAmount;
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount;
      }
      delay(30);
      break;
  }
}