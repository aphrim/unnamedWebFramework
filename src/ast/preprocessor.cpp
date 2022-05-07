#include "preprocessor.hpp"

 PreProcessor::PreProcessor(string path, map<string, string>* includedFiles) :
    m_curPath(path)
{
    m_includedFiles = includedFiles;
    ifstream file;
    file.open(path, ios::in);
    string chunk;
    while (getline(file, chunk)) m_code << chunk << '\n';
    file.close();
}

void PreProcessor::process() {
    string line;
    m_code.seekg(0, ios::beg);
    while (getline(m_code, line)) {
        processLine(line);
    }
    m_code.seekg(0, ios::beg);
    (*m_includedFiles)[m_curPath] = m_code.str();
}

void PreProcessor::processLine(string line) {
    if (line.size() > 1 && line[0] == '#') {
        if (isStringMatch("import", line)) processImport(line); 
    }
}

bool PreProcessor::isStringMatch(string target, string line) {
    if (line.size() - 1 < target.size());
    for (int i = 0; i < target.size(); i++)
        if (line[i + 1] != target[i])
            return false;
    if (line.size() - 2 > target.size() && line[target.size() + 1] != ' ') return false;
    return true;
}

void PreProcessor::processImport(string line) {
    fs::path importPath = fs::path(m_curPath).parent_path();
    int charIndex = 0;
    while (charIndex < line.size() && line[charIndex] != ' ') charIndex++;
    importPath /= line.substr(charIndex + 1);
    if (m_includedFiles->find(importPath.string()) == m_includedFiles->end()) {
        PreProcessor proc = PreProcessor(importPath.string(), m_includedFiles);
        proc.process();
    }
}
