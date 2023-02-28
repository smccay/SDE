#include <iostream>
#include <vector>
#include <array>

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
    int passwordSize{ password.size() };

}


int main()
{
    std::vector<std::string> password{ input()};
    encrypt(password);
    return 0;
}
