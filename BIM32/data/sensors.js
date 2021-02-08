function logout(){
  $.ajax({
    type:"POST",
    url:"esp/logout.php",
    cache:false
  }).done();
  document.cookie='auth=0';
  window.location='http://radiokot.ru';
}

$(function(){
  $(document).click(function(e){
    if(!$('#navmenu').is(e.target) && !$('#nav-toggle').is(e.target) && !$('#mn').is(e.target)){
      document.getElementById('nav-toggle').checked = false;
    }
  });

  $.getJSON(`config.json?R=${Math.random()}`,function(json){
    config = json;
    for(var b in config){
      try{
        $(`#${b}`).val(config[b]);
      }
      catch(b){}
    }
  });

  setInterval(function(){
    $.ajax({
	    url: 'esp/sensors.php',
	    method: 'get',
	    dataType: 'json',
	    success: function(data){
        for(var b in data){
          let cr = b.slice(1);
          if(data[b] == 40400) $(`#${b}`).html('--');
          else $(`#${b}`).html((Number(data[b]) + Number($(`#${cr}`).val())).toFixed(1));
        }
        $('#loading').removeClass('active');
	    }
    });
  },5000);

  $('form').submit(function(){
    $('#loading').addClass('active');
    config.bmet = Number($('#bmet').val());
    config.bmpt = Number($('#bmpt').val());
    config.shtt = Number($('#shtt').val());
    config.dhtt = Number($('#dhtt').val());
    config.bmeh = Number($('#bmeh').val());
    config.shth = Number($('#shth').val());
    config.dhth = Number($('#dhth').val());
    config.bmep = Number($('#bmep').val());
    config.bmpp = Number($('#bmpp').val());
    config.max  = Number($('#max').val());
    config.bh   = Number($('#bh').val());
    $.ajax({
	    url: 'esp/save.php',
	    method: 'post',
      data: `CONFIG=${JSON.stringify(config, null, 2)}`,
	    success: function(answ){
        if(answ != "OK") alert(answ);
        $('#loading').removeClass('active');
	    }
    });
    return false;
  });
});