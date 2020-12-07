QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
        tst_quizgame.cpp \
        ../f20_map_quizgame/logic/quiz.cpp \
        ../f20_map_quizgame/logic/question.cpp
