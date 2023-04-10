/*
 * dio_program.c
 *
 *     Created on: Apr 10, 2023
 *         Author: Hossam Elwahsh - https://github.com/HossamElwahsh
 *    Description: This file contains all Digital Input Output (DIO) functions' implementation.
 *  MCU Datasheet: AVR ATmega32
 *                  https://ww1.microchip.com/downloads/en/DeviceDoc/Atmega32A-DataSheet-Complete-DS40002072A.pdf
 */

/* MCAL */
#include "dio_private.h"
#include "dio_config.h"
#include "dio_interface.h"

/*********************************************************************************************************************/


/**
 * @brief Initializes a pin of the DIO interface with a given direction
 *
 * This function initializes a pin of the Digital Input/Output (DIO) interface with the given direction.
 * It sets the Data Direction Register (DDR) of the port to the given direction for the specified pin.
 *
 * @param[in] u8_a_pinNumber The pin number of the DIO interface to initialize (0 to 7)
 * @param[in] en_a_portNumber The port number of the DIO interface to initialize (A, B, C or D)
 * @param[in] en_a_direction The direction to set for the pin (INPUT or OUTPUT)
 *
 * @return An EN_DIO_Error_T value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_Error otherwise)
 */
EN_DIO_Error_T DIO_init(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber, EN_DIO_DIRECTION_T en_a_direction) {

    if(u8_a_pinNumber > DIO_MAX_PIN_NO || u8_a_pinNumber < DIO_MIN_PIN_NO) return DIO_Error;

    switch (en_a_portNumber) {

        case A:
            if (en_a_direction == OUT) {
                SET_BIT(DIO_U8_DDR_A_REG, u8_a_pinNumber); // set pin as output
            } else if (en_a_direction == IN) {
                CLR_BIT(DIO_U8_DDR_A_REG, u8_a_pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }

            break;
        case B:
            if (en_a_direction == OUT) {
                SET_BIT(DIO_U8_DDR_B_REG, u8_a_pinNumber); // set pin as output
            } else if (en_a_direction == IN) {
                CLR_BIT(DIO_U8_DDR_B_REG, u8_a_pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case C:
            if (en_a_direction == OUT) {
                SET_BIT(DIO_U8_DDR_C_REG, u8_a_pinNumber); // set pin as output
            } else if (en_a_direction == IN) {
                CLR_BIT(DIO_U8_DDR_C_REG, u8_a_pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case D:
            if (en_a_direction == OUT) {
                SET_BIT(DIO_U8_DDR_D_REG, u8_a_pinNumber); // set pin as output
            } else if (en_a_direction == IN) {
                CLR_BIT(DIO_U8_DDR_D_REG, u8_a_pinNumber); // set pin as input
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        default:
            // bad config
            return DIO_Error;
    }
    return DIO_OK;
}


/**
 * @brief Reads the value of a pin on a port of the DIO interface
 *
 * This function reads the value of a pin on a port of the Digital Input/Output (DIO) interface. It returns
 * the value of the specified pin as a 0 or 1 in the u8_a_value parameter. The pin number and port number
 * must be valid and in range for the DIO interface to function correctly.
 *
 * @param[in] u8_a_pinNumber The pin number to read from the port (0 to 7)
 * @param[in] en_a_portNumber The port number of the DIO interface to read from (A, B, C or D)
 * @param[out] u8_a_value Pointer to an unsigned 8-bit integer where the value of the pin will be stored
 *
 * @return An EN_DIO_Error_T value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_Error otherwise)
 */
EN_DIO_Error_T DIO_read(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber, u8 * u8_a_value) {
    if(u8_a_pinNumber > DIO_MAX_PIN_NO || u8_a_pinNumber < DIO_MIN_PIN_NO) return DIO_Error;

    switch (en_a_portNumber) {
        case A:
            *u8_a_value = GET_BIT(DIO_U8_PIN_A_REG, u8_a_pinNumber);
            return DIO_OK;
        case B:
            *u8_a_value = GET_BIT(DIO_U8_PIN_B_REG, u8_a_pinNumber);
            return DIO_OK;
        case C:
            *u8_a_value = GET_BIT(DIO_U8_PIN_C_REG, u8_a_pinNumber);
            return DIO_OK;
        case D:
            *u8_a_value = GET_BIT(DIO_U8_PIN_D_REG, u8_a_pinNumber);
            return DIO_OK;

        default:
            return DIO_Error;
    }
}


/**
 * @brief Writes a digital value to a specific pin in a specific port.
 *
 * This function writes a digital value to a specific pin in a specific port.
 * It first checks if the given pin number is valid or not, and if it's not valid, it returns an error.
 * If the pin number is valid, it writes the value to the specified port using the WRITE_BIT macro.
 * If the given value is not a valid digital value, the function returns an error.
 *
 * @param[in] u8_a_pinNumber The number of the pin to write to.
 * @param[in] en_a_portNumber The port number to write to.
 * @param[in] u8_a_value The digital value to write (either DIO_U8_PIN_HIGH or DIO_U8_PIN_LOW).
 *
 * @return EN_DIO_Error_T Returns DIO_OK if the write is successful, DIO_Error otherwise.
    */
EN_DIO_Error_T DIO_write(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber, u8 u8_a_value) {
    if(u8_a_pinNumber > DIO_MAX_PIN_NO || u8_a_pinNumber < DIO_MIN_PIN_NO) return DIO_Error;
    switch (en_a_portNumber) {
        case A:
            if (u8_a_value == DIO_U8_PIN_HIGH || u8_a_value == DIO_U8_PIN_LOW) {
                WRITE_BIT(DIO_U8_PORT_A_REG, u8_a_pinNumber, u8_a_value);
            } else {
                // error handling
                return DIO_Error;
            }

            break;
        case B:
            if (u8_a_value == DIO_U8_PIN_HIGH || u8_a_value == DIO_U8_PIN_LOW) {
                WRITE_BIT(DIO_U8_PORT_B_REG, u8_a_pinNumber, u8_a_value);
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case C:
            if (u8_a_value == DIO_U8_PIN_HIGH || u8_a_value == DIO_U8_PIN_LOW) {
                WRITE_BIT(DIO_U8_PORT_C_REG, u8_a_pinNumber, u8_a_value);
            } else {
                // error handling
                return DIO_Error;
            }
            break;
        case D:
            if (u8_a_value == DIO_U8_PIN_HIGH || u8_a_value == DIO_U8_PIN_LOW) {
                WRITE_BIT(DIO_U8_PORT_D_REG, u8_a_pinNumber, u8_a_value);

            }else {
                // error handling
                return DIO_Error;
            }
            break;
    }
    return DIO_OK;
}



/**
 * @brief Toggles the state of a pin in the specified port.
 *
 * This function toggles the state of a pin in the specified port.
 *
 * @param u8_a_pinNumber The pin number to toggle.
 * @param en_a_portNumber The port to which the pin belongs.
 * @return EN_DIO_Error_T Returns DIO_OK on success or DIO_Error if an error occurred.
 */
EN_DIO_Error_T DIO_toggle(u8 u8_a_pinNumber, EN_DIO_PORT_T en_a_portNumber){
    if(u8_a_pinNumber > DIO_MAX_PIN_NO || u8_a_pinNumber < DIO_MIN_PIN_NO) return DIO_Error;

    u8 *val = DIO_U8_PIN_LOW;
    EN_DIO_Error_T res = DIO_read(u8_a_pinNumber, en_a_portNumber, val);
    if (res == DIO_OK) {
        // toggle bit
        *val = ((*val) == DIO_U8_PIN_LOW) ? DIO_U8_PIN_HIGH : DIO_U8_PIN_LOW;

        DIO_write(u8_a_pinNumber, en_a_portNumber, *val);
        return DIO_OK;
    } else {
        return DIO_Error;
    }
}

/**
 * @brief Initializes a port of the DIO interface with a given direction and mask
 *
 * This function initializes a port of the Digital Input/Output (DIO) interface with the given direction
 * and mask. It sets the Data Direction Register (DDR) of the port to the given direction, while masking
 * off any bits that are not specified in the mask parameter. The DDR determines whether the corresponding
 * pins of the port are inputs or outputs.
 *
 * @param[in] en_a_portNumber The port number of the DIO interface to initialize (A, B, C or D)
 * @param[in] en_a_dir The direction to set for the port (INPUT or OUTPUT)
 * @param[in] u8_a_mask The mask to use when setting the DDR of the port
 *
 * @return An EN_DIO_Error_T value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_Error otherwise)
 */
EN_DIO_Error_T DIO_portInit(EN_DIO_PORT_T en_a_portNumber, EN_DIO_DIRECTION_T en_a_dir, u8 u8_a_mask) {
    if(u8_a_mask == 0) u8_a_mask = 0xFF;

    // output only masked u8_a_byte u8_a_value (used karnaugh map to calculate expression)
    switch (en_a_portNumber) {
        case A:
            DIO_U8_DDR_A_REG = ((~u8_a_mask) & DIO_U8_DDR_A_REG) | (u8_a_mask & en_a_dir);
            break;
        case B:
            DIO_U8_DDR_B_REG = ((~u8_a_mask) & DIO_U8_DDR_B_REG) | (u8_a_mask & en_a_dir);
            break;
        case C:
            DIO_U8_DDR_C_REG = ((~u8_a_mask) & DIO_U8_DDR_C_REG) | (u8_a_mask & en_a_dir);
            break;
        case D:
            DIO_U8_DDR_D_REG = ((~u8_a_mask) & DIO_U8_DDR_D_REG) | (u8_a_mask & en_a_dir);
            break;
        default:
            return DIO_Error;
    }
    return DIO_OK;
}

/**
 * @brief Writes a byte to a port of the DIO interface
 *
 * This function writes a byte to a port of the Digital Input/Output (DIO) interface. It sets the output
 * value of the Data Register (PORT) of the port to the given byte, while masking off any bits that are not
 * specified in the mask parameter. The PORT determines the state of the corresponding pins of the port that
 * are configured as outputs.
 *
 * @param[in] en_a_portNumber The port number of the DIO interface to write to (A, B, C or D)
 * @param[in] u8_a_byte The byte value to write to the port
 * @param[in] u8_a_mask The mask to use when setting the PORT of the port
 *
 * @return An EN_DIO_Error_T value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_Error otherwise)
 */
EN_DIO_Error_T DIO_portWrite(EN_DIO_PORT_T en_a_portNumber, u8 u8_a_byte, u8 u8_a_mask) {
    if(u8_a_mask == 0) u8_a_mask = 0xFF;

    // output only masked u8_a_byte u8_a_value (used karnaugh map to calculate expression)
    switch (en_a_portNumber) {
        case A:
            DIO_U8_PORT_A_REG = ((~u8_a_mask) & DIO_U8_PORT_A_REG) | (u8_a_mask & u8_a_byte);
            break;
        case B:
            DIO_U8_PORT_B_REG = ((~u8_a_mask) & DIO_U8_PORT_B_REG) | (u8_a_mask & u8_a_byte);
            break;
        case C:
            DIO_U8_PORT_C_REG = ((~u8_a_mask) & DIO_U8_PORT_C_REG) | (u8_a_mask & u8_a_byte);
            break;
        case D:
            DIO_U8_PORT_D_REG = ((~u8_a_mask) & DIO_U8_PORT_D_REG) | (u8_a_mask & u8_a_byte);
            break;
        default:
            return DIO_Error;
    }
    return DIO_OK;
}

/**
 * @brief Toggles the state of the pins of a port of the DIO interface
 *
 * This function toggles the state of the pins of a port of the Digital Input/Output (DIO) interface.
 * It XORs the PORT of the port with the given mask, which inverts the state of the pins that correspond
 * to the bits set in the mask. The PORT determines the state of the corresponding pins of the port that
 * are configured as outputs.
 *
 * @param[in] en_a_portNumber The port number of the DIO interface to toggle (A, B, C or D)
 * @param[in] u8_a_mask The mask to use when toggling the PORT of the port
 *
 * @return An EN_DIO_Error_T value indicating the success or failure of the operation
 *         (DIO_OK if the operation succeeded, DIO_Error otherwise)
 */
EN_DIO_Error_T DIO_portToggle(EN_DIO_PORT_T en_a_portNumber, u8 u8_a_mask)
{
    if(u8_a_mask == 0) u8_a_mask = 0xFF;
    switch (en_a_portNumber) {
        case A:
            DIO_U8_PORT_A_REG ^= u8_a_mask;
            break;
        case B:
            DIO_U8_PORT_B_REG ^= u8_a_mask;
            break;
        case C:
            DIO_U8_PORT_C_REG ^= u8_a_mask;
            break;
        case D:
            DIO_U8_PORT_D_REG ^= u8_a_mask;
            break;
        default:
            return DIO_Error;
    }
    return DIO_OK;
}
