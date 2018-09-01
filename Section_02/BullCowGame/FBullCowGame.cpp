#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// to make syntax unreal friendly
using int32 = int;
using FString = std::string;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";

	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bIsGameWon = false;
	return;
}

// receives a VALID guess, incriments # of tries, return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else 
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bIsGameWon = true;
	}
	else {
		bIsGameWon = false;
	}
	return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	// if the guess isn't an isogram, return an error
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram; 
	}
	// if the guess isn't all lower case, return an error
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase; 
	}
	//  if the guess length length is wrong, return an error
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EGuessStatus::Wrong_Length;
	}
	// otherwise, return OK
	else 
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup out map
	TMap<char, bool> LetterSeen;
	// loop through all the letters of the word
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed cases
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we do NOT have an isogram
		}
		// otherwise
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))// if not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
