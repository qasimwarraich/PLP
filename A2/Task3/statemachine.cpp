#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

void print_map(std::map<std::string, std::string>& m);



std::map<std::string, std::string> parse_states()
{
    std::ifstream infile("vending.machine");
    std::string title1 = "[States]";
    std::string title2 = "[Transitions]";
    std::string chars = "+*";
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

        for (char c : chars)
            key.erase(std::remove(key.begin(), key.end(), c), key.end());

        states[key.substr(0, key.find_first_of(" "))] =  val.substr(val.find_first_not_of(" "),val.length());
    }

    return states;
}

std::map<std::string, std::string> parse_transitions()
{
    /* Not properly implemented yet*/
    std::ifstream infile("vending.machine");
    std::string title1 = "[States]";
    std::string title2 = "[Transitions]";
    std::string temp;
    std::map<std::string, std::string> transitions;


    while ( std::getline(infile, temp) ){

        if (temp.length() == 0)
            continue;
        if (temp[0] == '#')
            continue;
        if (temp.compare(title1) == 0)
            continue;
        if (temp.compare(title2) == 0)
            continue;
        if (temp.find('#') < temp.length())
            temp.erase(temp.find('#'));


        auto colonpos = temp.find(':');
        auto key = temp.substr(temp.find_first_not_of(" "), colonpos);
        auto val = temp.substr(colonpos + 1, temp.length());

        transitions[key.substr(0, key.find_first_of(" "))] =  val.substr(val.find_first_not_of(" "),val.length());
    }
    return transitions;
}

int main()
{
    std::map<std::string, std::string> states = parse_states();
    std::map<std::string, std::string> transitions = parse_transitions();
    print_map(states);

    bool exit = 0;
    
        auto current_state = states["Ready"];
        auto previous_state = current_state;

    while (!exit) {

        std::string input;

        if (current_state == states["Ready"]){
            std::cout << "[Ready] " << current_state << '\n';
            std::cin >> input;
            current_state = states[input];
        }
        if (current_state == states["Exit"]) {
            std::cout << "[Exit] " << current_state << '\n';
            exit = 1;
            break;
        }
        if (current_state == states["Select"]) {
            std::cout << "[Select] " << current_state << '\n';
            std::cin >> input;
            previous_state = current_state;
            current_state = states[input];
        }
        if (current_state == states["Dispense"]) {
            std::cout << "[Dispense] " << current_state << '\n';
            std::cin >> input;
            previous_state = current_state;
            current_state = states[input];
        }
        else{
            std::cout << "Invalid Input, please try again" << '\n';
            current_state = previous_state;
            continue;
        }
    }

    return 0; 
}


void print_map(std::map<std::string, std::string>& m)
{
    for (const auto& x : m) {
        std::cout << "Key: " << x.first << "\tVal: " << x.second << "\n";
    }
    std::cout << "\n";
}
