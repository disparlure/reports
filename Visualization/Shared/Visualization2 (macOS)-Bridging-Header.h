//
//  Use this file to import your target's public headers that you would like to expose to Swift.
//

unsigned long getDataSize();
void getDataAtIndex(int index,
                               char* pAddressBuffer,
                               double* pLatitude,
                               double* pLongitude,
                               int* pVerticalVelocity,
                               int addressBufferLen);
