#define ledPin 0

int led_get_value() {
  int data = analogRead(ledPin);
  return data;
}