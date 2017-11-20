cmake_minimum_required(VERSION 3.8)

project(another_test C CXX ASM)

set(CMAKE_CXX_STANDARD 14)
#
#   Compiler & Linker
#
set(STM32_CHIP_GROUP  "STM32F1xx")
set(STM32_CHIP        "stm32f103x6")

add_definitions(-DSTM32F103x6)
add_definitions(-DUSE_HAL_DRIVER)

set(TARGET_TRIPLET    "arm-none-eabi")
set(TOOLCHAIN_PREFIX  "/usr")

SET(TOOLCHAIN_BIN_DIR "${TOOLCHAIN_PREFIX}/bin")
SET(TOOLCHAIN_INC_DIR "${TOOLCHAIN_PREFIX}/${TARGET_TRIPLET}/include")
SET(TOOLCHAIN_LIB_DIR "${TOOLCHAIN_PREFIX}/${TARGET_TRIPLET}/lib")

IF (WIN32)
    SET(TOOL_EXECUTABLE_SUFFIX  ".exe")
ELSE()
    SET(TOOL_EXECUTABLE_SUFFIX  "")
ENDIF()

SET(CMAKE_SYSTEM_NAME                   Generic)
SET(CMAKE_SYSTEM_PROCESSOR              arm)

SET(CMAKE_C_COMPILER                    ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER                  ${TOOLCHAIN_BIN_DIR}/arm-none-eabi-g++)

SET(CMAKE_TRY_COMPILE_TARGET_TYPE       STATIC_LIBRARY)
SET(CMAKE_C_COMPILER                    "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-gcc${TOOL_EXECUTABLE_SUFFIX}")
SET(CMAKE_CXX_COMPILER                  "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-g++${TOOL_EXECUTABLE_SUFFIX}")
SET(CMAKE_ASM_COMPILER                  "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-gcc${TOOL_EXECUTABLE_SUFFIX}")
SET(CMAKE_OBJCOPY                       "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objcopy${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objcopy tool")
SET(CMAKE_OBJDUMP                       "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-objdump${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "objdump tool")
SET(CMAKE_SIZE                          "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-size${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "size tool")
SET(CMAKE_DEBUGER                       "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-gdb${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "debuger")
SET(CMAKE_CPPFILT                       "${TOOLCHAIN_BIN_DIR}/${TARGET_TRIPLET}-c++filt${TOOL_EXECUTABLE_SUFFIX}" CACHE INTERNAL "C++filt")

set(CMAKE_C_FLAGS                       "${CMAKE_C_FLAGS} -DUSE_STDPERIPH_DRIVER")
set(CMAKE_EXE_LINKER_FLAGS              "${CMAKE_EXE_LINKER_FLAGS} -T${CMAKE_SOURCE_DIR}/STM32F103C8Tx_FLASH.ld")

SET(CMAKE_C_FLAGS_DEBUG                 "-Og -g" CACHE INTERNAL "c compiler flags debug")
SET(CMAKE_CXX_FLAGS_DEBUG               "-Og -g" CACHE INTERNAL "cxx compiler flags debug")
SET(CMAKE_ASM_FLAGS_DEBUG               "-g" CACHE INTERNAL "asm compiler flags debug")
SET(CMAKE_EXE_LINKER_FLAGS_DEBUG        "" CACHE INTERNAL "linker flags debug")

SET(CMAKE_C_FLAGS_RELEASE               "-Os -flto" CACHE INTERNAL "c compiler flags release")
SET(CMAKE_CXX_FLAGS_RELEASE             "-Os -flto" CACHE INTERNAL "cxx compiler flags release")
SET(CMAKE_ASM_FLAGS_RELEASE             "" CACHE INTERNAL "asm compiler flags release")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE      "-flto" CACHE INTERNAL "linker flags release")

SET(CMAKE_FIND_ROOT_PATH                "${TOOLCHAIN_PREFIX}/${TARGET_TRIPLET}" ${EXTRA_FIND_PATH})
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM   NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY   ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE   ONLY)

SET(CMAKE_C_FLAGS                       "-mthumb -fno-builtin -mcpu=cortex-m3 -Wall -std=gnu99 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "c compiler flags")
SET(CMAKE_CXX_FLAGS                     "-mthumb -fno-builtin -mcpu=cortex-m3 -Wall -std=c++14 -ffunction-sections -fdata-sections -fomit-frame-pointer -mabi=aapcs -fno-unroll-loops -ffast-math -ftree-vectorize" CACHE INTERNAL "cxx compiler flags")
SET(CMAKE_ASM_FLAGS                     "-mthumb -mcpu=cortex-m3 -x assembler-with-cpp" CACHE INTERNAL "asm compiler flags")

SET(CMAKE_EXE_LINKER_FLAGS              "-Wl,--gc-sections -specs=nosys.specs -specs=nano.specs  -mthumb -mcpu=cortex-m3 -mabi=aapcs" CACHE INTERNAL "executable linker flags")
SET(CMAKE_MODULE_LINKER_FLAGS           "-mthumb -mcpu=cortex-m3 -mabi=aapcs" CACHE INTERNAL "module linker flags")
SET(CMAKE_SHARED_LINKER_FLAGS           "-mthumb -mcpu=cortex-m3 -mabi=aapcs" CACHE INTERNAL "shared linker flags")
#
#   Load CMSIS
set(STM32_CMSIS_SOURCES)
#set(STM32_CMSIS_SOURCES                 ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${STM32_CHIP_GROUP}/Source/Templates/gcc/startup_${STM32_CHIP}.s
#                                       ${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${STM32_CHIP_GROUP}/Source/Templates/system_stm32f1xx.c
#)
include_directories(${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Include)
include_directories(${PROJECT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${STM32_CHIP_GROUP}/Include)
#TODO: Add support of DSP Library
#
#   HAL
set(STM32_HAL_SOURCES                   ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_cortex.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_rcc_ex.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_crc.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio.c
                                        ${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Src/stm32f1xx_hal_gpio_ex.c)

include_directories(${PROJECT_SOURCE_DIR}/Drivers/STM32F1xx_HAL_Driver/Inc)

#
#   Project
include_directories(Inc)
set(ASM_SOURCES                         startup_stm32f103xb.s)
set(H_SOURCES                           Inc/main.h
                                        Inc/stm32f1xx_hal_conf.h
                                        Inc/stm32f1xx_it.h)
set(C_SOURCES                           ${STM32_CMSIS_SOURCES}
                                        ${STM32_HAL_SOURCES}
                                        Src/main.c
                                        Src/stm32f1xx_hal_msp.c
                                        Src/stm32f1xx_it.c
                                        Src/system_stm32f1xx.c)
file(GLOB                               CXX_SOURCES Src/*.cpp)

add_executable(another_test ${C_SOURCES} ${CXX_SOURCES} ${H_SOURCES} ${ASM_SOURCES})