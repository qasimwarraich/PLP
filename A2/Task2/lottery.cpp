#include <algorithm>
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <math.h>
/* #include <ostream> */

#include "cxxopts.hpp"

void loading_animation();


void lottery (int n, int c, int p)
{
    int pot =  p;
    std::cout << "Pot Size: " << p << '\n';
    std::string user_input;
    std::getline(std::cin, user_input);

    std::stringstream ss (user_input);
    auto start = std::istream_iterator<int> { ss };
    auto end = std::istream_iterator<int> { };
    std::vector<int> input(start, end);
    int size = input.size(); 
    
    std::sort(std::begin(input), std::end(input));
    auto pos = std::adjacent_find(std::begin(input), std::end(input));

    try {
    if ( size != c) throw "Invalid input, wrong number of guesses"; 
    if ( pos != std::end(input)) throw "Invalid input, duplicate guesses exist";
    if ( input[0] == 0 ) throw "Guesses must be larger than 0";

    } catch (const char* err) {
        std::cout << "\nError: " << 
        err                      <<
        "\nPlease try again"     <<
        '\n';

        /* return if error caught */
        return;
    }

    loading_animation();

    std::vector<int> shuffled;
    for (int i = 0; i < c; i++) {
        shuffled.push_back(std::rand() % n);
        std::cout << shuffled[i] << ' ';
        std::flush(std::cout);
        sleep(2);
    }

    std::sort(std::begin(shuffled), std::end(shuffled));
    auto not_random = std::adjacent_find(std::begin(shuffled), std::end(shuffled));
    
    while ( not_random != std::end(shuffled) ) {
        *not_random = std::rand() % n;
        not_random = std::adjacent_find(std::begin(shuffled), std::end(shuffled));
    }

    std::vector<int> intersection(input.size() + shuffled.size());
    std::vector<int>::iterator it, st;
 
    st = std::set_intersection(
            input.begin(), input.end(),
            shuffled.begin(), shuffled.end(),
            intersection.begin());
    int count = 0;
    for (it = intersection.begin(); it != st; it++) {
        count++;
    }

    std::cout << "\nNumber of matches: " << count << '\n';
    int result;
    result = pow((float)pot, ((float)count/c)) + 0.5;
    std::cout << "\nYou got " << count << " out of " << c << " correct guesses and win " << result  << " beer tokens\n";

    return;
}

int main(int argc, char* argv[])
{
    cxxopts::Options options("Lottery Program", "Simple Lottery Game");

    options.add_options()
        ("n,numbers", "Numerical Range", cxxopts::value<int>())
        ("c,choices", "Number of lottery choices", cxxopts::value<int>())
        ("p,pot", "Define winning pot size", cxxopts::value<int>()->default_value("1000"));

    auto result = options.parse(argc, argv);

    int n = result["n"].as<int>();
    int c = result["c"].as<int>();
    int p = result["p"].as<int>();

    if ( result["n"].as<int>() < 0 || result["c"].as<int>() < 0 ) std::cout << "n too small \n";
    if ( result["n"].as<int>() < result["c"].as<int>()) std::cout << "n must be larger than c \n";

    lottery(n, c, p);
    return 0;
}

void loading_animation(){
    std::cout << "Shuffling... ";
    std::cout << '-' << std::flush;
    for (;;) {
        sleep(1);
        std::cout << "\b\\" << std::flush;
        sleep(1);
        std::cout << "\b|" << std::flush;
        sleep(1);
        std::cout << "\b/" << std::flush;
        sleep(1);
        std::cout << "\b-" << std::flush;
        sleep(1);
        std::cout << "\b  \n";
        break;
    }
}


