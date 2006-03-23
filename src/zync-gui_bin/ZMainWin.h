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

#ifndef ZMAINWIN_H
#define ZMAINWIN_H

#include <iostream>

#include <stdio.h>

#include <qmainwindow.h>
#include <qdialog.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qapplication.h>

#include "ZConfDlg.h"

class ZMainWin : public QMainWindow {
    Q_OBJECT
public:
    ZMainWin(QWidget *parent = 0, const char *name = 0,
	     WFlags f = WType_TopLevel);

public slots:
    void syncTodo();
    void syncCal();
    void syncAddr();
    void syncAll();
    void configure();
    void dispAbout();
signals:

private:
    QGridLayout *pZMainWinLayout;
    QGroupBox *pSyncGroupBox;
    QGridLayout *pSyncGroupBoxLayout;
    QPushButton *pTodoPushButton;
    QPushButton *pCalPushButton;
    QPushButton *pAddrPushButton;
    QPushButton *pAllPushButton;
    QPushButton *pAboutPushButton;
    QPushButton *pConfPushButton;
    QPushButton *pExitPushButton;
    QTextEdit *pLogTextEdit;

    QDialog *pAboutDlg;
    QTextEdit *pAboutCont;

    ZConfDlg *pConfDlg;
    int confExists;

    FILE *cmdOutput;
};

#endif
