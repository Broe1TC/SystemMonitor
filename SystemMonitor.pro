QT       += core gui widgets charts

CONFIG   += c++17

TARGET = SystemMonitor
TEMPLATE = app

SOURCES += \
    main.cpp \
    MainWindow.cpp \
    CpuMonitor.cpp \
    RamMonitor.cpp \
    DiskMonitor.cpp \
    NetworkMonitor.cpp

HEADERS += \
    MainWindow.h \
    CpuMonitor.h \
    RamMonitor.h \
    DiskMonitor.h \
    NetworkMonitor.h

FORMS += \
    ui/MainWindow.ui

LIBS += -liphlpapi