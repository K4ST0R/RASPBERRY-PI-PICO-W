#include <ArduinoOTA.h>
#include <HTTPUpdateServer.h>
#include <WebServer.h>
#include <WiFiUdp.h>

// Edit with your WIFI informations
#define SECRET_SSID "SSID"
#define SECRET_PASS "PASSWORD"

const char* host = "pico-webupdate";
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

WebServer httpServer(80);
HTTPUpdateServer httpUpdater(true);

void setup() {
  Serial.begin(115200);
  Serial.println("Booting");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    rp2040.restart();
  }

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  httpUpdater.setup(&httpServer);
  httpServer.begin();

  Serial.printf(
      "HTTPUpdateServer ready! Open http://%s.local/update in your browser\n",
      host);
}

void loop() { httpServer.handleClient(); }
