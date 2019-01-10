#!/bin/sh
clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -lraylib main.c
