#ifndef _A7105_RESG_H_
#define _A7105_RESG_H_

typedef enum {
	x00_MODE			=	0x00,
	x01_MODE_CONTROL	=	0x01,
	x02_CALC			=	0x02,
	x03_FIFO_I			=	0x03,
	x04_FIFO_II			=	0x04,
	x05_FIFO_DATA		=	0x05,
	x06_ID_DATA			=	0x06,
	x07_RC_OSC_I		=	0x07,
	x08_RC_OSC_II		=	0x08,
	x09_RC_OSC_III		=	0x09,
	x0A_CKO_PIN			=	0x0A,
	x0B_GPIO1_PIN_I		=	0x0B,
	x0C_GPIO2_PIN_II	=	0x0C,
	x0D_CLOCK			=	0x0D,
	x0E_DATA_RATE		=	0x0E,
	x0F_PLL_I			=	0x0F,
	x0F_CHANNEL			=	0x0F,
	x10_PLL_II			=	0x10,
	x11_PLL_III			=	0x11,
	x12_PLL_IV			=	0x12,
	x13_PLL_V			=	0x13,
	x14_TX_I			=	0x14,
	x15_TX_II			=	0x15,
	x16_DELAY_I			=	0x16,
	x17_DELAY_II		=	0x17,
	x18_RX				=	0x18,
	x19_RX_GAIN_I		=	0x19,
	x1A_RX_GAIN_II		=	0x1A,
	x1B_RX_GAIN_III		=	0x1B,
	x1C_RX_GAIN_IV		=	0x1C,
	x1D_RSSI_THRESHOLD	=	0x1D,
	x1E_ADC				=	0x1E,
	x1F_CODE_I			=	0x1F,
	x20_CODE_II			=	0x20,
	x21_CODE_III		=	0x21,
	x22_IF_CALIBRATION_I	=	0x22,
	x23_IF_CALIBRATION_II	=	0x23,
	x24_VCO_CURRENT_CALIBRATION	=	0x24,
	x25_VCO_SINGLE_BAND_CALIBRATION_I	=	0x25,
	x26_VCO_SINGLE_BAND_CALIBRATION_II	=	0x26,
	x27_BATTERY_DETECT	=	0x27,
	x28_TX_TEST			=	0x28,
	x29_RX_DEM_TEST_I	=	0x29,
	x2A_RX_DEM_TEST_II	=	0x2A,
	x2B_CPC				=	0x2B,
	x2C_CRYSTAL_TEST	=	0x2C,
	x2D_PLL_TEST		=	0x2D,
	x2E_VCO_TEST_I		=	0x2E,
	x2F_VCO_TEST_II		=	0x2F,
	x30_IFAT			=	0x30,
	x31_RSCALE			=	0x31,
	x32_FILTER_TEST		=	0x32
	} A7105_regs;
	
	

/*	Register: x00_MODE, R							*/
#define FECF 		0X40	// [0]: FEC pass. [1]: FEC error. (FECF is read only, it is updated internally while receiving every packet.)
#define CRCF 		0X20	// [0]: CRC pass. [1]: CRC error. (CRCF is read only, it is updated internally while receiving every packet.)
#define CER 		0X10	// [0]: RF chip is disabled. [1]: RF chip is enabled.
#define XER 		0X08	// [0]: Crystal oscillator is disabled. [1]: Crystal oscillator is enabled.
#define PLLER		0X04	// [0]: PLL is disabled. [1]: PLL is enabled.
#define TRSR 		0X02	// [0]: RX state. [1]: TX state. Serviceable if TRER=1 (TRX is enable).
#define TRER 		0X01	// [0]: TRX is disabled. [1]: TRX is enabled.

/*	Register: x01_MODE_CONTROL, W					*/
#define DDPC 		0X80	// DDPC (Direct mode data pin control): In Direct mode, If DDPC=1, MCU delivers / receives raw data of packet via SDIO pin instead of GIO1 or GIO2 pin.
#define ARSSI 		0X40	// ARSSI: Auto RSSI measurement while entering RX mode.
#define AIF 		0X20	// AIF (Auto IF Offset): RF LO frequency will auto offset one IF frequency while entering RX mode.
#define DFCD		0X10	// DFCD (Data Filter by CD): The received packet will be filtered out if CD is inactive.
#define WWSE 		0X08	// Reserved for internal usage only. Shall be set to [0].
#define FMT 		0X04	// Reserved for internal usage only. Shall be set to [0].
#define FMS 		0X02	// [0]: Direct mode. [1]: FIFO mode.
#define ADCM 		0X01	// ADC measurement enable (Auto clear when done).

/*	Register: x01_MODE_CONTROL, R					*/
#define DDPC 		0X80	// DDPC (Direct mode data pin control): In Direct mode, If DDPC=1, MCU delivers / receives raw data of packet via SDIO pin instead of GIO1 or GIO2 pin.
#define ARSSI 		0X40	// ARSSI: Auto RSSI measurement while entering RX mode.
#define AIF 		0X20	// AIF (Auto IF Offset): RF LO frequency will auto offset one IF frequency while entering RX mode.
#define CD 			0X10	// [0]: Input power below threshold. [1]: Input power above threshold.
#define WWSE 		0X08	// Reserved for internal usage only. Shall be set to [0].
#define FMT 		0X04	// Reserved for internal usage only. Shall be set to [0].
#define FMS 		0X02	// [0]: Direct mode. [1]: FIFO mode.
#define ADCM 		0X01	// ADC measurement enable (Auto clear when done).
	
/*	Register: x02_CALC, R/W							*/
#define VCC 		0X04	// VCO Current calibration enable (Auto clear when done).
#define VBC 		0X02	// VCO Bank calibration enable (Auto clear when done).
#define FBC 		0X01	// IF Filter Bank calibration enable (Auto clear when done).

/*	Register: x03_FIFO_I, W							*/
#define FEP7 		0X80	//
#define FEP6 		0X40	//
#define FEP5 		0X20	//
#define FEP4 		0X10	//
#define FEP3 		0X08	//
#define FEP2 		0X04	//
#define FEP1 		0X02	//
#define FEP0 		0X01	// FEP [7:0]: FIFO End Pointer for TX FIFO and Rx FIFO.

/*	Register: x04_FIFO_II, W						*/
#define FPM1 		0X80	//
#define FPM0 		0X40	// FPM [1:0]: FIFO Pointer Margin
#define PSA5 		0X20	//
#define PSA4 		0X10	//
#define PSA3 		0X08	//
#define PSA2 		0X04	//
#define PSA1 		0X02	//
#define PSA0 		0X01	// PSA [5:0]: Used for Segment FIFO.

/*	Register: x05_FIFO_DATA, R/W					*/
#define FIFO7 		0X80	//
#define FIFO6 		0X40	//
#define FIFO5 		0X20	//
#define FIFO4 		0X10	//
#define FIFO3 		0X08	//
#define FIFO2 		0X04	//
#define FIFO1 		0X02	//
#define FIFO0 		0X01	// FIFO [7:0]: FIFO data. TX FIFO (Write only) and RX FIFO (Read only).

/*	Register: x06_ID_DATA, R/W						*/
#define ID7 		0X80	//
#define ID6 		0X40	//
#define ID5 		0X20	//
#define ID4 		0X10	//
#define ID3 		0X08	//
#define ID2 		0X04	//
#define ID1 		0X02	//
#define ID0 		0X01	// When this address is accessed, ID Data is input or output sequential (ID Byte 0,1, 2 and 3) corresponding to Write or Read.

/*	Register: x07_RC_OSC_I, W						*/
#define WWS_SL7 	0X80	//
#define WWS_SL6 	0X40	//
#define WWS_SL5 	0X20	//
#define WWS_SL4 	0X10	//
#define WWS_SL3 	0X08	//
#define WWS_SL2 	0X04	//
#define WWS_SL1 	0X02	//
#define WWS SL0 	0X01	// WWS_SL [9:0]: Reserved for internal usage only.

/*	Register: x07_RC_OSC_I, R						*/
#define RC0C5 		0X20	//
#define RC0C4 		0X10	//
#define RC0C3 		0X08	//
#define RC0C2 		0X04	//
#define RC0C1 		0X02	//
#define RC0C0 		0X01	// RCOC [5:0]: Reserved for internal usage only.

/*	Register: x08_RC_OSC_II, W						*/
#define WWS_SL9 	0X80	//
#define WWS_SL8 	0X40	//
#define WWS_AC5 	0X20	//
#define WWS_AC4 	0X10	//
#define WWS_AC3 	0X08	//
#define WWS_AC2 	0X04	//
#define WWS_AC1 	0X02	//
#define WWS_AC0 	0X01	// WWS_AC [5:0]: Reserved for internal usage only.

/*	Register: x09_RC_OSC_III, W						*/
#define BBCKS1 		0X80	// Clock select for internal digital block Recommend BBCKS = [00]
#define BBCKS0 		0X40	// [00]: FSYCK / 8. [01]: FSYCK / 16. [10]: FSYCK / 32. [11]: FSYCK / 64.
#define RCOSC_E 	0X04	// RC-oscillator enable. Reserved for internal usage only.
#define TSEL 		0X02	// Timer select for TWWS function. Reserved for internal usage only. [0]: Use WWS_AC. [1]: Use WWS_SL.
#define TWWS_E 		0X01	// Enable TWWS function. Reserved for internal usage only.

/*	Register: x0A_CKO_PIN, W						*/
#define ECKOE 		0X80	// External Clock Output Enable for CKOS [3:0]= [0100] ~ [0111].
#define CKOS3 		0X40	//
#define CKOS2 		0X20	//
#define CKOS1 		0X10	//
#define CKOS0 		0X08	// CKOS [3:0]: CKO pin output select.
#define CKOI 		0X04	// CKO pin output signal invert. [0]: Non-inverted output. [1]: Inverted output.
#define CKOE 		0X02	// CKOE: CKO pin Output Enable. [0]: High Z. [1]: Enable.
#define SCKI 		0X01	// SPI clock input invert.[0]: Non-inverted input. [1]: Inverted input.

/*	Register: x0B_GPIO1_PIN_I, W					*/
#define GIO1S3 		0X20	//
#define GIO1S2 		0X10	//
#define GIO1S1 		0X08	//
#define GIOIS0 		0X04	// GIO1S [3:0]: GIO1 pin function select.
#define GIO1I 		0X02	// GIO1I: GIO1 pin output signal invert. [0]: Non-inverted output. [1]: Inverted output.
#define GIO1OE 		0X01	// GIO1OE: GIO1pin output enable. [0]: High Z. [1]: Enable.

/*	Register: x0C_GPIO2_PIN_II, W					*/
#define GIO2S3 		0X20	// 
#define GIO2S2 		0X10	// 
#define GIO2S1 		0X08	// 
#define GIO2S0 		0X04	// GIO2S [3:0]: GIO2 pin function select.
#define GIO2I 		0X02	// GIO2I: GIO2 pin output signal invert. [0]: Non-inverted output. [1]: Inverted output.
#define GIO2OE 		0X01	// GIO2OE: GIO2 pin Output Enable. [0]: High Z. [1]: Enable.

/*	Register: x0D_CLOCK, R/W						*/
#define GRC3 		0X80	// 
#define GRC2 		0X40	// 
#define GRC1 		0X20	// 
#define GRC0 		0X10	// GRC [3:0]: Clock generation reference counter.
#define CSC1 		0X08	// 
#define CSC0 		0X04	// CSC [1:0]: system clock FSYCK divider select.
#define CGS 		0X02	// Clock generator enable. Recommend CGS = [0].
#define XS 			0X01	// Crystal oscillator select. Recommend XS = [1]. [0]: External clock. [1]: Crystal.

/*	Register: x0E_DATA_RATE, R/W					*/
#define SDR7 		0X80	// 
#define SDR6 		0X40	// 
#define SDR5 		0X20	// 
#define SDR4 		0X10	// 
#define SDR3 		0X08	// 
#define SDR2 		0X04	// 
#define SDR1 		0X02	// 
#define SDR0 		0X01	// SDR [7:0]: Data rate division selection.

/*	Register: x0F_PLL_I/x0F_CHANNEL, R/W			*/
#define CHN7 		0X80	// 
#define CHN6 		0X40	// 
#define CHN5 		0X20	// 
#define CHN4 		0X10	// 
#define CHN3 		0X08	// 
#define CHN2 		0X04	// 
#define CHN1 		0X02	// 
#define CHN0 		0X01	// CHN [7:0]: LO channel number select.

/*	Register: x10_PLL_II, R/W						*/
#define DBL 		0X80	// Crystal frequency doubler selection. Recommend DBL = [1]. [0]: Disable. FXREF = FXTAL. [1]: Enable. FXREF =2 * FXTAL.
#define RRC1 		0X40	// 
#define RRC0 		0X20	// RRC [1:0]: RF PLL reference counter setting.
#define CHR3 		0X10	// 
#define CHR2 		0X08	// 
#define CHR1 		0X04	// 
#define CHR0 		0X02	// CHR [3:0]: PLL channel step setting.
#define IP8 		0X01	// 

/*	Register: x11_PLL_III, R/W						*/
#define IP7 		0X80	// 
#define IP6 		0X40	// 
#define IP5 		0X20	// 
#define IP4 		0X10	// 
#define IP3 		0X08	// 
#define IP2 		0X04	// 
#define IP1 		0X02	// 
#define IP0 		0X01	// IP [8:0]: LO frequency integer part value. Recommend BIP[8:0] = [0x04B].


/*	Register: x12_PLL_IV, W							*/
#define FP15 		0X80	// 
#define FP14 		0X40	// 
#define FP13 		0X20	// 
#define FP12 		0X10	// 
#define FP11 		0X08	// 
#define FP10 		0X04	// 
#define FP9 		0X02	// 
#define FP8 		0X01	// 

/*	Register: x12_PLL_IV, R							*/
#define AC14 		0X40	// 
#define AC13 		0X20	// 
#define AC12 		0X10	// 
#define AC11 		0X08	// 
#define AC10 		0X04	// 
#define AC9 		0X02	// 
#define AC8 		0X01	// 

/*	Register: x13_PLL_V, W							*/
#define FP7 		0X80	// 
#define FP6 		0X40	// 
#define FP5 		0X20	// 
#define FP4 		0X10	// 
#define FP3 		0X08	// 
#define FP2 		0X04	// 
#define FP1 		0X02	// 
#define FP0 		0X01	// BFP [15:0]: LO base frequency fractional part setting. Recommend BFP[15:0] = [0x0002]

/*	Register: x13_PLL_V, R							*/
#define AC7 		0X80	// 
#define AC6 		0X40	// 
#define AC5 		0X20	// 
#define AC4 		0X10	// 
#define AC3 		0X08	// 
#define AC2 		0X04	// 
#define AC1 		0X02	// FP [15:0] (Read): LO frequency fractional part setting.
#define AC0 		0X01	// AC [14:0] (Read): Auto Frequency compensation value (if FC (18h) =1).

/*	Register: x14_TX_I, W							*/
#define TXSM1 		0X80	// TXSM [1:0]: Moving average for non-filter select. Recommend TXSM= [00]
#define TXSM0 		0X40	// [00]: not average. [01]: 2 bit average. [10]: 4 bit average. [11]: 8 bit average
#define TXDI 		0X20	// TX data invert. Recommend TXDI = [0]. [0]: Non-invert. [1]: Invert.
#define TME 		0X10	// TX modulation enable.
#define FS 			0X08	// Filter select. Recommend FS = [0]. Gaussian filter (BT=0.7). [0]: disable. [1]: enable.
#define FDP2 		0X04	// 
#define FDP1 		0X02	// 
#define FDP0 		0X01	// FDP [2:0]: Frequency deviation power setting. Refer to control register (15h). Recommend FDP = [110].

/*	Register: x15_TX_II, W							*/
#define PDV1 		0X40	// 
#define PDV0 		0X20	// PDV [1:0]: Reserved for internal usage only. Shall be set to [01].
#define FD4 		0X10	// 
#define FD3 		0X08	// 
#define FD2 		0X04	// 
#define FD1 		0X02	// 
#define FD0 		0X01	// FD [4:0]: Frequency deviation setting.

/*	Register: x16_DELAY_I, W						*/
#define DPR2 		0X80	// 
#define DPR1 		0X40	// 
#define DPR0 		0X20	// DPR [2:0]: Delay scale. Recommend DPR= [000].
#define TDL1 		0X10	// 
#define TDL0 		0X08	// TDL [1:0]: Delay for TX settling from WPLL to TX. Recommend TDL= [10].
#define PDL2 		0X04	// 
#define PDL1 		0X02	// 
#define PDL0 		0X01	// PDL [2:0]: Delay for TX settling from PLL to WPLL. Recommend PDL= [010].

/*	Register: x17_DELAY_II, W						*/
#define WSEL2 		0X80	// 
#define WSEL1 		0X40	// 
#define WSEL0 		0X20	// WSEL [2:0]: XTAL settling delay setting (200us ~ 2.5ms). Recommend WSEL = [010].
#define AGC_D1 		0X10	// 
#define AGC_D0 		0X08	// AGC_D [1:0]: AGC delay settling Recommend AGC_D[1:0] = [00].
#define RS_DLY2 	0X04	// 
#define RS_DLY1 	0X02	// 
#define RS_DLY0 	0X01	// RS_DLY [2:0]: RSSI measurement delay (10us ~ 80us). Recommend RS_DLY = [000].

/*	Register: x18_RX, W								*/
#define RXSM1 		0X40	// Reserved for internal usage only. Shall be set to [1].
#define RXSM0 		0X20	// Reserved for internal usage only. Shall be set to [1].
#define FC 			0X10	// Frequency compensation select. [0]: Disalbe . [1]: Enable.
#define RXDI 		0X08	// RXDI: RX data output invert. Recommend RXDI = [0]. [0]: Non-inverted output. [1]: Inverted output.
#define DMG 		0X04	// Reserved for internal usage only. Shall be set to [0].
#define BWS 		0X02	// BPF bandwidth select. Recommend BWS = [1].
#define ULS 		0X01	// RX Up/Low side band select. [0]: Up side band, [1]: Low side band.

/*	Register: x19_RX_GAIN_I, R/W					*/
#define MVGS 		0X80	// Manual VGA calibrate. Recommend MVGS = [1]. [0]: Auto. [1]: Manual
#define IGC 		0X20	// Reserved for internal usage only. Shall be set to [0].
#define MGC1 		0X10	// Mixer gain. Recommend MGS = [00].
#define MGC0 		0X08	// [00]: 24dB. [01]: 18dB. [10]: 12dB. [11]: 6dB.
#define LGC2 		0X04	// 
#define LGC1 		0X02	// LNA gain. Recommend LGS = [000].
#define LGC0 		0X01	// [000]: 24dB. [001]: 18dB. [010]: 12dB. [011]: 6dB. [1XX]: 0dB.

/*	Register: x1A_RX_GAIN_II, W						*/
#define RH7 		0X80	// 
#define RH6 		0X40	// 
#define RH5 		0X20	// 
#define RH4 		0X10	// 
#define RH3 		0X08	// 
#define RH2 		0X04	// 
#define RH1 		0X02	// 
#define RH0 		0X01	// RH [7:0]: Reserved for internal usage only.

/*	Register: x1B_RX_GAIN_III, W					*/
#define RL7 		0X80	// 
#define RL6 		0X40	// 
#define RL5 		0X20	// 
#define RL4 		0X10	// 
#define RL3 		0X08	// 
#define RL2 		0X04	// 
#define RL1 		0X02	// 
#define RL0 		0X01	// RL [7:0]: Reserved for internal usage only.

/*	Register: x1C_RX_GAIN_IV, W						*/
#define ENGC 		0X80	// Reserved for internal usage only. Shall be set to [0].
#define MHC 		0X08	// Reserved for internal usage only. Shall be set to [1].
#define LHC1 		0X04	// 
#define LHC0 		0X02	// LHC [1:0]: Reserved for internal usage only. Shall be set to [01].
#define VGCE 		0X01	// Reserved for internal usage only. Shall be set to [0].

/*	Register: x1D_RSSI_THRESHOLD, W					*/
#define RTH7 		0X80	// 
#define RTH6 		0X40	// 
#define RTH5 		0X20	// 
#define RTH4 		0X10	// 
#define RTH3 		0X08	// 
#define RTH2 		0X04	// 
#define RTH1 		0X02	// 
#define RTH0 		0X01	// RTH [7:0]: Carrier detect threshold.

/*	Register: x1D_RSSI_THRESHOLD, R					*/
#define ADC7 		0X80	// 
#define ADC6 		0X40	// 
#define ADC5 		0X20	// 
#define ADC4 		0X10	// 
#define ADC3 		0X08	// 
#define ADC2 		0X04	// 
#define ADC1 		0X02	// ADC [7:0]: ADC output value for RSSI measurement.
#define ADC0 		0X01	// ADC input voltage= 1.2 * ADC [7:0] / 256 V.

/*	Register: x1E_ADC, W							*/
#define RSM1 		0X80	// RSM [1:0]: RSSI margin = RTH – RTL. Recommend RSM = [11].
#define RSM0 		0X40	// [00]: 5. [01]: 10. [10]: 15. [11]: 20.
#define ERSS 		0X20	// End for RSSI measurement. [0]: RSSI measurement continues until leave off RX mode. [1]: RSSI measurement will end when carrier detected and ID code word received.
#define FSARS 		0X10	// ADC clock select. Recommend FSARS = [0]. [0]: 4MHz. [1]: 8MHz.
#define XADS 		0X04	// ADC input signal select. [0]: Convert RSS signal. [1]: Reserved for internal usage.
#define RSS 		0X02	// RSSI measurement select. [0]: Reserved for internal usage. [1]: RSSI or carrier-detect measurement.
#define CDM 		0X01	// RSSI measurement mode. [0]: Single mode. [1]: Continuous mode.

/*	Register: x1F_CODE_I, W							*/
#define MCS 		0X40	// ???
#define WHTS 		0X20	// Data whitening (Data Encryption) select.[0]: Disable. [1]: Enable.
#define FECS 		0X10	// FEC select. [0]: Disable. [1]: Enable.
#define CRCS 		0X08	// CRC select. [0]: Disable. [1]: Enable.
#define IDL 		0X04	// ID code length select. Recommend IDL= [1]. [0]: 2 bytes. [1]: 4 bytes.
#define PML1 		0X02	// PML [1:0]: Preamble length select. Recommend PML= [11].
#define PML0 		0X01	// [00]: 1 byte. [01]: 2 bytes. [10]: 3 bytes. [11]: 4 bytes.

/*	Register: x20_CODE_II, W						*/
#define DCL2 		0X40	// 
#define DCL1 		0X20	// 
#define DCL0 		0X10	// DCL [2:0]: Demodulator DC estimation average mode. Recommend DCL[2:0] = [001]
#define ETH1 		0X08	// ETH [1:0]: ID code error tolerance. Recommend ETH = [01]
#define ETH0 		0X04	// [00]: 0 bit, [01]: 1 bit. [10]: 2 bits. [11]: 3 bits.
#define PMD1 		0X02	// PMD [1:0]: Preamble pattern detection length.
#define PMD0 		0X01	// [00]: 0bit. [01]: 4bits. [10]: 8bits. [11]: 16bits.

/*	Register: x21_CODE_III, R/W						*/
#define WS6 		0X40	// 
#define WS5 		0X20	// 
#define WS4 		0X10	// 
#define WS3 		0X08	// 
#define WS2 		0X04	// 
#define WS1 		0X02	// 
#define WS0			0X01	// WS [6:0]: Data Whitening seed setting (data encryption key).

/*	Register: x22_IF_CALIBRATION_I, W				*/
#define MFBS 		0X10	// IF filter calibration value select. Recommend MFBS = [0]. [0]: Auto calibration value. [1]: Manual calibration value.
#define MFB3 		0X08	// 
#define MFB2 		0X04	// 
#define MFB1 		0X02	// 
#define MFB0 		0X01	// MFB [3:0]: IF filter manual calibration value.

/*	Register: x22_IF_CALIBRATION_I, R				*/
#define FBCF 		0X10	// IF filter auto calibration flag. [0]: Pass. [1]: Fail.
#define FB3 		0X08	// 
#define FB2 		0X04	// 
#define FB1 		0X02	// 
#define FB0 		0X01	// FB [3:0]: IF filter calibration value.

/*	Register: x23_IF_CALIBRATION_II, R				*/
#define FCD4 		0X10	// 
#define FCD3 		0X08	// 
#define FCD2 		0X04	// 
#define FCD1 		0X02	// 
#define FCD0 		0X01	// FCD [4:0]: IF filter calibration deviation from goal (Read only).

/*	Register: x24_VCO_CURRENT_CALIBRATION, W		*/
#define VCCS 		0X20	// Reserved for internal usage only. Shall be set [0].
#define MVCS 		0X10	// VCO current calibration value select. Recommend MVCS = [1]. [0]: Auto calibration value. [1]: Manual calibration value.
#define VC0C3 		0X08	// 
#define VC0C2 		0X04	// 
#define VC0C1 		0X02	// 
#define VC0C0 		0X01	// VCOC [3:0]: VCO current manual calibration value. Recommend VCOC = [011].

/*	Register: x24_VCO_CURRENT_CALIBRATION, R		*/
#define FVCC 		0X10	// VCO current auto calibration flag. [0]: Pass. [1]: Fail.
#define VCB3 		0X08	// 
#define VCB2 		0X04	// 
#define VCB1 		0X02	// 
#define VCB0 		0X01	// VCB [3:0]: VCO current calibration value.

/*	Register: x25_VCO_SINGLE_BAND_CALIBRATION_I, W	*/
#define MVBS 		0X08	// VCO bank calibration value select. Recommend MVBS = [0]. [0]: Auto calibration value. [1]: Manual calibration value.
#define MVB2 		0X04	// 
#define MVB1 		0X02	// 
#define MVB0 		0X01	// MVB [2:0]: VCO band manual calibration value.

/*	Register: x25_VCO_SINGLE_BAND_CALIBRATION_I, R	*/
#define DVT1 		0X20	// DVT [1:0]: digital VCO tuning voltage output.
#define DVT0 		0X10	// [00]: VT<VTL<VTH. [01]: VTL<VT<VTH. [10]: No used. [11]: VTL<VTH<VT.
#define VBCF 		0X08	// VCO band auto calibration flag. [0]: Pass. [1]: Fail.
#define VB2 		0X04	// 
#define VB1 		0X02	// 
#define VB0 		0X01	// VB [2:0]: VCO bank calibration value.

/*	Register: x26_VCO_SINGLE_BAND_CALIBRATION_II, W	*/
#define VTH2 		0X20	// VTH [2:0]: VCO tuning voltage upper threshold level setting. Recommend VTH = [111].
#define VTH1 		0X10	// [000]: VDD_A – 0.6V. [001]: VDD_A – 0.7V. [010]: VDD_A – 0.8V. [011]: VDD_A – 0.9V
#define VTH0 		0X08	// [100]: VDD_A – 1.0V. [101]: VDD_A – 1.1V. [110]: VDD_A – 1.2V. [111]: VDD_A – 1.3V
#define VTL2 		0X04	// VTL [2:0]: VCO tuning voltage lower threshold level setting. Recommend VTL = [011].
#define VTL1 		0X02	// [000]: 0.1V. [001]: 0.2V. [010]: 0.3V. [011]: 0.4V.
#define VTL0 		0X01	// [100]: 0.5V. [101]: 0.6V. [110]: 0.7V. [111]: 0.8V

/*	Register: x27_BATTERY_DETECT, W					*/
#define RGS 		0X80	// VDD_D voltage setting in Sleep mode. [0]: 3/5 * REGI. [1]: 3/4 * REGI.
#define RGV1 		0X40	// RGV [1:0]: VDD_D and VDD_A voltage setting in non-Sleep mode. Recommend RGV = [00].
#define RGV0 		0X20	// [00]: 2.1V. [01]: 2.0V. [10]: 1.9V. [11]: 1.8V.
#define BVT2 		0X08	// BVT [2:0]: Battery voltage detect threshold.
#define BVT1 		0X04	// [000]: 2.0V. [001]: 2.1V. [010]: 2.2V. [011]: 2.3V.
#define BVT0 		0X02	// [100]: 2.4V. [101]: 2.5V. [110]: 2.6V. [111]: 2.7V.
#define BDS 		0X01	// Battery detect select. [0]: Disable. [1]: Enable. It will be clear after battery detection done.

/*	Register: x27_BATTERY_DETECT, R					*/
#define BDF 		0X10	// Battery detection flag. [0]: Battery voltage less than threshold. [1]: Battery voltage greater than threshold.

/*	Register: x28_TX_TEST, W						*/
#define TXCS 		0X20	// TX Current Setting. [0]
#define PAC1 		0X10	// 
#define PAC0 		0X08	// PAC [1:0]: PA Current Setting. [10]
#define TBG2 		0X04	// 
#define TBG1 		0X02	// 
#define TBG0 		0X01	// TBG [2:0]: TX Buffer Setting. [111]

/*	Register: x29_RX_DEM_TEST_I, W					*/
#define DMT 		0X80	// Reserved for internal usage only. Shall be set to [0].
#define DCM1 		0X40	// 
#define DCM0 		0X20	// DCM [1:0]: Demodulator DC estimation mode.
#define MLP1 		0X10	// 
#define MLP0 		0X08	// MLP [1:0]: Reserved for internal usage only. Shall be set to [00].
#define SLF2 		0X04	// 
#define SLF1 		0X02	// 
#define SLF0 		0X01	// SLF [2:0]: Reserved for internal usage only. Shall be set to [111].

/*	Register: x2A_RX_DEM_TEST_II, W					*/
#define DCV7		0X80	// 
#define DCV6 		0X40	// 
#define DCV5 		0X20	// 
#define DCV4 		0X10	// 
#define DCV3 		0X08	// 
#define DCV2 		0X04	// 
#define DCV1 		0X02	// 
#define DCV0 		0X01	// DCV [7:0]: Demodulator fix mode DC value. Recommend DCV = [0x80].

/*	Register: x2B_CPC, W							*/
#define CPC1 		0X02	// CPC [1:0]: Charge pump current setting. Recommend CPC = [11].
#define CPC0 		0X01	// [00]: 0.5mA. [01]: 1.0mA. [10]: 1.5mA. [11]: 2.0mA

/*	Register: x2C_CRYSTAL_TEST, W					*/
#define DBD 		0X08	// Reserved for internal usage only. Shall be set to [0].
#define XCC 		0X04	// Reserved for internal usage only. Shall be set to [0].
#define XCP1 		0X02	// 
#define XCP0 		0X01	// XCP [1:0]: Reserved for internal usage only. Shall be set to [01].

/*	Register: x2D_PLL_TEST, W						*/
#define PMPE 		0X40	// Reserved for internal usage only. Shall be set to [1].
#define PRRC1 		0X20	// 
#define PRRC0 		0X10	// PRRC [1:0]: Reserved for internal usage only. Shall be set to [00].
#define PRIC1 		0X08	// 
#define PRIC0 		0X04	// PRIC [1:0]: Reserved for internal usage only. Shall be set to [01].
#define SDPW 		0X02	// Reserved for internal usage only. Shall be set to [0].
#define NSDO 		0X01	// Reserved for internal usage only. Shall be set to [1].

/*	Register: x2E_VCO_TEST_I, W						*/
#define TLB1 		0X10	// 
#define TLB0 		0X08	// TLB [1:0]: Reserved for internal usage only. Shall be set to [11].
#define RLB1 		0X04	// 
#define RLB0 		0X02	// RLB [1:0]: Reserved for internal usage only. Shall be set to [00].
#define VCBS 		0X01	// Reserved for internal usage only. Shall be set to [0].

/*	Register: x2F_VCO_TEST_II, W					*/
#define RFT3 		0X08	// 
#define RFT2 		0X04	// 
#define RFT1 		0X02	// 
#define RFT0 		0X01	// RFT [3:0]: RF analog pin configuration for testing. Recommend RFT= [0000].

/*	Register: x30_IFAT, W							*/
#define IGFI2 		0X80	// 
#define IGFI1 		0X40	// 
#define IGFI0 		0X20	// IGFI [2:0]: Reserved for internal usage only. Shall be set to [000].
#define IGFQ2 		0X10	// 
#define IGFQ1 		0X08	// 
#define IGFQ0 		0X04	// IGFQ [2:0]: Reserved for internal usage only. Shall be set to [000].
#define IFBC 		0X02	// Reserved for internal usage only. Shall be set to [0].
#define LIMC 		0X01	// Reserved for internal usage only. Shall be set to [1].

/*	Register: x31_RSCALE, R/W						*/
#define RSC7 		0X80	// 
#define RSC6 		0X40	// 
#define RSC5 		0X20	// 
#define RSC4 		0X10	// 
#define RSC3 		0X08	// 
#define RSC2 		0X04	// 
#define RSC1 		0X02	// 
#define RSC0 		0X01	// RSC [7:0]: Reserved for internal usage only. Shall be set to = [0x0F].

/*	Register: x32_FILTER_TEST, W					*/
#define FT7 		0X80	// 
#define FT6 		0X40	// 
#define FT5 		0X20	// 
#define FT4 		0X10	// 
#define FT3 		0X08	// 
#define FT2 		0X04	// 
#define FT1 		0X02	// 
#define FT0 		0X01	// FT [7:0]: Reserved for internal usage only. Shall be set to = [0x00].

static const uint8_t AFHDS2A_regs[] =
{
	0xFF, ARSSI | AIF | FMS, 0x00, 0x25,
	0x00, 0xFF, 0xFF, 0x00,
	0x00, 0x00, 0x00, GIO10E,
	GIO2S2 | GIO2S1 | GIO2OE, CSC0 | XS, 0x00, 0x50, 
	0x9e, 0x4b, 0x00, 0x02,
	0x16, 0x2b, 0x12, 0x4f,
	0x62, 0x80, 0xFF, 0xFF,
	0x2a, 0x32, 0xc3, 0x1f,
	0x1e, 0xFF, 0x00, 0xFF,
	0x00, 0x00, 0x3b, 0x00,
	0x17, 0x47, 0x80, 0x03,
	0x01, 0x45, 0x18, 0x00,
	0x01, 0x0f
};
	
#endif // _A7105_RESG_H_
