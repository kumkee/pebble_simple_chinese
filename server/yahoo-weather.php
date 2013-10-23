<?php
define("FLICKR_KEY", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
define("MYSQLPASS", "xxxxxxxx");
define('MYSQLHOST', 'host.domain');
define('MYSQLUSER', 'username');
define('DBNAME', 'dbname');

error_reporting(0);

$payload = json_decode(file_get_contents('php://input'), true);
if(!$payload) {
	$payload = json_decode("{\"1\": 30000000,\"2\": 120000000,\"3\": \"c\"}", true);
}	
$lat = $payload[1] / 1000000;
$long = $payload[2] / 1000000;
$units = $payload[3];

//$pebbleid = "ABC1234567";
$pebbleid = $_SERVER['HTTP_X_PEBBLE_ID'];
if(empty($pebbleid) || !$pebbleid) {
	$pebbleid = "AXX1234567";
}

$flickrResponse = get_data('http://api.flickr.com/services/rest/?method=flickr.places.findByLatLon&format=json&api_key=' . FLICKR_KEY . '&lat=' . $lat . '&lon=' . $long);
$flickrResponse = json_decode(substr($flickrResponse, 14, strlen($flickrResponse) - 15), true);
$woeid = $flickrResponse['places']['place'][0]['woeid'];
$woename = $flickrResponse['places']['place'][0]['woe_name'];
if($woeid) {
	$xml = simplexml_load_file('http://weather.yahooapis.com/forecastrss?w=' . $woeid . '&u=' . $units);
	$xml->registerXPathNamespace('yweather', 'http://xml.weather.yahoo.com/ns/rss/1.0');

	$condition = $xml->channel->item->xpath('yweather:condition');
	$code = (int)$condition[0]['code'];
	$temperature = (int)round($condition[0]['temp']);
	$updtime = explode(" ", (string)$condition[0]['date']);
	$updtime = explode(":", $updtime[4]);

}
else {
	$code = 3200;
	$temperature = 999;
}

$data = array();

if($code == 3200) {
	$code=48;
}


$data[1] = $temperature;
$data[2] = $code;
$data[3] = (int)$updtime[0];
$data[4] = (int)$updtime[1];



header('Content-Type: application/json, charset=utf-8');
header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
header("Last-Modified: " . gmdate("D, d M Y H:i:s") . " GMT"); 
header("Cache-Control: no-store, no-cache, must-revalidate"); 
header("Cache-Control: post-check=0, pre-check=0", false);
header("Pragma: no-cache");
print json_encode($data);



$geojson = file_get_contents('http://maps.googleapis.com/maps/api/geocode/json?latlng=' . $lat . ',' . $long . '&sensor=false&language=zh-CN');
$geodata = json_decode($geojson, TRUE);
$addcomp = $geodata["results"][0]["address_components"];

$city_idx = 0; $i = 0;
foreach ($addcomp as $componet){
   if($componet["types"][0] == "locality")
	$city_idx = $i;
   $i++;
}

$city = $addcomp[$city_idx]["short_name"];
$prov = $addcomp[$city_idx+1]["short_name"];
$country = $addcomp[$city_idx+2]["short_name"];
$district = $addcomp[$city_idx-1]["short_name"];

//$tbl_name = $pebbleid;
//$tbl_name = "test";
$tbl_name = str_replace(":", "", $pebbleid);
$create_table =
'CREATE TABLE IF NOT EXISTS ' . $tbl_name . '  
(
    id INT NOT NULL AUTO_INCREMENT,
    pbl_id VARCHAR(25) DEFAULT NULL,
    upd_time TIMESTAMP,
    latitude DECIMAL(10,7) DEFAULT NULL,
    longitude DECIMAL(10,7) DEFAULT NULL,
    district VARCHAR(25) DEFAULT NULL,
    city VARCHAR(25) DEFAULT NULL,
    province VARCHAR(25) DEFAULT NULL,
    country VARCHAR(5) DEFAULT NULL,
    PRIMARY KEY(id)
)';

$db = new mysqli(MYSQLHOST, MYSQLUSER, MYSQLPASS, DBNAME);

if ($db->connect_errno) {
        echo "Failed to connect to MySQL: ("
    . $db->connect_errno . ") " . $db->connect_error;
}

$db->query($create_table);
if ($db->query($create_table)) {
//        echo "Table has created\n";
}
else {
        echo "error creating table\n";
	die();
}

$stmt = $db->prepare("INSERT INTO " . $tbl_name . "(pbl_id,latitude,longitude,district,city,province,country) VALUES (?, ?, ?, ?, ?, ?, ?)");
$stmt->bind_param('sddssss', $pebbleid, $lat, $long, $district, $city, $prov, $country);
$stmt->execute();

$stmt->close();

$db->close();



function get_data($url) {
    $ch = curl_init();
    $timeout = 5;
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $timeout);
    $data = curl_exec($ch);
    curl_close($ch);
    return $data;
}

?>
