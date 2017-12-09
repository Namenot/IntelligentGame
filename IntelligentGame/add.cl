
/*
 * add.cl
 * Matrix addition : A + B = C
 *
 */


__kernel void MatrixOp(__global float *A,
					   __global float *B, 
					   __global float *C)
{

  	int x = get_global_id(0) + 2;

	C[x] = A[x] + B[x];

}