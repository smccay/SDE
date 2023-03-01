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
        std::cout << password[0][i] << ": outer loop \n";
        for (int i1 = 0; i1 < 26; i1++)
        {
            if (lowercase[i1] == password[0][i] && lowercase[i1] != lowercase[25] && lowercase[i1] != lowercase[24] && lowercase[i1] != lowercase[23])
            {
                std::cout << "\n" <<lowercase[i1] << ": inside if statement \n";
                password[0][i] = lowercase[i1 + 3];
                std::cout << password[0][i] << " Success \n";
                break;
            }
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
