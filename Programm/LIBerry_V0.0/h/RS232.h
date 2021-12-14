#ifndef RS232_H
#define RS232_H

enum
{
// Frame IDs (Commands)
kGetModInfo = 1, 		// 1
kModInfoResp, 			// 2
kSetDataComponents, 	// 3
kGetData, 				// 4
kDataResp, 				// 5
kSetConfig, 			// 6
kGetConfig, 			// 7
kConfigResp, 			// 8
kSave, 					// 9
kStartCal, 				// 10
kStopCal, 				// 11
kSetParam, 				// 12
kGetParam, 				// 13
kParamResp, 			// 14
kPowerDown, 			// 15
kSaveDone, 				// 16
kUserCalSampCount, 		// 17
kUserCalScore, 			// 18
kSetConfigDone, 		// 19
kSetParamDone, 			// 20
kStartIntervalMode,		// 21
kStopIntervalMode, 		// 22
kPowerUp, 				// 23
kSetAcqParams, 			// 24
kGetAcqParams, 			// 25
kAcqParamsDone, 		// 26
kAcqParamsResp, 		// 27
kPowerDoneDown, 		// 28
kFactoryUserCal, 		// 29
kFactoryUserCalDone, 	// 30
kTakeUserCalSample, 	// 31
// Param IDs
kFIRConfig = 1, 		// 3-AxisID(UInt8)+Count(UInt8)+Value(Float64)+...
// Data Component IDs
kHeading = 5, 			// 5 - type Float32
kTemperature = 7, 		// 7 - type Float32
kDistortion = 8, 		// 8 - type boolean
kPCalibrated = 21, 		// 21 - type Float32
kRCalibrated, 			// 22 - type Float32
kIZCalibrated, 			// 23 - type Float32
kPAngle, 				// 24 - type Float32
kRAngle, 				// 25 - type Float32
kXAligned = 27, 		// 27 - type Float32
kYAligned, 				// 28 - type Float32
kZAligned, 				// 29 - type Float32
// Configuration Parameter IDs
kDeclination = 1, 		// 1 - type Float32
kTrueNorth,				// 2 - type boolean
kMountingRef = 10, 		// 10 - type UInt8
kUserCalStableCheck, 	// 11 - type boolean
kUserCalNumPoints, 		// 12 - type UInt32
kUserCalAutoSampling, 	// 13 – type boolean
kBaudRate, // 14 – UInt8
// Mounting Reference IDs
kMountedStandard = 1, 	// 1
kMountedXUp, 			// 2
kMountedYUp, 			// 3
kMountedStdPlus90, 		// 4
kMountedStdPlus180, 	// 5
kMountedStdPlus270, 	// 6
// Result IDs
kErrNone = 0, // 0
kErrSave, // 1
};



typedef struct
{
  uint16_t command;
  uint16_t data;  //uint8_t -1- 4091 ??
  uint16_t CRC_;   //
}_Structur;


void ID_Sendrequest();
uint16_t RS_CRC(void * data, uint32_t len);
uint16_t CommProtocol_SendData(_Structur data,uint8_t byte);


  #endif /* LED_H */
