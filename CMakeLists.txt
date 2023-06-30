cmake_minimum_required(VERSION 3.16)

set(TOOLCHAIN_DIR        ${CMAKE_SOURCE_DIR}/cmake)
set(LINKER_DIR           ${CMAKE_SOURCE_DIR}/ld)
set(STARTUP_DIR          ${CMAKE_SOURCE_DIR}/startup)
set(HARDWARE_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../stm32f429-hardware-library)

set(CMAKE_TOOLCHAIN_FILE ${TOOLCHAIN_DIR}/toolchain-arm-none-eabi.cmake)
set(LINKER_FILE          ${LINKER_DIR}/stm32f429zi_flash.ld)
set(STARTUP_FILE         ${STARTUP_DIR}/startup_stm32f429xx.s)

project(VehicleManagementSystem C CXX ASM)
set(SOURCES
  main.cpp
  ${STARTUP_FILE}
)

add_subdirectory(${HARDWARE_LIBRARY_DIR} ${HARDWARE_LIBRARY_DIR}/bld)

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
  -T${LINKER_FILE}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  DMA
  EXTI
  GPIO
  NVIC
  RCC
  SYSCFG
)

target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
)