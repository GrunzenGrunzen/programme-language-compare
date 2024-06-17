#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_set>

using namespace std::chrono;
using namespace std;
class Bingo {
public:
	int* bingoList;
	int length = 5;
	int size = 25;

	void generateBingoList() {
		int* bingoTemp = new int[size];
		for (int i = 0; i < size; i++) {
			bingoTemp[i] = i + 1;
		}
		random_shuffle(&bingoTemp[0], &bingoTemp[size]);
		bingoList = bingoTemp;
	}


	void printBingo() {
		for (size_t i = 0; i < size; i++)
		{
			cout << (bingoList[i] == -1 ? "X" : to_string(bingoList[i])) << "\t";
			if ((i + 1) % length == 0) cout << endl;
		}
		cout << endl;
	}

	void bingoNumber(int number) {
		for (size_t i = 0; i < size; i++) {
			if (bingoList[i] == number) {
				bingoList[i] = -1;
				break;
			}
		}
	}

	bool isBingo() {
		bool leftHypBingo = true;
		bool rightHypBingo = true;
		for (size_t i = 0; i < length; i++) {
			bool rowBingo = true;
			bool colBingo = true;
			for (size_t j = 0; j < length; j++) {
				//row
				if (bingoList[5 * i + j] != -1) {
					rowBingo = false;
				}

				//col
				if (bingoList[i + j * 5] != -1) {
					colBingo = false;
				}
			}
			//left hyp
			if (bingoList[i * 5 + i] != -1) {
				leftHypBingo = false;
			}

			//right hyp
			if (bingoList[(i + 1) * 4] != -1) {
				rightHypBingo = false;
			}

			if (rowBingo || colBingo) {
				return true;
			}
		}
		return leftHypBingo || rightHypBingo;
	}


	Bingo(int length = 5) : size(length* length) {
		generateBingoList();
	}


};

class RepeatInputException : public std::exception {};
int getUserInput(int size, unordered_set<int>& inputRecord) {
	try
	{
		string inputString = "0";
		cout << "Input a number: ";
		cin >> inputString;
		int number = stoi(inputString);

		auto start = high_resolution_clock::now();
		if (number < 0
			|| number > size)
			throw std::exception();
		else if (inputRecord.count(number)) {
			throw RepeatInputException();
		}
		//insert number to inputRecord
		inputRecord.insert(number);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		cout << "Time taken by Input function: "
			<< duration.count() << " microseconds" << endl;
		return number;
	}
	catch (RepeatInputException) {
		cout << "Repeated number, please input again" << endl;
		return getUserInput(size, inputRecord);
	}
	catch (const std::exception&)
	{
		cout << "Input error, please input again" << endl;
		return getUserInput(size, inputRecord);
	}
}

int main()
{
	srand(time(NULL));
	cout << "Start the bingo game" << endl << "You can enter 0 to end the game" << endl;
	//define bingo class
	Bingo bingo = Bingo();
	unordered_set<int> inputRecord;

	int userInput;
	while (true)
	{
		bingo.printBingo();
		userInput = getUserInput(bingo.size, inputRecord);
		auto start = high_resolution_clock::now();

		if (userInput == 0) {
			cout << "Game is end" << endl;
			break;
		}

		bingo.bingoNumber(userInput);
		if (bingo.isBingo()) {
			cout << "You win" << endl;
			break;
		}
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<microseconds>(stop - start);

		cout << "Time taken by function: "
			<< duration.count() << " microseconds" << endl;
	}
	return 0;
}
