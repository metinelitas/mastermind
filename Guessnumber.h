#ifndef GUESSNUMBER_H
#define GUESSNUMBER_H


class GuessNumber
{
public:
    GuessNumber();
    int getRandomNumberToGuess();
private:
    int array_number_to_guess[5];
    int number_to_guess;
    void generateRandomNumber();
};

#endif // GUESSNUMBER_H
