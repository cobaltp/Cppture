#include "stdafx.h"
#include "Cppture.h"

// Cppture�� �⺻ �������Դϴ�.
Cppture::Cppture(QWidget *parent) : 
	QMainWindow(parent)
{
	setupUi(this);

	// ���� ���� �̸��� �ҷ��´�.
	settingsFilename = new QString(QCoreApplication::applicationDirPath() + 
		QDir::separator() + "settings.ini");

	// ������ �ҷ��´�.
	loadSettings();

	// ���� ����Ű�� ����Ѵ�.
	RegisterHotkeys();

	// �׼��� �޴��� ����Ѵ�.
	createActions();

	// �˸� �������� �����Ѵ�.
	createTrayIcon();

	// �˸� �����ܿ� �̺�Ʈ�� ����Ѵ�.
	connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	// �˸� �������� ǥ���Ѵ�.
	trayIcon->show();

	QString title(*appName + " v" + *appVersion + " is online!");
	showMessage(title, 
		"Please right click icon if you want to know get more informations!");
}

// ���� ������ ǥ�� ���¸� �����մϴ�.
void Cppture::setVisible(bool visible)
{
	QMainWindow::setVisible(visible);
}

// close()�� �߻��ϴ� �̺�Ʈ�Դϴ�.
void Cppture::closeEvent(QCloseEvent *closeEvent)
{
	qApp->exit();
}

// overrided from QWidget::nativeEvent()
// ������ ���μ��� �Լ� WndProc() �� ���� �̺�Ʈ �Լ��Դϴ�.
bool Cppture::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	// ���� �Ű��������� ������� �ʽ��ϴ�.
	Q_UNUSED(eventType);
	Q_UNUSED(result);

	// �޽����� ���� ĳ���� �մϴ�.
	MSG *msg = static_cast<MSG *>(message);

	if (msg->message == WM_HOTKEY)
	{
		if ((UINT)msg->wParam == Hotkey::Hotkey1)
		{
			captureFullscreen();
			// QMessageBox::information(this, "OK", "Hotkey Pressed: ID " + Hotkey::Hotkey1);
			return true;
		}
		else if ((UINT)msg->wParam == Hotkey::Hotkey2)
		{
			captureWindow();
			// QMessageBox::information(this, "OK", "Hotkey Pressed: ID " + Hotkey::Hotkey2);
			return true;
		}
		else if ((UINT)msg->wParam == Hotkey::Hotkey3)
		{
			captureArea();
			// QMessageBox::information(this, "OK", "Hotkey Pressed: ID " + Hotkey::Hotkey3);
			return true;
		}
	}

	return false;
}

// �⺻������ ������ ���� ������ �����մϴ�.
void Cppture::createDefaultSettings()
{
	// ���� ������ ini �������� ���ϴ�.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	QString appVersion;
	Tools::GetProductAndVersion(QString(), appVersion);

	settings.setValue("ApplicationVersion", appVersion);

	// �׷� ����: [%General]
	settings.beginGroup("General");

	// ����Ű 1: Control + Shift + F; ��ü ȭ�� ĸó
	settings.setValue("HotKey1KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F));
	
	// ����Ű 2: Control + Shift + W; ���� â ĸó
	settings.setValue("HotKey2KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_W));
	
	// ����Ű 3: Control + Shift + C; ���� ���� ĸó
	settings.setValue("HotKey3KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_C));

	// ���� ���� ��� ���
	settings.setValue("UseLocalDirectory",	true);
	// ���� ���
	settings.setValue("SaveDirectory",		QCoreApplication::applicationDirPath() + 
		QDir::separator() + "screenshots");

	// ���� �̸� ���� �� Ȯ����
	settings.setValue("FilenameFormat",		"yyyyMMdd-hhmmss");
	settings.setValue("FileExtension",		"png");

	// �׷� ����: [%General]
	settings.endGroup();

	// ���� ���� ����ȭ
	settings.sync();

	return loadSettings();
}

// ���� ���Ͽ��� ������ �ҷ��ɴϴ�.
void Cppture::loadSettings()
{
	// ���� ������ ini �������� ���ϴ�.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	// ���ø����̼��� �̸��� ������ ���մϴ�.
	appName = new QString();
	appVersion = new QString();
	Tools::GetProductAndVersion(*appName, *appVersion);

	// ���� ���Ͽ� Ű�� �ϳ��� ��ϵǾ� ���� �ʰų�(���� ������ ����ְų� ���ٸ�)
	// ������ ���� ������ �ٸ��ٸ�, �⺻�� ���� ������ �����մϴ�.
	if (settings.allKeys().count() == 0)
	{
		return createDefaultSettings();
	}
	if (settings.value("ApplicationVersion").toString() != appVersion)
	{
		QMessageBox::warning(this, "Warning",
			"Version of settings.ini is different from application's version.\nsettings.ini is revert to default settings.");
		return createDefaultSettings();
	}

	// �׷� ����: [%General]
	settings.beginGroup("General");

	// ���� ����Ű �̺�Ʈ 1
	hotkey1KeySequence = new QKeySequence(settings.value("HotKey1KeySequence").toString());

	// ���� ����Ű �̺�Ʈ 2
	hotkey2KeySequence = new QKeySequence(settings.value("HotKey2KeySequence").toString());

	// ���� ����Ű �̺�Ʈ 3
	hotkey3KeySequence = new QKeySequence(settings.value("HotKey3KeySequence").toString());

	// ���� ���� ��� ���
	useLocalDirectory = new bool(settings.value("UseLocalDirectory").toBool());

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

	if (!saveDirectory->exists())
		QDir().mkpath(saveDirectoryString);

	filenameFormat = new QString(settings.value("FilenameFormat").toString());
	fileExtension = new QString(settings.value("FileExtension").toString());

	// �׷� ����: [%General]
	settings.endGroup();
}

// �׼��� �����ϰ�, ���� �Լ��� �����մϴ�.
void Cppture::createActions()
{
	settingsAction =		new QAction(tr("&Settings"),	this);
	aboutAction =			new QAction(tr("&About"),		this);
	quitAction =			new QAction(tr("&Quit"),		this);

	connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
	connect(aboutAction,	SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(quitAction,		SIGNAL(triggered()), this, SLOT(onExit()));
}

// �˸� �������� �����մϴ�.
void Cppture::createTrayIcon()
{
	// �޴��� �����ϰ�, �׼��� ����Ѵ�.
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(settingsAction);
	trayIconMenu->addAction(aboutAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	// �˸� �������� �����ϰ�, �޴��� �����Ѵ�.
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(QIcon(":/Cppture/Cppture.ico"));
	trayIcon->setToolTip(*appName + " v" + appVersion);
}

// ���� ����Ű�� ����մϴ�.
bool Cppture::RegisterHotkeys()
{
	// ���� ����Ű 1 ���
	if (!RegisterHotKey(
		HWND(winId()),
		Hotkey::Hotkey1,
		Tools::KeySequence::getNativeModifiers(*hotkey1KeySequence),
		Tools::KeySequence::getNativeVirtualKey(*hotkey1KeySequence)))
	{
		QMessageBox::warning(this, "Warning", "Can't register hotkey 1");
		return false;
	}
	 
	// ���� ����Ű 2 ���
	if (!RegisterHotKey(
		HWND(winId()),
		Hotkey::Hotkey2,
		Tools::KeySequence::getNativeModifiers(*hotkey2KeySequence),
		Tools::KeySequence::getNativeVirtualKey(*hotkey2KeySequence)))
	{
		QMessageBox::warning(this, "Warning", "Can't register hotkey 2");
		return false;
	}

	// ���� ����Ű 3 ���
	if (!RegisterHotKey(
		HWND(winId()),
		Hotkey::Hotkey3,
		Tools::KeySequence::getNativeModifiers(*hotkey3KeySequence),
		Tools::KeySequence::getNativeVirtualKey(*hotkey3KeySequence)))
	{
		QMessageBox::warning(this, "Warning", "Can't register hotkey 3");
		return false;
	}

	return true;
}

// ���� ����Ű�� �����մϴ�.
bool Cppture::UnregisterHotkeys()
{
	// ���� ����Ű 1 ����
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey1))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 1");

	// ���� ����Ű 2 ����
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey2))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 2");
	
	// ���� ����Ű 3 ����
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey3))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 3");

	return true;
}

// �˸� �����ܿ� ǳ�� �޽����� ǥ���մϴ�.
void Cppture::showMessage(
	QString title,
	QString text,
	QSystemTrayIcon::MessageIcon icon,
	int milliseconds)
{
	trayIcon->showMessage(title, text, icon, milliseconds);
}

// ĸó�� Pixmap�� �̹��� ���Ϸ� �����մϴ�.
void Cppture::saveImage()
{
	// ���� �ð��� ���մϴ�.
	QDateTime now = QDateTime::currentDateTime();
	// �ð������� ���� �̸��� �����մϴ�.
	const QString filename = now.toString(*filenameFormat) + "." + fileExtension;
	// ���� ��ο� ���� �̸��� �����մϴ�.
	const QString filepath = saveDirectory->absoluteFilePath(filename);

	// Pixmap�� �����մϴ�.
	if (screenshotPixmap.save(filepath))
	{
		showMessage("Click here to copy link", filepath);
		QClipboard *clipboard = QGuiApplication::clipboard();
		clipboard->setText(filepath);
	}
	else
	{
		showMessage("Saving file has failed", filename + "...");
	}
}

// �� ȭ���� ��ü ������ Pixmap�� ���մϴ�.
void Cppture::captureFullscreen()
{
	// �� ȭ���� ���Ѵ�.
	QScreen *screen = QGuiApplication::primaryScreen();

	// if (const QWindow *window = windowHandle())
	//		screen = window->screen();

	// �� ȭ���� Pixmap�� ���Ѵ�.
	screenshotPixmap = screen->grabWindow(0);

	// Pixmap�� �����Ѵ�.
	saveImage();
}

// ���� Ȱ��ȭ�� â�� Pixmap�� ���մϴ�.
void Cppture::captureWindow()
{
	// �� ȭ���� ���Ѵ�.
	QScreen *screen = QGuiApplication::primaryScreen();

	// Win32 Api; ���� Ȱ��ȭ�� â�� �ڵ��� ���Ѵ�.
	HWND hWnd = GetForegroundWindow();

	// �ڵ鿡�� â�� ������ ���Ѵ�.
	QWindow *window = QWindow::fromWinId((WId)hWnd);

	// â�� ��ǥ�� ũ�⸦ ���Ѵ�.
	int x = window->x();
	int y = window->y();
	int w = window->width();
	int h = window->height();

	// �ý��ۿ� ������ ��輱 ���� �е����� ���Ѵ�.
	int cxb = GetThemeSysSize(NULL, SM_CXBORDER);			// X�� ��輱;			 1px
	int cxp = GetThemeSysSize(NULL, SM_CXPADDEDBORDER);		// ���� ǥ���� �е�;	 4px
	int cyb = GetThemeSysSize(NULL, SM_CYBORDER);			// Y�� ��輱;			 1px
	int cys = GetThemeSysSize(NULL, SM_CYSIZE);				// ���� �ؽ�Ʈ ����;	22px

	// ��� â�� �ִ�ȭ ���°� �ƴ� ���, ��輱�� ����Ѵ�.
	if (!(window->windowState() == Qt::WindowMaximized))
	{
		x -= cxb;							// -  1px; 1
		y -= cyb + cxp + cys + cxp;			// - 31px; 1 + 4 + 22 + 4
		w += cxb + cxb;						// +  2px; 1 + 1
		h += cyb + cxp + cys + cxp + cyb;	// + 32px; 1 + 4 + 22 + 4 + 1
	}

	// �� ȭ�鿡�� ��ǥ�� ũ�⸦ �̿��� â ������ Pixmap�� ���Ѵ�.
	screenshotPixmap = screen->grabWindow(0, x, y, w, h);

	saveImage();
}

// ���õ� ������ Pixmap�� ���մϴ�.
void Cppture::captureArea()
{
	QScreen *screen = QGuiApplication::primaryScreen();

	screenshotPixmap = screen->grabWindow(0);

	QRect rect;
	showAndGetSelectArea(rect);

	screenshotPixmap = screenshotPixmap.copy(rect);

	saveImage();
}

void Cppture::showAndGetSelectArea(QRect &rect)
{
	SelectAreaDialog *selectAreaDialog = new SelectAreaDialog(&screenshotPixmap);
	selectAreaDialog->exec();
	rect = selectAreaDialog->getRect();
}

void Cppture::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		break;
	}
}

// ǳ�� �޽��� Ŭ�� �̺�Ʈ�� ó���մϴ�.
void Cppture::messageClicked(QString text)
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(text);
}

// ���� ���̾�α׸� ǥ���ϰ�, ������ �ٽ� �ҷ��ɴϴ�.
void Cppture::showSettingsDialog()
{
	settingsDialog = new SettingsDialog();

	// ���� ����Ű�� �����Ѵ�.
	UnregisterHotkeys();

	// ���� ���̾�α׸� Modal�� �����Ѵ�.
	settingsDialog->exec();

	// ������ �ٽ� �ҷ��´�.
	loadSettings();

	// ���� ����Ű�� ����Ѵ�.
	RegisterHotkeys();
}

// ���� ���̾�α׸� ǥ���մϴ�.
void Cppture::showAboutDialog()
{
	aboutDialog = new AboutDialog();
	aboutDialog->show();
}

// ���� �޴��� ����� ���� �Լ��Դϴ�.
void Cppture::onExit()
{
	UnregisterHotkeys();
	close();
}
