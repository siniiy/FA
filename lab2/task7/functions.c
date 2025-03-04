#include "functions.h"

status dichotomy_method(double *res, double left, double right, double eps, double (*f)(double))
{
    if (eps <= 0. || !res || !f)
        return INPUT_ERROR;
    double fl = f(left);
    if (fl * f(right) > 0.)
        return NO_ROOTS;
    double mid;

    while (fabs(right - left) >= eps)
    {
        mid = (left + right) / 2;
        if (fl * f(mid) <= 0.)
            right = mid;
        else
            left = mid;
    }
    *res = (right + left) / 2;
    return SUCCESS;
}

double func1(double x) { 
    return 2*x + 5; 
}

double func2(double x) { 
    return exp(x) - 2; 
}

double func3(double x) {
    return log(x) - 1; 
}
double func4(double x) {
    return x*x - 3*x + 2; 
}
double func5(double x) { 
    return cos(x); 
}