cmake_minimum_required(VERSION 3.16)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/toolchain-arm-none-eabi.cmake)

set(ASSEMBLY_SCRIPT startup_stm32f429xx.s)
project(VehicleManagementSystem C CXX ASM)
set(SOURCES
 main.cpp
 ${CMAKE_SOURCE_DIR}/startup/${ASSEMBLY_SCRIPT}
)

set(STM32_COMMON_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/../STM32CommonLibrary)
add_subdirectory(${STM32_COMMON_LIBRARY_DIR} ${STM32_COMMON_LIBRARY_DIR}/bld)

add_executable(${PROJECT_NAME}
  ${SOURCES}
)

set(LINKER_FILE stm32f429zi_flash.ld)
target_link_options(${PROJECT_NAME} PRIVATE
  -mcpu=cortex-m4
  -mthumb 
  -Wall
  --specs=nosys.specs
  -nostdlib
  -lgcc
  -T${CMAKE_SOURCE_DIR}/ld/${LINKER_FILE}
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
  SystemConfig
  Gpio
  Exti
)

target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
)