var fs = require('fs');
var extend = require('xtend');

var settings = {
    apiUrl: "https://api.spark.io",
    access_token: "YOUR_ACCESS_TOKEN",

    stopUrl: "http://svc.metrotransit.org/NexTrip/20031?format=json",

    //how many minutes of stops do we want to show
    cutoff: 60,

    dailyStartTime: "06:00",
    dailyStopTime: "22:30"
};

try {
  if (fs.existsSync('./settings.json')) {
    var some_json_string = fs.readFileSync('./settings.json');
    var the_json = JSON.parse(some_json_string);
    settings = extend(settings, the_json);
  }
} catch(ex) {
  console.error('tried to check and parse settings.json, but couldnt parse do it ', ex);
}

module.exports = settings;