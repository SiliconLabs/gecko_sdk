from typing import Any, Dict
from cc_base import cc_validate


class cc_multilevel_sensor(cc_validate):
    """Command Class Multilevel Sensor

    Raises:
        ValueError: Thrown when an invalid sensor name is used
        ValueError: Thrown when an invalid sensor scale is used
    """
    # From protocol/z-wave/ZAF/CommandClasses/MultilevelSensor/CC_MultilevelSensor_SensorHandlerTypes.h
    #
    # #define SENSOR_SCALE_DEFAULT        0x00
    # #define SENSOR_SCALE_CELSIUS        0x00
    # #define SENSOR_SCALE_FAHRENHEIT     0x01
    # #define SENSOR_SCALE_PERCENTAGE     0x00
    # #define SENSOR_SCALE_DIMENSIONLESS  0x01
    # #define SENSOR_SCALE_LUX            0x01
    # #define SENSOR_SCALE_WATT           0x00
    # #define SENSOR_SCALE_BTU_H          0x01 /*Btu/h*/
    # #define SENSOR_SCALE_ABSOLUTE_HUMIDITY  0x01 /*g/m3*/
    # #define SENSOR_SCALE_METER_SQUARE_SECOND 0x00 /*m/s^2*/

    # /**
    #  * Defined possible sensor types
    #  */
    # typedef enum sensor_name{
    #   SENSOR_NAME_AIR_TEMPERATURE = 0x00,
    #   SENSOR_NAME_GENERAL_PURPOSE,
    #   SENSOR_NAME_ILLUMINANCE,
    #   SENSOR_NAME_POWER,
    #   SENSOR_NAME_HUMIDITY,
    #   SENSOR_NAME_ACCELERATION_X,
    #   SENSOR_NAME_ACCELERATION_Y,
    #   SENSOR_NAME_ACCELERATION_Z,
    #   SENSOR_NAME_MAX_COUNT
    # }sensor_name_t;

    _names = [
        'SENSOR_NAME_AIR_TEMPERATURE',
        'SENSOR_NAME_GENERAL_PURPOSE',
        'SENSOR_NAME_ILLUMINANCE',
        'SENSOR_NAME_POWER',
        'SENSOR_NAME_HUMIDITY',
        'SENSOR_NAME_ACCELERATION_X',
        'SENSOR_NAME_ACCELERATION_Y',
        'SENSOR_NAME_ACCELERATION_Z',
        'SENSOR_NAME_MAX_COUNT'
    ]

    _scales = [
        'SENSOR_SCALE_DEFAULT',
        'SENSOR_SCALE_CELSIUS',
        'SENSOR_SCALE_FAHRENHEIT',
        'SENSOR_SCALE_PERCENTAGE',
        'SENSOR_SCALE_DIMENSIONLESS',
        'SENSOR_SCALE_LUX',
        'SENSOR_SCALE_WATT',
        'SENSOR_SCALE_BTU_H',
        'SENSOR_SCALE_ABSOLUTE_HUMIDITY',
        'SENSOR_SCALE_METER_SQUARE_SECOND'
    ]

    def __init__(self) -> None:
        """Constructor
        """
        super().__init__('zw_cc_multilevel_sensor', [
            'cc_multilevel_sensor_config.c.jinja', 'cc_multilevel_sensor_config.h.jinja'], 'sensors')

    def _validate(self, configuration: Dict[str, Dict[str, Any]]):
        for key, value in configuration[self.component][self.variable].items():
            # A key represents one instance but since this is a dictionary
            # we don't need to ensure that it is unique because python would
            # throw an error in case of non unique keys
            if value['name'] not in self._names:
                raise ValueError(
                    'Invalid name {} for sensor for {}'.format(value['name'], key))
            for scale in value['scales']:
                if scale not in self._scales:
                    raise ValueError(
                        'Invalid scale {} for sensor for {}'.format(scale, key))
