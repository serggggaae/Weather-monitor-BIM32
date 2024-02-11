import ComfortFn from "./ComfortFn";
import Languages from "../../Languages";
import PageHeader from "../../fragments/PageHeader";
import RangeInput from "../../fragments/RangeInput";
import SelectInput from "../../fragments/SelectInput";
import Menu from "../../menu/Menu";
import SaveRestart from "../SaveRestart";

class Comfort extends ComfortFn {
    render() {
        let text = new Languages();
        let lang = this.props.config.lang;

        let temperatures = [
            text.get('forecast', lang), text.get('wirelessSensor', lang),
            "Thingspeak", "BME280", "BMP180", "SHT21", "DHT22", "DS18B20", "BME680"
        ];

        let humidities  = [
            text.get('forecast', lang), text.get('wirelessSensor', lang),
            "Thingspeak", "BME280", "SHT21", "DHT22", "BME680"
        ];

        let wSensors = [];
        for(let i=0; i<2; i++) wSensors.push(text.get('wirelessSensor', lang) + ' ' + i);

        let wsensorTemp = [];
        for(let i=0; i<5; i++) wsensorTemp.push(text.get('temperature', lang) + ' ' + i);

        let fields = [];
        for(let i=1; i<=8; i++) fields.push(text.get('field', lang) + ' ' + i);

        return(<>
            <Menu language={lang} />
            
            <div className="d-flex justify-content-center">
                <div className="content m-2 m-lg-5">
                    <PageHeader h="2" text={text.get('comfort', lang)} />

                    {this.props.config.hasOwnProperty('comfort') && 
                    <div className="row">
                        <div className="col col-12 col-md-6 p-4">
                            <div className="border border-secondary rounded p-3 sensor">
                                <SelectInput value={'comfort.temp.source'}
                                    label={text.get('tempSource', lang)}
                                    options={temperatures}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />
                                {this.props.config.comfort.temp.source == 1 && <>
                                    <SelectInput value={'comfort.temp.wsensNum'}
                                        label={text.get('wirelessSensorNumber', lang)}
                                        options={wSensors}
                                        config={this.props.config} 
                                        changedConfig={(this.props.changedConfig)}
                                    />
                                    <SelectInput value={'comfort.temp.sens'}
                                        label={text.get('temperatureSensorNumber', lang)}
                                        options={wsensorTemp} 
                                        config={this.props.config} 
                                        changedConfig={this.props.changedConfig}
                                    />
                                </>}
                                {this.props.config.comfort.temp.source == 2 &&
                                <SelectInput value={'comfort.temp.thing'}
                                    label={text.get('field', lang)}
                                    options={fields}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />}
                                <RangeInput value={'comfort.temp.max.0'}
                                    label={text.get('tempMax', lang)} 
                                    min="-50"
                                    max="100"
                                    limitMin={this.props.config.comfort.temp.min[0]}
                                    limitMax="100"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"°C"}
                                />
                                <RangeInput value={'comfort.temp.max.1'}
                                    label={text.get('hysteresis', lang)} 
                                    min="0"
                                    max="10"
                                    limitMin="0"
                                    limitMax="10"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"°C"}
                                />
                                <hr />
                                <RangeInput value={'comfort.temp.min.0'}
                                    label={text.get('tempMin', lang)} 
                                    min="-50"
                                    max="100"
                                    limitMin="-50"
                                    limitMax={this.props.config.comfort.temp.max[0]}
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"°C"}
                                />
                                <RangeInput value={'comfort.temp.min.1'}
                                    label={text.get('hysteresis', lang)} 
                                    min="0"
                                    max="10"
                                    limitMin="0"
                                    limitMax="10"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"°C"}
                                />
                            </div>
                        </div>

                        <div className="col col-12 col-md-6 p-4">
                            <div className="border border-secondary rounded p-3 sensor">
                                <SelectInput value={'comfort.hum.source'}
                                    label={text.get('humSource', lang)}
                                    options={humidities}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />
                                {this.props.config.comfort.hum.source == 1 &&
                                <SelectInput value={'comfort.hum.wsensNum'}
                                    label={text.get('wirelessSensorNumber', lang)}
                                    options={wSensors}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />}
                                {this.props.config.comfort.hum.source == 2 &&
                                <SelectInput value={'comfort.hum.thing'}
                                    label={text.get('field', lang)}
                                    options={fields}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />}
                                <RangeInput value={'comfort.hum.max.0'}
                                    label={text.get('humMax', lang)} 
                                    min="0"
                                    max="100"
                                    limitMin={this.props.config.comfort.hum.min[0]}
                                    limitMax="100"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"%"}
                                />
                                <RangeInput value={'comfort.hum.max.1'}
                                    label={text.get('hysteresis', lang)} 
                                    min="0"
                                    max="10"
                                    limitMin="0"
                                    limitMax="10"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"%"}
                                />
                                <hr />
                                <RangeInput value={'comfort.hum.min.0'}
                                    label={text.get('humMin', lang)} 
                                    min="0"
                                    max="100"
                                    limitMin="0"
                                    limitMax={this.props.config.comfort.hum.max[0]}
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"%"}
                                />
                                <RangeInput value={'comfort.hum.min.1'}
                                    label={text.get('hysteresis', lang)} 
                                    min="0"
                                    max="10"
                                    limitMin="0"
                                    limitMax="10"
                                    step="1"
                                    config={this.props.config} 
                                    changedConfig={this.changedConfig}
                                    units={"%"}
                                />
                            </div>
                        </div>

                        <div className="col col-12 col-md-6 p-4">
                            <div className="border border-secondary rounded p-3 sensor">
                                <SelectInput value={'comfort.iaq.source'}
                                    label={text.get('indexForAirQuality', lang)}
                                    options={['--', 'BME680']}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />
                                <table className="table mt-4 text-center">
                                    <thead>
                                        <tr>
                                            <th>{text.get('indexForAirQuality', lang)}</th>
                                            <th>{text.get('airQuality', lang)}</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <tr className="table-success">
                                            <td>&lt; 100</td>
                                            <td>{text.get('good', lang)}</td>
                                        </tr>
                                        <tr className="table-warning">
                                            <td>100 - 200</td>
                                            <td>{text.get('polluted', lang)}</td>
                                        </tr>
                                        <tr className="table-danger">
                                            <td>&gt; 200</td>
                                            <td>{text.get('heavilyPolluted', lang)}</td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>

                        <div className="col col-12 col-md-6 p-4">
                            <div className="border border-secondary rounded p-3 sensor">
                                <SelectInput value={'comfort.co2.source'}
                                    label={'CO2'}
                                    options={['--', text.get('wirelessSensor', lang)]}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />
                                {this.props.config.comfort.co2.source == 1 &&
                                <SelectInput value={'comfort.co2.wsensNum'}
                                    label={text.get('wirelessSensorNumber', lang)}
                                    options={wSensors}
                                    config={this.props.config} 
                                    changedConfig={(this.props.changedConfig)}
                                />}
                                <table className="table mt-4 text-center">
                                    <thead>
                                        <tr>
                                            <th>{text.get('co2Level', lang)}</th>
                                            <th>{text.get('airQuality', lang)}</th>
                                        </tr>
                                    </thead>
                                    <tbody>
                                        <tr className="table-success">
                                            <td>&lt; 800</td>
                                            <td>{text.get('good', lang)}</td>
                                        </tr>
                                        <tr className="table-warning">
                                            <td>800 - 1400</td>
                                            <td>{text.get('polluted', lang)}</td>
                                        </tr>
                                        <tr className="table-danger">
                                            <td>&gt; 1400</td>
                                            <td>{text.get('heavilyPolluted', lang)}</td>
                                        </tr>
                                    </tbody>
                                </table>
                            </div>
                        </div>
                    </div>}
                </div>
            </div>

            <SaveRestart config={this.props.config} save="1" restart="1" />
        </>)
    };
};

export default Comfort;