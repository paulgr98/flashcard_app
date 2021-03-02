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

void QuizManager::flush()
{
    std::wcin.clear();
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool QuizManager::loadQuestions()
{
    setPath();
    if(m_question_manager.loadFromJson(m_path))
    {
        m_questions = m_question_manager.getAllQuestions();
        m_initial_questions_size = m_questions.size();
        return true;
    }

    return false;
}
//TODO: checkAnswer method
void QuizManager::printRandomQuestion()
{
    if(!m_questions.empty())
    {
        m_tries++;
        auto rand_quest_it = std::next(std::begin(m_questions),
                                       m_random.get(0, m_questions.size() - 1));

        std::wcout << L"\n Left: ";
        setFontColor(FontColor::purple);
        std::wcout << m_questions.size() << L'/' << m_initial_questions_size << L'\n';
        setFontColor(FontColor::white);

        std::wcout << L"\t\t" << rand_quest_it->first << L'\n';
        std::wcout << L"> ";
        std::wstring user_ans{};
        std::getline(std::wcin, user_ans);


        if(user_ans == rand_quest_it->second)
        {
            m_questions.erase(rand_quest_it);

            setFontColor(FontColor::green);
            std::wcout << L"\tGood answer!" << L'\n';
            setFontColor(FontColor::white);
            std::this_thread::sleep_for(1s);
        }
        else
        {
            setFontColor(FontColor::red);
            std::wcout << L"\tBad answer :/" << L'\n';
            setFontColor(FontColor::white);

            std::wcout << L"\tCorrect answer: ";
            setFontColor(FontColor::cyan);
            std::wcout << rand_quest_it->second << L'\n';
            setFontColor(FontColor::white);

            std::wcin.get();
        }
    }
}

void QuizManager::printSummary() const
{
    setFontColor(FontColor::cyan);
    std::wcout << L"\n\tTHE END!" << L"\n\n";
    setFontColor(FontColor::white);

    std::wcout << L" Tries: " << m_tries << L'\n';
    float accuracy = round(((float)m_initial_questions_size / (float)m_tries) * 100.0f);
    std::wcout << " Accuracy: ";

    if(accuracy >= 80) setFontColor(FontColor::green);
    else if(accuracy >= 50 && accuracy < 80) setFontColor(FontColor::cyan);
    else setFontColor(FontColor::red);

    std::wcout << accuracy << L"%\n";
    setFontColor(FontColor::white);

    std::wcin.get();
}

void QuizManager::setPath()
{
    QuizManager::setFontColor(FontColor::cyan);
    std::wcout << L"\n Path to questions file (default is questions.json): ";
    QuizManager::setFontColor(FontColor::white);
    std::getline(std::cin, m_path);

    m_path.erase(remove_if(m_path.begin(), m_path.end(), isspace), m_path.end());
    if(m_path.empty())
    {
        m_path = "questions.json";
    }

    system("cls");
}

std::string QuizManager::getPath() const
{
    return m_path;
}
