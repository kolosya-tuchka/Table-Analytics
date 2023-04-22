QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Timeline/Color.cpp \
    Timeline/GraphicsScene.cpp \
    Timeline/GraphicsView.cpp \
    Timeline/Indicator.cpp \
    Timeline/Track.cpp \
    Timeline/timeline.cpp \
    base_filter.cpp \
    base_filter_creator.cpp \
    base_filter_view.cpp \
    csv_config.cpp \
    csv_reader.cpp \
    csv_writer.cpp \
    filter_exception.cpp \
    filter_manager.cpp \
    filters_controller.cpp \
    hard_filter.cpp \
    hard_filter_creator.cpp \
    main.cpp \
    mainwindow.cpp \
    regex_filter.cpp \
    regex_filter_creator.cpp \
    soft_filter.cpp \
    soft_filter_creator.cpp \
    string_util.cpp

HEADERS += \
    Timeline/Color.h \
    Timeline/GraphicsScene.h \
    Timeline/GraphicsView.h \
    Timeline/Indicator.h \
    Timeline/Track.h \
    Timeline/timeline.h \
    base_filter.h \
    base_filter_creator.h \
    base_filter_view.h \
    codec.h \
    csv_config.h \
    csv_reader.h \
    csv_writer.h \
    filter_exception.h \
    filter_manager.h \
    filters_controller.h \
    hard_filter.h \
    hard_filter_creator.h \
    mainwindow.h \
    regex_filter.h \
    regex_filter_creator.h \
    soft_filter.h \
    soft_filter_creator.h \
    string_util.h

FORMS += \
    Timeline/timeline.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Timeline/Indicator_Head_shape.blend \
    Timeline/Indicator_Head_shape.blend1 \
    Timeline/indicatorHeadPolygon.txt
