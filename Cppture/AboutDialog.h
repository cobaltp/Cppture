#pragma once

// Qt �����ӿ�ũ ���
#include <QtWidgets/QDialog>
#include "ui_About.h"

// Cppture Ȯ�� ���� ���
#include "Tools.h"

class AboutDialog : public QDialog, public Ui_About
{
	Q_OBJECT

public:
	AboutDialog(QWidget *parent = 0);

private slots:
	void onPushButton();
};
