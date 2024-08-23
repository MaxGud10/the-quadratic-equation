//! @file  

//! функция для проверки unit тестов 

//! функция спрашивает нужны ли тебе unit тесты (YES/NO)

//! @param word массив с длинной CHAR_CONST для ввода ответа пользователя (YES/NO)
//! @param CHAR_CONST константа для размера массива word
//! @param data массив из параметров <b> a, b, c </b> для unit тестов
//! @param Data_number константа для размера массива data




int offer_test( char word[CHAR_CONST], const struct str_test data [Data_number])
{   
    
    scanf("%s", word);

    if (strcasecmp(word, "Yes") == 0 || strcasecmp(word, "yes") == 0)
    {
        proverka(data);
        return 0;

    }
    else if (strcasecmp(word, "No") == 0 || strcasecmp(word, "no") == 0) 
    {
        printf("Exiting the program.\n");
        return 0;
    }
    else printf("Invalid input, exiting.\n");
    return 0;
}