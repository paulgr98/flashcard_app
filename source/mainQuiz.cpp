#include "../headers/QuizManager.h"
#include <chrono>
#include <thread>

int main()
{
    using namespace std::chrono_literals;
    auto quiz = QuizManager();

    if(quiz.loadQuestions())
    {
        while (quiz.getQuestionsSize() > 0)
        {
            quiz.printRandomQuestion();
            std::this_thread::sleep_for(1s);
            system("cls");
        }
        quiz.printSummary();
    }
}