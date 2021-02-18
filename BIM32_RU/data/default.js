function logout(){
  document.cookie='auth=0';
  window.location='login.htm';
}

$(function(){
  $('#loading').removeClass('active');
  $(document).click(function(e){
    if(!$('#navmenu').is(e.target) && !$('#nav-toggle').is(e.target) && !$('#mn').is(e.target)){
      document.getElementById('nav-toggle').checked = false;
    }
  });

  $('#restore').click(function(){
    if(confirm('Внимание! Все настройки монитора погоды обнулятся. Вы действительно хотите всё сбросить?')){
      $('#loading').addClass('active');
      $('#restore').text("Отправка...");
      $('#restore').css("background-color", "#FA0");
      let config = `{
  "ssid": "",
  "pass": "",
  "mask": "",
  "dns1": "",
  "dns2": "",
  "ip": "",
  "gw": "",
  "type": false,
  "lang": "ru",
  "brt": 3,
  "brday": 100,
  "brnight": 100,
  "hd": 8,
  "md": 10,
  "hn": 21,
  "mn": 30,
  "temp_out": 0,
  "hum_out": 0,
  "pres_out": 0,
  "temp_in": 0,
  "hum_in": 0,
  "light_in": 7,
  "bat_disp": 1,
  "utc": 0,
  "dlst": false,
  "ntp": "time.nist.gov",
  "city": "Moscow,RU",
  "cityid": "524901",
  "lat": "55.75222",
  "lon": "37.615555",
  "appid": "",
  "appkey": "",
  "citysearch": 0,
  "provider": 0,
  "bmet": 0,
  "bmpt": 0,
  "shtt": 0,
  "dhtt": 0,
  "bmeh": 0,
  "shth": 0,
  "dhth": 0,
  "bmep": 0,
  "bmpp": 0,
  "max": 0,
  "bh": 0,
  "wtempc": 0,
  "whumc": 0,
  "wpresc": 0,
  "wlightc": 0,
  "wbatc": 150,
  "chnum": 1,
  "wexpire": 10,
  "battype": 1,
  "tupd": 5,
  "mqttsend": false,
  "thngsend": false,
  "nrdmsend": false,
  "mqttrcv": false,
  "thngrcv": false,
  "nrd_tout": 0,
  "nrd_hout": 0,
  "nrd_pout": 0,
  "nrd_tin": 0,
  "nrd_hin": 0,
  "nrd_lin": 1,
  "mqttServer": "",
  "mqttPort": 0,
  "mqttLogin": "",
  "mqttPass": "",
  "fq1": false,
  "fq2": false,
  "fq3": false,
  "fq4": false,
  "fq5": false,
  "fq6": false,
  "fq7": false,
  "fq8": false,
  "mqttF1": "",
  "mqttF2": "",
  "mqttF3": "",
  "mqttF4": "",
  "mqttF5": "",
  "mqttF6": "",
  "mqttF7": "",
  "mqttF8": "",
  "fd1": [0,0],
  "fd2": [0,0],
  "fd3": [0,0],
  "fd4": [0,0],
  "fd5": [0,0],
  "fd6": [0,0],
  "fd7": [0,0],
  "fd8": [0,0],
  "f1": [0,0],
  "f2": [0,0],
  "f3": [0,0],
  "f4": [0,0],
  "f5": [0,0],
  "f6": [0,0],
  "f7": [0,0],
  "f8": [0,0],
  "rdkey": "",
  "wrkey": "",
  "chid": 0,
  "mto": 1,
  "mho": 1,
  "mpo": 1,
  "mti": 1,
  "mhi": 1,
  "mli": 1,
  "tto": 1,
  "tho": 1,
  "tpo": 1,
  "tti": 1,
  "thi": 1,
  "tli": 1,
  "tbt": 1,
  "tq1": false,
  "tq2": false,
  "tq3": false,
  "tq4": false,
  "tq5": false,
  "tq6": false,
  "tq7": false,
  "tq8": false,
  "mqttT1": "",
  "mqttT2": "",
  "mqttT3": "",
  "mqttT4": "",
  "mqttT5": "",
  "mqttT6": "",
  "mqttT7": "",
  "mqttT8": "",
  "dp0": 6,
  "dp1": 2,
  "dp2": 2,
  "dp3": 2,
  "dp4": 0,
  "dp5": 0,
  "dt0": 1,
  "dt1": 1,
  "dt2": 1,
  "dt3": 1,
  "dt4": 1,
  "dt5": 1,
  "dc0": 65535,
  "dc1": 65535,
  "dc2": 65535,
  "dc3": 65535,
  "dc4": 65535,
  "dc5": 65535,
  "ds0": "C",
  "ds1": "C",
  "ds2": "C",
  "ds3": "C",
  "ds4": "C",
  "ds5": "C",
  "sdisp_sensitivity": 101,
  "ws_brt": 1,
  "ws_brightd": 24,
  "ws_brightn": 6,
  "ws_hd": 7,
  "ws_md": 40,
  "ws_hn": 21,
  "ws_mn": 9,
  "ws_sdisp_sensitivity": 26,
  "ws_light_in": 7
}`;

      $.ajax({
	      url: 'esp/save.php',
	      method: 'post',
        data: `CONFIG=${config}`,
	      success: function(answ){
          if(answ != "OK") alert(answ);
          $('#loading').removeClass('active');
          $('#restore').css("background-color", "#AF0");
          $('#restore').text("Сброшено");
          setTimeout(function(){
            $('#restore').css("background-color", "#F1F1F1");
            $('#restore').text("Сбросить");
          }, 3000);
	      }
      });
      return false;
    }
  });
});
