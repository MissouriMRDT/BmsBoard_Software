#ifndef BMS_SOFTWARE_H
#define BMS_SOFTWARE_H

#include "PinAssignments.h"
#include "RoveComm.h"
#include <cstdint>

// RoveComm
EthernetServer TCPServer(RC_ROVECOMM_ETHERNET_TCP_PORT);
RoveCommEthernet RoveComm;

// Telemetry
#define TELEMETRY_PERIOD 500000
IntervalTimer Telemetry;
void telemetry();

// Important constants
#define NUM_CELLS 6
#define NUM_VOLTAGE_READINGS 1000
#define RESTART_DELAY 1000 // millis
#define MAX_CURRENT 50 // Amps
#define ALLOWABLE_OVERCURRENT_PERIOD 30000 // millis
#define CELL_UNDERVOLT_THRESHOLD 2.7
#define CELL_CRITICAL_THRESHOLD 2.5

// Current conversion factor
#define ZERO_CURRENT_AMPS 0
#define ZERO_CURRENT_ANALOG 512
#define OTHER_CURRENT_AMPS 60
#define OTHER_CURRENT_ANALOG 670

// Voltage conversion factor
#define ZERO_VOLTS 0 //Volts
#define ZERO_VOLTS_ANALOG 0
#define OTHER_VOLTS 4.2
#define OTHER_VOLTS_ANALOG 1023

// Global variables
float current = 0;
float packVoltage = 0;
float cell_voltages[8];
uint8_t cell_voltage_pins[8] = {CELL_SENSE_1, CELL_SENSE_2, CELL_SENSE_3, CELL_SENSE_4, CELL_SENSE_5, CELL_SENSE_6, CELL_SENSE_7, CELL_SENSE_8};
uint32_t lastOvercurrentErrorTimestamp = 0;


// Function declarations
void roverEStop();
void roverRestart();

void errorOvercurrent();
void errorCellUndervoltage();
void errorCellCritical();

float mapAnalog();

#endif /* BMS_SOFTWARE_H */