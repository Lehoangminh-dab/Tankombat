#include <iostream>
using namespace std;
int main() {
    string alphabetArray = "abcdefghijklmnopqrstuvwxyz";
    int alphabetArrayLength = 27;

    int characterCnt[27];
    for (int i = 0; i < 27; i++)
    {
        characterCnt[i] = 0;
    }

    int test_cnt;
    cin >> test_cnt;
    string s;
    string total_string = "";
    for (int test_case = 0; test_case < test_cnt; test_case++)
    {
        cin >> s;
        total_string += s;
    }
    
    for (int i = 0; i < (int)total_string.size(); i++)
    {
        for (int j = 0; j < alphabetArrayLength; j++)
        {
            if (total_string[i] == alphabetArray[j])
            {
                characterCnt[j]++;
                break;
            }
        }
    }

    for (int i = 0; i < 27; i++)
    {
        if (characterCnt[i] != 0)
        {
            cout << alphabetArray[i] << " : " << characterCnt[i] << endl;
        }
    }
    return 0;
}