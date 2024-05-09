#pragma once

// Module includes
#include "led.h"
#include "gasSensor.h"
#include "button.h"
#include "config.h"
#include "fireExtinguisher.h"
#include "printer.h"

void printerHousingCtrl_init();
void printerHousingCtrl_main();

void updatePiInput();
