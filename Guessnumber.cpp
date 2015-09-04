#include "Guessnumber.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

GuessNumber::GuessNumber()
{

}

int GuessNumber::getRandomNumberToGuess()
{
    generateRandomNumber();
    return number_to_guess;
}

void GuessNumber::generateRandomNumber()
{
    srand(time(NULL));

    int generated_number_count = 0;


    for(;;)
    {
        int r = rand()%10;

        if (generated_number_count == 5)
            break;

        if (r==0)
        {
            continue;
        }
        array_number_to_guess[generated_number_count] = r;
        generated_number_count++;
    }

    for(int i=4;i>-1;i--)
       fprintf(stderr,"number_to_guess[%d]:%d\n",i,array_number_to_guess[i]);

    number_to_guess = array_number_to_guess[0] + array_number_to_guess[1]*10 +
            array_number_to_guess[2]*100 + array_number_to_guess[3]*1000 + array_number_to_guess[4]*10000;
}

