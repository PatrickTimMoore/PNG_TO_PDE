# Executable names:
EXE = mosaic

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = Image.o main.o

# Generated files
CLEAN_RM = output1.png, output2.png, output3.png

# Use the imageNameSpace makefile template:
include imageNameSpace/make/imageNameSpace.mk
