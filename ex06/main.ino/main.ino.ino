#define TOUCH_PIN 4
#define LED_PIN 2

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;
int mode = 0;

// 双闪效果参数
bool flashOn = false;
unsigned long lastFlashTime = 0;
const unsigned long flashInterval = 100; // 双闪频率，单位毫秒

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // 触摸检测（带防抖）
  if (touchRead(TOUCH_PIN) < 40) {
    if ((millis() - lastDebounceTime) > debounceDelay) {
      mode = (mode + 1) % 2; // 切换双闪模式：开/关
      lastDebounceTime = millis();
      if (mode == 1) {
        Serial.println("警车双闪已开启");
      } else {
        Serial.println("警车双闪已关闭");
        analogWrite(LED_PIN, 0); // 关闭模式时熄灭LED
      }
    }
  }

  // 模式1：警车双闪效果
  if (mode == 1) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastFlashTime >= flashInterval) {
      lastFlashTime = currentMillis;
      flashOn = !flashOn;
      analogWrite(LED_PIN, flashOn ? 255 : 0);
    }
  }
}