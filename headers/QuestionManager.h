#pragma once

#include <string>
#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "../additional_libraries/nlohmann/json.hpp"
#include "Utility.h"

using json = nlohmann::json;
using QuestionContainer = std::unordered_map<std::wstring, std::wstring>;
using QuestionContainerEncoded = std::unordered_map<std::string, std::string>;

//TODO: question editor
class QuestionManager
{
private:
    std::wstring m_question{}; //question typed by user
    std::wstring m_answer{}; //answer typed by user
    std::string m_question_encoded{}; //encoded question with utf-8
    std::string m_answer_encoded{}; //encoded answer with utf-8
    QuestionContainer m_allQuestions{}; //stores answers mapped to questions
    QuestionContainerEncoded m_allQuestionsEncoded{}; //stores answers mapped to questions (encoded)
    std::string m_path{"questions.json"}; //path to file with questions

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
    void printAllQuestions() const;
    QuestionContainer& getAllQuestions();
    QuestionContainerEncoded& getAllQuestionsEncoded();
};



