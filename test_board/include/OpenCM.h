/*
 *   OpenCM.h
 *
 *   Author: bottega
 *
 */

#ifndef OPENCM_H_
#define OPENCM_H_

#include "MX28.h"
#include "dynamixel.h"

namespace Robot
{
    class BulkReadData
    {
    public:
        int start_address;
        int length;
        int error;
        unsigned char table[MX28::MAXNUM_ADDRESS];

        BulkReadData();
        virtual ~BulkReadData() {}

        int ReadByte(int address);
        int ReadWord(int address);
    };
    
	class OpenCM
	{
	public:
		enum
		{
			SUCCESS,
			TX_CORRUPT,
			TX_FAIL,
			RX_FAIL,
			RX_TIMEOUT,
			RX_CORRUPT
		};

		enum
		{
			ID_CM			= 200,
			ID_BROADCAST	= 254
		};

	private:
		static const int RefreshTime = 6; //msec
		unsigned char m_ControlTable[MAXNUM_ADDRESS];

		unsigned char m_BulkReadTxPacket[MAXNUM_TXPARAM + 10];

	public:
		bool DEBUG_PRINT;
        BulkReadData m_BulkReadData[ID_BROADCAST];

		CM730(PlatformCM730 *platform);
		~CM730();

		// For board
		int WriteByte(int address, int value, int *error);
		int WriteWord(int address, int value, int *error);

		// For actuators
		int Ping(int id, int *error);
		int ReadByte(int id, int address, int *pValue, int *error);
		int ReadWord(int id, int address, int *pValue, int *error);
		int ReadTable(int id, int start_addr, int end_addr, unsigned char *table, int *error);
		int WriteByte(int id, int address, int value, int *error);
		int WriteWord(int id, int address, int value, int *error);

		// For motion control
		int SyncWrite(int start_addr, int each_length, int number, int *pParam);

		void MakeBulkReadPacket();
        int BulkRead();

		// Utility
		static int MakeWord(int lowbyte, int highbyte);
		static int GetLowByte(int word);
		static int GetHighByte(int word);
		static int MakeColor(int red, int green, int blue);

	};
}

#endif