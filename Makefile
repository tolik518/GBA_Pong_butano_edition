#---------------------------------------------------------------------------------------------------------------------
# TARGET is the name of the output.
# BUILD is the directory where object files & intermediate files will be placed.
# LIBBUTANO is the main directory of butano library (https://github.com/GValiente/butano).
# PYTHON is the path to the python interpreter.
# SOURCES is a list of directories containing source code.
# INCLUDES is a list of directories containing extra header files.
# DATA is a list of directories containing binary data.
# GRAPHICS is a list of directories containing files to be processed by grit.
# AUDIO is a list of directories containing files to be processed by mmutil.
# DMGAUDIO is a list of directories containing files to be processed by mod2gbt and s3m2gbt.
# ROMTITLE is a uppercase ASCII, max 12 characters text string containing the output ROM title.
# ROMCODE is a uppercase ASCII, max 4 characters text string containing the output ROM code.
# USERFLAGS is a list of additional compiler flags:
#     Pass -flto to enable link-time optimization.
#     Pass -O0 to improve debugging.
# USERASFLAGS is a list of additional assembler flags.
# USERLDFLAGS is a list of additional linker flags:
#     Pass -flto=auto -save-temps to enable parallel link-time optimization.
# USERLIBDIRS is a list of additional directories containing libraries.
#     Each libraries directory must contains include and lib subdirectories.
# USERLIBS is a list of additional libraries to link with the project.
# USERBUILD is a list of additional directories to remove when cleaning the project.
# EXTTOOL is an optional command executed before processing audio, graphics and code files.
#
# All directories are specified relative to the project directory where the makefile is found.
#---------------------------------------------------------------------------------------------------------------------
LIBBUTANOBASE=/home/developer/Projects/GBA/butano
LIBBUTANORELATIVE=$(shell realpath --relative-to $(PWD) $(LIBBUTANOBASE)/)

TARGET       :=  out/$(notdir $(CURDIR))
BUILD        :=  build
LIBBUTANO    :=  $(LIBBUTANOBASE)/butano
PYTHON       :=  python3
SOURCES      :=  src $(LIBBUTANORELATIVE)/common/src
INCLUDES     :=  include $(LIBBUTANORELATIVE)/common/include
DATA         :=
GRAPHICS     :=  graphics $(LIBBUTANORELATIVE)/common/graphics
AUDIO        :=  audio $(LIBBUTANORELATIVE)/common/audio
DMGAUDIO     :=  dmg_audio $(LIBBUTANORELATIVE)/common/dmg_audio
ROMTITLE     :=  PONG II
ROMCODE      :=  SBTP
USERFLAGS    :=
USERASFLAGS  :=
USERLDFLAGS  :=
USERLIBDIRS  :=
USERLIBS     :=
USERBUILD    :=
EXTTOOL      :=

#---------------------------------------------------------------------------------------------------------------------
# Export absolute butano path:
#---------------------------------------------------------------------------------------------------------------------

export LIBBUTANOABS=$(LIBBUTANOBASE)/butano
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=/opt/devkitpro/devkitARM

#---------------------------------------------------------------------------------------------------------------------
# Include main makefile:
#---------------------------------------------------------------------------------------------------------------------
include $(LIBBUTANOABS)/butano.mak

.PHONY: run
run:
	make && mgba-qt -4 out/$(notdir $(CURDIR)).gba

.PHONY: clean_build
clean_build:
	rm -f $$(pwd)/build/*
