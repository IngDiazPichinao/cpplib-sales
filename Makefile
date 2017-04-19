#
#  Makefile for cns-cpplib-sales
#
DEB_HOST_MULTIARCH ?= $(shell dpkg-architecture -q DEB_HOST_MULTIARCH)

DIR_SOURCES = ./src
DIR_BUILD   = ./builds
DIR_LIBS    = $(DIR_BUILD)/lib
DIR_INCLUDE = $(DIR_BUILD)/include/cns
DIR_HEADERS = $(DIR_INCLUDE)/sales

INSTALL_LIBS     = /usr/lib/$(DEB_HOST_MULTIARCH)
INSTALL_INCLUDES = /usr/include

LIB_NAME    = libcns-sales
LIB_MAYOR   = 0
LIB_MINOR   = 1
LIB_PATCH   = 0
LIB_VERSION = $(LIB_MAYOR).$(LIB_MINOR).$(LIB_PATCH)
LIB_SONAME  = $(LIB_NAME).so.$(LIB_MAYOR)

LIB_FNAME_A  = $(LIB_NAME).a
LIB_FNAME_SO = $(LIB_NAME).so.$(LIB_VERSION)

LIB_LINK_SONAME = $(DIR_LIBS)/$(LIB_SONAME)
LIB_LINK_NAME   = $(DIR_LIBS)/$(LIB_NAME).so

TARGET_A    = $(DIR_LIBS)/$(LIB_FNAME_A)
TARGET_SO   = $(DIR_LIBS)/$(LIB_FNAME_SO)
TARGET_TEST = $(DIR_BUILD)/testrun

LIB_DEPS = \
	-L$(DIR_SOURCES) \
	-lcns-common     \
	-lcns-pgsql      \

LIB_INCLUDES = \
	-I$(DIR_SOURCES)

CXX          = clang++
CXX_FLAGS    = -Wall -Wextra -Wconversion -pedantic -stdlib=libstdc++ -std=c++14
CXX_LIBFLAGS = -fPIC -g -c

CMD_COMPILE     = $(CXX) $(CXX_FLAGS) $(LIB_INCLUDES) $(CXX_LIBFLAGS)
CMD_LINK_STATIC = ar rcs
CMD_LINK_SHARED = clang++ -shared -Wl,-soname,$(LIB_SONAME) $(LIB_DEPS)
CMD_LINK_EXEC   = clang++ $(LIB_DEPS) -L$(DIR_LIBS) -lcns-sales

OBJECTS = \
	src/objs/Customer.o          \
	src/objs/Document.o          \
	src/objs/Item.o              \
	src/objs/Payment.o           \
	src/objs/PaymentCard.o       \
	src/objs/PaymentCheque.o     \
	src/objs/Translate.o         \
	src/objs/PaymentToDocument.o \
	src/objs/Accounting.o    	 \
	src/objs/SalesMan.o      	 \
	src/objs/Branch.o        	 \
	src/objs/Product.o       	 \
	src/objs/Sale.o          	 \
	src/objs/Debts.o         	 \
	src/objs/Banks.o         	 \


.PHONY: all build dirs headers clean


all: build


build: dirs $(TARGET_A) $(TARGET_SO) $(LIB_LINK_SONAME) $(LIB_LINK_NAME) headers
	find $(DIR_BUILD) -type f -exec chmod -x {} \;


# test: $(TARGET_TEST)
# 	LD_LIBRARY_PATH=$(DIR_LIBS) $(TARGET_TEST)


dirs:
	mkdir -p $(DIR_LIBS)
	mkdir -p $(DIR_HEADERS)


headers: dirs
	cp -ra $(DIR_SOURCES)/objs/*.hpp $(DIR_HEADERS)


install:
	# Prepare dirs (packaging does not create them for you)
	mkdir -p $(DESTDIR)$(INSTALL_LIBS)
	mkdir -p $(DESTDIR)$(INSTALL_INCLUDES)

	# Copy Libraries
	cp -a $(TARGET_SO) $(DESTDIR)$(INSTALL_LIBS)
	cp -a $(TARGET_A)  $(DESTDIR)$(INSTALL_LIBS)

	# Copy Headers
	cp -ra $(DIR_INCLUDE) $(DESTDIR)$(INSTALL_INCLUDES)

	# Link SONAME for binary lib and dev packages
	ln -sr $(DESTDIR)$(INSTALL_LIBS)/$(LIB_FNAME_SO) $(DESTDIR)$(INSTALL_LIBS)/$(LIB_SONAME)
	ln -sr $(DESTDIR)$(INSTALL_LIBS)/$(LIB_FNAME_SO) $(DESTDIR)$(INSTALL_LIBS)/$(LIB_NAME).so


clean:
	-rm -rvf $(DIR_BUILD)
	-rm -rvf $(DIR_SOURCES)/*.o


# $(TARGET_TEST): $(LIB_LINK_NAME) $(LIB_LINK_SONAME)
# 	$(CMD_COMPILE)   src/main.cpp -o src/main.o
# 	$(CMD_LINK_EXEC) src/main.o   -o $@


$(LIB_LINK_SONAME): $(TARGET_SO)
	ln -sr $^ $@


$(LIB_LINK_NAME): $(TARGET_SO)
	ln -sr $^ $@


$(TARGET_A): $(OBJECTS) | $(DIR_LIBS)
	$(CMD_LINK_STATIC) $@ $^


$(TARGET_SO): $(OBJECTS) | $(DIR_LIBS)
	$(CMD_LINK_SHARED) $^ -o $@


$(DIR_LIBS):
	mkdir -p $@


$(DIR_HEADERS):
	mkdir -p $@


%.o: %.cpp
	$(CMD_COMPILE) $^ -o $@
