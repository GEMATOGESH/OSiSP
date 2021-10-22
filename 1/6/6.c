#include <stdlib.h>   
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *first_file_p, *fileOut;
    
    if ((first_file_p = fopen(argv[1], "r")) == NULL)
    {
        printf("Error while opening first file.");
        return;
    }
    
    if ((second_file_p = fopen(argv[2], "w+")) == NULL)
    {
        printf("Error while opening second file.");
        return;
    }

    char ch, result[255] = "", str[255];    
    int error = -1, chCounter = 0, linesCounter = 0, chTotal = 0;

    while ((ch = getc(first_file_p)) != EOF)
    {
    	if (ch != '\n')
        {
            chCounter++;
        }
        else 
        {
            linesCounter++;       
            
            sprintf(str, "%d. %d\n", linesCounter, chCounter); 
            
            error = fputs(str, second_file_p);    	
     	    if (error == EOF)
    	    {
    	        printf("Error while writing a file.");    	   
    	        break;
    	    }
    	    
    	    chTotal += chCounter;
    	    chCounter = 0;
        }
    }
    
    sprintf(result, "Total: %d lines %d symbols", linesCounter, chTotal);
    
    error = fputs(result, second_file_p);
    if (error == EOF)
    {
        printf("Error while writing a file.");    	
        return;
    }

    if (fclose(first_file_p) == EOF)
    {
        printf("Error while closing first file!");
        
        return;
    }
    
    if (fclose(second_file_p) == EOF)
    {
        printf("Error while closing second file!");
        return;
    }
    
    printf("Success.\n");
}
