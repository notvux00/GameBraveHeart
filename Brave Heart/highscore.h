#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>


struct Highscore {
    int score;
};

bool compareScore(const Highscore& a, const Highscore& b) {
    return a.score > b.score;
}

std::vector<Highscore> readHighscoresFromFile(const std::string& filename) {
    std::vector<Highscore> highscores;
    std::ifstream file(filename);

    if (file.is_open()) {
        int score;
        while (file >> score) {
            highscores.push_back({score});
        }
        file.close();
    }

    std::sort(highscores.begin(), highscores.end(), compareScore);

    return highscores;
}

void writeHighscoresToFile(const std::string& filename, const std::vector<Highscore>& highscores) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (const auto& highscore : highscores) {
            file << highscore.score << std::endl;
        }
        file.close();
    }
}


#endif // HIGHSCORE_H

