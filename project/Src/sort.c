#include "sort.h"

typedef struct sort_struct
{
	uint16_t address;
	float value;
}sort_struct;

sort_struct sort_array[1030];
sort_struct sort_array2[16];

void Struct_Sort(float *struct_array)
{
	uint16_t i=0,j=0;
	sort_struct array_temp;
	for(i=0;i<1024;i++)
	{
		sort_array[i].address=i;
		sort_array[i].value=struct_array[i];
	}
	
	//对结构体按照幅度进行冒泡排序
	for(i=0;i<1024;i++)
	{
			for(j=0;j<1024-i-1;j++)
			{
				if(sort_array[j].value>sort_array[j+1].value)
				{
							array_temp=sort_array[j];
							sort_array[j]=sort_array[j+1];
							sort_array[j+1]=array_temp;
				}
			}
	}	
	
	for(i=0;i<15;i++)
		sort_array2[i]=sort_array[1024-i];
	
	//对选出的幅度最大的15个值按照频率排序
	for(i=0;i<15;i++)
	{
		for(j=0;j<15-i-1;j++)
		{
			if(sort_array2[j].address>sort_array2[j+1].address)
			{
				array_temp=sort_array2[j];
				sort_array2[j]=sort_array2[j+1];
				sort_array2[j+1]=array_temp;
			}				
		}
	}
	
	printf("_________________________");
	
	for(i=0;i<15;i++)
		printf("%d:%.2f\r\n",sort_array2[i].address,sort_array2[i].value);
	
	printf("_________________________");	
}

