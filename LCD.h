#ifndef LCD_H
#define LCD_H

void LCD_init();
void LCD_update(float temp, float packVoltage, float cell_voltages[], float current);

#endif // LCD_H