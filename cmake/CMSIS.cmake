#
#   CMSIS Build Injector
#
MACRO(ADD_CMSIS)
    SET(STM32_CMSIS_SOURCES)
    INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Drivers/CMSIS/CMSIS/Include)

    #TODO: Here we can place options for CMSIS (include libs or other staff)
ENDMACRO()