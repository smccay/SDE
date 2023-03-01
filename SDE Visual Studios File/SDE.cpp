#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>

std::vector<std::string> input(std::string_view x)
{
    std::cout << "Please enter a password to be "<< x <<"\n";
    std::string temp{};
    std::cin >> temp;
    std::vector<std::string> password;
    password.push_back(temp);
    return password;
}
std::vector<std::string> encrypt(std::vector<std::string> password)
{
    srand(time(NULL));
    int shift{ 0 };
    while (shift == 0) 
    { 
        shift = rand() % 11 - 5;
    }
    std::cout << shift <<"\n";
    int x{ 0 };
    int y{ 0 };
    if (shift > 0)
    {
        x = shift;
        //password.insert(password.begin(), std::to_string(x));
    }
    else
    {
        y = shift*-1;
        //password.insert(password.begin(), std::to_string(shift));
    }
    std::cout << x << "\n";
    std::cout << y << "\n";

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
        for (int i1 = 0+y; i1 < 95-x; i1++)
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
    password.insert(password.begin(), std::to_string(shift));
    return password;
}
std::vector<std::string> decrypt(std::vector<std::string> userEncrypted)
{
    std::array<char, 95>  characters{ ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
                    '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
                    'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
                    '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                    'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~' };
    std::string str = userEncrypted[0];
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        //Debug: std::cout <<"\n" << password[0][i] << ": outer loop \n";
        for (int i1 = 2; i1 < 91; i1++)
        {
            if (characters[i1] == userEncrypted[0][i])
            {
                //Debug:std::cout<< characters[i1] << ": inside if statement \n";
                userEncrypted[0][i] = characters[i1 - 3];
                //Debug:std::cout << userEncrypted[0][i] << ": Success - \n";
                break;
            }
        }
    }
    return userEncrypted;
}


int main()
{
    std::vector<std::string> password{ input("encrypted")};
    std::vector<std::string> encrypted{ encrypt(password) };
    for (const auto& str : encrypted) {
        std::cout << str << " ";
    }
    //std::vector<std::string> enPassword{ input("decrypted") };
    //std::vector<std::string> decrypted{ decrypt(enPassword) };
    //for (auto number : decrypted)
    //{
        //std::cout << "Your password decrypted is " << number << ' ' << "\n";
    //}
    return 0;
}
