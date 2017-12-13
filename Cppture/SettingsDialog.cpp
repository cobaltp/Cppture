#include "stdafx.h"
#include "SettingsDialog.h"

// SettingsDialog의 기본 생성자입니다.
SettingsDialog::SettingsDialog(QWidget *parent) : 
	QDialog(parent)
{
	setupUi(this);

	qApp->installEventFilter(this);
	settingsFilename = new QString(QCoreApplication::applicationDirPath() +
		QDir::separator() + "settings.ini");

	// 설정을 불러온다.
	loadSettings();

	// 슬롯 함수를 연결한다.
	connectSlots();
}

// 설정 파일에서 설정을 불러옵니다.
void SettingsDialog::loadSettings()
{
	// 설정 파일을 ini 형식으로 엽니다.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	// 그룹 시작: [%General]
	settings.beginGroup("General");

	// 전역 단축키 이벤트 1
	hotkey1KeySequence = new QKeySequence(settings.value("HotKey1KeySequence").toString());
	hotkey1Button->setText(hotkey1KeySequence->toString());

	// 전역 단축키 이벤트 2
	hotkey2KeySequence = new QKeySequence(settings.value("HotKey2KeySequence").toString());
	hotkey2Button->setText(hotkey2KeySequence->toString());

	// 전역 단축키 이벤트 3
	hotkey3KeySequence = new QKeySequence(settings.value("HotKey3KeySequence").toString());
	hotkey3Button->setText(hotkey3KeySequence->toString());

	// 로컬 저장 경로 사용
	useLocalDirectory = new bool(settings.value("UseLocalDirectory").toBool());
	saveToLocalCheckBox->setChecked(*useLocalDirectory);

	// 저장 경로
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

	// 그룹 종료: [%General]
	settings.endGroup();
}

// 설정을 저장합니다.
void SettingsDialog::saveSettings()
{
	// 설정 파일을 ini 형식으로 엽니다.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	QString appVersion;
	Tools::GetProductAndVersion(QString(), appVersion);

	settings.setValue("ApplicationVersion", appVersion);

	// 그룹 시작: [%General]
	settings.beginGroup("General");

	// 단축키 1
	settings.setValue("HotKey1KeySequence", hotkey1KeySequence->toString());

	// 단축키 2
	settings.setValue("HotKey2KeySequence", hotkey2KeySequence->toString());

	// 단축키 3
	settings.setValue("HotKey3KeySequence", hotkey3KeySequence->toString());

	// 로컬 저장 경로 사용
	settings.setValue("UseLocalDirectory", saveToLocalCheckBox->isChecked());
	// 저장 경로
	settings.setValue("SaveDirectory", QCoreApplication::applicationDirPath() +
		QDir::separator() + "screenshots/");

	// 파일명 포맷
	settings.setValue("FilenameFormat", filenameFormatLineEdit->text());

	// 파일 확장자
	settings.setValue("FileExtension", fileExtensionComboBox->currentText().remove(0, 1));

	// 그룹 종료: [%General]
	settings.endGroup();

	// 설정 파일 동기화
	settings.sync();
}

// 슬롯 함수를 위젯과 연결합니다.
void SettingsDialog::connectSlots()
{
	connect(okButton,		SIGNAL(released()), this, SLOT(onOkButton()));
	connect(cancelButton,	SIGNAL(released()), this, SLOT(onCancelButton()));
	connect(applyButton,	SIGNAL(released()), this, SLOT(onApplyButton()));
}

// 단축키 이벤트 필터입니다.
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