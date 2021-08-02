//
// Created by ZhouP on 4/4/2019.
//

#ifndef CPPSANDBOX_WORDLADDER_H
#define CPPSANDBOX_WORDLADDER_H

#include "../include/datastructure.h"

int ladderLength(std::string beginWord, std::string endWord, Strings& wordList) {
    std::unordered_set<std::string> dict(wordList.begin(), wordList.end());
    std::queue<std::string> todo;
    todo.push(beginWord);
    int ladder = 1;
    while (!todo.empty()) {
        int n = todo.size();
        for (int i = 0; i < n; i++) {
            std::string word = todo.front();
            todo.pop();
            if (word == endWord) {
                //if you will need to know the path, then hold the path in another queue
                return ladder;
            }
            dict.erase(word);
            for (int j = 0; j < word.size(); j++) {
                char c = word[j];       // save the alphabet
                for (int k = 0; k < 26; k++) {
                    word[j] = 'a' + k;
                    if (dict.find(word) != dict.end()) {
                        todo.push(word);
                    }
                }
                word[j] = c;
            }
        }
        ladder++;
    }
    return 0;
}

void test_wordladder()
{
    std::string beginWord = "hit";
    std::string endWord = "cog";
    Strings wordList = {"hot","dot","dog","lot","log","cog"};
    // Use the breath first search
    std::cout << ladderLength (beginWord, endWord, wordList) << std::endl;
}

#endif //CPPSANDBOX_WORDLADDER_H
