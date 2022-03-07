#pragma once
/*
 *   The Falcon Player (FPP) is free software; you can redistribute it
 *   and/or modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include <condition_variable>
#include <list>
#include <map>
#include <mutex>
#include <set>
#include <thread>

class WarningListener {
public:
    virtual void handleWarnings(std::list<std::string>& warnings) = 0;
};

class WarningHolder {
public:
    static void AddWarning(const std::string& w);
    static void RemoveWarning(const std::string& w);
    static void AddWarningTimeout(const std::string& w, int seconds);

    static void AddWarningListener(WarningListener* l);
    static void RemoveWarningListener(WarningListener* l);

    static std::list<std::string> GetWarnings();
    static void StartNotifyThread();
    static void StopNotifyThread();
    static void NotifyListenersMain(); // main for notify thread

private:
    static std::mutex warningsLock;
    static std::mutex notifyLock;
    static std::condition_variable notifyCV;
    static std::map<std::string, int> warnings;
    static std::thread* notifyThread;
    static std::set<WarningListener*> listenerList;
    static std::mutex listenerListLock;
    static volatile bool runNotifyThread;
};
