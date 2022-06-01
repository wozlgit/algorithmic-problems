default:
	gcc -std=c11 -Wall -Wpedantic -g \
	$(problemDir)/*.c \
	-o build/solution