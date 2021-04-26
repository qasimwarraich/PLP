#include <cstdio>
#include <ostream>
#include <map>
#include <fstream>
#include <string>
#include <iostream>


void print_map(std::map<std::string, std::string>& m);


void parser()
{

    std::ifstream infile("doggo.gfl");
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
            std::cout << temp.substr(temp.find('(')) << '\n';
        }
    }    
    /* This part aims to isolate the graphic and store it as a long string with 
     * appened newline chars to keep formatting
     */
    std::ifstream infile2("doggo.gfl");
    std::string temp2;
    std::string graphic_of_state;
    std::map<std::string, std::string> graphics_map;

    while (std::getline(infile2, temp2)){
        if (temp2[0] == '@') {
            /* Get title of graphic as key for the map */
            std::string title = temp2.substr(temp2.find_first_not_of("@*+"));

            /* Stop when a state transition line detected */
            while (std::getline(infile2, temp2)){
                if (temp2[0] == '>')
                    break;
                
                graphic_of_state.append(temp2 + '\n');
                graphics_map[title] = graphic_of_state;
            }
            graphic_of_state.clear();
        }
    }
        /* print_map(graphics_map); */ 
}



void print_map(std::map<std::string, std::string> &m)
{
    for (const auto& x : m) {
        std::cout << "Key: " << x.first << "\tVal: " << x.second << "\n";
    }
    std::cout << "\n";
}


int main()
{
    parser();

    return 0;
}
