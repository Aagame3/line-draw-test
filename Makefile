
build:
	gcc line.c -o line
	gcc -o gline gline.c -lglfw -lGL -lGLEW
clean:
	rm line gline