cmake_minimum_required(VERSION 3.25)
project(MovingCar C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(MovingCar
        main.c MCAL/dio/dio_program.c LIB/bit_math.h LIB/std.h APP/app_program.c APP/app_interface.h APP/app_config.h HAL/btn/btn_config.h HAL/btn/btn_interface.h HAL/btn/btn_program.c HAL/dcm/dcm_config.h HAL/dcm/dcm_interface.h HAL/dcm/dcm_program.c HAL/led/led_config.h HAL/led/led_interface.h HAL/led/led_program.c MCAL/exi/exi_private.h MCAL/exi/exi_interface.h MCAL/exi/exi_program.c MCAL/gli/gli_interface.h MCAL/gli/gli_private.h MCAL/gli/gli_program.c MCAL/timer/timer_config.h MCAL/timer/timer_program.c MCAL/timer/timer_private.h MCAL/timer/timer_interface.h)