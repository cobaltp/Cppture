#pragma once

// Qt 프레임워크 헤더
#include <QtWidgets/QDialog>
#include "ui_About.h"

// Cppture 확장 도구 헤더
#include "Tools.h"

class AboutDialog : public QDialog, public Ui_About
{
	Q_OBJECT

public:
	AboutDialog(QWidget *parent = 0);

private slots:
	void onPushButton();
};
