/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                         *
 *  Copyright (C) 2020 Mect s.r.l. <smart-home@mect.it>                 *
 *                                                                         *
 *  This library is free software; you can redistribute it and/or          *
 *  modify it under the terms of the GNU Lesser General Public             *
 *  License as published by the Free Software Foundation;                  *
 *  version 3 of the License.                                              *
 *                                                                         *
 *  This library is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 *  Lesser General Public License for more details.                        *
 *                                                                         *
 *  You should have received a copy of the GNU Lesser General Public       *
 *  License along with this library; If not, see                           *
 *  <http://www.gnu.org/licenses/>.                                        *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

//-----------------------------------------------
// ???? The output compiled .so file has
// ???? to be copied on: /usr/lib/x86_64-linux-gnu/nymea/plugins/
//-----------------------------------------------


#define INVALID_VALUE           "----"
#define LABEL_WSUNRAYS    QString::fromUtf8("☼")  // QChar(0x263c) White Sun with Rays
#define LABEL_MOON        QString::fromUtf8("☽")  // QChar(0x263d) First Quarter Moon

#include "plugininfo.h"
#include "integrationpluginmect.h"

#include <math.h>       /* floor */
#include <QTime>        /*Time Format display*/


IntegrationPluginMect::IntegrationPluginMect()
{
    // Stati Termostato
    lstThermoStatus.clear();
    lstThermoStatus.append(QT_TR_NOOP("Off"));
    lstThermoStatus.append(QT_TR_NOOP("Auto"));
    lstThermoStatus.append(QT_TR_NOOP("-2"));
    lstThermoStatus.append(QT_TR_NOOP("+2"));
    lstThermoStatus.append(QT_TR_NOOP("Boost"));
    // Stati Antifurto ZERO, OFF, ARMED, ENABLED, RINGING, MUTED, TESTING
    lstBaStatus.clear();
    lstBaStatus.append(QT_TR_NOOP("Zero"));
    lstBaStatus.append(QT_TR_NOOP("Off"));
    lstBaStatus.append(QT_TR_NOOP("Armed"));
    lstBaStatus.append(QT_TR_NOOP("Enabled"));
    lstBaStatus.append(QT_TR_NOOP("Ringing"));
    lstBaStatus.append(QT_TR_NOOP("Muted"));
    lstBaStatus.append(QT_TR_NOOP("Testing"));
}

IntegrationPluginMect::~IntegrationPluginMect()
{
    foreach (Thing* currentThing, this->myThings()) {
        qCDebug(dcMect()) << QString("Thing Name: [%1]") .arg(currentThing->name());
        QTimer *thingTimer = m_simulationTimers.value(currentThing);
        if (thingTimer  && thingTimer->isActive())  {
            thingTimer->stop();
        }
    }
}

void IntegrationPluginMect::init()
{
    // Initialisation can be done here.
    qCDebug(dcMect()) << QString("Plugin initialized. Version: %1") .arg(MECT_VERSION);
}

void IntegrationPluginMect::setupThing(ThingSetupInfo *info)
{
    struct  dati_device *deviceInfo;
    int                 nReg = 0;

    // Tutti i Device Mect sono Modbus TCP
    Thing *mySelf = info->thing();
    qCDebug(dcMect()) << "Set up thing" << mySelf->name();
    QString szValue;
    // Data Init
    deviceInfo = new dati_device();
    deviceInfo->isConnected = false;
    deviceInfo->readLoop = 0;
    deviceInfo->isNightTime = false;
    deviceInfo->datiBA = nullptr;
    deviceInfo->datiEP = nullptr;
    deviceInfo->datiTH = nullptr;
    deviceInfo->deviceMutex = new QMutex();
    // Pulizia dei Buffer per i Registri
    for (nReg = 0; nReg < TOTAL_HOLDING_REGS; nReg++)  {
        deviceInfo->holdingRegisters[nReg] = 0;
    }
    for (nReg = 0; nReg < TOTAL_WRITING_REGS; nReg++)  {
        deviceInfo->writeHoldingRegistersValues[nReg] = 0;
    }
    // Retrieving Settings Values by Device Type
    // Thermostat
    if (mySelf->thingClassId() == mectThermostatThingClassId)  {
        deviceInfo->szMyIPaddress = mySelf->paramValue(mectThermostatThingIpAddressParamTypeId).toString();
        deviceInfo->nMyPort = mySelf->paramValue(mectThermostatThingIpPortParamTypeId).toInt();
        deviceInfo->refreshTime = mySelf->paramValue(mectThermostatThingRefreshTimeParamTypeId).toInt();
        deviceInfo->myId = mySelf->paramValue(mectThermostatThingThermoIdParamTypeId).toInt();
        deviceInfo->myName = mySelf->paramValue(mectThermostatThingRoomNameParamTypeId).toString();
        szValue = QString("%1 - %2") .arg(deviceInfo->myId) .arg(deviceInfo->myName);
        mySelf->setStateValue(mectThermostatZoneNameStateTypeId, szValue);
        deviceInfo->datiTH = new dati_termostato();
        deviceInfo->firstModbusReg = (THERMO_BLOCK_SIZE * (deviceInfo->myId - 1)) + THERMO_STARTING_REG;
        deviceInfo->regsToRead = THERMO_TOTAL_REGS;
    }
    // Electric Panel
    else if (mySelf->thingClassId() == mectElectricPanelThingClassId)  {
        deviceInfo->szMyIPaddress = mySelf->paramValue(mectElectricPanelThingIpAddressParamTypeId).toString();
        deviceInfo->nMyPort = mySelf->paramValue(mectElectricPanelThingIpPortParamTypeId).toInt();
        deviceInfo->refreshTime = mySelf->paramValue(mectElectricPanelThingRefreshTimeParamTypeId).toInt();
        deviceInfo->myId = 0;
        deviceInfo->myName = mySelf->paramValue(mectElectricPanelThingPanelNameParamTypeId).toString();
        szValue = QString("%1 - %2") .arg(deviceInfo->myId) .arg(deviceInfo->myName);
        mySelf->setStateValue(mectElectricPanelEpNameStateTypeId, szValue);
        deviceInfo->datiEP = new dati_electric_panel();
        deviceInfo->firstModbusReg = 0;
        deviceInfo->regsToRead = EP_TOTAL_REGS;
    }
    else if (mySelf->thingClassId() == mectAntifurtoThingClassId)  {
        deviceInfo->szMyIPaddress = mySelf->paramValue(mectAntifurtoThingIpAddressParamTypeId).toString();
        deviceInfo->nMyPort = mySelf->paramValue(mectAntifurtoThingIpPortParamTypeId).toInt();
        deviceInfo->refreshTime = mySelf->paramValue(mectAntifurtoThingRefreshTimeParamTypeId).toInt();
        deviceInfo->myId = 0;
        deviceInfo->myName = mySelf->paramValue(mectAntifurtoThingLocationNameParamTypeId).toString();
        mySelf->setStateValue(mectAntifurtoBaNameStateTypeId, deviceInfo->myName);
        deviceInfo->datiBA = new dati_antifurto();
        deviceInfo->firstModbusReg = BA_STARTING_REG;
        deviceInfo->regsToRead = BA_TOTAL_REGS;
    }
    qCDebug(dcMect()) << QString("Setup Mect thing  id [%1] - [%2]@IP: %3:%4 Refresh: [%5]") .arg(deviceInfo->myId) .arg(deviceInfo->myName)
                                .arg(deviceInfo->szMyIPaddress) .arg(deviceInfo->nMyPort) .arg(deviceInfo->refreshTime);
    // Creating Modbus Interface Object
    deviceInfo->modBusHandler = new modbus();
    deviceInfo->modBusHandler->modbus_set_slave_id(1);
    // Open Modbus Connection
    deviceInfo->isConnected = deviceInfo->modBusHandler->modbus_connect(deviceInfo->szMyIPaddress.toStdString(), deviceInfo->nMyPort);
    if (deviceInfo->isConnected)  {
        qCDebug(dcMect()) << QString("Modbus Connection to Slave [IP: %1 - Port: %2] up and running") .arg(deviceInfo->szMyIPaddress) .arg(deviceInfo->nMyPort);
    }
    else  {
        qCWarning(dcMect()) << QString("Connection to Slave [IP: %1 - Port: %2] failed") .arg(deviceInfo->szMyIPaddress) .arg(deviceInfo->nMyPort);
    }
    // Aggiunta del Timer di interrogazione dell'oggetto
    deviceInfo->readTimer = new QTimer(mySelf);
    connect(deviceInfo->readTimer, &QTimer::timeout, this, &IntegrationPluginMect::updateFieldData);
    qCDebug(dcMect()) << QString("Starting timer with interval for device [%2] [%1] sec") .arg(deviceInfo->refreshTime) .arg(deviceInfo->myName);
    deviceInfo->readTimer->start(deviceInfo->refreshTime * 1000);
    // Aggiunta dell'oggetto alla lista dei Device info
    m_devicesInfo.insert(mySelf, deviceInfo);
    m_simulationTimers.insert(mySelf, deviceInfo->readTimer);
    info->finish(Thing::ThingErrorNoError);
}

void IntegrationPluginMect::executeAction(ThingActionInfo *info)
{
    // An action is being executed. Use info->action() to get details about the action,
    // do the required operations (e.g. send a command to the network) and call info->finish() when done.
    Thing *thing = info->thing();
    Action action = info->action();
    struct dati_device *deviceInfo;


    qCDebug(dcMect()) << "Executing action for thing" << thing << action.actionTypeId().toString() << action.params();
    if (! m_devicesInfo.contains(thing))  {
        qCCritical(dcMect()) << QString("Thing [%1] not found in Device Collection! - Action ignored") .arg(thing->name());
        return;
    }
    // Retrieving Device Information
    deviceInfo = m_devicesInfo.value(thing);
    // Device not connected, action ignored
    if (! deviceInfo->isConnected)  {
        qCCritical(dcMect()) << QString("Thing [%1] not Connected! - Action ignored") .arg(deviceInfo->myName);
        return;
    }
    // QMutex ??
    deviceInfo->deviceMutex->lock();
    // Thermostat
    if (thing->thingClassId() == mectThermostatThingClassId)  {
        int     nEnabledSensors = deviceInfo->datiTH->TH_enabled_sensors;
        // New Temperature Target
        if (action.actionTypeId() == mectThermostatTargetTemperatureActionTypeId) {
            int     nReg        = deviceInfo->firstModbusReg + (deviceInfo->isNightTime ? THERMO_TEMP_SP_NIGHT_REG : THERMO_TEMP_SP_DAY_REG);
            double  oldTarget   = deviceInfo->isNightTime ? deviceInfo->datiTH->TH_temperature_setpoint_nt : deviceInfo->datiTH->TH_temperature_setpoint;
            double  newTarget   = action.param(mectThermostatTargetTemperatureActionTargetTemperatureParamTypeId).value().toDouble();
            // Il target sul device è gestito come fixpoint a un decimale arrotondato a 1/2 grado
            deviceInfo->singleRegisterValue = (((uint16_t) (newTarget * 10.0)) / 5) * 5;
            newTarget = ((float) deviceInfo->singleRegisterValue) / 10.0;
            if (newTarget != oldTarget)  {
                qCDebug(dcMect()) << QString("Changing Temperature target [%1]-->[%2] for Register: [%3] Value[%4]") .arg(oldTarget, 5, 'f', 1) .arg(newTarget, 5, 'f', 1) .arg(nReg) .arg(deviceInfo->singleRegisterValue);
                if (deviceInfo->modBusHandler->modbus_write_register(nReg, deviceInfo->singleRegisterValue))  {
                    qCCritical(dcMect()) <<  QString("Error writing Modbus Register:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
                }
                else  {
                    thing->setStateValue(mectThermostatTargetTemperatureStateTypeId, newTarget);
                }
            }
            else  {
                thing->setStateValue(mectThermostatTargetTemperatureStateTypeId, oldTarget);
                qCWarning(dcMect()) << QString("Changing Temperature target [%1]-->[%2]  rejected") .arg(oldTarget, 5, 'f', 1) .arg(newTarget, 5, 'f', 1);
            }
        }
        // New Humidity Target
        else if (action.actionTypeId() == mectThermostatTargetHumidityActionTypeId)  {
            int     nReg        = deviceInfo->firstModbusReg + (deviceInfo->isNightTime ? THERMO_HUM_SP_NIGHT_REG : THERMO_HUM_SP_DAY_REG);
            int     oldTarget   = deviceInfo->isNightTime ? deviceInfo->datiTH->TH_humidity_setpoint_nt : deviceInfo->datiTH->TH_humidity_setpoint;
            int     newTarget   = action.param(mectThermostatTargetHumidityActionTargetHumidityParamTypeId).value().toInt();
            // Il target sul device è gestito come fixpoint a un decimale ma viene passato solo un intero
            deviceInfo->singleRegisterValue = ((uint16_t) newTarget * 10);
            // Cambia il valore solo se il termostato ha anche la lettura dell'umidità
            if (newTarget != oldTarget && nEnabledSensors < 0)  {
                // Rounding a 5%
                qCDebug(dcMect()) << QString("Changing Humidity target [%1]-->[%2] for Register: [%3] Value[%4]") .arg(oldTarget) .arg(newTarget) .arg(nReg) .arg(deviceInfo->singleRegisterValue);
                if (deviceInfo->modBusHandler->modbus_write_register(nReg, deviceInfo->singleRegisterValue))  {
                    qCCritical(dcMect()) <<  QString("Error writing Modbus Register:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
                }
                else  {
                    thing->setStateValue(mectThermostatTargetHumidityStateTypeId, newTarget);
                }
            }
            else {
                thing->setStateValue(mectThermostatTargetHumidityStateTypeId, oldTarget);
                qCWarning(dcMect()) << QString("Changing Humidity target [%1]-->[%2] rejected") .arg(oldTarget) .arg(newTarget);
            }
        }
        // New Thermo State Action
        else if (action.actionTypeId() == mectThermostatHeatingStatusActionTypeId)  {
            int     nReg        = deviceInfo->firstModbusReg + THERMO_HEATING_STATUS;
            QString szOldValue  = thing->stateValue(mectThermostatHeatingStatusStateTypeId).toString();
            QString szNewValue  = action.param(mectThermostatHeatingStatusActionHeatingStatusParamTypeId).value().toString();
            int     newStatus   = lstThermoStatus.indexOf(szNewValue);
            // Cambia il valore se il nuovo stato è presente nell'elenco degli stati possibili
            if (newStatus >= 0 && deviceInfo->datiTH->TH_heating_status != newStatus)  {
                // Adjust Thermo Heating Time if Zero
                if (deviceInfo->datiTH->TH_heating_timer <= 0) deviceInfo->datiTH->TH_heating_timer = THERMO_HEATING_TIME;
                deviceInfo->writeHoldingRegistersValues[0] = (uint16_t) newStatus;
                deviceInfo->writeHoldingRegistersValues[1] = (uint16_t) deviceInfo->datiTH->TH_heating_timer;
                qCDebug(dcMect()) << QString("Changing Thermostat Status from [%1]-->[%2] for Register: [%3] Value[%4] Heating Time [%5]") .arg(szOldValue) .arg(szNewValue) .arg(nReg) .arg(deviceInfo->singleRegisterValue) .arg(deviceInfo->datiTH->TH_heating_timer);
                if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                    qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
                }
            }
            else  {
                thing->setStateValue(mectThermostatHeatingStatusStateTypeId, szOldValue);
                qCWarning(dcMect()) << QString("Changing Thermostat Status from [%1]-->[%2] rejected") .arg(szOldValue) .arg(szNewValue);
            }
        }
    }
    // Electric Panel
    else if (thing->thingClassId() == mectElectricPanelThingClassId)  {
        // TODO: Azioni compatibili con EP
        // No Actions defined for now....
    }
    // BA Antifurto
    else if (thing->thingClassId() == mectAntifurtoThingClassId)  {
        // Button OFF
        if (action.actionTypeId() == mectAntifurtoBtnOffActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_DISABLE;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
        // Button NightTime
        else if (action.actionTypeId() == mectAntifurtoBtnNightActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_NIGHTTIME;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
        // Button DayTime
        else if (action.actionTypeId() == mectAntifurtoBtnDayTimeActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_DAYTIME;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
        // Button EveryThing
        else if (action.actionTypeId() == mectAntifurtoBtnEverythingActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_EVERYTHING;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
        // Button Enable
        else if (action.actionTypeId() == mectAntifurtoBtnEnableActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_ENABLE;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
        // Button Mute
        else if (action.actionTypeId() == mectAntifurtoBtnMuteActionTypeId)  {
            reg32_union modbusReg;
            int         nReg        = deviceInfo->firstModbusReg + BA_COMMAND_REG;
            uint        oldStatus   = thing->stateValue(mectAntifurtoBaStatusStateTypeId).toUInt();
            uint        baCommand   = ALARM_COMMAND_ACK;
            modbusReg.u32Value      = baCommand;
            qCDebug(dcMect()) << QString("Trying to Send Command to Ba: 0x[%1] Current Status [%2]") .arg(baCommand, 0, 16, QLatin1Char('0')) .arg(oldStatus) ;
            // Todo: Sending the right command to BA
            deviceInfo->writeHoldingRegistersValues[0] = modbusReg.dWord.lo;
            deviceInfo->writeHoldingRegistersValues[1] = modbusReg.dWord.hi;
            if (deviceInfo->modBusHandler->modbus_write_registers(nReg, 2, deviceInfo->writeHoldingRegistersValues))  {
                qCCritical(dcMect()) <<  QString("Error writing Modbus Registers:[%1] Value: 0x[%2]") .arg(nReg) .arg(deviceInfo->singleRegisterValue, 4, 16, QLatin1Char('0'));
            }
        }
    }
    deviceInfo->deviceMutex->unlock();
    info->finish(Thing::ThingErrorNoError);
}

void IntegrationPluginMect::thingRemoved(Thing *thing)
{
    struct dati_device *deviceInfo;

    // A thing is being removed from the system. Do the required cleanup
    if (m_devicesInfo.contains(thing))  {
        deviceInfo = m_devicesInfo.value(thing);
        deviceInfo->deviceMutex->tryLock(deviceInfo->refreshTime * 1000);
        // Stopping Timer
        if (deviceInfo->readTimer)  {
            deviceInfo->readTimer->stop();
            deviceInfo->readTimer->deleteLater();
        }
        // Closing Modbus connection
        if (deviceInfo->modBusHandler)  {
            if (deviceInfo->modBusHandler->isConnected())  {
                qCDebug(dcMect()) << QString("Closing Modbus Connection to Slave for Object: [%1]") .arg(thing->name());
                deviceInfo->modBusHandler->modbus_close();
            }
            else {
                qCWarning(dcMect()) << QString("Modbus connection for Object: [%1] already closed") .arg(thing->name());
            }
        }
        else  {
            qCWarning(dcMect()) << QString("Modbus connection not present for Object: [%1] already closed") .arg(thing->name());
        }
        deviceInfo->deviceMutex->unlock();
        m_devicesInfo.remove(thing);
    }
}

void IntegrationPluginMect::updateFieldData()
{

    // Determina quale oggetto ha scatenato il Timer
    QTimer  *callingTimer = static_cast<QTimer*>(sender());
    Thing   *currentThing = m_simulationTimers.key(callingTimer);
    struct dati_device *deviceInfo;


    bool    readOk = false;

    if (! m_devicesInfo.contains(currentThing))  {
        qCCritical(dcMect()) << QString("Thing [%1] not found in Device Collection! Action ignored") .arg(currentThing->name());
        return;
    }
    deviceInfo = m_devicesInfo.value(currentThing);
    deviceInfo->deviceMutex->tryLock(deviceInfo->refreshTime * 1000);
    if (deviceInfo->modBusHandler)  {
        // Refresh Connection State
        deviceInfo->isConnected = deviceInfo->modBusHandler->isConnected();
        if (deviceInfo->isConnected)  {
            // Ciclo di lettura registri a colpi di 64 per volta
            int     nLetti = 0;
            int     n2Read = deviceInfo->regsToRead <= MODBUS_MAX_BLOCK_SIZE ? deviceInfo->regsToRead : MODBUS_MAX_BLOCK_SIZE;
            int     nStart = deviceInfo->firstModbusReg;
            int     nDestination = 0;
            int     nLoop = 0;
            int8_t  nRes = 0;
            while (n2Read > 0)  {
                if ((nRes = deviceInfo->modBusHandler->modbus_read_holding_registers(nStart, n2Read, &deviceInfo->holdingRegisters[nDestination])) == 0)  {
                    nLetti += n2Read;
                }
                else  {
                    break;
                }
                n2Read = deviceInfo->regsToRead - nLetti;
                // qCDebug(dcMect()) << QString("Device [%1] Loop Lettura [%2] Letti[%3] - Start[%4] - Rimanenti[%5]") .arg(deviceInfo->myName) .arg(nLoop) .arg(nLetti) .arg(nStart) .arg(n2Read);
                // Incremento dei contatori per prossimo giro
                nStart += nLetti;
                nDestination += nLetti;
                ++nLoop;
            }
            if (nLetti == deviceInfo->regsToRead)  {
                readOk = true;
            }
            else  {
                qCWarning(dcMect()) << QString("Error reading Modbus Server: %1") .arg(nRes, 10, 16);
            }
        }
        else  {
            if (deviceInfo->readLoop % 30 == 0)  {
                deviceInfo->modBusHandler->modbus_close();
                qCDebug(dcMect()) << QString("Device [%1] Disconnected - Read Loop [%2], trying to connect...") .arg(deviceInfo->myName) .arg(deviceInfo->readLoop);
                deviceInfo->isConnected = deviceInfo->modBusHandler->modbus_connect(deviceInfo->szMyIPaddress.toStdString(), deviceInfo->nMyPort);
            }
            else  {
                qCDebug(dcMect()) << QString("Device [%1] Disconnected - Read Loop [%2]") .arg(deviceInfo->myName) .arg(deviceInfo->readLoop);
            }
        }
    }
    else  {
        qCWarning(dcMect()) << "No Device defined";
    }
    // Refresh Dati Termostato
    if (currentThing->thingClassId() == mectThermostatThingClassId)  {
        // Aggiornamento Flag di connessione
        currentThing->setStateValue(mectThermostatConnectedStateTypeId, deviceInfo->isConnected);
        // Update dei campi del Plugin
        if (deviceInfo->datiTH && deviceInfo->isConnected && readOk)  {
            parse_hr_termostato(deviceInfo);
            thermostatData2Plugin(currentThing, deviceInfo);
        }
    }
    // Refresh Dati Electric Panel
    else if (currentThing->thingClassId() == mectElectricPanelThingClassId)  {
        // Aggiornamento Flag di connessione
        currentThing->setStateValue(mectElectricPanelConnectedStateTypeId, deviceInfo->isConnected);
        // Update dei campi del Plugin
        if (deviceInfo->datiEP && deviceInfo->isConnected && readOk)  {
            parse_hr_electricp(deviceInfo);
            electricData2Plugin(currentThing, deviceInfo);
        }
    }
    // Refresh Dati Antifurto
    else if (currentThing->thingClassId() == mectAntifurtoThingClassId)  {
        // Aggiornamento Flag di connessione
        currentThing->setStateValue(mectAntifurtoConnectedStateTypeId, deviceInfo->isConnected);
        // Update dei campi del Plugin
        if (deviceInfo->datiBA && deviceInfo->isConnected && readOk)  {
            parse_hr_antifurto(deviceInfo);
            antitheftData2Plugin(currentThing, deviceInfo);
        }
    }
    deviceInfo->deviceMutex->unlock();
    deviceInfo->readLoop++;
}

void IntegrationPluginMect::thermostatData2Plugin(Thing * mySelf, dati_device *deviceInfo)
{
    double  dblValue = 0;
    QString szValue;
    // Valori da processare in funzione del tipo di Sensore e dall'orario
    int     nEnabledSensors = deviceInfo->datiTH->TH_enabled_sensors;
    double  tempSetPoint = 0.0;
    int     humSetPoint = 0;

    // qCDebug(dcMect()) << QString("Thermostat Read Loop: %1") .arg(deviceInfo->readLoop);
    // NightTime
    deviceInfo->isNightTime = deviceInfo->datiTH->TH_nighttime;
    // Reg.00  TH_heartbeat
    mySelf->setStateValue(mectThermostatHeartBeatStateTypeId, deviceInfo->datiTH->TH_heartbeat);
    // Reg.01  TH_enabled_sensors (Se positivo no humidità)
    // mySelf->setStateValue(mectThermostatEnabledSensorsStateTypeId, (nEnabledSensors));
    // Reg.02  TH_temperature
    mySelf->setStateValue(mectThermostatTemperatureStateTypeId, deviceInfo->datiTH->TH_temperature);
    // Reg.103  TH_temperature_bis
    dblValue = 0;
    if (abs(nEnabledSensors) >= 2)  {
        dblValue = deviceInfo->datiTH->TH_temperature_bis;
    }
    mySelf->setStateValue(mectThermostatTemperature2StateTypeId, dblValue);
    // Reg.04  TH_temperature_ext
    dblValue = 0;
    if (abs(nEnabledSensors) >= 3)  {
        dblValue = deviceInfo->datiTH->TH_temperature_ext;
    }
    mySelf->setStateValue(mectThermostatTempExtStateTypeId, dblValue);
    if (nEnabledSensors < 0)  {
        // Reg.05  TH_humidity
        mySelf->setStateValue(mectThermostatHumidityStateTypeId, deviceInfo->datiTH->TH_humidity);
        // Reg.06  TH_humidity_bis
        dblValue = 0;
        if (nEnabledSensors <= -2)  {
            dblValue = deviceInfo->datiTH->TH_humidity;
        }
        mySelf->setStateValue(mectThermostatHumidity2StateTypeId, dblValue);
        // Reg.07  TH_humidity_ext
        dblValue = 0;
        if (nEnabledSensors <= -3)  {
            dblValue = deviceInfo->datiTH->TH_humidity_ext;
        }
        mySelf->setStateValue(mectThermostatHumidityExtStateTypeId, dblValue);
    }
    else  {
        dblValue = 0.0;
        mySelf->setStateValue(mectThermostatHumidityStateTypeId, dblValue);
        mySelf->setStateValue(mectThermostatHumidity2StateTypeId, dblValue);
        mySelf->setStateValue(mectThermostatHumidityExtStateTypeId, dblValue);
    }
    // Daterminazione dei Set Point
    tempSetPoint    =   deviceInfo->isNightTime ? deviceInfo->datiTH->TH_temperature_setpoint_nt : deviceInfo->datiTH->TH_temperature_setpoint;
    humSetPoint     =   0;
    if (nEnabledSensors < 0)  {
        humSetPoint     =   deviceInfo->isNightTime ? deviceInfo->datiTH->TH_humidity_setpoint_nt : deviceInfo->datiTH->TH_humidity_setpoint;
    }
    // Update Set Points
    mySelf->setStateValue(mectThermostatTargetTemperatureStateTypeId, tempSetPoint);
    mySelf->setStateValue(mectThermostatTargetHumidityStateTypeId, humSetPoint);
    // Reg.10  TH_enabled_lamps
    // Reg.11  TH_lamp_1-4
    // Reg.12  TH_control_type
    // Reg.13  TH_heating Status
    mySelf->setStateValue(mectThermostatHeatingOnStateTypeId, deviceInfo->datiTH->TH_heating);
    // Periodo del Giorno
    if (deviceInfo->isNightTime)  {
        mySelf->setStateValue(mectThermostatIsNightTimeStateTypeId, LABEL_MOON);
    }
    else  {
        mySelf->setStateValue(mectThermostatIsNightTimeStateTypeId, LABEL_WSUNRAYS);
    }
    // Reg.14  TH_heating_status (intero da cui dipende la descrizione)
    if (deviceInfo->datiTH->TH_heating_status >= 0 && deviceInfo->datiTH->TH_heating_status < lstThermoStatus.count())  {
        szValue = lstThermoStatus.at(deviceInfo->datiTH->TH_heating_status);
    }
    else  {
        szValue = lstThermoStatus.at(0);        // Display Off if Out of Range
    }
    mySelf->setStateValue(mectThermostatHeatingStatusStateTypeId, szValue);
    // Reg.15  TH_heating_timer
    if (deviceInfo->datiTH->TH_heating_timer > 0)  {
        // szValue = QString::number(deviceInfo->datiTH->TH_heating_timer);
        szValue = seconds2String(deviceInfo->datiTH->TH_heating_timer);
    }
    else  {
        szValue = QString(INVALID_VALUE);
    }
    mySelf->setStateValue(mectThermostatHeatingTimerStateTypeId, szValue);
    // Reg.16  TH_sunrise
    // Reg.17  TH_sunset
    // Reg.21  TH_requested_W
    mySelf->setStateValue(mectThermostatRequestedWStateTypeId, deviceInfo->datiTH->TH_requested_W);
    // Reg.22  TH_control_type
    mySelf->setStateValue(mectThermostatControlTypeStateTypeId, deviceInfo->datiTH->TH_control_type);
}

void    IntegrationPluginMect::electricData2Plugin(Thing * mySelf, dati_device *deviceInfo)
{
    // qCDebug(dcMect()) << QString("EP Read Loop: %1") .arg(deviceInfo->readLoop);
    // Reg. 0  EP_heartbeat
    mySelf->setStateValue(mectElectricPanelHeartBeatStateTypeId, deviceInfo->datiEP->EP_heartbeat);
    // Reg. 1  EP_enabled_wattmeters
    mySelf->setStateValue(mectElectricPanelEnabledMetersStateTypeId, deviceInfo->datiEP->EP_enabled_wattmeters);
    // Reg. 3  EP_wattmeter_M_W (W)
    mySelf->setStateValue(mectElectricPanelCurrentPowerStateTypeId, (double) deviceInfo->datiEP->EP_wattmeter_M_W);
    // Reg. 5 EP_wattmeter_M_VA (VA)
    mySelf->setStateValue(mectElectricPanelMainActivePowerStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_VA);
    // Reg. 7  EP_wattmeter_M_F (Hz)
    mySelf->setStateValue(mectElectricPanelInHzStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_Hz);
    // Reg. 8  EP_wattmeter_M_V (Volt)
    mySelf->setStateValue(mectElectricPanelInVoltStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_V);
    // Reg. 9  EP_wattmeter_M_A (A)
    mySelf->setStateValue(mectElectricPanelMainCurrentStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_A);
    // Reg. 10  EP_wattmeter_M_kWh (kWh)
    mySelf->setStateValue(mectElectricPanelTotalEnergyConsumedStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_kWh);
    // Reg. 75  EP_wattmeter_M_kWh_60s (kWh)
    mySelf->setStateValue(mectElectricPanelMainDeltaKWh60sStateTypeId, deviceInfo->datiEP->EP_wattmeter_M_kWh_60s);
    // Reg. 14  EP_wattmeter_F_W (W)
    mySelf->setStateValue(mectElectricPanelFPowerStateTypeId, deviceInfo->datiEP->EP_wattmeter_F_W);
    // Reg. 16  EP_wattmeter_F_VA (VA)
    mySelf->setStateValue(mectElectricPanelFActivePowerStateTypeId, deviceInfo->datiEP->EP_wattmeter_F_VA);
    // Reg. 21  EP_wattmeter_F_kWh (kWh)
    mySelf->setStateValue(mectElectricPanelFTotalKWhStateTypeId, deviceInfo->datiEP->EP_wattmeter_F_kWh);
    // Reg. 77  EP_wattmeter_F_kWh_60s (kWh)
    mySelf->setStateValue(mectElectricPanelFDeltaKWh60sStateTypeId, deviceInfo->datiEP->EP_wattmeter_F_kWh_60s);
    // Reg. 89  EP_BlackoutDetected
    mySelf->setStateValue(mectElectricPanelIsBlackOutStateTypeId, deviceInfo->datiEP->EP_BlackoutDetected);
    // Reg. 89  EP_OverloadDetected
    mySelf->setStateValue(mectElectricPanelIsOverloadStateTypeId, deviceInfo->datiEP->EP_OverloadDetected);
    // Reg. 95  EP_requested_W
    mySelf->setStateValue(mectElectricPanelRequestedWStateTypeId, deviceInfo->datiEP->EP_requested_W);
    // Reg. 102 EP_assigned_W
    mySelf->setStateValue(mectElectricPanelAssignedWStateTypeId, deviceInfo->datiEP->EP_assigned_W);
    // Reg. 103 EP_control_type )
    mySelf->setStateValue(mectElectricPanelControlTypeStateTypeId, deviceInfo->datiEP->EP_control_type);
}

void        IntegrationPluginMect::antitheftData2Plugin(Thing *mySelf, struct dati_device *deviceInfo)
{
    QString szValue;

    // qCDebug(dcMect()) << QString("BA Read Loop: %1") .arg(deviceInfo->readLoop);
    // Reg. 0  BA_heartbeat
    mySelf->setStateValue(mectAntifurtoHeartBeatStateTypeId, deviceInfo->datiBA->BA_heartbeat);
    // Reg. 1  BA_enabled_sensors
    mySelf->setStateValue(mectAntifurtoEnabledSensorsStateTypeId, deviceInfo->datiBA->BA_enabled_sensors);
    // Reg. 2 BA_status
    if ((int) deviceInfo->datiBA->BA_status < lstBaStatus.count())  {
        szValue = lstBaStatus.at(deviceInfo->datiBA->BA_status);
    }
    else  {
        szValue = lstBaStatus.at(0);        // Display Off if Out of Range
    }
    mySelf->setStateValue(mectAntifurtoBaStatusStateTypeId, szValue);
    // Reg. 6  Bit 1 BA_led_green
    mySelf->setStateValue(mectAntifurtoLedGreenStateTypeId, deviceInfo->datiBA->BA_led_green);
    // Reg. 6  Bit 2 BA_led_red
    mySelf->setStateValue(mectAntifurtoLedRedStateTypeId, deviceInfo->datiBA->BA_led_red);
    // Reg. 6  Bit 3 BA_led_yellow1
    mySelf->setStateValue(mectAntifurtoLedYellow1StateTypeId, deviceInfo->datiBA->BA_led_yellow1);
    // Reg. 6  Bit 4 BA_led_yellow2
    mySelf->setStateValue(mectAntifurtoLedYellow2StateTypeId, deviceInfo->datiBA->BA_led_yellow2);
    // Reg. 6  Bit 5 BA_siren
    mySelf->setStateValue(mectAntifurtoSirenOnStateTypeId, deviceInfo->datiBA->BA_siren);
    // Reg. 6  Bit 5 BA_BlackoutDetected
    mySelf->setStateValue(mectAntifurtoPowerFailStateTypeId, deviceInfo->datiBA->BA_BlackoutDetected);
    // Reg. 41 ControlType
    mySelf->setStateValue(mectAntifurtoControlTypeStateTypeId, deviceInfo->datiBA->BA_control_type);
}



void        IntegrationPluginMect::parse_hr_termostato(dati_device *deviceInfo)
{
    deviceInfo->datiTH->TH_heartbeat             = parseRegister(deviceInfo->holdingRegisters, 0).u16Value;
    deviceInfo->datiTH->TH_enabled_sensors       = parseRegister(deviceInfo->holdingRegisters, 1).i16Value;
    deviceInfo->datiTH->TH_temperature           = parseRegister(deviceInfo->holdingRegisters, 2).i16Value / 10.0;
    deviceInfo->datiTH->TH_temperature_bis       = parseRegister(deviceInfo->holdingRegisters, 3).i16Value / 10.0;
    deviceInfo->datiTH->TH_temperature_ext       = parseRegister(deviceInfo->holdingRegisters, 4).i16Value / 10.0;
    deviceInfo->datiTH->TH_humidity              = parseRegister(deviceInfo->holdingRegisters, 5).i16Value / 10.0;
    deviceInfo->datiTH->TH_humidity_bis          = parseRegister(deviceInfo->holdingRegisters, 6).i16Value / 10.0;
    deviceInfo->datiTH->TH_humidity_ext          = parseRegister(deviceInfo->holdingRegisters, 7).i16Value / 10.0;
    deviceInfo->datiTH->TH_temperature_setpoint  = parseRegister(deviceInfo->holdingRegisters, 8).i16Value / 10.0;
    deviceInfo->datiTH->TH_humidity_setpoint     = parseRegister(deviceInfo->holdingRegisters, 9).i16Value / 10;
    deviceInfo->datiTH->TH_enabled_lamps         = parseRegister(deviceInfo->holdingRegisters, 10).u16Value;
    deviceInfo->datiTH->TH_lamp_1                = deviceInfo->holdingRegisters[11] & 0x0001;           //  WORD_BIT Decimal 1
    deviceInfo->datiTH->TH_lamp_2                = deviceInfo->holdingRegisters[11] & 0x0002;           //  WORD_BIT Decimal 2
    deviceInfo->datiTH->TH_lamp_3                = deviceInfo->holdingRegisters[11] & 0x0004;           //  WORD_BIT Decimal 3
    deviceInfo->datiTH->TH_lamp_4                = deviceInfo->holdingRegisters[11] & 0x0008;           //  WORD_BIT Decimal 4
    deviceInfo->datiTH->TH_lamp_5                = deviceInfo->holdingRegisters[11] & 0x0010;           //  WORD_BIT Decimal 5
    deviceInfo->datiTH->TH_max_request_W         = parseRegister(deviceInfo->holdingRegisters, 12).u16Value;
    deviceInfo->datiTH->TH_heating               = deviceInfo->holdingRegisters[13] & 0x0001;           //  WORD_BIT Decimal 1
    deviceInfo->datiTH->TH_nighttime             = deviceInfo->holdingRegisters[13] & 0x0002;           //  WORD_BIT Decimal 2
    deviceInfo->datiTH->TH_heating_status        = parseRegister(deviceInfo->holdingRegisters, 14).i16Value;
    deviceInfo->datiTH->TH_heating_timer         = parseRegister(deviceInfo->holdingRegisters, 15).i16Value;
    deviceInfo->datiTH->TH_sunrise               = parseRegister(deviceInfo->holdingRegisters, 16).u16Value;
    deviceInfo->datiTH->TH_sunset                = parseRegister(deviceInfo->holdingRegisters, 17).u16Value;
    deviceInfo->datiTH->TH_temperature_setpoint_nt= parseRegister(deviceInfo->holdingRegisters, 18).i16Value / 10.0;
    deviceInfo->datiTH->TH_humidity_setpoint_nt  = parseRegister(deviceInfo->holdingRegisters, 19).i16Value / 10.0;
    deviceInfo->datiTH->TH_lamp_feedback_1       = deviceInfo->holdingRegisters[11] & 0x0001;           //  WORD_BIT Decimal 1
    deviceInfo->datiTH->TH_lamp_feedback_2       = deviceInfo->holdingRegisters[11] & 0x0002;           //  WORD_BIT Decimal 2
    deviceInfo->datiTH->TH_lamp_feedback_3       = deviceInfo->holdingRegisters[11] & 0x0004;           //  WORD_BIT Decimal 3
    deviceInfo->datiTH->TH_lamp_feedback_4       = deviceInfo->holdingRegisters[11] & 0x0008;           //  WORD_BIT Decimal 4
    deviceInfo->datiTH->TH_lamp_feedback_5       = deviceInfo->holdingRegisters[11] & 0x0010;           //  WORD_BIT Decimal 5
    deviceInfo->datiTH->TH_requested_W           = parseRegister(deviceInfo->holdingRegisters, 21).u16Value;
    deviceInfo->datiTH->TH_control_type          = parseRegister(deviceInfo->holdingRegisters, 22).u16Value;
}

void        IntegrationPluginMect::parse_hr_electricp(dati_device *deviceInfo)
{
    deviceInfo->datiEP->EP_heartbeat         = parseRegister(deviceInfo->holdingRegisters, 0).u16Value;
    deviceInfo->datiEP->EP_enabled_wattmeters= parseRegister(deviceInfo->holdingRegisters, 1).u16Value;
    deviceInfo->datiEP->EP_wattmeters_ok     = parseRegister(deviceInfo->holdingRegisters, 2).u16Value;
    // Main WM
    deviceInfo->datiEP->EP_wattmeter_M_W     = parseRegister(deviceInfo->holdingRegisters, 3).i16Value;
    deviceInfo->datiEP->EP_wattmeter_M_var   = parseRegister(deviceInfo->holdingRegisters, 4).i16Value;
    deviceInfo->datiEP->EP_wattmeter_M_VA    = parseRegister(deviceInfo->holdingRegisters, 5).i16Value;
    deviceInfo->datiEP->EP_wattmeter_M_pf    = parseRegister(deviceInfo->holdingRegisters, 6).i16Value / 1000.0;
    deviceInfo->datiEP->EP_wattmeter_M_Hz     = parseRegister(deviceInfo->holdingRegisters, 7).i16Value / 100.0;
    deviceInfo->datiEP->EP_wattmeter_M_V     = parseRegister(deviceInfo->holdingRegisters, 8).i16Value / 100.0;
    deviceInfo->datiEP->EP_wattmeter_M_A     = parseRegister(deviceInfo->holdingRegisters, 9).i16Value / 100.0;
    deviceInfo->datiEP->EP_wattmeter_M_kWh   = parseRegister(deviceInfo->holdingRegisters, 10, true).i32Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter_M_e_kWh = parseRegister(deviceInfo->holdingRegisters, 12, true).i32Value / 10.0;
    // F WM
    deviceInfo->datiEP->EP_wattmeter_F_W     = parseRegister(deviceInfo->holdingRegisters, 14).i16Value;
    deviceInfo->datiEP->EP_wattmeter_F_var   = parseRegister(deviceInfo->holdingRegisters, 15).i16Value;
    deviceInfo->datiEP->EP_wattmeter_F_VA    = parseRegister(deviceInfo->holdingRegisters, 16).i16Value;
    deviceInfo->datiEP->EP_wattmeter_F_pf    = parseRegister(deviceInfo->holdingRegisters, 17).i16Value / 1000.0;
    deviceInfo->datiEP->EP_wattmeter_F_Hz     = parseRegister(deviceInfo->holdingRegisters, 18).i16Value / 100.0;
    deviceInfo->datiEP->EP_wattmeter_F_V     = parseRegister(deviceInfo->holdingRegisters, 19).i16Value / 100.0;
    deviceInfo->datiEP->EP_wattmeter_F_A     = parseRegister(deviceInfo->holdingRegisters, 20).i16Value / 1000.0;;
    deviceInfo->datiEP->EP_wattmeter_F_kWh   = parseRegister(deviceInfo->holdingRegisters, 21, true).i32Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter_F_e_kWh = parseRegister(deviceInfo->holdingRegisters, 23, true).i32Value / 10.0;
    // 01 WM
    deviceInfo->datiEP->EP_wattmeter01_W     = parseRegister(deviceInfo->holdingRegisters, 25).i16Value;
    deviceInfo->datiEP->EP_wattmeter01_var   = parseRegister(deviceInfo->holdingRegisters, 26).i16Value;
    deviceInfo->datiEP->EP_wattmeter01_VA    = parseRegister(deviceInfo->holdingRegisters, 27).i16Value;
    deviceInfo->datiEP->EP_wattmeter01_kWh   = parseRegister(deviceInfo->holdingRegisters, 28, true).i32Value / 10.0;
    // 02 WM
    deviceInfo->datiEP->EP_wattmeter02_W     = parseRegister(deviceInfo->holdingRegisters, 30).i16Value;
    deviceInfo->datiEP->EP_wattmeter02_var   = parseRegister(deviceInfo->holdingRegisters, 31).i16Value;
    deviceInfo->datiEP->EP_wattmeter02_VA    = parseRegister(deviceInfo->holdingRegisters, 32).i16Value;
    deviceInfo->datiEP->EP_wattmeter02_kWh   = parseRegister(deviceInfo->holdingRegisters, 33, true).i32Value / 10.0;
    // 03 WM
    deviceInfo->datiEP->EP_wattmeter03_W     = parseRegister(deviceInfo->holdingRegisters, 35).i16Value;
    deviceInfo->datiEP->EP_wattmeter03_var   = parseRegister(deviceInfo->holdingRegisters, 36).i16Value;
    deviceInfo->datiEP->EP_wattmeter03_VA    = parseRegister(deviceInfo->holdingRegisters, 37).i16Value;
    deviceInfo->datiEP->EP_wattmeter03_kWh   = parseRegister(deviceInfo->holdingRegisters, 38, true).i32Value / 10.0;
    // 04 WM
    deviceInfo->datiEP->EP_wattmeter04_W     = parseRegister(deviceInfo->holdingRegisters, 40).i16Value;
    deviceInfo->datiEP->EP_wattmeter04_var   = parseRegister(deviceInfo->holdingRegisters, 41).i16Value;
    deviceInfo->datiEP->EP_wattmeter04_VA    = parseRegister(deviceInfo->holdingRegisters, 42).i16Value;
    deviceInfo->datiEP->EP_wattmeter04_kWh   = parseRegister(deviceInfo->holdingRegisters, 43, true).i32Value / 10.0;
    // 05 WM
    deviceInfo->datiEP->EP_wattmeter05_W     = parseRegister(deviceInfo->holdingRegisters, 45).i16Value;
    deviceInfo->datiEP->EP_wattmeter05_var   = parseRegister(deviceInfo->holdingRegisters, 46).i16Value;
    deviceInfo->datiEP->EP_wattmeter05_VA    = parseRegister(deviceInfo->holdingRegisters, 47).i16Value;
    deviceInfo->datiEP->EP_wattmeter05_kWh   = parseRegister(deviceInfo->holdingRegisters, 48, true).i32Value / 10.0;
    // 06 WM
    deviceInfo->datiEP->EP_wattmeter06_W     = parseRegister(deviceInfo->holdingRegisters, 50).i16Value;
    deviceInfo->datiEP->EP_wattmeter06_var   = parseRegister(deviceInfo->holdingRegisters, 51).i16Value;
    deviceInfo->datiEP->EP_wattmeter06_VA    = parseRegister(deviceInfo->holdingRegisters, 52).i16Value;
    deviceInfo->datiEP->EP_wattmeter06_kWh   = parseRegister(deviceInfo->holdingRegisters, 53, true).i32Value / 10.0;
    // 07 WM
    deviceInfo->datiEP->EP_wattmeter07_W     = parseRegister(deviceInfo->holdingRegisters, 55).i16Value;
    deviceInfo->datiEP->EP_wattmeter07_var   = parseRegister(deviceInfo->holdingRegisters, 56).i16Value;
    deviceInfo->datiEP->EP_wattmeter07_VA    = parseRegister(deviceInfo->holdingRegisters, 57).i16Value;
    deviceInfo->datiEP->EP_wattmeter07_kWh   = parseRegister(deviceInfo->holdingRegisters, 58, true).i32Value / 10.0;
    // 08 WM
    deviceInfo->datiEP->EP_wattmeter08_W     = parseRegister(deviceInfo->holdingRegisters, 60).i16Value;
    deviceInfo->datiEP->EP_wattmeter08_var   = parseRegister(deviceInfo->holdingRegisters, 61).i16Value;
    deviceInfo->datiEP->EP_wattmeter08_VA    = parseRegister(deviceInfo->holdingRegisters, 62).i16Value;
    deviceInfo->datiEP->EP_wattmeter08_kWh   = parseRegister(deviceInfo->holdingRegisters, 63, true).i32Value / 10.0;
    // 09 WM
    deviceInfo->datiEP->EP_wattmeter09_W     = parseRegister(deviceInfo->holdingRegisters, 65).i16Value;
    deviceInfo->datiEP->EP_wattmeter09_var   = parseRegister(deviceInfo->holdingRegisters, 66).i16Value;
    deviceInfo->datiEP->EP_wattmeter09_VA    = parseRegister(deviceInfo->holdingRegisters, 67).i16Value;
    deviceInfo->datiEP->EP_wattmeter09_kWh   = parseRegister(deviceInfo->holdingRegisters, 68, true).i32Value / 10.0;
    // 10 WM
    deviceInfo->datiEP->EP_wattmeter10_W     = parseRegister(deviceInfo->holdingRegisters, 70).i16Value;
    deviceInfo->datiEP->EP_wattmeter10_var   = parseRegister(deviceInfo->holdingRegisters, 71).i16Value;
    deviceInfo->datiEP->EP_wattmeter10_VA    = parseRegister(deviceInfo->holdingRegisters, 72).i16Value;
    deviceInfo->datiEP->EP_wattmeter10_kWh   = parseRegister(deviceInfo->holdingRegisters, 73, true).i32Value / 10.0;
    // Valori ultimi 60s
    deviceInfo->datiEP->EP_wattmeter_M_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 75).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter_M_e_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 76).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter_F_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 77).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter_F_e_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 78).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter01_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 79).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter02_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 80).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter03_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 81).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter04_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 82).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter05_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 83).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter06_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 84).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter07_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 85).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter08_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 86).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter09_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 87).i16Value / 10.0;
    deviceInfo->datiEP->EP_wattmeter10_kWh_60s = parseRegister(deviceInfo->holdingRegisters, 88).i16Value / 10.0;
    deviceInfo->datiEP->EP_BlackoutDetected    = deviceInfo->holdingRegisters[89] & 0x0001;                 //  WORD_BIT Decimal 1
    deviceInfo->datiEP->EP_OverloadDetected    = deviceInfo->holdingRegisters[89] & 0x0020;                 //  WORD_BIT Decimal 2
    deviceInfo->datiEP->EP_enabled_relays      = parseRegister(deviceInfo->holdingRegisters, 90).i16Value;
    deviceInfo->datiEP->EP_relay_A             = deviceInfo->holdingRegisters[91] & 0x0001;                 //  WORD_BIT Decimal 1
    deviceInfo->datiEP->EP_relay_B             = deviceInfo->holdingRegisters[91] & 0x0002;                 //  WORD_BIT Decimal 2
    deviceInfo->datiEP->EP_relay_C             = deviceInfo->holdingRegisters[91] & 0x0004;                 //  WORD_BIT Decimal 3
    deviceInfo->datiEP->EP_relay_D             = deviceInfo->holdingRegisters[91] & 0x0008;                 //  WORD_BIT Decimal 4
    deviceInfo->datiEP->EP_relay_E             = deviceInfo->holdingRegisters[91] & 0x0010;                 //  WORD_BIT Decimal 5
    deviceInfo->datiEP->EP_relay_F             = deviceInfo->holdingRegisters[91] & 0x0020;                 //  WORD_BIT Decimal 6
    deviceInfo->datiEP->EP_relay_G             = deviceInfo->holdingRegisters[91] & 0x0040;                 //  WORD_BIT Decimal 7
    deviceInfo->datiEP->EP_relay_H             = deviceInfo->holdingRegisters[91] & 0x0080;                 //  WORD_BIT Decimal 8
    deviceInfo->datiEP->EP_overload_W          = parseRegister(deviceInfo->holdingRegisters, 92).u16Value;
    deviceInfo->datiEP->EP_max_assigned_W      = parseRegister(deviceInfo->holdingRegisters, 93).u16Value;
    deviceInfo->datiEP->EP_tic_in_tac          = parseRegister(deviceInfo->holdingRegisters, 94).u16Value;
    deviceInfo->datiEP->EP_requested_W         = parseRegister(deviceInfo->holdingRegisters, 95).u16Value;
    deviceInfo->datiEP->EP_T1_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 96).u16Value;
    deviceInfo->datiEP->EP_T2_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 97).u16Value;
    deviceInfo->datiEP->EP_T3_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 98).u16Value;
    deviceInfo->datiEP->EP_T4_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 99).u16Value;
    deviceInfo->datiEP->EP_T5_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 100).u16Value;
    deviceInfo->datiEP->EP_T6_assigned_W       = parseRegister(deviceInfo->holdingRegisters, 101).u16Value;
    deviceInfo->datiEP->EP_assigned_W          = parseRegister(deviceInfo->holdingRegisters, 102).u16Value;
    deviceInfo->datiEP->EP_control_type        = parseRegister(deviceInfo->holdingRegisters, 103).u16Value;
}

void        IntegrationPluginMect::parse_hr_antifurto(dati_device *deviceInfo)
{
    deviceInfo->datiBA->BA_heartbeat             = parseRegister(deviceInfo->holdingRegisters, 0).u16Value;
    deviceInfo->datiBA->BA_enabled_sensors       = parseRegister(deviceInfo->holdingRegisters, 1).u16Value;
    deviceInfo->datiBA->BA_status                = parseRegister(deviceInfo->holdingRegisters, 2).u16Value;
    deviceInfo->datiBA->BA_config_index          = parseRegister(deviceInfo->holdingRegisters, 3).u16Value;
    deviceInfo->datiBA->BA_config_mask           = parseRegister(deviceInfo->holdingRegisters, 4).u16Value;
    deviceInfo->datiBA->BA_led_green             = deviceInfo->holdingRegisters[6] & 0x0001;    //  WORD_BIT Decimal=1
    deviceInfo->datiBA->BA_led_red               = deviceInfo->holdingRegisters[6] & 0x0002;    //  WORD_BIT Decimal=2
    deviceInfo->datiBA->BA_led_yellow1           = deviceInfo->holdingRegisters[6] & 0x0004;    //  WORD_BIT Decimal=3
    deviceInfo->datiBA->BA_led_yellow2           = deviceInfo->holdingRegisters[6] & 0x0008;    //  WORD_BIT Decimal=4
    deviceInfo->datiBA->BA_siren                 = deviceInfo->holdingRegisters[6] & 0x0010;    //  WORD_BIT Decimal=5
    deviceInfo->datiBA->BA_relay_A               = deviceInfo->holdingRegisters[6] & 0x0020;    //  WORD_BIT Decimal=6
    deviceInfo->datiBA->BA_relay_B               = deviceInfo->holdingRegisters[6] & 0x0040;    //  WORD_BIT Decimal=7
    deviceInfo->datiBA->BA_relay_C               = deviceInfo->holdingRegisters[6] & 0x0080;    //  WORD_BIT Decimal=8
    deviceInfo->datiBA->BA_input_9               = deviceInfo->holdingRegisters[6] & 0x0100;    //  WORD_BIT Decimal=9
    deviceInfo->datiBA->BA_input_10              = deviceInfo->holdingRegisters[6] & 0x0200;    //  WORD_BIT Decimal=10
    deviceInfo->datiBA->BA_input_11              = deviceInfo->holdingRegisters[6] & 0x0400;    //  WORD_BIT Decimal=11
    deviceInfo->datiBA->BA_input_12              = deviceInfo->holdingRegisters[6] & 0x0800;    //  WORD_BIT Decimal=12
    deviceInfo->datiBA->BA_input_12              = deviceInfo->holdingRegisters[6] & 0x0800;    //  WORD_BIT Decimal=12
    deviceInfo->datiBA->BA_BlackoutDetected      = deviceInfo->holdingRegisters[6] & 0x1000;    //  WORD_BIT Decimal=13
    deviceInfo->datiBA->BA_command               = parseRegister(deviceInfo->holdingRegisters, 7, true).u32Value;
    deviceInfo->datiBA->BA_OK_1                  = parseRegister(deviceInfo->holdingRegisters, 9).u16Value;
    deviceInfo->datiBA->BA_OK_2                  = parseRegister(deviceInfo->holdingRegisters, 10).u16Value;
    deviceInfo->datiBA->BA_OK_3                  = parseRegister(deviceInfo->holdingRegisters, 11).u16Value;
    deviceInfo->datiBA->BA_OK_4                  = parseRegister(deviceInfo->holdingRegisters, 12).u16Value;
    deviceInfo->datiBA->BA_OK_5                  = parseRegister(deviceInfo->holdingRegisters, 13).u16Value;
    deviceInfo->datiBA->BA_OK_6                  = parseRegister(deviceInfo->holdingRegisters, 14).u16Value;
    deviceInfo->datiBA->BA_OK_7                  = parseRegister(deviceInfo->holdingRegisters, 15).u16Value;
    deviceInfo->datiBA->BA_OK_8                  = parseRegister(deviceInfo->holdingRegisters, 16).u16Value;
    deviceInfo->datiBA->BA_OK_9                  = parseRegister(deviceInfo->holdingRegisters, 17).u16Value;
    deviceInfo->datiBA->BA_OK_10                 = parseRegister(deviceInfo->holdingRegisters, 18).u16Value;
    deviceInfo->datiBA->BA_OK_11                 = parseRegister(deviceInfo->holdingRegisters, 19).u16Value;
    deviceInfo->datiBA->BA_OK_12                 = parseRegister(deviceInfo->holdingRegisters, 20).u16Value;
    deviceInfo->datiBA->BA_OK_13                 = parseRegister(deviceInfo->holdingRegisters, 21).u16Value;
    deviceInfo->datiBA->BA_OK_14                 = parseRegister(deviceInfo->holdingRegisters, 22).u16Value;
    deviceInfo->datiBA->BA_OK_15                 = parseRegister(deviceInfo->holdingRegisters, 23).u16Value;
    deviceInfo->datiBA->BA_OK_16                 = parseRegister(deviceInfo->holdingRegisters, 24).u16Value;
    deviceInfo->datiBA->BA_OK_17                 = parseRegister(deviceInfo->holdingRegisters, 25).u16Value;
    deviceInfo->datiBA->BA_OK_18                 = parseRegister(deviceInfo->holdingRegisters, 26).u16Value;
    deviceInfo->datiBA->BA_OK_19                 = parseRegister(deviceInfo->holdingRegisters, 27).u16Value;
    deviceInfo->datiBA->BA_OK_20                 = parseRegister(deviceInfo->holdingRegisters, 28).u16Value;
    deviceInfo->datiBA->BA_OK_21                 = parseRegister(deviceInfo->holdingRegisters, 29).u16Value;
    deviceInfo->datiBA->BA_OK_22                 = parseRegister(deviceInfo->holdingRegisters, 30).u16Value;
    deviceInfo->datiBA->BA_OK_23                 = parseRegister(deviceInfo->holdingRegisters, 31).u16Value;
    deviceInfo->datiBA->BA_OK_24                 = parseRegister(deviceInfo->holdingRegisters, 32).u16Value;
    deviceInfo->datiBA->BA_OK_25                 = parseRegister(deviceInfo->holdingRegisters, 33).u16Value;
    deviceInfo->datiBA->BA_OK_26                 = parseRegister(deviceInfo->holdingRegisters, 34).u16Value;
    deviceInfo->datiBA->BA_OK_27                 = parseRegister(deviceInfo->holdingRegisters, 35).u16Value;
    deviceInfo->datiBA->BA_OK_28                 = parseRegister(deviceInfo->holdingRegisters, 36).u16Value;
    deviceInfo->datiBA->BA_OK_29                 = parseRegister(deviceInfo->holdingRegisters, 37).u16Value;
    deviceInfo->datiBA->BA_OK_30                 = parseRegister(deviceInfo->holdingRegisters, 38).u16Value;
    deviceInfo->datiBA->BA_OK_31                 = parseRegister(deviceInfo->holdingRegisters, 39).u16Value;
    deviceInfo->datiBA->BA_OK_32                 = parseRegister(deviceInfo->holdingRegisters, 40).u16Value;
    deviceInfo->datiBA->BA_control_type          = parseRegister(deviceInfo->holdingRegisters, 41).u16Value;
}

reg32_union IntegrationPluginMect::parseRegister(uint16_t regs_array[], int nReg, bool doppioRegistro)
{
    reg32_union modbusReg;

    modbusReg.dWord.hi = 0;
    modbusReg.dWord.lo = regs_array[nReg];
    if (doppioRegistro)  {
        modbusReg.dWord.hi = regs_array[nReg + 1];
    }
    return modbusReg;
}

QString IntegrationPluginMect::seconds2String(int totalSeconds)
// Formatta il valore ricevuto in secondi in una stringa di tipo mm:ss o hh:mm:ss
{
    QString timeString;
    int nSecondi = totalSeconds % 60;
    int nMinuti = (totalSeconds / 60) % 60;
    int nOre = ((totalSeconds / 60) / 60);

    if (nOre > 0)  {
        timeString = QString("%1:%2:%3")
                        .arg(nOre, 2, 10, QChar('0'))
                        .arg(nMinuti, 2, 10, QChar('0'))
                        .arg(nSecondi, 2, 10, QChar('0'));
    }
    else  {
        timeString = QString("%1:%2")
                        .arg(nMinuti, 2, 10, QChar('0'))
                        .arg(nSecondi, 2, 10, QChar('0'));
    }
    return timeString;
}

QString     IntegrationPluginMect::minutes2String(int nMinutes)
// Formatta il valore ricevuto in minuti in una stringa di tipo hh:mm
{
    QString szHours("");

    int nHours = nMinutes / 60;
    szHours = QString("%1") .arg(nHours, 2, 10, QLatin1Char('0'));
    szHours.append(":");
    nMinutes = nMinutes % 60;
    szHours.append(QString("%1") .arg(nMinutes, 2, 10, QLatin1Char('0')));
    // Return Value
    return szHours;
}


