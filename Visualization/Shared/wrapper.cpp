//
//  wrapper.cpp
//  Visualization (iOS)
//
//  Created by Christine Fletcher on 4/23/22.
//
#include "trafficreport.h"
#include "reportmanager.h"
#include "RawData.h"

static trafficreportapp::reportmanager repMgr;

const char* GetAddressTypeText(trafficreportapp::ADDRESSTYPE type){
    switch(type){
        case trafficreportapp::ADDRESSTYPE::address_invalid:
            return "invalid";
        case trafficreportapp::ADDRESSTYPE::ADSB_IACO:
        case trafficreportapp::ADDRESSTYPE::ADSB_Selfsigned:
            return "ADSB";
        case trafficreportapp::TISB_IACO:
        case trafficreportapp::TISB_Trackid:
            return "TISB";
        case trafficreportapp::Surface_vehicle:
            return "Surface Vehicle";
        case trafficreportapp::ground_station:
            return "Ground Station";
        default:
            return "unknown";
    };
    return "unknown";
}

extern "C" unsigned long getDataSize(){
    
    int rawDataSize = sizeof(rawData)/sizeof(rawData[0]);
    repMgr.LoadSampleData(rawData, rawDataSize);
    auto collection = repMgr.GetLatestReportsForAddresses();
    return collection.size();
    }

extern "C" void getDataAtIndex(int index,
                               char* pAddressBuffer,
                               double* pLatitude,
                               double* pLongitude,
                               int* pVerticalVelocity,
                               int addressBufferLen) {

    int rawDataSize = sizeof(rawData)/sizeof(rawData[0]);
    repMgr.LoadSampleData(rawData, rawDataSize);
    auto collection = repMgr.GetLatestReportsForAddresses();
    if (index <= collection.size()) {
        
        *pLatitude = collection[index]->GetLatitudeDeg();
        *pLongitude = collection[index]->GetLongitudeDeg();
        *pVerticalVelocity = collection[index]->GetVerticalVelocityFps();
        
        snprintf(pAddressBuffer, addressBufferLen, "%s-%u",
                 GetAddressTypeText(collection[index]->GetAddressType()),
                 collection[index]->GetParticipantAddress());
    }
        
}


