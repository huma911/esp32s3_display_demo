# Edit following two lines to set component requirements (see docs)
if(CONFIG_BOARD_CUSTOM)
message(STATUS "Current board name is " CONFIG_BOARD_CUSTOM)
list(APPEND COMPONENT_ADD_INCLUDEDIRS ./board_configuration)
set(COMPONENT_SRCS
# ./board_configuration/board.c
# ./board_configuration/board_pins_config.c
# ./board_configuration/new_codec.c
)
endif()

register_component()
