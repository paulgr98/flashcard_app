#pragma once
#include "MyRandom.h"
#include "QuestionManager.h"
#include <iostream>
#include <limits>
#include <chrono>
#include <thread>
#include <windows.h>
#undef max //get rid of max macro from windows.h

enum class FontColor { green = 2, cyan = 11, red = 12, purple = 13, white = 15};

using namespace std::chrono_literals; //definitions of s, ms, ...

class QuizManager
{
private:
    MyRandom m_random; //random number generator used to get random questions
    unsigned int m_initial_questions_size; //number of all questions
    QuestionManager m_question_manager;
    QuestionContainer m_questions;
    std::string m_path{"questions.json"}; //default path used to read questions
    unsigned int m_tries{0}; //number of queses including good and bad answers

public:
    QuizManager() = default;
    unsigned int getQuestionsSize() const; //get number of questions that left

    static void setFontColor(const FontColor color);
    static void flush();
    bool loadQuestions(const std::string& path);
    bool loadQuestions();
    void printRandomQuestion();
    void printSummary() const;

    void setPath();
    std::string getPath() const;
};



