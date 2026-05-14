DISTRIBUTABLES += $(wildcard LICENSE*) res
RACK_DIR ?= ../..

SHELL:=/bin/bash -O extglob

MACHINE = $(shell $(CC) -dumpmachine)
FLAGS = \
	-Wno-deprecated-declarations \
	-O0 \
	-Werror=implicit-function-declaration \
	-Isrc
SOURCES = \
	$(wildcard src/*.cpp)
ifneq (, $(findstring mingw, $(MACHINE)))
	LDFLAGS += -lws2_32 -lwinmm
endif

FLAGS := $(filter-out -MMD,$(FLAGS))

include $(RACK_DIR)/plugin.mk
