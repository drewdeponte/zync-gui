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

#ifndef ZCONFDLG_H
#define ZCONFDLG_H

#include <stdlib.h>
#include <dlfcn.h>
#include <confmgr/ConfigManagerType.h>
#include <zync/TodoPluginType.hh>

#include <iostream>

#include <qdir.h>
#include <qstringlist.h>
#include <qmap.h>

#include <qdialog.h>
#include <qmessagebox.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qtabwidget.h>
#include <qwidget.h>
#include <qtextedit.h>

typedef QMap<QString, QString> PluginMapType;

class ZConfDlg : public QDialog {
    Q_OBJECT
public:
    ZConfDlg(QWidget *parent = 0, const char *name = 0,
	     bool modal = TRUE, WFlags f = 0);

public slots:
    void updatePluginDesc(const QString & string); 
    void saveConfig();
signals:
    void configUpdated();

private:
    QString GetTodoPluginName(QString pluginPath);
    QString GetTodoPluginDesc(QString pluginPath);

    bool origConfigHasPass;

    PluginMapType todoPluginMap;
    PluginMapType calPluginMap;
    PluginMapType addrPluginMap;

    QString todoPluginPath;

    QString confPath;
    ConfigManagerType confManager;

    QGridLayout *pZConfDlgLayout;
    QLineEdit *pZIpLineEdit;
    QComboBox *pConfWinComboBox;
    QCheckBox *pPasswdCheckBox;
    QLineEdit *pPasswdLineEdit;
    QPushButton *pApplyButton;
    QPushButton *pCancelButton;
    QGroupBox *pPluginGroupBox;
    QTabWidget *pPluginTabWidget;
    QWidget *pTodoTab;
    QComboBox *pTodoPluginComboBox;
    QTextEdit *pTodoPluginDesc;
    QWidget *pCalTab;
    QComboBox *pCalPluginComboBox;
    QTextEdit *pCalPluginDesc;
    QWidget *pAddrTab;
    QComboBox *pAddrPluginComboBox;
    QTextEdit *pAddrPluginDesc;
};

#endif
