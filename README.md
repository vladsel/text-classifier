# Text Classifier application.
(01.05.2021).
N -Grams
An N-gram is an N-character slice of a longer string. N-gram is supplemented with “_” characters to indicate the beginning (end) of a word.

For example, the word “TEXT” includes the following N-grams:
bi-grams: _T, TE, EX, XT, T_
tri-grams: _TE, TEX, EXT, XT_, T_ _
quad-grams: _TEX, TEXT, EXT_, XT_ _, T_ _ _

In the general case, a string of length k, padded with underscores, contains k + 1 bi-grams, k+1 tri-grams, k+1 quad-grams, etc.

Generation of profiles (Profiles) of N-Gram frequencies.
The “Generate Profile” procedure in Fig. 1 reads the input text and counts the number of occurrences of all N-grams. For this you need:

Break the text into words containing only letters. Supplement them with underscores at the beginning and end of words.

For each word, generate N-grams for N from 2 to 5 (including underscores).

Place the N-grams of the word in the table by increasing the number of occurrences.

The table should be sorted in descending order of the number of occurrences.

Classification procedure.
Classification includes the following stages.
1. Training.
Select texts that are examples of categories.
Generate N-grams frequency profiles for each of the texts. It is advisable to save profiles in files.
2. Recognition.
Generate frequency profile of N-grams of recognized text.
Calculate the distance measure between the frequency profile of the recognized text and the frequency profiles of category samples.
Choose the category with the smallest distance value. 

Calculating the Out-Of-Place Measure Between Two Profiles
The value of max depends on the length of the frequency profiles and is selected experimentally. For texts with a length of several kilobytes, its value can be 50-150.
Job assignment.
Design the TextClassifier class. Some basic parameters
//score for no match in frequency map
#define MAX_SCORE 150

#define LOWER_NGRAM_LEN 2
#define UPPER_NGRAM_LEN 5
//Length of recognized categories and text profiles
#define CATEGORY_LEN 1000

Perform recognition on the example of texts in English, Italian, French and Spain.
The results of the work should be presented in the form of a C++ program project, which includes the following files:
1. Class declaration file TextСlassifier.h.
2. TextClassifier.cpp class definition file.
3. Test drive file, for example <Test.cpp>.
Testing should be carried out on texts with a length of 5K to 10K bytes.
