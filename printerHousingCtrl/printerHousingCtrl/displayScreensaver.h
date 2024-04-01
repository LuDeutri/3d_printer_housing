/*
 * The display pi tft 5.0 has a poti so set the display brightness. The uC is connected to the result
 * analog value to set it to GND and setting the display brightness to zero, if the display is not needed.
 */

#ifndef DISPLAYSCREENSAVER_H_
#define DISPLAYSCREENSAVER_H_

#include "config.h"
#include "button.h"

typedef struct{
	bool displayScreensaverActive;
	bool ignoreRaspiInput;
	bool raspiInput;
}screensaver_t;
extern screensaver_t screensaver;


void screensaver_init();
void screensaver_update();

void tooglDisplayScreensaver();
void setDisplayScreensaver(bool displayTimeout);


#endif
