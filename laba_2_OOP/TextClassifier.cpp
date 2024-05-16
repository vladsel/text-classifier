#include "TextClassifier.h"

void TextClassifier::GenerateProfilebyFile() {
	std::ifstream in_f;
	in_f.open(category_text + ".txt", std::ifstream::in);
	if (!in_f.is_open()) {
		std::cerr << "file error with category " << category_text << " GenerateProfilebyFile()" << std::endl;
		return;
	}
	std::map <std::string, unsigned int> gram_dictionary;
	std::string str;
	std::string letters;
	std::string temp;
	while (1) {
		in_f >> str;
		if (in_f.eof())
			break;

		letters = "";
		std::regex regular("[\\W\\_\\d]");
		for (const auto &iter : std::regex_replace(str, regular, ""))
			letters.append(1, iter);
		std::transform(letters.begin(), letters.end(), letters.begin(), (int (*)(int))::toupper);

		if (!letters.empty()) {
			letters = "_" + letters + "_";
			size_t letters_len = letters.size();
			for (size_t n_gram = LOWER_NGRAM_LEN; n_gram <= UPPER_NGRAM_LEN; n_gram++)
				for (size_t i = n_gram; i <= letters_len + (n_gram - LOWER_NGRAM_LEN); i++) {
					temp = letters.substr(i - n_gram, n_gram);
					if (i > letters_len)
						temp.append(i - letters_len, '_');
					if (CATEGORY_LEN > gram_dictionary.size() && gram_dictionary.count(temp) == 0)
						gram_dictionary.emplace(temp, 1);
					else if (gram_dictionary.count(temp) != 0)
						if (gram_dictionary.find(temp) != gram_dictionary.end())
							gram_dictionary.find(temp)->second++;
				}
		}
	}
	in_f.close();

	//gram_vector.reserve(gram_dictionary.size());
	//using it_map = std::map <std::string, unsigned int>::iterator;
	//using mv = std::move_iterator <it_map>;
	//gram_vector.insert(gram_vector.end(), mv(gram_dictionary.begin()), mv(gram_dictionary.end()));

	gram_vector.reserve(gram_dictionary.size());
	for (auto &iter : gram_dictionary) 
		gram_vector.emplace_back(std::move(iter));
	gram_dictionary.clear();

	std::sort(gram_vector.begin(), gram_vector.end(), 
			  [](std::pair<std::string, unsigned int> a, std::pair<std::string, unsigned int> b) {
				  return a.second > b.second;
			  });
}

void TextClassifier::OutputFrequencyProfileToFile() {
	if (!gram_vector.empty()) {
		std::ofstream out_f;
		out_f.open(category_text + "_frequency.txt", std::ofstream::out);
		if (!out_f.is_open()) {
			std::cerr << "file error with category " << category_text << " OutputFrequencyProfileToFile()" << std::endl;
			return;
		}
		out_f << "<==========================|" << category_text << "|==========================>\n\n";
		for (const auto &iter : gram_vector)
		out_f << "grams: [" << iter.first.size() << "]\t" << iter.first << "\t<=>\t" << iter.second << "\t(freq)\n";
		out_f.close();
	}
	else {
		std::cout << "\nyou need to generate profile by file using method GenerateProfilebyFile() or your file is empty,"
			<< " your category is "<< category_text << std::endl;
		return;
	}
}

size_t TextClassifier::MakeDistanceMeasureBetweenProfiles(const TextClassifier &TC) {
	if (!gram_vector.empty() && !TC.gram_vector.empty()) {
		size_t distance = 0;
		bool flag = false;
		for (size_t i = 0; i < gram_vector.size(); i++) {
			flag = false;
			for (size_t j = 0; j < TC.gram_vector.size(); j++) {
				if (gram_vector.at(i).first == TC.gram_vector.at(j).first && i >= j) {
					distance += i - j;
					flag = true;
					break;
				}
				else if (gram_vector.at(i).first == TC.gram_vector.at(j).first && i < j) {
					distance += j - i;
					flag = true;
					break;
				}
			}
			if (flag == false)
				distance += MAX_SCORE;
		}
		return distance;
	}
	else {
		std::cout << "\nyou need to generate profile by file using method GenerateProfilebyFile() or your file is empty,"
			<< " your category is " << category_text << std::endl;
		return -1;
	}
}

void TextClassifier::SetCategory(std::string category_text) {
	this->category_text = category_text;
	if (!gram_vector.empty())
		gram_vector.clear();
}

std::string TextClassifier::GetCategory() {
	return category_text;
}

std::vector <TextClassifier> Classification() {
	std::vector <TextClassifier> lang_vector(4);
	for (int i = 0; i < lang_vector.size(); i++) {
		switch (i) {
		case 0:
			lang_vector[i].SetCategory("ENGLISH");
			break;
		case 1:
			lang_vector[i].SetCategory("SPANISH");
			break;
		case 2:
			lang_vector[i].SetCategory("ITALIAN");
			break;
		case 3:
			lang_vector[i].SetCategory("FRENCH");
			break;
		}
	}
	for (auto &iter : lang_vector) {
		std::cout << "frequency profile: " << iter.GetCategory() << " is generating and outputing to the file\n";
		iter.GenerateProfilebyFile();
		iter.OutputFrequencyProfileToFile();
	}
	return std::vector <TextClassifier> (lang_vector);
}

void Recognition(std::vector <TextClassifier> lang_vector) {
	TextClassifier test("TEST");
	std::cout << "\ntest frequency profile: " << test.GetCategory() << " is generating and outputing to the file\n";
	test.GenerateProfilebyFile();
	test.OutputFrequencyProfileToFile();
	std::cout << "calculating the distance measure between profiles\n\n";
	for (auto &iter : lang_vector)
		std::cout << test.GetCategory() << " and " << iter.GetCategory()
		<< " measure: " << test.MakeDistanceMeasureBetweenProfiles(iter) << "\n";
	std::cout << "\n\n";
}
