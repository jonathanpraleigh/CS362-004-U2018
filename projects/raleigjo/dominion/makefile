CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: testall

testall: randomtestcard1.c randomtestcard2.c randomtestadventurer.c dominion.c rngs.c randomtest.h helpers.c

	echo "randomtestcard1.c:" > randomtestcard1.out
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c helpers.c $(CFLAGS)
	randomtestcard1 >> randomtestcard1.out	
	gcov dominion.c >> randomtestcard1.out	

	echo "randomtestcard2.c:" > randomtestcard2.out
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c helpers.c $(CFLAGS)
	randomtestcard2 >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out	

	echo "randomtestadventurer.c:" > randomtestadventurer.out	
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c helpers.c $(CFLAGS)
	randomtestadventurer >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out	

clean:	

	rm *.out *.o
