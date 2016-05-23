#include <iostream>
#include <stdexcept>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <set>
#include <map>

const char DELIMITERS[] = " \t\n.,;";
const std::set<char> DELIMITER_SET(std::begin(DELIMITERS), std::end(DELIMITERS));

bool is_word_char(char c)
{
    return DELIMITER_SET.find(c) == DELIMITER_SET.end();
}

int main(int argc, char **argv)
{
    if (argc < 2)
        throw std::invalid_argument("expecting at least 1 command line parameter");
    const auto filename = argv[1];
    std::ifstream file(filename);
    if (!file)
        throw std::invalid_argument("could not open file");
    file >> std::noskipws;
    std::istream_iterator<char> chars(file);
    const std::istream_iterator<char> END_OF_FILE;
    std::map<std::string, size_t> words;
    while (true)
    {
        chars = std::find_if(chars, END_OF_FILE, &is_word_char);
        if (chars == END_OF_FILE)
            break;
        std::string word;
        do
        {
            word.push_back(*chars);
        } while (++chars != END_OF_FILE && is_word_char(*chars));
        auto word_it = words.insert(std::make_pair(word, 0)).first;
        (*word_it).second++;
    }
    for (auto &&word: words)
    {
        std::cout << word.first << " - " << word.second << std::endl;
    }
    return 0;
}
