#include "../headers/questionEditor.h"

int main()
{
    auto qe = QuestionEditor();
    qe.setPath();
    system("cls");

    try
    {
        switch (QuestionEditor::processMenu())
        {
            case Mode::New:
                system("cls");
                qe.makeQuestions();
                break;

            case Mode::Append:
                system("cls");
                qe.loadQuestions();
                qe.makeQuestions();
                break;

            case Mode::Edit:
                system("cls");
                qe.loadQuestions();
                qe.editQuestions();
                break;

            case Mode::Delete:
                system("cls");
                qe.loadQuestions();
                qe.deleteQuestion();
                break;
        }
    }
    catch (std::out_of_range &oor_exc)
    {
        std::cerr << "Error: question number incorrect" << '\n';
        Utility::flush();
        std::cin.get();
    }
    catch (std::exception &exc)
    {
        std::cerr << "Unknown error!" << '\n';
        std::cerr << exc.what() << '\n';
        Utility::flush();
        std::cin.get();
    }

    system("cls");

    if(!qe.saveToFile())
    {
        std::cerr << "\n There was no questions to save" << '\n';
        std::cin.get();
    }
}