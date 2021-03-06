/*
 * Copyright (C) 2006-2018 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef YARP_YARPROBOTINTERFACE_CALIBRATORTHREAD_H
#define YARP_YARPROBOTINTERFACE_CALIBRATORTHREAD_H

#include "Types.h"

#include <yarp/os/Thread.h>

namespace yarp { namespace os { class Semaphore; } }
namespace yarp { namespace dev { class ICalibrator; } }
namespace yarp { namespace dev { class DeviceDriver; } }

namespace RobotInterface {

class CalibratorThread: public yarp::os::Thread
{
public:
    enum Action {
        ActionCalibrate,
        ActionPark
    };

    CalibratorThread(yarp::dev::ICalibrator *calibrator,
                     const std::string &calibratorName,
                     yarp::dev::DeviceDriver *target,
                     const std::string &targetName,
                     RobotInterface::CalibratorThread::Action action);
    virtual ~CalibratorThread();

    void run() override;
    void onStop() override;

private:
    class Private;
    Private * const mPriv;
};

} // namespace RobotInterface

#endif // YARP_YARPROBOTINTERFACE_CALIBRATORTHREAD_H
