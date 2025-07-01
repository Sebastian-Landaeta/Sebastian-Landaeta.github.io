#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

bool checkLeft(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        --col;
        return checkLeft(word, grid, col, row);
    }
    return false;
}

bool checkRight(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        ++col;
        return checkRight(word, grid, col, row);
    }
    return false;
}

bool checkUp(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        --row;
        return checkUp(word, grid, col, row);
    }
    return false;
}

bool checkDown(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        ++row;
        return checkDown(word, grid, col, row);
    }
    return false;
}

bool checkDiDown(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        ++col;
        ++row;
        return checkDiDown(word, grid, col, row);
    }
    return false;
}

bool checkDiUp(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        --col;
        --row;
        return checkDiUp(word, grid, col, row);
    }
    return false;
}

bool checkDiDownAlt(list<string> word, vector<vector<string>> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        --col;
        ++row;
        return checkDiDownAlt(word, grid, col, row);
    }
    return false;
}

bool checkDiUpAlt(list<string> word, vector<vector<string >> &grid, int col, int row) {
    int wordLength = word.size();
    if (wordLength == 0) {
        return true;
    }
    string curChar = word.front();
    word.pop_front();
    if (curChar == grid[row][col]) {
        ++col;
        --row;
        return checkDiUpAlt(word, grid, col, row);
    }
    return false;
}

bool checkWord(int colNum, int rowNum, string word, vector<vector<string >> &grid) {
    list<string> wordLst;
    for (unsigned int i = 0; i < word.size(); i++) {
        string tempStr(1, word[i]);
        wordLst.push_back(tempStr);
    }
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < colNum; j++) {
            int wordLength = word.size();
            bool haveFound = false;
            if (j - wordLength >= -1) {
                haveFound = haveFound || checkLeft(wordLst, grid, j, i);
            }
            if (j + wordLength <= colNum) {
                haveFound = haveFound || checkRight(wordLst, grid, j, i);
            }
            if (i - wordLength >= -1) {
                haveFound = haveFound || checkUp(wordLst, grid, j, i);
            }
            if (i + wordLength <= rowNum) {
                haveFound = haveFound || checkDown(wordLst, grid, j, i);
            }
            if (j - wordLength >= -1 && i - wordLength >= -1) {
                haveFound = haveFound || checkDiUp(wordLst, grid, j, i);
            }
            if (j + wordLength <= colNum && i + wordLength <= rowNum) {
                haveFound = haveFound || checkDiDown(wordLst, grid, j, i);
            }
            if (j - wordLength >= -1 && i + wordLength <= rowNum) {
                haveFound = haveFound || checkDiDownAlt(wordLst, grid, j, i);
            }
            if (j + wordLength <= colNum && i - wordLength >= -1) {
                haveFound = haveFound || checkDiUpAlt(wordLst, grid, j, i);
            }
            if (haveFound) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<string>> makeBoard(int rowNum, int colNum) {
    vector<vector<string >> temp;
    for (int i = 0; i < rowNum; i++) {
        vector<string> tempRow(colNum, "0");
        temp.push_back(tempRow);
    }
    return temp;
}

bool addWord(string word, vector<vector<string>> &grid, int row, int col) {
    int wordLength = word.size();
    if (col + wordLength > grid[row].size()) {
        return false;
    }
    for (int i = 0; i < word.size(); i++) {
        int colHold = col + i;
        string tempStr(1, word[i]);
        if (grid[row][colHold] == "0" || grid[row][colHold] == tempStr) {
            grid[row][colHold] = tempStr;
        } else {
            for (int j = i - 1; j >= 0; j--) {
                int restoreColPos = col + j;
                grid[row][restoreColPos] = "0";
            }
            return false;
        }
    }
    return true;
}

bool addWordAlt(string word, vector<vector<string>> &grid, int row, int col) {
    int wordLength = word.size();
    if (row + wordLength > grid.size()) {
        return false;
    }
    for (int i = 0; i < word.size(); i++) {
        int rowHold = row + i;
        string tempStr(1, word[i]);
        if (grid[rowHold][col] == "0" || grid[rowHold][col] == tempStr) {
            grid[rowHold][col] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                int restoreRowPos = row + j;
                grid[restoreRowPos][col] = "0";
            }
            return false;
        }
    }
    return true;
}

bool addWordDi(string word, vector<vector<string>> &grid, int row, int col) {
    int wordLength = word.size();
    if (row + wordLength > grid.size() || col + wordLength > grid[row].size()) {
        return false;
    }
    for (int i = 0; i < word.size(); i++) {
        int rowHold = row + i;
        int colHold = col + i;
        string tempStr(1, word[i]);
        if (grid[rowHold][colHold] == "0" || grid[rowHold][colHold] == tempStr) {
            grid[rowHold][colHold] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                int restoreRowPos = row + j;
                int restoreColPos = col + j;
                grid[restoreRowPos][restoreColPos] = "0";
            }
            return false;
        }
    }
    return true;
}

bool addWordDiAlt(string word, vector<vector<string>> &grid, int row, int col) {
    int wordLength = word.size();
    if (row - wordLength < -1 || col + wordLength > grid[row].size()) {
        return false;
    }
    for (int i = 0; i < word.size(); i++) {
        int rowHold = row - i;
        int colHold = col + i;
        string tempStr(1, word[i]);
        if (grid[rowHold][colHold] == "0" || grid[rowHold][colHold] == tempStr) {
            grid[rowHold][colHold] = tempStr;
        } else {
            // undo the modifications on the matrix
            for (int j = i - 1; j >= 0; j--) {
                int restoreRowPos = row - j;
                int restoreColPos = col + j;
                grid[restoreRowPos][restoreColPos] = "0";
            }
            return false;
        }
    }
    return true;
}

bool wordAddingChecker(list<string> targets, int colNum, int rowNum, vector<vector<vector<string>>> &res, int col, int row, vector<vector<string>> gridHold) {
    if (targets.size() == 0) {
        return true;
    }
    vector<vector<string>> grid = gridHold;
    string word = targets.front();
    targets.pop_front();
    bool wordExist = checkWord(colNum, rowNum, word, gridHold);
    if (!wordExist) {
        for (int k = 0; k <= 1; k++) {
            for (int i = 0; i < rowNum; i++) {
                for (int j = 0; j < colNum; j++) {

                    bool horReturn = addWord(word, gridHold, i, j);
                    if (horReturn) {
                        bool addRet = wordAddingChecker(targets, colNum, rowNum, res, i, j, gridHold);
                        if (addRet) {
                            res.push_back(gridHold);
                        }
                    }
                    gridHold = grid;

                    bool verReturn = addWordAlt(word, gridHold, i, j);
                    if (verReturn) {
                        bool addRet = wordAddingChecker(targets, colNum, rowNum, res, i, j, gridHold);
                        if (addRet) {
                            res.push_back(gridHold);
                        }
                    }
                    gridHold = grid;

                    bool mainDiaReturn = addWordDi(word, gridHold, i, j);
                    if (mainDiaReturn) {
                        bool addRet = wordAddingChecker(targets, colNum, rowNum, res, i, j, gridHold);
                        if (addRet) {
                            res.push_back(gridHold);
                        }
                    }
                    gridHold = grid;

                    bool subDiaReturn = addWordDiAlt(word, gridHold, i, j);
                    if (subDiaReturn) {
                        bool addRet = wordAddingChecker(targets, colNum, rowNum, res, i, j, gridHold);
                        if (addRet) {
                            res.push_back(gridHold);
                        }
                    }
                }
            }
            reverse(word.begin(), word.end());
        }
    }
    return false;
}

void addWordDriver(list<string> &targets, int colNum, int rowNum, vector<vector<vector<string>>> &res) {
    vector<vector<string>> gridHold = makeBoard(rowNum, colNum);
    wordAddingChecker(targets, colNum, rowNum, res, 0, 0, gridHold);
}

bool fillGrid(vector<vector<vector<string>>> &res, int rowNum, int colNum, int row, int col, vector<vector<string>> tempVec, vector<string> &forbidWord) {
    if (row == rowNum) {
        // check if the grid have existed
        for (int i = 0; i < res.size(); i++) {
            if (tempVec == res[i]) {
                return false;
            }
        }

        string word;
        for (int i = 0; i < forbidWord.size(); i++) {
            word = forbidWord[i];
            bool wordExist = checkWord(colNum, rowNum, word, tempVec);
            if (wordExist) {
                return false;
            }
        }

        res.push_back(tempVec);
        return true;
    }
    if (col == colNum) {
        col = 0;
        row++;
        return fillGrid(res, rowNum, colNum, row, col, tempVec, forbidWord);
    }
    if (tempVec[row][col] == "0") {
        for (int i = 97; i <= 122; i++) {
            char charAscii = static_cast<char>(i);
            string strAsc(1, charAscii);
            tempVec[row][col] = strAsc;
            fillGrid(res, rowNum, colNum, row, col + 1, tempVec, forbidWord);
        }
    }
    return fillGrid(res, rowNum, colNum, row, col + 1, tempVec, forbidWord);
}

void cleanForbidGrid(vector<vector<vector<string>>> &res, vector<string> &forbidWord, int rowNum, int colNum) {
    vector<vector<vector<string>>>::iterator it = res.begin();
    while (it != res.end()) {
        vector<vector<string>> curVec = (*it);
        bool wordExist = false;
        for (int i = 0; i < forbidWord.size(); i++) {
            string word = forbidWord[i];
            wordExist = checkWord(colNum, rowNum, word, curVec);
            if (wordExist) {
                break;
            }
        }
        if (wordExist) {
            res.erase(it);
        } else {
            it++;
        }
    }
}

int main(int argc, char *argv[]) {
    ifstream in_str(argv[1]);
    if (in_str.good()) {
        list<string> targets;
        vector<string> forbidWord;
        string col = "0";
        in_str >> col;
        int colNum = stoi(col);
        string row = "0";
        in_str >> row;
        int rowNum = stoi(row);
        string x;
        string word;
        while (in_str >> x) {
            in_str >> word;
            if (x == "+") {
                targets.push_back(word);
            } else {
                forbidWord.push_back(word);
            }
        }
        vector<vector<vector<string>>> res;
        addWordDriver(targets, colNum, rowNum, res);

        cleanForbidGrid(res, forbidWord, rowNum, colNum);

        vector<vector<vector<string>>>::iterator iti = res.begin();
        while (iti != res.end()) {
            vector<vector<vector<string>>>::iterator itj = ++iti;
            iti--;
            while (itj != res.end()) {
                if ((*iti) == (*itj)) {
                    res.erase(itj);
                } else {
                    itj++;
                }
            }
            iti++;
        }

        for (int i = 0; i < res.size(); i++) {
            vector<vector<string>> curGrid = res[i];
            fillGrid(res, rowNum, colNum, 0, 0, curGrid, forbidWord);
        }

        cleanForbidGrid(res, forbidWord, rowNum, colNum);

        vector<vector<vector<string>>>::iterator it = res.begin();
        while (it != res.end()) {
            vector<vector<string>> curVec = (*it);
            bool hasZero = false;
            for (int i = 0; i < curVec.size(); i++) {
                for (int j = 0; j < curVec[i].size(); j++) {
                    if (curVec[i][j] == "0") {
                        hasZero = true;
                    }
                }
            }
            if (hasZero) {
                res.erase(it);
            } else {
                it++;
            }
        }

        ofstream out_str(argv[2]);
        if (out_str.good()) {
            if (res.size() == 0) {
                out_str << "No solutions found";
            } else {
                string numSol(argv[3]);
                if (numSol != "one_solution") {
                    out_str << res.size() << " solution(s)" << endl;
                }
                for (int i = 0; i < res.size(); i++) {
                    out_str << "Board: " << std::endl;
                    vector<vector<string>> curVec = res[i];
                    for (int j = 0; j < curVec.size(); j++) {
                        out_str << "  ";
                        for (int k = 0; k < curVec[j].size(); k++) {
                            out_str << curVec[j][k];
                        }
                        out_str << endl;
                    }
                    if (numSol == "one_solution") {
                        break;
                    }
                }
            }
        }
    }
}