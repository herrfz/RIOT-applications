APPLICATION = openwsn-app

# If no BOARD is found in the environment, use this default:
# BOARD ?= iot-lab_M3
BOARD ?= vesna

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Uncomment this to enable scheduler statistics for ps:
#CFLAGS += -DSCHEDSTATISTICS

# Uncomment this to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
export QUIET ?= 1

# Select radiomode between dummyriot and riot-adaption, default to dummyriot:
export RADIO ?= dummyriot


ifeq ($(RADIO),dummyriot)
	USEMODULE += dummyradio
endif

ifeq ($(RADIO),riot-adaption)
	USEMODULE += at86rf231
endif

USEPKG += openwsn

include $(RIOTBASE)/Makefile.include

INCLUDES += -I$(RIOTBASE)/../openwsn/projects/common/03oos_openwsn \
		-I$(RIOTBASE)/../openwsn/bsp/boards/$(RADIO)
# -I$(RIOTBASE)/../openwsn/bsp/boards/riot-adaption
# -I$(RIOTBASE)/../openwsn/bsp/boards/dummyriot
