#include <Stepper.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>

// Définition des LEDs pour le retour visuel
const int ledRed = A0;
const int ledYellow = A1;
const int ledBlue = A2;

// Déclaration des 5 servomoteurs
Servo servo1, servo2, servo3, servo4, servo5;

// Pins de branchement des servomoteurs
const int pinServo1 = 9;
const int pinServo2 = 10;
const int pinServo3 = 11;
const int pinServo4 = 12;
const int pinServo5 = 13;

// Positions de départ et de fin pour le mouvement
const int posStartServo1 = 50;
const int posEndServo1 = 90;
const int posStartServo2 = 25;
const int posEndServo2 = 0;
const int posStartServo3 = 70;
const int posEndServo3 = 120;

// Configuration des pins du capteur TCS3200
const int S0 = 4;
const int S1 = 5;
const int S2 = 6;
const int S3 = 7;
const int sensorOut = 8;

int frequencyRed = 0;
int frequencyGreen = 0;
int frequencyBlue = 0;

bool colorFind = false;

void setup() {
  // Configuration des LEDs en sortie
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledBlue, OUTPUT);

  // Initialisation des servos
  servo1.attach(pinServo1);
  servo2.attach(pinServo2);
  servo3.attach(pinServo3);
  servo4.attach(pinServo4);
  servo5.attach(pinServo5);

  moveServoStart(); // Position initiale du bras

  // Configuration du capteur de couleur
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Mise à l'échelle de la fréquence à 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  getFrequency(); // Lecture des couleurs

  if (!colorFind) {
    checkColor(); // Analyse de la couleur détectée
  } else {
    moveBlock(); // Action de tri si une couleur est trouvée
  }
}

void getFrequency() {
  // Lecture de la composante Rouge
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequencyRed = pulseIn(sensorOut, LOW);
  Serial.print("Red = ");
  Serial.print(frequencyRed);
  Serial.print(" ");
  delay(100);

  // Lecture de la composante Verte
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequencyGreen = pulseIn(sensorOut, LOW);
  Serial.print("Green = ");
  Serial.print(frequencyGreen);
  Serial.print(" ");
  delay(100);

  // Lecture de la composante Bleue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequencyBlue = pulseIn(sensorOut, LOW);
  Serial.print("Blue = ");
  Serial.print(frequencyBlue);
  Serial.println(" ");
  delay(100);
}

void checkColor() {
  // Éteindre les LEDs avant détection
  digitalWrite(ledRed, LOW);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledBlue, LOW);

  // Seuils de calibration extraits de ton rapport
  const int redThresholdLow = 25, redThresholdHigh = 45;
  const int greenThresholdLow = 85, greenThresholdHigh = 105;
  const int blueThresholdLow = 55, blueThresholdHigh = 75;
  const int yellowGreenThresholdLow = 40, yellowGreenThresholdHigh = 60;
  const int yellowBlueThresholdLow = 65, yellowBlueThresholdHigh = 85;
  const int blueRedThresholdLow = 70, blueRedThresholdHigh = 90;
  const int blueGreenThresholdLow = 75, blueGreenThresholdHigh = 95;
  const int blueThresholdLowAlt = 40, blueThresholdHighAlt = 60;

  // Logique de détection : Rouge
  if ((frequencyRed >= redThresholdLow && frequencyRed <= redThresholdHigh)
      && (frequencyGreen >= greenThresholdLow && frequencyGreen <= greenThresholdHigh)
      && (frequencyBlue >= blueThresholdLow && frequencyBlue <= blueThresholdHigh)) {
    digitalWrite(ledRed, HIGH);
    colorFind = true;
  }
  // Logique de détection : Jaune
  else if ((frequencyRed >= redThresholdLow && frequencyRed <= redThresholdHigh)
           && (frequencyGreen >= yellowGreenThresholdLow && frequencyGreen <= yellowGreenThresholdHigh)
           && (frequencyBlue >= yellowBlueThresholdLow && frequencyBlue <= yellowBlueThresholdHigh)) {
    digitalWrite(ledYellow, HIGH);
    colorFind = true;
  }
  // Logique de détection : Bleu
  else if ((frequencyRed >= blueRedThresholdLow && frequencyRed <= blueRedThresholdHigh)
           && (frequencyGreen >= blueGreenThresholdLow && frequencyGreen <= blueGreenThresholdHigh)
           && (frequencyBlue >= blueThresholdLowAlt && frequencyBlue <= blueThresholdHighAlt)) {
    digitalWrite(ledBlue, HIGH);
    colorFind = true;
  }
}

void moveServoStart() {
  // Positionnement initial de tous les axes
  servo1.write(posStartServo1);
  servo2.write(posStartServo2);
  servo3.write(posStartServo3);
  servo4.write(90);
  servo5.write(90);
}

void moveBlock() {
  clawClose(); // Fermer la pince pour saisir l'objet

  // Séquence de déplacement vers la zone de tri
  setServoPosition(servo2, posStartServo2, posEndServo2);
  setServoPosition(servo3, posStartServo3, posEndServo3);
  setServoPosition(servo1, posStartServo1, posEndServo1);

  // Ouvrir les pinces après le déplacement du bras
  clawOpen();

  // Revenir à la position initiale
  setServoPosition(servo1, posEndServo1, posStartServo1);
  setServoPosition(servo3, posEndServo3, posStartServo3);
  setServoPosition(servo2, posEndServo2, posStartServo2);

  delay(2000);
  moveServoStart();
  colorFind = false; // Prêt pour une nouvelle détection
}

// Fonction utilitaire pour un mouvement fluide des servos
void setServoPosition(Servo servo, int startPosition, int endPosition) {
  if (startPosition > endPosition) {
    for (int i = startPosition; i >= endPosition; i--) {
      servo.write(i);
      delay(30);
    }
  } else {
    for (int i = startPosition; i <= endPosition; i++) {
      servo.write(i);
      delay(30);
    }
  }
}

void clawOpen() {
  // Paramètres d'ouverture de la pince
  servo4.write(70);
  servo5.write(100);
}

void clawClose() {
  // Paramètres de fermeture de la pince
  servo4.write(100);
  servo5.write(80);
}