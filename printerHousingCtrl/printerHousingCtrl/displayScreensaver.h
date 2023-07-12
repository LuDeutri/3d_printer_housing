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
