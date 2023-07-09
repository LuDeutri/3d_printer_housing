#ifndef PRINTERHOUSINGCTRL_H_
#define PRINTERHOUSINGCTRL_H_

// Module includes
#include "led.h"
#include "gasSensor.h"
#include "button.h"
#include "config.h"
#include "fireExtinguisher.h"

extern bool printerSplyActive;
extern bool displayTimeout;

void printerHousingCtrl_init();
void printerHousingCtrl_main();

void updatePiInput();
void printerSupplyCtrl_update();
void setPrinterSplyCtrl(bool splyCtrl);

void toogleDisplayTimeout();

#endif
