/*
 * PrintParted is a program for viewing table of disk partitions
 * Copyright (C) 2021  Vadim Berezin
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "include/widget.h"
#include "include/part.h"
#include <unistd.h>
#include <sys/types.h>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    uid_t uid = getuid();
    uid_t euid = geteuid();

     if (euid != 0) {

        cout << "You don't have root permissions. Please run the program as root\n";
        a.exit();

   } else {

        Widget w;
        w.createSplash(":/splash/pic.png");
        QEventLoop loop;
        QTimer::singleShot(1000, &loop, &QEventLoop::quit);
        loop.exec();
        w.resize(1300, 900);
        w.show();
        return a.exec();

   }
}
