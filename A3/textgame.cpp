#include <cstdio>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <iostream>


void parser()
{

    std::ifstream infile("doggo.gfl");
    std::ifstream infile2("doggo.gfl");
    std::string temp;

    while ( std::getline(infile, temp) ){
        if (temp.length() == 0)
            continue;
        /* Parsing state titles */ 
        if (temp[0] == '@'){
            std::string state = temp.substr(temp.find_first_not_of("@*+"));
            state = state.replace(state.find_first_of(":"),1,"");
            std::cout << state << '\n';


        }
        /* Parsing Possible Transitions */
        if (temp[0] == '>') {
            if (temp.find('#') < temp.length())
                temp.erase(temp.find('#'));
            std::cout << temp << '\n';
        }
 
    }    
    std::string temp2;
    std::vector<std::list<std::string>> spam;
    std::list<std::string> gfx;
        while (std::getline(infile2, temp2)){
            if (temp2[0] == '@') {

                while (std::getline(infile2, temp2)){
                    if (temp2[0] == '>'){
                        std::cout << "spam" << '\n';
                        break;
                    }
                    gfx.push_back(temp2);
                }
                    spam.push_back(gfx);
            }
        }

        for (auto& i : gfx)
            std::cout << "image" << i << '\n';
        /* for (auto& j : spam) */
        /*     std::cout << "vector" << j.first() << '\n'; */
}

int main()
{
    parser();

    return 0;
}
