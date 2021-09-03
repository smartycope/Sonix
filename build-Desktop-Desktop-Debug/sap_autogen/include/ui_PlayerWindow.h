/********************************************************************************
** Form generated from reading UI file 'PlayerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERWINDOW_H
#define UI_PLAYERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWindow
{
public:
    QAction *actionPause;
    QAction *actionSkipForward;
    QAction *actionSkipBack;
    QAction *actionJumpForward;
    QAction *actionJumpBack;
    QAction *actionOpen;
    QAction *actionVolumeUp;
    QAction *actionVolumeDown;
    QAction *actionFaster;
    QAction *actionSlower;
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *paulBlart;
    QAction *actionOpenSettings;
    QAction *actionAuthcode;
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *cover;
    QHBoxLayout *horizontalLayout;
    QPushButton *jumpBackButton;
    QPushButton *skipBackButton;
    QPushButton *pauseButton;
    QPushButton *skipForwardButton;
    QPushButton *jumpForwardButton;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *chapterSelect;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QProgressBar *progressBar;
    QDoubleSpinBox *speedControl;
    QVBoxLayout *verticalLayout_5;
    QSlider *volumeControl;
    QSpacerItem *verticalSpacer;
    QCheckBox *muteButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *authorLabel;
    QLabel *label_2;
    QLabel *narratorLabel;
    QMenuBar *menubar;
    QMenu *menuControls;
    QMenu *menuFile;
    QMenu *menuSettings;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlayerWindow)
    {
        if (PlayerWindow->objectName().isEmpty())
            PlayerWindow->setObjectName(QString::fromUtf8("PlayerWindow"));
        PlayerWindow->resize(812, 616);
        actionPause = new QAction(PlayerWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        actionPause->setChecked(false);
        actionSkipForward = new QAction(PlayerWindow);
        actionSkipForward->setObjectName(QString::fromUtf8("actionSkipForward"));
        actionSkipBack = new QAction(PlayerWindow);
        actionSkipBack->setObjectName(QString::fromUtf8("actionSkipBack"));
        actionJumpForward = new QAction(PlayerWindow);
        actionJumpForward->setObjectName(QString::fromUtf8("actionJumpForward"));
        actionJumpBack = new QAction(PlayerWindow);
        actionJumpBack->setObjectName(QString::fromUtf8("actionJumpBack"));
        actionOpen = new QAction(PlayerWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionOpen->setAutoRepeat(true);
        actionVolumeUp = new QAction(PlayerWindow);
        actionVolumeUp->setObjectName(QString::fromUtf8("actionVolumeUp"));
        actionVolumeDown = new QAction(PlayerWindow);
        actionVolumeDown->setObjectName(QString::fromUtf8("actionVolumeDown"));
        actionFaster = new QAction(PlayerWindow);
        actionFaster->setObjectName(QString::fromUtf8("actionFaster"));
        actionSlower = new QAction(PlayerWindow);
        actionSlower->setObjectName(QString::fromUtf8("actionSlower"));
        actionQuit = new QAction(PlayerWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setMenuRole(QAction::QuitRole);
        actionAbout = new QAction(PlayerWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setMenuRole(QAction::AboutRole);
        paulBlart = new QAction(PlayerWindow);
        paulBlart->setObjectName(QString::fromUtf8("paulBlart"));
        QFont font;
        font.setFamily(QString::fromUtf8("Great Vibes"));
        paulBlart->setFont(font);
        paulBlart->setMenuRole(QAction::NoRole);
        actionOpenSettings = new QAction(PlayerWindow);
        actionOpenSettings->setObjectName(QString::fromUtf8("actionOpenSettings"));
        actionOpenSettings->setVisible(true);
        actionOpenSettings->setMenuRole(QAction::PreferencesRole);
        actionAuthcode = new QAction(PlayerWindow);
        actionAuthcode->setObjectName(QString::fromUtf8("actionAuthcode"));
        centralwidget = new QWidget(PlayerWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(0, 0, 801, 563));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        titleLabel = new QLabel(horizontalLayoutWidget_2);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setMinimumSize(QSize(0, 25));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cover = new QLabel(horizontalLayoutWidget_2);
        cover->setObjectName(QString::fromUtf8("cover"));
        cover->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cover->sizePolicy().hasHeightForWidth());
        cover->setSizePolicy(sizePolicy);
        cover->setMinimumSize(QSize(400, 400));
        cover->setMaximumSize(QSize(400, 400));
        cover->setSizeIncrement(QSize(1, 1));
        cover->setFrameShape(QFrame::StyledPanel);
        cover->setFrameShadow(QFrame::Sunken);
        cover->setPixmap(QPixmap(QString::fromUtf8("../assets/defaultBookCover.png")));
        cover->setScaledContents(true);
        cover->setAlignment(Qt::AlignCenter);
        cover->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_3->addWidget(cover);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        jumpBackButton = new QPushButton(horizontalLayoutWidget_2);
        jumpBackButton->setObjectName(QString::fromUtf8("jumpBackButton"));
        jumpBackButton->setAutoDefault(false);
        jumpBackButton->setFlat(true);

        horizontalLayout->addWidget(jumpBackButton);

        skipBackButton = new QPushButton(horizontalLayoutWidget_2);
        skipBackButton->setObjectName(QString::fromUtf8("skipBackButton"));
        skipBackButton->setAutoDefault(false);
        skipBackButton->setFlat(true);

        horizontalLayout->addWidget(skipBackButton);

        pauseButton = new QPushButton(horizontalLayoutWidget_2);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setCheckable(true);
        pauseButton->setChecked(false);
        pauseButton->setAutoDefault(false);
        pauseButton->setFlat(true);

        horizontalLayout->addWidget(pauseButton);

        skipForwardButton = new QPushButton(horizontalLayoutWidget_2);
        skipForwardButton->setObjectName(QString::fromUtf8("skipForwardButton"));
        skipForwardButton->setAutoDefault(false);
        skipForwardButton->setFlat(true);

        horizontalLayout->addWidget(skipForwardButton);

        jumpForwardButton = new QPushButton(horizontalLayoutWidget_2);
        jumpForwardButton->setObjectName(QString::fromUtf8("jumpForwardButton"));
        jumpForwardButton->setAutoDefault(false);
        jumpForwardButton->setFlat(true);

        horizontalLayout->addWidget(jumpForwardButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        chapterSelect = new QComboBox(horizontalLayoutWidget_2);
        chapterSelect->setObjectName(QString::fromUtf8("chapterSelect"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(chapterSelect->sizePolicy().hasHeightForWidth());
        chapterSelect->setSizePolicy(sizePolicy1);
        chapterSelect->setMinimumSize(QSize(80, 30));
        chapterSelect->setMaximumSize(QSize(500, 16777215));
        chapterSelect->setMaxVisibleItems(25);
        chapterSelect->setFrame(false);

        horizontalLayout_7->addWidget(chapterSelect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        progressBar = new QProgressBar(horizontalLayoutWidget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        horizontalLayout_6->addWidget(progressBar);

        speedControl = new QDoubleSpinBox(horizontalLayoutWidget_2);
        speedControl->setObjectName(QString::fromUtf8("speedControl"));
        sizePolicy1.setHeightForWidth(speedControl->sizePolicy().hasHeightForWidth());
        speedControl->setSizePolicy(sizePolicy1);
        speedControl->setMinimumSize(QSize(50, 30));
        speedControl->setMaximumSize(QSize(100, 16777215));
        speedControl->setAutoFillBackground(false);
        speedControl->setAlignment(Qt::AlignCenter);
        speedControl->setButtonSymbols(QAbstractSpinBox::PlusMinus);
        speedControl->setAccelerated(false);
        speedControl->setMinimum(0.050000000000000);
        speedControl->setMaximum(10.000000000000000);
        speedControl->setSingleStep(0.050000000000000);
        speedControl->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        speedControl->setValue(1.000000000000000);

        horizontalLayout_6->addWidget(speedControl);


        verticalLayout->addLayout(horizontalLayout_6);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        volumeControl = new QSlider(horizontalLayoutWidget_2);
        volumeControl->setObjectName(QString::fromUtf8("volumeControl"));
        volumeControl->setMaximum(100);
        volumeControl->setOrientation(Qt::Vertical);

        verticalLayout_5->addWidget(volumeControl);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer);

        muteButton = new QCheckBox(horizontalLayoutWidget_2);
        muteButton->setObjectName(QString::fromUtf8("muteButton"));
        muteButton->setChecked(false);

        verticalLayout_5->addWidget(muteButton);

        verticalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_5->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_5);

        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(590, 60, 361, 85));
        formLayoutWidget->setMinimumSize(QSize(100, 0));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(56, 0));
        label->setMaximumSize(QSize(51, 16777215));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        authorLabel = new QLabel(formLayoutWidget);
        authorLabel->setObjectName(QString::fromUtf8("authorLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(authorLabel->sizePolicy().hasHeightForWidth());
        authorLabel->setSizePolicy(sizePolicy2);
        authorLabel->setMinimumSize(QSize(116, 50));
        authorLabel->setMaximumSize(QSize(200, 16777215));
        authorLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        authorLabel->setWordWrap(true);
        authorLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        formLayout->setWidget(0, QFormLayout::FieldRole, authorLabel);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        narratorLabel = new QLabel(formLayoutWidget);
        narratorLabel->setObjectName(QString::fromUtf8("narratorLabel"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(narratorLabel->sizePolicy().hasHeightForWidth());
        narratorLabel->setSizePolicy(sizePolicy3);
        narratorLabel->setMinimumSize(QSize(116, 25));
        narratorLabel->setMaximumSize(QSize(116, 16777215));
        narratorLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        narratorLabel->setWordWrap(true);
        narratorLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

        formLayout->setWidget(1, QFormLayout::FieldRole, narratorLabel);

        PlayerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 30));
        menuControls = new QMenu(menubar);
        menuControls->setObjectName(QString::fromUtf8("menuControls"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        PlayerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlayerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlayerWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuControls->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuControls->addAction(actionPause);
        menuControls->addAction(actionSkipForward);
        menuControls->addAction(actionSkipBack);
        menuControls->addAction(actionJumpForward);
        menuControls->addAction(actionJumpBack);
        menuControls->addSeparator();
        menuControls->addAction(actionVolumeUp);
        menuControls->addAction(actionVolumeDown);
        menuControls->addAction(actionFaster);
        menuControls->addAction(actionSlower);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionAbout);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuSettings->addAction(actionOpenSettings);
        menuSettings->addAction(actionAuthcode);
        menuSettings->addSeparator();
        menuSettings->addAction(paulBlart);

        retranslateUi(PlayerWindow);
        QObject::connect(actionPause, SIGNAL(toggled(bool)), pauseButton, SLOT(setChecked(bool)));
        QObject::connect(actionQuit, SIGNAL(triggered()), PlayerWindow, SLOT(close()));
        QObject::connect(pauseButton, SIGNAL(toggled(bool)), actionPause, SLOT(setChecked(bool)));

        jumpBackButton->setDefault(false);
        skipBackButton->setDefault(false);
        pauseButton->setDefault(false);
        skipForwardButton->setDefault(false);
        jumpForwardButton->setDefault(false);
        chapterSelect->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(PlayerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *PlayerWindow)
    {
        PlayerWindow->setWindowTitle(QCoreApplication::translate("PlayerWindow", "SuperSonic Audiobook Player", nullptr));
        actionPause->setText(QCoreApplication::translate("PlayerWindow", "Pause/Play", nullptr));
#if QT_CONFIG(shortcut)
        actionPause->setShortcut(QCoreApplication::translate("PlayerWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSkipForward->setText(QCoreApplication::translate("PlayerWindow", "Skip Ahead", nullptr));
#if QT_CONFIG(tooltip)
        actionSkipForward->setToolTip(QCoreApplication::translate("PlayerWindow", "Skip forward 15 seconds", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSkipForward->setShortcut(QCoreApplication::translate("PlayerWindow", "Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSkipBack->setText(QCoreApplication::translate("PlayerWindow", "Skip Back", nullptr));
#if QT_CONFIG(tooltip)
        actionSkipBack->setToolTip(QCoreApplication::translate("PlayerWindow", "Skip Backward ", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSkipBack->setShortcut(QCoreApplication::translate("PlayerWindow", "Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionJumpForward->setText(QCoreApplication::translate("PlayerWindow", "Jump Ahead", nullptr));
#if QT_CONFIG(tooltip)
        actionJumpForward->setToolTip(QCoreApplication::translate("PlayerWindow", "Jump forward a chapter", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionJumpForward->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        actionJumpBack->setText(QCoreApplication::translate("PlayerWindow", "Jump Back", nullptr));
#if QT_CONFIG(tooltip)
        actionJumpBack->setToolTip(QCoreApplication::translate("PlayerWindow", "Jump back a chapter", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionJumpBack->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+Left", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("PlayerWindow", "Open...", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("PlayerWindow", "Open a new audio file", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionVolumeUp->setText(QCoreApplication::translate("PlayerWindow", "Volume Up", nullptr));
#if QT_CONFIG(tooltip)
        actionVolumeUp->setToolTip(QCoreApplication::translate("PlayerWindow", "Raise the volume", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionVolumeUp->setShortcut(QCoreApplication::translate("PlayerWindow", "Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionVolumeDown->setText(QCoreApplication::translate("PlayerWindow", "Volume Down", nullptr));
#if QT_CONFIG(tooltip)
        actionVolumeDown->setToolTip(QCoreApplication::translate("PlayerWindow", "Lower the volume", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionVolumeDown->setShortcut(QCoreApplication::translate("PlayerWindow", "Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionFaster->setText(QCoreApplication::translate("PlayerWindow", "Faster", nullptr));
#if QT_CONFIG(tooltip)
        actionFaster->setToolTip(QCoreApplication::translate("PlayerWindow", "Increase the playback speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionFaster->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+Up", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSlower->setText(QCoreApplication::translate("PlayerWindow", "Slower", nullptr));
#if QT_CONFIG(tooltip)
        actionSlower->setToolTip(QCoreApplication::translate("PlayerWindow", "Decrease the playback speed", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(shortcut)
        actionSlower->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+Down", nullptr));
#endif // QT_CONFIG(shortcut)
        actionQuit->setText(QCoreApplication::translate("PlayerWindow", "Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("PlayerWindow", "Close the program", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAbout->setText(QCoreApplication::translate("PlayerWindow", "About...", nullptr));
        paulBlart->setText(QCoreApplication::translate("PlayerWindow", "Paul Blart", nullptr));
#if QT_CONFIG(tooltip)
        paulBlart->setToolTip(QCoreApplication::translate("PlayerWindow", "\360\237\244\267", nullptr));
#endif // QT_CONFIG(tooltip)
        actionOpenSettings->setText(QCoreApplication::translate("PlayerWindow", "Open Settings", nullptr));
        actionAuthcode->setText(QCoreApplication::translate("PlayerWindow", "Enter Authcode", nullptr));
        titleLabel->setText(QString());
        cover->setText(QString());
        jumpBackButton->setText(QCoreApplication::translate("PlayerWindow", "|<", nullptr));
        skipBackButton->setText(QCoreApplication::translate("PlayerWindow", "<<", nullptr));
#if QT_CONFIG(shortcut)
        skipBackButton->setShortcut(QCoreApplication::translate("PlayerWindow", "Left", nullptr));
#endif // QT_CONFIG(shortcut)
        pauseButton->setText(QCoreApplication::translate("PlayerWindow", "||", nullptr));
#if QT_CONFIG(shortcut)
        pauseButton->setShortcut(QCoreApplication::translate("PlayerWindow", "Space", nullptr));
#endif // QT_CONFIG(shortcut)
        skipForwardButton->setText(QCoreApplication::translate("PlayerWindow", ">>", nullptr));
#if QT_CONFIG(shortcut)
        skipForwardButton->setShortcut(QCoreApplication::translate("PlayerWindow", "Right", nullptr));
#endif // QT_CONFIG(shortcut)
        jumpForwardButton->setText(QCoreApplication::translate("PlayerWindow", ">|", nullptr));
#if QT_CONFIG(shortcut)
        jumpForwardButton->setShortcut(QCoreApplication::translate("PlayerWindow", "Ctrl+Right", nullptr));
#endif // QT_CONFIG(shortcut)
        chapterSelect->setCurrentText(QString());
        chapterSelect->setPlaceholderText(QCoreApplication::translate("PlayerWindow", "No Chapters Available", nullptr));
        progressBar->setFormat(QCoreApplication::translate("PlayerWindow", "%p%", nullptr));
        speedControl->setSuffix(QCoreApplication::translate("PlayerWindow", "x", nullptr));
        muteButton->setText(QString());
        label->setText(QCoreApplication::translate("PlayerWindow", "Author:", nullptr));
        authorLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("PlayerWindow", "Narrator:", nullptr));
        narratorLabel->setText(QString());
        menuControls->setTitle(QCoreApplication::translate("PlayerWindow", "Controls", nullptr));
        menuFile->setTitle(QCoreApplication::translate("PlayerWindow", "File", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("PlayerWindow", "Options", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWindow: public Ui_PlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWINDOW_H
