
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// IR sensor pins
int irEntry = 2;
int irExit = 3;
int irA = 4;
int irB = 5;
int irC = 6;

// Slot availability
bool slotA = true;
bool slotB = true;
bool slotC = true;

// Buzzer
int buzzer = 7;

void setup() {
  lcd.begin();
  lcd.backlight();

  pinMode(irEntry, INPUT);
  pinMode(irExit, INPUT);
  pinMode(irA, INPUT);
  pinMode(irB, INPUT);
  pinMode(irC, INPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Slot status update
  slotA = !digitalRead(irA);
  slotB = !digitalRead(irB);
  slotC = !digitalRead(irC);

  int available = 0;
  if (!slotA) available++;
  if (!slotB) available++;
  if (!slotC) available++;

  if (digitalRead(irEntry) == LOW) {
    if (available > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Slots Available:");
      lcd.setCursor(0, 1);
      if (!slotA) lcd.print("A ");
      if (!slotB) lcd.print("B ");
      if (!slotC) lcd.print("C ");
      delay(2000);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parking Full");
      lcd.setCursor(0, 1);
      lcd.print("SORRY!");
      digitalWrite(buzzer, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
    }
  }

  if (digitalRead(irExit) == LOW) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Vehicle Exiting");
    delay(2000);
  }

  delay(500);
}
