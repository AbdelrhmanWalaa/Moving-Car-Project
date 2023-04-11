/*
 * led_program.c
 *
 *   Created on: Apr 10, 2023
 *       Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *  Description: This file contains all Light Emitting Diode (LED) functions' implementation.
 */

/* HAL */
#include "LED_Interface.h"

/* ******************************************************************** */
/* LED Prototypes                                                       */
/* ******************************************************************** */

/**
 * @brief Initializes a single LED pin as output
 *
 * This function initializes a single LED pin as output.
 *
 * @param[in] en_a_ledPort The port where the LED is located (PORT_A, PORT_B, PORT_C or PORT_D)
 * @param[in] u8_a_ledPin The pin number of the LED (DIO_U8_PIN_0 to DIO_U8_PIN_7)
 *
 * @return EN_LED_ERROR_t Returns LED_OK if the LED was initialized successfully,
 * LED_ERROR otherwise.
 */
EN_LED_ERROR_t LED_init(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_ledPin) {
    EN_DIO_ERROR_T dioError = DIO_init(u8_a_ledPin, en_a_ledPort, DIO_OUT);
    return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * Turn on an LED connected to a specific pin on a specific port.
 *
 * @param[in] en_a_ledPort The port where the LED is connected. (PORT_A, PORT_B, PORT_C, or PORT_D)
 * @param[in] u8_a_ledPin The pin number where the LED is connected. (DIO_U8_PIN_0 to DIO_U8_PIN_7)
 * @return The status of the LED operation, either LED_OK or LED_ERROR.
 */
EN_LED_ERROR_t LED_on(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_ledPin) {
    EN_DIO_ERROR_T dioError = DIO_write(u8_a_ledPin, en_a_ledPort, DIO_U8_PIN_HIGH);
    return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * @brief Turns off an LED on a specific port and pin.
 *
 * @param[in] en_a_ledPort the port of the LED to turn off (PORT_A, PORT_B, PORT_C, or PORT_D)
 * @param[in] u8_a_ledPin the pin number of the LED to turn off (DIO_U8_PIN_0 to DIO_U8_PIN_7)
 * @return EN_LED_ERROR_t LED_OK if successful, or LED_ERROR if there was an error.
 */
EN_LED_ERROR_t LED_off(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_ledPin) {
EN_DIO_ERROR_T dioError = DIO_write(u8_a_ledPin, en_a_ledPort, DIO_U8_PIN_LOW);
return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}


/* ******************************************************************** */
/* LED ARRAYS Prototypes                                                */
/* ******************************************************************** */

/**
 * @brief Initializes a group of LEDs connected to a specific port and pins with
 *        a specified mask as outputs.
 *
 * @param [in]en_a_ledPort The port to which the LEDs are connected.
 * @param [in]u8_a_mask The mask to set the direction of the specified pins.
 *
 * @return EN_LED_ERROR_t Returns LED_OK if the operation is successful, and
 *         LED_ERROR if the operation fails.
 */
EN_LED_ERROR_t LED_arrayInit(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_mask) {
    EN_DIO_ERROR_T dioError = DIO_portInit(en_a_ledPort, DIO_OUT, u8_a_mask);
    return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * @brief Turns on the specified LED pins by setting the corresponding bits in the specified LED port to high.
 *
 * @param [in]en_a_ledPort The LED port to turn on the LED pins from (PORT_A, PORT_B, PORT_C or PORT_D).
 * @param [in]u8_a_mask The bit mask specifying which LED pins to turn on. (DIO_NO_MASK, DIO_MASK_BITS_n..)
 * @return EN_LED_ERROR_t Returns LED_OK if the LED pins were successfully turned on,
 *         or LED_ERROR if there was an error in turning on the LED pins.
 */
EN_LED_ERROR_t LED_arrayOn(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_mask) {
    EN_DIO_ERROR_T dioError = DIO_portWrite(en_a_ledPort, DIO_U8_PORT_HIGH, u8_a_mask);
    return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}

/**
 * @brief Turns off the specified LED pins by setting the corresponding bits in the specified LED port to low.
 *
 * @param [in]en_a_ledPort The LED port to turn off the LED pins from (PORT_A, PORT_B, PORT_C or PORT_D).
 * @param [in]u8_a_mask The bit mask specifying which LED pins to turn off.  (DIO_NO_MASK, DIO_MASK_BITS_n..)
 * @return EN_LED_ERROR_t Returns LED_OK if the LED pins were successfully turned off, or LED_ERROR if there
 *         was an error in turning off the LED pins.
 */
EN_LED_ERROR_t LED_arrayOff(EN_DIO_PORT_T en_a_ledPort, u8 u8_a_mask){
    EN_DIO_ERROR_T dioError = DIO_portWrite(en_a_ledPort, DIO_U8_PORT_LOW, u8_a_mask);
    return dioError == DIO_ERROR ? LED_ERROR : LED_OK;
}