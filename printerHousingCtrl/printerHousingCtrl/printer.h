#ifndef PRINTER_H_
#define PRINTER_H_

#include "config.h"

typedef struct{
	bool splyCtrl;
	bool splyCtrlRaspiInput;
	bool ingoreRaspiInput;
}printer_t;
extern printer_t printer;

void printer_init();
void printer_update();

void printerShutdown();
void resetRaspiIgnoreStatement();

#endif /* PRINTER_H_ */
