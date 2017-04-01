#include <uSTimer2.h>
#include <CharliePlexM.h>
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 CharliePlexM::set(5, 6,7);
}
void loop() {
 // 2,1,13
  for (int i = 0; i < 14; i++) {
    Serial.println(i);
CharliePlexM::Write(i, 1);
      delay(500);
      CharliePlexM::Write(i, 0);
      delay (500);
  }}
