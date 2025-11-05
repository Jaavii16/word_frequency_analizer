#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;



//suitable data structure for the three dictionaries
struct Dictionaries {
	pair<unordered_map<string, int>, int> dict1;//documents 1-100, num of words
	pair<unordered_map<string, int>, int> dict2;//documents 1-1000, num of words
	pair<unordered_map<string, int>, int> dict3;//documents 1-7600, num of words
};

//global variable to store dictionaries
Dictionaries dictionaries;


// ANSI escape codes for colors
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define RED "\033[31m"
#define BOLD "\033[1m"

//menu for the application
void showMenu() {
	cout << CYAN << BOLD << "==========================================" << RESET << endl;
	cout << YELLOW << "         Word Occurrence Application      " << RESET << endl;
	cout << CYAN << BOLD << "==========================================" << RESET << endl;
	cout << GREEN << "1. Load Dictionaries" << RESET << endl;
	cout << GREEN << "2. Search a Word" << RESET << endl;
	cout << GREEN << "3. Generate HTML Output" << RESET << endl;
	cout << RED << "4. Exit" << RESET << endl;
	cout << CYAN << BOLD << "------------------------------------------" << RESET << endl;
	cout << YELLOW << "Enter your choice: " << RESET;
}


// Function to convert a string to lowercase
string toLowerCase(const string& str) {
	string lowerStr = str;
	transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
		[](unsigned char c) { return tolower(c); });
	return lowerStr;
}


//FUNCTIONS FOR 1.LOADING THE DATA FROM THE FILES INTO THE DICTIONARIES

//function for reading the words from the file
unordered_map<string, int> read_from_file(const string& filePath) {
	unordered_map<string, int> occurrence;
	ifstream file(filePath);
	if (!file.is_open()) {
		cout << "Error opening file: " << filePath << endl;
		return occurrence;
	}
	else cout << "Reading file: " << filePath << endl;

	string word;
	while (file >> word) {
		word = toLowerCase(word);  //convert word to lowercase
		occurrence[word]++;//this find the word we are reading in the dictionary and increments the count for the ocurrence
	}

	file.close();
	return occurrence;
}


void loadDictionaries() {
	std::cout << "Loading dictionaries from multiple files...\n";

	
	// Helper function to load a range of files into a dictionary
	auto loadFilesToDictionary = [](int start, int end, const string& folderPath) {
		unordered_map<string, int> dictionary;
		int totalWords = 0;
		for (int i = start; i <= end; ++i) {
			// Construct file name dynamically
			string fileName = folderPath + "/" + to_string(i) + ".txt";
			unordered_map<string, int> fileData = read_from_file(fileName);

			// Merge file data into the main dictionary
			for (const auto& p : fileData) {
				dictionary[p.first] += p.second;
				totalWords += p.second;
			}
		}
		cout << "Loaded in total: " << totalWords << " words" << endl;
		return make_pair(dictionary, totalWords);
	};

	// Load dictionaries from their respective file ranges using corrected folder paths
	string zipPath = "C:/Users/Usuario/Documents/Erasmus/PT/ptdata";
	// Load Dictionary 1
	pair<unordered_map<string, int>, int> result1 = loadFilesToDictionary(1, 100, zipPath);
	dictionaries.dict1.first = result1.first;
	dictionaries.dict1.second = result1.second;

	// Load Dictionary 2
	std::pair<unordered_map<string, int>, int> result2 = loadFilesToDictionary(1, 1000, zipPath);
	dictionaries.dict2.first = result2.first;
	dictionaries.dict2.second = result2.second;

	// Load Dictionary 3
	std::pair<unordered_map<string, int>, int> result3 = loadFilesToDictionary(1, 7600, zipPath);
	dictionaries.dict3.first = result3.first;
	dictionaries.dict3.second = result3.second;
	
	// Debugging output
	cout << "Total words in Dictionary 1: " << dictionaries.dict1.second << endl;
	cout << "Total words in Dictionary 2: " << dictionaries.dict2.second << endl;
	cout << "Total words in Dictionary 3: " << dictionaries.dict3.second << endl;

	std::cout << "Dictionaries loaded successfully.\n";
}


//FUNCTIONS FOR 2.SEARCHING A WORD IN DICTIONARIES


//searching specific words
bool searchWord(unordered_map<string, int>& dict, string& word) {
	return dict.find(word) != dict.end();//returns true if the word is found in the dictionary and false if not
}


//function for searching a word in the dictionaries
void searchWordInDictionaries() {
	cout << "Enter the word to search: ";
	string word;
	cin >> word;

	word = toLowerCase(word);  //convert input to lowercase

	bool found1 = searchWord(dictionaries.dict1.first, word);
	bool found2 = searchWord(dictionaries.dict2.first, word);
	bool found3 = searchWord(dictionaries.dict3.first, word);

	if (found1) std::cout << "Word found in Dictionary 1.\n";
	if (found2) std::cout << "Word found in Dictionary 2.\n";
	if (found3) std::cout << "Word found in Dictionary 3.\n";

	if (!found1 && !found2 && !found3) {
		cout << "Word not found in any dictionary.\n";
	}
}


//FUNCTIONS FOR 3.GENERATING HTML

//this function will sort the words in the dictionary by occurrence and will return a vector of the sorted words
vector<pair<string, int>> sortWordsByOccurrence(const unordered_map<string, int>& dictionary) {
	vector<pair<string, int>> sortedWords(dictionary.begin(), dictionary.end());//transform the dictionary values into pairs for storing them in a vector
	sort(sortedWords.begin(), sortedWords.end(), [](const auto& a, const auto& b) {
		return b.second < a.second; //sorts the vector descending by count, evaluating the second value which is the occurrence
		});

	return sortedWords;
}

//preparing words output in HTML
void prepareOutput(const string& fileName, const vector<pair<string, int>>& sortedWords, int totalWords) {
	ofstream output(fileName);
	if (!output.is_open()) {
		cout << "Error creating HTML file: " << fileName << endl;
		return;
	}

	output << "<html><head><title>Word Ocurrence</title></head><body>";
	output << "<h1>Word Ocurrence Analysis</h1><table border='1'>";
	output << "<tr><th>Word</th><th>Absolute Occurrence</th><th>Relative Occurrence (%)</th></tr>";

	for (const auto& word : sortedWords) {
		double relativeFreq = (static_cast<double>(word.second) / totalWords) * 100.0;//calculating the relative frequency
		output << "<tr><td>" << word.first << "</td><td>" << word.second << "</td><td>" << relativeFreq << "</td></tr>";
	}

	output << "</table></body></html>";
	output.close();
}

//function to generate HTML for dictionaries
void generateHTMLForDictionaries() {
	cout << "Generating HTML reports for dictionaries...\n";

	auto sortedDict1 = sortWordsByOccurrence(dictionaries.dict1.first);
	auto sortedDict2 = sortWordsByOccurrence(dictionaries.dict2.first);
	auto sortedDict3 = sortWordsByOccurrence(dictionaries.dict3.first);

	prepareOutput("dictionary1.html", sortedDict1, dictionaries.dict1.second);
	prepareOutput("dictionary2.html", sortedDict2, dictionaries.dict2.second);
	prepareOutput("dictionary3.html", sortedDict3, dictionaries.dict3.second);

	cout << "HTML reports generated.\n";
}

//FUNCTION FOR 4.EXIT

//function to exit the program
void exitProgram() {
	cout << "Exiting program. Goodbye!\n";
}


//MAIN CODE FOR THE PROGRAM

int main() {

	int choice = 0;
	bool runningProgramm = true;
	bool loaded = false;
	while (runningProgramm) {
		showMenu();
		if (!(cin >> choice)) { //check if input is invalid
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear(); //clear the error state
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard invalid input in the buffer
			continue; //skip this iteration and go to the beginning of the loop
		}
		
		if (choice < 1 || choice >4) {
			cout << "Please introduce a valid option" << endl;
			continue;
		}

		switch (choice) {
		case 1:
			if (!loaded) {
				loadDictionaries();
				loaded = true;
			}
			else cout << "Dictionaries already loaded" << endl;
			break;
		case 2:
			if (loaded) {
				searchWordInDictionaries();
			}
			else cout << "The dictionaries are not loaded yet" << endl;
			break;
		case 3:
			if (loaded) {
				generateHTMLForDictionaries();
			}
			else cout << "The dictionaries are not loaded yet" << endl;
			break;
		case 4:
			exitProgram();
			runningProgramm = false; //exit the loop for ending the application
			break;
		}
		cout << endl;
	}

	return 0;
}