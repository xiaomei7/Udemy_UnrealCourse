/*The Game Logic*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

// DO NOT use namespace inside a header file
class FBullCowGame 
{
public:
	// constructor
	FBullCowGame();

	// const only works on class functions
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const; 
	bool IsGameWon() const;
	
	void Reset(); 
	EGuessStatus CheckGuessValidity(FString);
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization 
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};