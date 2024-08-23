int compare_doubles(double x1, double x2) 
{   
    $$


    
    if (fabs(x1 - x2) < x_min) {
        return 0;  
    }
    return (x1 < x2) ? -1 : 1; 
}