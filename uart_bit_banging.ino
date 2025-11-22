const int TX_PIN = 5;      
const int BIT_DELAY = 833;

String message = "ValentynB_2025_11_21";

void sendByte(uint8_t b) {
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(BIT_DELAY);

  for (int i = 0; i < 8; i++) {
    digitalWrite(TX_PIN, (b & (1 << i)) ? HIGH : LOW);
    delayMicroseconds(BIT_DELAY);
  }

  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(BIT_DELAY);
}

void setup() {
  pinMode(TX_PIN, OUTPUT);
  digitalWrite(TX_PIN, HIGH);

  delay(1000);

  for (int i = 0; i < message.length(); i++) {
    sendByte(message[i]);
  }
}

void loop() {

}