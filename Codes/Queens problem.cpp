#include<stdio.h>

int a[20],b[20],c[40],d[40];
int n,t,i,j,k;


void Try(int i);
void Output(void);

int main()
{
	scanf_s("%d", &n);

	for(i=1; i<=n; ++i)
	{
		b[i] = 0;
		c[i] = 0;	c[n + i] = 0;
		d[i] = 0;	d[n + i] = 0;
	}
	Try(1);
	getchar();
	getchar();
	return 0;
}

void Output(void)
{
	t += 1;
	printf("%d.", t);
	for (int k=1; k<=n; ++k)
	{
		printf("%d ", a[k]);
	}
	putchar(10);
}

void Try(int i)
{
	int j;
	for (j=1; j<=n; ++j)
	{
		if((b[j]==0) && (c[i+j]==0) && (d[i-j+n]==0))
		{
			a[i] = j;
			b[j] = 1;
			c[i+j] = 1;
			d[i-j+n] = 1;
			if(i<n)
			{
				Try(i + 1);
			}
			else
			{
				Output();
			}
			b[j] = 0;
			c[i+j] = 0;
			d[i-j+n] = 0;
		}		
	}
}