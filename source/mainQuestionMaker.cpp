#include "../headers/QuestionManager.h"

void printDescription()
{
    std::cout << " - Type question and press ENTER to continue" << '\n';
    std::cout << " - Type answer and press ENTER to continue" << '\n';
    std::cout << " - If you want to save and exit, left question" << '\n';
    std::cout << "\tor answer blank, and press ENTER" << '\n';
}

std::string processMenu()
{
    std::string choice{};
    while(true)
    {
        std::cout << '\n';
        printDescription();
        std::cout << '\n';

        std::cout << "\t1. Create new file with questions" << '\n';
        std::cout << "\t2. Append existing file with questions" << '\n';
        std::cout << "> ";


        std::getline(std::cin, choice);

        if(choice == "1" || choice == "2")
        {
            return choice;
        }
        else
        {
            std::cout << '\n';
            std::cout << "There is no option: " << choice << '\n';
            std::cin.get();
            system("cls");
        }
    }
}

int main()
{
    auto qm = QuestionManager();
    qm.setPath();

    if(processMenu() == "2")
    {
        if(!qm.loadFromJson())
        {
            std::cout << '\n';
            std::cerr << "Cannot open file " << qm.getPath() << " to append" << '\n';
            std::cerr << "Make sure the file exists" << '\n';
            std::cin.get();
        }
    }

    system("cls");
    do
    {
        qm.makeQuestion();
    }while(!qm.getQuestion().empty() || !qm.getAnswer().empty());

    if(!qm.getAllQuestions().empty())
    {
        qm.saveToJson();
    }
}