/*
* Copyright (C) 2011-2014 MediaTek Inc.
* 
* This program is free software: you can redistribute it and/or modify it under the terms of the 
* GNU General Public License version 2 as published by the Free Software Foundation.
* 
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along with this program.
* If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _MTK_THERMAL_MONITOR_H
#define _MTK_THERMAL_MONITOR_H

#include <linux/thermal.h>

/*
 *  MTK_THERMAL_WRAPPER_BYPASS = 1 (use original Linux Thermal API)
 *  MTK_THERMAL_WRAPPER_BYPASS = 0 (use MTK Thermal API Monitor)
 */
#define MTK_THERMAL_WRAPPER_BYPASS 0

#if MTK_THERMAL_WRAPPER_BYPASS
/* Original LTF API */
#define mtk_thermal_zone_device_register      thermal_zone_device_register
#define mtk_thermal_zone_device_unregister    thermal_zone_device_unregister
#define mtk_thermal_cooling_device_unregister thermal_cooling_device_unregister
#define mtk_thermal_cooling_device_register   thermal_cooling_device_register
#define mtk_thermal_zone_bind_cooling_device  thermal_zone_bind_cooling_device  

#else

extern
struct thermal_zone_device *mtk_thermal_zone_device_register_wrapper
( 
    char *type,
	int  trips, 
	void *devdata,
	const struct thermal_zone_device_ops *ops,
	int tc1, 
	int tc2, 
	int passive_delay, 
	int polling_delay
);

extern 
void mtk_thermal_zone_device_unregister_wrapper
(
    struct thermal_zone_device *tz
);

extern 
struct thermal_cooling_device *mtk_thermal_cooling_device_register_wrapper
(
     char *type, 
     void *devdata, 
     const struct thermal_cooling_device_ops *ops
);

extern 
void mtk_thermal_cooling_device_unregister_wrapper
(
    struct thermal_cooling_device *cdev
);

extern int mtk_thermal_zone_bind_cooling_device_wrapper
(
    struct thermal_zone_device *tz,
    int trip,
    struct thermal_cooling_device *cdev
);

extern int mtk_thermal_zone_bind_trigger_trip
(
	struct thermal_zone_device *tz, 
	int trip, 
	int mode
);
#define mtk_thermal_zone_device_register      mtk_thermal_zone_device_register_wrapper
#define mtk_thermal_zone_device_unregister    mtk_thermal_zone_device_unregister_wrapper
#define mtk_thermal_cooling_device_unregister mtk_thermal_cooling_device_unregister_wrapper
#define mtk_thermal_cooling_device_register   mtk_thermal_cooling_device_register_wrapper
#define mtk_thermal_zone_bind_cooling_device  mtk_thermal_zone_bind_cooling_device_wrapper

#endif

typedef enum 
{
    MTK_THERMAL_SENSOR_CPU = 0, 
    MTK_THERMAL_SENSOR_ABB, 
    MTK_THERMAL_SENSOR_PMIC, 
    MTK_THERMAL_SENSOR_BATTERY, 
    MTK_THERMAL_SENSOR_MD1, 
    MTK_THERMAL_SENSOR_MD2, 
    MTK_THERMAL_SENSOR_WIFI, 
    
    MTK_THERMAL_SENSOR_COUNT
} MTK_THERMAL_SENSOR_ID;

extern int mtk_thermal_get_temp(MTK_THERMAL_SENSOR_ID id);

#endif 
