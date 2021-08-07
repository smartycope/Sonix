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
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
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
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *cover;
    QLabel *titleLabel;
    QLabel *authorLabel;
    QLabel *narratorLabel;
    QHBoxLayout *horizontalLayout;
    QPushButton *jumpBackButton;
    QPushButton *skipBackButton;
    QPushButton *pauseButton;
    QPushButton *skipForwardButton;
    QPushButton *jumpForwardButton;
    QDoubleSpinBox *speedControl;
    QProgressBar *progressBar;
    QSlider *volumeControl;
    QMenuBar *menubar;
    QMenu *menuControls;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlayerWindow)
    {
        if (PlayerWindow->objectName().isEmpty())
            PlayerWindow->setObjectName(QString::fromUtf8("PlayerWindow"));
        PlayerWindow->resize(800, 617);
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
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        cover = new QLabel(horizontalLayoutWidget_2);
        cover->setObjectName(QString::fromUtf8("cover"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cover->sizePolicy().hasHeightForWidth());
        cover->setSizePolicy(sizePolicy);
        cover->setMinimumSize(QSize(0, 350));
        cover->setMaximumSize(QSize(350, 16777215));
        cover->setPixmap(QPixmap(QString::fromUtf8("../assets/defaultBookCover.png")));
        cover->setScaledContents(true);
        cover->setAlignment(Qt::AlignCenter);
        cover->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_3->addWidget(cover);


        verticalLayout->addLayout(horizontalLayout_3);

        titleLabel = new QLabel(horizontalLayoutWidget_2);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        authorLabel = new QLabel(horizontalLayoutWidget_2);
        authorLabel->setObjectName(QString::fromUtf8("authorLabel"));
        authorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(authorLabel);

        narratorLabel = new QLabel(horizontalLayoutWidget_2);
        narratorLabel->setObjectName(QString::fromUtf8("narratorLabel"));
        narratorLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(narratorLabel);

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

        speedControl = new QDoubleSpinBox(horizontalLayoutWidget_2);
        speedControl->setObjectName(QString::fromUtf8("speedControl"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(speedControl->sizePolicy().hasHeightForWidth());
        speedControl->setSizePolicy(sizePolicy1);
        speedControl->setMinimumSize(QSize(50, 25));
        speedControl->setMaximumSize(QSize(16777215, 16777215));
        speedControl->setAutoFillBackground(false);
        speedControl->setAlignment(Qt::AlignCenter);
        speedControl->setMinimum(0.050000000000000);
        speedControl->setMaximum(10.000000000000000);
        speedControl->setSingleStep(0.050000000000000);
        speedControl->setStepType(QAbstractSpinBox::AdaptiveDecimalStepType);
        speedControl->setValue(1.000000000000000);

        verticalLayout->addWidget(speedControl, 0, Qt::AlignHCenter);

        progressBar = new QProgressBar(horizontalLayoutWidget_2);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);
        progressBar->setOrientation(Qt::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::TopToBottom);

        verticalLayout->addWidget(progressBar);


        horizontalLayout_2->addLayout(verticalLayout);

        volumeControl = new QSlider(horizontalLayoutWidget_2);
        volumeControl->setObjectName(QString::fromUtf8("volumeControl"));
        volumeControl->setMaximum(100);
        volumeControl->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(volumeControl);

        PlayerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlayerWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menuControls = new QMenu(menubar);
        menuControls->setObjectName(QString::fromUtf8("menuControls"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        PlayerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(PlayerWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlayerWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuControls->menuAction());
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
        menuFile->addAction(actionQuit);

        retranslateUi(PlayerWindow);
        QObject::connect(actionPause, SIGNAL(toggled(bool)), pauseButton, SLOT(setChecked(bool)));
        QObject::connect(actionQuit, SIGNAL(triggered()), PlayerWindow, SLOT(close()));
        QObject::connect(pauseButton, SIGNAL(toggled(bool)), actionPause, SLOT(setChecked(bool)));

        jumpBackButton->setDefault(false);
        skipBackButton->setDefault(false);
        pauseButton->setDefault(false);
        skipForwardButton->setDefault(false);
        jumpForwardButton->setDefault(false);


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
        cover->setText(QString());
        titleLabel->setText(QCoreApplication::translate("PlayerWindow", "Title", nullptr));
        authorLabel->setText(QCoreApplication::translate("PlayerWindow", "Author", nullptr));
        narratorLabel->setText(QCoreApplication::translate("PlayerWindow", "Narrator", nullptr));
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
        speedControl->setSuffix(QCoreApplication::translate("PlayerWindow", "x", nullptr));
        progressBar->setFormat(QCoreApplication::translate("PlayerWindow", "%p%", nullptr));
        menuControls->setTitle(QCoreApplication::translate("PlayerWindow", "Controls", nullptr));
        menuFile->setTitle(QCoreApplication::translate("PlayerWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWindow: public Ui_PlayerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERWINDOW_H
