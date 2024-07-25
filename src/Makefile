lib_dir = lib/raspberry-pi-i2c-sht4x
common_sources = ${lib_dir}/sensirion_common.c
i2c_sources = ${lib_dir}/sensirion_i2c.c
driver_sources = ${lib_dir}/sht4x_i2c.c

i2c_implementation ?= ${lib_dir}/sensirion_i2c_hal.c

aegis_sources = aegis.cpp SHT40Sensor.cpp MeasurementLogger.cpp Measurement.cpp Pump.cpp GPIOController.cpp

FLAGS = -Os -Wall -fstrict-aliasing -Wstrict-aliasing=1 -fPIC -I${lib_dir} -I.

ifdef CI
    FLAGS += -Werror
endif

CFLAGS = $(FLAGS) -g3
CXXFLAGS = $(CFLAGS)
LDFLAGS = -lpigpio -lrt -pthread -lfmt

OBJS = $(common_sources:.c=.o) $(i2c_sources:.c=.o) $(driver_sources:.c=.o) $(i2c_implementation:.c=.o) $(aegis_sources:.cpp=.o)

.PHONY: all clean

all: aegis

aegis: $(OBJS)
	g++ $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) aegis $(OBJS)