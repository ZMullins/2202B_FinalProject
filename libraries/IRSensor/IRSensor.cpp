
//CharliePlex - Top left is on = AE, One to the right means = IO
//Flip switch to change setting
#include "Arduino.h"
#include "IRSensor.h"
#include <uSTimer2.h>
#include <CharliePlexM.h>
//Plug in C4, C2, C1 into 5,6,7
IRSensor::IRSensor(int switchPin, int cOne, int cTwo, int cThree) {
	_switchPin = switchPin;
	CharliePlexM::set(cOne, cTwo, cThree);
	pinMode(_switchPin, INPUT);
}
bool IRSensor::AE() {
	if (digitalRead(_switchPin) == HIGH) {
		CharliePlexM::Write(2, 1);
		CharliePlexM::Write(1, 0);
		return true;
	}
	else {
		CharliePlexM::Write(1, 1);
		CharliePlexM::Write(2, 0);
		return false;
	}
}
bool IRSensor::checkLetters(bool lookingAE) {
	char val = valueReturned();
	if (lookingAE == true) {
		if ((val == 'A' || val == 'E')) {
			Serial.println(val);
			return true;
		}
	}
	else if ((val == 'O' || val == 'I')) {
		Serial.println(val);
		return true;
	}

		return false;
}

	char IRSensor::valueReturned() {
		char val = Serial.read();
		return val;
	}