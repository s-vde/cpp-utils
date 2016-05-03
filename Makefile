.PHONY:

#===== Makefile ==============================================================80
#
#                               C++ Utils
#
# author: 	Susanne van den Elsen
# date: 	2015-2016
#
# This file is to be included by the Makefile of projects using these C++ 
# Utils. It defines paths, adds relevant paths to VPATH (the list of paths 
# that make should search), and defines targets for C++ Utils files, 
# specifying their dependencies.
#
#===============================================================================

#======Variables =============================================================80
#
# User defined:
#	UTILS           : The root directory of C++ Utils (absolute path or
#                     relative path from including project.
#
# Defined here:
#	utils_src       : The directory of C++ Utils source files.
#	utils_srcs      : List of C++ Utils source files.
#
#===============================================================================

UTILS               ?= .
utils_src           := $(UTILS)/src
utils_srcs          := $(notdir $(shell find $(utils_src) -name "*.cpp"))

VPATH               += $(utils_src)

#===== Targets =====

# algo.*                    header-only

binary_sem.*:

color_output.*:

# container_format.* 		header-only
# container_input.*      	header-only
# container_io.*      		header-only
# container_output.*     	header-only
# debug.*                   header-only
# error.*					header-only

utils_io.*:

# utils_map.*				header-only
