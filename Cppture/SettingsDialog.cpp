#include "stdafx.h"
#include "SettingsDialog.h"

// SettingsDialog�� �⺻ �������Դϴ�.
SettingsDialog::SettingsDialog(QWidget *parent) : 
	QDialog(parent)
{
	setupUi(this);

	qApp->installEventFilter(this);
	settingsFilename = new QString(QCoreApplication::applicationDirPath() +
		QDir::separator() + "settings.ini");

	// ������ �ҷ��´�.
	loadSettings();

	// ���� �Լ��� �����Ѵ�.
	connectSlots();
}

// ���� ���Ͽ��� ������ �ҷ��ɴϴ�.
void SettingsDialog::loadSettings()
{
	// ���� ������ ini �������� ���ϴ�.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	// �׷� ����: [%General]
	settings.beginGroup("General");

	// ���� ����Ű �̺�Ʈ 1
	hotkey1KeySequence = new QKeySequence(settings.value("HotKey1KeySequence").toString());
	hotkey1Button->setText(hotkey1KeySequence->toString());

	// ���� ����Ű �̺�Ʈ 2
	hotkey2KeySequence = new QKeySequence(settings.value("HotKey2KeySequence").toString());
	hotkey2Button->setText(hotkey2KeySequence->toString());

	// ���� ����Ű �̺�Ʈ 3
	hotkey3KeySequence = new QKeySequence(settings.value("HotKey3KeySequence").toString());
	hotkey3Button->setText(hotkey3KeySequence->toString());

	// ���� ���� ��� ���
	useLocalDirectory = new bool(settings.value("UseLocalDirectory").toBool());
	saveToLocalCheckBox->setChecked(*useLocalDirectory);

	// ���� ���
	QString saveDirectoryString;

	if (useLocalDirectory)
	{
		saveDirectoryString = settings.value("SaveDirectory").toString();
	}
	else
	{
		saveDirectoryString = "%temp%\\Cppture\\screenshots";
	}

	saveDirectory = new QDir(saveDirectoryString);

	filenameFormat = new QString(settings.value("FilenameFormat").toString());
	filenameFormatLineEdit->setText(*filenameFormat);

	fileExtension = new QString(settings.value("FileExtension").toString());
	fileExtensionComboBox->setCurrentText("." + *fileExtension);

	if (!saveDirectory->exists())
		QDir().mkpath(saveDirectoryString);

	// �׷� ����: [%General]
	settings.endGroup();
}

// ������ �����մϴ�.
void SettingsDialog::saveSettings()
{
	// ���� ������ ini �������� ���ϴ�.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	QString appVersion;
	Tools::GetProductAndVersion(QString(), appVersion);

	settings.setValue("ApplicationVersion", appVersion);

	// �׷� ����: [%General]
	settings.beginGroup("General");

	// ����Ű 1
	settings.setValue("HotKey1KeySequence", hotkey1KeySequence->toString());

	// ����Ű 2
	settings.setValue("HotKey2KeySequence", hotkey2KeySequence->toString());

	// ����Ű 3
	settings.setValue("HotKey3KeySequence", hotkey3KeySequence->toString());

	// ���� ���� ��� ���
	settings.setValue("UseLocalDirectory", saveToLocalCheckBox->isChecked());
	// ���� ���
	settings.setValue("SaveDirectory", QCoreApplication::applicationDirPath() +
		QDir::separator() + "screenshots/");

	// ���ϸ� ����
	settings.setValue("FilenameFormat", filenameFormatLineEdit->text());

	// ���� Ȯ����
	settings.setValue("FileExtension", fileExtensionComboBox->currentText().remove(0, 1));

	// �׷� ����: [%General]
	settings.endGroup();

	// ���� ���� ����ȭ
	settings.sync();
}

// ���� �Լ��� ������ �����մϴ�.
void SettingsDialog::connectSlots()
{
	connect(okButton,		SIGNAL(released()), this, SLOT(onOkButton()));
	connect(cancelButton,	SIGNAL(released()), this, SLOT(onCancelButton()));
	connect(applyButton,	SIGNAL(released()), this, SLOT(onApplyButton()));
}

// ����Ű �̺�Ʈ �����Դϴ�.
bool SettingsDialog::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress)
	{
		if (qobject_cast<QPushButton *>(obj))
		{
			QPushButton *pButton = (QPushButton *)obj;
			QKeyEvent *pKeyEvent = (QKeyEvent *)event;
			QKeySequence **prevKeySequence;

			if (pButton == hotkey1Button)
				prevKeySequence = &hotkey1KeySequence;
			else if (pButton == hotkey2Button)
				prevKeySequence = &hotkey2KeySequence;
			else if (pButton == hotkey3Button)
				prevKeySequence = &hotkey3KeySequence;

			if (pKeyEvent->key() == Qt::Key_Control)
			{
				return false;
			}
			else if (pKeyEvent->key() == Qt::Key_Alt)
			{
				return false;
			}
			else if (pKeyEvent->key() == Qt::Key_Shift)
			{
				return false;
			}
			else if (pKeyEvent->key() == Qt::Key_Meta)
			{
				return false;
			}
			else if (pKeyEvent->key() == Qt::Key_Escape)
			{
				pButton->setText((*prevKeySequence)->toString());
				pButton->setChecked(false);
				return false;
			}

			*prevKeySequence = new QKeySequence(pKeyEvent->modifiers() + pKeyEvent->key());

			pButton->setText((*prevKeySequence)->toString());
			pButton->setChecked(false);
		}
	}

	return false;
}

void SettingsDialog::onOkButton()
{
	saveSettings();
	close();
}

void SettingsDialog::onCancelButton()
{
	close();
}

void SettingsDialog::onApplyButton()
{
	saveSettings();
	applyButton->setEnabled(false);
}

// Reserved for future uses
void SettingsDialog::onDataChanged()
{
	applyButton->setEnabled(true);
}