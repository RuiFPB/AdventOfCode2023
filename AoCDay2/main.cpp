#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

#define RED_LIMIT 12
#define GREEN_LIMIT 13
#define BLUE_LIMIT 14

std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    size_t pos_start = 0;
    size_t pos_end;
    const size_t delim_len = delimiter.length();

    std::vector<std::string> result;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
        std::string token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }

    result.push_back(str.substr(pos_start));

    // remove whitespace at beginning and end of each string
    for (std::string& split: result) {
        std::string tmp = split;
        const size_t first = tmp.find_first_not_of(' ');
        const size_t last = tmp.find_last_not_of(' ');
        split = tmp.substr(first, (last - first + 1));
    }
    
    return result;
}

class Draw {
private:
    int red;
    int green;
    int blue;
public:
    explicit Draw(const std::string& draw) {
        // draw format is [number] [color], [number] [color], ... (not all colors are required)
        // example: 1 red, 2 green, 3 blue
        // example: 1 red, 2 green

        red = green = blue = 0;

        // split the string by the comma
        const std::vector<std::string> splitDraw = split(draw, ",");

        // for each split, read the number and color
        for (const std::string& entry : splitDraw) {
            // if the color is red, set the red value
            if (std::vector<std::string> splitNumberColor = split(entry, " "); splitNumberColor[1] == "red") {
                red = std::stoi(splitNumberColor[0]);
            }
            // if the color is green, set the green value
            else if (splitNumberColor[1] == "green") {
                green = std::stoi(splitNumberColor[0]);
            }
            // if the color is blue, set the blue value
            else if (splitNumberColor[1] == "blue") {
                blue = std::stoi(splitNumberColor[0]);
            }
        }
    }

    [[nodiscard]] std::string toString() const {
        return std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
    }

    [[nodiscard]] bool isPossible() const {
        if (red > RED_LIMIT || green > GREEN_LIMIT || blue > BLUE_LIMIT) {
            return false;
        }
        return true;
    }

    [[nodiscard]] std::array<int, 3> getRawValues() const {
        return {red, green, blue};
    }
};

class Game {
private:
    int id;
    std::vector<Draw> draws;
public:
    explicit Game(const std::string& gameDesc) {
        const std::vector<std::string> splitIdDraws = split(gameDesc, ":");
        id = std::stoi(split(splitIdDraws[0], " ")[1]);

        const std::vector<std::string> splitDraws = split(splitIdDraws[1], ";");
        for (const std::string& draw : splitDraws) {
            draws.emplace_back(draw);
        }
    }

    [[nodiscard]] bool isPossible() const {
        return std::all_of(draws.begin(), draws.end(), [](const Draw& draw) { return draw.isPossible(); });
    }

    [[nodiscard]] int getId() const { return id; }

    [[nodiscard]] std::array<int, 3> getMinRequired() const {
        std::array<int, 3> minRequired = {0, 0, 0};

        for (const Draw& draw : draws) {
            std::array<int, 3> rawValues = draw.getRawValues();
            if (rawValues[0] > minRequired[0]) {
                minRequired[0] = rawValues[0];
            }
            if (rawValues[1] > minRequired[1]) {
                minRequired[1] = rawValues[1];
            }
            if (rawValues[2] > minRequired[2]) {
                minRequired[2] = rawValues[2];
            }
        }

        return minRequired;
    }

    [[nodiscard]] long getPower() const {
        const std::array<int, 3> minRequired = getMinRequired();
        return minRequired[0] * minRequired[1] * minRequired[2];
    }
};


int main() {
    unsigned long sum = 0;

    std::cout << "Select the part to run (1 or 2): ";
    int part;
    std::cin >> part;
    std::cin.ignore();

    if (part == 1) {
        // loop until the user enters an empty line
        while (true) {
            // get a line from the user
            std::string line;
            std::getline(std::cin, line);

            // if the line is empty, break out of the loop
            if (line.empty()) {
                break;
            }

            if (Game game(line); game.isPossible()) {
                sum += game.getId();
            }
        }
    }
    else if (part == 2) {
        while (true) {
            // get a line from the user
            std::string line;
            std::getline(std::cin, line);

            // if the line is empty, break out of the loop
            if (line.empty()) {
                break;
            }

            const Game game(line);
            sum += game.getPower();
            std::cout << "Game " << game.getId() << " power: " << game.getPower() << '\n';
        }
    }
    else {
        std::cout << "Invalid part!\n";
        return 1;
    }

    std::cout << "Total: " << sum << "\n";

    return 0;
}