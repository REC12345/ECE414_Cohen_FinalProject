cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(ECE414_Cohen_FinalProject)

pico_sdk_init()

add_executable(ECE414_Cohen_FinalProject    
    main.c
    UI/debounce_ts.c
    UI/user_interface.c
    UI/TouchScreen.c
    UI/TFTMaster.c
)

pico_generate_pio_header(ECE414_Cohen_FinalProject ${CMAKE_CURRENT_LIST_DIR}/SPIPIO.pio)

target_link_libraries(ECE414_Cohen_FinalProject  
    pico_stdlib
    hardware_gpio 
    hardware_pio 
    hardware_irq
    hardware_adc
    pico_bootsel_via_double_reset
)

pico_enable_stdio_uart(ECE414_Cohen_FinalProject 1)
pico_add_extra_outputs(ECE414_Cohen_FinalProject)