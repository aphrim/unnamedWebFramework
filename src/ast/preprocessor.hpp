/* PreProcessor for <Unnamed Web Framework>
 * For now, primarily handles includes
 * Will handle macros in the future.
 */
#include <string>
#include <map>
#include <utility>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

#pragma once

using namespace std;
namespace fs = filesystem;

class PreProcessor {
public:

    PreProcessor(string path, map<string, string>* includedFiles);

    void process();

private:

    int m_line;

    stringstream m_code;
    string m_curPath;
    map<string, string>* m_includedFiles;

    void processLine(string line);
    bool isStringMatch(string target, string line);

    void processImport(string line);
};
