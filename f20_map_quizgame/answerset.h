#ifndef ANSWERSET_H
#define ANSWERSET_H

#include <QString>
#include <vector>

class AnswerSet
{
public:
    AnswerSet();
    void addAnswer(QString ans);
    std::vector<QString> answers;
};

#endif // ANSWERSET_H
