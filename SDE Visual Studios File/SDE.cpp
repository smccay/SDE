#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cstdlib>
#include <ctime>
std::vector<std::string> input(std::string_view x, bool y)
{
    std::cout << "Please enter a password to be "<< x <<"\n";
    std::string temp{};
    std::cin >> temp;
    std::vector<std::string> password;
    password.push_back(temp);
    if (y == true)
    {
        std::cout << "Please enter the decryption key: \n";
        std::cin >> temp;
    }
    password.insert(password.begin(), temp);
    return password;
}
std::vector<std::string> encrypt_decrypt(std::vector<std::string> password, bool z)
{
    int shift{ 0 };
    int x{ 0 };
    int y{ 0 };
    if (z == false)
    {
        srand(time(NULL));
        while (shift == 0)
        {
            shift = rand() % 11 - 5;
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
    if (z == false)
    {
        password.insert(password.begin(), std::to_string(shift));
        password.pop_back();
    }
    return password;
}
void initializeUI()
{
    std::cout << "Welcome to Simple Decrypter / Encrypter \n";
    tryAgain:
    std::cout << "Do you wish to decrypt or encrypt? (1 for encrypt/2 for decrypt) \n";
    int userInput{};
    std::cin >> userInput;
    std::vector<std::string> password{};
    std::vector<std::string> encrypted{};
    std::vector<std::string> enPassword{};
    std::vector<std::string> decrypted{};
    switch (userInput)
    {
    case (1):
        password = { input("encrypted", false) };
        encrypted = { encrypt_decrypt(password, false) };
        std::cout << encrypted[0] << " is your encryption key \n" << encrypted[1] << " is your password encrypted \n";
        break;
    case (2):
        enPassword = { input("decrypted", true) };
        decrypted = {encrypt_decrypt(enPassword, true) };
        std::cout << decrypted[0] << " is your password decrypted \n";
        break;
    default:
        std::cout << "Please enter a VALID option. \n";
        goto tryAgain;
    }
}
int main()
{
    initializeUI();
    return 0;
}
