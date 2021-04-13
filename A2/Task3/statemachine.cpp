#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

void print_map(std::map<std::string, std::string>& m);

std::map<std::string, std::string> parse_transitions()
{
    std::ifstream infile("vending.machine");
    std::string title1 = "[States]";
    std::string title2 = "[Transitions]";
    std::string temp;
    std::map<std::string, std::string> transitions;

    /* Parse the states */
    while ( std::getline(infile, temp) ){

        if (temp.length() == 0)
            continue;
        if (temp[0] == '#')
            continue;
        if (temp.compare(title1) == 0)
            continue;
        if (temp.compare(title2) == 0)
            break;
        if (temp.find('#') < temp.length())
            temp.erase(temp.find('#'));


        auto colonpos = temp.find(':');
        auto key = temp.substr(temp.find_first_not_of(" "), colonpos);
        auto val = temp.substr(colonpos + 1, temp.length());

        transitions[key.substr(0, key.find_first_of(" "))] =  val.substr(val.find_first_not_of(" "),val.length());
    }
    return transitions;
}

std::map<std::string, std::string> parse_states()
{
    std::ifstream infile("vending.machine");
    std::string title1 = "[States]";
    std::string title2 = "[Transitions]";
    std::string temp;
    std::map<std::string, std::string> states;

    /* Parse the states */
    while ( std::getline(infile, temp) ){

        if (temp.length() == 0)
            continue;
        if (temp[0] == '#')
            continue;
        if (temp.compare(title1) == 0)
            continue;
        if (temp.compare(title2) == 0)
            break;
        if (temp.find('#') < temp.length())
            temp.erase(temp.find('#'));


        auto colonpos = temp.find(':');
        auto key = temp.substr(temp.find_first_not_of(" "), colonpos);
        auto val = temp.substr(colonpos + 1, temp.length());

        states[key.substr(0, key.find_first_of(" "))] =  val.substr(val.find_first_not_of(" "),val.length());
    }

    /* print_map(states); */
    return states;
}

int main()
{
    std::map<std::string, std::string> states = parse_states();
    std::map<std::string, std::string> transitions = parse_transitions();
    print_map(states);

    bool exit = 0;
    
    while (!exit) {

        std::string input;
        auto current_state = states["*Ready"];

        if (current_state == states["*Ready"]){
            std::cout << "[Ready] " << current_state << '\n';
            std::cin >> input;
            current_state = states[input];
        }
        if (current_state == states["+Exit"]) {
            std::cout << "[Exit] " << current_state << '\n';
            exit = 1;
            break;
        }

    }

    return 0; 
}


void print_map(std::map<std::string, std::string>& m)
{
    for (const auto& x : m) {
        std::cout << x.first << "--->" << x.second << "\n";
    }
    std::cout << "\n";
}
