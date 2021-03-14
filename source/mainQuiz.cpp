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
        Utility::setFontColor(FontColor::red);
        std::cerr << quiz.getPath() << '\n';
        Utility::setFontColor(FontColor::white);
        std::cerr << "Check if the path is correct" << '\n';

        Utility::wflush();
        std::wcin.get();
    }
}