/*
 * casocklib - An asynchronous communication library for C++
 * ---------------------------------------------------------
 * Copyright (C) 2010 Leandro Costa
 *
 * This file is part of casocklib.
 *
 * casocklib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * casocklib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with casocklib. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file casock/rpc/protobuf/server/RPCServerProxy.cc
 * \brief [brief description]
 * \author Leandro Costa
 * \date 2010
 *
 * $LastChangedDate$
 * $LastChangedBy$
 * $Revision$
 */

#include "casock/rpc/protobuf/server/RPCServerProxy.h"

#include "casock/util/Logger.h"
#include "casock/rpc/protobuf/server/RPCCallQueue.h"
#include "casock/rpc/protobuf/server/RPCCallHandler.h"
#include "casock/rpc/protobuf/server/RPCCallHandlerFactory.h"

namespace casock {
  namespace rpc {
    namespace protobuf {
      namespace server {
        RPCServerProxy::RPCServerProxy (const RPCCallHandlerFactory& rCallHandlerFactory)
          : mpCallQueue (new RPCCallQueue ()), mrCallHandlerFactory (rCallHandlerFactory)
        {
          LOGMSG (HIGH_LEVEL, "%s\n", __PRETTY_FUNCTION__);
        }

        RPCServerProxy::~RPCServerProxy ()
        {
          /*!
           * The call handlers are threads waiting for messages in the call queue.
           * Before we delete the call queue we need to cancel the call handlers.
           */
          LOGMSG (LOW_LEVEL, "%s - remove call handlers...\n", __PRETTY_FUNCTION__);
          removeCallHandlers (mCallHandlers.size ());

          delete mpCallQueue;
        }

        casock::util::Thread* RPCServerProxy::buildCallHandler ()
        {
          return mrCallHandlerFactory.buildRPCCallHandler (*mpCallQueue);
        }
      }
    }
  }
}
