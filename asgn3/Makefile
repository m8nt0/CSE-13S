CC = gcc
SOURCE = test_password_checker.c password_checker.c
OBJ = test_password_checker.o password_checker.o
HEADER = password_checker.h
EXE = password_checker

password_checker: $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $<

clean:
	rm -f $(EXE) $(OBJ)

