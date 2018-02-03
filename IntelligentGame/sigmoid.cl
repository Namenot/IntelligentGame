
/*
 * sigmoid.cl
 * Calculates a sigmoid function for a Matrix
 *
 */


__kernel void MatrixOp(__global double *A)
{

  	int x = get_global_id(0);

	int bias = 10;
	int e = 2.71828182845904550;

	double temp0 = A[x+2] - bias;
	double temp1 = pow(e, temp0);
	double temp2 = 1/temp1;
	double temp3 = 1+ temp2;

	A[x+2] = 1/temp3;


}
