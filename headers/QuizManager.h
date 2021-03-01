#pragma once
#include "MyRandom.h"
#include "QuestionManager.h"
#include <iostream>
#include <limits>
#include <windows.h>
#undef max //get rid of max macro from windows.h

enum class FontColor { green = 2, blue = 11, red = 12, purple = 13, white = 15};

class QuizManager
{
private:
    MyRandom m_random; //random number generator used to get random questions
    unsigned int m_questions_size;
    QuestionManager m_question_manager;
    QuestionContainer m_questions;

public:
    QuizManager() = default;
    unsigned int getQuestionsSize() const;

    static void setFontColor(const FontColor color);
   //static void flush();
    bool loadQuestions();
    void printRandomQuestion();
    void printSummary();
};



