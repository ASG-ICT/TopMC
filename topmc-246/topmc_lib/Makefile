VER=2.0
NAME=libtopmc-$(VER)
CFLAGS= -O3
CXXFLAGS=$(CFLAGS)

all: bin libtopmc.a
	cp libtopmc.a bin/

bin:
	mkdir bin

libtopmc.a: topmc_api.o
	ar -crs $@ $^

topmc_api.o: include/rdpmc.h include/topmc.h

install:
	cp bin/libtopmc.a /usr/local/lib
	cp -r include/* /usr/local/include

clean:
	rm -f *.o *.a

