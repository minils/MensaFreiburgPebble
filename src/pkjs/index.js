var xhrRequest = function(url, type, callback) {
    var xhr = new XMLHttpRequest();
    xhr.onload = function() {
	callback(this.responseText);
    };
    xhr.open(type, url);
    xhr.send();
}

var keys = require('message_keys');

function sendNextItem(items, index)
{
    var key = keys.MondayFood1 + index;
    var dict = {};
    dict[key] = items[index];

    Pebble.sendAppMessage(dict, function(e) {
	//console.log(JSON.stringify(dict));
	index++;
	if (index < items.length) {
	    sendNextItem(items, index);
	} else {
	    console.log('Last item sent');
	}
    }, function(e) {
	console.log('Error sending food data to Pebble');
    });
}

function sendList(items)
{
    console.log(JSON.stringify(items));
    sendNextItem(items, 0);
}

function getFood()
{
    var url = "https://minils.de/uni/api/";
    
    xhrRequest(url, 'GET', function(responseText) {
	var json = JSON.parse(responseText);
	sendList(json);
    });
	
}

Pebble.addEventListener('ready', function(e) {
    console.log('PebbleKit JS ready!');
    getFood();
});

Pebble.addEventListener('appmessage', function(e) {
    console.log('AppMessage received');
    getFood();
});
