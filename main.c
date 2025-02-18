#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024
#define RESULT_MAX 6144
#define CEASAR_ALPHABET_LEN 52
#define MORSE_ALPHABET_LEN 45

// Basic data for different ciphers and codes
const char caesar_alphabet[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char full_alphabet[] = " abcdefghijklmnopqrstuvwxyz0123456789.,?'!:;=";
const char* morse_code[] = {
	" ", ".- ", "-... ", "-.-. ", "-.. ", ". ", "..-. ", "--. ", ".... ", ".. ", ".--- ", "-.- ", ".-.. ", "-- ", "-. ", "--- ", ".--. ", "--.- ", ".-. ", "... ", "- ", "..- ", "...- ", ".-- ", "-..- ", "-.-- ", "--.. ", // A-Z
	"----- ", ".---- ", "..--- ", "...-- ", "....- ", "..... ", "-.... ", "--... ", "---.. ", "----. ",  // 0-9
	".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "---...", "-.-.-.", "-...-" // . , ? ' ! : ; =
};

// The phrase input function
char input(char input_phrase[MAX])
{
	char data = getchar();
	int input_mas_index = 0;

	// Collecting the phrase step by step
	while (data != '\n' && input_mas_index < MAX - 1)
	{
		input_phrase[input_mas_index++] = data;
		data = getchar();
	}

	// Marking the end of the phrase with an end symbol
	input_phrase[input_mas_index] = '\0';

	return;
}

// Interpret the phrase into Morse code
char morse_code_func(char input_phrase[MAX], char result[RESULT_MAX])
{
	int change_index = 0, result_index = 0;
	
	// Check every symbol to find similar ones
	for (int check_input_phrase = 0; check_input_phrase < strlen(input_phrase); check_input_phrase++)
	{
		for (int check_code_alphabet = 0; check_code_alphabet <= MORSE_ALPHABET_LEN; check_code_alphabet++)
		{
			change_index = -1;
			if (isalpha(input_phrase[check_input_phrase]) ? tolower(input_phrase[check_input_phrase]) == full_alphabet[check_code_alphabet] : input_phrase[check_input_phrase] == full_alphabet[check_code_alphabet])
			{
				change_index = check_code_alphabet;
				break;
			}
		}

		// Encrypt every symbol
		if (change_index != -1) strcpy_s(&result[result_index], 7, morse_code[change_index]);
		else strcpy_s(&result[result_index], 18, " Unknown symbol ");
		result_index = strlen(result);
	}

	// Marking the end of the phrase with an end symbol
	result[result_index] = '\0';
	return;
}

// Interpret the phrase into Caesar cipher
char caesar_cipher(char input_phrase[MAX], char result[MAX])
{
	char mode;
	int step = 0;

	// Collecting the step value
	printf("\nEnter step value (1-26): ");
step_repeat:
	scanf_s("%d", &step);
	// Check if the step is correct
	if (step > 26 || isdigit(step) == 1) {
		printf("This value is invalid.\nTry again:\n");
		goto step_repeat;
	}

	// Collecting the mode
	printf("You want to (d)ecrease or (i)ncrease, (use d/i): ");
mode_repeat:
	scanf_s(" %c", &mode);
	// Check if the mode is correct
	if (mode != 'i' && mode != 'd') {
		printf("This value is invalid.\nTry again:\n");
		goto mode_repeat;
	}

	int change_index = 0, result_index = 0;

	// Check every symbol to find similar ones
	for (; result_index < strlen(input_phrase); result_index++)
	{
		// Check if the symbol is correct for encrypting
		if (isalpha(input_phrase[result_index]) == 0)
		{
			result[result_index] = input_phrase[result_index];
			continue;
		}

		for (int check_index1 = 26; check_index1 <= CEASAR_ALPHABET_LEN; check_index1++)
		{
			if (tolower(input_phrase[result_index]) == caesar_alphabet[check_index1])
			{
				change_index = check_index1;
				break;
			}
		}

		// Encrypt every symbol
		if (mode == 'i') result[result_index] = caesar_alphabet[change_index + step];
		else result[result_index] = caesar_alphabet[change_index - step];
	}
	
	// Marking the end of the phrase with an end symbol
	result[result_index] = '\0';
	return;
}

// Interpret the phrase into Atbash cipher
char atbash_cipher(char input_phrase[MAX], char result[MAX])
{
	int change_index = 0, i = 0;

	// Check every symbol to find similar ones
	for (; i < strlen(input_phrase); i++)
	{
		for (int k = 0; k < 26; k++)
		{
			// Check if the symbol is correct for encrypting
			if (input_phrase[i] == ' ') result[i] = ' ';
			if (isalpha(input_phrase[i]) == 0) result[i] = input_phrase[i];
			change_index = -1;

			if (tolower(input_phrase[i]) == alphabet[k])
			{
				change_index = k;
				break;
			}
		}

		// Encrypt every symbol
		if (change_index != -1) result[i] = alphabet[25 - change_index];
	}

	// Marking the end of the phrase with an end symbol
	result[i] = '\0';
	result;
}

// The main part of the program
int main()
{
	char input_phrase[MAX], result[RESULT_MAX];
	int type;

	printf("Input the phrase:\n");
input_repeat:
	input(input_phrase);

	// Check if the phrase is empty
	if (strlen(input_phrase) == 0)
	{
		printf("You enter empty phrase.\nTry again:\n");
		goto input_repeat;
	}

restart:
	// Picking a cipher type
	printf("\nPick what you want to use for your text:\n\t1 - Morse code\n\t2 - Ceasar cipher.\n\t3 - Atbash cipher.\nEnter the value: ");
	scanf_s("%i", &type);

	if (type == 1)
	{
		morse_code_func(input_phrase, result);
		printf("\nMorze code result:\n");
	}
	else if (type == 2)
	{
		caesar_cipher(input_phrase, result);
		printf("\nCaesar cipher result:\n");
	}
	else if (type == 3)
	{
		atbash_cipher(input_phrase, result);
		printf("\nAtbash cipher result:\n");
	}
	
	// Printing the result
	for (int i = 0; i < strlen(result); i++)
	{
		printf("%c", result[i]);
	}

	char restart_question;
repeat_question:
	// Restart program?
	printf("\nDo you want to continue? (Y/N): "),
	scanf(" %c", &restart_question);
	if (restart_question == 'Y') goto restart;
	else if (restart_question == 'N') return 0;
	else goto repeat_question;
	return 0;
}