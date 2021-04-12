#include <cstdio>
#include <iostream>

const int BUFFER_SIZE = 128;

std::string system_call(std::string command)
{
    char buffer[BUFFER_SIZE];
    std::string output;

    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe)
        std::cout << "Could not open pipe" << "/n";

    while ( fgets(buffer, BUFFER_SIZE, pipe) != NULL ) {
            output += buffer;
    }
    pclose(pipe);

    return output;
}

int main()
{
    std:: cout << system_call("uname -r");
    std:: cout << system_call("fortune");
    std:: cout << system_call("neofetch");
    return 0;
}
