
/*
 * add.cl
 * Matrix addition : A + B = C
 *
 */


__kernel void MatrixOp(__global int *A,
					   __global int *B, 
					   __global int *C)
{

  	int x = get_global_id(0) + 2;

	C[x] = A[x] + B[x];

}