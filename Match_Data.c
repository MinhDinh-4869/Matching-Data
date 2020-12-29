#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
/**
int min_col(int data[][], int m, int n)
{
	int index[m];
	int value[m];
	int min_temp;
	for(int j = 0; j< n; j++ )
	{
		min_temp = data[0][j];
		index[j] = 0;
		for(int i = 1; i<m; i++)
		{
			if(data[i][j] > min_temp)
			{
				min_temp = data[i][j];
				index[j] = i;
			}
		}
		value[j] = min_temp;
	}
	for (int i = 0; i < n; ++i)
	{
		printf("%d\t", value[i]);
	}
	putchar('\n');
	for(int i = 0; i<n;i++)
	{
		printf("%d\t", index[i]);
	}
}
**/
//find correlation coefficient.
int sum_arr(int array[], int length_arr)
{
	//len_array = sizeof(array)/sizeof(array[0]);
	int sum = 0;
	for(int i=0; i<length_arr;i++)
	{
		sum = sum + array[i];
	}
	return(sum);
}
float find_corr(int arr_a[], int arr_b[], int length_arr)
{
	//len_a = sizeof(arr_a)/sizeof(arr_a[0]);
	const int n = length_arr;
	int xi_yi[n];
	for(int i = 0; i<n; i++)
	{
		xi_yi[i] = arr_a[i]*arr_b[i];
	}
	int sum_x_y = sum_arr(xi_yi,n); //cal sum xi*yi
	int sum_x = sum_arr(arr_a,n);
	int sum_y = sum_arr(arr_b,n);
	int x_square[n];
	int y_square[n];
	for(int i = 0; i<n;i++)
	{
		x_square[i] = arr_a[i]*arr_a[i];
		y_square[i] = arr_b[i]*arr_b[i];
	}
	int sum_x_square = sum_arr(x_square,n);
	int sum_y_square = sum_arr(y_square,n);
	int square_sum_x = sum_x*sum_x;
	int square_sum_y = sum_y*sum_y;
	float corr_x_y;
	int nominator = n*sum_x_y - sum_x*sum_y;
	float denominator_1 = sqrt(n*sum_x_square - square_sum_x);
	float denominator_2 = sqrt(n*sum_y_square - square_sum_y);
	corr_x_y = (float)nominator/(denominator_1*denominator_2);
	return(corr_x_y);
}
int modulo(int a, int b)
{
	int mod = (a > b) ? (a%b):(b%a);
	return(mod);
}
int main()
{
	//Create a Data set and sample set.
	srand((unsigned)time(NULL));
	const int m = 10;
	const int n = 10;
	const int k = 3;
	const int scale_num = 3;
	const int add_num = 3;
	int data[m][n];
	int sample[k][k];	
	for(int i = 0; i<m; i++)
	{
		for(int j = 0; j<n;j++)
		{
			int a = rand();
			a%=10;
			data[i][j]=a ;
		}
	}
	for(int i = 0; i<m; i++)
	{
		for(int j = 0; j<n;j++)
		{
			printf("%d ",data[i][j]);
		}
		putchar('\n');
	}
	printf("\n\n");
	for(int i = 0; i<k; i++)
	{
		for(int j = 0; j<k;j++)
		{
			sample[i][j] = data[3+i][5+j];
		}
	}
	for(int i = 0; i<k; i++)
	{
		for(int j = 0; j<k;j++)
		{
			printf("%d ",sample[i][j]);
		}
		putchar('\n');
	}
	printf("\n\n");
	for(int i=0; i<m; i++)
	{
		for(int j = 0; j < n; j++)
		{
			data[i][j] = data[i][j]*scale_num +add_num;
		}
	}
	printf("New data: \n\n");

	//print new data set.
	for(int i = 0; i<m; i++)
	{
		for(int j= 0; j<n; j++)
		{
			printf("%d\t",data[i][j]);
		}
		putchar('\n');
	}
	printf("\n\n");


	//turn sameple to 1D array:
	int sample_array[k*k];
	int pivot = 0;
	for(int i=0;i<k;i++)
	{
		for(int j=0;j<k;j++)
		{
			sample_array[pivot] = sample[i][j];
			pivot++;
		}
	}
	//Calculate the correlation coefficient.
	
	int result[m-k][n-k];
	int diff_min;
	for(int i = 0; i< m-k; i++)
	{
		for(int j = 0; j<n-k; j++)
		{
			int CORR;
			int temp_array[k*k];
			int tem_pivot =0;
			for(int p = 0; p<k;p++)
			{
				for(int q=0;q<k;q++)
				{
					temp_array[tem_pivot] = data[i+p][j+q];
					tem_pivot++;
				}
			}
			CORR = find_corr(temp_array, sample_array, k*k);
			result[i][j] = CORR;
		}
	}
	
	/**for(int i = 0; i <m-k; i++)
	{
		for(int j = 0; j<n-k; j++)
		{
			printf("%d ",result[i][j]);
		}
		putchar('\n');
	}
	**/

	////Find the index of the max value:
	//Find min of columns and indices:
	int index[m-k];
	int value[m-k];
	int max_temp;
	for(int j = 0; j< n-k; j++ )
	{
		max_temp = result[0][j];
		index[j] = 0;
		for(int i = 1; i<m-k; i++)
		{
			if(result[i][j] > max_temp)
			{
				max_temp = result[i][j];
				index[j] = i;
			}
		}
		value[j] = max_temp;
	}
	/**
	for (int i = 0; i < n-k; ++i)
	{
		printf("%d\t", value[i]);
	}
	putchar('\n');
	for(int i = 0; i<n-k;i++)
	{
		printf("%d\t", index[i]);
	}**/
	//Find max:
	int max_col = value[0];
	int max_col_index = index[0];
	for(int i=0; i<n; i++)
	{
		if(value[i] > max_col)
		{
			max_col = value[i];
			max_col_index = index[i];
		}
	}
	//give the min and index in column==> data[min_index_col][]
	//min value and index: min_col and min_col_index
	//Now find the min of rows:
	for(int i = 0; i< m-k; i++ )
	{
		max_temp = result[i][0];
		index[i] = 0;
		for(int j = 1; j<n-k; j++)
		{
			if(result[i][j] > max_temp)
			{
				max_temp = result[i][j];
				index[i] = j;
			}
		}
		value[i] = max_temp;
	}
	/**
	for (int i = 0; i < m-k; ++i)
	{
		printf("%d\t", value[i]);
	}
	putchar('\n');
	for(int i = 0; i<m-k;i++)
	{
		printf("%d\t", index[i]);
	}**/
	int max_row = value[0];
	int max_row_index = index[0];
	for(int i=1; i<m; i++)
	{
		if(value[i] > max_row)
		{
			max_row = value[i];
			max_row_index = index[i];
		}
	}
	//give the min and index in row==> data[min_index_col][min_index_row]
	//min value and index: min_row and min_row_index
	printf("The position of matched data is:\nRow: %d\nColumn: %d\n", max_col_index+1, max_row_index+1);
	return(0);
}