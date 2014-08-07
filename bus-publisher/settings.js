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
    var data = JSON.parse(fs.readFileSync('./settings.json'));
    settings = extend(settings, data);
  }
} catch(ex) {
  console.error('tried to check and parse settings.json, but couldnt parse do it ', ex);
}

if (process.env["ACCESS_TOKEN"]) {
    settings.access_token = process.env["ACCESS_TOKEN"];
}

module.exports = settings;