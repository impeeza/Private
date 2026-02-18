
TARGET := brewtendo
BUILD  := build
SOURCES := source
DATA := romfs
INCLUDES :=

LIBS := -lcitro2d -lcitro3d -lctru -lm

include $(DEVKITARM)/3ds_rules
