/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
#ifndef __REF_B_H__
#define __REF_B_H__

//*****************************************************************************
//
//! \addtogroup ref_api
//! @{
//
//*****************************************************************************

#include "../inc/msp.h"
#include <stdbool.h>
#include <stdint.h>

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
//The following are values that can be passed to Ref_setReferenceVoltage()
//in the referenceVoltageSelect parameter.
//
//*****************************************************************************
#define REF_A_VREF1_2V  REF_A_CTL0_VSEL_0
#define REF_A_VREF1_45V REF_A_CTL0_VSEL_1
#define REF_A_VREF2_5V  REF_A_CTL0_VSEL_3

//*****************************************************************************
//
//The following are values that are returned by Ref_getBandgapMode().
//
//*****************************************************************************
#define REF_A_STATICMODE 0x0
#define REF_A_SAMPLEMODE REF_A_CTL0_BGMODE

//*****************************************************************************
//
//! Sets the reference voltage for the voltage generator.
//!
//! \param referenceVoltageSelect is the desired voltage to generate for a
//!       reference voltage.
//!        Valid values are:
//!        - \b REF_A_VREF1_2V [Default]
//!        - \b REF_A_VREF1_45V
//!        - \b REF_A_VREF2_5V
//!        Modified bits are \b REFVSEL of \b REFCTL0 register.
//!
//! This function sets the reference voltage generated by the voltage generator
//! to be used by other peripherals. This reference voltage will only be valid
//! while the REF module is in control.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns \b REF_BUSY,
//! this function  will have no effect.
//!
//! \return none
//
//*****************************************************************************
extern void REF_A_setReferenceVoltage(uint_fast8_t referenceVoltageSelect);

//*****************************************************************************
//
//! Disables the internal temperature sensor to save power consumption.
//!
//! This function is used to turn off the internal temperature sensor to save
//! on power consumption. The temperature sensor is enabled by default. Please
//! note, that giving ADC12 module control over the REF module, the state of the
//! temperature sensor is dependent on the controls of the ADC12 module.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink  returns
//! \b REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFTCOFF of \b REFCTL0 register.
//! \return none
//
//*****************************************************************************
extern void REF_A_disableTempSensor(void);

//*****************************************************************************
//
//! Enables the internal temperature sensor.
//!
//! This function is used to turn on the internal temperature sensor to use by
//! other peripherals. The temperature sensor is enabled by default.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns
//! \b REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFTCOFF of \b REFCTL0 register.
//!
//! \return none
//
//*****************************************************************************
extern void REF_A_enableTempSensor(void);

//*****************************************************************************
//
//! Outputs the reference voltage to an output pin.
//!
//! This function is used to output the reference voltage being generated to an
//! output pin. Please note, the output pin is device specific. Please note,
//! that giving ADC12 module control over the REF module, the state of the
//! reference voltage as an output to a pin is dependent on the controls of the
//! ADC12 module.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns
//! \b REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFOUT of \b REFCTL0 register.
//! \return none
//
//*****************************************************************************
extern void REF_A_enableReferenceVoltageOutput(void);

//*****************************************************************************
//
//! Disables the reference voltage as an output to a pin.
//!
//! This function is used to disables the reference voltage being generated to
//! be given to an output pin.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns
//! \b REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFOUT of \b REFCTL0 register.
//! \return none
//
//*****************************************************************************
extern void REF_A_disableReferenceVoltageOutput(void);

//*****************************************************************************
//
//! Enables the reference voltage to be used by peripherals.
//!
//! This function is used to enable the generated reference voltage to be used
//! other peripherals or by an output pin, if enabled. Please note, that giving
//! ADC12 module control over the REF module, the state of the reference voltage
//! is dependent on the controls of the ADC12 module.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns
//! REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFON of \b REFCTL0 register.
//! \return none
//
//*****************************************************************************
extern void REF_A_enableReferenceVoltage(void);

//*****************************************************************************
//
//! Disables the reference voltage.
//!
//! This function is used to disable the generated reference voltage.
//! Please note, if the \link REF_A_isRefGenBusy() \endlink returns
//!  \b  REF_A_BUSY, this function will have no effect.
//!
//! Modified bits are \b REFON of \b REFCTL0 register.
//! \return none
//
//*****************************************************************************
extern void REF_A_disableReferenceVoltage(void);

//*****************************************************************************
//
//! Returns the bandgap mode of the REF module.
//!
//! This function is used to return the bandgap mode of the REF module,
//! requested by the peripherals using the bandgap. If a peripheral requests
//! static mode, then the bandgap mode will be static for all modules, whereas
//! if all of the peripherals using the bandgap request sample mode, then that
//! will be the mode returned. Sample mode allows the bandgap to be active only
//! when necessary to save on power consumption, static mode requires the
//! bandgap to be active until no peripherals are using it anymore.
//!
//! \return The bandgap mode of the REF module:
//!        - \b REF_A_STATICMODE if the bandgap is operating in static mode
//!        - \b REF_A_SAMPLEMODE if the bandgap is operating in sample mode
//
//*****************************************************************************
extern uint_fast8_t REF_A_getBandgapMode(void);

//*****************************************************************************
//
//! Returns the active status of the bandgap in the REF module.
//!
//! This function is used to return the active status of the bandgap in the REF
//! module. If the bandgap is in use by a peripheral, then the status will be
//! seen as active.
//!
//! \return true if the bandgap is being used, false otherwise
//
//*****************************************************************************
extern bool REF_A_isBandgapActive(void);

//*****************************************************************************
//
//! Returns the busy status of the reference generator in the REF module.
//!
//! This function is used to return the busy status of the reference generator
//! in the REF module. If the ref. generator is in use by a peripheral, then the
//! status will be seen as busy.
//!
//! \return true if the reference generator is being used, false otherwise.
//*****************************************************************************
extern bool REF_A_isRefGenBusy(void);

//*****************************************************************************
//
//! Returns the active status of the reference generator in the REF module.
//!
//! This function is used to return the active status of the reference generator
//! in the REF module. If the ref. generator is on and ready to use, then the
//! status will be seen as active.
//!
//! \return true if the reference generator is active, false otherwise.
//
//*****************************************************************************
extern bool REF_A_isRefGenActive(void);

//*****************************************************************************
//
//! Returns the busy status of the reference generator in the REF module.
//!
//! This function is used to return the buys status of the buffered bandgap
//! voltage in the REF module. If the ref. generator is on and ready to use,
//! then the status will be seen as active.
//!
//! \return true if the buffered bandgap voltage is ready to be used, false
//!         otherwise
//
//*****************************************************************************
extern bool REF_A_getBufferedBandgapVoltageStatus(void);

//*****************************************************************************
//
//! Returns the busy status of the variable reference voltage in the REF module.
//!
//! This function is used to return the buys status of the variable reference
//! voltage in the REF module. If the ref. generator is on and ready to use,
//! then the status will be seen as active.
//!
//! \return true if the variable bandgap voltage is ready to be used, false
//!         otherwise
//
//*****************************************************************************
extern bool REF_A_getVariableReferenceVoltageStatus(void);

//*****************************************************************************
//
//! Enables the one-time trigger of the reference voltage.
//!
//! Triggers the one-time generation of the variable reference voltage.  Once
//! the reference voltage request is set, this bit is cleared by hardware
//!
//! Modified bits are \b REFGENOT of \b REFCTL0 register.
//!
//! \return none
//
//*****************************************************************************
extern void REF_A_setReferenceVoltageOneTimeTrigger(void);

//*****************************************************************************
//
//! Enables the one-time trigger of the buffered bandgap voltage.
//!
//! Triggers the one-time generation of the buffered bandgap voltage.  Once
//! the buffered bandgap voltage request is set, this bit is cleared by hardware
//!
//! Modified bits are \b RefGOT of \b REFCTL0 register.
//!
//! \return none
//
//*****************************************************************************
extern void REF_A_setBufferedBandgapVoltageOneTimeTrigger(void);

/* Defines for future devices that might have multiple instances */
#define REF_A_setReferenceVoltageMultipleInstance(a,b) REF_A_setReferenceVoltage(b)
#define REF_A_disableTempSensorMultipleInstance(a) REF_A_disableTempSensor()
#define REF_A_enableTempSensorMultipleInstance(a) REF_A_enableTempSensor()
#define REF_A_enableReferenceVoltageOutputMultipleInstance(a) REF_A_enableReferenceVoltageOutput()
#define REF_A_disableReferenceVoltageOutputMultipleInstance(a) REF_A_disableReferenceVoltageOutput()
#define REF_A_enableReferenceVoltageMultipleInstance(a) REF_A_enableReferenceVoltage()
#define REF_A_disableReferenceVoltageMultipleInstance(a) REF_A_disableReferenceVoltage()
#define REF_A_getBandgapModeMultipleInstance(a) REF_A_getBandgapMode()
#define REF_A_isBandgapActiveMultipleInstance(a) REF_A_isBandgapActive()
#define REF_A_isRefGenBusyMultipleInstance(a) REF_A_isRefGenBusy()
#define REF_A_isRefGenActiveMultipleInstance(a) REF_A_isRefGenActive()
#define REF_A_getBufferedBandgapVoltageStatusMultipleInstance(a) REF_A_getBufferedBandgapVoltageStatus()
#define REF_A_getVariableReferenceVoltageStatusMultipleInstance(a) REF_A_getVariableReferenceVoltageStatus()
#define REF_A_setReferenceVoltageOneTimeTriggerMultipleInstance(a) REF_A_setReferenceVoltageOneTimeTrigger()
#define REF_A_setBufferedBandgapVoltageOneTimeTriggerMultipleInstance(a) REF_A_setBufferedBandgapVoltageOneTimeTrigger()

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

//*****************************************************************************
//
// Close the Doxygen group.
//! @}
//
//*****************************************************************************

#endif // __REF_A_H__
