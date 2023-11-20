//
// Created by bogdan on 18.11.2023.
//
#pragma once
#include "AnalysisCode.hpp"

#include <string>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

int AnalysisCode::getCountOfLines(const std::string& path) {
    std::string str;
    std::ifstream in(path);
    int ans = 0;
    while (!in.eof()) {
        std::getline(in, str, '\n');
        ans++;
    }
    in.close();
    std::cout << path << ' ' << ans << std::endl;
    return ans;
}

bool AnalysisCode::hasEnding(const std::string& currentFile, const std::string& ex) {
    int start;
    for (int i = currentFile.length() - 1; currentFile[i] != '.'; --i) {
        start = i;
    }
    if (currentFile.length() - start != ex.length()) return false;

    for (int i = 0; i < ex.length(); ++i) {
        if (currentFile[start++] != ex[i]) return false;
    }
    return true;
}

bool AnalysisCode::hasDirectory(const std::string& currentFile, const std::string& directory) {
    int start;
    for (int i = currentFile.length() - 1; currentFile[i] != '\\' && currentFile[i] != '/'; --i) {
        start = i;
    }
    if (currentFile.length() - start != directory.length()) return false;

    for (int i = 0; i < directory.length(); ++i) {
        if (currentFile[start++] != directory[i]) return false;
    }
    return true;
}

int AnalysisCode::process(const std::string& path) {
    int ans = 0;
    for (auto &p: fs::directory_iterator(path)) {
        std::string currentFile = p.path().string();
        if (fs::is_directory(currentFile)) {
            bool stop = false;
            for (int i = 0; i < stopDirectories.size(); ++i) {
                if (hasDirectory(currentFile, stopDirectories[i])) {
                    stop = true;
                    break;
                }
            }
            if (!stop) ans += process(currentFile);
            continue;
        }
        for (int i = 0; i < extension.size(); ++i) {
            if (hasEnding(currentFile, extension[i])) {
                ans += getCountOfLines(currentFile);
                break;
            }
        }
    }
    return ans;
}

int AnalysisCode::getMaxFile(const std::string& path) {
    int max = 0;
    for (auto &p: fs::directory_iterator(path)) {
        std::string currentFile = p.path().string();
        if (fs::is_directory(currentFile)) {
            bool stop = false;
            for (int i = 0; i < stopDirectories.size(); ++i) {
                if (hasDirectory(currentFile, stopDirectories[i])) {
                    stop = true;
                    break;
                }
            }
            if (!stop) max = std::max(max, getMaxFile(currentFile));
            continue;
        }
        for (int i = 0; i < extension.size(); ++i) {
            if (hasEnding(currentFile, extension[i])) {
                max = std::max(max, getCountOfLines(currentFile));
                break;
            }
        }
    }
    return max;
}

int AnalysisCode::getCountOfSymbols() {

}
