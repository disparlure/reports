#include "trafficreport.h"
#include <iostream>
#include <cstring>
#define MAX_LATLON_BYTES 0x800000
#define MAX_LATLON_DEGREES 180

namespace trafficreportapp {

TrafficReport::TrafficReport(uint8_t* pData) {
  m_message = std::make_unique<TRAFFICMESSAGE>();
  memcpy(m_message.get(), pData, sizeof(TRAFFICMESSAGE));
}

  // Get message id
  unsigned short TrafficReport::GetMessageId(){
    if(m_message != nullptr) {
      return m_message->messageId;
    }
    return 0;
  }

  // Get report status
  STATUSTYPE TrafficReport::GetReportStatus(){
    if(m_message != nullptr) {
      int status = (m_message->st & 0xf0) >> 4;
      if(status <= static_cast<int>(STATUSTYPE::status_reserved)) {
        return static_cast<STATUSTYPE>(status);
      }
    }
    return STATUSTYPE::status_invalid;
  }

  // Get address type
  ADDRESSTYPE TrafficReport::GetAddressType(){
    if(m_message != nullptr) {
      int address = (m_message->st & 0x0f);
      if(address <= static_cast<int>(ADDRESSTYPE::address_reserved)) {
        return static_cast<ADDRESSTYPE>(address);
      }
    }
    return ADDRESSTYPE::address_invalid;
  }

  // Get Participant address
  unsigned int TrafficReport::GetParticipantAddress(){
    if(m_message != nullptr) {
      return (m_message->aa[2] << 16) | (m_message->aa[1] << 8) | (m_message->aa[0]);
    }
    return 0;
  }

  // Get Latitude in decimal degrees
  double TrafficReport::GetLatitudeDeg(){
    if(m_message != nullptr) {
      int rawValue = (m_message->ll[2] << 16) | (m_message->ll[1] << 8) | (m_message->ll[0]);
      if (rawValue & MAX_LATLON_BYTES){
        rawValue = ~rawValue & (MAX_LATLON_BYTES-1);
        return (double)rawValue / (MAX_LATLON_BYTES) * (-1*MAX_LATLON_DEGREES);
      } else {
        return (double)rawValue / (MAX_LATLON_BYTES-1) * MAX_LATLON_DEGREES;
      }
    }
    return 0;
  }

  // Get Lonitude in decimal degrees.
  double TrafficReport::GetLongitudeDeg(){
    if(m_message != nullptr) {
      int rawValue = (m_message->nn[2] << 16) | (m_message->nn[1] << 8) | (m_message->nn[0]);
      if (rawValue & MAX_LATLON_BYTES){
        rawValue = ~rawValue & (MAX_LATLON_BYTES-1);
        return (double)rawValue / (MAX_LATLON_BYTES-1) * (-1*MAX_LATLON_DEGREES);
      } else {
        return (double)rawValue / (MAX_LATLON_BYTES-1) * MAX_LATLON_DEGREES;
      }
    }
    return 0;
  }

// Get altitude in feet. 25ft resolution. Limit 101350ft
int TrafficReport::GetAltitudeFt(){
  if(m_message != nullptr) {
    int rawValue = (m_message->dd << 8) | (m_message->dm >> 8);
    if (rawValue < 0xfff) {
      return (rawValue * 25) - 1000;
    } else {
      return -99999;
    }
  }
  return -99999;
}

// Get horizontal velocity in kts. Limit to 4094kts. -99999 indicates no data.
int TrafficReport::GetHorizVelocityKts(){
  if(m_message != nullptr) {
    int rawValue = (m_message->hh << 8) | (m_message->hv >> 8);
    if (rawValue == 0xFFF) {
      return -99999;
    } else if (rawValue >= 0xFFE) {
      rawValue = 0xFFE;
    }
    else {
      return rawValue;
    }
  }
  return -99999;
}

// Get vertical velocity. Limit to +/- 32756fpm. -99999 indicates no data.
int TrafficReport::GetVerticalVelocityFps(){
  if (m_message != nullptr) {
    int rawValue = ((m_message->hv & 0x0F) << 8) | m_message->vv;

    //Limit
    if (rawValue > 0x1FD && rawValue < 0x800) {
      rawValue = 0x1FD;
    }

    //Limit
    if (rawValue > 0x800 && rawValue < 0xE03) {
      rawValue = 0xE03;
    }

    // No-data marker
    if (rawValue == 0x800) {
      return -99999;
    }

    // 2s c
    if (rawValue & 0x800){
      rawValue = ((~rawValue & (0x800-1))+1) * -1;
    }

    return rawValue * 64;
  }
  return -99999;
}

// Get the heading data
short TrafficReport::GetTrackHeading() {
  if (m_message != nullptr) {
    return(((double)m_message->tt / 0xFF) * 360);
  }
  return -1;
}

// Retrieve callsign - max 6 chars
std::string TrafficReport::GetCallsign(){
  std::string retVal = "";
  if(m_message != nullptr) {
    retVal.assign(m_message->cc,8);
  }
  return retVal;
}
}
