int factorialNumber (int number)
{
    int r = 1;
    for (int i = 2; i <= number; ++i)
        r *= i;
    return r; 
}