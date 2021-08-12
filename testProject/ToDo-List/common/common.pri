QT += network sql

HEADERS += \
    $$PWD/IJson.hpp \
    $$PWD/QSingleton.h \
    $$PWD/Singleton.h \
    $$PWD/edit_box.h \
    $$PWD/http_client.h \
    $$PWD/question_box.h \
    $$PWD/sqlite_util.h

SOURCES += \
    $$PWD/edit_box.cpp \
    $$PWD/http_client.cpp \
    $$PWD/question_box.cpp \
    $$PWD/sqlite_util.cpp



INCLUDEPATH +=  \
    $$PWD

FORMS += \
    $$PWD/edit_box.ui \
    $$PWD/question_box.ui
