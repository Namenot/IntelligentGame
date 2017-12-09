
/*
 * test.cl
 * Test features of OpenCL without 
 * deleting code of the other kernels
 *
 */


__kernel void 
	MatrixOp(__global float *A,
			 __global float *B, 
			 __global float *C)
{

  	int x = get_global_id(1); 
	int y = get_global_id(0); 

	int allow = 1;
	
	if((float)x >= A[0] * A[1] || (float)y >= B[1])
	{
		x = 0;
		y = 0;
		allow = 0;
	}

	int rowB = x-((x/A[1]) * B[0]);	//z.B. [9, 6, 3] -> 0 || [8, 5, 2] -> 1 || [7, 4, 1] -> 2
	int rowA = x/A[1];			//z.B. [0, 3, 6] -> 0 || [1, 4, 7] -> 1 || [2, 5, 8] -> 2 
	
	int b = rowB*B[1] + y; 
	int c = rowA * C[1] + y;

	float AtimesB = A[x+2] * B[b+2];


	if(allow != 0)
	{
		C[c+2] +=  A[x+2] * B[b+2];
		printf("-");
	}
	

}
