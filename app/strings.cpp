#include <string>
#include <map>
#include <set>
#include <gtest/gtest.h>
#include <string_view>
#include "utils.h"

#include "absl/strings/str_join.h"
#include "absl/utility/utility.h"


/*
 * Suppose that you are given a string. Write a 
 * function to find the first nonrepeated character 
 * in that string. Here’s an example: suppose 
 * you are given the string “interview”. The 
 * first nonrepeated character in that string is 
 * ‘n’, because ‘i’ appears twice in the string. 
 * And the first nonrepeated character for “racecar” 
 * is ‘e’ – which is the first and only nonrepeated 
 * character. Explain the efficiency of your algorithm.
 */

// interview
// ......x..


TEST(StrFormat, test_function)
{
    std::string message = absl::StrFormat("Welcoe to %s", 6);
}

char firstNonRepeated(const std::string& string_ )
{
    LOG(string_);
    size_t size_of_string = string_.size();
    auto cstr = string_.c_str();

    std::set<char> seenChars;
    std::set<char>::iterator search;

    for (size_t pos(0); pos < size_of_string; pos++)
    {
        char cc = cstr[pos];
        // cum_sum(n*O(log(m)) ... of current length of map
        // delete if we exceed 1.
        search = seenChars.find(cc); 
        if (search != seenChars.end())
            seenChars.erase(search);
        else 
            seenChars.insert(cc); 
    }
    return *seenChars.begin();
}

TEST(firstNonRepeated, smoke_test)
{
    std::string instring = "interview";
    char res = firstNonRepeated(instring);
    LOG( instring << ": fisrt non_repeated:  " <<  res);
    ASSERT_TRUE('n' == res); 
}

TEST(firstNonRepeated, no_non_repeating_char)
{
    std::string instring = "abab";
    char res = firstNonRepeated(instring);
    LOG( instring << ": fisrt non_repeated:  " <<  res);
    EXPECT_EQ('\0',  res); 
}


// How do you reverse words in a given sentence without using any library method?
std::string reverseStrings(const std::string& strings_)
{

    std::string out_string;
    const char* cstr = strings_.c_str();
    int size = strings_.size();
    for (int pos(size-1); pos >= 0; pos--)
    {
        out_string += cstr[pos];
    }
    return out_string;
}

TEST(reverseStrings, smoke_test)
{
    std::string stin = "abcdefghijk";
    std::string stout = reverseStrings(stin);
    LOG("Original order: " << stin << " reverse order: " << stout);
    EXPECT_EQ(stout, "kjihgfedcba");
}

//How do you reverse words in a given sentence without using any library method?

const std::vector<std::string_view> getWords(const std::string_view& sentence_)
{
    size_t prev_pos = 0;
    std::vector<std::string_view> out_vec{0};
    for (size_t strpos = sentence_.find(' '); strpos < sentence_.size(); )
    {
        out_vec.push_back(sentence_.substr(prev_pos, strpos - prev_pos));
        strpos = sentence_.find(' ', strpos+1);
        LOG("found space at strpos=" << strpos);
        prev_pos = strpos;
    }
    LOG("out_vec.size()=" << out_vec.size());
    return out_vec;
}

std::string reverseWords(const std::string& sentence)
{
    // reversed words -> words reversed
    // and the cow -> cow the and
    // and the cows hat -> hat cows the and
    std::vector<int> pos;
    auto words = getWords(sentence);
    std::string outstring = "";
    for (std::vector<std::string_view>::iterator it = words.end(); it != words.end(); --it)
    {
        outstring + std::string(*it);
    }
    return outstring;
}

TEST(reverseWords, smoke_test)
{
    std::string sentence = "reveresed words in sentence";
    std::string out = reverseWords(sentence);
    LOG("sentence=" << sentence << ", out=" << out);
    EXPECT_EQ("sentence in words reversed", out);

}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

