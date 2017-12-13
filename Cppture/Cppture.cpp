#include "stdafx.h"
#include "Cppture.h"

// Cppture의 기본 생성자입니다.
Cppture::Cppture(QWidget *parent) : 
	QMainWindow(parent)
{
	setupUi(this);

	// 설정 파일 이름을 불러온다.
	settingsFilename = new QString(QCoreApplication::applicationDirPath() + 
		QDir::separator() + "settings.ini");

	// 설정을 불러온다.
	loadSettings();

	// 전역 단축키를 등록한다.
	RegisterHotkeys();

	// 액션을 메뉴에 등록한다.
	createActions();

	// 알림 아이콘을 생성한다.
	createTrayIcon();

	// 알림 아이콘에 이벤트를 등록한다.
	connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(messageClicked()));
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	// 알림 아이콘을 표시한다.
	trayIcon->show();

	QString title(*appName + " v" + *appVersion + " is online!");
	showMessage(title, 
		"Please right click icon if you want to know get more informations!");
}

// 현재 위젯의 표시 상태를 설정합니다.
void Cppture::setVisible(bool visible)
{
	QMainWindow::setVisible(visible);
}

// close()시 발생하는 이벤트입니다.
void Cppture::closeEvent(QCloseEvent *closeEvent)
{
	qApp->exit();
}

// overrided from QWidget::nativeEvent()
// 윈도우 프로세스 함수 WndProc() 의 래퍼 이벤트 함수입니다.
bool Cppture::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
	// 다음 매개변수들은 사용하지 않습니다.
	Q_UNUSED(eventType);
	Q_UNUSED(result);

	// 메시지를 정적 캐스팅 합니다.
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

// 기본값으로 지정된 설정 파일을 생성합니다.
void Cppture::createDefaultSettings()
{
	// 설정 파일을 ini 형식으로 엽니다.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	QString appVersion;
	Tools::GetProductAndVersion(QString(), appVersion);

	settings.setValue("ApplicationVersion", appVersion);

	// 그룹 시작: [%General]
	settings.beginGroup("General");

	// 단축키 1: Control + Shift + F; 전체 화면 캡처
	settings.setValue("HotKey1KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_F));
	
	// 단축키 2: Control + Shift + W; 현재 창 캡처
	settings.setValue("HotKey2KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_W));
	
	// 단축키 3: Control + Shift + C; 선택 영역 캡처
	settings.setValue("HotKey3KeySequence", QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::Key_C));

	// 로컬 저장 경로 사용
	settings.setValue("UseLocalDirectory",	true);
	// 저장 경로
	settings.setValue("SaveDirectory",		QCoreApplication::applicationDirPath() + 
		QDir::separator() + "screenshots");

	// 파일 이름 포맷 및 확장자
	settings.setValue("FilenameFormat",		"yyyyMMdd-hhmmss");
	settings.setValue("FileExtension",		"png");

	// 그룹 종료: [%General]
	settings.endGroup();

	// 설정 파일 동기화
	settings.sync();

	return loadSettings();
}

// 설정 파일에서 설정을 불러옵니다.
void Cppture::loadSettings()
{
	// 설정 파일을 ini 형식으로 엽니다.
	QSettings settings(*settingsFilename, QSettings::IniFormat);

	// 애플리케이션의 이름과 버전을 구합니다.
	appName = new QString();
	appVersion = new QString();
	Tools::GetProductAndVersion(*appName, *appVersion);

	// 설정 파일에 키가 하나도 등록되어 있지 않거나(설정 파일이 비어있거나 없다면)
	// 버전이 현재 버전과 다르다면, 기본값 설정 파일을 생성합니다.
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

	// 그룹 시작: [%General]
	settings.beginGroup("General");

	// 전역 단축키 이벤트 1
	hotkey1KeySequence = new QKeySequence(settings.value("HotKey1KeySequence").toString());

	// 전역 단축키 이벤트 2
	hotkey2KeySequence = new QKeySequence(settings.value("HotKey2KeySequence").toString());

	// 전역 단축키 이벤트 3
	hotkey3KeySequence = new QKeySequence(settings.value("HotKey3KeySequence").toString());

	// 로컬 저장 경로 사용
	useLocalDirectory = new bool(settings.value("UseLocalDirectory").toBool());

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

	if (!saveDirectory->exists())
		QDir().mkpath(saveDirectoryString);

	filenameFormat = new QString(settings.value("FilenameFormat").toString());
	fileExtension = new QString(settings.value("FileExtension").toString());

	// 그룹 종료: [%General]
	settings.endGroup();
}

// 액션을 생성하고, 슬롯 함수와 연결합니다.
void Cppture::createActions()
{
	settingsAction =		new QAction(tr("&Settings"),	this);
	aboutAction =			new QAction(tr("&About"),		this);
	quitAction =			new QAction(tr("&Quit"),		this);

	connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
	connect(aboutAction,	SIGNAL(triggered()), this, SLOT(showAboutDialog()));
	connect(quitAction,		SIGNAL(triggered()), this, SLOT(onExit()));
}

// 알림 아이콘을 생성합니다.
void Cppture::createTrayIcon()
{
	// 메뉴를 생성하고, 액션을 등록한다.
	trayIconMenu = new QMenu(this);
	trayIconMenu->addAction(settingsAction);
	trayIconMenu->addAction(aboutAction);
	trayIconMenu->addSeparator();
	trayIconMenu->addAction(quitAction);

	// 알림 아이콘을 생성하고, 메뉴를 연결한다.
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setContextMenu(trayIconMenu);
	trayIcon->setIcon(QIcon(":/Cppture/Cppture.ico"));
	trayIcon->setToolTip(*appName + " v" + appVersion);
}

// 전역 단축키를 등록합니다.
bool Cppture::RegisterHotkeys()
{
	// 전역 단축키 1 등록
	if (!RegisterHotKey(
		HWND(winId()),
		Hotkey::Hotkey1,
		Tools::KeySequence::getNativeModifiers(*hotkey1KeySequence),
		Tools::KeySequence::getNativeVirtualKey(*hotkey1KeySequence)))
	{
		QMessageBox::warning(this, "Warning", "Can't register hotkey 1");
		return false;
	}
	 
	// 전역 단축키 2 등록
	if (!RegisterHotKey(
		HWND(winId()),
		Hotkey::Hotkey2,
		Tools::KeySequence::getNativeModifiers(*hotkey2KeySequence),
		Tools::KeySequence::getNativeVirtualKey(*hotkey2KeySequence)))
	{
		QMessageBox::warning(this, "Warning", "Can't register hotkey 2");
		return false;
	}

	// 전역 단축키 3 등록
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

// 전역 단축키를 해지합니다.
bool Cppture::UnregisterHotkeys()
{
	// 전역 단축키 1 해지
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey1))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 1");

	// 전역 단축키 2 해지
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey2))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 2");
	
	// 전역 단축키 3 해지
	if (!UnregisterHotKey(HWND(winId()), Hotkey::Hotkey3))
		QMessageBox::warning(this, "Warning", "Can't unregister hotkey 3");

	return true;
}

// 알림 아이콘에 풍선 메시지를 표시합니다.
void Cppture::showMessage(
	QString title,
	QString text,
	QSystemTrayIcon::MessageIcon icon,
	int milliseconds)
{
	trayIcon->showMessage(title, text, icon, milliseconds);
}

// 캡처한 Pixmap을 이미지 파일로 저장합니다.
void Cppture::saveImage()
{
	// 현재 시간을 구합니다.
	QDateTime now = QDateTime::currentDateTime();
	// 시간값으로 파일 이름을 생성합니다.
	const QString filename = now.toString(*filenameFormat) + "." + fileExtension;
	// 저장 경로와 파일 이름을 연결합니다.
	const QString filepath = saveDirectory->absoluteFilePath(filename);

	// Pixmap을 저장합니다.
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

// 주 화면의 전체 영역의 Pixmap을 구합니다.
void Cppture::captureFullscreen()
{
	// 주 화면을 구한다.
	QScreen *screen = QGuiApplication::primaryScreen();

	// if (const QWindow *window = windowHandle())
	//		screen = window->screen();

	// 주 화면의 Pixmap을 구한다.
	screenshotPixmap = screen->grabWindow(0);

	// Pixmap을 저장한다.
	saveImage();
}

// 현재 활성화된 창의 Pixmap을 구합니다.
void Cppture::captureWindow()
{
	// 주 화면을 구한다.
	QScreen *screen = QGuiApplication::primaryScreen();

	// Win32 Api; 현재 활성화된 창의 핸들을 구한다.
	HWND hWnd = GetForegroundWindow();

	// 핸들에서 창의 정보를 구한다.
	QWindow *window = QWindow::fromWinId((WId)hWnd);

	// 창의 좌표와 크기를 구한다.
	int x = window->x();
	int y = window->y();
	int w = window->width();
	int h = window->height();

	// 시스템에 지정된 경계선 값과 패딩값을 구한다.
	int cxb = GetThemeSysSize(NULL, SM_CXBORDER);			// X축 경계선;			 1px
	int cxp = GetThemeSysSize(NULL, SM_CXPADDEDBORDER);		// 제목 표시줄 패딩;	 4px
	int cyb = GetThemeSysSize(NULL, SM_CYBORDER);			// Y축 경계선;			 1px
	int cys = GetThemeSysSize(NULL, SM_CYSIZE);				// 제목 텍스트 높이;	22px

	// 대상 창이 최대화 상태가 아닌 경우, 경계선을 계산한다.
	if (!(window->windowState() == Qt::WindowMaximized))
	{
		x -= cxb;							// -  1px; 1
		y -= cyb + cxp + cys + cxp;			// - 31px; 1 + 4 + 22 + 4
		w += cxb + cxb;						// +  2px; 1 + 1
		h += cyb + cxp + cys + cxp + cyb;	// + 32px; 1 + 4 + 22 + 4 + 1
	}

	// 주 화면에서 좌표와 크기를 이용해 창 영역의 Pixmap을 구한다.
	screenshotPixmap = screen->grabWindow(0, x, y, w, h);

	saveImage();
}

// 선택된 영역의 Pixmap을 구합니다.
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

// 풍선 메시지 클릭 이벤트를 처리합니다.
void Cppture::messageClicked(QString text)
{
	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(text);
}

// 설정 다이얼로그를 표시하고, 설정을 다시 불러옵니다.
void Cppture::showSettingsDialog()
{
	settingsDialog = new SettingsDialog();

	// 전역 단축키를 해지한다.
	UnregisterHotkeys();

	// 설정 다이얼로그를 Modal로 실행한다.
	settingsDialog->exec();

	// 설정을 다시 불러온다.
	loadSettings();

	// 전역 단축키를 등록한다.
	RegisterHotkeys();
}

// 정보 다이얼로그를 표시합니다.
void Cppture::showAboutDialog()
{
	aboutDialog = new AboutDialog();
	aboutDialog->show();
}

// 종료 메뉴에 연결된 슬롯 함수입니다.
void Cppture::onExit()
{
	UnregisterHotkeys();
	close();
}
