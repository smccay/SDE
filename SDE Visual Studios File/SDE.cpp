#include <iostream>
#include <vector>
#include <array>
#include <string>

std::vector<std::string> input()
{
    std::cout << "Please enter the password to be encrypted\n";
    std::string temp{};
    std::cin >> temp;
    std::vector<std::string> password;
    password.push_back(temp);
    return password;
}
std::vector<std::string> encrypt(std::vector<std::string> password)
{
    std::array<char, 26>  lowercase{ 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    std::string str = password[0];
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        for (int c{ 0 }; char letter : lowercase)
        {
            if (letter == password[0][i] && letter != lowercase[25] && letter != lowercase[24] && letter != lowercase[23])
            {
              std::cout << letter << "\n";
              password[0][i] = lowercase[c + 3];
              std::cout << password[0][i] << " Success \n";
            }
            ++c;
        }
        for (auto number : password)
        {
            std::cout << number << ' ';
        }
    }
    return password;
}
    

int main()
{
    std::vector<std::string> password{ input()};
    std::vector<std::string> encrypted{ encrypt(password) };
    for (auto number : encrypted)
    {
        std::cout << number << ' ';
    }
    return 0;
}
