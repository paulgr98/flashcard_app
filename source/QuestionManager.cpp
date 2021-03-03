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

    if(!m_question.empty() || !m_answer.empty()) //insert q and a if they both exists
    {
        m_allQuestions.insert({m_question, m_answer});
    }
}

void QuestionManager::printAllQuestions() const
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
        std::string json_string = json_obj.dump(4); //make json object into string with indent of 4

        file << json_string;

        file.close();
        return true;
    }

    return false;
}

bool QuestionManager::saveToJson() const
{
    return saveToJson(m_path);
}

bool QuestionManager::loadFromJson(const std::string& path)
{
    std::ifstream file{path};
    if(file.good())
    {
        json json_obj = json::parse(file); //read from file to json object
        m_allQuestions = json_obj.get<QuestionContainer>(); //make json object into questions

        file.close();
        return true;
    }

    return false;
}

bool QuestionManager::loadFromJson()
{
    return loadFromJson(m_path);
}

QuestionContainer QuestionManager::getAllQuestions() const
{
    return m_allQuestions;
}

void QuestionManager::setPath()
{
    std::string new_path{};
    std::wcout << L"\n Path to questions file (default is questions.json): ";
    std::getline(std::cin, new_path);

    //remove spaces from path string (if for example user typed only spaces)
    new_path.erase(remove_if(new_path.begin(), new_path.end(), isspace), new_path.end());
    if(!new_path.empty()) //if path exists, make it default path to read/save
    {
        m_path = new_path;
    }

    system("cls");
}

std::string QuestionManager::getPath() const
{
    return m_path;
}
