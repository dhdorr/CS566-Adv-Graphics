Derek Dorr

resources: I used ChatGPT to help me understand how to use stringstream to split the inputs for the faces of the object.
I gave it a sample line from sphere.obj and it gave me this code which I used in this assignment:
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::string str = "380/398/380 361/399/361 382/401/382";
    std::istringstream iss(str);
    std::string token;
    std::vector<unsigned int> numbers;

    // Splitting by space first to separate the sets of numbers
    while (std::getline(iss, token, ' ')) {
        std::istringstream tokenStream(token);
        std::string numberStr;

        // Splitting each set by '/'
        while (std::getline(tokenStream, numberStr, '/')) {
            try {
                unsigned int number = std::stoul(numberStr);
                numbers.push_back(number);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument: " << e.what() << '\n';
            } catch (const std::out_of_range& e) {
                std::cerr << "Out of range: " << e.what() << '\n';
            }
        }
    }

    // Output the numbers to verify
    for (unsigned int num : numbers) {
        std::cout << num << std::endl;
    }

    return 0;
}


I belive this code runs as expected, no problems.

comments: reading in the obj file was tough, especially for the face vectors. I guess I just don't understand how to use stringstream
 or how the implicit type conversion seems to be working. Some more guidance or a warm-up on that would have been nice.