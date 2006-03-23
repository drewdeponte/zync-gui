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

#include "ZConfDlg.h"

ZConfDlg::ZConfDlg(QWidget *parent, const char *name,
		   bool modal, WFlags f)
    : QDialog(parent, name, modal, f) 
{
    char *pEnvVarVal;
    int retval;
    char optVal[256];

    origConfigHasPass = FALSE;

    // First things first, I want this dialog to be modal (not allow access to
    // the windows below it once it has been opened).
    setModal(TRUE);
    setCaption(tr("Configuration"));

    // Now that I have setup the dialog the way I wanted, I create a grid
    // layout so that I can organize widgets in the dialog easily.
    pZConfDlgLayout = new QGridLayout(this, 1, 1, 11, 6, "ZConfDlgLayout");

    // In this section I create the Zaurus IP entry area and its label.
    QLabel *pZIpLabel = new QLabel(this, "ZIpLabel");
    pZIpLabel->setAlignment(int(QLabel::AlignVCenter));
    pZIpLabel->setText(tr("Zaurus IP:"));
    pZConfDlgLayout->addWidget(pZIpLabel, 0, 0);

    pZIpLineEdit = new QLineEdit(this, "ZIpLineEdit");
    pZIpLineEdit->setMaxLength(15);
    pZConfDlgLayout->addMultiCellWidget(pZIpLineEdit, 0, 0, 1, 2);

    // In this section I create the Conflict Winner label and combo box.
    QLabel *pConfWinLabel = new QLabel(this, "ConfWinLabel");
    pConfWinLabel->setAlignment(int(QLabel::AlignVCenter));
    pConfWinLabel->setText(tr("Conflict Winner:"));
    pZConfDlgLayout->addWidget(pConfWinLabel, 1, 0);

    pConfWinComboBox = new QComboBox(FALSE, this, "ConfWinComboBox");
    pZConfDlgLayout->addMultiCellWidget(pConfWinComboBox, 1, 1, 1, 2);
    pConfWinComboBox->clear();
    pConfWinComboBox->insertItem(tr("Both"));
    pConfWinComboBox->insertItem(tr("Zaurus"));
    pConfWinComboBox->insertItem(tr("Desktop"));

    // In this section I create the Save Password check box and the password
    // entry field.
    pPasswdCheckBox = new QCheckBox(this, "PasswdCheckBox");
    pPasswdCheckBox->setEnabled(TRUE);
    pPasswdCheckBox->setText(tr("Save Passcode:"));
    pZConfDlgLayout->addMultiCellWidget(pPasswdCheckBox, 2, 2, 0, 1);

    pPasswdLineEdit = new QLineEdit(this, "PasswdLineEdit");
    pPasswdLineEdit->setEnabled(FALSE);
    pPasswdLineEdit->setEchoMode(QLineEdit::Password);
    pZConfDlgLayout->addWidget(pPasswdLineEdit, 2, 2);

    // In this section I create the Apply and Cancel buttons.
    pApplyButton = new QPushButton(this, "ApplyButton");
    pApplyButton->setText(tr("Apply"));
    pZConfDlgLayout->addWidget(pApplyButton, 0, 3);
    pCancelButton = new QPushButton(this, "CancelButton");
    pCancelButton->setText(tr("Cancel"));
    pZConfDlgLayout->addWidget(pCancelButton, 1, 3);

    // In this section I create the Plug-in Group box to house the tabbed
    // plug-in selection widgets.
    pPluginGroupBox = new QGroupBox(this, "PluginGroupBox");
    pPluginGroupBox->setFrameShape(QGroupBox::Box);
    pPluginGroupBox->setFrameShadow(QGroupBox::Sunken);
    pPluginGroupBox->setAlignment(int(QGroupBox::AlignHCenter));
    pPluginGroupBox->setFlat(TRUE);
    pPluginGroupBox->setTitle(tr("Desktop Plug-in Selections"));
    pZConfDlgLayout->addMultiCellWidget(pPluginGroupBox, 3, 3, 0, 3);

    // In this section I fill the Plug-in Group box I just created with a
    // tabbed widet which will provide a mechanism for selecting plugins.
    pPluginTabWidget = new QTabWidget(pPluginGroupBox, "PluginTabWidget");
    pPluginTabWidget->setGeometry(QRect(0, 20, 370, 160));

    // In this section I create the Todo Tab for the tabbed widget and fill it
    // with the proper widgets.
    pTodoTab = new QWidget(pPluginTabWidget, "TodoTab");
    pPluginTabWidget->insertTab(pTodoTab, "To-Do");

    pTodoPluginComboBox = new QComboBox(FALSE, pTodoTab, "TodoPluginComboBox");
    pTodoPluginComboBox->setGeometry(QRect(10, 10, 340, 30));

    pTodoPluginDesc = new QTextEdit(pTodoTab, "TodoPluginDesc");
    pTodoPluginDesc->setGeometry(QRect(10, 50, 340, 70));
    pTodoPluginDesc->setReadOnly(TRUE);

    printf("created todo plugin desc box.\n");

    // The segfault occurs when I do this section!!!!!!!!!
    todoPluginPath = QString("/usr/local/lib/zync/plugins/todo/");
    QDir todoPluginDir(todoPluginPath);
    QStringList todoPlugins;
    todoPlugins = todoPluginDir.entryList("*.so");

    for (QStringList::Iterator it = todoPlugins.begin();
        it != todoPlugins.end(); ++it) {
        QString fooBar((*it));
        // The following either two lines cause a segfault.
        QString pluginName(GetTodoPluginName(todoPluginPath + (*it)));
        //QString pluginDesc(GetTodoPluginDesc(todoPluginPath + (*it)));
        printf("Testing: %s.\n", fooBar.ascii());
        printf("Testing: %s.\n", pluginName.ascii());
        pTodoPluginComboBox->insertItem(tr(fooBar));
    }

    
    /*
    for (QStringList::Iterator it = todoPlugins.begin();
	    it != todoPlugins.end(); ++it) {
    	QString pluginName(GetTodoPluginName(todoPluginPath + (*it)));
    	QString pluginDesc(GetTodoPluginDesc(todoPluginPath + (*it)));
    	todoPluginMap[pluginName] = (*it);
    	pTodoPluginComboBox->insertItem(tr(pluginName));
    }
    */

    /*

    printf("filled in the todo plugin info.\n");

    // In this section I create the Calendar Tab for the tabbed widget and
    // fill it with the proper widgets.
    pCalTab = new QWidget(pPluginTabWidget, "CalTab");
    pPluginTabWidget->insertTab(pCalTab, "Calendar");

    pCalPluginComboBox = new QComboBox(FALSE, pCalTab, "CalPluginComboBox");
    pCalPluginComboBox->setGeometry(QRect(10, 10, 340, 30));

    pCalPluginDesc = new QTextEdit(pCalTab, "CalPluginDesc");
    pCalPluginDesc->setGeometry(QRect(10, 50, 340, 70));
    pCalPluginDesc->setReadOnly(TRUE);

    // In this section I create the Address Boox Tab for the tabbed widget and
    // fill it with the proper widgets.
    pAddrTab = new QWidget(pPluginTabWidget, "AddrTab");
    pPluginTabWidget->insertTab(pAddrTab, "Address Book");

    pAddrPluginComboBox = new QComboBox(FALSE, pAddrTab, "AddrPluginComboBox");
    pAddrPluginComboBox->setGeometry(QRect(10, 10, 340, 30));

    pAddrPluginDesc = new QTextEdit(pAddrTab, "AddrPluginDesc");
    pAddrPluginDesc->setGeometry(QRect(10, 50, 340, 70));
    pAddrPluginDesc->setReadOnly(TRUE);

    printf("Created addr plugin desc box.\n");

    // Here I resize the dialog to a size which I like.
    //resize(QSize(391, 301).expandedTo(minimumSizeHint()));

    // Now I start to set the connections between the signals and the slots.

    // This first connection connects the save passcode check box to the
    // enable/disable feature of the passcode line edit.
    connect(pPasswdCheckBox, SIGNAL(toggled(bool)), pPasswdLineEdit,
	    SLOT(setEnabled(bool)));

    connect(pCancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    connect(pTodoPluginComboBox, SIGNAL(activated(const QString &)), this,
	    SLOT(updatePluginDesc(const QString &)));

    connect(pApplyButton, SIGNAL(clicked()), this, SLOT(saveConfig()));
    //connect(this, SIGNAL(configUpdated()), this, SLOT(accept()));

    // Here I try to obtain in the needed config content and set the values of
    // the proper widgets based on it.
    pEnvVarVal = getenv("HOME");
    if (!pEnvVarVal) {
	    QMessageBox::critical(0, "zync-gui", QString("Failed to obtain") +
			      " value of HOME environment variable.");
    }

    confPath = QString(pEnvVarVal);
    confPath.append("/.zync.conf");

    printf("Created the zync.conf path.\n");

    // At this point the full path to the config for the user which is running
    // this application has been built. Hence, I try and load the config file.
    retval = confManager.Open((char *)confPath.ascii());
    printf("Finished opening the file, %d.\n", retval);
    if (retval != 0) {
        printf("Err: Failed to open %s for reading.\n",
            (char *)confPath.ascii());
            */
            /*
	    QMessageBox::critical(0, "zync-gui", QString("Failed to open ") +
			      confPath + " for reading. Please click the" + 
			      " \"Configure\" button and configure zync.");
                  */
                  /*
    }

    printf("Opened the zync.conf file.\n");

    // Now that I have opened the config file I want to go through and set all
    // the widget values based on the config options.
    retval = confManager.GetValue("zaurus_ip", optVal, 256);
    if (retval == 0) {
	    QString zIp(optVal);
	    pZIpLineEdit->setText(tr(zIp));
    }

    retval = confManager.GetValue("conflict_winner", optVal, 256);
    if (retval == 0) {
	    QString confWinner(optVal);
    	if (confWinner == QString("both")) {
	        pConfWinComboBox->setCurrentText("Both");
	    } else if (confWinner == QString("zaurus")) {
	        pConfWinComboBox->setCurrentText("Zaurus");
	    } else if (confWinner == QString("desktop")) {
	        pConfWinComboBox->setCurrentText("Desktop");
	    }
    }

    retval = confManager.GetValue("passcode", optVal, 256);
    if (retval == 0) {
	    QString passcode(optVal);
	    pPasswdCheckBox->setChecked(TRUE);
	    pPasswdLineEdit->setText(passcode);
	    origConfigHasPass = TRUE;
    }

    retval = confManager.GetValue("todo_plugin_path", optVal, 256);
    if (retval == 0) {
	if (!todoPlugins.isEmpty()) {
	    QString todoPluginPath(optVal);
	    QString confTodoPluginName = GetTodoPluginName(todoPluginPath);
	    pTodoPluginComboBox->setCurrentText(confTodoPluginName);
	}
    }

    // Now I need to load the Descriptions for the plugin selections and set
    // them.
    if (!todoPlugins.isEmpty()) {
	    QString curPluginDesc;
	    QString curPluginFileName;
	    curPluginFileName = todoPluginMap[pTodoPluginComboBox->currentText()];
	    curPluginDesc = GetTodoPluginDesc(todoPluginPath + curPluginFileName);
	    pTodoPluginDesc->setText(curPluginDesc);
    } else {
	    pTodoPluginDesc->setText(tr("No Plugins Found!"));
    }
    */
    printf("Finished ZConfDlg Constructor.\n");
}

void ZConfDlg::updatePluginDesc(const QString & string) {
    printf("Entered the updatePluginDesc func.\n");
    QString curPluginDesc;
    QString curPluginFileName;

    curPluginFileName = todoPluginMap[string];
    curPluginDesc = GetTodoPluginDesc(todoPluginPath + curPluginFileName);
    pTodoPluginDesc->setText(curPluginDesc);
    printf("Exiting the updatePluginDesc func.\n");
}

void ZConfDlg::saveConfig() {
    printf("Entered the saveConfig function.\n");
    int retval;

    // Here I handle the storing of the value of Zaurus IP LineEdit.
    QString zaurusIp;
    zaurusIp = pZIpLineEdit->text();
    retval = confManager.SetValue("zaurus_ip", (char *)zaurusIp.ascii());
    if (retval != 0) {
        /*
	    QMessageBox::critical(0, "zync-gui",
			      QString("Failed to set zaurus_ip value. "));
        */
        printf("Foo BARRRRRRRR, failed to set the zaurus ip.\n");    
    }

    // Here I handle the storing of the value of the Conflict Winner ComboBox.
    QString confWin;
    // A variable used to store the proper value to save in the config file.
    QString saveConfWin;
    confWin = pConfWinComboBox->currentText();
    if (confWin == QString("Both")) {
	    saveConfWin = "both";
    } else if (confWin == QString("Zaurus")) {
	    saveConfWin = "zaurus";
    } else if (confWin == QString("Desktop")) {
	    saveConfWin = "desktop";
    }
    retval = confManager.SetValue("conflict_winner",
				  (char *)saveConfWin.ascii());
    if (retval != 0) {
	    QMessageBox::critical(0, "zync-gui",
			      QString("Failed to set conflict_winner value."));
    }


    // Here I handle the saving of the passcode status and value.
    if (pPasswdCheckBox->isChecked()) {
	    // Save the passcode
	    QString passcode;
	    passcode = pPasswdLineEdit->text();
	    retval = confManager.SetValue("passcode", (char *)passcode.ascii());
	    if (retval != 0) {
	        QMessageBox::critical(0, "zync-gui",
				  QString("Failed to set passcod value."));
	    }
    } else {
	    if (origConfigHasPass) {
	        // Delete the passcode from the config.
	        retval = confManager.DeleteItem("passcode");
	        if (retval != 0) {
		        QMessageBox::critical(0, "zync-gui",
				    QString("Failed to delete passcode item."));
		
	        }
	    }
    }

    // Here I handle the saving of the To-Do plugin ComboBox
    QString curPluginName;
    QString curPluginFileName;
    QString curPluginPath;
    curPluginName = pTodoPluginComboBox->currentText();
    curPluginFileName = todoPluginMap[curPluginName];
    curPluginPath = todoPluginPath + curPluginFileName;
    retval = confManager.SetValue("todo_plugin_path",
				  (char *)curPluginPath.ascii());
    if (retval != 0) {
	    QMessageBox::critical(0, "zync-gui",
			      QString("Failed to set todo_plugin_path value."));
    }
    
    retval = confManager.Save((char *)confPath.ascii());
    if (retval != 0) {
	    QMessageBox::critical(0, "zync-gui",
			      QString("Failed to save ") + confPath + ".");
	    reject();
    } else {
	    emit configUpdated();
	    accept();
    }

    printf("Exiting the saveConfig() function.\n");
}

QString ZConfDlg::GetTodoPluginName(QString pluginPath) {
    printf("Entering GetTodoPluginName().\n");
    QString name("Shitting");
    QString bs("Fucking");

    void *libHandle;

    printf("Attempting to open %s.\n", pluginPath.ascii());
    libHandle = dlopen(pluginPath.ascii(), RTLD_LAZY);
    if (!libHandle) {
        printf("Err: failed in call to dlopen.\n");
        return bs;
    }

    dlclose(libHandle);
    
    printf("Exiting GetTodoPluginName().\n");
    return name;
    /*
    printf("Entering the GetTodoPluginName() function.\n");
    void *libHandle;
    create_todo_t pCreateFunc;
    destroy_todo_t pDestroyFunc;
    TodoPluginType *pTodoPlugin;
    QString name;
    printf("Created the functions variables.\n");

    // Open the plugin and load the creation and destroy symbols.
    libHandle = dlopen(pluginPath.ascii(), RTLD_LAZY);
    if (!libHandle) {
        return QString("Failed to open .so file.");
    }

    pCreateFunc = (create_todo_t)dlsym(libHandle, "createTodoPlugin");
    if (!pCreateFunc) {
        return QString("Failed to get create symbol.");
    }

    pDestroyFunc = (destroy_todo_t)dlsym(libHandle, "destroyTodoPlugin");
    if (!pDestroyFunc) {
        return QString("Failed to get destroy symbol.");
    }

    pTodoPlugin = pCreateFunc();
    if (!pTodoPlugin) {
        return QString("Failed to create object.");
    }

    // At this point it should be opened.
    name = QString(pTodoPlugin->GetPluginName());

    pDestroyFunc(pTodoPlugin);
    dlclose(libHandle);

    printf("Exiting the GetTodoPluginName() function.\n");
    return name;
    */
}


QString ZConfDlg::GetTodoPluginDesc(QString pluginPath) {
    printf("Entering the GetTodoPluginDesc() function.\n");
    void *libHandle;
    create_todo_t pCreateFunc;
    destroy_todo_t pDestroyFunc;
    TodoPluginType *pTodoPlugin;
    QString desc;

    // Open the plugin and load the creation and destroy symbols.
    libHandle = dlopen(pluginPath.ascii(), RTLD_LAZY);
    if (!libHandle) {
	return QString("Failed to open .so file.");
    }

    pCreateFunc = (create_todo_t)dlsym(libHandle, "createTodoPlugin");
    if (!pCreateFunc) {
	return QString("Failed to get create symbol.");
    }

    pDestroyFunc = (destroy_todo_t)dlsym(libHandle, "destroyTodoPlugin");
    if (!pDestroyFunc) {
	return QString("Failed to get destroy symbol.");
    }

    pTodoPlugin = pCreateFunc();
    if (!pTodoPlugin) {
	return QString("Failed to create object.");
    }

    // At this point it should be opened.
    desc = QString(pTodoPlugin->GetPluginDescription());

    pDestroyFunc(pTodoPlugin);
    dlclose(libHandle);

    printf("Exiting the GetTodoPluginDesc() function.\n");
    return desc;
}
