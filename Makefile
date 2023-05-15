DEFAULT:
	gcc src/main.c -o bin/i8080-core && ./bin/i8080-core

TEST:
	gcc test/main_test.c test/memory/memory_controller_test.c src/memory/memory_controller.h src/memory/memory_controller.c -lcheck -o bin/test && ./bin/test