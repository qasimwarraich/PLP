#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

void printer(char flag);

void fizzbuzz(int m, int n, int fizz, int buzz)
{
    std::cout << "\nResult:" << '\n';
    for (; m <= n; m++) {
        if (m % fizz == 0) {
            if (m % buzz == 0) {
                std::cout << "FizzBuzz ";
            } else {
                std::cout << "Fizz ";
            }
        } else if (m % buzz == 0) {
            std::cout << "Buzz ";
        }

        else {
            std::cout << m << " ";
        }
    }
    std::cout << '\n';
}

int main()
{
    /* Flag for program looping */
    bool exit = 0;
    std::string user_input;
    printer('w');

    while (!exit) {

        /* Instruction message, see: printer(char flag) */
        printer('i');

        /* Initial user input parsing and exit check. */
        std::getline(std::cin, user_input);

        if (user_input == "quit" || user_input == "q") {
            printer('e');
            exit = 1;
            break;
        } else {
            /* Using string stream to put everything in an array of integers.
             * This has the added benefit of cutting off the stream when a non
             * integer is detected. Since we already checked for our magic word
             * "quit" this approach seems to work quite well. 
             */
            std::stringstream ss(user_input);
            auto start = std::istream_iterator<int> { ss };
            auto end = std::istream_iterator<int> {};
            std::vector<int> input(start, end);
            int n = input.size();

            /* More detailed input sanitising. */
            try {
                if (n != 4)
                    throw ">> Please enter exactly 4 Integers.\n";
                if (input[0] >= input[1])
                    throw ">> Integer m must be greater than n.\n";
                if (input[2] == input[3])
                    throw ">> Integers x and y must not be the equal.\n";
                for (int i = 0; i < n; i++)
                    if (input[i] < 1)
                        throw ">> Integers must be positive.\n";

            } catch (const char* err) {
                std::cout << "\nError: " << err << "Please try again\n"
                          << '\n';

                /* Restart if error caught */
                continue;
            }
            /* Input parsing complete, now call the function. */
            fizzbuzz(input[0], input[1], input[2], input[3]);
        }
    }
    return 0;
}

void printer(char flag)
{
    switch (flag) {

    case 'w':
        std::cout << "=====================\n"
                  << "Welcome to fizzbuzz++\n"
                  << "=====================\n"
                  << '\n';
        break;
    case 'e':

        std::cout << "\n\n"
                  << "=====================\n"
                  << "       EXITING       \n"
                  << "=====================\n"
                  << '\n';
        break;

    case 'i':
        std::cout << '\n'
                  << "==================================================\n"
                  << "Please enter four positive integers (m, n, x, y)\n"
                  << "seperated by one or more blank spaces or type quit\n"
                  << "==================================================\n"
                  << '\n';
        break;
    }
}
