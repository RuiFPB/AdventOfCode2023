#include <iostream>

int getFirstDigit(const std::string& line) {
    // loop through the line
    for (int i = 0; i < line.length(); i++) {
        // if the current character is a digit
        if (isdigit(line[i])) {
            // return the digit
            return line[i] - '0';
        }
    }

    // if we didn't find a digit, return -1
    return -1;
}

int getLastDigit(const std::string& line) {
    // loop through the line in reverse
    for (int i = line.length() - 1; i >= 0; i--) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
    }

    // if we didn't find a digit, return -1
    return -1;
}

int concatenateDigits(int firstDigit, int lastDigit) {
    // return the concatenation of the two digits
    return firstDigit * 10 + lastDigit;
}

std::string parseSpelledOutNumbers(const std::string& line) {
    // create new line
    std::string newLine;

    std::string patterns[] = {
        "zero", "one", "two", "three", "four",
        "five", "six", "seven", "eight", "nine",
        "0", "1", "2", "3", "4",
        "5", "6", "7", "8", "9"
    };

    // loop through the line, matching patterns
    for (int i = 0; i < line.length(); i++) {
        // loop through the patterns
        for (int j = 0; j < 20; j++) {
            // if the current pattern matches
            if (line.substr(i, patterns[j].length()) == patterns[j]) {
                // append the digit to the new line
                // if the pattern is a spelled out number
                if (j < 10) {
                    newLine += std::to_string(j);
                } else { // if the pattern is a digit
                    newLine += patterns[j];
                };
                // break out of the loop
                break;
            }
        }
    }


    return newLine;
}

int main() {

    unsigned long sum = 0;

    // loop until the user enters an empty line
    while (true) {
        // get a line from the user
        std::string line;
        std::getline(std::cin, line);

        // if the line is empty, break out of the loop
        if (line.empty()) {
            break;
        }

        // Comment out this line for part 1
        std::string parsedLine = parseSpelledOutNumbers(line);

        //std::cout << "Parsed line from " << line << " to " << parsedLine << '\n';

        int firstDigit = getFirstDigit(parsedLine);
        int lastDigit = getLastDigit(parsedLine);
        int concatenated = concatenateDigits(firstDigit, lastDigit);

        //std::cout << "Value: " << concatenated << '\n';

        sum += concatenated;
    }

    std::cout << "Total: " << sum << "\n";

    return 0;
}
