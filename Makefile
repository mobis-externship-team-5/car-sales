all:
	cd lib-src; make
	cd app-src; make

clean:
	cd lib-src; make clean
	cd app-src; make clean