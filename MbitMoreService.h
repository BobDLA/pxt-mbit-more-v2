#include "pxt.h"

#if MICROBIT_CODAL

#ifndef MBIT_MORE_SERVICE_H
#define MBIT_MORE_SERVICE_H

#include "MicroBitConfig.h"

#if CONFIG_ENABLED(DEVICE_BLE)

#include "MicroBit.h"
#include "MicroBitBLEManager.h"
#include "MicroBitBLEService.h"

#include "MbitMoreCommon.h"
#include "MbitMoreDevice.h"

// // Forward declaration
class MbitMoreDevice;

/**
 * Class definition for the Scratch basic Service.
 * Provides a BLE service for default extension of micro:bit in Scratch3.
 */
class MbitMoreService : public MicroBitBLEService, MicroBitComponent {
public:
  /**
   * Constructor.
   * Create a representation of default extension for Scratch3.
   */
  MbitMoreService();

  /**
   * Invoked when BLE connects.
   */
  void onConnect(const microbit_ble_evt_t *p_ble_evt);

  /**
   * Invoked when BLE disconnects.
   */
  void onDisconnect(const microbit_ble_evt_t *p_ble_evt);

  /**
   * Callback. Invoked when any of our attributes are written via BLE.
   */
  void onDataWritten(const microbit_ble_evt_write_t *params);

  /**
   * Callback. Invoked when any of our attributes are read via BLE.
   * Set  params->data and params->length to update the value
   */
  void onDataRead(microbit_onDataRead_t *params);

  /**
   * Periodic callback from MicroBit idle thread.
   */
  virtual void idleCallback();

  /**
   * @brief Notify data of the basic extension.
   *
   * @param data Data to notify.
   * @param length Length of the data.
   */
  void notifyBasicData(uint8_t *data, uint16_t length);

  /**
   * @brief Notify action event.
   *
   * @param data Data to notify.
   * @param length Lenght of the data.
   */
  void notifyActionEvent(uint8_t *data, uint16_t length);

  /**
   * @brief Notify IO event.
   *
   * @param data Data to notify.
   * @param length Lenght of the data.
   */
  void notifyIOEvent(uint8_t *data, uint16_t length);

  void notifySharedData();

  void notify();

  void update();

  /**
   * Set value to Slots.
   */
  void setSharedData(int index, int value);

  /**
   * Get value to Slots.
   */
  int getSharedData(int index);

private:
  /**
   * @brief micro:bit runtime object.
   *
   */
  MicroBit &uBit;

  /**
   * @brief Microbit More object.
   *
   */
  MbitMoreDevice *mbitMore;

  // Index for each charactersitic in arrays of handles and UUIDs
  typedef enum mbitmore_cIdx
  {
    mbitmore_cIdx_COMMAND,
    mbitmore_cIdx_SENSORS,
    mbitmore_cIdx_DIRECTION,
    mbitmore_cIdx_PIN_EVENT,
    mbitmore_cIdx_ACTION_EVENT,
    mbitmore_cIdx_ANALOG_IN_P0,
    mbitmore_cIdx_ANALOG_IN_P1,
    mbitmore_cIdx_ANALOG_IN_P2,
    mbitmore_cIdx_SHARED_DATA,
    mbitmore_cIdx_COUNT
  } mbitmore_cIdx;

  // UUIDs for our service and characteristics
  static const uint8_t baseUUID[16];
  static const uint16_t serviceUUID;
  static const uint16_t charUUID[mbitmore_cIdx_COUNT];

  // Data for each characteristic when they are held by Soft Device.
  MicroBitBLEChar chars[mbitmore_cIdx_COUNT];

  // Buffer of characteristic for receiving commands.
  uint8_t commandChBuffer[MM_CH_BUFFER_SIZE_DEFAULT] = {0};

  // Buffer of characteristic for sending data of sensors.
  uint8_t sensorsChBuffer[7] = {0};

  // Buffer of characteristic for sending data about direction.
  uint8_t directionChBuffer[18] = {0};

  // Buffer of characteristic for sending pin events.
  uint8_t pinEventChBuffer[MM_CH_BUFFER_SIZE_DEFAULT] = {0};

  // Buffer of characteristic for sending action events.
  uint8_t actionEventChBuffer[MM_CH_BUFFER_SIZE_DEFAULT] = {0};

  // Buffer of characteristic for sending analog input values of P0.
  uint8_t analogInP0ChBuffer[2] = {0};

  // Buffer of characteristic for sending analog input values of P1.
  uint8_t analogInP1ChBuffer[2] = {0};

  // Buffer of characteristic for sending analog input values of P2.
  uint8_t analogInP2ChBuffer[2] = {0};

  // Buffer of characteristic for sending shared data.
  uint8_t sharedDataChBuffer[8] = {0};

  /**
   * Write IO characteristics.
   */
  void writeDigitalIn();

public:
  int characteristicCount() { return mbitmore_cIdx_COUNT; };
  MicroBitBLEChar *characteristicPtr(int idx) { return &chars[idx]; };
};

#endif // CONFIG_ENABLED(DEVICE_BLE)
#endif // MBIT_MORE_SERVICE_H
#endif // MICROBIT_CODAL
