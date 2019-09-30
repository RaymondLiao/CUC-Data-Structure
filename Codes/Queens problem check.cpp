//#include<stdio.h>
//#include<math.h>
//int a[20]={0};
//int n,t;
//
//
//void Try(int i);
//void Output(void);
//
//int main()
//{
//	scanf_s("%d", &n);
//
//	Try(1);
//	getchar();
//	getchar();
//	return 0;
//}
//
//void Output(void)
//{
//	t += 1;
//	printf("%d.", t);
//	for (int k=1; k<=n; ++k)
//	{
//		printf("%d ", a[k]);
//	}
//	putchar(10);
//}
//
//int check(int k)
//{
//		for (int i=1; i<=k-1; ++i)
//		{
//			if(((abs(a[i] - a[k]) == abs(i - k)) || (a[i] == a[k])))
//				return 0;
//		}
//	return 1;
//}
//
//void Try(int i)
//{
//	int j;
//	for (j=1; j<=n; ++j)
//	{
//		a[i] = j;
//		if (!check(i))
//		{
//			a[i] = 0;
//			continue;
//		}
//		if (i < n)
//		{
//			Try(i + 1);
//		}
//		else
//		{
//			Output();
//		}
//			
//	}
//}
//
//
//
