QT  += core gui openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    ebo.h \
    mainwindow.h \
    glrenderwidget.h \
    shader.h \
    Texture.h \
    vao.h \
    vbo.h

SOURCES += \
    ebo.cpp \
    main.cpp \
    mainwindow.cpp \
    glrenderwidget.cpp \
    shader.cpp \
    Texture.cpp \
    utils.cpp \
    vao.cpp \
    vbo.cpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += resources.qrc
