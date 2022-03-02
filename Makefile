z:
	make all;
	cd ~/DIR-MAKETEST/app-src; ./app
y:
	make clean;
	make all;
	cd app-src; ./app
r:
	cd app-src; vi app.c
all:
	cd lib-src; make
	cd app-src; make

clean:
	cd lib-src; make clean
	cd app-src; make clean
