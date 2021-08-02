//
// Created by ZhouP on 3/20/2019.
//

#ifndef CPPSANDBOX_WORLDSEARCH_H
#define CPPSANDBOX_WORLDSEARCH_H

#include "../include/datastructure.h"

void internal_search_word_1(int i, int j, int row, int col, HSInt& hp, std::vector<std::vector<char>>& board, std::string word, const Trie& aTrie, std::set<std::string>& collected)
{
    if (i<0 || j<0|| i>=row || j>=col)
    {
        return;
    }
    else if (hp.find(i*col+j)!=hp.end())
    {
        return;
    }
    else if (aTrie.startsWith(word))
    {
        if (aTrie.search(word))
            collected.insert(word);

        word = word + board[i][j];
        hp.emplace(i*col+j);
        internal_search_word_1 (i-1, j, row, col, hp, board, word, aTrie, collected);
        internal_search_word_1 (i+1, j, row, col, hp, board, word, aTrie, collected);
        internal_search_word_1 (i, j-1, row, col, hp, board, word, aTrie, collected);
        internal_search_word_1 (i, j+1, row, col, hp, board, word, aTrie, collected);
        hp.erase(i*col+j);
    }
    else
    {
        return;
    }
}

bool test_search_word_1(std::vector<std::vector<char>>& board, std::vector<std::string> words) {
    // search the words. First construct the trie??
    int height = board.size();
    int width = board.front().size();

    Trie aTrie;
    for (std::string str: words)
        aTrie.insert(str);

    std::set<std::string> collection;

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) {
            HSInt hp;
            internal_search_word_1(i, j, height, width, hp, board, "", aTrie, collection);
        }
    }

    printf("\n");
    for_each(collection.begin(), collection.end(), [&](std::string s) { printf ("%s, ", s.c_str());});
    printf("\n");
}

bool internal_search_word_2(int i, int j, int row, int col, HSInt& hp, std::vector<std::vector<char>>& board, std::string word)
{
    if (word.empty())
    {
        return true;
    }
    else if (i<0 || j<0|| i>=row || j>=col)
    {
        return false;
    }
    else if (hp.find(i*col+j)!=hp.end())
    {
        return false;
    }
    else if (board[i][j]==word[0])
    {
        std::string sub_word = word.substr(1);
        hp.emplace(i*col+j);
        if (internal_search_word_2 (i-1, j, row, col, hp, board, sub_word))
            return true;
        if (internal_search_word_2 (i+1, j, row, col, hp, board, sub_word))
            return true;
        if (internal_search_word_2 (i, j-1, row, col, hp, board, sub_word))
            return true;
        if (internal_search_word_2 (i, j+1, row, col, hp, board, sub_word))
            return true;
        hp.erase(i*col+j);
        return false;
    }
    else
    {
        return false;
    }
}

bool test_search_word_2(std::vector<std::vector<char>>& board, std::string word) {
    int height = board.size();
    int width = board.front().size();

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) {
            HSInt hp;
            if (internal_search_word_2(i, j, height, width, hp, board, word))
                return true;
        }
    }
    return false;
}

void test_search_word ()
{
//    board =
//    [
//    ['A','B','C','E'],
//    ['S','F','C','S'],
//    ['A','D','E','E']
//    ]
//
//    Given word = "ABCCED", return true.
//    Given word = "SEE", return true.
//    Given word = "ABCB", return false.

    std::vector<std::vector<char>> board(3);
    board[0] = {'A','B','C','E'};
    board[1] = {'S','F','C','S'};
    board[2] = {'A','D','E','E'};

//    std::string word("ABCCED");
//    std::string word("SEE");
//    std::string word("ABCB");
//    std::cout << "Given word = " << word << ", return " << std::boolalpha <<  test_search_word_2 (board, word) << std::endl;

    std::vector<std::string> words;
    words.reserve(3);
    words.push_back("ABCCED");
    words.push_back("SEE");
    words.push_back("ABCB");

    test_search_word_1 (board, words);
}

#endif //CPPSANDBOX_WORLDSEARCH_H
