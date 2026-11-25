/*
 * ESP32 Weather Station
 * ---------------------
 * Reads temperature and humidity from a DHT11/DHT22 sensor and
 * shows them on a live web page hosted by the ESP32 itself.
 * The page refreshes automatically every 5 seconds.
 *
 * Board:  any ESP32 dev board
 * Sensor: DHT11 or DHT22 (DHT22 is more accurate)
 * Libs:   "DHT sensor library" by Adafruit
 *         + "Adafruit Unified Sensor" (install both from the Library Manager)
 */

#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>

// ---- Change these to your own network ----
const char* WIFI_SSID     = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
// ------------------------------------------

#define DHT_PIN  4        // data pin of the sensor
#define DHT_TYPE DHT11    // change to DHT22 if that is your sensor

DHT dht(DHT_PIN, DHT_TYPE);
WebServer server(80);

float lastTemp = NAN;
float lastHum  = NAN;

void readSensor() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  // keep the last good reading if the sensor glitches
  if (!isnan(t)) lastTemp = t;
  if (!isnan(h)) lastHum  = h;
}

String pageHtml() {
  String temp = isnan(lastTemp) ? "--" : String(lastTemp, 1);
  String hum  = isnan(lastHum)  ? "--" : String(lastHum, 1);
  String html =
    "<!DOCTYPE html><html><head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1'>"
    "<meta http-equiv='refresh' content='5'>"
    "<title>ESP32 Weather Station</title>"
    "<style>"
    "body{font-family:sans-serif;text-align:center;background:#0b1120;color:#e2e8f0;padding-top:50px}"
    ".card{display:inline-block;margin:12px;padding:24px 40px;border-radius:16px;background:#111c33}"
    ".value{font-size:2.6rem;font-weight:700}.label{color:#7dd3fc}"
    "</style></head><body>"
    "<h1>Weather Station</h1>"
    "<div class='card'><div class='label'>Temperature</div><div class='value'>" + temp + " &deg;C</div></div>"
    "<div class='card'><div class='label'>Humidity</div><div class='value'>" + hum + " %</div></div>"
    "<p>Updates every 5 seconds</p>"
    "</body></html>";
  return html;
}

void handleRoot() { readSensor(); server.send(200, "text/html", pageHtml()); }

void setup() {
  Serial.begin(115200);
  dht.begin();

  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! Open this in your browser: http://");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();
}
