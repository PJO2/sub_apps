all: P1 P2 P0

P1: ipc_compare.c ipc_center.h
	gcc -o $@ -D P1 ipc_compare.c

P2: ipc_compare.c ipc_center.h
	gcc -o $@ -D P2 ipc_compare.c


P0: ipc_center.c ipc_center.h
	gcc -o $@ ipc_center.c

clean:
	rm P1 P2 P0

