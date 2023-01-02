#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char* argv[])
{
    // Get the path of the machine code file from the user
    std::cout << "Enter the path of the machine code file: ";
    std::string filePath;
    std::getline(std::cin, filePath);

    // Open the machine code file
    std::ifstream input(filePath);
    if (!input.is_open())
    {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return 1;
    }

    // Check for an error state in the input stream
    std::ifstream open(filePath);
    if (open.fail())
    {
        std::cerr << "Error reading file: " << filePath << std::endl;
        return 1;
    }

    // Read the machine code from the file
    std::string machineCode;
    std::string line;
    while (std::getline(input, line))
    {
        machineCode += line;
    }

    // Close the machine code file
    input.close();

    // Create the command to run objdump
    std::string command = "echo '" + machineCode + "' | objdump -D -mi386 -Mintel -";
    command += " > output.txt";

    // Run objdump and check the return value
    int ret = system(command.c_str());
    if (ret != 0)
    {
        std::cerr << "Error running objdump" << std::endl;
        return 1;
    }

    // Open the output file
    std::ifstream output("output.txt");
    if (!output.is_open())
    {
        std::cerr << "Error opening output file" << std::endl;
        return 1;
    }

    // Read the output of objdump
    while (std::getline(output, line))
    {
        std::cout << line << std::endl;
    }

    // Close the output file
    output.close();

    // Wait for the user to press a key before exiting
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}
