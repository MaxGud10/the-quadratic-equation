//! @file 

//! функция для защиты ввода параметров <b> a, b, c</b> для решения квадратного уравнения  ax^2 + bx +c

//! если пользователь будет вводить неправильно параметры, то эта функция не даст это сделать
//! параметры <b>a, b,c</b> могут быть только целочисленными или с плавающей точкой 

//! ax^2 + bx +c
//! @param a - первый коэффициент квадратного уравнения
//! @param b - второй коэффициент квадратного уравнения 
//! @param c - третий коэффициент квадратного уравнения 
//! @param ch - переменная символьного типа для удаления неправильных типов переменной коэффициентов квадратного уравнения  
//! @param  





int check_input(double *a, double *b, double *c)
{   
    while (1) {
        printf("Enter coefficients a, b, c:\n");

        int result = scanf("%lf %lf %lf", a, b, c);
        
        
        if (result == 3) {
            break; 
        } else 
        {
            printf("Invalid input, please enter numeric values.\n");
            clean_bufer();
            break;
        }
    }

    return 0;
}

int clean_bufer()
{
    for (;;)
    {   
        
        int ch = getchar();
        if( ch == '\n' || ch == EOF)
        {
            return 0;
        }
    }
    return 0;
}