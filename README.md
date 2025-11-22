# ESP32-C3 UART Bit-Banging (Software UART)

This repository contains the implementation of a software-based UART transmitter on the ESP32-C3 microcontroller.  
UART frames are generated manually (bit-banging) without using the Serial library.

---

## Project Overview

The goal of this task is to manually generate UART frames according to the standard format:

- **Start bit:** LOW  
- **8 data bits:** Least Significant Bit first  
- **Stop bit:** HIGH  
- **Bit duration:** 833 µs (calculated for 1200 baud)

The bit stream is produced using:
- `digitalWrite()`
- `delayMicroseconds()`

This allows emulation of UART transmission entirely in software.

---

## Hardware Used

| Component | Description |
|----------|-------------|
| **ESP32-C3FH4** | Microcontroller used for bit-banging UART |
| **USB–UART Adapter CP2102** | Receives manually generated UART data on PC |
| **Dupont wires** | Connect TX and GND |

---

## Wiring Connection

| ESP32-C3 pin | USB–UART CP2102 | Purpose |
|--------------|----------------|---------|
| **GPIO5**    | **RXD**         | Software UART TX output |
| **GND**      | **GND**         | Common ground |

---

## Source Code

```cpp
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

void loop() {}
