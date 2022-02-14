#include <string>
#include <iostream>
#include <unordered_map>

#include "ESN.hpp"

// Entry Point
int main (int argc, char* argv[])
{
    // Read the file
    std::string Path = "Example.esn";
    std::string FileString;
    bool SuccessReadFile = ESN::ReadFile(Path,FileString);
    // FIle reading error handling
    if ( !SuccessReadFile )
    {
        std::cout << "Unexpected error occured while reading file \"" << Path << "\"\n"; 
    }

    ESN::Map ParsedString = ESN::Parse(FileString);

    ESN::Map Variable;
    Variable["${Foo}"] = "Name";
    Variable["^Bar"] = "Some";

    ESN::SetVariable(ParsedString, Variable);

    // Due to the nature of unordered map, this will appear reversed from the file
    // You can see in ESN.cpp how we combat this
    std::cout << "\nLooping through ESN Map...\n";
    for (auto it : ParsedString)
    {
        std::cout << it.first << ", " << it.second << "\n";
    }
    std::cout << "\n";

    std::cout << "Printing ESN Map...\n" << ESN::ToString(ParsedString) << "\n\n";
    std::cout << "Pretty-printing ESN Map...\n" << ESN::PrettyPrint(ParsedString) << "\n";
    
    //End Program
    return 0;
}
