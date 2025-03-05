#include "functions.h"

status bisection_method(double *res, double left, double right, double eps,  double (*f)(double)) {
    if(!f || !res || eps <= __DBL_EPSILON__) return INPUT_ERROR;

    double mid = (right - left) / 2. + left;

    if(f(left) * f(right) > 0) return NO_ROOTS;

    while(fabs(right - left) > eps) {
        if(fabs(f(mid)) < __DBL_EPSILON__) {
            *res = mid;
            return OK;
        }
        if(f(left) * f(mid) < 0.) right = mid;
        else left = mid;
        mid = (right - left) / 2. + left;
    }

    *res = (right - left) / 2. + left;
    
    return OK;
}

double func1(double x)
{
    return x - 11.2232;
}

double func2(double x)
{
    return sin(x) - 1 / x;
}

double func3(double x)
{
    return x * x + 10 * x - 4;
}

double func4(double x)
{
    return x + x * x + 3 * x * x * x + 1;
}

double func5(double x)
{
    return sqrt(x) - 4.4;
}

// double func1(double x) { 
//     return 2. * x - 5.; //todo
// }



























// status dichotomy_method(double *res, double left, double right, double eps, double (*f)(double))
// {
//     if (eps <= 0. || !res || !f)
//         return INPUT_ERROR;
//     double fl = f(left);
//     if (fl * f(right) > 0.)
//         return NO_ROOTS;
//     double mid;

//     while (fabs(right - left) >= eps)
//     {
//         mid = (left + right) / 2;
//         if (fl * f(mid) <= 0.)
//             right = mid;
//         else
//             left = mid;
//     }
//     *res = (right + left) / 2;
//     return OK;
// }


// double func2(double x) { 
//     return exp(x) - 2; 
// }

// double func3(double x) {
//     return log(x) - 1; 
// }
// double func4(double x) {
//     return x*x - 3*x + 2; 
// }
// double func5(double x) { 
//     return cos(x); 
// }