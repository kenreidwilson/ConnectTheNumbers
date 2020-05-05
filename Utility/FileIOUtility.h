#ifndef FILEIOUTILITY_H
#define FILEIOUTILITY_H

#include <string>
#include <vector>
using namespace std;

namespace Utility
{
class FileIOUtility
{
public:

    /**
    * Creates a file at the provided filePath
    *
    * @param the path to the file being created.
    */
    static void initializeFile(string filePath);

    /**
    * Returns a string representation of a line at the provided lineNumber from the provided file.
    *
    * @throw invalid_argument if lineNumber > lines in the file || file cannot be read.
    *
    * @param filePath the path to the file being read.
    * @param lineNumber the line number that the line is at.
    *
    * @return a string representation of a line at the provided lineNumber.
    */
    static string readLine(string filePath, int lineNumber);

    /**
    * Returns a string per line in a file stored in a vector.
    *
    * @throw invalid_argument if file cannot be read.
    *
    * @param the path to the file being created.
    *
    * @return a vector of strings that represent each line in the file.
    */
    static vector<string> readLines(string filePath);

    /**
    * Writes a string to the lineNumber in the provided file.
    * If the lineNumber > lines in the file, the line will be writtin to the last line.
    *
    * @throw invalid_argument if file cannot be read.
    *
    * @postcondition the current line of the file will be deleted.
    *
    * @param filePath the path to the file being writin to.
    * @param line the string that is being writtin to the file.
    * @param lineNumber the line number that the line is at.
    */
    static void writeLine(string filePath, string line, int lineNumber);

    /**
    * Replaces the file at the filePath with the lines provided.
    *
    * @throw invalid_argument if file cannot be read.
    *
    * @postcondition the file's original contents will be deleted.
    *
    * @param filePath the path to the file being writin to.
    * @param lines a vector of strings representing each line in the new file.
    */
    static void writeLines(string filePath, vector<string> lines);

private:
};
}
#endif // FILEIOUTILITY_H
