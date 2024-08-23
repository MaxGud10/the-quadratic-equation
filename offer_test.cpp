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