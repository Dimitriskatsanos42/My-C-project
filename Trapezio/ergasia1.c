#include <stdio.h>

#include <math.h>


double fun(double x)

{

    return (pow(x,3)+x+1);

}



double integrate(double a,double b,int N)

{

    double E,Xi;
    Xi= (b-a)/N;
    E=(fun(a)+fun(a+N*Xi))/2;
    for ( int k=0; k<=N; k++)
    {    
      E+= fun(a+k*Xi);

    }
     E*=Xi;
     return E;

}

 int main()

{

    double a,b,x;

    int N;

    printf("Value of a:");

    scanf("%lf",&a);

    printf("Value of b:");

    scanf("%lf",&b);

    printf("Value of N:");

    scanf("%d",&N);

    x=integrate(a,b,N);

    printf("%lf",x);



    return 0;

}
/*  h=(b-a)/n;
    sum=(f(a)+f(a+n*h))/2;
    for(i=1;i<n;i++)
        sum+=f(a+i*h); 
    sum=sum*h;  */



