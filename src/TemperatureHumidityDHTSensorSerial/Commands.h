#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "Common.h"
#include "duinocom2.h"
#include "EEPROMHelper.h"

void checkCommand();

void handleCommand(char* msg);

void restoreDefaultSettings();

#endif
