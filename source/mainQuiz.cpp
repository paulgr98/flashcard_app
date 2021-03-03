#include "../headers/QuizManager.h"


int main()
{
    auto quiz = QuizManager();
    quiz.setPath();

    if(quiz.loadQuestions())
    {
        while (quiz.getQuestionsSize() > 0) //get questions until there are any
        {
            quiz.printRandomQuestion();
            system("cls");
        }
        quiz.printSummary();
    }
    else
    {
        std::cerr << "Cannot open file in path: ";
        QuizManager::setFontColor(FontColor::red);
        std::cerr << quiz.getPath() << '\n';
        QuizManager::setFontColor(FontColor::white);
        std::cerr << "Check if the path is correct" << '\n';

        QuizManager::flush();
        std::wcin.get();
    }
}