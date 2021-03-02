#include "../headers/QuestionManager.h"

//TODO: appending mode
int main()
{
    auto qm = QuestionManager();

    do
    {
        qm.makeQuestion();
    }while(!qm.getQuestion().empty() || !qm.getAnswer().empty());

    if(!qm.getAllQuestions().empty())
    {
        qm.saveToJson();
    }
}