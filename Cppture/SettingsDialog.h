#pragma once

// Qt �����ӿ�ũ ���
#include <QtWidgets/QDialog>
#include <QApplication>
#include <QSettings>
#include <QKeyEvent>

// UI ���
#include "ui_Settings.h"

// Cppture Ȯ�� ���� ���
#include "Tools.h"

class SettingsDialog : public QDialog, public Ui::settings
{
	Q_OBJECT

private:
	QString *settingsFilename;

	QKeySequence *hotkey1KeySequence;
	QKeySequence *hotkey2KeySequence;
	QKeySequence *hotkey3KeySequence;
	QDir *saveDirectory;
	bool *useLocalDirectory;
	QString *filenameFormat;
	QString *fileExtension;

public:
	SettingsDialog(QWidget *parent = 0);

private:
	void loadSettings();
	void saveSettings();
	void connectSlots();
	bool eventFilter(QObject *obj, QEvent *event);

private slots:
	void onOkButton();
	void onCancelButton();
	void onApplyButton();
	void onDataChanged();
};
