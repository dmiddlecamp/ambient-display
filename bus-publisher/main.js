var settings = require("./settings.js");


// example values:
var sample = { Departures:
   [ { DepartureText: '15 Min',
       DepartureTime: '6/22/2014 6:09:00 PM',
       Actual: 'True',
       Route: '4',
       Terminal: 'P',
       Description: 'Bryant-Penn/Southtown/82St-35W TC',
       DirectionName: 'SOUTHBOUND',
       BlockNumber: 1034,
       VehicleHeading: 0,
       VehicleLatitude: 44.9834408,
       VehicleLongitude: -93.2673636,
       Gate: '' },
     { DepartureText: '6:39',
       DepartureTime: '6/22/2014 6:39:00 PM',
       Actual: 'False',
       Route: '4',
       Terminal: 'L',
       Description: 'Bryant Av/82St-35W TC/Via Lyndale',
       DirectionName: 'SOUTHBOUND',
       BlockNumber: 1039,
       VehicleHeading: 0,
       VehicleLatitude: 0,
       VehicleLongitude: 0,
       Gate: '' },
     { DepartureText: '7:09',
       DepartureTime: '6/22/2014 7:09:00 PM',
       Actual: 'False',
       Route: '4',
       Terminal: 'P',
       Description: 'Bryant-Penn/Southtown/82St-35W TC',
       DirectionName: 'SOUTHBOUND',
       BlockNumber: 1035,
       VehicleHeading: 0,
       VehicleLatitude: 0,
       VehicleLongitude: 0,
       Gate: '' },
     { DepartureText: '7:39',
       DepartureTime: '6/22/2014 7:39:00 PM',
       Actual: 'False',
       Route: '4',
       Terminal: 'L',
       Description: 'Bryant Av/82St-35W TC/Via Lyndale',
       DirectionName: 'SOUTHBOUND',
       BlockNumber: 1037,
       VehicleHeading: 0,
       VehicleLatitude: 0,
       VehicleLongitude: 0,
       Gate: '' },
     { DepartureText: '8:09',
       DepartureTime: '6/22/2014 8:09:00 PM',
       Actual: 'False',
       Route: '4',
       Terminal: 'P',
       Description: 'Bryant-Penn/Southtown/82St-35W TC',
       BlockNumber: 1032,
       SortOrder: 0,
       Gate: '' } ] };

var moment = require('moment');
var request = require('request');
var ApiClient = require("./ApiClient.js");




//NEW FORMAT
var handleBusInfo = function (data) {
    if (!data) {
        console.log("Data was empty");
        return [];
    }

    var now = moment();
    var cutoff = moment().add('minutes', settings.cutoff);
    var results = [];
    for (var i = 0; i < data.length; i++) {
        var obj = data[i],
            time = moment(obj.DepartureTime);

        if ((time > cutoff) || (time < now)) {
            continue;
        }

        if (obj.Route != "4") {
            continue;
        }

        results.push(time.fromNow());
    }

    return results;
};

//OLD FORMAT
//var handleBusInfo = function (data) {
//    if (!data) {
//        console.log("Data was empty");
//        return [];
//    }
//
//    data = data["Departures"];
//    var now = moment();
//    var cutoff = moment().add('minutes', settings.cutoff);
//    var results = [];
//    for (var i = 0; i < data.length; i++) {
//        var obj = data[i];
//        var time = moment(data[i].DepartureTime);
//        if ((time > cutoff) || (time < now)) {
//            continue;
//        }
//        results.push(time.fromNow());
//    }
//
//    return results;
//};

var publishBusInfo = function (times) {
    console.log("Publishing " + times.join(","));
    api.publishEvent("rgb_bus_times", times.join(","));
}

var scheduleNextUpdate = function () {
    //api.publishEvent("rgb_bus_times", null);
    //TODO: sleep until next update time.

    //sleep for two minutes
    setTimeout(updateBusInfo, 60 * 1000);
};

var updateBusInfo = function () {

    request({
            uri: settings.stopUrl,
            method: "GET",
            json: true
        },
        function (error, response, body) {
            if (error) {
                scheduleNextUpdate();
                console.error("Error! " + error);
            }
            else {
                //console.log("GOT BODY ", body);

                var times = handleBusInfo(body);
                publishBusInfo(times);
                scheduleNextUpdate();
            }
        });
};


var api = new ApiClient(settings.apiUrl, settings.access_token);
//api.publishEvent("rgb_motd", "Message Of the Day!");

updateBusInfo();


//var times = handleBusInfo(sample);
//publishBusInfo(times);
