/*
 * BTN_Program.c
 *
 *   Created on: Nov 20, 2022
 *       Author: Abdelrhman Walaa - https://github.com/AbdelrhmanWalaa
 *  Description: This file contains all Button (BTN) functions' implementation.
 */

/* HAL */
#include "btn_config.h"
#include "btn_interface.h"

/**
 * @brief Initialize a GPIO pin as an input pin
 *
 * This function initializes a specified GPIO pin as an input pin using the DIO_init() function.
 *
 * @param [in]u8_a_pinNumber The pin number to be initialized (0-7).
 * @param [in]en_a_portNumber The port number to which the pin belongs (PORT_A, ..).
 *
 * @return STD_OK if the pin initialization was successful, STD_NOK otherwise.
 */
u8 BTN_init(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber) {
    if (DIO_init(u8_a_pinNumber, en_a_portNumber, DIO_IN) == DIO_OK) {
        return STD_OK;
    }
    return STD_NOK;
}

/**
 * @brief Get the current state of a specified button
 *
 * This function reads the current state of a specified button by calling the DIO_read() function.
 * The button ID is specified as an input parameter, and the current state is returned in an output parameter.
 * If the button ID is out of range or the output parameter pointer is NULL, the function returns an error state (STD_NOK).
 *
 * @param [in]u8_a_btnId The ID of the button to read (BTN_U8_1 to BTN_U8_8).
 * @param [out]u8ptr_a_returnedBtnState A pointer to an 8-bit unsigned integer where the button state will be stored.
 *
 * @return STD_OK if the button state was read successfully, STD_NOK otherwise.
 */
u8 BTN_getBtnState(u8 u8_a_btnId, u8 *u8ptr_a_returnedBtnState) {
    /* Define local variable to set the error state = OK */
    u8 Loc_u8ErrorState = STD_OK;

    /* Check 1: BTNId is in the valid range, and Pointer is not equal to NULL */
    if ((u8_a_btnId <= BTN_U8_8) && (u8ptr_a_returnedBtnState != NULL)) {
        /* Check 1.1: Required BTNId */
        switch (u8_a_btnId) {
            case BTN_U8_1:
                DIO_read(BTN_U8_1_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_2:
                DIO_read(BTN_U8_2_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_3:
                DIO_read(BTN_U8_3_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_4:
                DIO_read(BTN_U8_4_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_5:
                DIO_read(BTN_U8_5_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_6:
                DIO_read(BTN_U8_6_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_7:
                DIO_read(BTN_U8_7_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
            case BTN_U8_8:
                DIO_read(BTN_U8_8_PIN, BTN_U8_PORT, u8ptr_a_returnedBtnState);
                break;
        }
    }
        /* Check 2: BTNId is not in the valid range, or Pointer is equal to NULL */
    else {
        /* Update error state = NOK, wrong BTNId or Pointer is NULL! */
        Loc_u8ErrorState = STD_NOK;
    }

    return Loc_u8ErrorState;
}

/*******************************************************************************************************************************************************************/