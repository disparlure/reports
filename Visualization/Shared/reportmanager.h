#pragma once
#include <memory>
#include <vector>
#include <map>
#include "trafficreport.h"

namespace trafficreportapp {
  typedef std::shared_ptr<TrafficReport> pTrafficReport;
  typedef std::vector<pTrafficReport> trafficReportCollection;

  // A report collection class to handle bulk-parsing,
  // and filtering reports
  class reportmanager {
  public:
      reportmanager() {};
      ~reportmanager() {};

      bool LoadSampleData(uint8_t* pData, int nLen);

      // Get the latest reports for each address
      trafficReportCollection GetLatestReportsForAddresses();

      // Get all of the reports
      trafficReportCollection GetAllReports();

    private:
      trafficReportCollection m_reports;
      std::map<int,pTrafficReport> m_latestReports;
  };
}
