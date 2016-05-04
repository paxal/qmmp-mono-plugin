# include(../../plugins.pri)

HEADERS += monoplugin.h \
           effectmonofactory.h

SOURCES += monoplugin.cpp \
           effectmonofactory.cpp

# TARGET =$$PLUGINS_PREFIX/Effect/mono
TARGET = .

INCLUDEPATH += /usr/include/qt5/QtWidgets
CONFIG += warn_on \
plugin

TEMPLATE = lib
# QMAKE_LIBDIR += ../../../../lib

# RESOURCES = translations/translations.qrc
RESOURCES = 

# FORMS += settingsdialog.ui

unix {
    isEmpty(LIB_DIR){
        LIB_DIR = /lib
    }
    target.path = $$LIB_DIR/qmmp/Effect
    INSTALLS += target

    LIBS += -lqmmp -L/usr/lib -I/usr/include
    QMAKE_CLEAN =$$PLUGINS_PREFIX/Effect/libmono.so
}

win32 {
    QMAKE_LIBDIR += ../../../../bin
    LIBS += -lqmmp0
}
