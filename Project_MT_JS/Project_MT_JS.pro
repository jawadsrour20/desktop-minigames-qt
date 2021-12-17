QT+=widgets \
    multimedia

SOURCES += \
    battleship.cpp \
    button.cpp \
    discshooter.cpp \
    gridesquare.cpp \
    history.cpp \
    home.cpp \
    login.cpp \
    main.cpp \
    playgame1.cpp \
    questionpopscreen.cpp \
    register.cpp \
    scoresmodel.cpp \
    shootingdiscs.cpp \
    shootingdiscsscene.cpp \
    targetdisc.cpp

HEADERS += \
    battleship.h \
    button.h \
    discshooter.h \
    gridesquare.h \
    history.h \
    home.h \
    login.h \
    playgame1.h \
    questionpopscreen.h \
    register.h \
    scoresmodel.h \
    shootingdiscs.h \
    shootingdiscsscene.h \
    targetdisc.h

RESOURCES += \
    resources.qrc

CONFIG+=sdk_no_version_check
QMAKE_CXXFLAGS += -Wno-enum-compare
