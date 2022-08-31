int abs(int number) {
    if(number > 0)
        return number;
    else
        return number * -1;
}
//lack of precision for number > 20
/*
double ln(int number) {
    double x = (number-1)/(number+1);
    return 2*( x + ((x*x*x)/3) + ((x*x*x*x*x)/5) + ((x*x*x*x*x*x*x)/7) + ((x*x*x*x*x*x*x*x*x)/9) + ((x*x*x*x*x*x*x*x*x*x*x)/11) + ((x*x*x*x*x*x*x*x*x*x*x*x*x)/13) + ((x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/15) + ((x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/17) + ((x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/19) + ((x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x*x)/21));
}

double log10(int number) {
    return ln(number)/2.30258509299405; //divided by ln(10)
}*/

void memory_copy(char *source, char *destination, int nbr_bytes) {
    for (int i=0; i < nbr_bytes; i++) {
        destination[i] = source[i];
    }
}
/*
int number_len(int number) {
    if (number>0)
        return (int) (log10(number)+1);
    else if (number == 0)
        return 1;
    else
        return (int) (log10(abs(number))+2);
}*/

void int_to_str(int dataIn, char* bffr, int radix){
    int temp_dataIn;
    temp_dataIn = dataIn;
    int stringLen=1;

    while ((int)temp_dataIn/radix != 0){
        temp_dataIn = (int)temp_dataIn/radix;
        stringLen++;
    }
    temp_dataIn = dataIn;
    do{
        *(bffr+stringLen-1) = (temp_dataIn%radix)+'0';
        temp_dataIn = (int) temp_dataIn / radix;
    } while (stringLen--);
}