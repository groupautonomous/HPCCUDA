#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<complex.h>
#include<math.h>
#include<time.h>
#define M_pi 3.14159
long double measuretime(struct timespec ts,struct timespec ts1);
void mul_cpx_mainfile(double *a_re,double *a_im,double *b_re,double *b_im,int k);
void newtonmethod(double complex a,int d,int *n,double *valuesx,double *valuesy,long int dimension,int *result);
int main(int argc, char *argv[])
{struct timespec ts,ts1;
	timespec_get(&ts,TIME_UTC);
	int iter;	int d;
	float rgbscaling;
	int threads,dimension;
	float div;
	int i,result,n,j,counter;
	int flag=0;
	d=strtol(argv[3],NULL,10);
	rgbscaling=16581375/(d);

	if(argv[1][1]>argv[2][1])
	{threads=strtol((strtok(argv[1], "-t")),NULL,10); 
		dimension=strtol((strtok(argv[2],"-l")),NULL,10);}
	else
	{threads=strtol((strtok(argv[2], "-t")),NULL,10); 
		dimension=strtol((strtok(argv[1],"-l")),NULL,10);}
	div=(4.0/(dimension-1));
	printf("%0.4f",div);
	int root;
	float d1=(float) (d);	
if(d==1)
{iter=20;}
else{iter=50;}
	int * esentries = (int*) malloc(sizeof(int) *(dimension)* (dimension)*(dimension));
	int ** rgb= (int**) malloc(sizeof(int*) * (dimension));
	for ( size_t ix = 0, jx = 0; ix <dimension; ++ix, jx+=3*(dimension))
		rgb[ix] = esentries + jx;

	int * fsentries = (int*) malloc(sizeof(int)*(dimension) * (dimension)*(dimension));
	int ** convergence= (int**) malloc(sizeof(int*) * (dimension));
	for ( size_t ix = 0, jx = 0; ix <dimension; ++ix, jx+=3*(dimension) )
		convergence[ix] = fsentries + jx;
	double are;
	double aim;
	double bre;
	double bim;
	double *valuesx=(double*) malloc(sizeof(double)*dimension);
	double *valuesy=(double*) malloc(sizeof(double)*dimension);	 
	FILE *write,*write1;
	write=fopen("read.ppm","w");
	write1=fopen("read1.ppm","w");
	printf("d=%d",d);
	for(i=0;i<d;i++)
	{	valuesx[i]=cos(2*i*M_pi/(d));
		valuesy[i]=sin(2*i*M_pi/(d));

	}
	for(i=0;i<dimension;i++)
	{counter=0;
		for(j=0;j<dimension;j++)
		{	n=0;
			result=1;
			are=(-2+div*j);
			aim=(-2+(div*i));
			flag=0;
			for(int k=0;k<100;k++)
			{//	printf("are=%f",are);
				if(flag==1)
				{
					n=k;
					break;}
				else
				{
					mul_cpx_mainfile(&bre,&bim,&are,&aim,d-1);
					are=are*((d1-1)/d1)+((bre/((bre*bre+bim*bim)*d1)));
					aim=(aim*((d1-1)/d1)-(bim/((bre*bre+bim*bim)*d1)));
					for(int x=0;x<d;x++)
					{if((((are-valuesx[x])*(are-valuesx[x]))+((aim-valuesy[x])*(aim-valuesy[x])))<0.000001)	
						{flag=1;
							result=x;
							break;	
						}	

						else if((((are*are)+(aim*aim))<0.000001)||are>10000000000||aim>10000000000)
						{flag=1;
							result=0;
							break;
						}	}
				}}
			root=result*rgbscaling	;
				
			rgb[i][counter]=(int)root/(255*255);
                        rgb[i][counter+1]=(int)(root/255)%255;
                        rgb[i][counter+2]=(int) root%255;
                        convergence[i][counter]=(int)n;
                        convergence[i][counter+1]=(int)n;
                        convergence[i][counter+2]=(int)n;
			counter=counter+3;
		}
	}
	fprintf(write,"%s\n","P3");
	fprintf(write,"%d %d\n",dimension,dimension);
	fprintf(write,"%d\n",255);
	for(i=0;i<dimension;i++)
	{//printf("\n");
		for(int j=0;j<3*(dimension);j++)
		{fprintf(write,"%d ",rgb[i][j]);
		}fprintf(write,"\n");
	}
	fclose(write);
	fprintf(write1,"%s\n","P3");
		fprintf(write1,"%d %d\n",dimension,dimension);
		fprintf(write1,"%d\n",iter);

		for(i=0;i<dimension;i++)
		{//printf("\n");
		for(int j=0;j<3*(dimension);j++)
		{fprintf(write1,"%d ",convergence[i][j]);
	}fprintf(write1,"\n");
	}
	timespec_get(&ts1,TIME_UTC);
	long double totaltime=measuretime(ts,ts1);
	printf("time=%Lf",totaltime);

	fclose(write1);
	free(valuesx);
	free(valuesy);
	free(fsentries);
	free(esentries);
	free(rgb);
	free(convergence);
	printf("threads is %d Dimension is %d",threads,dimension);
	return 0;
}
void mul_cpx_mainfile(double *a_re,double *a_im,double *b_re,double *b_im,int k){
	double a,b;
	for(int j=0;j<=k;j++)
	{       if(k==0)
		{*a_re=1;
			break;}
		if(j==1)
		{ a=*b_re;
			b=*b_im;
			*a_re=a;
			*a_im=b;

		}
		

		else
		{*a_re=a**b_re-b**b_im;
			*a_im=(*b_re*b)+(a**b_im);
			a=*a_re;
			b=*a_im;}


	}}

long double measuretime(struct timespec ts,struct timespec ts1)
{time_t s1,s2;
	long ns1,ns2;
	long double finaltime;
	s1=ts.tv_sec;
	s2=ts1.tv_sec;
	ns1=ts.tv_nsec;
	ns2=ts1.tv_nsec;
	if((ns2-ns1)<0)
		finaltime=s2-s1-1+((1000000000.0+ns2-ns1)/1000000000.0);
	else
		finaltime=s2-s1+((ns2-ns1)/1000000000.0);
	return finaltime;
}
