#include "../headers/QuestionManager.h"

QuestionManager::QuestionManager() = default;

void QuestionManager::setQuestion()
{
    std::wcout << L"Question: ";
    std::getline(std::wcin, m_question);
    m_question = Utility::trim(m_question);
    m_question_encoded = Utility::utf8_encode(m_question);
}

void QuestionManager::setAnswer()
{
    std::wcout << L"Answer: ";
    std::getline(std::wcin, m_answer);
    m_answer = Utility::trim(m_answer);
    m_answer_encoded = Utility::utf8_encode(m_answer);
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
        m_allQuestions.insert({m_answer, m_question});
        m_allQuestionsEncoded.insert({m_question_encoded, m_answer_encoded});
    }
}

void QuestionManager::printAllQuestions() const
{
    int nr{1};
    for(auto [question, answer] : m_allQuestions)
    {
        std::wcout << L' ' << nr << L". " << question << L" : " << answer << L'\n';
        nr++;
    }
}

bool QuestionManager::saveToJson(const std::string& path) const
{
    std::ofstream file{path};
    if(file.good())
    {
        json json_obj = m_allQuestionsEncoded;
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
        m_allQuestionsEncoded = json_obj.get<QuestionContainerEncoded>(); //make json object into questions

        //iterate through questions and decode them
        for(auto [question, answer] : m_allQuestionsEncoded)
        {
            std::wstring question_decoded = Utility::utf8_decode(question);
            std::wstring answer_decoded = Utility::utf8_decode(answer);
            m_allQuestions.insert({question_decoded, answer_decoded});
        }

        file.close();
        return true;
    }

    return false;
}

bool QuestionManager::loadFromJson()
{
    return loadFromJson(m_path);
}

QuestionContainer& QuestionManager::getAllQuestions()
{
    return m_allQuestions;
}

QuestionContainerEncoded& QuestionManager::getAllQuestionsEncoded() {
    return m_allQuestionsEncoded;
}

void QuestionManager::setPath()
{
    std::string new_path{};
    std::wcout << L"\n Path to questions file (default is questions.json): ";
    std::getline(std::cin, new_path);

    //remove trailing and leading spaces from path string
    new_path = Utility::trim(new_path);
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

