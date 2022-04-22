#include <memory>
#include <vector>
#include <map>
#include "trafficreport.h"
#include "reportmanager.h"


namespace trafficreportapp{

  bool reportmanager::LoadSampleData(uint8_t* pData, int nLen) {

    if (nLen % sizeof(TRAFFICMESSAGE) != 0) {
      return false;
    }

    for(int x = 0; x < nLen; x+=sizeof(TRAFFICMESSAGE)){
      pTrafficReport repItem = std::make_shared<TrafficReport>(pData + x);
      m_reports.push_back(repItem);
      if (m_latestReports.count(repItem->GetParticipantAddress()) == 0) {
        m_latestReports.emplace(repItem->GetParticipantAddress(), repItem);
      } else {
        m_latestReports[repItem->GetParticipantAddress()] = repItem;
      }
    }
    return true;
  }

  trafficReportCollection reportmanager::GetAllReports() {
    return m_reports;
  }

  trafficReportCollection reportmanager::GetLatestReportsForAddresses() {
    trafficReportCollection result;
    for (const auto&item : m_latestReports) {
      result.push_back(item.second);
    }
    return result;
  }
}
