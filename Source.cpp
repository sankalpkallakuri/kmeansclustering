//written by sankalp kallakuri -- Date 19/08/16//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int K=2;
void generatedata(float** data,int *clustername,int N,int dims);
void cluster(float** data,int *clustername,int N,int dims);
void assignclusters(float **centroids,float** data,int *clustername,int N,int dims);
void findcentroids(float **centroids,float** data,int *clustername,int N,int dims);
void main()
{
	int iter =0;
	int Iterations =10;
	int i=0;
	int dims = 4;
	int N = 100;
	int NumClust = 2;
	float **data =(float **)calloc(N,sizeof(float *));
	for(i=0;i<N;i++)
	{
		 data[i]=(float *) calloc(dims+1,sizeof(float));
	
	}
	int *clustername = (int*)calloc(N,sizeof(int));
	int **clusters = (int**)calloc(Iterations,sizeof(int*));
	for(i=0;i<Iterations;i++)
	{
		clusters[i] = (int *)calloc(N,sizeof(int));
	
	}
	generatedata(data,clustername,N,dims);
	
	for(iter=0;iter<Iterations;iter++)
	{
		for(i=0;i<N;i++)
		{
			clustername[i]=-1;
			data[i][dims]= -1.0f;
		}
	
		cluster(data,clustername,N,dims);
	
		for(i=0;i<N;i++)
		{
			printf("%d ",clustername[i]);
			clusters[iter][i] = clustername[i]; 
		}
		printf("____%d_____\n",iter);
	}
	for(i =0;i<Iterations;i++)
	{
		free(clusters[i]);
	}
	free(clusters);
	getchar();
}
void generatedata(float** data,int *clustername,int N,int dims)
{
	int i,j;
	
	
	for ( i = 0; i < N; i++)
	{
		for ( j = 0; j < dims; j++)
		{
			data[i][j]= (float)rand()/(float)RAND_MAX;
		}
	}
	for (i = 0; i < N; i++)
	{
		for ( j = 0; j < dims; j++)
		{
			if(i%2==0)
			{
				data[i][j]+= 2.0f;
			}
			else
			{
				data[i][j]+=7.0f;			
			}
			printf("%f ", data[i][j]);
		}
		printf("\n");
	}  
	
}
void cluster(float** data,int *clustername,int N,int dims)
{
	int i =0;
	int j =0;
	int cindex=0;
	int whilecount =0;
	float acc =0.0f;
	float **centroids= (float**)calloc(K,sizeof(float*));
	float **centroids_prev= (float**)calloc(K,sizeof(float*));
	for(j=0;j<K;j++)
	{
		centroids[j] = (float*)calloc(dims,sizeof(float));
		centroids_prev[j] = (float*)calloc(dims,sizeof(float));
	}
	
	while(i<K)
	{ 
		cindex=(int)N*((float)rand()/(float)RAND_MAX);
		if(data[cindex][dims]==-1)
		{
			for(j=0;j<dims;j++)
			{
				centroids[i][j]=data[cindex][j];// these should be randomly chosen
			    data[cindex][dims]=1;     
		
			}
			i++;
		}
	}
	whilecount =0;
	do
	{
		assignclusters(centroids,data,clustername,N,dims);
		findcentroids(centroids,data,clustername,N,dims);
		acc =0.f;
		for(i=0;i<K;i++)
		{
			for(j=0;j<dims;j++)
			{
				acc = acc+ abs(centroids_prev[i][j] - centroids[i][j]); 			
			}
		}
		
		if(acc<=0.001f)
		{
			break;
		}
		printf("%f___ %d \n",acc,whilecount);
		
		for(i=0;i<K;i++)
		{
			for(j=0;j<dims;j++)
			{
				centroids_prev[i][j] = centroids[i][j]; 			
			}
		}
		whilecount++;
	} while (true);


}
void assignclusters(float **centroids,float** data,int *clustername,int N,int dims)
{
	int i=0;
	int j=0;
	int dimI=0;
	int minIndex =0;
	float minVal =0.f;
	//float * distances = (float*)calloc(K,sizeof(float));
	//float distances[2];
	for(i=0;i<N;i++)
	{
		float * distances = (float*)calloc(K,sizeof(float));
		for(j=0;j<K;j++)
		{
			
			for(dimI=0;dimI<dims;dimI++)
			{
				distances[j]= distances[j]+ (centroids[j][dimI]-data[i][dimI]) * (centroids[j][dimI]-data[i][dimI]);
			}
		
		}
	
	    minIndex =-1;
		minVal = 1000.0f; 
		for(j=0;j<K;j++)
		{
			if(minVal>distances[j])
			{
				minVal = distances[j];
				minIndex = j;
			}
		}
		clustername[i]=minIndex;
		free(distances);
	}
	//free(distances);

}
void findcentroids(float **centroids,float** data,int *clustername,int N,int dims)
{
	int i=0;
	int j=0;
	int dimI=0;
	int counter =0;
	float **calc_centroids= (float**)calloc(K,sizeof(float*));
	for(j=0;j<K;j++)
	{
		calc_centroids[j] = (float*)calloc(dims,sizeof(float));
	}
	for(i=0;i<K;i++)
	{
		for(dimI=0;dimI<dims;dimI++)
		{
			for(j=0;j<N;j++)
			{
				if(clustername[j]==i)
				{
				
					calc_centroids[i][dimI] += data[j][dimI];
				    counter++;
				}
			
			}
			calc_centroids[i][dimI]= calc_centroids[i][dimI]/(float)counter;
		    counter =0;
		}
	}
	for(i=0;i<K;i++)
	{
		for(j=0;j<dims;j++)
		{
			centroids[i][j]=calc_centroids[i][j];
		}
	}
	for(i=0;i<K;i++)
	{
		free(calc_centroids[i]);
	}
	free(calc_centroids);

}