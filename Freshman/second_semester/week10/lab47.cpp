#include <iostream>
#include <string>

class Encryption {
    std::string _text;
    std::string _range;

  public:
    Encryption(std::string text, std::string range) : _text(text), _range(range) {}

    char character(char ch);
    std::string decrypt();
    void set_text(std::string text) { this->_text = text; }
    std::string get_text() { return _text; }
};

char Encryption::character(char ch) {
    if (std::isalpha(ch))
        ch = tolower(ch);

    int index = this->_range.find(ch);
    if (index == std::string::npos)
        return ch;

    int new_index = (index + this->_range.size() - 2) % this->_range.size();

    return this->_range[new_index];
}

std::string Encryption::decrypt() {
    std::string decrypted_text;

    for (int i = 0; i < this->_text.size(); i++)
        decrypted_text += (this->_text[i] != ' ') ? character(this->_text[i]) : ' ';

    return decrypted_text;
}

int main(void) {
    Encryption encrypted_text(std::string(), "qwertyuiop[]asdfghjkl;'zxcvbnm,./");
    std::string text;

    while (std::getline(std::cin, text)) {
        encrypted_text.set_text(text);
        std::cout << encrypted_text.decrypt() << std::endl;
    }
}
