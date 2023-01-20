// project_UP_pract.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

/**
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Lora Hristova
* @idnumber 6MI0600252* @compiler GCC
*
*/


#include <iostream>
#include <fstream>
using namespace std;

const int MAX_LEN_FOR_POLYNOMIAL_RESULT_ENCRYPT = 9;
const int MAX_LEN_FOR_POLYNOMIAL_RESULT_DECRYPT = 11;
const int MAX_LEN_FOR_POLYNOMIAL_BINARY = 8;
const int SIZE_OF_MATRIX = 4;
const int SIZE = 16;
const int MAX_LENGTH_OF_TEXT = 256;
const int SIZE_OF_EXPANDEDKEYS_ARRAY = 176;
const int sizeOfTextPlusTerminatingZero = MAX_LENGTH_OF_TEXT + 1;
const int sizePlusTerminatingZero = SIZE + 1;

//S-Box lookup table
unsigned char s[MAX_LENGTH_OF_TEXT] =
{
	0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
	0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
	0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
	0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
	0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
	0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
	0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
	0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
	0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
	0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
	0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
	0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
	0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
	0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
	0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
	0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

//inversed s-box for decryption
unsigned char inv_s[MAX_LENGTH_OF_TEXT] =
{
	0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
	0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
	0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
	0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
	0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
	0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
	0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
	0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
	0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
	0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
	0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
	0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
	0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
	0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
	0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

//Round constants 
unsigned char rcon[10] =
{
	0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36
};

const unsigned char PREDEFINED_MATRIX[SIZE_OF_MATRIX][SIZE_OF_MATRIX] = { {0x02, 0x03, 0x01, 0x01}, {0x01, 0x02, 0x03, 0x01}, {0x01, 0x01, 0x02, 0x03}, {0x03, 0x01, 0x01, 0x02} };
const unsigned char PREDEFINED_MATRIX_INV[SIZE_OF_MATRIX][SIZE_OF_MATRIX] = { {0x0E, 0x0B, 0x0D, 0x09}, {0x09, 0x0E, 0x0B, 0x0D}, {0x0D, 0x09, 0x0E, 0x0B}, {0X0B, 0X0D, 0X09, 0X0E} };

int strLength(char* str)
{
	int count = 0;

	while (*str != '\0')
	{
		count++;
		str++;
	}

	return count;
}

//Functions from row 41 to row 181 are used in mixColumns functions
int getIndexOfSymbol(char ch)
{
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	else if (ch >= 'A' && ch <= 'F')
		return 10 + (ch - 'A');
	else
		return ch;
}

char getSymbolFromIndex(int ind)
{
	if (ind >= 0 && ind <= 9)
		return ind + '0';

	if (ind >= 10 && ind <= 15)
		return (ind - 10) + 'A';

	return 0;
}

//"from" is in K numeral system. The function converts it to decimal (and the result is stored in an int)
unsigned int fromRandomToDecimal(const unsigned char from[], size_t size, unsigned k)
{
	int mult = 1;
	int result = 0;

	for (int i = size - 1, mult = 1; i >= 0; i--, mult *= k)
		result += (int)from[i] * mult;
	return result;
}

// CHAR
//converts number from decimal to a number in K numeral system. The result is stored in the array "to"
void fromDecimalToRandom(unsigned n, unsigned char to[], size_t size, unsigned k)
{
	for (int arrayIter = size - 1; arrayIter >= 0; arrayIter--)
	{
		int ind = n % k;
		char current = getSymbolFromIndex(ind);
		to[arrayIter] = current;
		n /= k;
	}
}

//converts the number FROM (k numerical system) TO n numerical system. The result is stored in the array "to".
void fromRandomToRandom(const unsigned char from[], size_t fromSize, int k, char unsigned to[], size_t toSize, int n)
{
	unsigned int decimal = fromRandomToDecimal(from, fromSize, k);
	fromDecimalToRandom(decimal, to, toSize, n);
}

//INT
void fromDecimalToRandom(unsigned n, int to[], size_t size, unsigned k)
{
	for (int arrayIter = size - 1; arrayIter >= 0; arrayIter--)
	{
		int ind = n % k;
		to[arrayIter] = ind;
		n /= k;
	}
}

void fromRandomToRandom(const unsigned char from[], size_t fromSize, int k, int to[], size_t toSize, int n)
{
	unsigned int decimal = fromRandomToDecimal(from, fromSize, k);
	fromDecimalToRandom(decimal, to, toSize, n);
}

int power(int number, int k)
{
	int result = 1;

	if (k == 0)
		return 1;

	for (int i = 0; i < k; i++)
		result *= number;

	return result;
}

void checkIfPolynomialIsCorrect(int* polynomial)
{
        if (polynomial[0] == 1)
        {
            polynomial[0] = 0;
            polynomial[4] += 1;
            polynomial[5] += 1;
            polynomial[7] += 1;
            polynomial[8] += 1;
        }

    for (int i = 1; i <= MAX_LEN_FOR_POLYNOMIAL_RESULT_ENCRYPT; i++)
    {
        if (polynomial[i] == 0)
            continue;

        if (polynomial[i] % 2 == 0)
            polynomial[i] = 0;

        else if (polynomial[i] % 2 == 1)
            polynomial[i] = 1;

    }
}

void checkIfPolynomialIsCorrectDecryption(int* polynomial)
{
	if (polynomial[0] == 1)
	{
		polynomial[0] = 0;
		polynomial[4] += 1;
		polynomial[5] += 1;
		polynomial[7] += 1;
		polynomial[10] += 1;
	}

	if (polynomial[1] == 1)
	{
		polynomial[1] = 0;
		polynomial[5] += 1;
		polynomial[6] += 1;
		polynomial[8] += 1;
		polynomial[9] += 1;
	}

	if (polynomial[2] == 1)
	{
		polynomial[2] = 0;
		polynomial[6] += 1;
		polynomial[7] += 1;
		polynomial[9] += 1;
		polynomial[10] += 1;
	}

	for (int i = 3; i < MAX_LEN_FOR_POLYNOMIAL_RESULT_DECRYPT; i++)
	{
		if (polynomial[i] == 0)
			continue;

		if (polynomial[i] % 2 == 0)
			polynomial[i] = 0;

		else if (polynomial[i] % 2 == 1)
			polynomial[i] = 1;

	}

}

void multiplyTwoPolynomials(int A[], int B[], int result[])
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_LEN_FOR_POLYNOMIAL_BINARY; j++)
		{
			result[i + j] += A[i] * B[j];
		}
	}

	checkIfPolynomialIsCorrect(result);
}

void multuplyTwoPolynomialForDecryption(int A[], int B[], int result[])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < MAX_LEN_FOR_POLYNOMIAL_BINARY; j++)
		{
			result[i + j] += A[i] * B[j];
		}
	}

	checkIfPolynomialIsCorrectDecryption(result);

}

void fromArrayToVariable(int* array, int& variable, size_t arraySize)
{
	for (int i = arraySize - 1; i >= 0; i--)
	{
		variable += array[i] * power(2, arraySize - 1 - i);
	}
}

void transferTextInMatrix(unsigned char* plainText, unsigned char matrix[][SIZE_OF_MATRIX])
{
	int index = 0;
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			matrix[j][i] = plainText[index++];
		}
	}
}

void printMatrix(unsigned char matrix[][SIZE_OF_MATRIX])
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			cout << "[" << getIndexOfSymbol(matrix[i][j]) << "]";
		}
		cout << endl;
	}
}

void keyExpansion(char* key, int index)
{
		char tmp = key[0];

		key[0] = s[key[1]];
		key[1] = s[key[2]];
		key[2] = s[key[3]];
		key[3] = s[tmp];

		key[0] ^= rcon[index];
}

void keyExpansionRounds(char* key, unsigned char* expandedKeys)
{
	int indexOfRCon = 0;
	char tmpLastWord[4];
	char tmpFisrtWord[4];
	char tmpSecondWord[4];
	char tmpThirdWord[4];
	char tmpFourthWord[4];

	for (int i = 0; i < SIZE; i++)
	{
		expandedKeys[i] = key[i];
	}

	for (int i = 1; i <= 10; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmpLastWord[j] = expandedKeys[i * SIZE - 4 + j];
			tmpFisrtWord[j] = expandedKeys[(i - 1) * SIZE + j];
			tmpSecondWord[j] = expandedKeys[(i - 1) * SIZE + 4 + j];
			tmpThirdWord[j] = expandedKeys[i * SIZE - 8 + j];
			tmpFourthWord[j] = tmpLastWord[j];
		}

		keyExpansion(tmpLastWord, indexOfRCon++);
		
		for (int k = 0; k < 4; k++)
		{
			expandedKeys[i * SIZE + k] = tmpFisrtWord[k] ^ tmpLastWord[k];
			expandedKeys[i * SIZE + 4 + k] = tmpSecondWord[k] ^ expandedKeys[i * SIZE + k];
			expandedKeys[i * SIZE + 8 + k] = tmpThirdWord[k] ^ expandedKeys[i * SIZE + 4 + k];
			expandedKeys[i * SIZE + 12 + k] = tmpFourthWord[k] ^ expandedKeys[i * SIZE + 8 + k];
		}
	}
}

//Substitute bytes from S-Box lookup table
void subBytes(unsigned char textToEncrypt[][SIZE_OF_MATRIX])
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
			textToEncrypt[i][j] = s[textToEncrypt[i][j]];
	}
		
}

//Decryption
void invSubBytes(unsigned char textToEncrypt[][SIZE_OF_MATRIX])
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
			textToEncrypt[i][j] = inv_s[textToEncrypt[i][j]];
	}

}

//Shifting rows: Row 1 - no shifting, Row 2 - 1 byte left shift, Row 3 - 2 byte left shift, Row 4 - 3 byte left shift
void shiftRows(unsigned char textToEncrypt[][SIZE_OF_MATRIX])
{
	char temp = textToEncrypt[1][0];
	textToEncrypt[1][0] = textToEncrypt[1][1];
	textToEncrypt[1][1] = textToEncrypt[1][2];
	textToEncrypt[1][2] = textToEncrypt[1][3];
	textToEncrypt[1][3] = temp;

	temp = textToEncrypt[2][0];
	textToEncrypt[2][0] = textToEncrypt[2][2];
	textToEncrypt[2][2] = temp;
	temp = textToEncrypt[2][1];
	textToEncrypt[2][1] = textToEncrypt[2][3];
	textToEncrypt[2][3] = temp;

	temp = textToEncrypt[3][3];
	textToEncrypt[3][3] = textToEncrypt[3][2];
	textToEncrypt[3][2] = textToEncrypt[3][1];
	textToEncrypt[3][1] = textToEncrypt[3][0];
	textToEncrypt[3][0] = temp;
}

//Decryption
void invShiftRows(unsigned char textToEncrypt[][SIZE_OF_MATRIX])
{
	char temp = textToEncrypt[1][3];
	textToEncrypt[1][3] = textToEncrypt[1][2];
	textToEncrypt[1][2] = textToEncrypt[1][1];
	textToEncrypt[1][1] = textToEncrypt[1][0];
	textToEncrypt[1][0] = temp;


	temp = textToEncrypt[2][0];
	textToEncrypt[2][0] = textToEncrypt[2][2];
	textToEncrypt[2][2] = temp;
	temp = textToEncrypt[2][1];
	textToEncrypt[2][1] = textToEncrypt[2][3];
	textToEncrypt[2][3] = temp;

	temp = textToEncrypt[3][0];
	textToEncrypt[3][0] = textToEncrypt[3][1];
	textToEncrypt[3][1] = textToEncrypt[3][2];
	textToEncrypt[3][2] = textToEncrypt[3][3];
	textToEncrypt[3][3] = temp;
}

//Encryption
void mixColumns(unsigned char matrix[][SIZE_OF_MATRIX])
{
	unsigned char result[SIZE_OF_MATRIX][SIZE_OF_MATRIX] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	unsigned char temp[1];
	unsigned char tempSecond[1];
	int polynomial[2] = { 0, 0 };
	int secondPolynomial[MAX_LEN_FOR_POLYNOMIAL_BINARY] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			for (int k = 0; k < SIZE_OF_MATRIX; k++)
			{
				int resultOf[MAX_LEN_FOR_POLYNOMIAL_RESULT_ENCRYPT] = { 0 };

				int variable = 0;
				temp[0] = PREDEFINED_MATRIX[i][k];
				tempSecond[0] = matrix[k][j];
				fromRandomToRandom(temp, 1, SIZE, polynomial, 2, 2);
				fromRandomToRandom(tempSecond, 1, SIZE, secondPolynomial, 8, 2);
				multiplyTwoPolynomials(polynomial, secondPolynomial, resultOf);
				fromArrayToVariable(resultOf, variable, MAX_LEN_FOR_POLYNOMIAL_RESULT_ENCRYPT);
				result[i][j] ^= variable;
			}
		}
	}

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			matrix[i][j] = result[i][j];
		}
	}
}

//Decryption
void invMixColumns(unsigned char matrix[][SIZE_OF_MATRIX])
{	
	unsigned char result[SIZE_OF_MATRIX][SIZE_OF_MATRIX] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} };
	unsigned char temp[1];
	unsigned char tempSecond[1];
	int polynomial[4] = { 0, 0, 0, 0};
	int secondPolynomial[MAX_LEN_FOR_POLYNOMIAL_BINARY] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			for (int k = 0; k < SIZE_OF_MATRIX; k++)
			{
				int resultOf[MAX_LEN_FOR_POLYNOMIAL_RESULT_DECRYPT] = { 0 };

				int variable = 0;
				temp[0] = PREDEFINED_MATRIX_INV[i][k];
				tempSecond[0] = matrix[k][j];
				fromRandomToRandom(temp, 1, SIZE, polynomial, 4, 2);
				fromRandomToRandom(tempSecond, 1, SIZE, secondPolynomial, 8, 2);
				multuplyTwoPolynomialForDecryption(polynomial, secondPolynomial, resultOf);
				fromArrayToVariable(resultOf, variable, MAX_LEN_FOR_POLYNOMIAL_RESULT_DECRYPT);
				result[i][j] ^= variable;
			}
		}
	}

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			matrix[i][j] = result[i][j];
		}
	}
}

//Encryption
void addRoundKey(unsigned char result[][SIZE_OF_MATRIX], unsigned char* expandedKeys, unsigned int round)
{
	int e = 0;

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++, e++)
		{
			result[j][i] ^= expandedKeys[SIZE * round + e];
		}
	} 
}

//Decryption
void invAddRoundKey(unsigned char result[][SIZE_OF_MATRIX], unsigned char* expandedKeys, unsigned int round)
{
	int e = 0;

	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++, e++)
		{
			result[j][i] ^= expandedKeys[SIZE_OF_EXPANDEDKEYS_ARRAY - SIZE * (round + 1) + e];
		}
	}
}

void moveToFront(int size, char* plainText)
{
	for (int i = SIZE; i < size; i++)
	{
		plainText[i - SIZE] = plainText[i];
	}
}

void convertMatrixToArray(unsigned char matrix[][SIZE_OF_MATRIX], char* encryptedMessage, int& index)
{
	for (int i = 0; i < SIZE_OF_MATRIX; i++)
	{
		for (int j = 0; j < SIZE_OF_MATRIX; j++)
		{
			encryptedMessage[index++] = matrix[j][i];
		}
	}
	encryptedMessage[index] = '\0';
}

void encrypt(char* encryptedMessage)
{
	char plainText[sizeOfTextPlusTerminatingZero];
	char keyForPlainText[sizePlusTerminatingZero];
	fstream file("text_to_encrypt.txt", fstream::in);

	if (file.is_open())
	{

		file.getline(plainText, sizeOfTextPlusTerminatingZero);
		file.getline(keyForPlainText, sizePlusTerminatingZero);
		int lengthOfPlainText = strLength(plainText);
		int leftWhenDividingBy16 = lengthOfPlainText % SIZE;
		int zeroesToAdd = SIZE - leftWhenDividingBy16;
		int newLengthOfPlainText = lengthOfPlainText + zeroesToAdd;
		int indexForEncryptedMessage = 0;

		for (int i = lengthOfPlainText; i < newLengthOfPlainText; i++)
		{
			plainText[lengthOfPlainText] = 0;
		}

		int index = 0;
		int howManyMatrixes = newLengthOfPlainText / SIZE;
		while (index < howManyMatrixes)
		{
			unsigned char matrix[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
			unsigned char arrayToWorkWith[SIZE];
			unsigned char expandedKeys[SIZE_OF_EXPANDEDKEYS_ARRAY];
			int round = 0;

			for (int i = 0; i < SIZE; i++)
			{
				arrayToWorkWith[i] = plainText[i];
			}

			transferTextInMatrix(arrayToWorkWith, matrix);
			keyExpansionRounds(keyForPlainText, expandedKeys);
			addRoundKey(matrix, expandedKeys, round++);

			//1 TO 9 ROUND
			for (; round <= 9; round++)
			{
				subBytes(matrix);
				shiftRows(matrix);
				mixColumns(matrix);
				addRoundKey(matrix, expandedKeys, round);
			}

			//last round
			subBytes(matrix);
			shiftRows(matrix);
			addRoundKey(matrix, expandedKeys, round);

			convertMatrixToArray(matrix, encryptedMessage, indexForEncryptedMessage);
			moveToFront(newLengthOfPlainText, plainText);
			index++;
		}
		file.close();
	}

	else
	{
		cout << "File cannot be found!" << endl;
		exit(1);
	}

	fstream descrypted("encrypted_text.txt", fstream::out);
	descrypted << encryptedMessage << "\n";
	descrypted << keyForPlainText;
	descrypted.close();
}

void decrypt(char* decryptedMessage)
{
	char cypherText[sizeOfTextPlusTerminatingZero];
	char keyForCypherText[sizePlusTerminatingZero];
	fstream file("text_to_decrypt.txt", fstream::in);

	if (file.is_open())
	{

		file.getline(cypherText, sizeOfTextPlusTerminatingZero);
		file.getline(keyForCypherText, sizePlusTerminatingZero);
		int lengthOfCypherText = strLength(cypherText);
		int leftWhenDividingBy16 = lengthOfCypherText % SIZE;
		int zeroesToAdd = SIZE - leftWhenDividingBy16;
		int newLengthOfCypherText = lengthOfCypherText + zeroesToAdd;
		int indexForDecryptedMessage = 0;

		for (int i = lengthOfCypherText; i < newLengthOfCypherText; i++)
		{
			cypherText[lengthOfCypherText] = 0;
		}

		int index = 0;
		int howManyMatrixes = newLengthOfCypherText / SIZE;
		while (index < howManyMatrixes)
		{
			unsigned char matrix[SIZE_OF_MATRIX][SIZE_OF_MATRIX];
			unsigned char arrayToWorkWith[SIZE];
			unsigned char expandedKeys[SIZE_OF_EXPANDEDKEYS_ARRAY];
			int round = 0;

			for (int i = 0; i < SIZE; i++)
			{
				arrayToWorkWith[i] = cypherText[i];
			}

			transferTextInMatrix(arrayToWorkWith, matrix);
			keyExpansionRounds(keyForCypherText, expandedKeys);
			invAddRoundKey(matrix, expandedKeys, round++);

			//Round from 1 to 9
			for (; round <= 9; round++)
			{
				invShiftRows(matrix);
				invSubBytes(matrix);
				invAddRoundKey(matrix, expandedKeys, round);
				invMixColumns(matrix);
			}

			//last round
			invShiftRows(matrix);
			invSubBytes(matrix);
			invAddRoundKey(matrix, expandedKeys, round);

			convertMatrixToArray(matrix, decryptedMessage, indexForDecryptedMessage);
			moveToFront(newLengthOfCypherText, cypherText);
			index++;
		}
		file.close();
	}

	else
	{
		cout << "File cannot be found!" << endl;
		exit(1);
	}

	fstream decrypted("decrypted_text.txt", fstream::out);
	decrypted << decryptedMessage << "\n";
	decrypted << keyForCypherText;
	decrypted.close();
}


int main()
{
	cout << "=============================" << endl;
	cout << " 128-bit AES Encryption Tool   " << endl;
	cout << "=============================" << endl;

	int n;
	cout << "Choose encryption or decryption: Choose 1 or 2" << endl;
	cin >> n;

	if (n != 1 && n != 2)
	{
		cout << "Invalid number! Try again!";
		return 0;
	}

	else if (n == 1)
	{
		char encryptedMessage[sizeOfTextPlusTerminatingZero];
		encrypt(encryptedMessage);
		cout << encryptedMessage;
	}

	else if (n == 2)
	{
		char decryptedMessage[sizeOfTextPlusTerminatingZero];
		decrypt(decryptedMessage);
		cout << decryptedMessage;
	}

}

