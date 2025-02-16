#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 1024
#define RESULT_MAX 6144
const char caesar_alphabet[] = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
const char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
const char full_alphabet[] = " abcdefghijklmnopqrstuvwxyz0123456789.,?'!:;=";
const char* morse_code[] = {
	" ", ".- ", "-... ", "-.-. ", "-.. ", ". ", "..-. ", "--. ", ".... ", ".. ", ".--- ", "-.- ", ".-.. ", "-- ", "-. ", "--- ", ".--. ", "--.- ", ".-. ", "... ", "- ", "..- ", "...- ", ".-- ", "-..- ", "-.-- ", "--.. ", // A-Z
	"----- ", ".---- ", "..--- ", "...-- ", "....- ", "..... ", "-.... ", "--... ", "---.. ", "----. ",  // 0-9
	".-.-.-", "--..--", "..--..", ".----.", "-.-.--", "---...", "-.-.-.", "-...-" // . , ? ' ! : ; =
};

char input(char input_phrase[MAX])
{
	char data = getchar();
	int index = 0;
	while (data != '\n' && index < MAX - 1)
	{
		input_phrase[index++] = data;
		data = getchar();
	}

	input_phrase[index] = '\0';

	return;
}

char morse_code_func(char input_phrase[MAX], char result[RESULT_MAX])
{
	int num = 0, result_index = 0;
	for (int i = 0; i < strlen(input_phrase); i++)
	{
		for (int k = 0; k < 46; k++)
		{
			num = -1;
			if (isalpha(input_phrase[i]) ? tolower(input_phrase[i]) == full_alphabet[k] : input_phrase[i] == full_alphabet[k])
			{
				num = k;
				break;
			}
		}
		if (num != -1) strcpy_s(&result[result_index], 7, morse_code[num]);
		else strcpy_s(&result[result_index], 18, " Unknown symbol ");
		result_index = strlen(result);
	}

	result[result_index] = '\0';
	return;
}

char caesar_cipher(char input_phrase[MAX], char result[MAX])
{
	char mode;
	int step = 0;

	printf("\nEnter step value (1-26): ");
step_repeat:
	scanf_s("%d", &step);
	if (step > 26 || isdigit(step) == 1) {
		printf("This value is invalid.\nTry again:\n");
		goto step_repeat;
	}

	printf("You want to (d)ecrease or (i)ncrease, (use d/i): ");
mode_repeat:
	scanf_s(" %c", &mode);
	if (mode != 'i' && mode != 'd') {
		printf("This value is invalid.\nTry again:\n");
		goto mode_repeat;
	}

	int num = 0, i = 0;
	for (; i < strlen(input_phrase); i++)
	{
		if (isalpha(input_phrase[i]) == 0)
		{
			result[i] = input_phrase[i];
			continue;
		}

		for (int k = 26; k <= 52; k++)
		{
			if (tolower(input_phrase[i]) == caesar_alphabet[k])
			{
				num = k;
				break;
			}
		}
		if (mode == 'i') result[i] = caesar_alphabet[num + step];
		else result[i] = caesar_alphabet[num - step];
	}
	
	result[i] = '\0';
	return;
}

char atbash_cipher(char input_phrase[MAX], char result[MAX])
{
	int num = 0, i = 0;
	for (; i < strlen(input_phrase); i++)
	{
		for (int k = 0; k < 26; k++)
		{
			if (input_phrase[i] == ' ') result[i] = ' ';
			if (isalpha(input_phrase[i]) == 0) result[i] = input_phrase[i];
			num = -1;
			if (tolower(input_phrase[i]) == alphabet[k])
			{
				num = k;
				break;
			}
		}
		if (num != -1) result[i] = alphabet[25 - num];
	}

	result[i] = '\0';
	result;
}

int main()
{
	char input_phrase[MAX], result[RESULT_MAX];
	int type;
	printf("Input the phrase:\n");
input_repeat:
	input(input_phrase);
	if (strlen(input_phrase) == 0)
	{
		printf("You enter empty phrase.\nTry again:\n");
		goto input_repeat;
	}
	printf("\nPick what you want to use for your text:\n\t1 - Morse code\n\t2 - Ceasar cipher.\n\t3 - Atbash cipher.\nEnter the value: ");
	scanf_s("%i", &type);

	if (type == 1)
	{
		morse_code_func(input_phrase, result);
		printf("\nMorze code reult:\n");
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
	
	
	for (int i = 0; i < strlen(result); i++)
	{
		printf("%c", result[i]);
	}

	return 0;
}