#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// إعداد شاشة الـ I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// إعداد حساس الرطوبة
#define DHTPIN 2
#define DHTTYPE DHT11 // لو الحساس أبيض خليه DHT22
DHT dht(DHTPIN, DHTTYPE);

// إعداد الأطراف
#define LM35_PIN A0


void setup() {
  lcd.init();
  lcd.backlight();
  dht.begin();
  
  lcd.setCursor(0, 0);
  lcd.print("System Ready...");
  delay(1500);
  lcd.clear();
}

void loop() {
  // 1. قراءة الحرارة المباشرة من LM35
  int analogTemp = analogRead(LM35_PIN);
  float voltage = (analogTemp / 1024.0) * 5.0; 
  float t = voltage * 100.0; // LM35 يعطي 10mV لكل درجة مئوية

  // 2. قراءة الرطوبة
  float h = dht.readHumidity();



  // العرض على الشاشة (الصف الأول)
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 1);
 


  // العرض على الشاشة (الصف الثاني
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  if (isnan(h)) {
    lcd.print("Error  ");
  } else {
    lcd.print(h, 1);
    lcd.print("%    ");
  }

  delay(500); }