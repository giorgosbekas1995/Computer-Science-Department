 function validation(){
	
	if(document.myForm.pass.value != document.myForm.conpass.value){
		
		document.getElementById('passMessage').innerHTML = "wrong password";
		document.getElementById('conpassMessage').innerHTML = "wrong password";
		return false;
	}
	return true;
}


function initMap() {
        var map = new google.maps.Map(document.getElementById('map'), {
          zoom: 8,
          center: {lat: -34.397, lng: 150.644}
        });
        var geocoder = new google.maps.Geocoder();

        document.getElementById('submit').addEventListener('click', function() {
          geocodeAddress(geocoder, map);
        });
      }

      function geocodeAddress(geocoder, resultsMap) {
        var address = document.getElementById('address').value;
        geocoder.geocode({'address': address}, function(results, status) {
          if (status === 'OK') {
          	document.getElementById('MapMessage').innerHTML = "Place exist";
          	document.getElementById('submitMap').addEventListener('click', function() {
          		resultsMap.setCenter(results[0].geometry.location);
            var marker = new google.maps.Marker({
              map: resultsMap,
              position: results[0].geometry.location
            });
        });
          } else {
           document.getElementById('MapMessage').innerHTML = "INVALID INFO";
          }
        });
      }

     