<?php

error_reporting(0);
/*
$payload = json_decode(file_get_contents('php://input'), true);
if(!$payload) {
	$payload = json_decode("{\"1\": 40424248,\"2\": -2008086,\"3\": \"c\"}", true);
}	
$lat = $payload[1] / 1000000;
$long = $payload[2] / 1000000;
$units = $payload[3];

$pebbleid = "ABC1234567";

try {
	$pebbleid = $_SERVER['HTTP_X_PEBBLE_ID'];
}
catch (Exception $e) { }

$flickrResponse = get_data('http://api.flickr.com/services/rest/?method=flickr.places.findByLatLon&format=json&api_key=' . FLICKR_KEY . '&lat=' . $lat . '&lon=' . $long);
$flickrResponse = json_decode(substr($flickrResponse, 14, strlen($flickrResponse) - 15), true);
$woeid = $flickrResponse['places']['place'][0]['woeid'];
$woename = $flickrResponse['places']['place'][0]['woe_name'];
*/
$woeid = "2165360";
$units = "c";
if($woeid) {
	$xml = simplexml_load_file('http://weather.yahooapis.com/forecastrss?w=' . $woeid . '&u=' . $units);
	$xml->registerXPathNamespace('yweather', 'http://xml.weather.yahoo.com/ns/rss/1.0');

	$condition = $xml->channel->item->xpath('yweather:condition');
	$code = (int)$condition[0]['code'];
	$temperature = (int)round($condition[0]['temp']);
	$updtime = explode(" ", (string)$condition[0]['date']);
	$updtime = explode(":", $updtime[4]);

	//$astronomy = $xml->channel->xpath('yweather:astronomy');
	//$sunrise = str_replace(' ', '', $astronomy[0]['sunrise']);
	//$sunset = str_replace(' ', '', $astronomy[0]['sunset']);

	//$forecast = $xml->channel->item->xpath('yweather:forecast');
	//$forecasthigh = (int)$forecast[0]['high'];
	//$forecastlow = (int)$forecast[0]['low'];

	//$location = $xml->channel->xpath('yweather:location');
	//$city = $location[0]['city'];
}
else {

	$code = 3200;
	$temperature = 999;
	$forecasthigh = 99;
	$forecasthigh = 99;

}

$data = array();

if($code == 3200) {
	$code=48;
}


$data[1] = $temperature;
//$data[2] = $forecasthigh; 
//$data[3] = $forecastlow;
$data[2] = $code;
$data[3] = (int)$updtime[0];
$data[4] = (int)$updtime[1];

/*
$logentry = date('Y-m-d H:i:s') . PHP_EOL . $pebbleid . PHP_EOL . json_encode($payload) . PHP_EOL . json_encode($data) . PHP_EOL; 
$fp = @fopen('log.txt', 'a');  
fputs($fp, $logentry . PHP_EOL);  
@fclose($fp);  
*/

$json = file_get_contents('http://maps.googleapis.com/maps/api/geocode/json?latlng=31.38505597,120.92879549&sensor=false&language=zh-CN');
$geocode = json_decode($json, TRUE);
$addcomp = $geocode["results"][1]["address_components"];
$district = $addcomp[1]["short_name"];
$city = $addcomp[2]["short_name"];
$prov = $addcomp[3]["short_name"];
$country = $addcomp[4]["short_name"];

header('Content-Type: application/json; charset=utf-8');
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); 
header("Cache-Control: no-store, no-cache, must-revalidate"); 
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
print json_encode($data);

print PHP_EOL;
print $district;
print PHP_EOL;
print $city;
print PHP_EOL;
print $prov;
print PHP_EOL;
print $country;


/*function get_data($url) {
    $ch = curl_init();
    $timeout = 5;
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
    $data = curl_exec($ch);
    curl_close($ch);
    return $data;
}
*/

?>
