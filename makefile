CGCC = gcc

CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2\
         -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address\
         -fsanitize=undefined -fno-sanitize-recover -fstack-protector

compile : graph_impl.c letter_manager.c route_optimizer.c Main.c 
	$(CGCC) graph_impl.c letter_manager.c route_optimizer.c Main.c -o main

run: main
	./main

clean: 
	rm -f Main main PDOptimization

