#
# "main" pseudo-component makefile.
#
# (Uses default behaviour of compiling all source files in directory, adding 'include' to include path.)

ifdef CONFIG_BOARD_CUSTOM
COMPONENT_ADD_INCLUDEDIRS += ./board_configuration
COMPONENT_SRCDIRS += ./board_configuration
endif