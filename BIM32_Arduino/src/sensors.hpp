#include <Wire.h>
#include <Adafruit_BME280.h> // v2.2.4 https://github.com/adafruit/Adafruit_BME280_Library
#include <Adafruit_BMP085.h> // v1.2.4 https://github.com/adafruit/Adafruit-BMP085-Library
#include "SHT21.h" // https://github.com/markbeee/SHT21
#include "DHTesp.h" // v1.19.0 http://desire.giesecke.tk/index.php/2018/01/30/esp32-dht11/
#include <MAX44009.h> // v1.2.3 https://github.com/dantudose/MAX44009
#include <BH1750.h> // v1.3.0 https://github.com/claws/BH1750
#include <OneWire.h> // v2.3.7 https://github.com/PaulStoffregen/OneWire
#include <DallasTemperature.h> // v3.9.0 https://github.com/milesburton/Arduino-Temperature-Control-Library
#include "bsec.h" // v1.8.1492 https://www.bosch-sensortec.com/software-tools/software/bsec/
#include <Adafruit_PCF8574.h> // v1.1.1 https://github.com/adafruit/Adafruit_PCF8574
#include "DS3232.h" // v0.4.1 https://github.com/RobTillaart/DS3232

OneWire             oneWire(ONE_WIRE_BUS_PIN);
DallasTemperature   term(&oneWire);
DeviceAddress       thermometer;
SHT21               SHT21;
DHTesp              dht;
MAX44009            max_light;
BH1750              lightMeter(0x23);
Adafruit_BMP085     bmp;
Adafruit_BME280     bme;
Adafruit_Sensor     *bme_temp = bme.getTemperatureSensor();
Adafruit_Sensor     *bme_pressure = bme.getPressureSensor();
Adafruit_Sensor     *bme_humidity = bme.getHumiditySensor();
Adafruit_PCF8574    pcf8574;
Bsec                iaqSensor;
DS3231              rtc;

#ifdef __cplusplus
  extern "C"{
#endif
  unsigned int temprature_sens_read();
#ifdef __cplusplus
}
#endif
unsigned int temprature_sens_read();

#define DS18B20_RESOLUTION    12 /* DS18B20 resolution 9,10,11 or 12 bits */

class Sensors {
    public:
        void init(void);
        void read(void);
        void BME680Read(void);
        float get_esp32_temp(bool corr);
        float get_bme280_temp(bool corr);
        float get_bme280_hum(bool corr);
        float get_bme280_pres(bool corr);
        float get_bmp180_temp(bool corr);
        float get_bmp180_pres(bool corr);
        float get_sht21_temp(bool corr);
        float get_sht21_hum(bool corr);
        float get_dht22_temp(bool corr);
        float get_dht22_hum(bool corr);
        float get_ds18b20_temp(bool corr);
        float get_max44009_light(bool corr);
        float get_bh1750_light(bool corr);
        float get_analog_voltage(bool corr);
        float get_bme680_temp(bool corr);
        float get_bme680_hum(bool corr);
        float get_bme680_pres(bool corr);
        float get_bme680_iaq(bool corr);
        uint8_t get_bme680_iaq_accuracy();
        void get_ds3231_timeDate();
        void set_ds3231_timeDate();
        void comfortDevices(bool heater, bool cooler, bool humidifier, bool dehumidifier, bool purifier);

    private:
        bool _bme280_det = false;
        bool _bmp180_det = false;
        bool _sht21_det = false;
        bool _dht22_det = false;
        bool _ds18b20_det = false;
        bool _max44009_det = false;
        bool _bh1750_det = false;
        bool _bme680_det = false;
        bool _pcf8574_det = false;
        bool _ds3231_det = false;
        uint8_t _bme680_bsecState[BSEC_MAX_STATE_BLOB_SIZE] = {0};
        uint16_t _bme680_stateUpdateCounter = 0;
        unsigned int _bme680_stateCounter = 0;
        unsigned int _bme680_stateTimestamp = 0;

        float _esp32_temp = 40400.0;
        float _bme280_temp = 40400.0;
        float _bme280_hum = 40400.0;
        float _bme280_pres = 40400.0;
        float _bmp180_temp = 40400.0;
        float _bmp180_pres = 40400.0;
        float _sht21_temp = 40400.0;
        float _sht21_hum = 40400.0;
        float _dht22_temp = 40400.0;
        float _dht22_hum = 40400.0;
        float _ds18b20_temp = 40400.0;
        float _max44009_light = -1000.0;
        float _bh1750_light = -10000.0;
        float _analog_voltage = -10000.0;
        float _bme680_temp = 40400.0;
        float _bme680_hum = 40400.0;
        float _bme680_pres = 40400.0;
        float _bme680_iaq = 40400.0;
        uint8_t _bme680_iaq_accuracy = 0;

        void _BME280Init(void);
        void _BMP180Init(void);
        void _SHT21Init(void);
        void _DHT22Init(void);
        void _DS18B20Init(void);
        void _MAX44009Init(void);
        void _BH1750Init(void);
        void _BME680Init(void);
        void _PCF8574Init(void);
        bool _BME680_validateIaqSensorStatus(void);
        void _BME680_loadState(void);
        void _BME680_updateState(void);
        void _DS3231Init(void);

        void _BME280Read(void);
        void _BMP180Read(void);
        void _SHT21Read(void);
        void _DHT22Read(void);
        void _DS18B20Read(void);
        void _MAX44009Read(void);
        void _BH1750Read(void);
        void _AnalogRead(void);
        void _ESP32Read(void);
};

/**
 * Initialize all sensors
 */
void Sensors::init(void) {
    _DS18B20Init();
    _DHT22Init();
    _BME280Init();
    _BMP180Init();
    _SHT21Init();
    _MAX44009Init();
    _BH1750Init();
    _BME680Init();
    _PCF8574Init();
    _DS3231Init();
    Serial.println(SEPARATOR);
    Serial.println("Sensor initialization");
    Serial.printf("%s %s%s\r\n", "DS18B20:  ", _ds18b20_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "BME280:   ", _bme280_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "BMP180:   ", _bmp180_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "SHT21:    ", _sht21_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "DHT22:    ", _dht22_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "MAX44009: ", _max44009_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "BH1750:   ", _bh1750_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "BME680:   ", _bme680_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "PCF8574:  ", _pcf8574_det ? "" : "NOT ", "Detected");
    Serial.printf("%s %s%s\r\n", "DS3231:   ", _ds3231_det ? "" : "NOT ", "Detected");
}

/**
 * Reads all sensors
 */
void Sensors::read(void) {
    _BME280Read();
    _BMP180Read();
    _SHT21Read();
    _DHT22Read();
    _DS18B20Read();
    _MAX44009Read();
    _BH1750Read();
    _ESP32Read();
    _AnalogRead();
}

/**
 * Getters
 */
float Sensors::get_esp32_temp(bool corr) {
    return _esp32_temp + (corr ? config.esp32_temp_corr() : 0.0);
}

float Sensors::get_bme280_temp(bool corr) {
    return _bme280_temp + (corr ? config.bme280_temp_corr() : 0.0);
}

float Sensors::get_bme280_hum(bool corr) {
    return _bme280_hum + (corr ? config.bme280_hum_corr() : 0.0);
}

float Sensors::get_bme280_pres(bool corr) {
    return _bme280_pres + (corr ? config.bme280_pres_corr() : 0.0);
}

float Sensors::get_bmp180_temp(bool corr) {
    return _bmp180_temp + (corr ? config.bmp180_temp_corr() : 0.0);
}

float Sensors::get_bmp180_pres(bool corr) {
    return _bmp180_pres + (corr ? config.bmp180_pres_corr() : 0.0);
}

float Sensors::get_sht21_temp(bool corr) {
    return _sht21_temp + (corr ? config.sht21_temp_corr() : 0.0);
}

float Sensors::get_sht21_hum(bool corr) {
    return _sht21_hum + (corr ? config.sht21_hum_corr() : 0.0);
}

float Sensors::get_dht22_temp(bool corr) {
    return _dht22_temp + (corr ? config.dht22_temp_corr() : 0.0);
}

float Sensors::get_dht22_hum(bool corr) {
    return _dht22_hum + (corr ? config.dht22_hum_corr() : 0.0);
}

float Sensors::get_ds18b20_temp(bool corr) {
    return _ds18b20_temp + (corr ? config.ds18b20_temp_corr() : 0.0);
}

float Sensors::get_max44009_light(bool corr) {
    return _max44009_light + (corr ? config.max44009_light_corr() : 0.0);
}

float Sensors::get_bh1750_light(bool corr) {
    return _bh1750_light + (corr ? config.bh1750_light_corr() : 0.0);
}

float Sensors::get_analog_voltage(bool corr) {
    return _analog_voltage + (corr ? config.analog_voltage_corr() : 0.0);
}

float Sensors::get_bme680_temp(bool corr) {
    return _bme680_temp + (corr ? config.bme680_temp_corr() : 0.0);
}

float Sensors::get_bme680_hum(bool corr) {
    return _bme680_hum + (corr ? config.bme680_hum_corr() : 0.0);
}

float Sensors::get_bme680_pres(bool corr) {
    return _bme680_pres + (corr ? config.bme680_pres_corr() : 0.0);
}

float Sensors::get_bme680_iaq(bool corr) {
    return _bme680_iaq + (corr ? config.bme680_iaq_corr() : 0.0);
}

uint8_t Sensors::get_bme680_iaq_accuracy() {
    return _bme680_iaq_accuracy;
}

/**
 * Initialize BME280 sensor
 */
void Sensors::_BME280Init(void) {
    _bme280_det = bme.begin(0x76, &Wire);
    if(!_bme280_det) _bme280_det = bme.begin(0x77, &Wire);
}

/**
 * Initialize BMP180 sensor
 */
void Sensors::_BMP180Init(void) {
    if(bmp.begin()) _bmp180_det = true;
}

/**
 * Initialize SHT21 sensor
 */
void Sensors::_SHT21Init(void) {
    SHT21.begin();
    Wire.beginTransmission(SHT21_ADDRESS);
    Wire.write(0xE7);
    Wire.endTransmission();
    delay(100);
    Wire.requestFrom(SHT21_ADDRESS, 1);
    if(Wire.available() == 1) {
        Wire.read();
        _sht21_det = true;
    }
}

/**
 * Initialize DHT22 sensor
 */
void Sensors::_DHT22Init(void) {
    dht.setup(DHT22_PIN, DHTesp::DHT22);
    dht.getTempAndHumidity();
    dht.getStatus();
    if(dht.getStatus() == 0) _dht22_det = true;
}

/**
 * Initialize DS18B20 sensor
 */
void Sensors::_DS18B20Init(void) {
    term.begin();
    _ds18b20_det = term.getDeviceCount();
    if(_ds18b20_det > 0) {
        term.getAddress(thermometer, 0);
        term.setResolution(thermometer, DS18B20_RESOLUTION);
        term.requestTemperatures();
    }
}

/**
 * Initialize MAX44009 sensor
 */
void Sensors::_MAX44009Init(void) {
    if(!max_light.begin()) _max44009_det = true;
}

/**
 * Initialize BH1750 sensor
 */
void Sensors::_BH1750Init(void) {
    if(lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2)) _bh1750_det = true;
}

/**
 * Initialize PCF8574 port-expander
 */
void Sensors::_PCF8574Init(void) {
    if(pcf8574.begin(0x20, &Wire)) {
        _pcf8574_det = true;
        for(uint8_t i=0; i<8; i++) pcf8574.pinMode(i, OUTPUT);
        for(uint8_t i=0; i<8; i++) pcf8574.digitalWrite(i, LOW);
    }
}

/**
 * Initialize DS3231 RTC
 */
void Sensors::_DS3231Init() {
    if(rtc.begin() == DS3232_OK) {
        _ds3231_det = true;
        get_ds3231_timeDate();
    }
}

/**
 * Initialize BME680 sensor
 */
void Sensors::_BME680Init(void) {
    const uint8_t bsec_config_iaq[] = {
        #include "config/generic_33v_3s_4d/bsec_iaq.txt"
    };
  
    iaqSensor.begin(BME68X_I2C_ADDR_HIGH, Wire);
    _bme680_det = _BME680_validateIaqSensorStatus();
    if(_bme680_det) {
        iaqSensor.setConfig(bsec_config_iaq);
        _BME680_validateIaqSensorStatus();
        _BME680_loadState();

        bsec_virtual_sensor_t sensorList[4] = {
            BSEC_OUTPUT_IAQ,
            BSEC_OUTPUT_RAW_PRESSURE,
            BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
            BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY
        };
        iaqSensor.updateSubscription(sensorList, 4, BSEC_SAMPLE_RATE_LP);
        _BME680_validateIaqSensorStatus();
    }
}

/*
 * Check BME680 Status
 * @return true if there are no problems
 */
bool Sensors::_BME680_validateIaqSensorStatus(void) {
    if(iaqSensor.bsecStatus != BSEC_OK) return false;
    if(iaqSensor.bme68xStatus != BME68X_OK) return false;
    return true;
}

/**
 * Load BME680 state from EEPROM
 */
void Sensors::_BME680_loadState(void) {
    Serial.println(SEPARATOR);
    Serial.print("Read BME680 state file... ");

    File file = LittleFS.open("/bme680.json");
    if(file) {
        while(file.available()) {
            String json = file.readString();

            JsonDocument state;
            DeserializationError errorState = deserializeJson(state, json);

            if(!errorState) {
                _bme680_stateTimestamp = state["timestamp"];
                _bme680_stateCounter = state["counter"];
                for(uint8_t i=0; i<BSEC_MAX_STATE_BLOB_SIZE; i++) {
                    _bme680_bsecState[i] = state["data"][i];
                }

                if(_bme680_stateCounter > 0) {
                    iaqSensor.setState(_bme680_bsecState);
                    _BME680_validateIaqSensorStatus();

                    Serial.println("done");
                }
                else Serial.println("state file is empty");
            }
            else Serial.println(" BME680 state file corrupted");
        }
    }
    else Serial.println(" No BME680 file found");
}

/**
 * Update BME680 status file
 */
void Sensors::_BME680_updateState(void) {
    #define STATE_SAVE_PERIOD  UINT32_C(6 * 60 * 60)           /* 6 hours - 4 times a day */

    if((now() - _bme680_stateTimestamp >= STATE_SAVE_PERIOD) and (iaqSensor.iaqAccuracy >= 3)) {
        Serial.println(SEPARATOR);
        Serial.print("Update BME680 state file... ");

        if(LittleFS.exists("/bme680.json")) {
            iaqSensor.getState(_bme680_bsecState);
            _BME680_validateIaqSensorStatus();

            _bme680_stateTimestamp = now();
            _bme680_stateCounter++;

            char datetime[20];
            sprintf(datetime, "%02d.%02d.%d %02d:%02d:%02d", day(), month(), year(), hour(), minute(), second());

            JsonDocument json;
            json["timestamp"] = _bme680_stateTimestamp;
            json["datetime"] = datetime;
            json["counter"] = _bme680_stateCounter;
            for(uint8_t i=0; i<BSEC_MAX_STATE_BLOB_SIZE; i++) {
                json["data"][i] = _bme680_bsecState[i];
            }

            String data = "";
            serializeJsonPretty(json, data);
            //Serial.println(data);

            File file = LittleFS.open("/bme680.json", "w");
            if(file) {
                file.print(data);
                file.close();
                data = String();
                Serial.println("done");
            }
            else Serial.println("Failed to save BME680 state file");
        }
        else Serial.println("File /bme680.json does not extist");
    }
}

/**
 * Read data from BME280 sensor
 */
void Sensors::_BME280Read(void) {
    if(_bme280_det) {
        _bme280_temp = bme.readTemperature();
        _bme280_hum = bme.readHumidity();
        _bme280_pres = bme.readPressure() / 100.0F;
    }
    else {
        _bme280_temp = 40400.0;
        _bme280_hum = 40400.0;
        _bme280_pres = 40400.0;
    }
}

/**
 * Read data from BMP180 sensor
 */
void Sensors::_BMP180Read(void) {
    if(_bmp180_det) {
        _bmp180_temp = bmp.readTemperature();
        _bmp180_pres = bmp.readPressure() / 100.0F;
    }
    else {
        _bmp180_temp = 40400.0;
        _bmp180_pres = 40400.0;
    }
}

/**
 * Read data from SHT21 sensor
 */
void Sensors::_SHT21Read(void) {
    if(_sht21_det) {
        _sht21_temp = SHT21.getTemperature();
        _sht21_hum = SHT21.getHumidity();
    }
    else {
        _sht21_temp = 40400.0;
        _sht21_hum = 40400.0;
    }
}

/**
 * Read data from DHT22 sensor
 */
void Sensors::_DHT22Read(void) {
    if(_dht22_det) {
        _dht22_temp = dht.getTemperature();
        _dht22_hum = dht.getHumidity();
    }
    else {
        _dht22_temp = 40400.0;
        _dht22_hum = 40400.0;
    }
}

/**
 * Read data from DS18B20 sensor
 */
void Sensors::_DS18B20Read(void) {
    if(_ds18b20_det) {
        _ds18b20_temp = term.getTempC(thermometer);
        term.requestTemperatures();
    }
    else _ds18b20_temp = 40400.0;
}

/**
 * Read data from MAX44009 sensor
 */
void Sensors::_MAX44009Read(void) {
    if(_max44009_det) _max44009_light = max_light.get_lux();
    else _max44009_light = -10000.0;
}

/**
 * Read data from BH1750 sensor
 */
void Sensors::_BH1750Read(void) {
    if(_bh1750_det) _bh1750_light = lightMeter.readLightLevel();
    else _bh1750_light = -10000.0;
}

/**
 * Read data from analog ambient light sensor
 */
void Sensors::_AnalogRead(void) {
    float adc = float(analogRead(PHOTORESISTOR_PIN));
    _analog_voltage = adc / 1241.0;
}

/**
 * Read ESP32 temperature
 */
void Sensors::_ESP32Read(void) {
    _esp32_temp = (temprature_sens_read() - 32) / 1.8;
}

/**
 * Read data from BME680 sensor
 */
void Sensors::BME680Read(void) {
    if(_bme680_det) {
        if(iaqSensor.run()) {
            _bme680_temp = iaqSensor.temperature;
            _bme680_hum = iaqSensor.humidity;
            _bme680_pres = iaqSensor.pressure / 100.0F;
            _bme680_iaq = iaqSensor.iaq;
            _bme680_iaq_accuracy = iaqSensor.iaqAccuracy;
            _BME680_updateState();
        }
        else _BME680_validateIaqSensorStatus();
    }
    else {
        _bme680_temp = 40400.0;
        _bme680_hum = 40400.0;
        _bme680_pres = 40400.0;
        _bme680_iaq = 40400.0;
    }
}

/**
 * Get time & date from DS3231 RTC
 */
void Sensors::get_ds3231_timeDate() {
    if(_ds3231_det) {
        rtc.read();
        setTime(
            rtc.hours(), 
            rtc.minutes(), 
            rtc.seconds(), 
            rtc.day(), 
            rtc.month(), 
            2000 + rtc.year()
        );
    }
}

/**
 * Set time & date to DS3231 RTC
 */
void Sensors::set_ds3231_timeDate() {
    if(_ds3231_det) {
        if(year() > 2000) rtc.setYear(year() - 2000);
        rtc.setMonth(month());
        rtc.setDay(day());
        rtc.setWeekDay(weekday());
        rtc.setHours(hour());
        rtc.setMinutes(minute());
        rtc.setSeconds(second());
        rtc.write();
    }
}

/**
 * Send data to PCF8574
 */
void Sensors::comfortDevices(bool heater, bool cooler, bool humidifier, bool dehumidifier, bool purifier) {
    if(_pcf8574_det) {
        pcf8574.digitalWrite(0, heater);
        pcf8574.digitalWrite(1, cooler);
        pcf8574.digitalWrite(2, humidifier);
        pcf8574.digitalWrite(3, dehumidifier);
        pcf8574.digitalWrite(4, purifier);
    }
}