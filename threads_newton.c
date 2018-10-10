#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<complex.h>
#include<math.h>
#include<time.h>
#include<pthread.h>


/*global variables*/
#define M_pi 3.14159
double *valuesx,*valuesy;
int ** rgb,**convergence;
float d1;
int d;	
float rgbscaling;
int threads;
float div1;
int dimension;
FILE *write,*write1;	
pthread_mutex_t mutex_write;
int block_size;
char **p;
char *item_done;
char **conv;
/*function declaration*/
void tostring(char str[], int num);

long double measuretime(struct timespec ts,struct timespec ts1);
void *newtonmethod(void * restrict arg);
void * write_main(void * restrict args);
void mul_cpx_mainfile(double *a_re,double *a_im,double *b_re,double *b_im,int k);
int main(int argc, char *argv[])
{struct timespec ts,ts1;
	long double totaltime=0;
	for(int op=0;op<1;op++){
		timespec_get(&ts,TIME_UTC);
		d=strtol(argv[3],NULL,10);
		pthread_mutex_init(&mutex_write, NULL);
		rgbscaling=16581375/(d);
		if(argv[1][1]>argv[2][1])
		{threads=strtol((strtok(argv[1], "-t")),NULL,10); 
			dimension=strtol((strtok(argv[2],"-l")),NULL,10);}
		else
		{threads=strtol((strtok(argv[2], "-t")),NULL,10); 
			dimension=strtol((strtok(argv[1],"-l")),NULL,10);
		}
		item_done=(char*)malloc(sizeof(char)*dimension);
		block_size=dimension/threads;
		pthread_t* compute_threads = (pthread_t*)malloc(sizeof(pthread_t*)*threads);
		for (int ix =0 ; ix <dimension; ++ix){

			item_done[ix]=0;

		}
		pthread_t* write_thread = (pthread_t*)malloc(sizeof(pthread_t*));
		div1=(4.0/(dimension-1));
		valuesx=(double*) malloc(sizeof(double)*dimension);
		valuesy=(double*) malloc(sizeof(double)*dimension);
		p=(char**)malloc(sizeof(char*)*dimension);
		for(int i=0;i<dimension;i++)
			p[i]=(char*)malloc(sizeof(char)*dimension*15);
		conv=(char**)malloc(sizeof(char*)*dimension);
		for(int i=0;i<dimension;i++)
			conv[i]=(char*)malloc(sizeof(char)*dimension*15);

		d1=(float) (d);	
		char trgb[]="read.ppm";
		char tcon[]="read1.ppm";
		write=fopen(trgb,"w");
		fprintf(write,"%s\n","P3");
		fprintf(write,"%d %d\n",dimension,dimension);
		fprintf(write,"%d\n",255);
		write1=fopen(tcon,"w");
		fprintf(write1,"%s\n","P3");
		fprintf(write1,"%d %d\n",dimension,dimension);
		fprintf(write1,"%d\n",50);
		for(int i=0;i<d;i++)


		{	valuesx[i]=cos(2*i*M_PI/(d));
			valuesy[i]=sin(2*i*M_PI/(d));

		}
		int ix=0;
		int count =0;
		for(int tx=0;tx<threads ; tx++)
		{//	printf("%d",count);
			size_t * args = malloc(sizeof(size_t));
			*args= tx;
			pthread_create(&compute_threads[ix],NULL,newtonmethod,(void*)args);
			count=count+1;
			ix=ix+1;
		}
		pthread_create(&write_thread,NULL,write_main,NULL);
		for(int tx=0; tx<threads;++tx){
			if(pthread_join(compute_threads[tx],NULL)){
				printf("Error  \n");
				exit(1);
			}
		}
		fclose(write);
		fclose(write1);
		timespec_get(&ts1,TIME_UTC);
		totaltime=totaltime+measuretime(ts,ts1);
	/*	if(op!=9)
		  {remove(trgb);
		  remove(tcon);}*/
		free(compute_threads);
		free(valuesx);
		free(valuesy);
	}
	printf("%Lf",totaltime);
	return 0;
}

void* newtonmethod(void *restrict arg)
{	char c[20];
	char e[20];
	size_t input= *((size_t*)arg);
	int n,result,flag;
	free(arg);
	for ( size_t i=input; i<dimension; i+=threads){ 	
		char *l=p[i];
		char *h=conv[i];
		flag=0;
		int counter=0;
		int root;
		double are,aim,bre,bim;
		for(int j=0;j<dimension;j++)
		{	n=0;
			result=0;
			are=(-2+div1*j);
			aim=(-2+(div1*i));
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
				tostring(c,(int)root/(255*255) );
				l=stpcpy(l,c);

			l=stpcpy(l," ");
			tostring(c,(int)(root/255)%255 );
			l=stpcpy(l,c);
			l=stpcpy(l," ");
			tostring(c,(int) root%255 );
                        l=stpcpy(l,c);
                        l=stpcpy(l," ");
			tostring(e,n);

			h=stpcpy(h,e);
			h=stpcpy(h," ");
			h=stpcpy(h,e);
                        h=stpcpy(h," ");
			h=stpcpy(h,e);
                        h=stpcpy(h," ");

if(j==dimension-1)
{h=stpcpy(h,"\n");
	l=stpcpy(l,"\n");
}
		//	sprintf(c,"%d %d %d ",(int)root/(255*255),(int)(root/255)%255,(int) root%255);
		//	sprintf(e,"%d %d %d ",n,n,n);
			
		}	//p[i]=stpcpy(p[i],"\n");
//		strcat(conv[i],"\n");
		pthread_mutex_lock(&mutex_write);
		item_done[i] =1;
		pthread_mutex_unlock(&mutex_write);
//		printf("itemdone %d",item_done[i]);
		

	}}
void mul_cpx_mainfile(double *a_re,double *a_im,double *b_re,double *b_im,int k){


	double a,b;
	for(int j=0;j<=k;j++)
	{       if(k==0)
		{	*a_re=1;
			break;
		}
		if(j==1)
		{	 a=*b_re;
			b=*b_im;
			*a_re=a;
			*a_im=b;

		}


		else
		{	*a_re=a**b_re-b**b_im;
			*a_im=(*b_re*b)+(a**b_im);
			a=*a_re;
			b=*a_im;
		}


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



void * write_main(void * restrict args){
	struct timespec sleep_timespec;
	char * item_done_loc =(char*)calloc(dimension,sizeof(char));
	for (size_t ix =0 ;ix< dimension; ){
		pthread_mutex_lock(&mutex_write);
		if(item_done[ix] != 0)
			memcpy(item_done_loc ,item_done, dimension*sizeof(char));
		

		pthread_mutex_unlock(&mutex_write);
		if (item_done_loc[ix]==0){
			nanosleep(&sleep_timespec,NULL);
				continue;
		}
		for (;ix <dimension && item_done_loc[ix] !=0;++ix){
			fputs(p[ix],write);
			fputs(conv[ix],write1);
			
//		printf("ix %d",ix);
		}
		}
	
}
void tostring(char str[], int num)
{
    if(num==0)
    {   str[0]='0';
    		str[1]=0;}
    else
    {
	int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';}
}

