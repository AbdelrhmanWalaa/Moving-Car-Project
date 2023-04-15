/*
 * app_config.h
 *
 *   Created on: Apr 10, 2023
 *       Author: Hacker Kermit - https://github.com/AbdelrhmanWalaa/Moving-Car-Project.git
 *  Description: This file contains all Application (APP) pre-build configurations, through which user can configure before using the APP.
 */ 

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* ***********************************************************************************************/
/* APP Configurations */

/* BTNs Config */
#define APP_STOP_BTN			2
#define APP_START_BTN			3

/* LEDs Config */
#define APP_MOVE_FWD_LD_LED		0
#define APP_MOVE_FWD_SD_LED		1
#define APP_ROTATE_LED			2
#define APP_STOP_LED			3

/* Delays/Timing Config */
#define APP_STARTING_DELAY      1000
#define APP_FWD_LD_DURATION     3000
#define APP_FWD_LD_DUTY         50
#define APP_ROTATION_DELAY      500
#define APP_ROTATION_DURATION   620
#define APP_FWD_SD_DURATION     2000
#define APP_FWD_SD_DUTY         30

/* APP_BREAK_FLAG */
#define APP_BREAK_FLAG_UP       1
#define APP_BREAK_FLAG_DOWN     0

/* End of Configurations */

/* ***********************************************************************************************/

#endif /* APP_CONFIG_H_ */