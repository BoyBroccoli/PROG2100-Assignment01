#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {

    // defining a variable named fileName and content
    std::string fileName;
    std:: string outputFileName;
    //std::string content; // to store the lines of the file being opened

    // Defining the regex for .cpp extension
    std::regex cppPattern("^.+\\.cpp$");
    std::regex windowsPattern("^(?!^(PRN|AUX|CLOCK$|NUL|CON|COM\\d|LPT\\d|..)(..+)?$)[^\\x00-\\x1f\\?:\";|/]+\\.cpp$");

    // declaring a bool for validation
    bool validFileType = false;

    do {
        // asking user to input a file name
        std::cout << "Please enter the file name:" << std::endl;
        std::cin >> fileName;

        // checking if file matches the pattern
        if(std::regex_match(fileName, cppPattern)) {
            std::cout << "Valid c++ file!" << std::endl;

            // reading in the file
            validFileType = true;
        }

    } while(!validFileType);

        // using ifstream to declare an object
        std::ifstream file; // declaring an ifstream object

        // opening the file
        file.open(fileName, ios::app);

        if(file.is_open()){

            // reading the lines from the file and storing in a string
            std:: string line;
            std:: string content = "";

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
            //closing outfile
            outfile.close();

        } else if (file.fail()){
            std::cout << "Error: Unable to open the file!" << std::endl;

            return 1;
        } else {
            std::cout << "Error:File does not exist!" << std::endl;

            return 1;
        }

    return 0;
}
