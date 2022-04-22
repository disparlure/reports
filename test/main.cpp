#include <stdint.h>
#include <iostream>
#include "reportmanager.h"
#include "RawData.h"
#include <cstring>
#include <iomanip>

using namespace trafficreportapp;

// Helper to get a print-friendly name from the status
std::string GetStatusString(STATUSTYPE type) {
  switch(type) {
    case STATUSTYPE::status_invalid:
      return "invalid";
      break;
    case STATUSTYPE::no_alert:
      return "no-alert";
      break;
    case STATUSTYPE::traffic_alert:
      return "traffic alert";
      break;
    default:
      return "unknown";
  }
}

// Helper to get a print-friendly address type
std::string GetAddressTypeText(ADDRESSTYPE type){
  switch (type){
    case ADDRESSTYPE::address_invalid:
      return "invalid";
      break;
    case ADDRESSTYPE::ADSB_IACO:
    case ADDRESSTYPE::ADSB_Selfsigned:
      return "ADSB";
      break;
    case ADDRESSTYPE::TISB_IACO:
    case ADDRESSTYPE::TISB_Trackid:
      return "TISB";
      break;
    case ADDRESSTYPE::Surface_vehicle:
      return "surface vehicle";
      break;
    case ADDRESSTYPE::ground_station:
      return "ground station";
      break;
    default:
      return "unknown";
  }
}

// Basic test cases - show all reports, show latest reports for an address
int main(int argc, char *argv[]) {

  int rawDataSize = sizeof(rawData)/sizeof(rawData[0]);

  reportmanager rm;
  rm.LoadSampleData(rawData, rawDataSize);

  std::cout << std::setw(4) << "MessageId\t"
            << std::setw(4) << "Status\t"
            << std::setw(8)<< "Callsign\t"
            << std::setw(12)<< "Address\t"
            << std::setw(12)<< "Latitude\t"
            << std::setw(12)<< "Longitude\t"
            << std::setw(12)<< "Altitude\t"
            << std::setw(12)<< "VertVelocity\t"
            << std::setw(12)<< "Heading\t"
            << std::setw(12)<< "HorizontalVelocity" << std::endl;

  if (argc == 2 && strcmp(argv[1], "latest")==0) {
    for(auto repItem : rm.GetLatestReportsForAddresses()){

      std::cout << std::setw(4) << repItem->GetMessageId() << "\t"
                << std::setw(4) << GetStatusString(repItem->GetReportStatus()) << "\t"
                << std::setw(12) << repItem->GetCallsign() << "\t"
                << std::setw(12) << GetAddressTypeText(repItem->GetAddressType ()) << repItem->GetParticipantAddress() << "\t"
                << std::setw(12) << repItem->GetLatitudeDeg() << "\t"
                << std::setw(12) << repItem->GetLongitudeDeg() << "\t"
                << std::setw(12) << repItem->GetAltitudeFt() << "\t"
                << std::setw(12) << repItem->GetVerticalVelocityFps()
                << std::setw(12) << repItem->GetTrackHeading() << "\t"
                << std::setw(12) << repItem->GetHorizVelocityKts() << std::endl;
    }
  } else {
    for(auto repItem : rm.GetAllReports()){
      std::cout << std::setw(4) << repItem->GetMessageId() << "\t"
                << std::setw(4) << GetStatusString(repItem->GetReportStatus()) << "\t"
                << std::setw(12) << repItem->GetCallsign() << "\t"
                << std::setw(12) << GetAddressTypeText(repItem->GetAddressType ()) << repItem->GetParticipantAddress() << "\t"
                << std::setw(12) << repItem->GetLatitudeDeg() << "\t"
                << std::setw(12) << repItem->GetLongitudeDeg() << "\t"
                << std::setw(12) << repItem->GetAltitudeFt() << "\t"
                << std::setw(12) << repItem->GetVerticalVelocityFps() << "\t"
                << std::setw(12) << repItem->GetTrackHeading() << "\t"
                << std::setw(12) << repItem->GetHorizVelocityKts() << std::endl;
    }
  }



}
