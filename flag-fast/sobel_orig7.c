// This will apply the sobel filter and return the PSNR between the golden sobel and the produced sobel
// sobelized image
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define SIZE	4096
#define INPUT_FILE	"input.grey"
#define OUTPUT_FILE	"output_sobel7.grey"
#define GOLDEN_FILE	"golden.grey"

/* The horizontal and vertical operators to be used in the sobel filter */
char horiz_operator[3][3] = {{-1, 0, 1}, 
                             {-2, 0, 2}, 
                             {-1, 0, 1}};
char vert_operator[3][3] = {{1, 2, 1}, 
                            {0, 0, 0}, 
                            {-1, -2, -1}};

double sobel(unsigned char *input, unsigned char *output, unsigned char *golden);
int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]);

/* The arrays holding the input image, the output image and the output used *
 * as golden standard. The luminosity (intensity) of each pixel in the      *
 * grayscale image is represented by a value between 0 and 255 (an unsigned *
 * character). The arrays (and the files) contain these values in row-major *
 * order (element after element within each row and row after row. 			*/
unsigned char input[SIZE*SIZE], output[SIZE*SIZE], golden[SIZE*SIZE];


/* Implement a 2D convolution of the matrix with the operator */
/* posy and posx correspond to the vertical and horizontal disposition of the *
 * pixel we process in the original image, input is the input image and       *
 * operator the operator we apply (horizontal or vertical). The function ret. *
 * value is the convolution of the operator with the neighboring pixels of the*
 * pixel we process.														  */
int convolution2D(int posy, int posx, const unsigned char *restrict input, char operator[][3]) {
	int i, j, res;
        int temp1, temp2, temp3;
  
	res = 0;
        temp1 = (posy - 1 )*SIZE + posx;
        temp2 = (posy)*SIZE + posx;
        temp3 = (posy + 1)*SIZE + posx ;
	for (j = -1; j <= 1; j++) {
		
                res += input[temp1 + j] * operator[0][j+1];
                res += input[temp2 + j] * operator[1][j+1];
                res += input[temp3 + j] * operator[2][j+1];
		
	}
	return(res);
}


/* The main computational function of the program. The input, output and *
 * golden arguments are pointers to the arrays used to store the input   *
 * image, the output produced by the algorithm and the output used as    *
 * golden standard for the comparisons.									 */
double sobel(unsigned char *restrict input, unsigned char *restrict output, unsigned char *restrict golden)
{
	register double PSNR = 0, t;
	register int i, j, k;
	register unsigned int p;
	register int res, res1, res2;
	struct timespec  tv1, tv2;
	FILE *f_in, *f_out, *f_golden;
        
        register int temp1 , temp2, temp3, temp4, temp5, temp6;

	/* The first and last row of the output array, as well as the first  *
     * and last element of each column are not going to be filled by the *
     * algorithm, therefore make sure to initialize them with 0s.		 */
	memset(output, 0, SIZE*sizeof(unsigned char));
	memset(&output[SIZE*(SIZE-1)], 0, SIZE*sizeof(unsigned char));
        temp3 = SIZE;
	for (i = 1; i < SIZE-1; i = i + 2) {
		output[temp3] = 0;
		output[temp3 + SIZE - 1] = 0;
                temp3 = temp3 + SIZE;
                output[temp3] = 0;
		output[temp3 + SIZE - 1] = 0;
                temp3 = temp3 + SIZE;
	}

	/* Open the input, output, golden files, read the input and golden    *
     * and store them to the corresponding arrays.						  */
	f_in = fopen(INPUT_FILE, "r");
	if (f_in == NULL) {
		printf("File " INPUT_FILE " not found\n");
		exit(1);
	}
  
	f_out = fopen(OUTPUT_FILE, "wb");
	if (f_out == NULL) {
		printf("File " OUTPUT_FILE " could not be created\n");
		fclose(f_in);
		exit(1);
	}  
  
	f_golden = fopen(GOLDEN_FILE, "r");
	if (f_golden == NULL) {
		printf("File " GOLDEN_FILE " not found\n");
		fclose(f_in);
		fclose(f_out);
		exit(1);
	}    

	fread(input, sizeof(unsigned char), SIZE*SIZE, f_in);
	fread(golden, sizeof(unsigned char), SIZE*SIZE, f_golden);
	fclose(f_in);
	fclose(f_golden);
  
	/* This is the main computation. Get the starting time. */
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
	/* For each pixel of the output image */
        temp3 = SIZE;
        
	for (i=1; i<SIZE-1; i= i + 2 ) {
                temp1 = temp3;
                temp2 = temp3 + SIZE;
                for (j=1; j<SIZE-1; j+=1) {
                        
                        /* int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]); */
                
                        res1 = 0;
                        temp4 = (i - 1 )*SIZE + j;
                        temp5 = (i)*SIZE + j;
                        temp6 = (i + 1)*SIZE + j ;
                        for (k = -1; k <= 1; k++) {
                                
                                res1 += input[temp4 + k] * horiz_operator[0][k+1];
                                res1 += input[temp5 + k] * horiz_operator[1][k+1];
                                res1 += input[temp6 + k] * horiz_operator[2][k+1];
                                
                        }
                        
                         /* int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]); */
                        
                
                        res2 = 0;
                        temp4 = (i - 1 )*SIZE + j;
                        temp5 = (i)*SIZE + j;
                        temp6 = (i + 1)*SIZE + j ;
                        for (k = -1; k <= 1; k++) {
                                
                                res2 += input[temp4 + k] * vert_operator[0][k+1];
                                res2 += input[temp5 + k] * vert_operator[1][k+1];
                                res2 += input[temp6 + k] * vert_operator[2][k+1];
                                
                        }
                        
                        /***************************/
                    
			/* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.								  */
			p = res1*res1 + res2*res2;
                        
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			if (res > 255)
				output[temp1 + j] = 255;      
			else
				output[temp1 + j] = (unsigned char)res;
                        
                        
                        /* int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]); */
//                         res3 = 0;
//                         temp4 = (i)*SIZE + j;
//                         temp5 = (i+1)*SIZE + j;
//                         temp6 = (i+2)*SIZE + j;
//                         for (k = -1; k <= 1; k++) {
//                                 
//                                 res3 += input[temp4 + k] * horiz_operator[0][k+1];
//                                 res3 += input[temp5 + k] * horiz_operator[1][k+1];
//                                 res3 += input[temp6 + k] * horiz_operator[2][k+1];
//                                 
//                         }
                       
                        /* int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]); */
//                         res4 = 0;
//                         temp4 = (i)*SIZE + j;
//                         temp5 = (i+1)*SIZE + j;
//                         temp6 = (i+2)*SIZE + j;
//                         for (k = -1; k <= 1; k++) {
//                                 
//                                 res4 += input[temp4 + k] * vert_operator[0][k+1];
//                                 res4 += input[temp5 + k] * vert_operator[1][k+1];
//                                 res4 += input[temp6 + k] * vert_operator[2][k+1];
//                                 
//                         }
                        
                        /*************************************/
                        
                        /* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.								  */
			p = convolution2D(i+1, j, input, horiz_operator)*convolution2D(i+1, j, input, horiz_operator) + 
				convolution2D(i+1, j, input, vert_operator)*convolution2D(i+1, j, input, vert_operator);
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			if (res > 255)
				output[temp2 + j] = 255;      
			else
				output[temp2 + j] = (unsigned char)res;
		}
		temp3 = temp3 + SIZE + SIZE;
	}

	/* Now run through the output and the golden output to calculate *
	 * the MSE and then the PSNR.									 */
	for ( j=1; j<SIZE-1; j = j + 2 ) {
                temp3 = SIZE + j;
                for (i=1; i<SIZE-1; i++) {
		
			t = (output[temp3] - golden[temp3])*(output[temp3] - golden[temp3]);
			PSNR += t;
                        
                        t = (output[temp3+1] - golden[temp3+1])*(output[temp3+1] - golden[temp3+1]);
			PSNR += t;
                        
                        temp3 = temp3 + SIZE;
		}
	}
  
	PSNR /= (double)(SIZE*SIZE);
	PSNR = 10*log10(65536/PSNR);

	/* This is the end of the main computation. Take the end time,  *
	 * calculate the duration of the computation and report it. 	*/
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);

	printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));

  
	/* Write the output file */
	fwrite(output, sizeof(unsigned char), SIZE*SIZE, f_out);
	fclose(f_out);
  
	return PSNR;
}


int main(int argc, char* argv[])
{
	double PSNR;
	PSNR = sobel(input, output, golden);
	printf("PSNR of original Sobel and computed Sobel image: %g\n", PSNR);
	printf("A visualization of the sobel filter can be found at " OUTPUT_FILE ", or you can run 'make image' to get the jpg\n");

	return 0;
}

