#include "../headers/QuizManager.h"

void QuizManager::setFontColor(const FontColor color)
{
    auto hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

unsigned int QuizManager::getQuestionsSize() const
{
    return m_questions.size();
}

/*
void QuizManager::flush()
{
    std::wcin.clear();
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
*/

bool QuizManager::loadQuestions()
{
    if(m_question_manager.loadFromJson())
    {
        m_questions = m_question_manager.getAllQuestions();
        return true;
    }

    return false;
}

void QuizManager::printRandomQuestion()
{
    if(!m_questions.empty())
    {
        auto rand_quest_it = std::next(std::begin(m_questions),
                                       m_random.get(0, m_questions.size() - 1));

        std::wcout << L'\t' << rand_quest_it->first << L'\n';
        std::wcout << L"> ";

        std::wstring user_ans{};
        std::getline(std::wcin, user_ans);


        if(user_ans == rand_quest_it->second)
        {
            m_questions.erase(rand_quest_it);
            std::wcout << L"Good answer!" << L'\n';
        }
        else
        {
            std::wcout << L"Bad answer :/" << L'\n';
        }
    }
}
//TODO: implement accuracy atc.
void QuizManager::printSummary()
{
    std::wcout << L"THE END!" << L'\n';
    std::wcin.get();
}
