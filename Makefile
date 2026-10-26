CC=gcc
CFLAGS=-g -march=native -O2 -std=c11
TARGET=array

$(TARGET): main.o libtest.a libarray.a
	$(CC) $(CFLAGS) $^ -L. -ltest -larray -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

libtest.a: test.o test_impl.o libarray.a
	ar rcs $@ $^

test.o: test_main.c test.h
	$(CC) $(CFLAGS) -c $< -o $@

test_impl.o: test.c test.h
	$(CC) $(CFLAGS) -c $< -o $@

libarray.a: array.o
	ar rcs $@ $^

array.o: array.c array.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.a $(TARGET)
