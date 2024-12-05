

test1: cache-test-skel.c $cache_64c_2a_16b.o
	gcc -Wall -m32 $^ -o $@

test2: cache-test-skel.c $cache_32c_8a_8b.o
	gcc -Wall -m32 $^ -o $@

test3: cache-test-skel.c $cache_16c_4a_4b.o
	gcc -Wall -m32 $^ -o $@