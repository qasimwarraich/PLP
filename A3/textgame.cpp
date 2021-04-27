#include <cstdio>
#include <ostream>
#include <map>
#include <fstream>
#include <string>
#include <iostream>

std::map<std::string, std::string> parse_graphics()
{
    /* This part aims to isolate the graphic and store it as a long string with 
     * appened newline chars to keep formatting
     */
    std::ifstream infile("doggo.gfl");
    std::string temp;
    std::string graphic_of_state;
    std::map<std::string, std::string> graphics_map;

    while (std::getline(infile, temp)){
        if (temp[0] == '@') {
            /* Get title of graphic as key for the map */
            std::string title = temp.substr(temp.find_first_not_of("@*+"));
            title = title.erase(title.find(':'));

            /* Stop when a state transition line detected */
            while (std::getline(infile, temp)){
                if (temp[0] == '>')
                    break;
                
                graphic_of_state.append(temp + '\n');
                graphics_map[title] = graphic_of_state;
            }
            graphic_of_state.clear();
        }
    }
    return graphics_map;
}

void print_map(std::multimap<std::string, std::string> &m)
{
    for (const auto& x : m) {
        std::cout << "Key: " << x.first << "\t\tVal: " << x.second << "\n";
    }
    std::cout << "\n";
}

void print_graphics_map(std::map<std::string, std::string> &m)
{
    for (const auto& x : m) {
        std::cout << "Key: " << x.first << "\t\tVal: " << x.second << "\n";
    }
    std::cout << "\n";
}

int main(int argc, char *argv[])
{
    /* std::cout << argv[0] << '\n'; */
    std::ifstream infile("doggo.gfl");
    std::string temp;
    std::string state;
    std::string initial_state;
    std::map<std::string, std::string> graphics_map;
    std::multimap<std::string, std::string> commands;
    std::multimap<std::string, std::string> messages;
    std::multimap<std::string, std::string> transitions;

    graphics_map = parse_graphics();


    /* Parse states, intial state, transitions and messages */
    while ( std::getline(infile, temp) ){
        if (temp.length() == 0)
            continue;
        /* Parsing state titles */ 
        if (temp[0] == '@'){
            if ( temp.find('*') < temp.length()  ){
                initial_state = temp.substr(temp.find_first_not_of("@*+"));
                initial_state = initial_state.replace(initial_state.find_first_of(":"),1,"");
                }
            state = temp.substr(temp.find_first_not_of("@*+"));
            state = state.replace(state.find_first_of(":"),1,"");
            /* std::cout << state << '\n'; */
        }
        /* Parsing Possible Transitions */
        if (temp[0] == '>') {
            if (temp.find('#') < temp.length())
                temp.erase(temp.find('#'));
            /* Removes current state leaving just expected command and outputs. */
            std::string command = temp.substr(temp.find( '(') + 1 );
            std::string message = temp.substr(temp.find_first_of( ':') + 1 );
            std::string transition = command.substr(command.find_first_of( ")" ) + 2);
            transition = transition.erase(transition.find(':')) ;

            commands.insert(std::pair<std::string,std::string> (state, command.erase(command.find( ")" )) ));
            messages.insert(std::pair<std::string,std::string> (command, message));
            transitions.insert(std::pair<std::string,std::string> (command, transition));
        }
    }

    print_map(commands);
    print_map(transitions);
    print_map(messages);

    bool exit = 0;
    std::string input;

    std::cout << "**Welcome to a text based adventure game**" << "\n\n\n";
    std::string current_state = initial_state;
    
    while (!exit) {


        std::cout << graphics_map[current_state];
        if (current_state == "GameOver")
            break;
        std::cout << "> Doggo is currently [" << current_state << "] Enter a command from above\n";
        /* std::cin >> input; */ 
        std::getline(std::cin, input);
        if (input == "quit" ) {
            exit = 1;
            break;
        }
        else {
            /* if (messages.find(input) != messages.end()){ */ 
            if (messages.find(input) != messages.end()){ 
                std::cout << "spam " << commands.find(current_state)->second << '\n';
                std::cout << "\n\n=>" << messages.find(input)->second << " <=\n";
                current_state = transitions.find(input)->second;
            }
            else
                std::cout << "**INVALID INPUT, TRY AGAIN**\n";
        }
    }
    return 0;
}
