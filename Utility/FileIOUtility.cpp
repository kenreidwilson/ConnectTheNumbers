#include "FileIOUtility.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Utility
{

void FileIOUtility::initializeFile(string filePath)
{
    ofstream outFile (filePath);
    outFile << "" << endl;
    outFile.close();
}

string FileIOUtility::readLine(string filePath, int lineNumber)
{
    vector<string> lines = readLines(filePath);
    if (lineNumber > lines.size())
    {
        throw invalid_argument("Line not found: " + to_string(lineNumber));
    }
    return lines[lineNumber - 1];
}

vector<string> FileIOUtility::readLines(string filePath)
{
    ifstream file (filePath);
    if (!file)
    {
        throw invalid_argument("File not found: " + filePath);
    }
    vector<string> lines;
    string currentLine;
    while(getline (file, currentLine))
    {
        lines.push_back(currentLine);
    }
    file.close();
    return lines;
}

void FileIOUtility::writeLine(string filePath, string line, int lineNumber)
{
    vector<string> lines = readLines(filePath);
    stringstream outStream;

    for (int i = 0; i < lines.size(); i++)
    {
        if (i == lineNumber - 1)
        {
            outStream << line << endl;
        }
        else
        {
            outStream << lines[i] << endl;
        }
    }

    ofstream outFile (filePath);
    outFile << outStream.rdbuf();
}

void FileIOUtility::writeLines(string filePath, vector<string> lines)
{
    stringstream outStream;

    for (string line : lines)
    {
        outStream << line << endl;
    }

    ofstream outFile (filePath);
    outFile << outStream.rdbuf();
}
}
