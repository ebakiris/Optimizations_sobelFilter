# Makefile. If you change it, remember than in makefiles multiple spaces
# ARE NOT EQUIVALENT to tabs. The line after a rule starts with a tab!

#Add any executable you want to be created here.
EXECUTABLES	= sobel_orig sobel_orig1 sobel_orig2 sobel_orig3 sobel_orig4 sobel_orig5 sobel_orig6 sobel_orig7 sobel_orig8

#This is the compiler to use
CC = icc

#These are the flags passed to the compiler. Change accordingly
CFLAGS = -Wall -fast

#These are the flags passed to the linker. Nothing in our case
LDFLAGS = -lm


# make all will create all executables
all: $(EXECUTABLES)

# This is the rule to create any executable from the corresponding .c 
# file with the same name.
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# make clean will remove all executables, jpg files and the 
# output of previous executions.
clean:
	rm -f $(EXECUTABLES) *.jpg *.grey

# make image will create the output_sobel.jpg from the output_sobel.grey. 
# Remember to change this rule if you change the name of the output file.
# image0 without optimizations
# image1 with one optimization ..
image0: output_sobel.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel.grey output_sobel0.jpg 
image1: output_sobel1.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel1.grey output_sobel1.jpg 
image2: output_sobel2.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel2.grey output_sobel2.jpg 
image3: output_sobel3.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel3.grey output_sobel3.jpg
image4: output_sobel4.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel4.grey output_sobel4.jpg 
image5: output_sobel5.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel5.grey output_sobel5.jpg 
image6: output_sobel6.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel6.grey output_sobel6.jpg 
image7: output_sobel7.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel7.grey output_sobel7.jpg
image8: output_sobel8.grey
	convert -depth 8 -size 4096x4096 GRAY:output_sobel8.grey output_sobel8.jpg