// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double exponentiation(double left, double right) {
    double final_value=1;
    int r=right;
    for (int i=0;i < r;++i){
        final_value=final_value*left;
    }
    return final_value;
}
