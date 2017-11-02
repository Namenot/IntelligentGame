
/*
 * multiply.cl
 * Matrix multiplication : A * B = C
 *
 */


__kernel void 
	MatrixOp(__global int *A,
			 __global int *B, 
			 __global int *C)
{
  	int x = get_global_id(0); /* size of A */
	int y = get_global_id(1); /* height of b | width of A */

	if(x >= A[0] * A[1] || y >= B[0])
	{
		x = 0;
		y = 0;
	}

	int rowA = x-((x/A[1]) * B[0]); //z.B. [0, 3, 6] -> 0 || [1, 4, 7] -> 1 || [2, 5, 8] -> 2 for matrix down below
	int bpos = rowA*B[1] + y;


	int cpos = ((x / A[1]) * C[1]) + y + 2;

	C[cpos] = A[x+ 2] * B[bpos];
	
	printf("x : %i \ny : %i \n\n", x, y);
	
}

/*
array[ 0, 1, 2, |
	   3, 4, 5, | row
	   6, 7, 8] V
       __ __ _> colums 
*/