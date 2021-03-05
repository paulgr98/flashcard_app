#include "../headers/QuizManager.h"



unsigned int QuizManager::getQuestionsSize() const
{
    return m_questions.size();
}


bool QuizManager::loadQuestions(const std::string& path)
{
    if(m_question_manager.loadFromJson(path))
    {
        m_questions = m_question_manager.getAllQuestions();
        m_initial_questions_size = m_questions.size();
        return true;
    }

    return false;
}

bool QuizManager::loadQuestions()
{
    return loadQuestions(m_path);
}
//TODO: checkAnswer method
void QuizManager::printRandomQuestion()
{
    if(!m_questions.empty()) //if there are any questions
    {
        m_tries++;
        //random question iterator as std::pair
        auto rand_quest_it = std::next(std::begin(m_questions),
                                       m_random.get(0, m_questions.size() - 1));

        //questions left out of all
        std::wcout << L"\n Left: ";
        Utility::setFontColor(FontColor::purple);
        std::wcout << m_questions.size() << L'/' << m_initial_questions_size << L'\n';
        Utility::setFontColor(FontColor::white);

        //question
        std::wcout << L"\t\t" << rand_quest_it->first << L'\n';
        std::wcout << L"> ";

        //get answer from user
        std::wstring user_ans{};
        std::getline(std::wcin, user_ans);
        user_ans = Utility::trim(user_ans);


        if(user_ans == rand_quest_it->second) //ANSWER CORRECT
        {
            m_questions.erase(rand_quest_it); //if the answer was correct, remove that question

            Utility::setFontColor(FontColor::green);
            std::wcout << L"\tGood answer!" << L'\n';
            Utility::setFontColor(FontColor::white);
            std::this_thread::sleep_for(0.8s);
        }
        else //ANSWER NOT CORRECT
        {
            //if the answer was not correct, show the correct one
            Utility::setFontColor(FontColor::red);
            std::wcout << L"\tBad answer :/" << L'\n';
            Utility::setFontColor(FontColor::white);

            std::wcout << L"\tCorrect answer: ";
            Utility::setFontColor(FontColor::cyan);
            std::wcout << rand_quest_it->second << L'\n';
            Utility::setFontColor(FontColor::white);

            std::wcin.get();
        }
    }
}

void QuizManager::printSummary() const
{
    Utility::setFontColor(FontColor::cyan);
    std::wcout << L"\n\tTHE END!" << L"\n\n";
    Utility::setFontColor(FontColor::white);

    std::wcout << L" Tries: " << m_tries << L'\n';
    float accuracy = round(((float)m_initial_questions_size / (float)m_tries) * 100.0f);
    std::wcout << " Accuracy: ";

    //accuracy color depending on the value
    if(accuracy >= 80) Utility::setFontColor(FontColor::green);
    else if(accuracy >= 50 && accuracy < 80) Utility::setFontColor(FontColor::cyan);
    else Utility::setFontColor(FontColor::red);

    std::wcout << accuracy << L"%\n";
    Utility::setFontColor(FontColor::white);

    std::wcin.get();
}

void QuizManager::setPath()
{
    std::string new_path{};
    Utility::setFontColor(FontColor::cyan);
    std::wcout << L"\n Path to questions file (default is questions.json): ";
    Utility::setFontColor(FontColor::white);
    std::getline(std::cin, new_path);

    //remove trailing and leading spaces from path string
    new_path = Utility::trim(new_path);
    if(!new_path.empty()) //if path exists, make it default path to read
    {
        m_path = new_path;
    }

    system("cls");
}

std::string QuizManager::getPath() const
{
    return m_path;
}
