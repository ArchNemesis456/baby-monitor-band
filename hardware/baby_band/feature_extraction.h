#ifndef FEATURE_EXTRACTION_H
#define FEATURE_EXTRACTION_H

#include "data_models.h"

#ifndef SENSORS_H
#define SENSORS_H

#include "data_models.h"

void initSensors();

RawSensorData readSensors();

#endif

#endif