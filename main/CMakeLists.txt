if(CONFIG_CUSTOMER_BOARD)
    if(CONFIG_CUSTOMER_BOARD_DISPLAY_ST7796)
        set(INCLUDE_DIRS "." "ui/custom" "ui/generated" "ui/generated/guider_customer_fonts")
    elseif(CONFIG_CUSTOMER_BOARD_DISPLAY_ST7789)
        set(INCLUDE_DIRS ".")
    else()
        set(INCLUDE_DIRS ".")
    endif()
endif()

set(SOURCES "")
file(GLOB_RECURSE SOURCES ./*.c)

idf_component_register(
                        SRCS ${SOURCES}
                        INCLUDE_DIRS ${INCLUDE_DIRS}
                        )

spiffs_create_partition_image(html ../html FLASH_IN_PROJECT)