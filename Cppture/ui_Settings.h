/********************************************************************************
** Form generated from reading UI file 'Settingsh14224.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SETTINGSH14224_H
#define SETTINGSH14224_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settings
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *applyButton;
    QTabWidget *tabWidget;
    QWidget *generalTab;
    QGroupBox *hotkeyGroupBox;
    QWidget *formLayoutWidget;
    QFormLayout *hotkeyFormLayout;
    QLabel *hotkey1Label;
    QLabel *hotkey2Label;
    QLabel *hotkey3Label;
    QPushButton *hotkey1Button;
    QPushButton *hotkey2Button;
    QPushButton *hotkey3Button;
    QGroupBox *saveGroupBox;
    QWidget *formLayoutWidget_2;
    QFormLayout *saveFormLayout;
    QCheckBox *saveToLocalCheckBox;
    QLabel *filenameFormatLabel;
    QLineEdit *filenameFormatLineEdit;
    QComboBox *fileExtensionComboBox;
    QWidget *unusedTab;

    void setupUi(QDialog *settings)
    {
        if (settings->objectName().isEmpty())
            settings->setObjectName(QStringLiteral("settings"));
        settings->setWindowModality(Qt::ApplicationModal);
        settings->resize(480, 320);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settings->sizePolicy().hasHeightForWidth());
        settings->setSizePolicy(sizePolicy);
        gridLayoutWidget = new QWidget(settings);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 481, 321));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        cancelButton = new QPushButton(gridLayoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        gridLayout->addWidget(cancelButton, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        okButton = new QPushButton(gridLayoutWidget);
        okButton->setObjectName(QStringLiteral("okButton"));

        gridLayout->addWidget(okButton, 1, 1, 1, 1);

        applyButton = new QPushButton(gridLayoutWidget);
        applyButton->setObjectName(QStringLiteral("applyButton"));
        applyButton->setEnabled(false);

        gridLayout->addWidget(applyButton, 1, 3, 1, 1);

        tabWidget = new QTabWidget(gridLayoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        generalTab = new QWidget();
        generalTab->setObjectName(QStringLiteral("generalTab"));
        hotkeyGroupBox = new QGroupBox(generalTab);
        hotkeyGroupBox->setObjectName(QStringLiteral("hotkeyGroupBox"));
        hotkeyGroupBox->setGeometry(QRect(10, 10, 441, 101));
        formLayoutWidget = new QWidget(hotkeyGroupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 10, 441, 91));
        hotkeyFormLayout = new QFormLayout(formLayoutWidget);
        hotkeyFormLayout->setObjectName(QStringLiteral("hotkeyFormLayout"));
        hotkeyFormLayout->setContentsMargins(5, 5, 5, 5);
        hotkey1Label = new QLabel(formLayoutWidget);
        hotkey1Label->setObjectName(QStringLiteral("hotkey1Label"));

        hotkeyFormLayout->setWidget(0, QFormLayout::LabelRole, hotkey1Label);

        hotkey2Label = new QLabel(formLayoutWidget);
        hotkey2Label->setObjectName(QStringLiteral("hotkey2Label"));

        hotkeyFormLayout->setWidget(1, QFormLayout::LabelRole, hotkey2Label);

        hotkey3Label = new QLabel(formLayoutWidget);
        hotkey3Label->setObjectName(QStringLiteral("hotkey3Label"));

        hotkeyFormLayout->setWidget(2, QFormLayout::LabelRole, hotkey3Label);

        hotkey1Button = new QPushButton(formLayoutWidget);
        hotkey1Button->setObjectName(QStringLiteral("hotkey1Button"));
        hotkey1Button->setCheckable(true);

        hotkeyFormLayout->setWidget(0, QFormLayout::FieldRole, hotkey1Button);

        hotkey2Button = new QPushButton(formLayoutWidget);
        hotkey2Button->setObjectName(QStringLiteral("hotkey2Button"));
        hotkey2Button->setCheckable(true);

        hotkeyFormLayout->setWidget(1, QFormLayout::FieldRole, hotkey2Button);

        hotkey3Button = new QPushButton(formLayoutWidget);
        hotkey3Button->setObjectName(QStringLiteral("hotkey3Button"));
        hotkey3Button->setCheckable(true);

        hotkeyFormLayout->setWidget(2, QFormLayout::FieldRole, hotkey3Button);

        saveGroupBox = new QGroupBox(generalTab);
        saveGroupBox->setObjectName(QStringLiteral("saveGroupBox"));
        saveGroupBox->setGeometry(QRect(10, 120, 441, 121));
        formLayoutWidget_2 = new QWidget(saveGroupBox);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 10, 441, 111));
        saveFormLayout = new QFormLayout(formLayoutWidget_2);
        saveFormLayout->setObjectName(QStringLiteral("saveFormLayout"));
        saveFormLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        saveFormLayout->setRowWrapPolicy(QFormLayout::DontWrapRows);
        saveFormLayout->setContentsMargins(5, 5, 5, 5);
        saveToLocalCheckBox = new QCheckBox(formLayoutWidget_2);
        saveToLocalCheckBox->setObjectName(QStringLiteral("saveToLocalCheckBox"));

        saveFormLayout->setWidget(0, QFormLayout::SpanningRole, saveToLocalCheckBox);

        filenameFormatLabel = new QLabel(formLayoutWidget_2);
        filenameFormatLabel->setObjectName(QStringLiteral("filenameFormatLabel"));

        saveFormLayout->setWidget(1, QFormLayout::SpanningRole, filenameFormatLabel);

        filenameFormatLineEdit = new QLineEdit(formLayoutWidget_2);
        filenameFormatLineEdit->setObjectName(QStringLiteral("filenameFormatLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(filenameFormatLineEdit->sizePolicy().hasHeightForWidth());
        filenameFormatLineEdit->setSizePolicy(sizePolicy1);
        filenameFormatLineEdit->setMaximumSize(QSize(150, 16777215));
        filenameFormatLineEdit->setBaseSize(QSize(0, 0));
        filenameFormatLineEdit->setLayoutDirection(Qt::RightToLeft);

        saveFormLayout->setWidget(2, QFormLayout::LabelRole, filenameFormatLineEdit);

        fileExtensionComboBox = new QComboBox(formLayoutWidget_2);
        fileExtensionComboBox->setObjectName(QStringLiteral("fileExtensionComboBox"));
        sizePolicy.setHeightForWidth(fileExtensionComboBox->sizePolicy().hasHeightForWidth());
        fileExtensionComboBox->setSizePolicy(sizePolicy);

        saveFormLayout->setWidget(2, QFormLayout::FieldRole, fileExtensionComboBox);

        tabWidget->addTab(generalTab, QString());
        unusedTab = new QWidget();
        unusedTab->setObjectName(QStringLiteral("unusedTab"));
        tabWidget->addTab(unusedTab, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 4);


        retranslateUi(settings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(settings);
    } // setupUi

    void retranslateUi(QDialog *settings)
    {
        settings->setWindowTitle(QApplication::translate("settings", "Settings", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("settings", "&Cancel", Q_NULLPTR));
        okButton->setText(QApplication::translate("settings", "&OK", Q_NULLPTR));
        applyButton->setText(QApplication::translate("settings", "&Apply", Q_NULLPTR));
        hotkeyGroupBox->setTitle(QApplication::translate("settings", "Hotkeys", Q_NULLPTR));
        hotkey1Label->setText(QApplication::translate("settings", "Capture Fullscreen", Q_NULLPTR));
        hotkey2Label->setText(QApplication::translate("settings", "Capture Current Window", Q_NULLPTR));
        hotkey3Label->setText(QApplication::translate("settings", "Capture Selected Area", Q_NULLPTR));
        hotkey1Button->setText(QApplication::translate("settings", "PushButton", Q_NULLPTR));
        hotkey2Button->setText(QApplication::translate("settings", "PushButton", Q_NULLPTR));
        hotkey3Button->setText(QApplication::translate("settings", "PushButton", Q_NULLPTR));
        saveGroupBox->setTitle(QApplication::translate("settings", "Save", Q_NULLPTR));
        saveToLocalCheckBox->setText(QApplication::translate("settings", "Save to Local Directory", Q_NULLPTR));
        filenameFormatLabel->setText(QApplication::translate("settings", "Filename Format", Q_NULLPTR));
        fileExtensionComboBox->clear();
        fileExtensionComboBox->insertItems(0, QStringList()
         << QApplication::translate("settings", ".png", Q_NULLPTR)
         << QApplication::translate("settings", ".jpg", Q_NULLPTR)
         << QApplication::translate("settings", ".gif", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(generalTab), QApplication::translate("settings", "General", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(unusedTab), QApplication::translate("settings", "Unused", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class settings: public Ui_settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SETTINGSH14224_H
