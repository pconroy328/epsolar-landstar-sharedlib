/*
 */

/* 
 * File:   ls10x4b.h
 * Author: pconroy
 *
 * Created on September 24, 2018, 3:09 PM
 */

#ifndef LS10X4B_H
#define LS10X4B_H

#ifdef __cplusplus
extern "C" {
#endif

#include <modbus/modbus.h>

//
// Arbitrary. Not sure its used or required
#define LANDSTAR_1024B_ID       0x01

    

//
//  Note 1: I'm using the terms "RatedData", "RealTime Data" as they are used in the 
//  documentation I have from EPSolar.
//
//  Note 2: I'm using an EPSolar document noted as "B_Series MODBUS Specification EPEVER Corporation V2.3 June 12, 2015"
//  Other, older versions of this document are out on the net
//
typedef struct RatedData {
    float   pvArrayRatedVoltage;
    float   pvArrayRatedCurrent;
    float   pvArrayRatedPower;
    float   batteryRatedVoltage;
    float   batteryRatedCurrent;
    float   batteryRatedPower;
    char    *chargingMode;
    float   ratedCurrentOfLoad;
} RatedData_t;


typedef struct  RealTimeData {
    float   pvArrayVoltage;
    float   pvArrayCurrent;
    float   pvArrayPower;
    float   batteryPower;
    float   loadVoltage;
    float   loadCurrent; 
    float   loadPower;
    float   batteryTemp;
    float   caseTemp;
    int     batterySOC;
    float   remoteBatteryTemperature;
    float   batteryRealRatedPower;
} RealTimeData_t;

typedef  struct  RealTimeStatus {
    int     batteryStatusValue;
    int     chargingStatusValue;
    int     dischargingStatusValue;

    char    *batteryStatusVoltage;
    char    *batteryStatusTemperature;
    char    *batteryInnerResistance;
    char    *batteryCorrectIdentification;
    
    char    *chargingStatus;
    char    *chargingInputVoltageStatus;
    int     chargingMOSFETShort;
    int     someMOSFETShort;
    int     antiReverseMOSFETShort;
    int     inputIsOverCurrent;
    int     loadIsOverCurrent;
    int     loadIsShort;
    int     loadMOSFETIsShort;
    int     pvInputIsShort;
    int     chargingStatusNormal;
    int     chargingStatusRunning;
    
    int     dischargingStatusNormal;
    char    *dischargingInputVoltageStatus;
    char    *dischargingOutputPower;
    int     dischargingShortCircuit;
    int     unableToDischarge;
    int     unableToStopDischarging;
    int     outputVoltageAbnormal;
    int     inputOverpressure;
    int     highVoltageSideShort;
    int     boostOverpressure;
    int     outputOverpressure;
    int     dischargingStatusRunning;
} RealTimeStatus_t;

typedef struct  Settings {
    char    *batteryType;
    int     batteryCapacity;
    float   tempCompensationCoeff;
    float   highVoltageDisconnect;
    float   chargingLimitVoltage;
    float   overVoltageReconnect;
    float   equalizationVoltage;
    float   boostVoltage;
    float   floatVoltage;
    float   boostReconnectVoltage;
    float   lowVoltageReconnect;
    float   underVoltageRecover;
    float   underVoltageWarning;
    float   lowVoltageDisconnect;
    float   dischargingLimitVoltage;
    int     equalizationChargingCycle;
    char    *realtimeClock;
    float   batteryTempWarningUpperLimit;
    float   batteryTempWarningLowerLimit;
    
    float   controllerInnerTempUpperLimit;
    float   controllerInnerTempUpperLimitRecover;
    float   powerComponentTempUpperLimit;
    float   powerComponentTempUpperLimitRecover;
    float   lineImpedence;

    
    float   daytimeThresholdVoltage;


    int     lightSignalStartupTime;
    float   lighttimeThresholdVoltage;
    int     lightSignalCloseDelayTime;
    int     localControllingModes;
    int     workingTimeLength1;
    int     workingTimeLength2;
    int     turnOnTiming1_seconds;
    int     turnOnTiming1_minutes;
    int     turnOnTiming1_hours;

    int     turnOffTiming1_seconds;
    int     turnOffTiming1_minutes;
    int     turnOffTiming1_hours;
    
    int     turnOnTiming2_seconds;
    int     turnOnTiming2_minutes;
    int     turnOnTiming2_hours;

    int     turnOffTiming2_seconds;
    int     turnOffTiming2_minutes;
    int     turnOffTiming2_hours;

    int     lengthOfNight;
    int     batteryRatedVoltageCode;
    int     loadTimingControlSelection;
    int     defaultLoadOnOffManualMode;
    float   equalizeDuration;
    float   boostDuration;
    int     dischargingPercentage;
    int     chargingPercentage;
    int     batteryManagementMode;

    int     backlightTime;
    int     deviceConfigureMainPower;
} Settings_t;

typedef struct  StatisticalParameters {
    float   maximumInputVoltageToday;
    float   minimumInputVoltageToday;
    float   maximumBatteryVoltageToday;
    float   minimumBatteryVoltageToday;
    float   consumedEnergyToday;
    float   consumedEnergyMonth;
    float   consumedEnergyYear;
    float   totalConsumedEnergy;
    float   generatedEnergyToday;
    float   generatedEnergyMonth;
    float   generatedEnergyYear;
    float   totalGeneratedEnergy;
    float   batteryCurrent;
    float   batteryVoltage;
} StatisticalParameters_t;



extern  modbus_t *openController( const char *devicePort, const int slaveID ); 
extern  void    closeController( modbus_t * );

extern  void    restoreSystemDefaults( modbus_t *ctx );

extern  void    clearEnergyGeneratingStatistics( modbus_t *ctx );
extern  void    forceLoadOnOff( modbus_t *ctx, const int value );

extern  int     getChargingDeviceStatus( modbus_t *ctx );
extern  int     getDefaultLoadControlMode( modbus_t *ctx );
extern  int     getEnableLoadTestMode( modbus_t *ctx );
extern  int     getManualLoadControlMode( modbus_t *ctx );
extern  int     getOutputControlMode( modbus_t *ctx );
extern  int     getOverTemperatureInsideDevice( modbus_t *ctx );

extern  void    getRealtimeClock( modbus_t *ctx, int *seconds, int *minutes, int *hour, int *day, int *month, int *year );
extern  char    *getRealtimeClockStr( modbus_t *ctx, char *buffer, const int buffSize );
extern  void    setRealtimeClockToNow( modbus_t *ctx );
extern  void    setRealtimeClock( modbus_t *ctx, const int seconds, const int minutes, const int hour, const int day, const int month, const int year );


extern  void    getRatedData( modbus_t *ctx, RatedData_t *data );
extern  void    getRealTimeData( modbus_t *ctx, RealTimeData_t *data );
extern  void    getRealTimeStatus( modbus_t *ctx, RealTimeStatus_t *data );
extern  void    getSettings( modbus_t *ctx, Settings_t *data );
extern  void    getStatisticalParameters( modbus_t *ctx, StatisticalParameters_t *data );

extern  int     isNightTime( modbus_t *ctx );

extern  void    setBacklightTime( modbus_t *ctx, const int seconds );

extern  void    setBatteryCapacity( modbus_t *ctx, const int batteryCapacityAH );
extern  void    setBatteryRatedVoltageCode( modbus_t *ctx, const int value );
extern  void    setBatteryTemperatureWarningLowerLimit( modbus_t *ctx, const float value );
extern  void    setBatteryTemperatureWarningUpperLimit( modbus_t *ctx, const float value );
extern  void    setBatteryType( modbus_t *ctx, const int batteryTypeCode );

extern  void    setBoostDuration( modbus_t *ctx, const int value );
extern  void    setBoostReconnectVoltage( modbus_t *ctx, const float value );
extern  void    setBoostVoltage( modbus_t *ctx, const float value );

extern  void    setChargingDeviceOff( modbus_t *ctx );
extern  void    setChargingDeviceOn( modbus_t *ctx );

extern  void    setChargingDeviceStatus( modbus_t *ctx, const int value );
extern  void    setChargingLimitVoltage( modbus_t *ctx, const float value );
extern  void    setChargingPercentage( modbus_t *ctx, const float value );

extern  void    setControllerInnerTemperatureUpperLimitRecover( modbus_t *ctx, const float value );
extern  void    setControllerInnerTemperatureUpperLimit( modbus_t *ctx, const float value );

extern  void    setDayTimeThresholdVoltage( modbus_t *ctx, const float value );

extern  void    setDefaultLoadControlMode( modbus_t *ctx, const int value );
extern  void    setDefaultLoadOnOffInManualMode( modbus_t *ctx, const int value );

extern  void    setDeviceConfigureOfMainPowerSupply( modbus_t *ctx, const int value );

extern  void    setDischargingLimitVoltage( modbus_t *ctx, const float value );
extern  void    setDischargingPercentage( modbus_t *ctx, const float value );

extern  void    setEnableLoadTestMode( modbus_t *ctx, const int value );

extern  void    setEqualizationVoltage( modbus_t *ctx, const float value );
extern  void    setEqualizeDuration( modbus_t *ctx, const int value );

extern  void    setFloatVoltage( modbus_t *ctx, const float value );
extern  void    setHighVoltageDisconnect( modbus_t *ctx, const float value );
extern  void    setLengthOfNight( modbus_t *ctx, const int hour, const int minute );
extern  void    setLightSignalCloseDelayTime( modbus_t *ctx, const int value );
extern  void    setLightSignalStartupDelayTime( modbus_t *ctx, const int value );
extern  void    setLoadControllingModes( modbus_t *ctx, const int value );
extern  void    setLoadDeviceOff( modbus_t *ctx );
extern  void    setLoadDeviceOn( modbus_t *ctx );
extern  void    setLowVoltageDisconnect( modbus_t *ctx, const float value );
extern  void    setLowVoltageReconnect( modbus_t *ctx, const float value );
extern  void    setManagementModesOfBatteryChargingAndDischarging( modbus_t *ctx, const int value );
extern  void    setManualLoadControlMode( modbus_t *ctx, const int value );
extern  void    setNightTimeThresholdVoltage( modbus_t *ctx, const float value );
extern  void    setOutputControlMode( modbus_t *ctx, const int value );
extern  void    setOverVoltageReconnect( modbus_t *ctx, const float value );
extern  void    setTempertureCompensationCoefficient( modbus_t *ctx, const int value );
extern  void    setTurnOffTiming1( modbus_t *ctx, const int hour, const int minute, const int second );
extern  void    setTurnOffTiming2( modbus_t *ctx, const int hour, const int minute, const int second );
extern  void    setTurnOnTiming1( modbus_t *ctx, const int hour, const int minute, const int second );
extern  void    setTurnOnTiming2( modbus_t *ctx, const int hour, const int minute, const int second );
extern  void    setUnderVoltageRecover( modbus_t *ctx, const float value );
extern  void    setUnderVoltageWarning( modbus_t *ctx, const float value );
extern  void    setWorkingTimeLength1( modbus_t *ctx, const int hour, const int minute );
extern  void    setWorkingTimeLength2( modbus_t *ctx, const int hour, const int minute );



#ifdef __cplusplus
}
#endif

#endif /* LS10X4B_H */

