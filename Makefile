# name of your application
APPLICATION = rescuefan

# If no BOARD is found in the environment, use this default:
EXTERNAL_BOARD_DIRS = ../boards
BOARD ?= stm32f334-disco

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../RIOT/

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Shell modules
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += core_idle_thread
# Enable scheduler statistics for ps:
USEMODULE += schedstatistics
USEMODULE += xtimer

EXTERNAL_MODULE_DIRS += $(CURDIR)/../modules
USEMODULE += hrtim

include $(RIOTBASE)/Makefile.include
