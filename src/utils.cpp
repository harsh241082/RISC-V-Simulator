#include "../include/utilis.h"

std::vector<std::string> tokenize(std::string &line)
{
    std::vector<std::string> tokens;
    std::string token = "";
    std::string label;
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
    if (index != std::string::npos)
    {
        tokens.resize(4);
        std::string token = tokens[2];
        std::string newToken = "";
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
            std::string temp = tokens[2];
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

int strToInt(const std::string &num)
{
    int32_t i = 0;
    if (num[0] == '-')
    {
        std::string token = "";
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
        std::string token = "";
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

int rigToInt(const std::string &num)
{
    std::string token = "";
    for (int i = 1; i < num.length(); i++)
        token += num[i];

    return stoi(token);
}

std::vector<std::string> split(const std::string &str)
{
    std::vector<std::string> words;
    std::istringstream iss(str);
    std::string word;
    while (iss >> word)
    {
        words.push_back(word);
    }
    return words;
}