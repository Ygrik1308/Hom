#include "main.h"
/////////////////////////////////////////////
#if defined SMBus    // chip
///////////////////////////////////////
#include "SMBus.h"


uint8_t SMBus_ReadByte(uint8_t slaveAddr, uint8_t readAddr)
{
	uint16_t res;
	SMBus_ReadWord(slaveAddr, &res, readAddr);
	return res;
}
#endif //SMBus

