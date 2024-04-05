#include "BMS_Software.h"


void setup () {
    Serial.begin(115200);
    Serial.println("BMS Setup");

    //I/O Pins
    pinMode(BUZZER, OUTPUT);
    pinMode(ESTOP, OUTPUT);
    digitalWrite(BUZZER, LOW);
    digitalWrite(ESTOP, HIGH);

    //RoveComm
    Serial.println("RoveComm Initializing...");
    RoveComm.begin(RC_BMSBOARD_FIRSTOCTET, RC_BMSBOARD_SECONDOCTET, RC_BMSBOARD_THIRDOCTET, RC_BMSBOARD_FOURTHOCTET, &TCPServer); 
    Serial.println("Complete."); 

    //Telemetry
    Telemetry.begin(telemetry, TELEMETRY_PERIOD);
}


void loop() {
    // Read voltage and current from battery
    readCells();
    current = mapAnalog(CURRENT_SENSE, ZERO_CURRENT_AMPS, OTHER_CURRENT_AMPS, ZERO_CURRENT_ANALOG, OTHER_CURRENT_ANALOG);

    // Check for critical cells
    for (uint8_t i = 0; i < NUM_CELLS; i++) {
        if (cell_voltages[i] <= CELL_CRITICAL_THRESHOLD) {
            errorCellCritical();
        }
    }

    // Check for undervoltage cells
    for (uint8_t i = 0; i < NUM_CELLS; i++) {
        if (cell_voltages[i] <= CELL_UNDERVOLT_THRESHOLD) {
            errorCellUndervoltage();
        }
    }

    //Check for overcurrent
    if (current >= MAX_CURRENT) {
        errorOvercurrent();
    }

    // Handle incoming RoveComm packets
    rovecomm_packet packet = RoveComm.read();

    switch (packet.data_id) {
        //Estop
        case RC_BMSBOARD_ESTOP_DATA_ID:
            roverEStop();
            break;

        //Reboot
        case RC_BMSBOARD_REBOOT_DATA_ID:
            roverRestart();
            break;
    }
}


void telemetry() {
    RoveComm.write(RC_BMSBOARD_PACKCURRENT_DATA_ID, RC_BMSBOARD_PACKCURRENT_DATA_COUNT, current);
    RoveComm.write(RC_BMSBOARD_PACKVOLTAGE_DATA_ID, RC_BMSBOARD_PACKVOLTAGE_DATA_COUNT, packVoltage);
    RoveComm.write(RC_BMSBOARD_CELLVOLTAGE_DATA_ID, RC_BMSBOARD_CELLVOLTAGE_DATA_COUNT, cell_voltages);
}


void readCells() {
    // Repeatedly read the voltage of all cells
    // To eliminate voltage drops from current spikes, store the largest value into the cell_voltages array
    for (uint16_t j = 0; j < NUM_VOLTAGE_READINGS; j++) {
        for (uint8_t i = 0; i < NUM_CELLS; i++) {
            float new_voltage = mapAnalog(cell_voltage_pins[i], ZERO_VOLTS, OTHER_VOLTS, ZERO_VOLTS_ANALOG, OTHER_VOLTS_ANALOG);
            if (j == 0 || cell_voltages[i] < new_voltage) {
                cell_voltages[i] = new_voltage;
            }
        }
    }

    // Calculate pack voltage; global variable is used in interrupt, so it should only be changed after the total is calculated
    float pv = 0;
    for (uint8_t i = 0; i < NUM_CELLS; i++) {
        pv += cell_voltages[i];
    }
    packVoltage = pv;
}


float mapAnalog(uint8_t pin, float units1, float units2, uint16_t analog1, uint16_t analog2) {
    float slope = (units2 - units1) / (analog2 - analog1);
    return ((analogRead(pin) - analog1) * slope) + units1;
}


void roverEStop() {
    digitalWrite(ESTOP, LOW);

    //beep bc bms is on, but everything else off
    while (true) {
        // smoke detector beep pattern
        digitalWrite(BUZZER, HIGH);
        delay(1000);
        digitalWrite(BUZZER, LOW);
        delay(30000);
    }
}


void roverRestart() {
    digitalWrite(ESTOP, LOW);
    digitalWrite(BUZZER, HIGH);
    delay(RESTART_DELAY);
    digitalWrite(ESTOP, HIGH);
    digitalWrite(BUZZER, LOW);
}


uint8_t dummy = 0;

void errorOvercurrent() {
    RoveComm.writeReliable(RC_BMSBOARD_OVERCURRENT_DATA_ID, RC_BMSBOARD_OVERCURRENT_DATA_COUNT, dummy);

    // Occasional overcurrent errors are acceptable
    // If more than one occurs within a given time period, assume short circuit and estop
    uint32_t current_time = millis();
    if ((current_time - lastOvercurrentErrorTimestamp) >= ALLOWABLE_OVERCURRENT_PERIOD) {
        roverRestart();
        lastOvercurrentErrorTimestamp = current_time;
    } else {
        roverEStop();
    }
}


void errorCellUndervoltage() {
    RoveComm.writeReliable(RC_BMSBOARD_CELLUNDERVOLTAGE_DATA_ID, RC_BMSBOARD_CELLUNDERVOLTAGE_DATA_COUNT, dummy);
    roverEStop();
}


void errorCellCritical() {
    RoveComm.writeReliable(RC_BMSBOARD_CELLCRITICAL_DATA_ID, RC_BMSBOARD_CELLCRITICAL_DATA_COUNT, dummy);
    roverEStop();
}