
/*
 * test.cl
 * Test features of OpenCL without 
 * deleting code of the other kernels
 *
 */


__kernel void 
	MatrixOp(__global int *A,
			 __global int *B, 
			 __global int *C)
{

  	int x = get_global_id(0); 
	int y = get_global_id(1); 
	
	if(x >= A[0] * A[1] || y >= B[0])
	{
		x = 0;
		y = 0;
	}

	int rowA = x-((x/A[1]) * B[0]); //z.B. [0, 3, 6] -> 0 || [1, 4, 7] -> 1 || [2, 5, 8] -> 2
	int b = rowA*B[1] + y; 

	int c =;


	printf("A[%i]: %i\n", x, A[x+2]);
	printf("B[%i]: %i\n", y, B[b+2]); 
	printf("C[x] += A[x] * B[x]\n");
	printf("C[x] = x\n");
	printf("C[x] = %i\n\n", A[x+2]* B[b+2]);
	//printf("x: %i\ny: %i\n\n", x, y);
	
}
