/*
 * Copyright 2003, 2004 Andrew De Ponte
 * 
 * This file is part of zsrep.
 * 
 * zsrep is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * zsrep is distributed in the hopes that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with zsrep; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ZMainWin.h"

ZMainWin::ZMainWin(QWidget *parent, const char *name, WFlags f)
    : QMainWindow(parent, name, f) 
{
    confExists = 0;
    if (!name)
	    setName("ZMainWin");

    setCaption("Zync Graphical User Interface");

    // Now I create a grid layout.
    setCentralWidget(new QWidget(this, "qt_central_widget"));
    pZMainWinLayout = new QGridLayout(centralWidget(), 1, 1, 11, 6,
				      "ZMainWinLayout");

    pSyncGroupBox = new QGroupBox(centralWidget(), "SyncGroupBox");
    pSyncGroupBox->setTitle(tr("Synchronize"));
    pSyncGroupBox->setColumnLayout(0, Qt::Vertical);
    pSyncGroupBox->layout()->setSpacing(6);
    pSyncGroupBox->layout()->setMargin(11);
    pSyncGroupBoxLayout = new QGridLayout(pSyncGroupBox->layout());
    pSyncGroupBoxLayout->setAlignment(Qt::AlignTop);

    // Here I setup all the buttons that go inside the sync group box.
    pTodoPushButton = new QPushButton( pSyncGroupBox, "TodoPushButton" );
    pTodoPushButton->setText(tr("To-Do"));
    pSyncGroupBoxLayout->addWidget(pTodoPushButton, 1, 0);

    pCalPushButton = new QPushButton( pSyncGroupBox, "CalPushButton" );
    pCalPushButton->setText(tr("Calendar"));
    pSyncGroupBoxLayout->addWidget(pCalPushButton, 2, 0);

    pAddrPushButton = new QPushButton( pSyncGroupBox, "AddrPushButton" );
    pAddrPushButton->setText(tr("Address Book"));
    pSyncGroupBoxLayout->addWidget(pAddrPushButton, 3, 0);

    pAllPushButton = new QPushButton( pSyncGroupBox, "AllPushButton" );
    pAllPushButton->setText(tr("All"));
    pSyncGroupBoxLayout->addWidget(pAllPushButton, 4, 0);

    pZMainWinLayout->addWidget(pSyncGroupBox, 0, 0);

    // Here I setup the exit and configure buttons.
    pConfPushButton = new QPushButton(centralWidget(), "ConfPushButton");
    pConfPushButton->setText(tr("Configure"));
    pZMainWinLayout->addWidget(pConfPushButton, 1, 0);

    pAboutPushButton = new QPushButton(centralWidget(), "AboutPushButton");
    pAboutPushButton->setText(tr("About"));
    pZMainWinLayout->addWidget(pAboutPushButton, 2, 0);

    pExitPushButton = new QPushButton(centralWidget(), "ExitPushButton");
    pExitPushButton->setText(tr("Exit"));
    pZMainWinLayout->addWidget(pExitPushButton, 3, 0);

    // Here I setup the text edit widget.
    pLogTextEdit = new QTextEdit(centralWidget(), "LogTextEdit");
    pLogTextEdit->setReadOnly(TRUE);
    pZMainWinLayout->addMultiCellWidget(pLogTextEdit, 0, 3, 1, 1);

    // Here I create the about dialog box.
    pAboutDlg = new QDialog(this, "AboutDlg");
    pAboutCont = new QTextEdit(pAboutDlg, "AboutCont");
    pAboutCont->setReadOnly(TRUE);
    pAboutCont->append("<b>zync-gui v0.1.2</b>\n");
    pAboutCont->append("Bringing Zaurus synchronization to all Linux users.");
    pAboutCont->append("<p><b>License:</b><br>zync-gui is licensed under the GNU General Public License v2. The license can be found at <a href=\"http://www.gnu.org\">www.gnu.org</a>.");
    pAboutCont->append("<p><b>Author(s):</b><br>Andrew De Ponte (cyphactor@socal.rr.com)<br> -- Founder, Lead Developer.</p>");
    pAboutCont->resize(400, 200);
    pAboutDlg->setCaption(tr("About zync-gui"));

    printf("Created About Dialog.\n");

    // This line is causing the segfault, it must be something that is
    // happening in the constructor of ZConfDlg.
    //pConfDlg = new ZConfDlg(this, "ZConfDlg");

    printf("Created ZConfDlg.\n");

    // Here I make all the connections between the buttons.
    connect(pExitPushButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(pConfPushButton, SIGNAL(clicked()), this, SLOT(configure()));
    connect(pTodoPushButton, SIGNAL(clicked()), this, SLOT(syncTodo()));
    connect(pCalPushButton, SIGNAL(clicked()), this, SLOT(syncCal()));
    connect(pAddrPushButton, SIGNAL(clicked()), this, SLOT(syncAddr()));
    connect(pAllPushButton, SIGNAL(clicked()), this, SLOT(syncAll()));
    connect(pAboutPushButton, SIGNAL(clicked()), this, SLOT(dispAbout()));

    printf("Finished setup.\n");
}

void ZMainWin::syncTodo() {
    char buff[256];
    int bytesRead;

    cmdOutput = popen("zync -t", "r");
    if (!cmdOutput) {
	QMessageBox::critical(0, "zync-gui", QString("Failed to popen ") +
			      "zync -t.");
    }

    //pLogTextEdit->clear();
    bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    while (bytesRead) {
	buff[bytesRead] = '\0';

	pLogTextEdit->append(QString(buff));

	bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    }

    if (pclose(cmdOutput) == -1) {
	    QMessageBox::critical(0, "zync-gui", QString("Failed to pclose."));	
    }
}

void ZMainWin::syncCal() {
    char buff[256];
    int bytesRead;

    cmdOutput = popen("zync -c", "r");
    if (!cmdOutput) {
	QMessageBox::critical(0, "zync-gui", QString("Failed to popen ") +
			      "zync -c.");
    }

    //pLogTextEdit->clear();
    bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    while (bytesRead) {
	buff[bytesRead] = '\0';

	pLogTextEdit->append(QString(buff));

	bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    }

    if (pclose(cmdOutput) == -1) {
	QMessageBox::critical(0, "zync-gui", QString("Failed to pclose."));	
    }
}

void ZMainWin::syncAddr() {
    char buff[256];
    int bytesRead;

    cmdOutput = popen("zync -a", "r");
    if (!cmdOutput) {
	QMessageBox::critical(0, "zync-gui", QString("Failed to popen ") +
			      "zync -a.");
    }

    //pLogTextEdit->clear();
    bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    while (bytesRead) {
	buff[bytesRead] = '\0';

	pLogTextEdit->append(QString(buff));

	bytesRead = fread((char *)buff, 1, 255, cmdOutput);
    }

    if (pclose(cmdOutput) == -1) {
	QMessageBox::critical(0, "zync-gui", QString("Failed to pclose."));
    }
}

void ZMainWin::syncAll() {
    //pLogTextEdit->clear();
    syncTodo();
    syncCal();
    syncAddr();
}

void ZMainWin::configure() {
    if (!confExists) {
        pConfDlg = new ZConfDlg(this, "ZConfDlg");
        confExists = 1;
    }
    pConfDlg->show();
}

void ZMainWin::dispAbout() {
    pAboutDlg->show();
}
