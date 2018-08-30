/* This is the concole excutable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/
#include <iostream> //preprocessor directive, <> for standard 
#include <string>  // #include mean copy and paste 
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;


// prototype
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}

void PrintIntro()
{
	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
	return;
}

// loop untill valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		// get a guess from the user
		FText Guess = "";
		std::cout << "Try " << CurrentTry << ". Enter your guess: " << std::flush;
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters." << std::endl;
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?" << std::flush;
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 count = 0; count < MaxTries; count++)
	{
		FText Guess = GetValidGuess(); // TODO make loop checking valid guesses 

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.Submitguess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls << " " << std::flush;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	// TODO add a game summary 
}

	


