/*MT*
    
    MediaTomb - http://www.mediatomb.cc/
    
    sopcast_service.h - this file is part of MediaTomb.
    
    Copyright (C) 2005 Gena Batyan <bgeradz@mediatomb.cc>,
                       Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>
    
    Copyright (C) 2006-2010 Gena Batyan <bgeradz@mediatomb.cc>,
                            Sergey 'Jin' Bostandzhyan <jin@mediatomb.cc>,
                            Leonhard Wimmer <leo@mediatomb.cc>
    
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2
    as published by the Free Software Foundation.
    
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    version 2 along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
    
    $Id$
*/

/// \file sopcast_service.h
/// \brief Definition of the SopCastService class.

#ifdef SOPCAST

#ifndef __SOPCAST_SERVICE_H__
#define __SOPCAST_SERVICE_H__

#include <curl/curl.h>
#include <memory>
#include <pugixml.hpp>

#include "online_service.h"

// forward declaration
class Config;
class ContentManager;
class Database;

/// \brief This is an interface for all online services, the function
/// handles adding/refreshing content in the database.
class SopCastService : public OnlineService {
public:
    explicit SopCastService(std::shared_ptr<ContentManager> content);
    ~SopCastService() override;

    /// \brief Retrieves user specified content from the service and adds
    /// the items to the database.
    bool refreshServiceData(std::shared_ptr<Layout> layout) override;

    /// \brief Get the type of the service (i.e. SopCast, Shoutcast, etc.)
    service_type_t getServiceType() override;

    /// \brief Get the human readable name for the service
    std::string getServiceName() const override;

protected:
    // the handle *must never be used from multiple threads*
    CURL* curl_handle;
    // safeguard to ensure the above
    pthread_t pid;

    /// \brief This function will retrieve the XML according to the parametrs
    std::unique_ptr<pugi::xml_document> getData();
};

#endif //__ONLINE_SERVICE_H__

#endif //SOPCAST
