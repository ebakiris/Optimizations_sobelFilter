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
#define OUTPUT_FILE	"output_sobel8.grey"
#define GOLDEN_FILE	"golden.grey"

/* The horizontal and vertical operators to be used in the sobel filter */
char horiz_operator[3][3] = {{-1, 0, 1}, 
                             {-2, 0, 2}, 
                             {-1, 0, 1}};
char vert_operator[3][3] = {{1, 2, 1}, 
                            {0, 0, 0}, 
                            {-1, -2, -1}};

double sobel(unsigned char *input, unsigned char *output, unsigned char *golden);
// int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]);

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
// int convolution2D(int posy, int posx, const unsigned char *input, char operator[][3]) {
// 	int i, j, res;
//         int temp1,temp2,temp3, temp4;
//         
//         temp1 = posx - 1;
//         temp2 = posx + 1;
// 	res = 0;
//         temp3 = -SIZE;
// 	for (i = -1; i <= 1; i++) {
// 		res += input[posy*SIZE + temp3 + temp1] * operator[i + 1][0];
//                 res += input[posy*SIZE + temp3 + posx ] * operator[i + 1][1];
//                 res += input[posy*SIZE + temp3 + temp2] * operator[i + 1][2];
//                 
//                 temp3 = temp3 + SIZE;
// 	}
// 	return(res);
// }


/* The main computational function of the program. The input, output and *
 * golden arguments are pointers to the arrays used to store the input   *
 * image, the output produced by the algorithm and the output used as    *
 * golden standard for the comparisons.									 */
double sobel(unsigned char *restrict input, unsigned char *restrict output, unsigned char *restrict golden)
{
	register double PSNR = 0, t;
	register int i, j;
	register unsigned int p;
	register int res,res1,res2,res3,res4,res5,res6,res7,res8;
	struct timespec  tv1, tv2;
	FILE *f_in, *f_out, *f_golden;
        
        register int temp1, temp2, temp = SIZE*SIZE , temp3, temp4, temp5, temp6, temp7;
        register int k;
        
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

	fread(input, sizeof(unsigned char), temp, f_in);
	fread(golden, sizeof(unsigned char), temp, f_golden);
	fclose(f_in);
	fclose(f_golden);
  
	/* This is the main computation. Get the starting time. */
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
	/* For each pixel of the output image */
        temp4 = SIZE;
	for (i=1; i<SIZE-1; i = i + 2) {
                temp1 = temp4;
                temp4 = temp4 + SIZE;
                temp2 = temp4;
                temp3 = (i+1);
                temp4 = temp4 + SIZE;
		for (j=1; j< (SIZE/2); j+=1 ) {
			/* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.	*/
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        
                        temp5 = j - 1;
                        temp6 = j + 1;
                        res1 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res1 += input[i*SIZE + temp7 + temp5] * horiz_operator[k + 1][0];
                                res1 += input[i*SIZE + temp7 + j ] * horiz_operator[k + 1][1];
                                res1 += input[i*SIZE + temp7 + temp6] * horiz_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        
                        
                        res2 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res2 += input[i*SIZE + temp7 + temp5] * vert_operator[k + 1][0];
                                res2 += input[i*SIZE + temp7 + j ] * vert_operator[k + 1][1];
                                res2 += input[i*SIZE + temp7 + temp6] * vert_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                        /****************************/
			p = res1*res1 + res2*res2;
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			
                        if (res > 255)
				output[temp1 + j] = 255;      
			else
				output[temp1 + j] = (unsigned char)res;
                        
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        
                        res3 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res3 += input[temp3*SIZE + temp7 + temp5] * horiz_operator[k + 1][0];
                                res3 += input[temp3*SIZE + temp7 + j ] * horiz_operator[k + 1][1];
                                res3 += input[temp3*SIZE + temp7 + temp6] * horiz_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                       
                        res4 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res4 += input[temp3*SIZE + temp7 + temp5] * vert_operator[k + 1][0];
                                res4 += input[temp3*SIZE + temp7 + j ] * vert_operator[k + 1][1];
                                res4 += input[temp3*SIZE + temp7 + temp6] * vert_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                        /****************************/
                        
                        
                        /* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.								  */
			p = res3*res3 + res4*res4;
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			if (res > 255)
				output[temp2 + j] = 255;      
			else
				output[temp2 + j] = (unsigned char)res;
		}
		
		for (j=(SIZE/2); j<SIZE-1; j+=1 ) {
                    
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        temp5 = j - 1;
                        temp6 = j + 1;
                        res5 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res5 += input[i*SIZE + temp7 + temp5] * horiz_operator[k + 1][0];
                                res5 += input[i*SIZE + temp7 + j ] * horiz_operator[k + 1][1];
                                res5 += input[i*SIZE + temp7 + temp6] * horiz_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                         /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        
                        
                        res6 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res6 += input[i*SIZE + temp7 + temp5] * vert_operator[k + 1][0];
                                res6 += input[i*SIZE + temp7 + j ] * vert_operator[k + 1][1];
                                res6 += input[i*SIZE + temp7 + temp6] * vert_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                    
                        /*****************************/
			/* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.								  */
			p = res5*res5 + res6*res6;
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			if (res > 255)
				output[temp1 + j] = 255;      
			else
				output[temp1 + j] = (unsigned char)res;
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                        
                        res7 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res7 += input[temp3*SIZE + temp7 + temp5] * horiz_operator[k + 1][0];
                                res7 += input[temp3*SIZE + temp7 + j ] * horiz_operator[k + 1][1];
                                res7 += input[temp3*SIZE + temp7 + temp6] * horiz_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                        /*       convolution2D      */
                        /* (int posy, int posx, const unsigned char *input, char operator[][3]) */
                        
                       
                        res8 = 0;
                        temp7 = -SIZE;
                        for (k = -1; k <= 1; k++) {
                                
                                res8 += input[temp3*SIZE + temp7 + temp5] * vert_operator[k + 1][0];
                                res8 += input[temp3*SIZE + temp7 + j ] * vert_operator[k + 1][1];
                                res8 += input[temp3*SIZE + temp7 + temp6] * vert_operator[k + 1][2];
                                
                                temp7 = temp7 + SIZE;
                        }
                        
                        
                        /****************************/
                        /* Apply the sobel filter and calculate the magnitude *
			 * of the derivative.								  */
			p = res7*res7 + res8*res8;
			res = (int)sqrt(p);
			/* If the resulting value is greater than 255, clip it *
			 * to 255.											   */
			if (res > 255)
				output[temp2 + j] = 255;      
			else
				output[temp2 + j] = (unsigned char)res;
		}
	}

	/* Now run through the output and the golden output to calculate *
	 * the MSE and then the PSNR.									 */
	for (j=1; j<SIZE-1; j = j + 2) {
		temp1 = SIZE;
                for ( i=1; i<(SIZE/2); i+=1 ) {
                        
			t = (output[temp1 + j] - golden[temp1 + j])*(output[temp1 + j] - golden[temp1 + j]);
			PSNR += t;
                        
                        t = (output[temp1 + j + 1] - golden[temp1 + j + 1])*(output[temp1 + j + 1] - golden[temp1 + j + 1]);
			PSNR += t;
                        
                        temp1 = temp1 + SIZE;
		}
		
		for ( i=(SIZE/2); i<SIZE-1; i+=1 ) {
                    
			t = (output[temp1 + j] - golden[temp1 + j])*(output[temp1 + j] - golden[temp1 + j]);
			PSNR += t;
                        
                        t = (output[temp1 + j + 1] - golden[temp1 + j + 1])*(output[temp1 + j + 1] - golden[temp1 + j + 1]);
			PSNR += t;
                        
                        temp1 = temp1 + SIZE;
		}
	}
  
	PSNR /= (double)(temp);
	PSNR = 10*log10(65536/PSNR);

	/* This is the end of the main computation. Take the end time,  *
	 * calculate the duration of the computation and report it. 	*/
	clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);

	printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));

  
	/* Write the output file */
	fwrite(output, sizeof(unsigned char), temp, f_out);
	fclose(f_out);
  
	return PSNR;
}


int main(int argc, char* argv[])
{
	register double PSNR;
	PSNR = sobel(input, output, golden);
	printf("PSNR of original Sobel and computed Sobel image: %g\n", PSNR);
	printf("A visualization of the sobel filter can be found at " OUTPUT_FILE ", or you can run 'make image' to get the jpg\n");

	return 0;
}

