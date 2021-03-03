#pragma once

#include <string>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../additional_libraries/nlohmann/json.hpp"

using json = nlohmann::json;
using QuestionContainer = std::unordered_map<std::wstring, std::wstring>;

//TODO: question editor
class QuestionManager
{
private:
    std::wstring m_question{};
    std::wstring m_answer{};
    QuestionContainer m_allQuestions{};
    std::string m_path{"questions.json"};

public:
    QuestionManager();

    void setQuestion();
    void setAnswer();

    void setPath();
    std::string getPath() const;

    [[nodiscard]] std::wstring getQuestion() const;
    [[nodiscard]] std::wstring getAnswer() const;

    void makeQuestion();
    bool saveToJson(const std::string& path) const;
    bool saveToJson() const;
    bool loadFromJson(const std::string& path);
    bool loadFromJson();
    void printQuestions() const;
    QuestionContainer getAllQuestions() const;
};



