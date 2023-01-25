#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <exception>

using namespace std;

int main() {

    // defining a variable named fileName and outputFileName
    std::string fileName, outputFileName;


    // Defining the regex for a Windows file path and .cpp extension
    // source: https://stackoverflow.com/questions/15709711/c-regex-to-search-file-paths-in-a-string
    std::regex windowsPattern(".?:(\\\\[a-zA-Z 0-9]*)*.[a-zA-Z]*.cpp");

    // declaring a bool for validation
    bool validFileType = false;

    do {
        // asking user to input a file name
        std::cout << "Please enter the file name (e.g. 'testFile' or 'c:\\testFile.cpp'" << std::endl;
        std::cin >> fileName;

        // checking if file matches the pattern
        if(std::regex_match(fileName, windowsPattern)) {
            std::cout << "Valid c++ file!" << std::endl;

            validFileType = true;
        }

    } while(!validFileType);


    // implement try catch block

    try {

        // using ifstream to declare an object
        std::ifstream file;

        // opening the file
        file.open(fileName, ios::app);

        if(file.is_open()){

            // reading the lines from the file and storing in a string
            std:: string line, content;

            // Reading the file line by line for replacements
            do {
                line = std::regex_replace(line,std::regex("<"),"&lt"); // replacing all "<" with "&lt"
                line = std::regex_replace(line,std::regex(">"),"&gt"); // replacing all ">" with "&gt"
                content += line + '\n';
            } while(std::getline(file,line));

            //closing the file
            file.close();

            // changing fileName to include ".html" extension and storing in new ofstream object
            outputFileName = std::regex_replace(fileName,std::regex(".cpp"),".html");

            // now opening file in write mode to write <PRE> at beginning and </PRE> at the end
            std::ofstream outfile (outputFileName);

            outfile << "<PRE>\n" << content << "\n</PRE>";

            // closing outfile
            outfile.close();

        } else if (file.fail()){
            std::cout << "Error: Unable to open the file!" << std::endl;

            return 1;

        } else {
            std::cout << "Error: File does not exist!" << std::endl;

            return 1;
        }

    }catch (exception e){

    }


    return 0;
}
