# ESP32 Weather Station

A mini weather station: an ESP32 reads temperature and humidity from a
DHT sensor and shows them on a live web page that it hosts itself.
The page refreshes every 5 seconds, so you can watch the values change
from your phone.

## Features

- Live temperature and humidity dashboard in the browser
- Auto-refresh every 5 seconds
- Keeps showing the last good reading if the sensor glitches
- Supports both DHT11 and DHT22 (one-line change)

## Hardware

| Part | Notes |
|---|---|
| ESP32 dev board | any model |
| DHT11 or DHT22 sensor | DHT22 is more accurate |
| Jumper wires | |
| 10k ohm resistor | pull-up on the data line (recommended) |

### Wiring

| DHT pin | Connects to |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 (through the 10k pull-up to 3.3V) |

## Libraries

Install both from the Arduino Library Manager:

- **DHT sensor library** by Adafruit
- **Adafruit Unified Sensor** by Adafruit

## Setup

1. Wire the sensor as shown above.
2. Open `esp32-weather-station.ino` and fill in your WiFi credentials.
3. If you have a DHT22, change `#define DHT_TYPE DHT11` to `DHT22`.
4. Upload and open the Serial Monitor at 115200 baud to get the IP.
5. Visit `http://<the-printed-ip>` in your browser.

## Testing status

The code was carefully written and reviewed but has **not been run on
real hardware yet**. Sensor readings and wiring should be verified on
your own setup - please open an issue if you hit a problem.
