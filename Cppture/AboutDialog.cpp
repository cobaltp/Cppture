#include "stdafx.h"
#include "AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent) : 
	QDialog(parent)
{
	setupUi(this);
	connect(pushButton, SIGNAL(released()), this, SLOT(onPushButton()));
	
	QString appName;
	QString appVersion;

	Tools::GetProductAndVersion(appName, appVersion);
	label->setText(QString("%1 v%2\nBy Kyoungman Kim\n2017").arg(appName).arg(appVersion));
}

void AboutDialog::onPushButton()
{
	close();
}

