#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <random>
#include <wx/string.h>
#include <wx/tokenzr.h>


std::vector<std::string> encrypt_decrypt(std::vector<std::string> password, bool z)
{
    int shift{ 0 };
    int x{ 0 };
    int y{ 0 };
    if (z == false)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        //Generator Params
        std::uniform_int_distribution<> numGen(5, 11);
        while (shift == 0)
        {
            shift = numGen(gen);
        }
        if (shift > 0)
        {
            x = shift;
        }
        else
        {
            y = shift * -1;
        }
    }
    else
    {
        shift = std::stoi(password[0]);
        password.erase(password.begin());
        if (shift < 0)
        {
            x = shift * -1;
        }
        else
        {
            y = shift;
        }
    }
    //Debug: std::cout << x << "\n";
    //Debug: std::cout << y << "\n";

    std::array<char, 95>  characters{ ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
                    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
                    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~' };
    std::string str = password[0];
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        //Debug: std::cout <<"\n" << password[0][i] << ": outer loop \n";
        for (int i1 = 0 + y; i1 < 95 - x; i1++)
        {
            if (characters[i1] == password[0][i])
            {
                //Debug:std::cout<< characters[i1] << ": inside if statement \n";
                password[0][i] = characters[i1 + x - y];
                //Debug:std::cout << password[0][i] << ": Success - \n";
                break;
            }
        }
    }
    if (z == false)
    {
        password.insert(password.begin(), std::to_string(shift));
        //password.pop_back();
    }
    return password;
}

std::string passwordGen(int pLen)
{
    std::array <char, 94> passwordChars = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
    'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
    'Y', 'Z', '!', '@', '#', '$', '%', '^', '&', '*',
    '(', ')', '-', '_', '+', '=', '`', '~', '[', ']',
    '{', '}', '|', ';', ':', ',', '.', '/', '<', '>',
    '?' };
    std::vector<std::string> password;
    std::random_device rd;
    std::mt19937 gen(rd());
    //Generator Params
    std::uniform_int_distribution<> numGen(0, 9);
    std::uniform_int_distribution<> lcGen(9, 35);
    std::uniform_int_distribution<> ucGen(35, 61);
    std::uniform_int_distribution<> charGen(0, 94);
    for (int i = 0; i < pLen; i++)
    {
        // Ensures that there are at least 1 of each type of characters in password
        int num{};
        if (i == 0) { num = numGen(gen); }
        else if (i == 1) { num = lcGen(gen); }
        else if (i == 2) { num = ucGen(gen); }
        else if (i > 2) { num = charGen(gen); }
        //DEBUG//std::cout <<"Iteration; "<< i <<"| Random NUM; " << num << "\n";
        password.push_back(std::string(1, passwordChars[num]));
    }
    std::string generatedPassword;
    for (const std::string& character : password)
    {
        generatedPassword += character;
    }

    return generatedPassword;
}

std::vector<std::string> wxStringToVector(const wxString& wxstr)
{
    std::vector<std::string> result;
    wxStringTokenizer tokenizer(wxstr, "\n");  // Split wxString by newline character

    while (tokenizer.HasMoreTokens())
    {
        wxString token = tokenizer.GetNextToken();
        std::string str(token.utf8_string());  // Convert wxString to std::string
        result.push_back(str);
    }
    return result;
}

std::vector<std::string> wxStringToVectorx2(const wxString& wxstr1, const wxString& wxstr2)
{
    std::vector<std::string> result;
    std::string str1(wxstr1.utf8_string()); // Convert wxString to std::string
    std::string str2(wxstr2.utf8_string()); // Convert wxString to std::string
    result.push_back(str1);
    result.push_back(str2);
    return result;
}

std::vector<wxString> vectorToWxString(const std::vector<std::string>& strings)
{
    std::vector<wxString> result;
    for (const auto& str : strings)
    {
        wxString wxstr(str.c_str(), wxConvUTF8); // Convert std::string to wxString
        result.push_back(wxstr);
    }
    return result;
}

wxString wxSplit(std::vector<wxString> vec, bool x)
{
    if (x)
    {
        wxString y{ vec[0] };
        return y;
    }
    else
    {
        wxString z{ vec[1] };
        return z;
    }
}