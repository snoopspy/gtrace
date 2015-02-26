#-------------------------------------------------
#
# Project created by QtCreator 2014-11-17T12:38:20
#
#-------------------------------------------------

QT -= core gui
TARGET = gtrace_test
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += exam.cpp \
	gtrace.c

HEADERS += \
	gtrace.h

win32:LIBS += -lws2_32

OTHER_FILES += \
	makefile \
	readme.md
