//
// Created by bogdan on 18.11.2023.
//

#include <iostream>
#include <vector>

class AnalysisCode {
private:
    std::vector<std::string> extension{"cpp", "hpp", "c", "h"};
    std::vector<std::string> stopDirectories{"build", "cmake-build-debug", "vendor", "Vendor", "out", "cmake"};
    bool hasEnding(const std::string& currentFile, const std::string& str);
    bool hasDirectory(const std::string& currentFile, const std::string& directory);
public:
    int getCountOfLines(const std::string& path);
    int process(const std::string& path);
    int getMaxFile(const std::string& path);
    int getCountOfSymbols();
};
