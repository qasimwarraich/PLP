#include <cstdio>
#include <ostream>
#include <map>
#include <fstream>
#include <string>
#include <iostream>


void print_map(std::multimap<std::string, std::string>& m);


void parser()
{

    std::ifstream infile("doggo.gfl");
    std::string temp;
    std::string state;
    std::multimap<std::string, std::string> commands;
    std::multimap<std::string, std::string> messages;
    std::multimap<std::string, std::string> transitions;

    while ( std::getline(infile, temp) ){
        if (temp.length() == 0)
            continue;
        /* Parsing state titles */ 
        if (temp[0] == '@'){
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
            /* commands.insert(state, command);*/
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
        print_map(commands); 
        print_map(messages); 
        print_map(transitions); 
}


void print_map(std::multimap<std::string, std::string> &m)
{
    for (const auto& x : m) {
        std::cout << "Key: " << x.first << "\tVal: " << x.second << "\n";
    }
    std::cout << "\n";
}


int main(int argc, char *argv[])
{
    /* std::cout << argv[0] << '\n'; */
    parser();

    return 0;
}
