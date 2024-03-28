#include<iostream> // std::cout
#include<vector>   // std::vector
#include<string>   // std::string
#include<fstream>  // std::ifstream
#include<random>   // random things
#include<fstream>  // std::ofstream

auto has(std::string s, char c) -> bool
{
    for (auto x : s)
    {
        if (x == c) { return true; }
    }
    return false;
}

auto not_in(std::vector<char>& chars, char c, int _i)
{
    for (int i = 0; i < chars.size(); i++)
    {
        if (chars[i] == c && i != _i)
        {
            return false;
        }
    }
    return true;
}

auto find_not_taken(std::vector<char>& chars, int x)
{
    for (int i = 0; i < chars.size(); i++)
    {
        if (chars[i] == '_' && i != x && not_in(chars, chars[i], i))
        {
            return i;
        }
    }
    return -1;
}

auto compare(std::string maybe, std::string to_compare, std::vector<std::string>& vec, std::vector<char>& chars)
{
    const std::string grey_square{ "\xe2\xac\x9b" };
    const std::string green_square{ "\xf0\x9f\x9f\xa9" };
    const std::string yellow_square{ "\xf0\x9f\x9f\xa8" };
    std::string result{};
    for (int i = 0; i < to_compare.size() && i < maybe.size(); i++)
    {
        if (maybe[i] == to_compare[i])
        {
            /*
            if(chars[i] != '_')
            {
            if(find_not_taken(chars, i) != -1)
            {
                chars[find_not_taken(chars, i)] = maybe[i];
            }
            }
            */
            chars.push_back(maybe[i]);
            vec.push_back(green_square);
        }
        else if (has(to_compare, maybe[i]))
        {
            chars.push_back(maybe[i]);
            vec.push_back(yellow_square);
        }
        else
        {
            vec.push_back(grey_square);
        }
    }
}

auto get_all_that_have(std::vector<std::string> current, char letter)
{
    std::vector<std::string> result{};
    for (auto x : current)
    {
        if (x.find(letter) == 0 || x.find(letter) == 1 || x.find(letter) == 2 || x.find(letter) == 3 || x.find(letter) == 4)
        {
            result.push_back(x);
        }
    }
    return result;
}

auto find_in_dictionary(std::vector<std::string>& words, std::vector<char>& letters)
{
    std::vector<std::string> current = words;
    for (int i = 0; i < letters.size(); i++)
    {
        if (letters[i] == '_')
        {
            // we do nothing
        }
        else
        {
            current = get_all_that_have(current, letters[i]);
        }
    }
    return current;
}

int main()
{
    // read in from the file into a vector
    std::string line{};
    std::vector<std::string> vec{};
    std::ifstream myfile("words.txt");
    std::vector<std::string> results_table{};
    std::vector<char> emojis_{ ' ', ' ', ' ', ' ', ' ' };
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            vec.push_back(line);
        }
        myfile.close();
    }

    // get the random number
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, vec.size()); // distribution in range [1, 6]
    auto random_number = dist6(rng);

    std::string random_word = vec[random_number];
    std::string input{};

    // now do the wordle part of it;
    std::vector<char> letters{ '_', '_', '_', '_', '_' };
    int number_of_goes = 0;
    while (number_of_goes < 6 && input != random_word)
    {
        std::cin >> input;
        compare(input, random_word, results_table, letters);
        std::cout << "\n\n\n\n\n\n\n\n\n";
        std::cout << input << "\n";
        int j{ 1 };
        for (int i = 0; i < results_table.size() && i < 36; i++)
        {
            std::cout << results_table[i];
            if (j % 5 == 0)
            {
                std::cout << "\n";
            }
            j++;
        }
        number_of_goes += 1;
    }
    std::cout << "The letters that you can have are as follows:\n";
    for (auto x : letters)
    {
        std::cout << x;
    }
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    auto only_word = find_in_dictionary(vec, letters);
    for (auto x : only_word)
    {
        std::cout << x << "\n";
    }
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n";
    std::cout << "\n" << random_word;
}