#pragma once

// Qt �����ӿ�ũ ���
#include <QtWidgets/QMainWindow>
#include <QCloseEvent>
#include <QSettings>
#include <QClipboard>

// UI �� ���̾�α� ���
#include "ui_Cppture.h"
#include "AboutDialog.h"
#include "SettingsDialog.h"
#include "SelectAreaDialog.h"

// Cppture Ȯ�� ���� ���
#include "Tools.h"

class Cppture : public QMainWindow, public Ui::CpptureClass
{
	Q_OBJECT

	// Cppture::Hotkey
	// ����Ű ID
	enum Hotkey {
		Hotkey1 = 101,
		Hotkey2,
		Hotkey3,
		Hotkey4
	};

private:
	QString	*settingsFilename;

	QSystemTrayIcon	*trayIcon;
	QMenu *trayIconMenu;
	QPixmap screenshotPixmap;

	// ����
	QString *appName;
	QString *appVersion;
	QKeySequence *hotkey1KeySequence;
	QKeySequence *hotkey2KeySequence;
	QKeySequence *hotkey3KeySequence;
	QDir *saveDirectory;
	bool *useLocalDirectory;
	QString *filenameFormat;
	QString *fileExtension;

	QAction *settingsAction;
	QAction *aboutAction;
	QAction	*quitAction;

	QDialog *settingsDialog;
	QDialog	*aboutDialog;
	
public:
	Cppture(QWidget *parent = 0);
	void setVisible(bool visible) override;

protected:
	void closeEvent(QCloseEvent *closeEvent) override;
	bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
	void createDefaultSettings();
	void loadSettings();
	void createActions();
	void createTrayIcon();
	bool RegisterHotkeys();
	bool UnregisterHotkeys();
	void showMessage(
		QString title,
		QString text,
		QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information,
		int milliseconds = 10000
	);

	void saveImage();
	void captureFullscreen();
	void captureWindow();
	void captureArea();
	void showAndGetSelectArea(QRect &rect);

private slots:
	// void setIcon(int index);
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
	void messageClicked(QString text);
	void showSettingsDialog();
	void showAboutDialog();
	void onExit();
};
