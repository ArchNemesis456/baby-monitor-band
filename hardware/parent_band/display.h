#ifndef DISPLAY_H
#define DISPLAY_H

#include "data_models.h"

bool initializeDisplay();

void showBootScreen();

void showWiFiConnecting();

void showWiFiConnected();

void showPrediction(const PredictionData &prediction);

void showConnectionError();

#endif