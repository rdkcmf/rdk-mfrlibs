##########################################################################
# If not stated otherwise in this file or this component's LICENSE
# file the following copyright and licenses apply:
#
# Copyright 2014 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################

CC          := mipsel-linux-gcc
CXX         := mipsel-linux-g++
RM          := rm -rf 
CFLAGS      := -fPIC -D_REENTRANT -Wall
IARM_PATH   := $(COMBINED_DIR)/iarm
INSTALL     := $(PWD)
INCLUDE     := -I$(PWD)                         \
               -I$(PWD)/hal/include             \
               -I$(PWD)/include                 \
               -I$(BUILDS_DIR)/iarm

INCLUDE     += -I$(DFB_ROOT)/usr/local/include/directfb
CFLAGS      += $(INCLUDE)

CLI_OBJS    = mfrcli.o
SRV_OBJS    = mfrsrv.o
CLI_LIBNAME = libmfrcli.so
SRV_LIBNAME = libmfrsrv.so

all: install
	@echo "Build Finished...."

library: $(CLI_OBJS) $(SRV_OBJS)
	@echo "Building $(CLI_LIBNAME)..."
	$(CC) $(CLI_OBJS) $(CFLAGS) -g -shared -Wl -o $(CLI_LIBNAME)
	$(CC) $(SRV_OBJS) $(CFLAGS) -g -shared -Wl -o $(SRV_LIBNAME)

%.o: %.c
	@echo "Building $@ ...."
	$(CC) -c $<  $(CFLAGS) -o $@

install: library
	@echo "installling...!"
	@cp -f $(CLI_LIBNAME) $(INSTALL)/lib
	@cp -f $(SRV_LIBNAME) $(INSTALL)/lib

uninstall:
	@$(RM) $(INSTALL)/lib/$(CLI_LIBNAME)
	@$(RM) $(INSTALL)/lib/$(SRV_LIBNAME)

clean:
	@echo "Cleaning the directory..."
	@$(RM) $(CLI_OBJS) $(SRV_OBJS) $(CLI_LIBNAME) $(SRV_LIBNAME)

