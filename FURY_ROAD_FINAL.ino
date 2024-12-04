// blynk template details 
#define BLYNK_TEMPLATE_ID ""   // add blynk template id here
#define BLYNK_TEMPLATE_NAME "" // add blynk template name here
#define BLYNK_AUTH_TOKEN ""    // add blynk auth token here

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Motor PINs
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENA D5
#define ENB D6


// arrow key variables
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;

int fb_speed = 0; // forward and backward Speed value controlled by the slider (0-255)
int rl_speed = 0; // right and left turn speed value controlled by the slider (0-255)


// Wifi Credentials
char ssid[] = "";  // add your Wi-Fi network name
char pass[] = "";  // add your Wi-Fi password


void setup() {
  // Initializing the serial monitor
  Serial.begin(115200);

  // Setting the motor pins as the output pin
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(2, OUTPUT);

  // Initialize the Blynk communication
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}


// Reciving parameter values from blynk

// Arrow Keys values
BLYNK_WRITE(V3) {
  forward = param.asInt();
}
BLYNK_WRITE(V4) {
  right = param.asInt();
}
BLYNK_WRITE(V5) {
  backward = param.asInt();
}
BLYNK_WRITE(V6) {
  left = param.asInt();
}

// Speed value
BLYNK_WRITE(V8) {
  fb_speed = param.asInt(); // Read the slider value (0-255)
}

BLYNK_WRITE(V9){
  rl_speed = param.asInt(); // Read the slider value (0-255)
}


// Arrow Key Control
void carControl() {
  if (forward == 1) {
    Forward(fb_speed);
  } else if (backward == 1) {
    Backward(fb_speed);
    Serial.println("Backward");
  } else if (left == 1) {
    Left(rl_speed);
    Serial.println("Left");
  } else if (right == 1) {
    Right(rl_speed);
    Serial.println("Right");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    Stop();
    Serial.println("Stop");
  }
}

void loop() {
  // Run the Blynk library
  Blynk.run();
  carControl();

}

// Motor control functions
void Forward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Backward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


void Left(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void Right(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void Stop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}