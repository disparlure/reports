#pragma once
#include <memory>
#pragma pack(1)

namespace trafficreportapp {

  typedef unsigned char BYTE;

  // Status types
  typedef enum STATUSTYPEtag {
    status_invalid = -1,
    no_alert,
    traffic_alert,
    status_reserved
  } STATUSTYPE;

  // Address types
  typedef enum ADDRESSTYPEtag {
    address_invalid = -1,
    ADSB_IACO,
    ADSB_Selfsigned,
    TISB_IACO,
    TISB_Trackid,
    Surface_vehicle,
    ground_station,
    address_reserved
  } ADDRESSTYPE;

  // NIC Statuses
  typedef enum NICSTATUStag {
    NIC_unknown,
    NIC_lt20nm,
    NIC_lt8nm,
    NIC_lt4nm,
    NIC_lt2nm,
    NIC_lt1nm,
    NIC_lt0_6nm,
    NIC_lt0_2nm,
    NIC_lt0_1nm,
    NIC_hpllt75Xvpl112,
    NIC_hpllt25Xvpl37_5,
    NIC_hpllt7_5Xvpl11,
    NIC_unused
  } NICSTATUS;

  // NACP Statuses
  typedef enum NACPSTATUStag {
    NACP_unknown,
    NACP_lt10nm,
    NACP_lt4nm,
    NACP_lt2nm,
    NACP_lt1nm,
    NACP_lt0_5nm,
    NACP_lt0_3nm,
    NACP_lt0_1nm,
    NACP_lt0_05nm,
    NACP_HFOM30mXVFOM45m,
    NACP_HFOM10mXVFOM15m,
    NACP_HFOM3mXVFOM4m,
    NACP_unused
  } NACPSTATUS;

  // Emitter categories
  typedef enum EMITTERCATEGORYtag {
    None,
    Light,
    Small,
    Large,
    HighVortexLarge,
    Heavy,
    HighlyManeuverable,
    Rotorcraft,
    unassigned_1,
    Glider,
    LighterThanAir,
    Parachutist,
    Ultralight,
    unassigned_2,
    UAV,
    SpaceVehicle,
    unassigned_3,
    Surfacevehicle_emergency,
    Surfacevehicle_normal,
    PointObstacle,
    ClusterObstacle,
    LineObstacle,
    emitter_reserved
  } EMITTERCATEGORY;

  // Emergency codes
  typedef enum EMERGENCYCODEtag {
    no_emergency,
    general_emergency,
    medical_emergency,
    miniumum_fuel,
    no_communication,
    unlawful_interference,
    downed_aircraft,
    reserved
  } EMERGENCYCODE;

  // structure representing the memory organization of the message
  typedef struct TRAFFICMESSAGEtag{
    BYTE messageId;

    BYTE st;          // Status / Alert
    BYTE aa[3];       // Participant Address (24bit)
    BYTE ll[3];       // Latitude (24bit)
    BYTE nn[3];       // Longitude (24bit)
    BYTE dd;          // Altitude 12-bit (byte 1-2)
    BYTE dm;          // Altitude (byte 3)/ Misc Indicator
    BYTE ia;          // Integrity / Accuracy
    BYTE hh;          // Horiz Velocity (byte 1-2)
    BYTE hv;          // Horiz Velocity (byte 3)/ Vertical Velocity (byte 1)
    BYTE vv;          // Vertical Velocity (byte 2-3)
    BYTE tt;          // Track/heading 8-bit
    BYTE ee;          // Emitter Category
    char cc[8];       // Callsign (8 ASCII chars)
    BYTE px;          // PriorityCode/Spare-reserved
  } TRAFFICMESSAGE;

  // The TrafficReport class - responsible for decoding the traffic report
  class TrafficReport {
    public:
       // C'tor - takes pointer to byte array containing the data
       TrafficReport(uint8_t* pBytes);
       // D'tor
       ~TrafficReport() {};

       unsigned short GetMessageId();
       STATUSTYPE GetReportStatus();

       ADDRESSTYPE GetAddressType();
       unsigned int GetParticipantAddress();

       double GetLatitudeDeg();
       double GetLongitudeDeg();

       int GetAltitudeFt();

       NICSTATUS GetNICStatus();
       NACPSTATUS GetNACPStatus();

       int GetHorizVelocityKts();
       int GetVerticalVelocityFps();

       short GetTrackHeading();

       EMITTERCATEGORY GetEmitterCategory();
       std::string GetCallsign();

       EMERGENCYCODE GetEmergencyCode();

    private:
      std::unique_ptr<TRAFFICMESSAGE> m_message;
  };
}
