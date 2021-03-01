#include "../headers/QuestionManager.h"

QuestionManager::QuestionManager() = default;

void QuestionManager::setQuestion()
{
    std::wcout << L"Question: ";
    std::getline(std::wcin, m_question);
}

void QuestionManager::setAnswer()
{
    std::wcout << L"Answer: ";
    std::getline(std::wcin, m_answer);
}

std::wstring QuestionManager::getQuestion() const
{
    return m_question;
}

std::wstring QuestionManager::getAnswer() const
{
    return m_answer;
}

void QuestionManager::makeQuestion()
{
    setQuestion();
    setAnswer();
    std::wcout << L'\n';

    if(!m_question.empty() || !m_answer.empty())
    {
        m_allQuestions.insert({m_question, m_answer});
    }
}

void QuestionManager::printQuestions() const
{
    for(auto [question, answer] : m_allQuestions)
    {
        std::wcout << question << L" : " << answer << L'\n';
    }
}

bool QuestionManager::saveToJson(const std::string& path) const
{
    std::ofstream file{path};
    if(file.good())
    {
        json json_obj = m_allQuestions;
        std::string json_string = json_obj.dump(4);

        file << json_string;

        file.close();
        return true;
    }

    return false;
}

bool QuestionManager::loadFromJson(const std::string& path)
{

    std::ifstream file{path};
    if(file.good())
    {
        json json_obj = json::parse(file);
        m_allQuestions = json_obj.get<QuestionContainer>();

        file.close();
        return true;
    }

    return false;
}

QuestionContainer QuestionManager::getAllQuestions() const
{
    return m_allQuestions;
}
