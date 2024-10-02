#include "../include/utilis.h"

using namespace std;

vector<string> tokenize(string &line)
{
    vector<string> tokens;
    string token = "";
    string label;
    while (line[0] == ' ')
    {
        line.erase(0, 1);
    }
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == '#' || line[i] == ';')
        {
            if (tokens.size() == 0)
            {
                return tokens;
            }
            if (tokens[0] == "")
            {
                tokens.resize(0);
            }
        }
        if (line[i] == ',')
            continue;
        if (line[i] == ':')
        {
            label = token;
            token = "";
            i++;
            labelData.insert({label, ProgramCounter});
            continue;
        }
        if (line[i] == ' ')
        {
            tokens.push_back(token);
            token = "";
            continue;
        }
        token += line[i];
    }
    tokens.push_back(token);
    if (tokens.size() == 0)
    {
        return tokens;
    }
    size_t index = tokens[2].find("(");
    if (index != string::npos)
    {
        tokens.resize(4);
        string token = tokens[2];
        string newToken = "";
        int j;
        for (j = 0; j < token.length(); j++)
        {
            if (token[j] == '(')
            {
                tokens[3] = newToken;
                newToken = "";
                break;
            }
            newToken += token[j];
        }
        for (j++; j < token.length(); j++)
        {
            if (token[j] == ')')
            {
                tokens[2] = (newToken);
                token = newToken;
                break;
            }
            newToken += token[j];
        }
        if (tokens[3][0] == 'x')
        {
            string temp = tokens[2];
            tokens[2] = tokens[3];
            tokens[3] = temp;
        }
    }
    while (*tokens[0].end() == ' ')
    {
        tokens[0].pop_back();
    }
    while (*tokens[0].begin() == ' ')
    {
        tokens[0].erase(0, 1);
    }
    return tokens;
}

int strToInt(const string &num)
{
    int32_t i = 0;
    if (num[0] == '-')
    {
        string token = "";
        for (int j = 1; j < num.length(); j++)
        {
            token += num[j];
        }
        if (token[1] == 'x')
            i = stoi(token.substr(2, num.length() - 2), nullptr, 16);
        else if (token[1] == 'b')
            i = stoi(token.substr(2, num.length() - 2), nullptr, 2);
        else
            i = stoi(token);
        i *= -1;
    }
    else
    {
        string token = "";
        for (int j = 0; j < num.length(); j++)
        {
            token += num[j];
        }
        if (token[1] == 'x')
            i = stoi(token.substr(2, num.length() - 2), nullptr, 16);
        else if (token[1] == 'b')
            i = stoi(token.substr(2, num.length() - 2), nullptr, 2);
        else
            i = stoi(token);
    }
    return i;
}

int rigToInt(const string &num)
{
    string token = "";
    for (int i = 1; i < num.length(); i++)
        token += num[i];

    return stoi(token);
}