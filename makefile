CC = clang
eApprox: eApprox.c
	$(CC) eApprox.c -o eApprox.o
debug: eApprox.c
	$(CC) eApprox.c -g -o debug_eApprox.o
clean:
	rm -rf eApprox.o debug_eApprox.o debug_eApprox.o.dSYM
