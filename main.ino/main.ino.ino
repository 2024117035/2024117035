#define TOUCH_PIN 4
#define LED_PIN   2

bool ledState = false;
bool lastTouch = false;
unsigned long debounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(TOUCH_PIN, INPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(115200);  // 开启串口通信，波特率115200
  Serial.println("程序启动成功！");
}

void loop() {
  bool currTouch = digitalRead(TOUCH_PIN);
  unsigned long now = millis();

  Serial.print("触摸状态：");
  Serial.println(currTouch);

  if (currTouch && !lastTouch && (now - debounceTime) > debounceDelay) {
    debounceTime = now;
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    Serial.print("LED状态切换为：");
    Serial.println(ledState ? "亮" : "灭");
  }

  lastTouch = currTouch;
}