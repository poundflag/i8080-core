DEFAULT:
	gcc src/main.c -o bin/i8080-core && ./bin/i8080-core

TEST:
	gcc test/main_test.c test/sample_test.c -lcheck -o bin/test && ./bin/test
