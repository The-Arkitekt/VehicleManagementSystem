cmake_minimum_required(VERSION 3.16)

set(STM32F429_COMMON_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../../STM32f429CommonLibrary)
set(CMAKE_TOOLCHAIN_FILE ${STM32F429_COMMON_LIBRARY_DIR}/cmake/toolchain-arm-none-eabi.cmake)

project(VehicleManagementSystem C CXX ASM)
set(SOURCES
 main.cpp
 ${PROJECT_SOURCE_DIR}/../../STM32f429CommonLibrary/startup/startup_stm32f429xx.s
)

add_subdirectory(${STM32F429_COMMON_LIBRARY_DIR} ${STM32F429_COMMON_LIBRARY_DIR}/bld)

add_executable(${PROJECT_NAME}
  ${SOURCES}
)

target_link_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m4
  -mthumb 
  -Wall
  --specs=nosys.specs
  -nostdlib
  -lgcc
  -T${STM32F429_COMMON_LIBRARY_DIR}/ld/stm32f429zi_flash.ld
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  Gpio
)

target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
)