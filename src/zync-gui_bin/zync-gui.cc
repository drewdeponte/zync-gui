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

#include <qapplication.h>

#include "ZMainWin.h"

int main( int argc, char **argv ) {
    QApplication a( argc, argv );

    ZMainWin mainWin(0, "zync-gui");

    a.setMainWidget(&mainWin);
    printf("Set the main widget.\n");
    mainWin.show();

    return a.exec();
}
