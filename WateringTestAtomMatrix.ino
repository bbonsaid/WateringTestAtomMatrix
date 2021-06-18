// WateringTestAtomMatrix bbd

#include <M5Atom.h>

#define P(col, row)   (((row) * 5) + (col))
#define RGB(r, g, b)  (((g) << 16) + ((r) << 8) + (b))

#define SECONDS(s)    ((s) * 1000)
#define MINUTES(m)    SECONDS(m * 60)

const int WAIT_TIME = SECONDS(1);

#define INPUT_PIN 32
#define PUMP_PIN 26

bool flag = true;
int rawADC;

void setup() { 
  M5.begin(true, false, true);

  pinMode(INPUT_PIN,INPUT);
  pinMode(PUMP_PIN,OUTPUT);
}

void
DispLevel(int lv) {
  int it = lv / 1000;
  int ih = (lv % 1000) / 100;

  static int lvPrev = 0;
  if (lv == lvPrev)
    return;
  lvPrev = lv;

  for (int i = 0 ; i < 5; i++) {
    M5.dis.drawpix(P(i, 0), RGB(0, 0xf0, 0) * (it > i));
  }
  M5.dis.drawpix(P(0, 1), RGB(0, 0xf0, 0xf0) * (ih > 0));
  M5.dis.drawpix(P(0, 2), RGB(0, 0xf0, 0xf0) * (ih > 1));
  M5.dis.drawpix(P(1, 1), RGB(0, 0xf0, 0xf0) * (ih > 2));
  M5.dis.drawpix(P(1, 2), RGB(0, 0xf0, 0xf0) * (ih > 3));
  M5.dis.drawpix(P(2, 1), RGB(0, 0xf0, 0xf0) * (ih > 4));
  M5.dis.drawpix(P(2, 2), RGB(0, 0xf0, 0xf0) * (ih > 5));
  M5.dis.drawpix(P(3, 1), RGB(0, 0xf0, 0xf0) * (ih > 6));
  M5.dis.drawpix(P(3, 2), RGB(0, 0xf0, 0xf0) * (ih > 7));
  M5.dis.drawpix(P(4, 1), RGB(0, 0xf0, 0xf0) * (ih > 8));
  M5.dis.drawpix(P(4, 2), RGB(0, 0xf0, 0xf0) * (ih > 9));
}

void loop() { 
  rawADC = analogRead(INPUT_PIN);
  Serial.print("Watering ADC value: ");
  Serial.println(rawADC);
  DispLevel(rawADC);
  if (M5.Btn.wasPressed()) {
      Serial.print("flag: ");
      Serial.println(flag);
      digitalWrite(PUMP_PIN,flag);
      flag = !flag;
  }
  M5.update();
  
  delay(WAIT_TIME);
}
