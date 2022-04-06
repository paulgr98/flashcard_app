#include "../headers/QuestionManager.h"
#include "../headers/Utility.h"

enum class Mode {New, Append, Edit, Exit};

class QuestionEditor
{
private:
    QuestionManager m_QM;
public:
    QuestionEditor() : m_QM(QuestionManager()) {}

    static void printDescription()
    {
        std::cout << " - Type question and press ENTER to continue" << '\n';
        std::cout << " - Type answer and press ENTER to continue" << '\n';
        std::cout << " - If you want to save and exit, left question" << '\n';
        std::cout << "\tor answer blank, and press ENTER" << '\n';
        std::cout << " - While editing question, you can left blank" << '\n';
        std::cout << "\tfield to assign old value" << '\n';
    }

    void setPath()
    {
        m_QM.setPath();
    }

    QuestionManager& getQM()
    {
        return m_QM;
    }

    static Mode processMenu()
    {
        std::string choice{};
        while(true)
        {
            std::cout << '\n';
            printDescription();
            std::cout << '\n';

            std::cout << "\t1. Create new file with questions" << '\n';
            std::cout << "\t2. Append existing file with questions" << '\n';
            std::cout << "\t3. Edit existing questions" << '\n';
            std::cout << "\t4. Exit" << '\n';
            std::cout << "> ";


            std::getline(std::cin, choice);
            choice = Utility::trim(choice);

            if(choice == "1")
            {
                return Mode::New;
            }
            else if(choice == "2")
            {
                return Mode::Append;
            }
            else if(choice == "3")
            {
                return Mode::Edit;
            }
            else if(choice == "4")
            {
                return Mode::Exit;
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

    void makeQuestions()
    {
        do
        {
            m_QM.makeQuestion();
        }while(!m_QM.getQuestion().empty() || !m_QM.getAnswer().empty()); //make questions until q or a field is empty
    }

    void loadQuestions()
    {
        if(!m_QM.loadFromJson())
        {
            std::cout << '\n';
            std::cerr << " Cannot open file " << m_QM.getPath() << " to append" << '\n';
            std::cerr << " Make sure the file exists" << '\n';
            std::cin.get();
        }
    }

    void editQuestions()
    {
        if(!m_QM.getAllQuestions().empty())
        {
            std::cout << " Choose question to edit: " << "\n\n";
            m_QM.printAllQuestions();
            std::cout << "> ";

            int choice{};
            try
            {
                std::cin >> choice;
            }
            catch(std::exception& e)
            {
                throw e;
            }

            //get specific question
            auto quest_it = std::next(m_QM.getAllQuestions().begin(), choice - 1);
            auto quest_encoded_it = std::next(m_QM.getAllQuestionsEncoded().begin(), choice - 1);
            std::wcout << L"\n " << quest_it->first << L" : " << quest_it->second << L'\n';

            Utility::flush();

            //get edited question
            std::wcout << L"Question: ";
            std::wstring new_qest{};
            std::getline(std::wcin, new_qest);
            new_qest = Utility::trim(new_qest);
            if(new_qest.empty()) new_qest = quest_it->first; //if edited question was empty, use the old one


            //get edited answer
            std::wcout << L"Answer: ";
            std::wstring new_answer{};
            std::getline(std::wcin, new_answer);
            new_answer = Utility::trim(new_answer);
            if(new_answer.empty()) new_answer = quest_it->second; //if edited answer was empty, use the old one

            //delete chosen question
            m_QM.getAllQuestions().erase(quest_it);
            m_QM.getAllQuestionsEncoded().erase(quest_encoded_it);

            //add edited question
            m_QM.getAllQuestions().insert({new_qest, new_answer});
            m_QM.getAllQuestionsEncoded().insert({Utility::utf8_encode(new_qest), Utility::utf8_encode(new_answer)});
        }
    }

    bool saveToFile()
    {
        if(!m_QM.getAllQuestions().empty()) //save to file if there is something to change
        {
            m_QM.saveToJson();
            return true;
        }
        return false;
    }
};

int main()
{
    auto qe = QuestionEditor();
    qe.setPath();
    system("cls");

    Mode mode;
    do
    {
        mode = QuestionEditor::processMenu();
        switch (mode) {
            case Mode::New:
                system("cls");
                qe.makeQuestions();
                break;

            case Mode::Append:
                system("cls");
                if(qe.getQM().getAllQuestions().empty())
                {
                    qe.loadQuestions();
                }
                qe.makeQuestions();
                break;

            case Mode::Edit:
                system("cls");
                if(qe.getQM().getAllQuestions().empty())
                {
                    qe.loadQuestions();
                }
                qe.editQuestions();
                break;

            case Mode::Exit:
                break;
        }
        system("cls");
    } while(mode != Mode::Exit);

    if(!qe.saveToFile())
    {
        std::cerr << "\n There was no questions to save" << '\n';
        std::cin.get();
    }
}