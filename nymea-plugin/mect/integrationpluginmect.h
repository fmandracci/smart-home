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

#ifndef INTEGRATIONPLUGINMECT_H
#define INTEGRATIONPLUGINMECT_H


#include "integrations/integrationplugin.h"
#include "plugintimer.h"

#include "modbus.h"
#include "mect_types.h"

#include <QString>
#include <QStringList>
#include <QHash>
#include <QTimer>

class IntegrationPluginMect: public IntegrationPlugin
{
    Q_OBJECT

    Q_PLUGIN_METADATA(IID "io.nymea.IntegrationPlugin" FILE "integrationpluginmect.json")
    Q_INTERFACES(IntegrationPlugin)


public:
    explicit IntegrationPluginMect();
    ~IntegrationPluginMect();
    void init() override;
    void setupThing(ThingSetupInfo *info) override;
    void executeAction(ThingActionInfo *info) override;
    void thingRemoved(Thing *thing) override;

private slots:

    void        updateFieldData();

private:

    void        thermostatData2Plugin(Thing *mySelf, struct dati_device *deviceInfo);
    void        electricData2Plugin(Thing *mySelf, struct dati_device *deviceInfo);
    void        antitheftData2Plugin(Thing *mySelf, struct dati_device *deviceInfo);
    void        parse_hr_termostato(dati_device *deviceInfo);
    void        parse_hr_electricp(dati_device *deviceInfo);
    void        parse_hr_antifurto(dati_device *deviceInfo);
    reg32_union parseRegister(uint16_t regs_array[], int nReg, bool doppioRegistro = false);
    QString     seconds2String(int totalSeconds);                           // Formatta il valore ricevuto in secondi in una stringa di tipo mm:ss o hh:mm:ss
    QString     minutes2String(int nMinutes);                               // Formatta il valore ricevuto in minuti in una stringa di tipo hh:mm

    QHash<Thing*, QTimer*>              m_simulationTimers;
    QHash<Thing*, struct dati_device*>  m_devicesInfo;

    PluginTimer                        *m_refreshTimer = nullptr;
    QStringList                         lstThermoStatus;
    QStringList                         lstBaStatus;

};

#endif // INTEGRATIONPLUGINMECT_H
