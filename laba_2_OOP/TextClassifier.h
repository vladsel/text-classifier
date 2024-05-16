#ifndef _TEXT_CLASSIFIER_H_
#define _TEXT_CLASSIFIER_H_

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

//score for no match in frequency map
#define MAX_SCORE 150
#define LOWER_NGRAM_LEN	2
#define UPPER_NGRAM_LEN	5
//Length of profiles of recognized categories and texts
#define CATEGORY_LEN 1000

class TextClassifier {
public:
	TextClassifier() : category_text("empty") {}
	TextClassifier(const std::string _category_text) : category_text(_category_text) {}
	~TextClassifier() { gram_vector.clear(); }
	void GenerateProfilebyFile();
	void OutputFrequencyProfileToFile();
	size_t MakeDistanceMeasureBetweenProfiles(const TextClassifier &TC);
	void SetCategory(std::string category);
	std::string GetCategory();
private:
	std::vector <std::pair <std::string, unsigned int>> gram_vector;
	std::string category_text;
};

std::vector <TextClassifier> Classification();
void Recognition(std::vector <TextClassifier> lang_vector);

#endif // _TEXT_CLASSIFIER_H_
