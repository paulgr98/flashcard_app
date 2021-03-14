#pragma once

#include "../headers/QuestionManager.h"

enum class Mode {New, Append, Edit, Delete};

class QuestionEditor
{
private:
    QuestionManager m_QM;
public:
    QuestionEditor() : m_QM(QuestionManager()) {}

    static void printDescription();
    void setPath();
    static Mode processMenu();
    void makeQuestions();
    void loadQuestions();
    void editQuestions();
    void deleteQuestion();
    bool saveToFile();
};
